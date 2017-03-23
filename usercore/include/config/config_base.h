#ifndef CONFIG_BASE_H
#define CONFIG_BASE_H

#include <QObject>

#include "bases/export_handling.h"

class ROVIZ_EXPORT_CLASS ConfigBase
{
public:
    virtual ~ConfigBase() = default;
    virtual ConfigImplBase *getImplBase(void) const = 0;
};

#endif // CONFIG_BASE_H
