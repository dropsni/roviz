#ifndef ROVIZITEMDEVBASE_H
#define ROVIZITEMDEVBASE_H

#include <string>
#include <functional>
#include <QWidget>
#include "item/abstract_item.h"
#include "core/typedecl.h"
#include "bases/export_handling.h"

class RovizItemDevBasePrivate;

/**
 * @brief Base class that binds PortableItem to traviz/Qt
 * \ingroup robot_framework
 */
class ROVIZ_EXPORT_CLASS RovizItemDevBase : public AbstractItem
{
    Q_OBJECT
    friend class RovizItemDevBasePrivate;

public:
    explicit RovizItemDevBase(std::string typeName);
    virtual ~RovizItemDevBase();

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
     * See the documentation of RovizItem to see what these functions
     * do.
     */
    ///@{
protected:
    virtual bool running(void) = 0;

    template<class T>
    Input addInputBase(std::string name);

    template<class T>
    Output addOutputBase(std::string name);

    virtual void pushOut(StreamObject obj, Output output);
    virtual Trim addTrim(std::string name, int min, int max);
    virtual Trim addTrim(std::string name, double min, double max, int steps);
    virtual double trimValue(Trim trim);
    virtual void trimChanged(Trim trim, double value);
    virtual void addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker = [](std::string a){return a;});
    virtual void addConfig(std::string name, int *value, std::function<int (int)> checker = [](int a){return a;});
    virtual void addConfig(std::string name, double *value, std::function<double (double)> checker = [](double a){return a;});
    virtual void addConfig(std::string name, bool *value);
    virtual void addConfig(std::string name, std::vector<std::string> possibilities, int *index);

public slots:
    virtual void start(void);
    virtual void stop(void);
    void restart(void);
    virtual void pause(void) = 0;
    virtual void unpause(void) = 0;

protected slots:
    virtual void pushIn(StreamObject obj, Input input) = 0;
    ///@}

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void contextMenuPrepare(QMenu &menu) const override;

private:
    QScopedPointer<RovizItemDevBasePrivate> _this;
};

#endif // ROVIZITEMDEVBASE_H
