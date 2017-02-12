
#include "core/roviz_item.h"
#include "core/roviz_item_p.h"

#include <thread>
#include <chrono>
#include "streams/all_streams.h"

RovizItem::RovizItem(std::string type_name)
    : RovizItemBase(type_name),
      _this(new RovizItemPrivate())
{
    _this->th = nullptr;
    _this->is_stopped = true;
    _this->is_paused = false;
}

RovizItem::~RovizItem()
{
    this->stop();
    for(auto &ent : _this->in_queue)
        delete ent.second;
    _this->in_queue.clear();
}

void RovizItem::starting()
{
}

bool RovizItem::wait()
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [this]{return !_this->is_paused || _this->is_stopped;});

    return !_this->is_stopped;
}

bool RovizItem::running() const
{
    return !_this->is_stopped && !_this->is_paused;
}

bool RovizItem::waitForCond(std::function<bool ()> cond)
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [&]{return (!_this->is_paused && cond()) || _this->is_stopped;});

    return !_this->is_stopped;
}

bool RovizItem::waitFor(std::function<bool ()> cond)
{
    while((_this->is_paused || !cond()) && !_this->is_stopped)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return !_this->is_stopped;
}

void RovizItem::wake() const
{
    _this->cond.notify_all();
}

std::mutex &RovizItem::mutex() const
{
    return _this->mtx;
}

void RovizItem::trimChanged(Trim, double)
{
}

void RovizItem::addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker)
{
    RovizItemBase::addConfig(name, value, checker);
}

void RovizItem::addConfig(std::string name, int *value, std::function<int (int)> checker)
{
    RovizItemBase::addConfig(name, value, checker);
}

void RovizItem::addConfig(std::string name, double *value, std::function<double (double)> checker)
{
    RovizItemBase::addConfig(name, value, checker);
}

void RovizItem::addConfig(std::string name, bool *value)
{
    RovizItemBase::addConfig(name, value);
}

void RovizItem::addConfig(std::string name, std::vector<std::string> possibilities, int *index)
{
    RovizItemBase::addConfig(name, possibilities, index);
}

void RovizItem::pushIn(StreamObject obj, Input in)
{
    if(_this->in_queue.size() < MAX_QUEUE_SIZE)
    {
        _this->in_queue[in]->push(obj);
        _this->cond.notify_all();
    }
}

void RovizItem::stopped()
{
}

void RovizItem::pushOut(StreamObject obj, Output out)
{
    RovizItemBase::pushOut(obj, out);
}

bool RovizItem::waitForInput(Input in)
{
    // Give other threads a chance too
    std::this_thread::yield();

    if(_this->in_queue.find(in) == _this->in_queue.end())
        return false;

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [&]{return _this->in_queue[in]->available() || _this->is_stopped;});

    return !_this->is_stopped;
}

Trim RovizItem::addTrim(std::string name, int min, int max)
{
    return RovizItemBase::addTrim(name, min, max);
}

Trim RovizItem::addTrim(std::string name, double min, double max, int steps)
{
    return RovizItemBase::addTrim(name, min, max, steps);
}

double RovizItem::trimValue(Trim trim) const
{
    return RovizItemBase::trimValue(trim);
}

void RovizItem::pause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = true;
}

void RovizItem::unpause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = false;
    this->wake();
}

void RovizItem::start()
{
    this->starting();
    RovizItemBase::start();
    _this->is_stopped = false;
    _this->th = new std::thread(&RovizItem::thread, this);
}

void RovizItem::stop()
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
    RovizItemBase::stop();
}

template<class T>
Input RovizItem::addInput(std::string name)
{
    Input in;

    in = this->addInputBase<T>(name);
    _this->in_queue[in] = new InputQueue();

    return in;
}

template<class T>
Output RovizItem::addOutput(std::string name)
{
    return this->addOutputBase<T>(name);
}

template<class T>
T RovizItem::newest(Input in)
{
    return T(_this->in_queue[in]->newest());
}

template<class T>
T RovizItem::next(Input in)
{
    return T(_this->in_queue[in]->next());
}

INSTANTIATE_PORTABLE_ITEM
