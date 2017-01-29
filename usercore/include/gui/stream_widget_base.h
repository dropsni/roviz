#ifndef STREAM_WIDGET_BASE_H
#define STREAM_WIDGET_BASE_H

#include <QWidget>
#include "portable/stream_object.h"

// Virtual, because the derived class will most certainly
// inherit from a different specialisation of QWidget,
// like for example QLabel
class StreamWidgetBase : virtual public QWidget
{
    Q_OBJECT
public:
    explicit StreamWidgetBase(QWidget *parent = 0);

public slots:
    virtual void newObject(StreamObject obj);
};

#endif // STREAM_WIDGET_BASE_H
