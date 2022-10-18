#include "BasicScheduler.h"
#include "ArrayTaskQueue.h"
#include "FrameStamp.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <future>
#include <ranges>


using namespace msge;

class TestTaskA : public AbstractSchedulerTask
{
public:
   explicit TestTaskA(TaskProperties&& properties ) 
        : AbstractSchedulerTask(std::move(properties))
    {
    }


    void run(const FrameStamp& frameStamp) override
    {
      //  std::cout << std::format("Running {}\n", getProperties().taskId);
        std::this_thread::sleep_for(std::chrono::milliseconds(16 * 10));
    }
};
//task that unschedules itself after a number of frames 
class TestTaskB : public AbstractSchedulerTask
{
public:
    explicit TestTaskB(TaskProperties&& properties)
        : AbstractSchedulerTask(std::move(properties))
    {
    }


    void run(const FrameStamp& frameStamp) override
    {
      //  std::cout << std::format("Running {}\n", getProperties().taskId);
        if (frameStamp.frameNumber == 100)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
          //  std::cout << std::format("Ending and unscheduling {}\n", getProperties().taskId);
            getProperties().reschedule = false;
        }
    }
};
void microSleep(std::chrono::nanoseconds time_to_sleep)
{
    if (0 >= time_to_sleep.count())
    {
        return;
    }

    auto                     start = std::chrono::high_resolution_clock::now();
   
    while (std::chrono::nanoseconds(std::chrono::high_resolution_clock::now() - start) < time_to_sleep)
        ;
}

void onFrameEnd(const SchedulerRunInfo& runInfo)
{
    microSleep(std::chrono::milliseconds(500) - runInfo.frameTiming.getDuration());
    if (runInfo.frameNumber % 2 != 0)
    {
        return;
    }
    std::cout << std::format("num tasks: {:04d}---------# {:05d}\n", runInfo.numTasksRun, runInfo.frameNumber);
    //std::cout << runInfo.lastFrameDuration << "\n";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(runInfo.frameTiming.getDuration()) << ")\n";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(runInfo.frameTiming.timeBetweenFrames(runInfo.previousFrameTiming)) << ")\n";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(runInfo.frameTiming.totalFrameTime(runInfo.previousFrameTiming)) << ")\n";
   
    

}
//TODO: unit tests
// dynamically remove/add task while scheduler is running
// 
int main(int argc, char** argv)
try
{
   
    msge::BasicScheduler scheduler; 
    auto                 ajq = std::make_shared<msge::ArrayTaskQueue>();
    scheduler.setTaskQueue(ajq);

    ajq->addTask(std::make_unique<TestTaskA>(TaskProperties{"A", true}));
    ajq->addTask(std::make_unique<TestTaskA>(TaskProperties{"B", true}));
    ajq->addTask(std::make_unique<TestTaskA>(TaskProperties{"C", true}));

    ajq->addTask(std::make_unique<TestTaskA>(TaskProperties{"D", false}));
    ajq->addTask(std::make_unique<TestTaskB>(TaskProperties{"X", true}));

    ajq->addTask(std::make_unique<TestTaskA>(TaskProperties{"A1", true}));
    ajq->addTask(std::make_unique<TestTaskA>(TaskProperties{"B1", true}));
    ajq->addTask(std::make_unique<TestTaskA>(TaskProperties{"C1", true}));

    ajq->addTask(std::make_unique<TestTaskB>(TaskProperties{"Ax1", true}));
    ajq->addTask(std::make_unique<TestTaskB>(TaskProperties{"Bx1", true}));
    ajq->addTask(std::make_unique<TestTaskB>(TaskProperties{"Cx1", true}));
    ajq->addTask(std::make_unique<TestTaskB>(TaskProperties{"Ax2", true}));
    ajq->addTask(std::make_unique<TestTaskB>(TaskProperties{"Bx2", true}));
    ajq->addTask(std::make_unique<TestTaskB>(TaskProperties{"Cx2", true}));
    scheduler.start();
    scheduler.setFrameEndCallback(&onFrameEnd);
    
    auto s = std::jthread([&]{ std::this_thread::sleep_for(std::chrono::seconds(60)); scheduler.stop(); });
    
    scheduler.run();
    
    

    return 0;

}
catch (const std::exception& e )
{
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}
catch (...)
{
    std::cerr << "Uncaught unstructured exception "<< "\n";
}