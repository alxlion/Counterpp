#include "counter.h"

Counter::Counter(Folder* folder, vector<string>* allowed_extensions)
    : _folder(folder), _allowed_extensions(allowed_extensions) { }

Counter::~Counter() {

    // Free _files File pointers
    for(int i = 0; i < _files.size(); i++) {
        delete[] _files[i];
    }

    // Free _result File and int pointers
    for(auto it = _result.begin(); it != _result.end(); ++it) {
        delete it->first;
        delete it->second;
    }

    delete _allowed_extensions;
}

/**
 * Get the number of files in the directory and add it to the current result map
 *
 */
void Counter::process() {

   constructFilesFromFolder(_folder);

   for(int i(0); i < _files.size(); i++) {

       // If the file extension is allowed
       if ( find(_allowed_extensions->begin(), _allowed_extensions->end(), _files[i]->getExtension()) != _allowed_extensions->end() ) {
           int* current_source_count = new int[2]{0, 0};
           linesCount(_files[i], current_source_count);

           _result.insert(pair<File*, int*>(_files[i], current_source_count));
           _total_lines += current_source_count[0];
           _total_comments += current_source_count[1];
       }
   }

}

/**
 * Browses all files in the directory and add these in the files vector
 *
 * @param f Folder to browse
 */
void Counter::constructFilesFromFolder(Folder* f) {

    DIR* dir;
    struct dirent* entry;

    if( dir = opendir(f->getPath().c_str()) ) {

        while(entry = readdir(dir)){

            // Get all files from directory expects directories
            if( isValid(string(entry->d_name)) && entry->d_type == DT_REG) {
                _files.push_back(new File(string(f->getPath() + "/" + entry->d_name)));
            } else if ( isValid(string(entry->d_name)) && entry->d_type == DT_DIR) {
                constructFilesFromFolder(new Folder(f->getPath() + "/" + entry->d_name));
            }

        }

        closedir(dir);
    }
}

/**
 * Counts the number of line of code and comments
 *
 * @param f File to count lines
 * @param result to save code and comment number
 */
void Counter::linesCount(File* f, int* result) {

    ifstream file(f->getPath());
    string line;
    smatch match;
    bool block(false);

    while(getline(file, line)) {

        // C, C++, C#, JAVA, PHP, JAVASCRIPT
        if(f->getExtension() == "c" || f->getExtension() == "cpp" ||
                f->getExtension() == "h" || f->getExtension() == "hpp" ||
                f->getExtension() == "cs" || f->getExtension() == "java" ||
                f->getExtension() == "php" || f->getExtension() == "js") {

            regex c_regex("^(?!A-Za-z) *(//|/\\*|\\*/)", regex_constants::ECMAScript);
            bool reg = regex_search(line, match, c_regex);

            if (reg || block) {
                if(Utils::trim(match.str()) == "/*")
                    block = true;
                if(Utils::trim(match.str()) == "*/")
                    block = false;
                result[1]++;
            } else {
                result[0]++;
            }

        }

        // HTML
        if(f->getExtension() == "ejs" || f->getExtension() == "htm" || f->getExtension() == "xhtml") {

            regex c_regex("^(?!A-Za-z) *<!--.*-->", regex_constants::ECMAScript);
            bool reg = regex_search(line, match, c_regex);

            if (reg) {
                result[1]++;
            } else {
                result[0]++;
            }

        }

        // PYTHON
        if(f->getExtension() == "py") {

            regex c_regex("^(?!A-Za-z) *#", regex_constants::ECMAScript);
            bool reg = regex_search(line, match, c_regex);

            if (reg) {
                result[1]++;
            } else {
                result[0]++;
            }

        }
    }

}

/**
 * Checks if the file is a valid file
 *
 * @param name String name of the file *
 * @return true, if the file is valid. Else false.
 */
bool Counter::isValid(string name) const {
    return name != "." && name != ".." && name[0] != '.';
}

void Counter::printTableFiles() const {

    Utils::printSeparator();
    cout << left << setw(30) << setfill(' ') << "File" << " | #lines" << " | # comments" << endl;
    Utils::printSeparator();

    for(auto it = _result.begin(); it != _result.end(); ++it) {
        Utils::printInTab(it->first->getName(), it->second);
    }
}

void Counter::printTableResult() const {
    int t[2] = {_total_lines, _total_comments};

    Utils::printSeparator();
    Utils::printInTab("Total", t);
    Utils::printSeparator();
}
