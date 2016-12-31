#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QImage>
#include "core/robot_core.h"
#include "portable/portable_image.h"
#include "core/stream.h"

/**
 * @brief A widget to show images
 *
 * This widget automatically scales the image it is supposed to display to the
 * correct size.
 *
 * \ingroup robot_framework
 */
class ROBOTCORE_EXPORT ImageWidget : public QOpenGLWidget
{
Q_OBJECT

public:
    ImageWidget(QWidget *parent = nullptr);

    /**
     * @brief Reset the widget to make it show the default image again
     */
    void reset(void);

protected:
    void initializeGL(void) override;
    void paintGL(void) override;
    void resizeGL(int w, int h) override;
};

#endif // IMAGEWIDGET_H
