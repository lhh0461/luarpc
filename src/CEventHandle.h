class CEventHandle
{
public:
    void SerUserData(void *user_data);
    void CallReadHandler();
    void CallWriteHandler();
private:
    std::function<int(void*, int)> read_event_handler;
    std::function<int(void*, int)> wriete_event_handler;
    void *user_data;
};