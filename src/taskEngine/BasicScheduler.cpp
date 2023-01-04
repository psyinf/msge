#include "BasicScheduler.h"
#include "AbstractSchedulerTask.h"
#include "AbstractTaskQueue.h"
#include "FrameStamp.h"

#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <ranges>
#include <thread>


using namespace msge;

void BasicScheduler::run() 
{
    using Clock = std::chrono::high_resolution_clock;


    
    const auto                     launch_mode = std::launch::async;
    std::vector<std::future<void>> scheduled_tasks;
    SchedulerRunInfo               lastRunInfo;

    while (isRunning)
    {
        auto       frame_start = Clock::now();
        auto f = FrameStamp{frameNumber, std::chrono::milliseconds(16)};
        while (taskQueue->hasNext())
        {
            auto& task       = taskQueue->getNext();
            auto taskFuture = std::async(launch_mode, [&task, &f]() { task.run(f); });
            scheduled_tasks.emplace_back(std::move(taskFuture));
        }

        std::ranges::for_each(scheduled_tasks, [](auto& future) { future.get(); });
        
        
        taskQueue->restartIndex();
       
        auto frame_end = Clock::now();
        //auto frame_length = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::duration( - frame_start));

        auto runInfo = SchedulerRunInfo{frameNumber, scheduled_tasks.size(),  {frame_start, frame_end}, lastRunInfo.frameTiming };
        lastRunInfo  = runInfo;
        scheduled_tasks.clear();
        
        onFrameEnd(runInfo);

    }
    std::cout << "Finished running " << std::endl;
    
}

void BasicScheduler::setTaskQueue(std::shared_ptr<AbstractTaskQueue> taskQueue)
{
    this->taskQueue = taskQueue;
}

void BasicScheduler::onFrameEnd(const SchedulerRunInfo& sri)
{
    ++frameNumber;
    AbstractScheduler::onFrameEnd(sri);
}

void BasicScheduler::stop()
{
    isRunning = false;
}

void BasicScheduler::start()
{
    isRunning = true;
}

