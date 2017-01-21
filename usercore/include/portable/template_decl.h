#ifndef TEMPLATEDECL_H
#define TEMPLATEDECL_H

#include "portable/portable_item_global.h"

// Including the header here might lead to a circular inclusion
class Image;
class Message;

#ifndef PORTABLE_EXPORT
// The MOC is not smart enough to handle it if its encapsulated
// within the macro. If you want to add a stream, copy one of the
// classes below and name it StreamInit*YOUR_TYPE*. The class is only
// used for type-matching and coloring.

// PortableImage stream
class Q_DECL_EXPORT StreamInitImage : public QObject \
{ Q_OBJECT public: static void init(void); };

// Message stream
class Q_DECL_EXPORT StreamInitMessage : public QObject \
{ Q_OBJECT public: static void init(void); };

#endif

// Make sure all templates for the streams get instantiated
#define DO_FOR_ALL_STREAMS(EXPR) \
    EXPR(Image) \
    EXPR(Message)

// If you just want to add a new stream, the things below don't matter
// for you.

#define INSTANTIATE_PORTABLE_ITEM_P(T) \
    template Input PortableItem::addInput<T>(std::string name); \
    template Output PortableItem::addOutput<T>(std::string name); \
    template T PortableItem::next<T>(Input in); \
    template T PortableItem::newest<T>(Input in);

// The '##' is needed to prevent expansion
#define INSTANTIATE_PORTABLE_ITEM \
    DO_FOR_ALL_STREAMS(INSTANTIATE_PORTABLE_ITEM##_P)

#define INSTANTIATE_PORTABLE_BASE_P(T) \
    template Input PortableItemBase::addInputBase<T>(std::string name); \
    template Output PortableItemBase::addOutputBase<T>(std::string name);

#define INSTANTIATE_PORTABLE_BASE \
    DO_FOR_ALL_STREAMS(INSTANTIATE_PORTABLE_BASE##_P)

#define INSTANTIATE_STREAM_P(T) \
    template class Stream<T>;

#define INSTANTIATE_STREAM \
    DO_FOR_ALL_STREAMS(INSTANTIATE_STREAM##_P)

#define MAKE_ALL_STREAMS_A_FRIEND_P(T) \
    friend class T;

#define MAKE_ALL_STREAMS_A_FRIEND \
    DO_FOR_ALL_STREAMS(MAKE_ALL_STREAMS_A_FRIEND##_P)

#endif // TEMPLATEDECL_H
