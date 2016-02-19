#include "file.h"

File::File(string path) : _path(path) {
    _name = path.substr(path.find_last_of("/") + 1, path.length());
    _extension = _name.substr(_name.find_first_of(".") + 1, _name.length());
}
