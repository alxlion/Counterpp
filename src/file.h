#ifndef FILE_H
#define FILE_H

#include <string>

class File
{
public:
    File(std::string path);

    /* Getters */
    std::string getExtension() { return _extension; }
    std::string getName()  { return _name; }
    std::string getPath() { return _path; }
    int sourceCount() { return _source_count; }
    int commentCount() { return _comment_count; }

    /* Setters */
    void setSourceCount(int nb) { _source_count = nb; }
    void setCommentCount(int nb) { _comment_count = nb; }

private:
    std::string _name;
    std::string _extension;
    std::string _path;

    int _source_count;
    int _comment_count;
};

#endif // FILE_H
