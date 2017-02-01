#ifndef STREAM_H
#define STREAM_H

#include "core/stream_base.h"
#include "portable/template_decl.h"

template<class T>
class Stream : public StreamBase
{
public:
    Stream();
    ~Stream() = default;
};

#endif // STREAM_H
