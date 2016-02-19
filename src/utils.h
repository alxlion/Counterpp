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
    static void printInTab(string title, int* values) {
        cout << left << setw(30) << setfill(' ') << title;

        for(int i(0); i < sizeof(values)/sizeof(values[0]); i++) {
            cout << setw(3) << setfill(' ') << " |" << setw(6) << values[i];
        }

        cout << endl;
    }

    static void printSeparator() {
        cout << left << setw(55) << setfill('-') << "-" << endl;
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
