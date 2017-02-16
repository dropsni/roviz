#ifndef FRAMEDELAYER_ITEM_H
#define FRAMEDELAYER_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include <queue>
#include <thread>

/**
 * @brief Delays incoming frames for some time before outputting them again
 *
 * \ingroup robot_plugins
 */
class FrameDelayerItem : public RovizItem
{
    Q_OBJECT

public:
    ROVIZ_INVOKABLE FrameDelayerItem();
    ~FrameDelayerItem();

protected:
    void starting(void) override;
    void thread(void) override;
    void trimChanged(void *trim, int value);

private:
    Input input;
    Output output;
    Trim delay_trim;
    std::queue<Image> queue;
    unsigned int delay;
    std::mutex mtx;
};

#endif // FRAMEDELAYER_ITEM_H
