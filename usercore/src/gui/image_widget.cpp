
#include "gui/image_widget.h"

ImageWidget::ImageWidget(QWidget *parent)
    : QLabel(parent)
{
    this->setMinimumSize(1, 1);
    this->setSizePolicy(QSizePolicy::Expanding,
                        QSizePolicy::Expanding);
}

// TODO Implement
void ImageWidget::reset()
{
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawImage(this->image_rect, this->image_qt);
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    if(this->image.format() == Image::NoFormat)
        return;

    this->recalcImageRect(event->size().width(), event->size().height());
}

void ImageWidget::newObject(StreamObject obj)
{
    Image img = this->image;
    this->image = Image(obj);

    // We have to resize, when the aspect ratio changes
    if(this->image.format() != Image::NoFormat &&
       (img.format() != Image::NoFormat ||
        this->image.width() != img.width() ||
        this->image.height() != img.height()))
    {
        this->recalcImageRect(this->width(), this->height());
    }

    this->image_qt = this->image.toQt();
}

void ImageWidget::recalcImageRect(double w, double h)
{
    if(this->image.width() == 0 || this->image.height() == 0)
    {
        this->image_rect.setRect(0, 0, 0, 0);
        return;
    }

    double ar = (double)this->image.width() / this->image.height();

    if(w > ar * h)
        this->image_rect.setRect((w - (ar * h)) / 2, 0, ar * h, h);
    else
        this->image_rect.setRect(0, (h - (w / ar)) / 2, w, w / ar);
}
