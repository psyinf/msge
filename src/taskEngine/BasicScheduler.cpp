#include "BasicScheduler.h"
#include "AbstractSchedulerTask.h"
#include "AbstractTaskQueue.h"
#include "FrameStamp.h"

#include <chrono>
#include <future>
#include <iostream>
#include <thread>


using namespace msge;

void BasicScheduler::run() //TODO: const/mutable
{

    FrameStamp                     f = {0u, std::chrono::milliseconds(16)};
    
    const auto                     launch_mode = std::launch::async | std::launch::deferred;
    std::vector<std::future<void>> scheduled_tasks;

    //TODO: while running
    while (true)
    {

        while (taskQueue->hasNext())
        {
            auto& task       = taskQueue->getNext();
            auto taskFuture = std::async(launch_mode, [&task, &f]() { task.run(f); });
            scheduled_tasks.emplace_back(std::move(taskFuture));
        }

        std::ranges::for_each(scheduled_tasks, [](auto& future) { future.get(); });
        scheduled_tasks.clear();
        taskQueue->restartIndex();
    }
    
}

void BasicScheduler::setTaskQueue(std::shared_ptr<AbstractTaskQueue> taskQueue)
{
    this->taskQueue = taskQueue;
}

void BasicScheduler::onFrameEnd(SchedulerRunInfo)
{
    taskQueue->restartIndex();
}

