
#include "config.h"

#include "core/template_decl.h"

template<>
Config<int>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed)
    : _this(new ConfigPrivate<int>())
{
    this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(min, max);
}

template<>
Config<double>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed)
    : _this(new ConfigPrivate<double>())
{
    this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(min, max);
}

template<>
Config<std::string>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string&)> checker, bool restart_when_changed)
    : _this(new ConfigPrivate<std::string>())
{
    this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(checker);
}

template<>
Config<std::list<std::string> >::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<std::list<std::string> >::type &default_index, const std::list<std::string> &possibilities, bool restart_when_changed)
    : _this(new ConfigPrivate<std::list<std::string> >())
{
    this->init(parent, name, default_index, restart_when_changed);
    _this->impl.init(possibilities);
}

template<>
Config<bool>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<bool>::type &default_index, bool restart_when_changed)
{
    this->init(parent, name, default_index, restart_when_changed);
    _this->impl.init();
}

template<>
Config<FilePath>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<FilePath>::type &default_index, const std::string &filter, enum FilePath::Mode file_mode, bool restart_when_changed)
{
    this->init(parent, name, default_index, restart_when_changed);
    _this->impl.init(filter, file_mode);
}

template<typename T>
typename ConfigStorageType<T>::type Config<T>::value()
{
    std::lock_guard<std::mutex> lock(_this->mtx);

    return _this->val;
}

template<typename T>
bool Config<T>::changed()
{
    std::lock_guard<std::mutex> lock(_this->mtx);

    return _this->changed;
}

template<typename T>
ConfigImplBase *Config<T>::getImplBase() const
{
    return &_this->impl;
}

template<typename T>
void Config<T>::init(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, bool restart_when_changed)
{
    _this->parent = parent;
    _this->name = name;
    _this->val = _this->impl.load(default_value);

    _this->changed = false;
    _this->restart_after_change = restart_when_changed;
}

INSTANTIATE_CONFIG
