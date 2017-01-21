#ifndef TPG_H
#define TPG_H

// This is a simulation only item
#ifndef PORTABLE_EXPORT

#include <QImage>
#include <QTimer>
#include <atomic>
#include "portable/portable_item.h"
#include "portable/portable_image_m.h"

/**
 * @brief Test pattern generator for testing
 *
 * \ingroup robot_plugins
 */
class TPGItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE TPGItem();
    ~TPGItem();

private:
    void starting(void) override;
    void thread(void) override;
    void trimChanged(Trim trim, double value) override;

    QImage test_pattern;
    ImageMutable out_img;
    QTimer timer;
    int timeout;
    Output output;
    Trim trim;
    bool timer_expired;

private slots:
    void timerExpired(void);

};

#endif
#endif // TPG_H
