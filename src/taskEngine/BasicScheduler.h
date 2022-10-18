#pragma once 
#include "AbstractScheduler.h"

namespace msge{

class BasicScheduler : public AbstractScheduler
{
public:
    ~BasicScheduler() override = default;

    void run() override;

    void setTaskQueue(std::shared_ptr<AbstractTaskQueue> taskQueue) override;

    void onFrameEnd(SchedulerRunInfo) override;

private:
    std::shared_ptr<AbstractTaskQueue> taskQueue;
};

	
}