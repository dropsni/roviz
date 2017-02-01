#ifndef SUBTRACTOR_ITEM_H
#define SUBTRACTOR_ITEM_H

#include "portable/roviz_item.h"
#include "portable/image_m.h"

/**
 * @brief Subtracts two images
 *
 * \ingroup robot_plugins
 */
class SubtractorItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE SubtractorItem();
    ~SubtractorItem();

protected:
    void starting(void) override;
    void thread(void) override;

private:
    Input input1, input2;
    Output output;
};

#endif // SUBTRACTOR_ITEM_H
