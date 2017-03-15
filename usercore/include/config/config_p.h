#ifndef CONFIG_P_H
#define CONFIG_P_H

#include <string>
#include <mutex>
#include "bases/export_handling.h"
#include ROVIZ_CONFIG_IMPL_INCLUDE
#include "config/config_p.h"

class RovizItem;

template<typename T>
class ConfigStorageType
{ typedef T type; };

template<typename T>
class ConfigPrivate
{
public:
    RovizItem *parent;
    std::string name;
    ConfigImpl<T> impl;
    ConfigStorageType<T>::type val, tmp_val;
    std::mutex mtx;
    bool has_changed, has_tmp_changed, restart_after_change;
};

#endif // CONFIG_P_H
