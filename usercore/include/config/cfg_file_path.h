#ifndef CFG_FILE_PATH_H
#define CFG_FILE_PATH_H

#include "config/config.h"

class CfgFilePath : public Config
{
public:
    CfgFilePath(RovizItem *item_to_restart = nullptr);
    ~Config() = default;

    QWidget *widget(void) const override;
};

#endif // CFG_FILE_PATH_H
