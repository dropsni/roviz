#ifndef TEMPLATEDECL_H
#define TEMPLATEDECL_H

#include "portable/portable_item_global.h"
#include PORTABLE_BASE_INCLUDE
#include "portable/portable_image.h"
#include "portable/portable_item.h"
#include "core/stream.h"

extern template Input PortableItemBase::addInput<PortableImage>(std::string name);
extern template Output PortableItemBase::addOutput<PortableImage>(std::string name);
extern template Input PortableItem::addInput<PortableImage>(std::string name);
extern template Output PortableItem::addOutput<PortableImage>(std::string name);
extern template PortableImage PortableItem::next<PortableImage>(Input in);
extern template PortableImage PortableItem::newest<PortableImage>(Input in);
extern template class Stream<PortableImage>;
extern template static void Stream<PortableImage>::init(void);

#endif // TEMPLATEDECL_H
