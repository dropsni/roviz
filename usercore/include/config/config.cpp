
#include "config.h"

template<>
Config<int>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType::type &default_value, int min, int max, bool restart_when_changed)
    : ConfigImpl<T>(_this)
{
    this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(min, max);
}

template<>
Config<double>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType::type &default_value, double min, double max, bool restart_when_changed)
    : ConfigImpl<T>(_this)
{
    this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(min, max);
}

template<>
Config<std::string>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType::type &default_value, std::function<std::string (std::string)> checker, bool restart_when_changed)
    : ConfigImpl<T>(_this)
{
    this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(checker);
}

template<>
Config<std::list<std::string> >::Config(RovizItem *parent, const std::string &name, const ConfigStorageType::type &default_index, const std::list<std::string> &possibilities, bool restart_when_changed)
    : ConfigImpl<T>(_this)
{
    this->init(parent, name, default_index, restart_when_changed);
    _this->impl.init(possibilities);
}

template<typename T>
ConfigStorageType<T>::type Config::value()
{
    std::lock_guard<std::mutex> lock;

    return _this->value;
}

template<typename T>
bool Config::changed()
{
    std::lock_guard<std::mutex> lock;

    return _this->changed;
}

template<typename T>
ConfigImplBase *Config::getImplBase() const
{
    return &_this->impl;
}

template<typename T>
void Config::init(RovizItem *parent, const std::string &name, const ConfigStorageType::type &default_value, bool restart_when_changed)
{
    _this->parent = parent;
    _this->name = name;
    _this->val_tmp = _this->val = _this->impl.load(default_value);

    _this->changed = false;
    _this->restart_after_change = restart_when_changed;
}
