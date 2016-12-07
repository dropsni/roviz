
#include "core/stream_to_input_mapper.h"

StreamToInputMapper::StreamToInputMapper(QObject *parent)
    : QObject(parent)
{
}

StreamToInputMapper::~StreamToInputMapper()
{
}

void StreamToInputMapper::imgInputMapper(PortableImage image)
{
    emit this->newImage(ImageInput(this->input), image);
}

void StreamToInputMapper::msgInputMapper(Message message)
{
    emit this->newMessage(MessageInput(this->input), message);
}

void StreamToInputMapper::pcInputMapper(Pointcloud pointcloud)
{
    emit this->newPointcloud(PointcloudInput(this->input), pointcloud);
}
