#pragma once
#include "AbstractScheduler.h"

#include <atomic>

namespace msge
{

class BasicScheduler : public AbstractScheduler
{
public:
  
    ~BasicScheduler() override = default;

    void run() override;

    void setTaskQueue(std::shared_ptr<AbstractTaskQueue> taskQueue) override;

    void onFrameEnd(const SchedulerRunInfo&) override;


    void stop() override;

    void start() override;
private:
    std::shared_ptr<AbstractTaskQueue> taskQueue;
    std::atomic_bool                   isRunning{false};
    std::uint32_t                      frameNumber{0};
};


} // namespace msge
