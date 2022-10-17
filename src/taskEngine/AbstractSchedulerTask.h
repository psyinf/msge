#pragma once


#include <cstdint>


namespace msge{
struct FrameStamp;

using TaskId = std::uint32_t;
class AbstractSchedulerTask{
public:
    explicit AbstractSchedulerTask(TaskId id)
        : taskId(id)
    {
    }
    virtual ~AbstractSchedulerTask()               = default;
    virtual void run(const FrameStamp& frameStamp) = 0;

private:
  const  TaskId taskId;
};
	
}