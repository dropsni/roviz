#ifndef ABSTRACTROBOTITEM_H
#define ABSTRACTROBOTITEM_H

#include <QObject>
#include <QLabel>
#include <QSlider>
#include <QImage>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QMap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QScopedPointer>
#include <QMenu>
#include "gui/gui_manager.h"
#include "item/abstract_item.h"
#include "gui/shared_window.h"
#include "gui/slider_label.h"
#include "gui/image_widget.h"
#include "helper/settings_scope.h"
#include "item/item_input.h"
#include "item/item_output.h"
#include "core/image_stream.h"
#include "core/stream_to_input_mapper.h"
#include "gui/config_dialog.h"
#include "core/message_stream.h"
#include "core/point_stream.h"
#include "core/message_stream.h"
#include "portable/strong_typedef.h"

class AbstractRobotItemPrivate;

// To be able to be the base class of PortableItem
class AbstractRobotItem;
typedef AbstractRobotItem PortableItemBase;

/**
 * @brief Base class that binds PortableItem to traviz/Qt
 * \ingroup robot_framework
 */
class ROBOTCORE_EXPORT AbstractRobotItem : public AbstractItem
{
    Q_OBJECT
    friend class AbstractRobotItemPrivate;

public:
    explicit AbstractRobotItem(std::string typeName);
    virtual ~AbstractRobotItem();

    /**
     * @return The main widget of the item
     *
     * Can be overwritten to show a custom widget. (Enclose in #ifdef QT_PRESENT when overriding)
     *
     * \sa SharedWindow
     */
    virtual QWidget *widget(void);

    /**
     * @name Interface implementation
     *
     * Implementation of the interface that PortableItem demands.
     * See the documentation of PortableItem to see what these functions
     * do.
     */
    ///@{
protected:
    virtual bool running(void) = 0;
    virtual ImageInput addImageInput(std::string name);
    virtual ImageOutput addImageOutput(std::string name);
    virtual void pushImageOut(PortableImage img, ImageOutput output);
    virtual Trim addTrim(std::string name, int min, int max);
    virtual Trim addTrim(std::string name, double min, double max, int steps);
    virtual double trimValue(Trim trim);
    virtual void trimChanged(Trim trim, double value);
    virtual void addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker = [](std::string a){return a;});
    virtual void addConfig(std::string name, int *value, std::function<int (int)> checker = [](int a){return a;});
    virtual void addConfig(std::string name, double *value, std::function<double (double)> checker = [](double a){return a;});
    virtual void addConfig(std::string name, bool *value);
    virtual void addConfig(std::string name, std::vector<std::string> possibilities, int *index);
    virtual MessageOutput addMessageOutput(std::string name);
    virtual MessageInput addMessageInput(std::string name);
    virtual void pushMessageOut(Message message, MessageOutput output);
    virtual void pushMessageIn(Message msg, MessageInput input);
    virtual PointcloudInput addPointcloudInput(std::string name);
    virtual PointcloudOutput addPointcloudOutput(std::string name);
    virtual void pushPointcloudOut(Pointcloud pc, PointcloudOutput output);

public slots:
    virtual void start(void);
    virtual void stop(void);
    void restart(void);
    virtual void pause(void) = 0;
    virtual void unpause(void) = 0;

protected slots:
    virtual void pushImageIn(const PortableImage img, ImageInput input) = 0;
    virtual void pushPointcloudIn(const Pointcloud pc, PointcloudInput input) = 0;
    virtual void newMessageReceived(Message message, MessageInput input) = 0;
    ///@}

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void contextMenuPrepare(QMenu &menu) const override;

private:
    QScopedPointer<AbstractRobotItemPrivate> _this;
};

#endif // ABSTRACTROBOTITEM_H
