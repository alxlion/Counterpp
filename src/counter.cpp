#include "counter.h"

Counter::Counter(Folder* folder, std::vector<std::string>* allowed_extensions)
    : _folder(folder), _allowed_extensions(allowed_extensions) { }

/**
 * Count process
 */
void Counter::process() {

   constructTreeFromFolder(_folder);

   // Root folder browsing
   for(int i(0); i < _folder->getFiles().size(); i++) {

       File* current_file = _folder->getFiles().at(i);

       int* current_source_count = new int[2]{0, 0};
       linesCount(current_file, current_source_count);

       current_file->setSourceCount(current_source_count[0]);
       current_file->setCommentCount(current_source_count[1]);

   }

   // Sub folders browsing
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
void Counter::constructTreeFromFolder(Folder* f) {

    DIR* dir;
    struct dirent* entry;


    if( dir = opendir(f->getPath().c_str()) ) {

        while(entry = readdir(dir)){

            // Add valid files to folder and recurse if it's a directory
            if( isValid(std::string(entry->d_name)) && entry->d_type == DT_REG) {
                f->addFile(new File(std::string(f->getPath() + "/" + entry->d_name)));
            } else if ( std::string(entry->d_name) != "." && std::string(entry->d_name) != ".." && entry->d_type == DT_DIR) {
                _sub_folders.push_back(new Folder(f->getPath() + "/" + entry->d_name));
                constructTreeFromFolder(_sub_folders.back());
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
void Counter::linesCount(File* const f, int* result) {

    std::ifstream file(f->getPath());
    std::string line;
    std::smatch match;
    bool block(false);

    while(std::getline(file, line)) {

        // C, C++, C#, JAVA, PHP, JAVASCRIPT
        if(f->getExtension() == "c" || f->getExtension() == "cpp" ||
                f->getExtension() == "h" || f->getExtension() == "hpp" ||
                f->getExtension() == "cs" || f->getExtension() == "java" ||
                f->getExtension() == "php" || f->getExtension() == "js") {

            std::regex c_regex("^(?!A-Za-z) *(//|/\\*|\\*/)", std::regex_constants::ECMAScript);
            bool reg = std::regex_search(line, match, c_regex);

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
        if(f->getExtension() == "html" || f->getExtension() == "htm" || f->getExtension() == "xhtml") {

            std::regex c_regex("^(?!A-Za-z) *<!--.*-->", std::regex_constants::ECMAScript);
            bool reg = std::regex_search(line, match, c_regex);

            if (reg) {
                result[1]++;
            } else {
                result[0]++;
            }

        }

        // PYTHON
        if(f->getExtension() == "py") {

            std::regex c_regex("^(?!A-Za-z) *#", std::regex_constants::ECMAScript);
            bool reg = std::regex_search(line, match, c_regex);

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
bool Counter::isValid(const std::string name) const {

    std::string ext = name.substr(name.find_first_of(".") + 1, name.length());

    if (std::find(_allowed_extensions->begin(), _allowed_extensions->end(), ext) != _allowed_extensions->end())
        return name[0] != '.';

    return false;


}

std::ostream& operator<< (std::ostream &out, Counter &c) {

    int total_source(0), total_comment(0);

    Utils::separator(out);
    out << std::left << std::setw(30) << std::setfill(' ') << "File" << " | #lines" << " | #comments" << std::endl;
    Utils::separator(out);

    // Print root folder files and their results
    for(int i = 0; i < c.getRoot()->getFiles().size(); i++) {
        File* current_file = c.getRoot()->getFiles().at(i);

        Utils::format(out, current_file->getName(), new std::vector<int>{current_file->sourceCount(), current_file->commentCount()});

        total_source += current_file->sourceCount();
        total_comment += current_file->commentCount();
    }

    // Print sub folders files and their results
    for(int i = 0; i < c.getSubFolders().size(); i++) {

        for(int j = 0; j < c.getSubFolders()[i]->getFiles().size(); j++) {

            File* current_file = c.getSubFolders()[i]->getFiles()[j];
            Utils::format(out, current_file->getName(), new std::vector<int>{current_file->sourceCount(), current_file->commentCount()});

            total_source += current_file->sourceCount();
            total_comment += current_file->commentCount();
        }

    }

    // Print final result
    int perc = (float)total_comment/(total_source+total_comment)*100.f;
    Utils::separator(out);
    Utils::format(out, "Total", new std::vector<std::string>{std::to_string(total_source), std::to_string(total_comment) + "("+ std::to_string(perc) + "%)"});
    Utils::separator(out);

}
