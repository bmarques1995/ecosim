#include <cstdint>
#include <cstdlib>

struct EntityHash
{
    
}

class Entity
{
public:
    //virtual void Move() = 0;
    virtual void Reproduce() = 0;
protected:
    size_t m_Age;
    //size_t m_Energy;
    const char m_Code;
}