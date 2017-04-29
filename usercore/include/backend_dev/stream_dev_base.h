#ifndef STREAM_DEV_BASE_H
#define STREAM_DEV_BASE_H

#include <QObject>
#include <QWidget>
#include "streams/stream_object.h"

class StreamDevBase : public QObject
{
Q_OBJECT

public:
    StreamDevBase() = default;
    virtual ~StreamDevBase() = default;
    QWidget *widget(void);

protected:
    QWidget *widget_ptr;

signals:
    void newObject(StreamObject obj);
};

#endif // STREAM_DEV_BASE_H
