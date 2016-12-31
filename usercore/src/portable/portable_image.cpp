
#include "portable/portable_image.h"
#include "portable/portable_image_p.h"

PortableImage::PortableImage(std::initializer_list<SourceID> sources)
    : StreamObject(sources),
      _this(new PortableImagePrivate())
{
    _this_base.reset(_this);

    _this->is_self_managed = true;
    _this->data_ptr = nullptr;

    _this->init(0, 0, PortableImage::NoFormat);
}

PortableImage::PortableImage(bool, std::initializer_list<SourceID> sources)
    : StreamObject(sources),
      _this(new PortableImagePrivate())
{
}

#ifdef QT_PRESENT
PortableImage::PortableImage(QImage img, std::initializer_list<SourceID> sources)
    : StreamObject(sources),
      _this(new PortableImagePrivate())
{
    _this_base.reset(_this);

    enum PortableImage::Format f;
    int cf = -1;

    switch(img.format())
    {
        case QImage::Format_RGB555: f = PortableImage::RGB555; break;
        case QImage::Format_RGB888: f = PortableImage::RGB888; break;
        case QImage::Format_Grayscale8: f = PortableImage::Gray8; cf = CV_8UC1; break;
        default: f = PortableImage::NoFormat; break;
    }

    _this->is_self_managed = false;
    _this->qt_img = img;

    // Now things are getting ugly, but Qt fights hard to force us to make a copy
    _this->data_ptr = const_cast<unsigned char*>(_this->qt_img.constBits());

#ifdef OPENCV_PRESENT
    _this->cv_img = cv::Mat(img.height(), img.width(), cf, _this->data_ptr);
#endif

    _this->init(img.width(), img.height(), f);
}
#endif

#ifdef OPENCV_PRESENT
PortableImage::PortableImage(cv::Mat img, std::initializer_list<SourceID> sources)
    : StreamObject(sources),
      _this(new PortableImagePrivate())
{
    _this_base.reset(_this);

    enum PortableImage::Format f;
    QImage::Format qf = QImage::Format_Invalid;

    // Be very careful when using OpenCV images in color mode! They use BGR, not RGB!
    switch(img.channels())
    {
        case 1: f = PortableImage::Gray8; qf = QImage::Format_Grayscale8; break;
        case 3: f = PortableImage::BGR_CV; break;
        default: f = PortableImage::NoFormat; break;
    }

    _this->is_self_managed = false;
    _this->cv_img = img;
    _this->data_ptr = _this->cv_img.data;

#ifdef QT_PRESENT
    _this->qt_img = QImage(img.data, img.cols, img.rows, qf);
#endif

    _this->init(img.cols, img.rows, f);
}
#endif

PortableImage::~PortableImage()
{
}

int PortableImage::width() const
{
    return _this->w;
}

int PortableImage::height() const
{
    return _this->h;
}

PortableImage::Format PortableImage::format() const
{
    return _this->f;
}

int PortableImage::bitsPerPixel() const
{
    return _this->bits;
}

int PortableImage::bytesPerPixel() const
{
    return _this->bytes;
}

int PortableImage::dataLength() const
{
    return _this->len;
}

const unsigned char *PortableImage::data() const
{
    return _this->data_ptr;
}

const QImage PortableImage::toQt()
{
    return _this->qt_img;
}

const cv::_InputArray PortableImage::toCv()
{
    return cv::_InputArray(_this->cv_img);
}
