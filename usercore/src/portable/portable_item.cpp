
#include "portable/portable_item.h"
#include "portable/portable_item_p.h"

PortableItem::PortableItem(std::string type_name)
    : PortableItemBase(type_name),
      _this(new PortableItemPrivate(this))
{
    _this->th = nullptr;
    _this->is_stopped = true;
    _this->is_paused = false;
}

PortableItem::~PortableItem()
{
    this->stop();
    for(auto &ent : _this->in_queue)
        delete ent.second;
    _this->in_queue.clear();
}

void PortableItem::starting()
{
}

bool PortableItem::wait()
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [this]{return !_this->is_paused || _this->is_stopped;});

    return !_this->is_stopped;
}

bool PortableItem::running()
{
    return !_this->is_stopped && !_this->is_paused;
}

bool PortableItem::waitForCond(std::function<bool ()> cond)
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [&]{return (!_this->is_paused && cond()) || _this->is_stopped;});

    return !_this->is_stopped;
}

bool PortableItem::waitFor(std::function<bool ()> cond)
{
    while((_this->is_paused || !cond()) && !_this->is_stopped)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return !_this->is_stopped;
}

void PortableItem::wake()
{
    _this->cond.notify_all();
}

std::mutex &PortableItem::mutex()
{
    return _this->mtx;
}

void PortableItem::trimChanged(Trim, double )
{
}

void PortableItem::addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker)
{
    PortableItemBase::addConfig(name, value, checker);
}

void PortableItem::addConfig(std::string name, int *value, std::function<int (int)> checker)
{
    PortableItemBase::addConfig(name, value, checker);
}

void PortableItem::addConfig(std::string name, double *value, std::function<double (double)> checker)
{
    PortableItemBase::addConfig(name, value, checker);
}

void PortableItem::addConfig(std::string name, bool *value)
{
    PortableItemBase::addConfig(name, value);
}

void PortableItem::addConfig(std::string name, std::vector<std::string> possibilities, int *index)
{
    PortableItemBase::addConfig(name, possibilities, index);
}

void PortableItem::pushIn(StreamObject obj, Input in)
{
    if(_this->in_queue.size() < MAX_QUEUE_SIZE)
    {
        _this->in_queue[in]->push(obj);
        _this->cond.notify_all();
    }
}

void PortableItem::stopped()
{
}

void PortableItem::pushOut(StreamObject obj, Output out)
{
    PortableItemBase::pushOut(obj, out);
}

bool PortableItem::waitForInput(Input in)
{
    // Give other threads a chance too
    std::this_thread::yield();

    if(_this->in_queue.find(in) == _this->in_queue.end())
        return false;

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [&]{return _this->in_queue[in]->available() || _this->is_stopped;});

    return !_this->is_stopped;
}

Trim PortableItem::addTrim(std::string name, int min, int max)
{
    return PortableItemBase::addTrim(name, min, max);
}

Trim PortableItem::addTrim(std::string name, double min, double max, int steps)
{
    return PortableItemBase::addTrim(name, min, max, steps);
}

double PortableItem::trimValue(Trim trim)
{
    return PortableItemBase::trimValue(trim);
}

void PortableItem::pause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = true;
}

void PortableItem::unpause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = false;
    this->wake();
}

void PortableItem::start()
{
    this->starting();
    AbstractRobotItem::start();
    _this->is_stopped = false;
    _this->th = new std::thread(&PortableItem::thread, this);
}

void PortableItem::stop()
{
    if(_this->th != nullptr)
    {
        _this->mtx.lock();
        _this->is_stopped = true;
        _this->is_paused = false;
        _this->mtx.unlock();
        _this->cond.notify_all();
        _this->th->join();
        delete _this->th;
        _this->th = nullptr;
    }
    this->stopped();
    PortableItemBase::stop();
}

template<class T>
Input PortableItem::addInput(std::string name)
{
    Input in;

    in = this->addInputBase<T>(name);
    _this->in_queue[in] = new InputQueue();

    return in;
}

template<class T>
Output PortableItem::addOutput(std::string name)
{
    return this->addOutputBase<T>(name);
}

template<class T>
T PortableItem::newest(Input in)
{
    return T(_this->in_queue[in]->newest());
}

template<class T>
T PortableItem::next(Input in)
{
    return T(_this->in_queue[in]->next());
}
