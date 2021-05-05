#include <functional>

#include "CEventLoop.h"
#include "CEpollPoller.h"

CEventLoop::CEventLoop(int maxset)
{
    poller = new CKqueuePoller(maxset);
    terminate = false;

}

CEventLoop::～CEventLoop()
{
    delete poller;
}

void CEventLoop::Run()
{
    poller->Poll(50, [this](int fd, int mask){
        if (mask & READ_EVENT)
        {
            handlers[fd]->read_event_handler();
        }
        if (mask & WRITE_EVENT)
        {

        }
    });
}

void CEventLoop::RegisterEventHandler(int fd, int event_mask, std::function<int(int)> func, void* data)
{
    if (terminate)
    {
        return;
    }
    poller->AddEvent(fd, event_mask);
    EventHandler eh;
    if （event_mask == READ_EVENT）
    {

    }

}

void CEventLoop::DeleteEventHandler()
{
    poller->DeleteEvent();
}
