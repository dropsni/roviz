#ifndef CONFIG_BASE_H
#define CONFIG_BASE_H

class ConfigImplBase;

class ConfigBase
{
public:
    virtual ConfigImplBase *getImplBase(void) const = 0;
};

#endif // CONFIG_BASE_H
