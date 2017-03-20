#ifndef FILE_PATH_H
#define FILE_PATH_H

#include <string>

class FilePath
{
public:
    enum Mode
    {
        AnyFile,
        ExistingFile,
        MultipleFiles,
        Directory
    };

    FilePath(std::string path, bool is_dir = false);
    std::string path(void);
    bool isDir(void);
    bool isFile(void);

private:
    std::string path;
    bool is_dir;
};

#endif // FILE_PATH_H
