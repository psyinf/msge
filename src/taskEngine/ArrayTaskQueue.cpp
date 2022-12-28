#include "ArrayTaskQueue.h"
#include <FrameStamp.h>
#include <algorithm>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <fmt/core.h>

void msge::ArrayTaskQueue::addTask(Task&& task)
{
    if (scheduledTasks.end() != std::ranges::find_if(scheduledTasks, [&task](const auto& t) { return t->getProperties().taskId == task->getProperties().taskId; }))
    {
        throw std::invalid_argument(fmt::format("Task with id {} already in queue", task->getProperties().taskId));
    }
    scheduledTasks.emplace_back(std::move(task));
}

void msge::ArrayTaskQueue::removeTask(const TaskId& taskId)
{
    removedTaskIds.insert(taskId);
}

msge::AbstractSchedulerTask& msge::ArrayTaskQueue::getNext()
{
    if (hasNext())
    {
        return *runningTasks.at(queue_iter++);
    }
    throw std::out_of_range("No next task");
}

size_t msge::ArrayTaskQueue::queueLength() const
{
    return runningTasks.size();
}

size_t msge::ArrayTaskQueue::queueRemaining() const
{
    if (queue_iter > queueLength())
    {
        return 0;
    }
    return queueLength() - queue_iter;
}

bool msge::ArrayTaskQueue::hasNext() const
{
    return queueRemaining() > 0;
}

void msge::ArrayTaskQueue::restartIndex()
{
    // clear for new run
    runningTasks.clear();
    // delete removed tasks, indicated by a nullptr
    removedTasks.clear();
    //
    std::erase_if(scheduledTasks, [](const auto& t) { return t == nullptr; });


    queue_iter = 0;

    // make list for scheduled run
    std::ranges::for_each(scheduledTasks, [this](auto& t) { runningTasks.push_back(t.get()); });


    // determine all to be removed due to non re-scheduling
    auto getId     = [](const auto& t) { return t->getProperties().taskId; };
    auto removable = [](const auto& t) { return !t->getProperties().reschedule; };
    auto matches   = [this, getId](const auto& t) { return removedTaskIds.contains(getId(t)); };

    auto toRemoveRange = scheduledTasks | std::views::filter(removable) | std::views::transform(getId);
    std::ranges::copy(toRemoveRange, std::inserter(removedTaskIds, removedTaskIds.end()));
    // take removed out of scheduled
    std::ranges::move(scheduledTasks | std::views::filter(matches), std::insert_iterator(removedTasks, removedTasks.end()));
}
