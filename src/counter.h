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

/**
 * @class
 * Main class to compute line counting in source files
 *
 */
class Counter
{
public:
    Counter(Folder* folder, std::vector<std::string>* allowed_extensions);
    void process();
    void constructTreeFromFolder(Folder* f);
    void linesCount(File* const f, int* result);

    /* Getters */
    Folder* getRoot() { return _folder; }
    std::vector<Folder*> getSubFolders() { return _sub_folders; }
    
private:

    /* Variables */
    Folder* _folder;
    std::vector<std::string>* _allowed_extensions;
    std::vector<Folder*> _sub_folders;

    /* Methods */
    bool isValid(const std::string name) const;


friend std::ostream& operator<< (std::ostream &out, Counter &c);
};



#endif // SUPCOUNT_H
