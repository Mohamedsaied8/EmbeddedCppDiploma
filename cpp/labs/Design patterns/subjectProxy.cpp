#include <iostream>

using namespace std; 

class Subject 
{
public:
    virtual void defineProtocol()=0;
	virtual void request() = 0;
	virtual ~Subject() {}
};
 
class RealSubject : public Subject 
{
public:

    void defineProtocol()
    {

    }
	void request() 
    { 
		cout << "RealSubject.request()" << endl; 
	}
};
 
class Proxy : public Subject 
{
private:
	Subject* realSubject;

public:
	Proxy() : realSubject (new RealSubject())  //allocation for real subject
	{}

	~Proxy() { 
		delete realSubject; 
	}
    void defineProtocol()
    {
       realSubject->defineProtocol(); 
    }
	// Forward calls to the RealSubject:
	void request() 
	{ 
		realSubject->request(); 
	}
};
 

int main() 
{
	Proxy p;
	p.request();
}