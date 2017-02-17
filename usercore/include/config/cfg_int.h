#ifndef CFG_INT_H
#define CFG_INT_H

#include "config/config.h"

class CfgInt : public Config
{
public:
    CfgInt(RovizItem *item_to_restart = nullptr);
    ~Config() = default;

    QWidget *widget(void) const override;
};

#endif // CFG_INT_H
