#pragma once


namespace msge {

class AbstractFrameScheduler{
    virtual void run() = 0;
    virtual void schedule(Entity)
};
	
}