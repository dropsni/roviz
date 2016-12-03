#ifndef STREAMTOINPUTMAPPER_H
#define STREAMTOINPUTMAPPER_H

#include <QObject>
#include "item/item_input.h"
#include "portable/portable_image.h"
#include "portable/portable_item_global.h"
#include "core/message.h"
#include "core/pointcloud.h"

/**
 * @brief Maps the signal that a new message is ready to the right input
 *
 * \ingroup robot_framework
 */
class StreamToInputMapper : public QObject
{
    Q_OBJECT

public:
    ItemInput *input;
    QMetaObject::Connection conn1, conn2;

    explicit StreamToInputMapper(QObject *parent = nullptr);
    ~StreamToInputMapper();

public slots:
    void imgInputMapper(PortableImage image);
    void msgInputMapper(Message message);
    void pcInputMapper(Pointcloud pointcloud);

signals:
    void newImage(void *input, PortableImage image);
    void newMessage(void *input, Message message);
    void newPointcloud(void *input, Pointcloud pointcloud);
};

#endif // STREAMTOINPUTMAPPER_H
