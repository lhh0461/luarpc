class IComponent
{
public:
    IComponent();
    virtual ~IComponent();
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
private:
    
};
