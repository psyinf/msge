#pragma once


#include <functional>
#include <string>


namespace msge
{
struct FrameStamp;

using TaskId = std::string;

struct TaskProperties
{
    TaskId taskId;
    bool   reschedule = true; ///< needs re-scheduling to run continuously until removed
};


class AbstractSchedulerTask
{
public:
    explicit AbstractSchedulerTask(TaskProperties&& taskProperties)
        : taskProperties(std::move(taskProperties))
    {
    }
    virtual ~AbstractSchedulerTask()               = default;

    AbstractSchedulerTask(AbstractSchedulerTask&&) = default;

    virtual void run(const FrameStamp& frameStamp) = 0;

    const TaskProperties& getProperties() const
    {
        return taskProperties;
    }


    TaskProperties& getProperties()
    {
        return taskProperties;
    }

private:
    TaskProperties taskProperties;
};

class FunctionTask : public AbstractSchedulerTask
{
public:
    using TaskFunction = std::function<void(const FrameStamp& frameStamp)>;
    FunctionTask(const TaskFunction& func, TaskProperties&& taskProperties)
        : AbstractSchedulerTask(std::move(taskProperties))
        , func(func)
    {
    }

    FunctionTask(FunctionTask&& rhs) noexcept 
        : AbstractSchedulerTask(std::move(rhs.getProperties()))
    {
        func = std::move(rhs.func);
    }
    void run(const FrameStamp& frameStamp) override
    {
        func(frameStamp);
    }

private:
    TaskFunction func;
};
} // namespace msge