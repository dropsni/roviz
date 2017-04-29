#ifndef CONFIG_STORAGE_TYPE_H
#define CONFIG_STORAGE_TYPE_H

#include "config/file_path.h"

template<typename T>
class ConfigStorageType
{ public: typedef T type;};

template<>
class ConfigStorageType<std::list<std::string> >
{ public: typedef int type; };

template<>
class ConfigStorageType<FilePath>
{ public: typedef std::list<std::string> type; };

#endif // CONFIG_STORAGE_TYPE_H
