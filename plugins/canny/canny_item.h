#ifndef CANNY_ITEM_H
#define CANNY_ITEM_H

#include "portable/roviz_item.h"
#include "portable/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class CannyItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE CannyItem();
    ~CannyItem();

protected:
    void thread(void) override;

private:
    Input input;
    Output output;
    Trim thres, ratio;
};

#endif // CANNY_ITEM_H
