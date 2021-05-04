#include "CEventLoop.h"

void CEventLoop::Run()
{
    poller->Disptach();
}

void RegisterEventHandler()
{
    poller->AddEvent();
}

void DeleteEventHandler()
{
    poller->DeleteEvent();
}
