#ifndef FOLDER_H
#define FOLDER_H

#include <string>

using namespace std;

class Folder
{
public:
    Folder(string path);

    /* Getters */
    string getPath() { return _path; }

private:
    string _path;
};

#endif // FOLDER_H
