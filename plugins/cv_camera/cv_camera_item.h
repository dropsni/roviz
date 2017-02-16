#ifndef CVCAMERA_ITEM_H
#define CVCAMERA_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class CvCameraItem : public RovizItem
{
    Q_OBJECT

public:
    ROVIZ_INVOKABLE CvCameraItem();
    ~CvCameraItem();

protected:
    void thread(void) override;
    void stopped(void) override;

private:
    Output output;
    int cam_id;
    cv::VideoCapture cap;
    std::vector<std::string> res_list;
    std::vector<int> width_list, height_list;
    int res_index;
};

#endif // CVCAMERA_ITEM_H
