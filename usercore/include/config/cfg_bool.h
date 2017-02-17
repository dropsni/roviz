#ifndef CFG_BOOL_H
#define CFG_BOOL_H

#include "config/config.h"

class QCheckBox;

// I started to implement with this, use this as a reference to continue

class CfgBool : public Config
{
public:
    CfgBool(std::string name, bool default_value, RovizItem *parent, bool restart_when_changed = false);
    ~Config() = default;

    QWidget *widget(void) const override;

private:
    QCheckBox *checkbox;
};

#endif // CFG_BOOL_H
