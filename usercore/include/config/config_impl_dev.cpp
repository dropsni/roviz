
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
#include <QCheckBox>
#include <QVariant>
#include <QFileDialog>
#include <QPushButton>
#include "helper/settings_scope.h"
#include "gui/gui_manager.h"
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

template<>
ConfigStorageType<bool>::type ConfigImplDev<bool>::load(const ConfigStorageType<bool>::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/bool/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toBool();
}

template<>
ConfigStorageType<FilePath>::type ConfigImplDev<FilePath>::load(const ConfigStorageType<FilePath>::type &default_value)
{
    QVariant var = _this->parent->settingsScope()->value("Config/file_path/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return default_value;
    else
        return var.toString();
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
void ConfigImplDev::init()
{
    QCheckBox *box = new QCheckBox();

    QObject::connect(box, &QCheckBox::toggled,
                     [this](bool checked)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = checked;
    });
    this->initMainWidget(box);
}

template<typename T>
void ConfigImplDev::init(const std::string &filter, enum FilePath::Mode file_mode)
{
    QFileDialog::FileMode mode;

    switch(file_mode)
    {
        case FilePath::AnyFile:       mode = QFileDialog::AnyFile; break;
        case FilePath::ExistingFile:  mode = QFileDialog::ExistingFile; break;
        case FilePath::MultipleFiles: mode = QFileDialog::ExistingFiles; break;
        case FilePath::Directory:     mode = QFileDialog::Directory; break;
    }

    QHBoxLayout *hlayout = new QHBoxLayout();
    QLineEdit *edit = new QLineEdit();
    QPushButton *button = new QPushButton("File...");

    hlayout->addWidget(edit);
    hlayout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked,
                     [this, mode, filter](void)
    {
        QFileDialog diag = new QFileDialog(GuiManager::instance()->widgetReference(),
                                           "Select...",
                                           "",
                                           filter);
        diag.setFileMode(mode);
        if(!diag.exec())
            return;

        QStringList files = diag.selectedFiles();
        _this->,
    })


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

template<>
void ConfigImplDev<bool>::save()
{ _this->parent->settingsScope()->setValue("Config/bool/" + QString::fromStdString(_this->name), _this->val); }

template<>
void ConfigImplDev<FilePath>::save()
{ _this->parent->settingsScope()->setValue("Config/file_path/" + QString::fromStdString(_this->name), _this->val); }

INSTANTIATE_CONFIG_IMPL
