#ifndef CONFIG_IMPL_DEV_BASE_H
#define CONFIG_IMPL_DEV_BASE_H

#include <QObject>

class QWidget;

class ConfigImplDevBase : public QObject
{
public:
    virtual QWidget *widget(void) = 0;
    virtual bool restartAfterChange(void) const = 0;

public slots:
    virtual void changed(void) = 0;
};

#endif // CONFIG_IMPL_DEV_BASE_H
