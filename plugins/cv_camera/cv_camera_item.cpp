
#include "cv_camera_item.h"

CvCameraItem::CvCameraItem()
    : RovizItem("CvCamera"),
      conf_res(this,
               "Resolution",
               2,
               {
                   "1920x1080",
                   "1280x720",
                   "640x480"
               },
               true),
      conf_cam_id(this,
                  "Camera",
                  0,
                  0, 1000) // Should be enough
                  // TODO Make that safer
{
    ROVIZ_INIT_ITEM(CvCamera);

    this->width_list =
    {
        1920,
        1280,
        640
    };

    this->height_list =
    {
        1080,
        720,
        480
    };

    this->output = this->addOutput<Image>("Camera Output");
    this->addConfig(this->conf_cam_id);
    this->addConfig(this->conf_res);
}

CvCameraItem::~CvCameraItem()
{
    this->stop();
}

void CvCameraItem::thread()
{
    cv::Mat frame;

    this->cap.open(this->conf_cam_id.value());
    if(!this->cap.isOpened())
        return;

    // TODO Use resolution

    while(this->wait())
    {
        this->cap >> frame;
        emit this->pushOut(Image(frame), this->output);
    }
}

void CvCameraItem::stopped()
{
    this->cap.release();
}
