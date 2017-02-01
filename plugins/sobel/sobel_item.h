#ifndef SOBEL_ITEM_H
#define SOBEL_ITEM_H

#include "portable/roviz_item.h"
#include "portable/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class SobelItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE SobelItem();
    ~SobelItem();

protected:
    void thread(void) override;

private:
    Input input;
    Output output;
    Trim depth, dx, dy;
};

#endif // SOBEL_ITEM_H
