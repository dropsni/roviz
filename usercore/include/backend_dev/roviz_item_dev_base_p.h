#ifndef ROVIZITEMDEVBASEPRIVATE_H
#define ROVIZITEMDEVBASEPRIVATE_H

#include <QMap>
#include <QList>
#include <QImage>
#include "core/typedecl.h"

class QWidget;
class QPushButton;
class QSlider;
class QHBoxLayout;
class SettingsScope;
class SliderLabel;
class StreamToInputMapper;
class RovizItemDevBase;
class ConfigImplDevBase;

class RovizItemDevBasePrivate : public QObject
{
    Q_OBJECT

public:
    RovizItemDevBase *_this;
    QWidget *main_widget;
    QPushButton *collapse_btn;
    QHBoxLayout *main_layout, *main_image_layout, *main_control_layout;
    QMap<Output, QWidget*> out_widgets;
    QMap<ItemInput*, StreamToInputMapper*> in_mappers;
    QList<ConfigImplDevBase*> config_impls;
    QWidget *control_base;
    QImage default_image;
    QList<QMetaObject::Connection> trim_conns;
    bool config_present, conf_loaded;

    RovizItemDevBasePrivate(RovizItemDevBase *q);

public slots:
    /**
     * @brief The input was connected or disconnected
     */
    void inputStateChanged(void);

    /**
     * @brief (Un)collapses all trim sliders
     */
    void collapseBtnClicked(void);

    /**
     * @brief Restarts the item operation if the item is running
     */
    void restartIfRunning(void);

    /**
     * @brief Adds the item to the shared window (cannot be done in
     * the constructor, because the SettingsScope is still parentless.
     * @param Old SettingsScope
     */
    void parentScopeChanged(SettingsScope *old);

    void showConfigWindow(void);
};

#endif // ROVIZITEMDEVBASEPRIVATE_H
