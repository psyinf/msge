#pragma once
#include <AbstractTaskQueue.h>
#include <atomic>
#include <set>
#include <vector>

namespace msge {
	
class ArrayTaskQueue : public AbstractTaskQueue
{
    std::vector<Task::element_type*> runningTasks;
    std::vector<Task>                scheduledTasks;
    std::set<TaskId>                 removedTaskIds;
    std::vector<Task>                removedTasks;
    std::atomic_size_t queue_iter = 0 ;

public:
    ArrayTaskQueue() = default;

    void addTask(Task&& task) override;

    void removeTask(TaskId taskId) override;

    AbstractSchedulerTask& getNext() override;

    size_t queueLength() const override;

    size_t queueRemaining() const override;

    bool hasNext() const override;

    void restartIndex() override;
};

} //namespace msge