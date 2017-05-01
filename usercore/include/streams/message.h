#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <initializer_list>
#include "core/export_handling.h"
#include "streams/stream_object.h"
#include ROVIZ_STREAM_BASE_INCLUDE

class QWidget;
class MessagePrivate;

/**
 * @brief Used to send messages across streams
 *
 * This class provides an interface to send generic messages across streams.
 * This could be useful for control signals or the like. It consists of a list
 * of entries. Each entry has a name and a value. The type of the value can be
 * either int, double or string.
 *
 * \ingroup roviz_interface
 * \ingroup roviz_streams
 * \ingroup roviz_core
 */
class Message : public StreamObject
{
public:
    /**
     * @brief An entry of a message
     *
     * Depending on the type, either i, d or s is valid.
     */
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

        // Can't use it for the string because of its non-trivial constructor/
        // destructor, but let's at least use it here.
        union {
            int i;
            double d;
        };
    };

    Message(const StreamObject &base);
    Message(std::initializer_list<SourceID> sources = {});
    virtual ~Message() = default;

    /**
     * @brief Get an entry of the message
     * @param name The name of the entry
     * @return The first entry with a matching name
     *
     * If name is not found in the message, an invalid entry is returned.
     */
    const Entry &entry(const std::string &name) const;

    /**
     * @brief Get an entry of the message
     * @param index The index of the entry
     * @return The entry
     *
     * This function checks the bounds and returns an invalid entry if the index
     * is out of bounds.
     */
    const Entry &at(int index) const;

    /**
     * @brief Get an entry of the message
     * @param index The index of the entry
     * @return The entry
     *
     * WARNING: This function doesn't check the bounds!
     */
    const Entry &operator[](int index) const;

    /**
     * @brief Get the size of a message
     * @return The amount of entries of this message
     */
    int size(void) const;

protected:
    MessagePrivate *_this;

// Handle the displaying of the message
#ifndef ROVIZ_EXPORT
public:
    static QWidget *initWidget(StreamBase *stream);
#endif
};

#endif // MESSAGE_H
