#pragma once
#include "Portable.h"

#if defined(HAVE_EPOLL)

#include "IPoller.h"

class CEpollPoller : public IPoller
{
public:
    int AddEvent(int id, int mask);
    int DelEvent(int id, int mask);
    int Poll();
private:
    int efd;
    struct epoll_event *events;
};

#endif