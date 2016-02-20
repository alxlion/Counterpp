#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <vector>
#include "file.h"

using namespace std;

class Folder
{
public:
    Folder(string path);
    ~Folder();

    /* Getters */
    string getPath() { return _path; }
    vector<File*> getFiles() { return _files; }

    /* Setters */
    void addFile(File* f) { _files.push_back(f); }

private:
    string _path;
    vector<File*> _files;
};

#endif // FOLDER_H
