#ifndef CONFIG_IMPL_DEV_H
#define CONFIG_IMPL_DEV_H

#include <functional>
#include <QObject>
#include "config/config_p.h"
#include "config/config_impl_dev_base.h"

class QWidget;
class QHBoxLayout;
class QLabel;

template<typename T>
class ConfigImplDev : public ConfigImplDevBase
{
public:
    ConfigImplDev(ConfigPrivate<T> *config);
    QWidget *widget() const override;
    ConfigStorageType<T>::type load(const ConfigStorageType<T>::type &default_value);
    bool restartAfterChange(void) const override;

    // The only thing that's really needed by Config
    void init(int min, int max); // Int
    void init(double min, double max); // Double
    void init(std::function<std::string (std::string)> checker); // String
    void init(const std::list<std::string> &possibilities); // List TODO check 'API' version (possibilities)
    // TODO File Path

public slots:
    void changed(void) override;

private:
    ConfigPrivate<T> *_this;
    QWidget *main_widget;
    ConfigStorageType<T>::type tmp_val;
    bool tmp_changed;

    void initMainWidget(QWidget *sub_widget);
};

#endif // CONFIG_IMPL_DEV_H
