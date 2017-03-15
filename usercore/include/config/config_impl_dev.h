#ifndef CONFIG_IMPL_DEV_H
#define CONFIG_IMPL_DEV_H

#include "config/config_p.h"

class QWidget;

template<typename T>
class ConfigImplDev
{
public:
    ConfigImplDev(ConfigPrivate<T> config);
    QWidget *widget();

private:
    ConfigPrivate *cfg;
};

#endif // CONFIG_IMPL_DEV_H
