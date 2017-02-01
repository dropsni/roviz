#ifndef TEMPLATEDECL_H
#define TEMPLATEDECL_H

#include "portable/export_handling.h"
#include "portable/template_decl_helpers.h"

// Including the header here leads to a circular inclusion
class Image;
class Message;

#ifndef PORTABLE_EXPORT
// The MOC is not smart enough to handle it if its encapsulated
// within the macro. If you want to add a stream, copy one of the
// classes below and name it StreamInit*YOUR_TYPE*. The class is only
// used for type-matching and coloring.

// PortableImage stream
class Q_DECL_EXPORT StreamInitImage : public QObject \
{ Q_OBJECT public: static void init(void); };

// Message stream
class Q_DECL_EXPORT StreamInitMessage : public QObject \
{ Q_OBJECT public: static void init(void); };

#endif

// Make sure all templates for the streams get instantiated
#define DO_FOR_ALL_STREAMS(EXPR) \
    EXPR(Image) \
    EXPR(Message)


#endif // TEMPLATEDECL_H
