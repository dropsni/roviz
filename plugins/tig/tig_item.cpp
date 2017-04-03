
#include "tig_item.h"

TIGItem::TIGItem()
    : RovizItem("Test Image Generator"),
      conf_load_grey(this,
                     "Load Image as greyscale",
                     true,
                     true),
//      dummy(),
      conf_path(this,
                "Path to the image",
                {""},
                FilePath::ExistingFile,
                "All Files (*)",
                true)
{
    ROVIZ_INIT_ITEM(TIG);

    this->output = this->addOutput<Image>("Output");
    this->addConfig(this->conf_load_grey);
    this->addConfig(this->conf_path);
}

TIGItem::~TIGItem()
{
    this->stop();
}

void TIGItem::thread()
{
    this->img = Image(cv::imread(this->conf_path.value().front(),
                                 this->conf_load_grey.value() ?
                                     CV_LOAD_IMAGE_GRAYSCALE
                                   :
                                     CV_LOAD_IMAGE_COLOR));

    while(this->wait())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->pushOut(this->img, this->output);
    }
}
