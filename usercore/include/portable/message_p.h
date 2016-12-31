#ifndef MESSAGEPRIVATE_H
#define MESSAGEPRIVATE_H

#include "message.h"
#include "portable/stream_object_p.h"

class MessagePrivate : public StreamObjectPrivate
{
public:
    std::vector<Message::Entry> entries;
    Message::Entry default_entry;
};

#endif // MESSAGEPRIVATE_H
