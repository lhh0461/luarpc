
class IPoller
{
public:
    //抽象接口
    virtual int Create(int max_num) = 0;
    virtual int AddEvent(int id, int mask) = 0;
    virtual int DelEvent(int id, int mask) = 0;
    virtual int Poll(int millsecond, std::function<void(int)>eventcb) = 0;
protected:
    int max_num;
};
