#ifndef CONFIG_IMPL_DEV_BASE_H
#define CONFIG_IMPL_DEV_BASE_H

#include <QObject>

class QWidget;

class ConfigImplDevBase
{
public:
    virtual QWidget *widget(void) const = 0;
    virtual bool restartAfterChange(void) const = 0;
    virtual void changed(void) = 0;
};

#endif // CONFIG_IMPL_DEV_BASE_H
