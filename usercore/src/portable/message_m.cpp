
#include "portable/message_m.h"
#include "portable/message_p.h"

MessageMutable::MessageMutable(std::initializer_list<SourceID> sources)
    : Message(sources)
{
}

MessageMutable::~MessageMutable()
{
}

Message::Entry &MessageMutable::entry(unsigned int index)
{
    if(index > _this->entries.size())
        return _this->default_entry;

    return _this->entries[index];
}

Message::Entry &MessageMutable::at(int index)
{
    return this->entry(index);
}

Message::Entry &MessageMutable::operator[](int index)
{
    return _this->entries[index];
}
