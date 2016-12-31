#ifndef PORTABLEIMAGEPRIVATE_H
#define PORTABLEIMAGEPRIVATE_H

#include <vector>
#include <memory>
#include <initializer_list>
#include "portable/portable_image.h"
#include "portable/stream_object_p.h"

class PortableImagePrivate : public StreamObjectPrivate
{
public:
#ifdef QT_PRESENT
    QImage qt_img;
#endif
#ifdef OPENCV_PRESENT
    cv::Mat cv_img;
#endif
    unsigned char *data_ptr;
    bool is_self_managed;
    int w, h, bits, bytes, len;
    enum PortableImage::Format f;

    ~PortableImagePrivate();
    void init(int w, int h, enum PortableImage::Format f);
};

#endif // PORTABLEIMAGEPRIVATE_H
