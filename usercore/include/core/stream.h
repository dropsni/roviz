#ifndef STREAM_H
#define STREAM_H

#include "core/stream_base.h"
#include "portable/template_decl.h"
#include "gui/stream_widget_base.h"

template<class T>
class Stream : public StreamBase
{
public:
    Stream();
    ~Stream() = default;
};

#endif // STREAM_H
