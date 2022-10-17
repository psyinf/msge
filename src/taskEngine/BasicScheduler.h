#pragma once 
#include "AbstractScheduler.h"

namespace msge{

class BaseScheduler : public AbstractScheduler
{
public:
    ~BaseScheduler() override = default;

    void run() override;

    void putTask(AbstractSchedulerTask* task) override;

private:
    std::vector<AbstractSchedulerTask*> tasks;
};

	
}