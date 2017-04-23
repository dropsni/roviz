
#include "trim_dev_base.h"

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include "helper/settings_scope.h"
#include "gui/slider_label.h"
#include "core/roviz_item.h"

// TODO Implement num_of_steps
TrimDevBase::TrimDevBase(std::string name, double min, double max, int steps, bool num_of_steps)
    : _this(new TrimDevBasePrivate())
{
    QLabel *label_name = new QLabel(QString::fromStdString(name));
    QLabel *label_value = new QLabel();

    if(steps <= 0)
        steps = max - min;

    _this->main_slider = new QSlider();
    _this->main_layout = new QVBoxLayout();
    _this->main_slider->setMinimum(0);
    _this->main_slider->setMaximum(steps);
    _this->main_slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    _this->main_slider->setFixedWidth(50);
    _this->main_layout->addWidget(label_name);
    _this->main_layout->addWidget(_this->main_slider);
    _this->main_layout->addWidget(label_value);
    _this->main_layout->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    double factor = (max - min) / steps;
    TrimDevBasePrivate *t = _this.get();
    QObject::connect(_this->main_slider, &QSlider::valueChanged,
                     [t, factor, min, label_value](int value)
    {
        t->val = min + (factor * static_cast<double>(value));
        label_value->setText(QString::number(t->val));
    });

    // TODO Why?
    //    slider->setObjectName(QString::fromStdString(name));
}

TrimDevBase::TrimDevBase(TrimDevBase &&trim)
    : _this(trim._this.get())
{
    trim._this.release();
}

TrimDevBase &TrimDevBase::operator=(TrimDevBase &&trim)
{
    _this.reset(trim._this.get());
    trim._this.release();
    return *this;
}

QLayout *TrimDevBase::layout() const
{
    return _this->main_layout;
}

QSlider *TrimDevBase::slider() const
{
    return _this->main_slider;
}

double TrimDevBase::value() const
{
    return _this->val;
}
