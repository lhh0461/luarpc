class IPoller
{
    virtual int AddEvent(int id, int mask) = 0;
    virtual int DelEvent(int id, int mask) = 0;
    virtual int Poll(int millsecond) = 0;
};
