#ifndef CONFIG_P_H
#define CONFIG_P_H

#include <string>
#include <mutex>
#include "bases/export_handling.h"
#include ROVIZ_CONFIG_IMPL_INCLUDE

class RovizItem;

template<typename T>
class ConfigPrivate
{
public:
    ConfigPrivate();

    RovizItem *parent;
    std::string name;
    ConfigImpl<T> impl;
    typename ConfigStorageType<T>::type val;
    std::mutex mtx;
    bool changed, restart_after_change;
};

#endif // CONFIG_P_H
