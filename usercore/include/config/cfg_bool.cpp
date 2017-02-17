
#include "cfg_bool.h"

#include <QString>
#include <QVariant>
#include <QCheckBox>
#include "core/roviz_item.h"

CfgBool::CfgBool(std::string name, bool default_value, RovizItem *parent, bool restart_when_changed)
    : Config(parent)
{
    this->checkbox = new QCheckBox(QString::fromStdString(name));

    QVariant variant = parent->settingsScope()->value("config/CfgBool/" + QString::fromStdString(name));

    if(variant.isValid())
        this->checkbox->setChecked(variant.toBool());
    else
        this->checkbox->setChecked(default_value);

    connect(this->checkbox, &QCheckBox::clicked,
            this, &CfgBool::stateChanged);
}

QWidget *CfgBool::widget() const
{
    return this->checkbox;
}
