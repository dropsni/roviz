
#include "config/file_path.h"

FilePath::FilePath(std::string path, bool is_dir)
{
    this->file_path = path;
    this->is_dir = is_dir;
}

std::string FilePath::path() const
{
    return this->file_path;
}

bool FilePath::isDir() const
{
    return this->is_dir;
}

bool FilePath::isFile() const
{
    return !this->is_dir;
}
