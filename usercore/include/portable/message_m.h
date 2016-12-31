#ifndef MESSAGE_M_H
#define MESSAGE_M_H

#include "portable/message.h"

class MessageMutable : public Message
{
public:
    MessageMutable(std::initializer_list<SourceID> sources = {});
    ~MessageMutable();

    Message::Entry &entry(unsigned int index);
    Message::Entry &at(int index);
    Message::Entry &operator[](int index);
};

#endif // MESSAGE_M_H
