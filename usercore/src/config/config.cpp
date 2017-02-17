
#include "config/config.h"

#include "core/roviz_item.h"

Config::Config(RovizItem *parent, bool restart_when_changed)
{
    this->item = parent;
    this->has_changed = false;
    this->restart = restart_when_changed;
}

bool Config::changed()
{
    std::lock_guard<std::mutex> lock(this->mtx);

    bool c = this->has_changed;
    this->has_changed = false;

    return c;
}

void Config::stateChanged()
{
    std::lock_guard<std::mutex> lock(this->mtx);

    this->has_changed = true;
    if(this->item != nullptr && this->restart)
        this->item->restart();
}
