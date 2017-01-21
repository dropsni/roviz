
#include "core/stream_to_input_mapper.h"

StreamToInputMapper::StreamToInputMapper(QObject *parent)
    : QObject(parent)
{
}

void StreamToInputMapper::inputMapper(StreamObject obj)
{
    emit this->newObject(obj, Input(this->input));
}
