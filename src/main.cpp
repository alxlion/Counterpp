#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <regex>

#include "counter.h"

using namespace std;

void help(char *argv[]);

int main(int argc, char *argv[])
{

    Counter *sc = NULL;
    vector<string>* extensions = new vector<string>();

    // Execute SupCount with arguments
    if(argc > 1) {

        if(strcmp(argv[1], "help") == 0) {
            help(argv);
            return 1;
        }

        if(argc > 2) {
            for(int i(argc-1); i > 1; i--) {
                extensions->push_back(string(argv[i]));
            }
        }

        sc = new Counter(
                    new Folder(argv[1]),
                    extensions
                    );

    } else { // Execute SupCount with stdin

        string path;
        string tmp_ext;

        cout << "Enter folder location: " << endl;
        getline(cin, path);

        cout << "Extensions (space separated without point): ";
        getline(cin, tmp_ext);

        *extensions = Utils::split(tmp_ext, ' ');

        sc = new Counter(
                    new Folder(path),
                    extensions
                    );

    }


    sc->process();
    cout << *sc << endl;

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
    cout << "Usage: " << argv[0] << " [path] extensions" << endl;
    cout << "\nextensions: list all extension you want separated by space without point\n" << endl;
}
