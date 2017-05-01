#ifndef STREAM_OBJECT_H
#define STREAM_OBJECT_H

#include <memory>
#include <vector>
#include "core/template_decl.h"
#include "core/export_handling.h"

struct SrcTreeNode;
class StreamObjectPrivate;

/**
 * @brief The ID and source tree of an image
 *
 * Every time an object is created, you have to say where the origins of
 * that object lie. If you create an object which is constructed from
 * another image, you tell the object that this image is its source. For
 * example, image1 is at the input of a filter item and image2 is at its
 * output. Then the source of image2 would be image1.  That way, you can
 * easily recover a source tree and determine the original image after a
 * long filtering pipeline.
 *
 * \ingroup roviz_core
 * \ingroup roviz_stream_dev
 */
typedef std::shared_ptr<SrcTreeNode> SourceID;

/**
 * @brief A node of the source-tree
 */
struct SrcTreeNode
{
    std::vector<SourceID> sources;
};

/**
 * @brief Base class of all objects that can be transported with a stream
 *
 * \sa Stream
 */
class ROVIZ_EXPORT_CLASS StreamObject
{
    MAKE_ALL_STREAMS_A_FRIEND

public:
    StreamObject() = default;
    virtual ~StreamObject() = default;

    /**
     * @brief Get the SourceID of the object
     * @return The SourceID
     */
    SourceID id(void) const;

protected:
    std::shared_ptr<StreamObjectPrivate> _this_base;

    // Cannot be done in the constructer, because the derived class has to
    // initialize the private data first.
    void initSources(std::initializer_list<SourceID> sources = {});

    // C++ doesn't allow this, just make sure the object implements such a
    // function.
//  virtual QWidget *initWidget(StreamBase *stream);
};

// This is the only place within the portable code that we need that. I'm not
// going to make a portable macro just for that.
#ifndef ROVIZ_EXPORT
    Q_DECLARE_METATYPE(StreamObject)
#endif

#endif // STREAM_OBJECT_H
