#ifndef PORTABLEITEM_H
#define PORTABLEITEM_H

/**
 * \defgroup roviz_framework Roviz Framework
 *
 * The roviz framework is optimized to easily manipulate image/video streams
 * within the itemframework. It is completely decoupled from Qt and items that
 * are carefully written can therefore directly run on e.g. embedded hardware.
 * To achieve this portability, the base class of all items, RovizItem, is
 * written portably in pure C++. Depending on how the user compiles the program,
 * RovizItem gets a different base class. To use it with the itemframework, it
 * has RovizItemDevBase as the base class. This is the base class intended for
 * development. A more stripped down framework that would run in some kind of
 * production environment might be called RovizItemProdBase, but this class
 * heavily depends on the use case, which is why it doesn't exist yes. Items
 * that are for simulation/development purposes only, like test image generators
 * and the like, can be flagged as non-exportable by inheriting from
 * RovizItemNoExport, which provides the same interface, but won't be available
 * in production.
 *
 * Items also have a start/pause/stop mechanism that is triggered externally.
 * When an item is started, it gets its own thread where it can process all
 * the data. Pause will make the thread wait, but preserves the state the
 * item currently has. Stop will stop the thread and the item will fall
 * back to its initial state.
 *
 * There are trim values and configs to customize the item. Trim values are
 * nummeric values that can be adjusted at runtime. Adjusting them can for
 * example happen with a slider on a GUI (which RovizItemDevBase provides).
 * Configs on the other hand are not meant to change often. Everytime a config
 * changes, the item is automatically restarted. The advantage of them, is that
 * there are more data types available for configs. They can be used for static
 * values, like frame sizes, that you most likely only have to set once and can
 * forget about afterwards.
 *
 * The robot framework also provides message streams for control data. Once
 * the desired information is extracted from images, these messages could
 * be used to control other applications. They could also be a second
 * source of information that isn't as ressource intensive as images.
 *
 * If you want to write an item using the roviz framework, have a look at
 * RovizItem to get started.
 */

/**
 * \defgroup roviz_plugins Robot Plugins
 *
 * Plugins for the roviz framework.
 *
 * \ingroup roviz_framework
 */

// TODO If one thread alone can't handle all data, spawn more threads
// to already start processing the next images as soon as they arrive.

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <mutex>
#include "bases/export_handling.h"
#include "config/config_base.h"
#include "core/template_decl.h"
#include "core/typedecl.h"
#include "streams/stream_object.h"

// Include the appropriate base class
#include ROVIZ_BASE_INCLUDE

class RovizItemPrivate;

// Maximal number of frames that an input queue can hold.
// Depending on the application, this might have to be adjusted.
// TODO This should be easier to configure
#define MAX_QUEUE_SIZE 32

/**
 * @brief Base class for all items that use the roviz framework.
 *
 * All items using the roviz framework have to inherit from this class. They
 * have to at least implement thread(). This function will run in a seperate
 * thread and can process the image data.
 *
 * The templated functions need to know on what kind of stream they operate.
 * Examples might be Image or Message. You can also implement your own
 * stream-type. Look at Stream<T> for more information. Trying to call e.g.
 * next() with the wrong stream type for the given input will result in
 * undefined behavior!
 *
 * \sa RovizItemBase
 * \sa RovizItemDevBase
 * \sa RovizItemNoExport
 * \ingroup roviz_framework
 */
class ROVIZ_EXPORT_CLASS RovizItem : public RovizItemBase
{
    // The moc won't allow a portable name
    Q_OBJECT

public:
    /**
     * @param typeName The name of the item
     */
    explicit RovizItem(std::string type_name);
    virtual ~RovizItem();

protected:
    /**
     * @brief Called, when the thread is about to start
     *
     * Use this function to reset, clear and initialize everything that might
     * change during runtime. After the call to this function, the item has
     * to be in a clean, fresh state. The item is not allowed to have any
     * information of the previous "session" or thread run left. That would
     * defy the purpose of the start/stop mechanism. The inputs/outputs are
     * preserved, you can set them in the constructor. The thread doesn't run
     * yet at this point.
     *
     * \sa stopped
     */
    virtual void starting(void);

