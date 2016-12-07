
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
    emit this->newImage(image, ImageInput(this->input));
}

void StreamToInputMapper::msgInputMapper(Message message)
{
    emit this->newMessage(message, MessageInput(this->input));
}

void StreamToInputMapper::pcInputMapper(Pointcloud pointcloud)
{
    emit this->newPointcloud(pointcloud, PointcloudInput(this->input));
}
