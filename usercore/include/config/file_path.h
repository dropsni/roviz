#ifndef FILE_PATH_H
#define FILE_PATH_H

#include <string>
#include "bases/export_handling.h"

class ROVIZ_EXPORT_CLASS FilePath
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
    std::string path(void) const;
    bool isDir(void) const;
    bool isFile(void) const;

private:
    std::string file_path;
    bool is_dir;
};

#endif // FILE_PATH_H
