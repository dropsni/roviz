
#include "frame_delayer_item.h"

FrameDelayerItem::FrameDelayerItem()
    : PortableItem("FrameDelayer")
{
    PORTABLE_INIT(FrameDelayer);

    this->input = this->addInput<Image>("Input");
    this->output = this->addOutput<Image>("Output");
    this->delay_trim = this->addTrim("Delay (Frames)", 1, 10);
    this->delay = 1;
}

FrameDelayerItem::~FrameDelayerItem()
{
    this->stop();
}

void FrameDelayerItem::starting()
{
    std::lock_guard<std::mutex> g(this->mtx);

    this->delay = this->trimValue(this->delay_trim);
}

void FrameDelayerItem::thread()
{
    while(this->waitForInput(this->input))
    {
        std::this_thread::yield();
        std::lock_guard<std::mutex> g(this->mtx);

        this->queue.push(this->newest<Image>(this->input));
        if(this->delay >= this->queue.size())
            continue;

        this->pushOut(this->queue.front(), this->output);
        this->queue.pop();
    }
}

void FrameDelayerItem::trimChanged(void *, int value)
{
    std::lock_guard<std::mutex> g(this->mtx);

    this->delay = value;
    // Clear queue
    std::queue<Image>().swap(this->queue);
}
