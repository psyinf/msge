#pragma once
#include <AbstractSchedulerTask.h>

#include <cstdint>
#include <chrono>
#include <functional>
#include <memory>
namespace msge {
class AbstractTaskQueue;

class SchedulerRunInfo
{
    std::uint32_t             frameNumber;
    std::chrono::microseconds lastFrameDuration;
    std::chrono::microseconds currentFrameDuration;

};

class AbstractScheduler{
public:
    using FrameEndCallback = std::function<void(SchedulerRunInfo)>;

    virtual ~AbstractScheduler() = default;
    
	void setFrameEndCallback(FrameEndCallback&& cb) {
        frameEndCallback = std::move(cb);
	}

    virtual void onFrameEnd(SchedulerRunInfo) = 0;
    
    virtual void setTaskQueue(std::shared_ptr<AbstractTaskQueue> task) = 0;
    virtual void run() = 0;

    
private:
    FrameEndCallback frameEndCallback;
};
	
}