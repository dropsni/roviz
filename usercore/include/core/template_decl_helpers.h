#ifndef TEMPLATE_DECL_HELPERS_H
#define TEMPLATE_DECL_HELPERS_H

#define STREAM_COLOR_GREEN  Qt::green
#define STREAM_COLOR_RED    Qt::red
#define STREAM_COLOR_YELLOW Qt::yellow

#define INIT_STREAM_CPP(T, color) \
    STARTUP_ADD_COMPONENT(StreamInit##T) \
    void StreamInit##T::init() \
    { \
        AbstractItem::registerConnectorStyle(color, qMetaTypeId<Stream<T>*>()); \
    }

#define INSTANTIATE_PORTABLE_ITEM_P(T) \
    template Input RovizItem::addInput<T>(std::string name); \
    template Output RovizItem::addOutput<T>(std::string name); \
    template T RovizItem::next<T>(Input in); \
    template T RovizItem::newest<T>(Input in);

// The '##' is needed to prevent expansion
#define INSTANTIATE_PORTABLE_ITEM \
    DO_FOR_ALL_STREAMS(INSTANTIATE_PORTABLE_ITEM##_P)

#define INSTANTIATE_PORTABLE_BASE_P(T) \
    template Input RovizItemBase::addInputBase<T>(std::string name); \
    template Output RovizItemBase::addOutputBase<T>(std::string name);

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

#endif // TEMPLATE_DECL_HELPERS_H
