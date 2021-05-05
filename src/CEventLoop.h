#include "IPoller.h"

enum EventType
{
    READ_EVENT,
    WRITE_EVENT,
    TIMER_EVENT,
    EXCEPTION_EVENT,
};

class CEventLoop
{
public:
    CEventLoop();
    ~CEventLoop();
    void Run();
    void RegisterEventHandler(int fd, int event_mask, std::function<int(int)> func);
    void DeleteEventHandler();
private:
    int maxset;
    bool terminate;
    IPoller *poller;
    std::map<int, CEventHandler *> handlers;
};
