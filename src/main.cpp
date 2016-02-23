#include <iostream>
#include <vector>
#include <string>

#include "counter.h"

void help(char *argv[]);

int main(int argc, char *argv[])
{

    Counter *sc = NULL;
    std::vector<std::string>* extensions = new std::vector<std::string>();

    // Execute with arguments
    if(argc > 1) {

        if(strcmp(argv[1], "help") == 0) {
            help(argv);
            return 1;
        }

        if(argc > 2) {
            for(int i(argc-1); i > 1; i--) {
                extensions->push_back(std::string(argv[i]));
            }
        }

        sc = new Counter(
                    new Folder(argv[1]),
                    extensions
                    );

    } else { // Execute with stdin

        std::string path;
        std::string tmp_ext;

        std::cout << "Enter folder location: " << std::endl;
        std::getline(std::cin, path);

        std::cout << "Extensions (space separated without point): ";
        std::getline(std::cin, tmp_ext);

        *extensions = Utils::split(tmp_ext, ' ');

        sc = new Counter(
                    new Folder(path),
                    extensions
                    );

    }


    sc->process();
    std::cout << *sc << std::endl;

    delete sc;
    delete extensions;

    return 0;
}

/**
 * Shows the usage of the program
 *
 * @param argv[] Program arguments
 */
void help(char *argv[]) {
    std::cout << "Usage: " << argv[0] << " [path] extensions" << std::endl;
    std::cout << "\nextensions: list all extension you want separated by space without point\n" << std::endl;
}
