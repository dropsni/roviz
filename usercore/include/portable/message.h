#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <initializer_list>
#include <memory>
#include "portable/stream_object.h"
#include "core/stream_base.h"

class MessagePrivate;

class Message : public StreamObject
{
public:
    struct Entry
    {
        std::string name;

        enum Type
        {
            Invalid,
            String,
            Int,
            Double
        } type;

        std::string s;
        int i;
        double d;
    };

    Message(const StreamObject &base);
    Message(std::initializer_list<SourceID> sources = {});
    virtual ~Message() = default;

    const Entry &entry(unsigned int index) const;
    const Entry &at(int index) const;
    const Entry &operator[](int index) const;

protected:
    MessagePrivate *_this;

// Handle the displaying of the message
#ifndef PORTABLE_EXPORT
public:
    static QWidget *initWidget(StreamBase *stream);
#endif
};

#endif // MESSAGE_H
