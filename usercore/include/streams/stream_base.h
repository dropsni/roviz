#ifndef STREAM_BASE_H
#define STREAM_BASE_H

#include <QObject>
#include <QWidget>
#include "portable/stream_object.h"

class StreamBase : public QObject
{
Q_OBJECT

public:
    StreamBase() = default;
    virtual ~StreamBase() = default;
    QWidget *widget(void);

protected:
    QWidget *widget_ptr;

signals:
    void newObject(StreamObject obj);
};

#endif // STREAM_BASE_H
