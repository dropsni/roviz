#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <functional>
#include "bases/export_handling.h"
#include ROVIZ_CONFIG_IMPL_INCLUDE
#include "config/config_p.h"
#include "config/config_base.h"

class RovizItem;
class ConfigImplBase;

template<typename T>
class Config : public ConfigBase
{
friend class RovizItemBase;

public:
    Config(RovizItem *parent, const std::string &name, const ConfigStorageType<T>::type &default_value, int min, int max, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const ConfigStorageType<T>::type &default_value, double min, double max, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const ConfigStorageType<T>::type &default_value, std::function<std::string (std::string)> checker = [](std::string s){return s;}, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const ConfigStorageType<T>::type &default_index, const std::list<std::string> &possibilities, bool restart_when_changed = false);
    ~Config();

    ConfigStorageType<T>::type value(void);
    bool changed(void);

    // TODO Make private and friend?
    ConfigImplBase *getImplBase(void) const override;

private:
    std::unique_ptr<ConfigPrivate<T> > _this;

    void init(RovizItem *parent, const std::string &name, const ConfigStorageType::type &default_value, bool restart_when_changed);
};

#endif // CONFIG_H
