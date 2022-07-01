#include <iostream>
#include <string.h>

class String
{
    public:

    String(const char* string)
    {
        printf("created\n");
        mSize = strlen(string);
        m_data = new char[mSize];
        memcpy(m_data,string,mSize);
    }

    String(const String& other)
    {
        printf("Copied\n");
        mSize = other.mSize;
        m_data = new char[mSize];
        memcpy(m_data,other.m_data,mSize);

    }
    
    String(String&& other)
    {
        printf("moved\n");
        mSize = other.mSize;
        m_data = other.m_data;
        other.mSize = 0;
        other.m_data = nullptr;
    }
    
    void print()
    {
        for(int i;i < mSize;i++)
            printf("%c",m_data[i]);
        printf("\n");
    }

    ~String()
    {
        delete m_data;
    }
    private:
    char *m_data;
    uint32_t mSize;
};

class Entity
{
    public:
    Entity(const String& name) : mName(name)
    {

    }
     Entity(String&& name) : mName(std::move(name)) //std::move(name)
    {

    }
    void printName()
    {
        mName.print();
    }
    private:
    String mName;

};

int main()
{
    Entity entity(String("RoboticsCorner"));
    entity.printName();

}