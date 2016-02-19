#ifndef FILE_H
#define FILE_H

#include <string>

using namespace std;

class File
{
public:
    File(string path);

    /* Getters */
    string getExtension() { return _extension; }
    string getName()  { return _name; }
    string getPath() { return _path; }

private:
    string _name;
    string _extension;
    string _path;
};

#endif // FILE_H
