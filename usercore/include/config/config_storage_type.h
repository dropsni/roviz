#ifndef CONFIG_STORAGE_TYPE_H
#define CONFIG_STORAGE_TYPE_H

template<typename T>
class ConfigStorageType
{ public: typedef T type; };

template<>
class ConfigStorageType<std::list<std::string> >
{ public: typedef int type; };

template<>
class ConfigStorageType<FilePath>
{ public: typedef int std::string; };

#endif // CONFIG_STORAGE_TYPE_H
