#pragma once
#include <AbstractSchedulerTask.h>

#include <memory>

namespace msge
{


/**
 * Queue holding Tasks in two containers. Adding and removing tasks is done on a back-buffer, while retrieving jobs is done via @code getNext on a front-buffer. 
 * After all tasks are retrieved for a scheduler run, swap needs to be called to exchange front and back buffers. 
 */

class AbstractTaskQueue
{

public:
    using Task = std::unique_ptr<AbstractSchedulerTask>;

    virtual ~AbstractTaskQueue()       = default;

    /**
     * Add a new task. It will be available via getNext only after @code restartIndex
     */
    virtual void addTask(Task&& task) = 0;
    /**
     * Add a new task. It will be removed from the current view only after @code restartIndex
     */
    virtual void removeTask(const TaskId& task) = 0;
    /**
     * Get the next task in line.
     */
    virtual AbstractSchedulerTask& getNext() = 0;
    /**
     * Get number of tasks total in this schedule
     */
    virtual size_t queueLength() const = 0;
    /**
     * Get number of remaining elements
     */
    virtual size_t queueRemaining() const = 0;
    /**
     * check if more elements are available
     */
    virtual bool hasNext() const = 0;
    /**
     * reset the index to start from the front. This also will reflect removed and added tasks.
     */
    virtual void restartIndex() = 0;

};

} //namespace msge