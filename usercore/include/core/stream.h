#ifndef STREAM_H
#define STREAM_H

#include "core/stream_base.h"

template<class T>
class Stream : public StreamBase
{
public:
    // Not implemented, has be be implemented for each specialization
    // Don't forget STARTUP_ADD_COMPONENT
    static void init(void);
};

#endif // STREAM_H