    /**
     * @brief Main thread of the item
     *
     * This function will be executed in a different thread and you can
     * process the image data in here.
     *
     * \sa starting
     * \sa stopped
     */
    virtual void thread(void) = 0;

    /**
     * @brief Stop thread operation
     *
     * __Important:__ You have to call this function in the destructor,
     * otherwise the thread might still run after destruction of the members,
     * even if it is called in the base class destructor.
     *
     * \sa stopped
     * \sa starting
     */
    void stop(void) override;

    /**
     * @brief Called after the thread stopped
     *
     * Called _after_ the thread stopped. You can do some cleanup here if you
     * like.
     *
     * \sa starting
     */
    virtual void stopped(void);

    /**
     * @brief Returns the next object in the input queue
     * @param input The input handle returned from addInput()
     * @return The next object in the input queue
     *
     * \sa addInput
     * \sa newest
     */
    template<class T>
    T next(Input in);

    /**
     * @brief Returns the newest object in the input queue
     * @param input The input handle returned from addInput()
     * @return Returns the newest object in the input queue
     *
     * All older objects in the input queue are discarded.
     *
     * \sa addInput
     * \sa next
     */
    template<class T>
    T newest(Input in);

    /**
     * @brief Send an object out through an output
     * @param obj The object
     * @param out The output handle returned from addOutput()
     *
     * This function is completely thread safe, you can call it from thread()
     * or any other function, like e.g. an event handler.
     *
     * \sa addOutput
     */
    void pushOut(StreamObject obj, Output out);

    /**
     * @brief Add an input
     * @param name Name of the input
     * @return Handle to that input
     *
     * \sa addOutput
     */
    template<class T>
    Input addInput(std::string name);

    /**
     * @brief Add an output
     * @param name Name of the output
     * @return Handle to that output
     *
     * \sa addInput
     * \sa pushOut
     */
    template<class T>
    Output addOutput(std::string name);

    /**
     * @brief Wait until an object is available at the input
     * @param input The input handle returned from addInput()
     * @return true - New object is available
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function should be used by most (image processing) items to ensure
     * the start/pause/stop mechanism works.
     *
     * This function implements the pause/stop mechanism. It doesn't return
     * as long as the item is paused and returns false if it is stopped. It
     * is important that the thread exits when this happens!
     *
     * \sa waitFor
     * \sa wait
     * \sa running
     */
    bool waitForInput(Input in);

    /**
     * @brief Sleep until a condition comes true
     * @param cond Condition to wait for
     * @return true - The condition returned true
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function could be used by image sources that have to wait for
     * hardware events. It will wait until the cond function returns true.
     * The cond function will be called periodically. It might happen, that
     * the thread keeps sleeping and doesn't notice that the condition
     * changed. Use wake() from an event handler or interrupt or something
     * similar to ensure the thread checks the condidion again. If this is not
     * possible, use the less efficient waitFor() instead. This function
     * will aquire the mutex returned by mutex() while executing cond.
     * Make sure you only manipulate the condition while holding that mutex.
     *
     * This function implements the pause/stop mechanism. It doesn't return
     * as long as the item is paused and returns false if it is stopped. It
     * is important that the thread exits when this happens!
     *
     * \sa wake
     * \sa mutex
     * \sa waitForImage
     * \sa wait
     * \sa running
     */
    bool waitForCond(std::function<bool (void)> cond);

    /**
     * @brief Wait until a condition comes true
     * @param cond Condition to wait for
     * @return true - The condition returned true
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function could be used by image sources that have to wait for
     * hardware events. It will wait until the cond function returns true.
     * The cond function will be called periodically. Unlike waitForCond(),
     * this functions guarantees that the condition is evatluated
     * periodically. This function will aquire the mutex returned by mutex()
     * while executing cond. Make sure you only manipulate the condition while
     * holding that mutex.
     *
     * This function implements the pause/stop mechanism. It doesn't return
     * as long as the item is paused and returns false if it is stopped. It
     * is important that the thread exits when this happens!
     *
     * \sa wake
     * \sa mutex
     * \sa waitForImage
     * \sa wait
     * \sa running
     */
    bool waitFor(std::function<bool (void)> cond);

