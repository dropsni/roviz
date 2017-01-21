
#include "core/stream_base.h"

StreamBase::StreamBase()
{
    this->default_widget = nullptr;
}

QWidget *StreamBase::widget()
{
    // We only construct it if the base class implementation is really
    // called, we don't want it constructed, if the derived class has
    // its own implementation.
    if(this->default_widget == nullptr)
        this->default_widget = new QWidget();

    return this->default_widget;
}
