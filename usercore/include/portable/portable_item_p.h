#ifndef PORTABLEITEMPRIVATE_H
#define PORTABLEITEMPRIVATE_H

#include "portable/portable_item.h"
#include "portable/input_queue.h"
#include "core/pointcloud.h"
#include "core/message.h"

class PortableItemPrivate
{
public:
    PortableItem *_this;
    std::map<ImageInput, InputQueue<PortableImage>* > img_in_queue;
    std::map<MessageInput, InputQueue<Message>* > msg_in_queue;
    std::map<PointcloudInput, InputQueue<Pointcloud>* > pc_in_queue;
    std::condition_variable cond;
    std::thread *th;
    std::mutex mtx;
    bool is_paused, is_stopped;

    PortableItemPrivate(PortableItem *q);
    ~PortableItemPrivate();
};

#endif // PORTABLEITEMPRIVATE_H
