#include "counter.h"

Counter::Counter(Folder* folder, vector<string>* allowed_extensions)
    : _folder(folder), _allowed_extensions(allowed_extensions) { }

/**
 * Count process
 */
void Counter::process() {

   constructFilesFromFolder(_folder);

   for(int i(0); i < _folder->getFiles().size(); i++) {

       File* current_file = _folder->getFiles().at(i);

       int* current_source_count = new int[2]{0, 0};
       linesCount(current_file, current_source_count);

       current_file->setSourceCount(current_source_count[0]);
       current_file->setCommentCount(current_source_count[1]);

   }

   for(int i(0); i < _sub_folders.size(); i++) {

       for(int j(0); j < _sub_folders[i]->getFiles().size(); j++) {

           File* current_file = _sub_folders[i]->getFiles()[j];

           int* current_source_count = new int[2]{0, 0};
           linesCount(current_file, current_source_count);

           current_file->setSourceCount(current_source_count[0]);
           current_file->setCommentCount(current_source_count[1]);

       }

   }

}

/**
 * Browses all files in the directory and adds these in their respective folder vector
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
                f->addFile(new File(string(f->getPath() + "/" + entry->d_name)));
            } else if ( string(entry->d_name) != "." && string(entry->d_name) != ".." && entry->d_type == DT_DIR) {
                _sub_folders.push_back(new Folder(f->getPath() + "/" + entry->d_name));
                constructFilesFromFolder(_sub_folders.back());
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
 * @param name String name of the file
 * @return true, if the file is valid. Else false.
 */
bool Counter::isValid(string name) const {

    string ext =  name.substr(name.find_first_of(".") + 1, name.length());

    if (find(_allowed_extensions->begin(), _allowed_extensions->end(), ext) != _allowed_extensions->end())
        return name[0] != '.';

    return false;


}

ostream& operator<< (ostream &out, Counter &c) {

    int total_source(0), total_comment(0);

    Utils::separator(out);
    out << left << setw(30) << setfill(' ') << "File" << " | #lines" << " | #comments" << endl;
    Utils::separator(out);

    for(int i = 0; i < c.getRoot()->getFiles().size(); i++) {
        File* current_file = c.getRoot()->getFiles().at(i);

        Utils::format(out, current_file->getName(), new vector<int>{current_file->sourceCount(), current_file->commentCount()});

        total_source += current_file->sourceCount();
        total_comment += current_file->commentCount();
    }

    for(int i = 0; i < c.getSubFolders().size(); i++) {

        for(int j = 0; j < c.getSubFolders()[i]->getFiles().size(); j++) {

            File* current_file = c.getSubFolders()[i]->getFiles()[j];
            Utils::format(out, current_file->getName(), new vector<int>{current_file->sourceCount(), current_file->commentCount()});

            total_source += current_file->sourceCount();
            total_comment += current_file->commentCount();
        }

    }

    /* Print result */
    int perc = (float)total_comment/(total_source+total_comment)*100.f;
    Utils::separator(out);
    Utils::format(out, "Total", new vector<string>{to_string(total_source), to_string(total_comment) + "("+ to_string(perc) + "%)"});
    Utils::separator(out);

}
