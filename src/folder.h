#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <vector>
#include "file.h"

class Folder
{
public:
    Folder(std::string path);
    ~Folder();

    /* Getters */
    std::string getPath() { return _path; }
    std::vector<File*> getFiles() { return _files; }

    /* Setters */
    void addFile(File* f) { _files.push_back(f); }

private:
    std::string _path;
    std::vector<File*> _files;
};

#endif // FOLDER_H
