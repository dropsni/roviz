#ifndef CFG_DOUBLE_H
#define CFG_DOUBLE_H

#include "config/config.h"

class CfgDouble : public Config
{
public:
    CfgDouble(RovizItem *item_to_restart = nullptr);
    ~Config() = default;

    QWidget *widget(void) const override;
};

#endif // CFG_DOUBLE_H
