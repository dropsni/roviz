#ifndef CFG_URL_H
#define CFG_URL_H

#include "config/config.h"

class CfgURL : public Config
{
public:
    CfgURL(RovizItem *item_to_restart = nullptr);
    ~Config() = default;

    QWidget *widget(void) const override;
};

#endif // CFG_URL_H
