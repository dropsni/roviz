#ifndef GRAYCONV_ITEM_H
#define GRAYCONV_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_m.h"

/**
 * @brief Converts an RGB image to grayscale
 *
 * \ingroup robot_plugins
 */
class GrayConvItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE GrayConvItem();
    ~GrayConvItem();

protected:
    void starting(void) override;
    void thread(void) override;

private:
    Output output;
    Input input;

    static Image fromRGB(Image in, int depth);
    static Image fromRGB555(Image in);
    static Image fromRGB888(Image in);
    static Image fromYUV422(Image in);
    static Image fromYUV422_Flipped(Image in);
};

#endif // GRAYCONV_ITEM_H
