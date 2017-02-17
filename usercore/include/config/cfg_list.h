#ifndef CFG_LIST_H
#define CFG_LIST_H

#include "config/config.h"

class CfgList : public Config
{
public:
    CfgList(RovizItem *item_to_restart = nullptr);
    ~Config() = default;

    QWidget *widget(void) const override;
};

#endif // CFG_LIST_H
