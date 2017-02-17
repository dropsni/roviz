#ifndef CONFIG_H
#define CONFIG_H

#include <mutex>
#include <QObject>

class RovizItem;
class QWidget;

// Deriving from QObject in case some child class wants to use signals
class Config : QObject
{
Q_OBJECT

public:
    Config(RovizItem *parent, bool restart_when_changed = false);
    virtual ~Config() = default;

    bool changed(void);
    virtual QWidget *widget(void) const = 0;

protected:
    std::mutex mtx;

protected slots:
    void stateChanged(void);

private:
    RovizItem *item;
    bool has_changed;
    bool restart;
};

#endif // CONFIG_H
