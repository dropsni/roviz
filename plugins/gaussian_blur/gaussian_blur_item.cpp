
#include "gaussian_blur_item.h"

GaussianBlurItem::GaussianBlurItem()
    : PortableItem("GaussianBlur")
{
    PORTABLE_INIT(GaussianBlur);

    this->input = this->addInput<Image>("Input");
    this->output = this->addOutput<Image>("Output");
    this->trim = this->addTrim("Blur Factor", 0.1, 10, 100);
}

GaussianBlurItem::~GaussianBlurItem()
{
    this->stop();
}

void GaussianBlurItem::thread()
{
    while(this->waitForInput(this->input))
    {
        cv::Mat out;
        Image img = this->next<Image>(this->input);
        cv::GaussianBlur(img.toCv(),
                         out,
                         cv::Size(0, 0),
                         this->trimValue(this->trim));
        this->pushOut(Image(out, {img.id()}), this->output);
    }
}
