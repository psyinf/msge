#pragma once
#include <AbstractSchedulerTask.h>

#include <cstdint>
#include <chrono>
#include <functional>

namespace msge {

class SchedulerRunInfo
{
    std::uint32_t             frameNumber;
    std::chrono::microseconds duration;

};

class AbstractScheduler{
public:
	using FrameEndCallback = std::function<void(SchedulerRunInfo)>;

    virtual ~AbstractScheduler() = default;
    
	void setFrameEndCallback(FrameEndCallback cb) {
        frameEndCallback = cb;
	}
    virtual void putTask(AbstractSchedulerTask* task) = 0;
    virtual void run() = 0;

    
private:
    FrameEndCallback frameEndCallback;
};
	
}