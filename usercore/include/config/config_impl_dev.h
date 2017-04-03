#ifndef CONFIG_IMPL_DEV_H
#define CONFIG_IMPL_DEV_H

#include <functional>
#include <QObject>
#include "config/config_impl_dev_base.h"
#include "config/config_storage_type.h"
#include "config/file_path.h"
#include "bases/export_handling.h"

class QWidget;
class QHBoxLayout;
class QLabel;

template<typename T>
class ConfigPrivate;

template<typename T>
class ROVIZ_EXPORT_CLASS ConfigImplDev : public ConfigImplDevBase
{
public:
    ConfigImplDev(ConfigPrivate<T> *config);
    QWidget *widget() const override;
    void load(void);
    bool restartAfterChange(void) const override;

    // The only thing that's really needed by Config
    void init(int min, int max); // Int
    void init(double min, double max); // Double
    void init(std::function<bool (std::string&)> checker); // String
    void init(const std::list<std::string> &possibilities); // List TODO check 'API' version (possibilities)
    void init(void); // Bool
    void init(const std::string &filter, enum FilePath::Mode file_mode); // File path

    void changed(void) override;

private:
    ConfigPrivate<T> *_this;
    QWidget *main_widget, *data_widget;
    typename ConfigStorageType<T>::type tmp_val;
    bool tmp_changed;

    void initMainWidget(QWidget *sub_widget);
    void save(void);
};

#endif // CONFIG_IMPL_DEV_H
