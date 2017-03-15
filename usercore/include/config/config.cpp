
#include "config.h"

template<typename T>
Config::Config(RovizItem *parent, std::string name, ConfigStorageType::type default_value, bool restart_when_changed)
    : ConfigImpl<T>(_this)
{
    bool success;

    _this->parent = parent;
    _this->name = name;
    _this->val_tmp = _this->val = _this->impl.load(name, &success);

    if(!success)
        _this->val_tmp = _this->val = default_value;

    _this->has_changed = _this->has_tmp_changed = false;
    _this->restart_after_change = restart_when_changed;

    // We can't init it in the constructor because we need to init this class first
    _this->impl.init();
}

template<typename T>
ConfigStorageType::type Config::value()
{
    std::lock_guard<std::mutex> lock;

    return _this->value;
}

template<typename T>
bool Config::changed()
{
    std::lock_guard<std::mutex> lock;

    return _this->has_changed;
}
