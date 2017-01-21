#ifndef STREAM_OBJECT_H
#define STREAM_OBJECT_H

#include <memory>
#include <vector>
#include "portable/template_decl.h"

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

class PORTABLE_EXPORT_CLASS StreamObject
{
    MAKE_ALL_STREAMS_A_FRIEND

public:
    virtual ~StreamObject() = default;
    SourceID id(void) const;

protected:
    std::shared_ptr<StreamObjectPrivate> _this_base;

    StreamObject(std::initializer_list<SourceID> sources = {});
};

#endif // STREAM_OBJECT_H
