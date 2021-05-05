#include "CKqueuePoller.h"

#if defined(HAVE_KQUEUE)

CKqueuePoller::CKqueuePoller()
{
    this->kqfd = kqueue();
    this->events = zmalloc(sizeof(struct kevent)*this->max_num);
}

int CKqueuePoller::AddEvent(int fd, int mask)
{
    struct kevent ke;

    if (mask & READ_EVENT) {
        EV_SET(&ke, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        if (kevent(this->kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
    }
    if (mask & WRITE_EVENT) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
        if (kevent(this->kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
    }
    return 0;
}

int CKqueuePoller::DelEvent(int fd, int delmask)
{
    struct kevent ke;

    if (delmask & READ_EVENT) {
        EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        kevent(this->kqfd, &ke, 1, NULL, 0, NULL);
    }
    if (delmask & WRITE_EVENT) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        kevent(this->kqfd, &ke, 1, NULL, 0, NULL);
    }
    return 0;
}

int CKqueuePoller::Poll(int millsecond, std::function<void(int)> eventcb) {
    int numevents = kevent(this->kqfd, NULL, 0, this->events, this->max_num,
                        &timeout);
    if (numevents > 0)
    {
        for (int i = 0; i < numevents; i++) {
            int mask = 0;
            struct kevent *e = this->events+i;

            if (e->filter == EVFILT_READ) mask |= READ_EVENT;
            if (e->filter == EVFILT_WRITE) mask |= WRITE_EVENT;
            eventcb(fd, mask);
        }
    }
    return 0;
}

#endif