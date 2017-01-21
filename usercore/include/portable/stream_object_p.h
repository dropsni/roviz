#ifndef STREAM_OBJECT_P_H
#define STREAM_OBJECT_P_H

#include "stream_object.h"

class StreamObjectPrivate
{
public:
    SourceID id;

    StreamObjectPrivate() = default;
    ~StreamObjectPrivate() = default;
};

#endif // STREAM_OBJECT_P_H
