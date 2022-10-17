#include "BasicScheduler.h"
#include "FrameStamp.h"

#include <chrono>
#include <future>
#include <iostream>


using namespace msge;

void BaseScheduler::run()
{
    FrameStamp                     f = {0u, std::chrono::milliseconds(16)};
    std::vector<std::future<void>> scheduled_tasks(tasks.size());
    
    auto runTask = [&](auto task){ task->run(f); };
    
    std::ranges::for_each(tasks, [&](auto& task) { scheduled_tasks.emplace_back(std::async(std::launch::async, runTask, task)); });
    std::ranges::for_each(scheduled_tasks, [](auto& future) { future.get(); });
}

void BaseScheduler::putTask(AbstractSchedulerTask* task)
{   
    tasks.emplace_back(task);
}
TODO: scheduler test project/example