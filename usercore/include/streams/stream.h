#ifndef STREAM_H
#define STREAM_H

#include "streams/stream_base.h"

template<class T>
class Stream : public StreamBase
{
public:
    Stream();
    ~Stream() = default;
};

#endif // STREAM_H
