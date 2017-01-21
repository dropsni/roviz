
#include "portable/message.h"
#include "portable/message_p.h"

Message::Message(const StreamObject &base)
{
    _this_base = base._this_base;
}

Message::Message(std::initializer_list<SourceID> sources)
    : StreamObject(sources),
      _this(new MessagePrivate())
{
    _this_base.reset(_this);
}

const Message::Entry &Message::entry(unsigned int index) const
{
    if(index > _this->entries.size())
        return _this->default_entry;

    return _this->entries[index];
}

const Message::Entry &Message::at(int index) const
{
    return this->entry(index);
}

const Message::Entry &Message::operator[](int index) const
{
    return _this->entries[index];
}