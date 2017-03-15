#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include "bases/export_handling.h"
#include ROVIZ_CONFIG_IMPL_INCLUDE
#include "config/config_p.h"

class RovizItem;

template<typename T>
class Config
{
friend class RovizItemBase;

public:
    Config(RovizItem *parent, std::string name, ConfigStorageType<T>::type default_value, bool restart_when_changed = false);
    ~Config();

    ConfigStorageType<T>::type value(void);
    bool changed(void);

private:
    std::unique_ptr<ConfigPrivate<T> > _this;
};

#endif // CONFIG_H
