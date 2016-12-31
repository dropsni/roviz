
#include "gui/image_widget.h"

ImageWidget::ImageWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setMinimumSize(1, 1);
    this->setSizePolicy(QSizePolicy::Expanding,
                        QSizePolicy::Expanding);
}

void ImageWidget::reset()
{

}

void ImageWidget::initializeGL()
{

}

void ImageWidget::paintGL()
{

}

void ImageWidget::resizeGL(int w, int h)
{

}
