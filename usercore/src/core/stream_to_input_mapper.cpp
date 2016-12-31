
#include "core/stream_to_input_mapper.h"

StreamToInputMapper::StreamToInputMapper(QObject *parent)
    : QObject(parent)
{
}

StreamToInputMapper::~StreamToInputMapper()
{
}

void StreamToInputMapper::inputMapper(StreamObject obj)
{
    emit this->newObject(obj, Input(this->input));
}
