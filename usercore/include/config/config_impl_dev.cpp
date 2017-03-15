
#include "config/config_impl_dev.h"

#include <mutex>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QComboBox>
#include <QVariant>
#include "core/roviz_item.h"

ConfigImplDev::ConfigImplDev(ConfigPrivate<T> *config)
{
    this->cfg = config;
}

template<typename T>
QWidget *ConfigImplDev::widget() const
{
    return this->main_widget;
}

template<>
ConfigStorageType<int>::type ConfigImplDev::load(const ConfigStorageType::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/int/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toInt();
}

template<>
ConfigStorageType<double>::type ConfigImplDev::load(const ConfigStorageType::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/double/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toDouble();
}

template<>
ConfigStorageType<std::string>::type ConfigImplDev::load(const ConfigStorageType::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/string/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toString();
}

template<>
ConfigStorageType<std::list<std::string> >::type ConfigImplDev::load(const ConfigStorageType::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/list/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toInt();
}

template<typename T>
bool ConfigImplDev::restartAfterChange() const
{
    return _this->restart_after_change;
}

template<>
QWidget *ConfigImplDev<int>::init(int min, int max)
{
    QLineEdit *edit = new QLineEdit();

    edit->setValidator(QIntValidator(this->min, this->max));
    connect(edit, &QLineEdit::textEdited,
            this, [this](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toInt();
    });
    this->initMainWidget(edit);
}

template<>
QWidget *ConfigImplDev<double>::init(double min, double max)
{
    QLineEdit *edit = new QLineEdit();

    edit->setValidator(QDoubleValidator(this->min, this->max));
    connect(edit, &QLineEdit::textEdited,
            this, [this](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toDouble();
    });
    this->initMainWidget(edit);
}

template<>
void ConfigImplDev<std::string>::init(std::function<std::string (std::string)> checker)
{
    QLineEdit *edit = new QLineEdit();

    // TODO Add custom validator
    connect(edit, &QLineEdit::textEdited,
            this, [this](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toStdString();
    });
    this->initMainWidget(edit);
}

template<typename T>
void ConfigImplDev<std::list<std::string> >::init(const std::list<std::__cxx11::string> &possibilities)
{
    QComboBox *combo = new QComboBox();

    // TODO Add custom validator
    connect(combo, &QComboBox::currentIndexChanged,
            this, [combo, this](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = combo->currentIndex();
    });
    this->initMainWidget(combo);
}

template<typename T>
void ConfigImplDev::changed()
{
    std::lock_guard<std::mutex> lock(_this->mtx);

    _this->changed = true;
    this->tmp_changed = false;

    _this->val = this->tmp_val;
}

template<typename T>
void ConfigImplDev::initMainWidget(QWidget *sub_widget)
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
