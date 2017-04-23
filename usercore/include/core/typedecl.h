#ifndef TYPEDECL_H
#define TYPEDECL_H

#include <string>
#include "core/strong_typedef.h"

class ItemInput;
class ItemOutput;
class QSlider;

struct InputTag{};
struct OutputTag{};

#ifdef ROVIZ_EXPORT
// Insert the typdefs for the exported case here
#else
typedef StrongTypedef<InputTag, ItemInput*, nullptr> Input;
typedef StrongTypedef<OutputTag, ItemOutput*, nullptr> Output;

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
