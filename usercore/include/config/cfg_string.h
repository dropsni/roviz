#ifndef CFG_STRING_H
#define CFG_STRING_H

#include "config/config.h"

class CfgString : public Config
{
public:
    CfgString(RovizItem *item_to_restart = nullptr);
    ~Config() = default;

    QWidget *widget(void) const override;
};

#endif // CFG_STRING_H
