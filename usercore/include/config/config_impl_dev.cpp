
#include "config/config_impl_dev.h"

#include <mutex>
#include <QtGlobal>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QComboBox>
#include <QVariant>
#include "helper/settings_scope.h"
#include "config/config_p.h"
#include "core/template_decl.h"
#include "core/roviz_item.h"

template<typename T>
ConfigImplDev<T>::ConfigImplDev(ConfigPrivate<T> *config)
{
    _this = config;
}

template<typename T>
QWidget *ConfigImplDev<T>::widget() const
{
    return this->main_widget;
}

template<>
ConfigStorageType<int>::type ConfigImplDev<int>::load(const ConfigStorageType<int>::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/int/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toInt();
}

template<>
ConfigStorageType<double>::type ConfigImplDev<double>::load(const ConfigStorageType<double>::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/double/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toDouble();
}

template<>
ConfigStorageType<std::string>::type ConfigImplDev<std::string>::load(const ConfigStorageType<std::string>::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/string/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toString().toStdString();
}

template<>
ConfigStorageType<std::list<std::string> >::type ConfigImplDev<std::list<std::string> >::load(const ConfigStorageType<std::list<std::string> >::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/list/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toInt();
}

template<typename T>
bool ConfigImplDev<T>::restartAfterChange() const
{
    return _this->restart_after_change;
}

template<>
void ConfigImplDev<int>::init(int min, int max)
{
    QLineEdit *edit = new QLineEdit();
    QIntValidator *valid = new QIntValidator(min, max);

    edit->setValidator(valid);
    QObject::connect(edit, &QLineEdit::textEdited,
                     [this](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toInt();
    });
    this->initMainWidget(edit);
}

template<>
void ConfigImplDev<double>::init(double min, double max)
{
    QLineEdit *edit = new QLineEdit();
    // 1000 is the default
    QDoubleValidator *valid = new QDoubleValidator(min, max, 1000);

    edit->setValidator(valid);
    QObject::connect(edit, &QLineEdit::textEdited,
                     [this](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toDouble();
    });
    this->initMainWidget(edit);
}

template<>
void ConfigImplDev<std::string>::init(std::function<bool (std::string&)> checker)
{
    QLineEdit *edit = new QLineEdit();

    // TODO Add custom validator
    QObject::connect(edit, &QLineEdit::textEdited,
                     [this, checker](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_val = text.toStdString();
        this->tmp_changed = checker(this->tmp_val);
    });
    this->initMainWidget(edit);
}

template<>
void ConfigImplDev<std::list<std::string> >::init(const std::list<std::string> &possibilities)
{
    QComboBox *combo = new QComboBox();

    for(const auto &entry : possibilities)
        combo->addItem(QString::fromStdString(entry));

    QObject::connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [combo, this](int)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = combo->currentIndex();
    });
    this->initMainWidget(combo);
}

template<typename T>
void ConfigImplDev<T>::changed()
{
    std::lock_guard<std::mutex> lock(_this->mtx);

    // Only proceed if this item really changed
    if(!this->tmp_changed)
        return;

    _this->changed = true;
    this->tmp_changed = false;

    _this->val = this->tmp_val;
    this->save();

    if(_this->restart_after_change)
        _this->parent->restart();
}

template<typename T>
void ConfigImplDev<T>::initMainWidget(QWidget *sub_widget)
{
    QHBoxLayout *hlayout;
    QLabel *name_label;
    this->main_widget = new QWidget();

    // We assume that is the default layout. Specialize init() if that is not
    // the case.
    hlayout = new QHBoxLayout();
    name_label = new QLabel(QString::fromStdString(_this->name));
    hlayout->addWidget(name_label);
    hlayout->addWidget(sub_widget);
    this->main_widget->setLayout(hlayout);
}

template<>
void ConfigImplDev<int>::save()
{ _this->parent->settingsScope()->setValue("Config/int/" + QString::fromStdString(_this->name), _this->val); }

template<>
void ConfigImplDev<double>::save()
{ _this->parent->settingsScope()->setValue("Config/double/" + QString::fromStdString(_this->name), _this->val); }

template<>
void ConfigImplDev<std::string>::save()
{ _this->parent->settingsScope()->setValue("Config/string/" + QString::fromStdString(_this->name), QString::fromStdString(_this->val)); }

template<>
void ConfigImplDev<std::list<std::string> >::save()
{ _this->parent->settingsScope()->setValue("Config/list/" + QString::fromStdString(_this->name), _this->val); }

INSTANTIATE_CONFIG_IMPL
