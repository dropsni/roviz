
#include "canny_item.h"

CannyItem::CannyItem()
    : PortableItem("Canny")
{
    PORTABLE_INIT(Canny);

    this->input = this->addInput<Image>("Input");
    this->output = this->addOutput<Image>("Output");
    this->thres = this->addTrim("Threshold 1", 1, 100, 100);
    this->ratio = this->addTrim("Ratio", 1, 10, 100);
}

CannyItem::~CannyItem()
{
    this->stop();
}

void CannyItem::thread()
{
    while(this->waitForInput(this->input))
    {
        cv::Mat out;
        int t1, t2;
        Image in = this->next<Image>(this->input);

        if(in.format() != Image::Gray8)
            continue;

        t1 = this->trimValue(thres);
        t2 = t1 * this->trimValue(ratio);
        cv::Canny(in.toCv(), out, t1, t2);
        this->pushOut(Image(out), this->output);
    }
}
