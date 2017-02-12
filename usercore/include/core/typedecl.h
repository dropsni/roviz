#ifndef TYPEDECL_H
#define TYPEDECL_H

#include "core/strong_typedef.h"

class ItemInput;
class ItemOutput;
class QSlider;

struct InputTag{};
struct OutputTag{};
struct TrimTag{};

typedef StrongTypedef<InputTag, ItemInput*, nullptr> Input;
typedef StrongTypedef<OutputTag, ItemOutput*, nullptr> Output;
typedef StrongTypedef<TrimTag, QSlider*, nullptr> Trim;

#ifndef ROVIZ_EXPORT
class RovizItem;

/**
 * @brief Use RovizItemNoExport for simulation-only items
 *
 * This type will be undefined when exporting, making it easier to detect
 * the error when trying to export a simulation-only item.
 *
 * \ingroup roviz_framework
 */
typedef RovizItem RovizItemNoExport;
#endif

#endif // TYPEDECL_H
