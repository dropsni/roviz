#ifndef MESSAGEPRIVATE_H
#define MESSAGEPRIVATE_H

#include "message.h"
#include "streams/stream_object_p.h"

/**
 * @brief Private part of the Message class
 *
 * \ingroup roviz_core
 */
class MessagePrivate : public StreamObjectPrivate
{
public:
    std::vector<Message::Entry> entries;
    Message::Entry default_entry;

    ~MessagePrivate() = default;
};

#endif // MESSAGEPRIVATE_H
