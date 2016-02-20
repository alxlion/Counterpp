#include "folder.h"

Folder::Folder(string path) : _path(path) { }

Folder::~Folder() {

    // Dealloc _files File pointers
    for(int i = 0; i < _files.size(); i++) {
        delete[] _files[i];
    }
}
