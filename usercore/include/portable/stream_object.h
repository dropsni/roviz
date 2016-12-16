#ifndef STREAM_OBJECT_H
#define STREAM_OBJECT_H

//#include "portable/stream_object_base.h"

//template<class T>
class StreamObject //: public StreamObjectBase
{
public:
    StreamObject();
};


/*
 * Rough idea:
 *
 * Every object that you can output (image, message, shapecollection) has
 * StreamObject as its base class. All functions will then either be
 * templated and use a cast to get the right class from StreamObject, or
 * it only uses StreamObject itself. The needs to be some copy implementation
 * for StreamObject, because just copying it might not copy the derived
 * object correctly if you don't know its type. Pure-virtual clone()
 * method? Called in copy-constructor?
 *
 * ShapeCollection:
 *
 * Collection of Shape objects, implemented similar to StreamObject, base
 * class of shapes (points, circles, ...), access functions of
 * ShapeCollection have to be templated to provide proper access to the
 * right items. A shape probably needs to provide a unique type-id
 * (pure-virtual id()?) that can be checked before a cast. SEE typeinfo
 * KEYWORD!!!
 *
 */

#endif // STREAM_OBJECT_H