    /**
     * @brief Wait if the item is paused
     * @return true - No need to wait any further
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function could be used for image sources that don't need a
     * condidion to be true to generate an image.
     *
     * This function implements the pause/stop mechanism. It doesn't return
     * as long as the item is paused and returns false if it is stopped. It
     * is important that the thread exits when this happens!
     *
     * \sa waitForImage
     * \sa waitFor
     * \sa running
     */
    bool wait(void);

    /**
     * @brief Check if the thread is running
     * @return true, if the thread is running
     *         false, if the thread is paused or stopped
     *
     * This function does _not_ handle start/pause/stop events itself. It
     * could be used in event handlers, to check, whether they have to
     * process this event, because it doesn't make sense to do that if the
     * thread isn't running anyway. It normally doesn't make much sense to
     * call this function from the thread() function. Use wait() instead
     * for that.
     *
     * \sa waitForImage
     * \sa waitFor
     * \sa wait
     */
    bool running(void) const override;

    /**
     * @brief Wake the possibly waiting thread
     *
     * If you know the thread is waiting for a condidion and e.g. an event
     * handler sees that the condidion has changed, it's a good idea to
     * notify the thread and wake it up.
     *
     * \sa waitFor
     */
    void wake(void) const;

    /**
     * @brief Mutex that waitFor() locks to check the condidion
     * @return Mutex that waitFor() locks to check the condidion
     *
     * Only change the condition waitFor() is waiting for while holding this
     * mutex!
     *
     * \sa waitFor
     * \sa waitForCond
     */
    std::mutex &mutex(void) const;

    /**
     * @brief Add a trim value
     * @param name Name of the value
     * @param min Minimum value
     * @param max Maximum value
     * @return Handle to the trim value
     *
     * Adds a trim value with whole-number steps. See addTrim().
     *
     * \sa addTrim
     * \sa trimValue
     * \sa trimChanged
     */
    Trim addTrim(std::string name, int min, int max) override;

    /**
     * @brief Add a trim value
     * @param name Name of the value
     * @param min Minimum value
     * @param max Maximum value
     * @param steps Number of steps between min and max
     * @return Handle to the trim value
     *
     * A trim value is a value, that can be adjusted (trimmed) at runtime. The
     * user can changed it e.g. through a slider on a GUI.
     */
    Trim addTrim(std::string name, double min, double max, int steps) override;

    /**
     * @brief Get the value of a trim value
     * @param trim Handle to the trim value returned from addTrim()
     * @return The value the trim value currently has
     */
    double trimValue(Trim trim) const override;

    /**
     * @brief Called, when the trim value changed
     * @param trim Handle to the trim value returned from addTrim()
     * @param value New value that the trim value has
     *
     * This function will be called in the main thread, _not_ the thread that
     * the thread() function lives in.
     */
    virtual void trimChanged(Trim trim, double value) override;

    void addConfig(const ConfigBase &config) override;

private:
    std::unique_ptr<RovizItemPrivate> _this;

    /**
     * @name Internal interface functions
     *
     * These functions are not visible to child classes. They are part of the
     * interface that is visible to the base class. The base class can call
     * them to interact with this class. They are marked as override so the
     * base class is forced to implement them as virtual functions. Otherwise,
     * the base class could not even see them.
     */
    ///@{

    /**
     * @brief Add an object to the input queue
     * @param obj The object
     * @param input The input handle returned from addInput()
     *
     * Called by the base class to add a new object to the queue of an input.
     */
    void pushIn(StreamObject obj, Input input) override;

    /**
     * @brief Start execution
     *
     * Starts the thread and the processing of data
     *
     * \sa stop
     * \sa pause
     */
    void start(void) override;

    /**
     * @brief Pause execution
     *
     * Pauses the operation of the item, but does not reset it.
     *
     * \sa unpause
     */
    void pause(void) override;

    /**
     * @brief Resume execution
     *
     * Resumes execution after a call to pause()
     *
     * \sa pause
     */
    void unpause(void) override;
    ///@}
};

#endif // PORTABLEITEM_H
