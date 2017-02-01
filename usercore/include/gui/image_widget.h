#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QImage>
#include <QPainter>
#include "core/robot_core.h"
#include "portable/portable_image.h"
#include "core/stream.h"

#include <QLabel>

// TODO Use native OpenGL, implement BGR display for OpenCV, just switching to
// QOpenGLWidget doesn't seem to work, don't know why.
/**
 * @brief A widget to show images
 *
 * This widget automatically scales the image it is supposed to display to the
 * correct size.
 *
 * \ingroup robot_framework
 */
class ROBOTCORE_EXPORT ImageWidget : public QLabel
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
