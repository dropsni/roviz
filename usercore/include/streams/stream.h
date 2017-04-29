#ifndef STREAM_H
#define STREAM_H

#include "core/export_handling.h"
#include ROVIZ_STREAM_BASE_INCLUDE

template<class T>
class Stream : public StreamBase
{
public:
    Stream();
    ~Stream() = default;
};

#endif // STREAM_H
