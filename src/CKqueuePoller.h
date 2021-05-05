#pragma once
#include "Portable.h"

#if defined(HAVE_KQUEUE)

#include <sys/types.h>
#include <sys/event.h>

#include "IPoller.h"

class CKqueuePoller : public IPoller
{
public:
    int AddEvent(int id, int mask);
    int DelEvent(int id, int mask);
    int Poll();
private:
    int kqfd;
    struct kevent *events;
};
#endif