#ifndef SUPCOUNT_H
#define SUPCOUNT_H

#include <string>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <map>
#include <regex>

#include "folder.h"
#include "file.h"
#include "utils.h"

using namespace std;

/**
 * @class
 * Main class to compute line counting in source files
 *
 */
class Counter
{
public:
    Counter(Folder* folder, vector<string>* allowed_extensions);
    void process();
    void constructFilesFromFolder(Folder* f);
    void linesCount(File* f, int* result);
    void printTableFiles() const;
    void printTableResult() const;
    ~Counter();
    
    /* Getters */
    map<File*, int*> getResult() { return _result; }

private:

    /* Variables */
    Folder* _folder;
    vector<string>*_allowed_extensions;
    vector<File*> _files;
    map<File*, int*> _result;
    int _total_lines;
    int _total_comments;

    /* Methods */
    bool isValid(string name) const;
};

#endif // SUPCOUNT_H
