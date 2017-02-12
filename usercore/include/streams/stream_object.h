#ifndef STREAM_OBJECT_H
#define STREAM_OBJECT_H

#include <memory>
#include <vector>
#include "core/template_decl.h"
#include "bases/export_handling.h"

struct SrcTreeNode;
class StreamObjectPrivate;

/**
 * @brief The ID and source tree of an image
 */
typedef std::shared_ptr<SrcTreeNode> SourceID;

/**
 * @brief A node of the source-tree
 */
struct SrcTreeNode
{
    std::vector<SourceID> sources;
};

class ROVIZ_EXPORT_CLASS StreamObject
{
    MAKE_ALL_STREAMS_A_FRIEND

public:
    StreamObject() = default;
    virtual ~StreamObject() = default;
    SourceID id(void) const;

protected:
    std::shared_ptr<StreamObjectPrivate> _this_base;

    // Cannot be done in the constructer, because the derived class has to
    // initialize the private data first.
    void initSources(std::initializer_list<SourceID> sources = {});

    // C++ doesn't allow this, just make sure the object implements such a function.
    // virtual static StreamWidgetBase *constructWidget(void);
};
Q_DECLARE_METATYPE(StreamObject)

#endif // STREAM_OBJECT_H
