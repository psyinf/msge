#include "BasicScheduler.h"
#include "AbstractTaskQueue.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <future>
#include <ranges>


using namespace msge;

class TestTaskA : public AbstractSchedulerTask
{
public:
   explicit TestTaskA(const std::string& id) 
        : AbstractSchedulerTask(TaskProperties{id, false})
    {
        
    }


    void run(const FrameStamp& frameStamp) override
    {
        std::cout << "Running " << std::quoted(taskProperties.taskId) << std::endl; 
    }
};


class ArrayJobQueue : public AbstractTaskQueue
{
    std::vector<Task::element_type*> running_tasks;
    std::vector<Task>                scheduled_tasks;
    std::vector<TaskId>                removed_tasks;
    std::atomic_size_t queue_iter = 0 ;

public:
    ArrayJobQueue() = default;
    void addTask(Task&& task) override
    {
        scheduled_tasks.emplace_back(std::move(task));
    }

    void removeTask(TaskId taskId) override
    {
        removed_tasks.push_back(taskId);
    }

    AbstractSchedulerTask& getNext() override
    {
        if (hasNext())
        {
            return *running_tasks.at(queue_iter++);
        }
        throw std::out_of_range("No next task");
    }

    size_t queueLength() const override
    {
        return running_tasks.size();
    }

    size_t queueRemaining() const override
    {
        if (queue_iter > queueLength())
        {
            return 0;
        }
        return queueLength() -queue_iter;
    }

    bool hasNext() const override
    {
        return queueRemaining() > 0;
    }

    void restartIndex() override
    {
        queue_iter = 0;
        running_tasks.clear();
        std::ranges::for_each(scheduled_tasks, [this](auto& t) { running_tasks.push_back(t.get()); });
        //remove all that are not rescheduled
        //erase pattern: std::ranges::remove_if(scheduled_tasks, [](auto& t) { return !t->getProperties().reschedule; });
        //remove deleted    
    }
};


int main(int argc, char** argv)
try
{
   
    msge::BasicScheduler scheduler; 
    auto                 ajq = std::make_shared<ArrayJobQueue>();
    scheduler.setTaskQueue(ajq);
    ajq->addTask(std::make_unique<TestTaskA>("A"));
    
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