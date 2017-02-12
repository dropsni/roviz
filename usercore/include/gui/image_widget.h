#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QRectF>
#include <QImage>
#include <QLabel>
#include "bases/export_handling.h"
#include "streams/image.h"
#include "streams/stream_object.h"

class QWidget;
class QPaintEvent;
class QResizeEvent;

// TODO Use native OpenGL, implement BGR display for OpenCV, just switching to
// QOpenGLWidget doesn't seem to work, don't know why.
/**
 * @brief A widget to show images
 *
 * This widget automatically scales the image it is supposed to display to the
 * correct size.
 *
 * \ingroup roviz_framework
 */
class ROVIZ_EXPORT_CLASS ImageWidget : public QLabel
{
Q_OBJECT

public:
    ImageWidget(QWidget *parent = nullptr);

    /**
     * @brief Reset the widget to make it show the default image again
     */
    void reset(void);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void newObject(StreamObject obj);

private:
    QImage image_qt;
    Image image; // To keep a reference, prevents deletion
    QRectF image_rect;

    void recalcImageRect(double w, double h);
};

#endif // IMAGEWIDGET_H
