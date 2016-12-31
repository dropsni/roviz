
#include "portable/portable_image_p.h"

void PortableImagePrivate::init(int w, int h, PortableImage::Format f)
{
    this->w = w;
    this->h = h;
    this->f = f;

    switch(f)
    {
        case PortableImage::RGB555:

            this->bits = 16;
            this->bytes = 2;
            break;

        case PortableImage::RGB888:

            this->bits = 24;
            this->bytes = 3;
            break;

        case PortableImage::Gray8:

            this->bits = 8;
            this->bytes = 1;
            break;

        case PortableImage::YUV422:
        case PortableImage::YUV422_Flipped:

            this->bits = 16;
            this->bytes = 2;
            break;

        default:
            break;
    }

    this->len = w * h * this->bytes;
}
