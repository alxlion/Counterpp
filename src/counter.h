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
    void constructTreeFromFolder(Folder* f);
    void linesCount(File* const f, int* result);

    /* Getters */
    Folder* getRoot() { return _folder; }
    vector<Folder*> getSubFolders() { return _sub_folders; }
    
private:

    /* Variables */
    Folder* _folder;
    vector<string>* _allowed_extensions;
    vector<Folder*> _sub_folders;

    /* Methods */
    bool isValid(const string name) const;


friend ostream& operator<< (ostream &out, Counter &c);
};



#endif // SUPCOUNT_H
