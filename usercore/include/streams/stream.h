#ifndef STREAM_H
#define STREAM_H

#include "core/export_handling.h"
#include ROVIZ_STREAM_BASE_INCLUDE

/**
 * @brief A stream that transports SteramObjects from one item to another
 *
 * \ingroup roviz_core
 * \ingroup roviz_stream_dev
 */
template<class T>
class Stream : public StreamBase
{
public:
    Stream();
    ~Stream() = default;
};

#endif // STREAM_H
