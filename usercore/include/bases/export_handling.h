#ifndef PORTABLE_ITEM_GLOBAL_H
#define PORTABLE_ITEM_GLOBAL_H

/** \mainpage roviz
 *
 * This is a combined documentation of the roviz framework and the itemframework.
 * If you would like to start writing a plugin for the roviz framework, have
 * a look at the overeview of the Robot Framework under 'Modules'. You can
 * also find out more about the itemframework under 'Related Pages'. You can
 * find a short description of the project and its source code under
 * https://github.com/rdit-ch/roviz
 *
 */

//#define PORTABLE_EXPORT

#ifdef PORTABLE_EXPORT
    #define ROVIZ_BASE_INCLUDE     "core/roviz_item_prod_base.h"
    #define ROVIZ_BASE_INCLUDE_P   "core/roviz_item_prod_base_p.h"
    #define ROVIZ_EXPORT_CLASS
    #define ROVIZ_INVOKABLE
    // Qt doesn't allow renaming O_OBJECT, because the moc isn't that smart
    #define Q_OBJECT
    #define ROVIZ_INIT_ITEM(name)
    #define OPENCV_PRESENT
#else
    #define ROVIZ_BASE_INCLUDE     "core/roviz_item_dev_base.h"
    #define ROVIZ_BASE_INCLUDE_P   "core/roviz_item_dev_base_p.h"
    #define ROVIZ_EXPORT_CLASS     Q_DECL_EXPORT
    #define ROVIZ_INVOKABLE        Q_INVOKABLE
    #define ROVIZ_INIT_ITEM(name)  {this->setImage(QImage(":/logo_"#name".png"));}
    #define QT_PRESENT
    #define OPENCV_PRESENT

    // Select the appropriate base class for the items here
    class RovizItemDevBase;
    typedef RovizItemDevBase RovizItemBase;

    struct ROVIZ_EXPORT_CLASS LinkerHelper
    { static void ensureUserCoreGetsLinked(){} };
#endif

#endif // PORTABLE_ITEM_GLOBAL_H
