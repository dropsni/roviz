
#include "bases/roviz_item_dev_base.h"
#include "bases/roviz_item_dev_base_p.h"

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "helper/settings_scope.h"
#include "gui/gui_manager.h"
#include "item/item_input.h"
#include "item/item_output.h"
#include "core/template_decl.h"
#include "gui/shared_window.h"
#include "gui/config_dialog.h"
#include "gui/slider_label.h"
#include "bases/stream_base.h"
#include "streams/stream.h"

RovizItemDevBase::RovizItemDevBase(std::string type_name)
    : AbstractItem(QString::fromStdString(type_name)),
      _this(new RovizItemDevBasePrivate(this))
{
    // Each item can display a widget in the shared window.
    // That's prepared here.
    _this->main_widget = new QWidget();
    _this->main_layout = new QHBoxLayout();
    _this->main_control_layout = new QHBoxLayout();
    _this->main_image_layout = new QHBoxLayout();
    _this->control_base = new QWidget();
    _this->collapse_btn = new QPushButton();
    QHBoxLayout *hlayout = new QHBoxLayout();

    _this->control_base->setLayout(_this->main_control_layout);
    _this->collapse_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _this->collapse_btn->setFixedWidth(20);
    _this->collapse_btn->setFixedHeight(20);
    _this->collapse_btn->setText("-");
    hlayout->addWidget(_this->collapse_btn);
    hlayout->addWidget(_this->control_base);
    _this->main_layout->addLayout(hlayout);
    connect(_this->collapse_btn, &QPushButton::clicked,
            _this.data(), &RovizItemDevBasePrivate::collapseBtnClicked);

    _this->main_layout->addLayout(_this->main_image_layout);
    _this->main_widget->setLayout(_this->main_layout);

    hlayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _this->main_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _this->main_control_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _this->main_image_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    hlayout->setAlignment(_this->collapse_btn, Qt::AlignTop | Qt::AlignLeft);

    // We need a parent for the config dialog that get destructed when the
    // application closes.
    _this->conf_diag = new ConfigDialog(GuiManager::instance()->widgetReference());
    _this->config_present = false;
    _this->conf_loaded = false;
    connect(_this->conf_diag, &ConfigDialog::itemsChanged,
            _this.data(), &RovizItemDevBasePrivate::restartIfRunning);
    connect(_this->conf_diag, &ConfigDialog::itemsChanged,
            _this.data(), &RovizItemDevBasePrivate::saveConfigs);

    // Hide the collapse button as long as there is nothing to collapse
    _this->collapse_btn->hide();
    connect(this->settingsScope(), &SettingsScope::parentScopeChanged,
            _this.data(), &RovizItemDevBasePrivate::parentScopeChanged);
    _this->main_widget->hide();
}

RovizItemDevBase::~RovizItemDevBase()
{
    if(this->settingsScope()->parentScope() != nullptr)
        SharedWindow::instance(this->settingsScope()->parentScope())->removeItem(this);
}

QWidget *RovizItemDevBase::widget()
{
    // The main widget contains the trims as well as all output stream widgets
    return _this->main_widget;
}

void RovizItemDevBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // Opens the shared window on a double click
    AbstractItem::mouseDoubleClickEvent(event);
    SharedWindow::instance(this->settingsScope()->parentScope())->load();
    _this->main_widget->parentWidget()->show();
    _this->main_widget->show();
}

void RovizItemDevBase::contextMenuPrepare(QMenu &menu) const
{
    if(!_this->conf_loaded)
    {
        _this->conf_diag->load(this->settingsScope());
        _this->conf_loaded = true;
    }

    if(_this->config_present)
        menu.addAction("Configure", [this]{_this->conf_diag->show();});
}

// TODO Re-enable3
void RovizItemDevBase::stop()
{
//    for(ImageWidget* iw : _this->out_widgets)
//        iw->reset();
}

void RovizItemDevBase::restart()
{
    this->stop();
    this->start();
}

