#ifndef TIG_ITEM_H
#define TIG_ITEM_H

#include "portable/roviz_item.h"
#include "portable/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class TIGItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE TIGItem();
    ~TIGItem();

protected:
    void thread(void) override;

private:
    Output output;
    Image img;
    std::string img_path;
    bool is_gray;
};

#endif // TIG_ITEM_H
