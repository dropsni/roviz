#ifndef STREAM_BASE_H
#define STREAM_BASE_H

#include <QObject>
#include <QWidget>
#include "portable/stream_object.h"

class StreamBase : public QObject
{
Q_OBJECT

public:
    StreamBase();
    virtual ~StreamBase();
    virtual QWidget *widget(void);

private:
    QWidget *default_widget;

signals:
    void newObject(StreamObject obj);
};

#endif // STREAM_BASE_H
