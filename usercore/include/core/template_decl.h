#ifndef TEMPLATEDECL_H
#define TEMPLATEDECL_H

/**
 * @page create_streams How to create you own streams
 *
 * Streams describe the connection between two items. For example, the main
 * stream of the roviz framework is the image stream. It transports objects of
 * type Image from one item to another. If you would like to transport your
 * own type with a stream, all you have to do is the following:
 *
 * -# Create a class for your transport type
 * -# Make it publically inherit from StreamObject (streams/stream_object.h)
 * -# Add a 'QWidget *initWidget(StreamBase *stream)' function
 *    This function should return a pointer to a QWidget that will be displayed
 *    in the shared window for this stream. If you do not want do display
 *    anything, just return nullptr. Make sure you enclose it withing a
 *    #ifndef ROVIZ_EXPORT ... #endif block, because that part can't be
 *    exported. The 'stream' parameter refers to the stream that the QWidget
 *    will be associated with. You should use it to connect the
 *    StreamBase::newObject() signal to update the widget when a new object
 *    enters the stream.
 * -# Add your class to streams/template_decl.h
 *    Stream<T> is a templated class and will accept your class as a stream
 *    object, but as plugins are dynamically linked, you need to tell the
 *    compiler/linker to also instantiate Stream<YourClass>. This is done by
 *    macros, all you have to do is to add your class to the DO_FOR_ALL_STREAMS
 *    macro in streams/template_decl.h. You also have to create an init class to
 *    initialize the color of your stream. Because the Qt MOC isn't that smart,
 *    that can't be encapsulated within a macro. See the existing streams for
 *    examples, it's quite straight forward.
 * -# Choose a color
 *    Every stream is identified by a connection color. You can set that color
 *    by using the macro INIT_STREAM_CPP(YourClass, YOUR_COLOR) in the
 *    streams/template_decl.cpp file. The color is a Qt color, some are
 *    portably predefined in streams/template_decl_helpers.h, but you can also
 *    use a custom color. See the Qt documentaion for that.
 * -# Include your class in streams/all_streams.h
 *    If a file needs to include all stream object it will include
 *    streams/all_streams.h. Just add a line where you include the header of
 *    your class.
 * -# Now you're ready to go!
 */

#include "bases/export_handling.h"
#include "core/template_decl_helpers.h"

// Including the header here leads to a circular inclusion
class Image;
class Message;

#ifndef PORTABLE_EXPORT
#include <QObject>

// The MOC is not smart enough to handle it if its encapsulated
// within the macro. If you want to add a stream, copy one of the
// classes below and name it StreamInit*YOUR_TYPE*.

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
