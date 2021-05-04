
class CEventLoop
{
public:
    CEventLoop();
    ~CEventLoop();
    void Run();
    void RegisterEventHandler();
    void DeleteEventHandler();
private:
    bool terminate;
    IPoller *poller;
    std::vector<CEventHandler *> handlers;
};
