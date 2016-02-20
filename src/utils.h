#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class Utils
{
public:

    template<typename T>
    static void format(ostream& out, string title, vector<T>* values) {

        out << left << setw(30) << setfill(' ') << title;

        for(int i(0); i < values->size(); i++) {
            out << setw(3) << setfill(' ') << " |" << setw(6) << values->at(i);
        }

        out << endl;

    }

    static void separator(ostream& out) {
        out << left << setw(55) << setfill('-') << "-" << endl;
    }

    static vector<string> split(string & str, char sep) {
        vector<string> trimmed;
        string tmp;

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

    static string trim(string str) {
        int i;
        while ((i = str.find_first_of(" \n\t")) != -1)
            str.erase(i,1);

        return str;
    }
};

#endif // UTILS_H
