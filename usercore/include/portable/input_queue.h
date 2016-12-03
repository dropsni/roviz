#ifndef IMAGEQUEUE_H
#define IMAGEQUEUE_H

#include <list>
#include <mutex>
#include "portable/portable_item_global.h"
#include "portable/portable_image.h"

class PortableImage;

/**
 * @brief A queue to buffer input stream objects
 *
 * Used to queue streams that arrive at item inputs.
 *
 * \ingroup robot_framework
 */
template <class T>
class PORTABLE_EXPORT_CLASS InputQueue
{
public:
    std::mutex mtx;

    InputQueue(){}

    /**
     * @brief Push an object into the queue
     * @param obj The object to push in the queue
     */
    void push(T obj)
    {
        std::lock_guard<std::mutex> g(this->mtx);
        this->objects.push_back(obj);
    }

    /**
     * @brief Get the next object in the queue
     * @return The next object in the queue
     */
    T next(void)
    {
        std::lock_guard<std::mutex> g(this->mtx);
        T obj = this->objects.front();
        this->objects.pop_front();
        return obj;
    }

    /**
     * @brief Get the newest object in the queue
     * @return The newest object in the queue
     *
     * Discards all older objects
     */
    T newest(void)
    {
        std::lock_guard<std::mutex> g(this->mtx);
        T obj = this->objects.back();
        this->objects.clear();
        return obj;
    }

    /**
     * @brief Check whether an object is available
     * @return True if an object is available, false otherwise
     */
    bool available(void)
    {
        std::lock_guard<std::mutex> g(this->mtx);
        return !this->objects.empty();
    }

private:
    std::list<T> objects;
};

#endif // IMAGEQUEUE_H
