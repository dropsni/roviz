#ifndef STREAMTOINPUTMAPPER_H
#define STREAMTOINPUTMAPPER_H

#include <QObject>
#include "bases/export_handling.h"
#include "core/typedecl.h"
#include "streams/stream_object.h"

class ItemInput;

/**
 * @brief Maps the signal that a new message is ready to the right input
 *
 * \ingroup roviz_framework
 */
class StreamToInputMapper : public QObject
{
    Q_OBJECT

public:
    ItemInput *input;
    QMetaObject::Connection conn1, conn2;

    explicit StreamToInputMapper(QObject *parent = nullptr);
    ~StreamToInputMapper() = default;

public slots:
    void inputMapper(StreamObject obj);

signals:
    void newObject(StreamObject obj, Input input);
};

#endif // STREAMTOINPUTMAPPER_H
