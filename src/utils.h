#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

class Utils
{
public:

    template<typename T>
    static void format(std::ostream& out, std::string title, std::vector<T>* values) {

        out << std::left << std::setw(30) << std::setfill(' ') << title;

        for(int i(0); i < values->size(); i++) {
            out << std::setw(3) << std::setfill(' ') << " |" << std::setw(6) << values->at(i);
        }

        out << std::endl;

    }

    static void separator(std::ostream& out) {
        out << std::left << std::setw(55) << std::setfill('-') << "-" << std::endl;
    }

    static std::vector<std::string> split(std::string & str, char sep) {

        std::vector<std::string> trimmed;
        std::string tmp;

        for(char & c : str) {
            if(c == ' ') {
                trimmed.push_back(tmp);
                tmp = "";
            } else {
                tmp += c;
            }
        }

        trimmed.push_back(tmp);
        tmp = "";

        return trimmed;
    }

    static std::string trim(std::string str) {
        int i;
        while ((i = str.find_first_of(" \n\t")) != -1)
            str.erase(i,1);

        return str;
    }
};

#endif // UTILS_H
