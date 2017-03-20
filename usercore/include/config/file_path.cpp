
#include "file_path.h"

FilePath::FilePath(std::string path, bool is_dir)
{
    this->file_path = path;
    this->is_dir = is_dir;
}

std::string FilePath::path()
{
    return this->file_path;
}

bool FilePath::isDir()
{
    return this->is_dir;
}

bool FilePath::isFile()
{
    return !this->is_dir;
}
