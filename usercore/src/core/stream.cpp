
#include "core/stream.h"

INSTANTIATE_STREAM

template<class T>
Stream::Stream()
{
    this->widget_ptr = T::constructWidget();
    connect(this, &Stream<T>::newObject,
            this->widget_ptr, &StreamWidgetBase::newObject);
}
