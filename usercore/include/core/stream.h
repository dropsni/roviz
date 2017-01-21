#ifndef STREAM_H
#define STREAM_H

#include "core/stream_base.h"
#include "portable/template_decl.h"

// This class is only needed to get a typeid
template<class T>
class Stream : public StreamBase
{
public:
    Stream() = default;
    ~Stream() = default;
};

#endif // STREAM_H
