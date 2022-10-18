#pragma once


#include <string>


namespace msge{
struct FrameStamp;

using TaskId = std::string;

struct TaskProperties
{
    TaskId taskId;
    bool reschedule; ///< needs re-scheduling to run continuously until removed
};


class AbstractSchedulerTask{
public:
    explicit AbstractSchedulerTask(TaskProperties const& taskProperties)
        : taskProperties(taskProperties)
    {
    }
    virtual ~AbstractSchedulerTask()               = default;
    virtual void run(const FrameStamp& frameStamp) = 0;

    const TaskProperties& getProperties() const
    {
        return taskProperties;
    }

protected:
    const TaskProperties taskProperties;
    
};
	
}