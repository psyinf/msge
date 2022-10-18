#pragma once
#include <AbstractSchedulerTask.h>

#include <cstdint>
#include <chrono>
#include <functional>
#include <memory>
namespace msge {
class AbstractTaskQueue;

    using Clock = std::chrono::high_resolution_clock;

class FrameTiming
{
public:
    Clock::time_point frameStart;
    Clock::time_point frameEnd;

    /**
     * Time between start and end of scheduler run
     */
    Clock::duration getDuration() const{
        return frameEnd - frameStart;
    }
    /**
     * Time between end of previous end and current start time
     */
    
    Clock::duration timeBetweenFrames(const FrameTiming& previous) const {
        return frameStart - previous.frameEnd;
    }
    /**
     * Time between frame starts, e.g. actual time passed between frames
     */
    Clock::duration totalFrameTime(const FrameTiming& previous) const {
        return frameEnd - previous.frameEnd;
    }
};

class SchedulerRunInfo
{
public:
    std::uint32_t   frameNumber;
    size_t          numTasksRun;
    FrameTiming     frameTiming;
    FrameTiming     previousFrameTiming;
};

class AbstractScheduler{
public:
    using FrameEndCallback = std::function<void(SchedulerRunInfo)>;

    virtual ~AbstractScheduler() = default;
    
	void setFrameEndCallback(FrameEndCallback&& cb) {
        frameEndCallback = std::move(cb);
	}

    virtual void onFrameEnd(const SchedulerRunInfo& sri) {
        frameEndCallback(sri);
    };
    
    virtual void setTaskQueue(std::shared_ptr<AbstractTaskQueue> task) = 0;
    virtual void run()                                                 = 0;
    virtual void start()                                               = 0;
    virtual void stop()                                                = 0;

    
private:
    FrameEndCallback frameEndCallback;
};
	
}