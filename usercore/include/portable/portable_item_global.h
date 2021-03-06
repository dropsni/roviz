#ifndef PORTABLE_ITEM_GLOBAL_H
#define PORTABLE_ITEM_GLOBAL_H

//#define PORTABLE_EXPORT

#ifdef PORTABLE_EXPORT
    #define PORTABLE_BASE_INCLUDE  "portable_item_embedded.h"
    #define PORTABLE_EXPORT_CLASS
    #define PORTABLE_INVOKABLE
    // Qt doesn't allow renaming O_OBJECT, because the moc isn't that smart
    #define Q_OBJECT
    #define PORTABLE_INIT(name)
    #define OPENCV_PRESENT
#else
    #include <QtCore/qglobal.h>
    #include <QObject>
    #include <QSlider>
    #include "portable/strong_typedef.h"
    #include "item/item_input.h"
    #include "item/item_output.h"
    #define PORTABLE_BASE_INCLUDE      "core/abstract_robot_item.h"
    #define PORTABLE_BASE_INCLUDE_P    "core/abstract_robot_item_p.h"
    #define PORTABLE_EXPORT_CLASS      Q_DECL_EXPORT
    #define PORTABLE_INVOKABLE         Q_INVOKABLE
    #define PORTABLE_INIT(name)        {this->setImage(QImage(":/logo_"#name".png"));}
    #define QT_PRESENT
    #define OPENCV_PRESENT

    struct ImageInputTag{};
    struct MessageInputTag{};
    struct PointcloudInputTag{};
    struct ImageOutputTag{};
    struct MessageOutputTag{};
    struct PointcloudOutputTag{};
    struct TrimTag{};

    typedef StrongTypedef<ImageInputTag, ItemInput*, nullptr> ImageInput;
    typedef StrongTypedef<MessageInputTag, ItemInput*, nullptr> MessageInput;
    typedef StrongTypedef<PointcloudInputTag, ItemInput*, nullptr> PointcloudInput;
    typedef StrongTypedef<ImageOutputTag, ItemOutput*, nullptr> ImageOutput;
    typedef StrongTypedef<MessageOutputTag, ItemOutput*, nullptr> MessageOutput;
    typedef StrongTypedef<PointcloudOutputTag, ItemOutput*, nullptr> PointcloudOutput;
    typedef StrongTypedef<TrimTag, QSlider*, nullptr> Trim;

    class PortableItem;

    /**
     * @brief Use NonPortableItem for simulation-only items
     *
     * This type will be undefined when exporting, making it easier to detect
     * the error when trying to export a simulation-only item.
     *
     * \ingroup robot_framework
     */
    typedef PortableItem NonPortableItem;
#endif

#endif // PORTABLE_ITEM_GLOBAL_H
