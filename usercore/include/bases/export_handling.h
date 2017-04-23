#ifndef EXPORT_HANDLING_H
#define EXPORT_HANDLING_H

/** \mainpage roviz
 *
 * This is a combined documentation of the roviz framework and the itemframework.
 * If you would like to start writing a plugin for the roviz framework, have
 * a look at the overeview of the Roviz Framework under 'Modules'. You can
 * also find out more about the itemframework under 'Related Pages'. You can
 * find a short description of the project and its source code under
 * https://github.com/rdit-ch/roviz
 *
 */

//#define ROVIZ_EXPORT

#ifdef ROVIZ_EXPORT
    #define ROVIZ_BASE_INCLUDE     "core/roviz_item_prod_base.h"
    #define ROVIZ_BASE_INCLUDE_P   "core/roviz_item_prod_base_p.h"
    #define ROVIZ_EXPORT_CLASS
    #define ROVIZ_INVOKABLE
    // Qt doesn't allow renaming O_OBJECT, because the moc isn't that smart
    #define Q_OBJECT
    #define ROVIZ_INIT_ITEM(name)
    #define OPENCV_PRESENT
#else
    #define ROVIZ_BASE_INCLUDE        "bases/roviz_item_dev_base.h"
    #define ROVIZ_BASE_INCLUDE_P      "bases/roviz_item_dev_base_p.h"
    #define ROVIZ_CONFIG_IMPL_INCLUDE "config/config_impl_dev.h"
    #define ROVIZ_EXPORT_CLASS        Q_DECL_EXPORT
    #define ROVIZ_INVOKABLE           Q_INVOKABLE
    #define ROVIZ_INIT_ITEM(name)     {this->setImage(QImage(":/logo_"#name".png"));}
    #define QT_PRESENT
    #define OPENCV_PRESENT

    // Needed by some modules and I don't want to wrap an #ifdef around all
    // of them.
    #include <QObject>

    // Select the appropriate base class for the items here
    class RovizItemDevBase;
    typedef RovizItemDevBase RovizItemBase;

    // Select the appropriate implementation of the configs
    class ConfigImplDevBase;
    typedef ConfigImplDevBase ConfigImplBase;

    // Select the appropriate base class for the trim here
    class TrimDevBase;
    typedef TrimDevBase TrimBase;

    // Even though we use a #define below, this is still needed. Somehow.
    template<typename>
    class ConfigImplDev;

    // C++ won't allow us to use a typedef or using here because that would
    // impose restrictions, like not being allowed to instantiate the template
    // using the alias. So we have to do it the ugly way.
    #define ConfigImpl ConfigImplDev

#endif

#endif // EXPORT_HANDLING_H
