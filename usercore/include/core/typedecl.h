#ifndef TYPEDECL_H
#define TYPEDECL_H

#include <string>
#include "core/strong_typedef.h"

class ItemInput;
class ItemOutput;
class QSlider;

struct InputTag{};
struct OutputTag{};
struct TrimTag{};
struct FilePathTag{};

// C++ doesn't allow us to do this without a pointer
typedef StrongTypedef<FilePathTag, std::string*, nullptr> FilePath;

#ifdef ROVIZ_EXPORT
// Insert the typdefs for the exported case here
#else
typedef StrongTypedef<InputTag, ItemInput*, nullptr> Input;
typedef StrongTypedef<OutputTag, ItemOutput*, nullptr> Output;
typedef StrongTypedef<TrimTag, QSlider*, nullptr> Trim;

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
