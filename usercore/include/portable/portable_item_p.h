#ifndef PORTABLEITEMPRIVATE_H
#define PORTABLEITEMPRIVATE_H

#include "portable/portable_item.h"
#include "portable/input_queue.h"
#include "portable/message.h"

class PortableItemPrivate
{
public:
    PortableItem *_this;
    std::map<Input, InputQueue*> in_queue;
    std::condition_variable cond;
    std::thread *th;
    std::mutex mtx;
    bool is_paused, is_stopped;

    PortableItemPrivate(PortableItem *q);
    ~PortableItemPrivate();
};

#endif // PORTABLEITEMPRIVATE_H
