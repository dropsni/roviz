
#include "core/abstract_robot_item_p.h"

AbstractRobotItemPrivate::AbstractRobotItemPrivate(AbstractRobotItem *q)
{
    this->_this = q;
}

void AbstractRobotItemPrivate::imageInputStateChanged()
{
    ItemInput *in;
    ImageStream *stream;
    StreamToInputMapper *map;

    in = qobject_cast<ItemInput*>(sender());
    if(in == nullptr)
        return;

    map = this->in_mappers.value(in, nullptr);
    if(map != nullptr)
    {
        disconnect(map->conn1);
        disconnect(map->conn2);
        this->in_mappers.remove(in);
        delete map;
    }

    stream = qobject_cast<ImageStream*>(in->data());
    if(stream == nullptr)
        return;

    map = new StreamToInputMapper(this);
    map->input = in;
    map->conn1 = connect(stream, &ImageStream::newImage,
                         map, &StreamToInputMapper::imgInputMapper);
    map->conn2 = connect(map, &StreamToInputMapper::newImage,
                         _this, &AbstractRobotItem::pushImageIn);
    this->in_mappers.insert(in, map);
}

void AbstractRobotItemPrivate::messageInputStateChanged()
{
    ItemInput *in;
    MessageStream *stream;
    StreamToInputMapper *map;

    in = qobject_cast<ItemInput*>(sender());
    if(in == nullptr)
        return;

    map = this->in_mappers.value(in, nullptr);
    if(map != nullptr)
    {
        disconnect(map->conn1);
        disconnect(map->conn2);
        this->in_mappers.remove(in);
        delete map;
    }

    stream = qobject_cast<MessageStream*>(in->data());
    if(stream == nullptr)
        return;

    map = new StreamToInputMapper(this);
    map->input = in;
    map->conn1 = connect(stream, &MessageStream::newMessage,
                         map, &StreamToInputMapper::msgInputMapper);
    map->conn2 = connect(map, &StreamToInputMapper::newMessage,
                         _this, &AbstractRobotItem::pushMessageIn);
    this->in_mappers.insert(in, map);
}

void AbstractRobotItemPrivate::pointcloudInputStateChanged()
{
    ItemInput *in;
    PointStream *stream;
    StreamToInputMapper *map;

    in = qobject_cast<ItemInput*>(sender());
    if(in == nullptr)
        return;

    map = this->in_mappers.value(in, nullptr);
    if(map != nullptr)
    {
        disconnect(map->conn1);
        disconnect(map->conn2);
        this->in_mappers.remove(in);
        delete map;
    }

    stream = qobject_cast<PointStream*>(in->data());
    if(stream == nullptr)
        return;

    map = new StreamToInputMapper(this);
    map->input = in;
    map->conn1 = connect(stream, &PointStream::newPoints,
                         map, &StreamToInputMapper::pcInputMapper);
    map->conn2 = connect(map, &StreamToInputMapper::newPointcloud,
                         _this, &AbstractRobotItem::pushPointcloudIn);
    this->in_mappers.insert(in, map);
}

void AbstractRobotItemPrivate::trimChangedSlot(int value)
{
    QSlider *s;
    SliderLabel *sl;

    s = static_cast<QSlider*>(sender());
    sl = this->slider_to_label[s];
    sl->setValue(value);
    _this->settingsScope()->setValue(QString("Sliders/") + sl->name(), value);

    _this->trimChanged(sl, sl->value());
}

void AbstractRobotItemPrivate::collapseBtnClicked()
{
    QPropertyAnimation *an = new QPropertyAnimation(this->control_base, "maximumWidth");
    an->setDuration(500);

    if(this->control_base->width() < 2)
    {
        // Qt needs some SERIOUS forcing to recalculate it's dimensions...
        this->control_base->hide();
        this->control_base->setMaximumWidth(65535);
        this->control_base->show();

        an->setStartValue(0);
        an->setEndValue(this->control_base->width());
        qobject_cast<QPushButton*>(this->collapse_btn)->setText("-");
    }
    else
    {
        an->setStartValue(this->control_base->width());
        an->setEndValue(0);
        qobject_cast<QPushButton*>(this->collapse_btn)->setText("+");
    }
    an->start();
}

void AbstractRobotItemPrivate::saveConfigs()
{
    this->conf_diag->save(_this->settingsScope());
}

void AbstractRobotItemPrivate::restartIfRunning()
{
    if(_this->running())
        _this->restart();
}

void AbstractRobotItemPrivate::parentScopeChanged(SettingsScope *old)
{
    QString trim_name;

    if(old != nullptr)
        SharedWindow::instance(old)->removeItem(_this);

    if(_this->settingsScope()->parentScope() != nullptr)
    {
        if(old == nullptr)
        {
            for(auto &setting_name : _this->settingsScope()->allSettings().keys())
            {
                if(setting_name.left(8) != "Sliders/")
                    continue;

                trim_name = setting_name.mid(8);
                for(auto &trim : this->slider_to_label.keys())
                {
                    if(this->slider_to_label[trim]->name() == trim_name)
                    {
                        trim->setValue(_this->settingsScope()->value(setting_name).toInt());
                        break;
                    }
                }
            }
        }

        SharedWindow::instance(_this->settingsScope()->parentScope())->addItem(_this);
    }
}
