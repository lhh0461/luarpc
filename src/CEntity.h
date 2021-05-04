class IEntity
{
public:
    virtual void RegisterComponent() = 0;
    void Update();
private:
    int iEntityId;
    std::list<IComponent *> m_ComponentList;
};

class IEntity
{

}
