
#include "streams/message.h"
#include "streams/message_p.h"

#include <QWidget>

Message::Message(const StreamObject &base)
{
    _this_base = base._this_base;
}

Message::Message(std::initializer_list<SourceID> sources)
    : _this(new MessagePrivate())
{
    _this_base.reset(_this);
    this->initSources(sources);
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

#ifndef ROVIZ_EXPORT
QWidget *Message::initWidget(StreamBase *)
{
    // TODO Implement
    return new QWidget();
}
#endif
