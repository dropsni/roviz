#ifndef TVG_ITEM_H
#define TVG_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <ctime>

class TVGItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE TVGItem();
    ~TVGItem();

protected:
    void thread(void) override;

private:
    ImageOutput output;
    std::string vid_path;
};

#endif // TVG_ITEM_H
