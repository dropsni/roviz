#ifndef TIG_ITEM_H
#define TIG_ITEM_H

#include "core/roviz_item.h"
#include "config/config.h"
#include "streams//image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <thread>

class TIGItem : public RovizItem
{
    Q_OBJECT

public:
    ROVIZ_INVOKABLE TIGItem();
    ~TIGItem();

protected:
    void thread(void) override;

private:
    Output output;
    Image img;
    Config<FilePath> conf_path;
    Config<bool> conf_load_grey;
};

#endif // TIG_ITEM_H
