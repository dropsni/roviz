#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <functional>
#include "bases/export_handling.h"
#include ROVIZ_CONFIG_IMPL_INCLUDE
#include "config/config_p.h"
#include "config/config_base.h"
#include "config/config_storage_type.h"
#include "config/file_path.h"

class RovizItem;

template<typename T>
class ROVIZ_EXPORT_CLASS Config : public ConfigBase
{
public:
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, int min, int max, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, double min, double max, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, std::function<bool (std::string&)> checker = [](std::string s){return s;}, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_index, const std::list<std::string> &possibilities, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_index, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_index, enum FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed = false);

    ~Config() = default;

    typename ConfigStorageType<T>::type value(void);
    bool changed(void);

    // TODO Make private and friend?
    ConfigImplBase *getImplBase(void) const override;

private:
    std::unique_ptr<ConfigPrivate<T> > _this;

    void init(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, bool restart_when_changed);
};

#endif // CONFIG_H
