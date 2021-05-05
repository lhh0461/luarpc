
#include "CEpollPoller.h"
#if defined(HAVE_EPOLL)

#include <sys/epoll.h>

CEpollPoller::CEpollPoller()
{
    this->efd = epoll_create(1024);
}

int CEpollPoller::AddEvent(int fd, int mask)
{
    struct epoll_event ee = {0}; /* avoid valgrind warning */
    /* If the fd was already monitored for some event, we need a MOD
     *      * operation. Otherwise we need an ADD operation. */
    int op = eventLoop->events[fd].mask == AE_NONE ?
        EPOLL_CTL_ADD : EPOLL_CTL_MOD;

    ee.events = 0;
    mask |= eventLoop->events[fd].mask; /* Merge old events */
    if (mask & AE_READABLE) ee.events |= EPOLLIN;
    if (mask & AE_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.fd = fd;

    if (epoll_ctl(efd,op,fd,&ee) == -1) return -1;
    return 0;
}

int CEpollPoller::DelEvent(int fd, int delmask)
{
    struct epoll_event ee = {0}; /* avoid valgrind warning */
    int mask = eventLoop->events[fd].mask & (~delmask);

    ee.events = 0;
    if (mask & AE_READABLE) ee.events |= EPOLLIN;
    if (mask & AE_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.fd = fd;
    if (mask != AE_NONE) {
        epoll_ctl(state->epfd,EPOLL_CTL_MOD,fd,&ee);
    } else {
        /* Note, Kernel < 2.6.9 requires a non null event pointer even for
         *          * EPOLL_CTL_DEL. */
        epoll_ctl(state->epfd,EPOLL_CTL_DEL,fd,&ee);
    }
}

int CEpollPoller::Poll(int millsecond,  std::function<void(int)>eventcb) {
    epoll_wait(epoll_fd_, events_, max_events_ + 1, millsecond);
}


#endif