// The following two functions can't have the same name as in RovizItem because
// they are templated and also because functions with the same name already
// exist in AbstractItem (from the itemframework).
template<class T>
Input RovizItemDevBase::addInputBase(std::string name)
{
    ItemInput *in;

    in = this->AbstractItem::addInput(qMetaTypeId<Stream<T>*>(), QString::fromStdString(name));
    connect(in, &ItemInput::dataChanged,
            _this.data(), &RovizItemDevBasePrivate::inputStateChanged);

    return Input(in);
}

template<class T>
Output RovizItemDevBase::addOutputBase(std::string name)
{
    ItemOutput *out;
    Stream<T> *stream = new Stream<T>();

    out = this->AbstractItem::addOutput(qMetaTypeId<Stream<T>*>(), QString::fromStdString(name));
    this->setOutputData(out, stream);
    _this->out_widgets.insert(Output(out), stream->widget());
    _this->main_image_layout->addWidget(stream->widget());

    return Output(out);
}

void RovizItemDevBase::pushOut(StreamObject obj, Output output)
{
    ItemOutput *out;
    StreamBase *stream;

    out = static_cast<ItemOutput*>(output);
    if(out == nullptr || out->data() == nullptr)
        return;

    stream = qobject_cast<StreamBase*>(out->data());
    if(stream == nullptr)
        return;

    emit stream->newObject(obj);

    // Prevent overwriting the default widget if the item is not running
    // TODO Maybe that check is no longer necessary
    if(this->running())
        _this->out_widgets[output]->update();
}

Trim RovizItemDevBase::addTrim(std::string name, int min, int max)
{
    return this->addTrim(name, min, max, (max - min) + 1);
}

Trim RovizItemDevBase::addTrim(std::string name, double min, double max, int steps)
{
    QSlider *slider = new QSlider();
    QVBoxLayout *layout = new QVBoxLayout();
    SliderLabel *label = new SliderLabel(min, max, steps, QString::fromStdString(name));

    slider->setMinimum(0);
    slider->setMaximum(steps - 1);
    slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    slider->setFixedWidth(50);
    layout->addWidget(new QLabel(QString::fromStdString(name)));
    layout->addWidget(slider);
    layout->addWidget(label);
    layout->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    _this->main_control_layout->addLayout(layout);

    connect(slider, &QSlider::valueChanged,
            _this.data(), &RovizItemDevBasePrivate::trimChangedSlot);

    _this->collapse_btn->show();

    // TODO Why?
//    slider->setObjectName(QString::fromStdString(name));
    _this->sliders.append(slider);
    _this->slider_to_label.insert(slider, label);
    return Trim(slider);
}

double RovizItemDevBase::trimValue(Trim trim) const
{
    QSlider *s;

    s = static_cast<QSlider*>(trim);
    if(s)
        return _this->slider_to_label[s]->value();
    else
        return 0.0f;
}

void RovizItemDevBase::trimChanged(Trim, double)
{
}

void RovizItemDevBase::addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker)
{
    _this->conf_diag->addItem(name, value, checker);
    _this->config_present = true;
}

void RovizItemDevBase::addConfig(std::string name, int *value, std::function<int (int)> checker)
{
    _this->conf_diag->addItem(name, value, checker);
    _this->config_present = true;
}

void RovizItemDevBase::addConfig(std::string name, double *value, std::function<double (double)> checker)
{
    _this->conf_diag->addItem(name, value, checker);
    _this->config_present = true;
}

void RovizItemDevBase::addConfig(std::string name, bool *value)
{
    _this->conf_diag->addItem(name, value);
    _this->config_present = true;
}

void RovizItemDevBase::addConfig(std::string name, std::vector<std::string> possibilities, int *index)
{
    _this->conf_diag->addItem(name, possibilities, index);
    _this->config_present = true;
}

void RovizItemDevBase::start()
{
    // TODO The itemframework should have an 'initialization complete' signal
    if(!_this->conf_loaded)
    {
        _this->conf_diag->load(this->settingsScope());
        _this->conf_loaded = true;
    }
}

INSTANTIATE_PORTABLE_BASE
