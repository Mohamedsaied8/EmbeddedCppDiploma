#include <iostream>

using namespace std;

class Singleton
{
public:
	static Singleton *getInstance(); 
 
private:
	Singleton(){}
    Singleton(const Singleton&);
	const Singleton& operator=(const Singleton&);
	static Singleton* instance;
};


Singleton* Singleton::instance = 0;

Singleton* Singleton::getInstance() 
{
	if(!instance) {
		instance = new Singleton();
		cout << "getInstance(): First instance\n";
		return instance;
	}
	else {
		cout << "getInstance(): previous instance\n";
		return instance;
	}
}

int main()
{
	Singleton *s1 = Singleton::getInstance();
	Singleton *s2 = Singleton::getInstance();
	
	return 0;
}
