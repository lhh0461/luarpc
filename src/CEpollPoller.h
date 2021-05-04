class CEpollPoller : public IPoller
{
public:
    int AddEvent(int id, int mask);
    int DelEvent(int id, int mask);
    int Poll();
private:
    
};
