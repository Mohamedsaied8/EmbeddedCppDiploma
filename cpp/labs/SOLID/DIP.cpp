/////Reference:
/// Design Patterns in Modern C++: Reusable Approaches for Object-Oriented
///
///https://raw.githubusercontent.com/boost-ext/di/cpp14/include/boost/di.hpp

#include <iostream>
#include <ostream>

#include "di.hpp"


struct ILogger
{
	~ILogger() {};
	virtual void Log(const std::string& s) = 0;
};

struct ConsoleLogger: ILogger
{
	void Log(const std::string& s) override
	{
		std::cout << "LOG: " << s.c_str() << std::endl;
	}
};
struct Engine 
{
	/**
	 * \brief 
	 */
	float voulme = 0;
	int hourse_power = 0;

	Engine()
		: voulme(5),
		hourse_power(400)
	{
		std::cout << voulme << std::endl;
	}

	Engine(float _voulme, int hourse_power)
		: voulme(_voulme),
		  hourse_power(hourse_power)
	{
		std::cout << voulme << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& os, const Engine& obj)
	{
		return os
			<< "voulme: " << obj.voulme
			<< " hourse_power: " << obj.hourse_power;
	}
};


struct Car
{

	std::shared_ptr<Engine> engine;
	std::shared_ptr<ILogger> logger;


	explicit Car(const std::shared_ptr<Engine>& _engine)
	{
		engine = _engine;
	}
	explicit Car(const std::shared_ptr<Engine>& _engine,
	 const std::shared_ptr<ILogger>& i_logger)
		: engine(_engine),
		  logger(i_logger)
	{
		logger->Log("Car Created..\n");
	}

	friend std::ostream& operator<<(std::ostream& os, const Car& obj)
	{
		return os <<  "Car with engine: " << *obj.engine;
	}
};


int main (int argc, char ** argv)
{
	using namespace boost::di;
	auto injector = make_injector(bind<ILogger>().to<ConsoleLogger>());
	auto c = injector.create<std::shared_ptr<Car>>();
	c->engine->voulme = 5;
	std::cout << *c<<std::endl;

	auto engine = std::make_shared<Engine>();
	auto console = std::make_shared<ConsoleLogger>();
	auto bmw = std::make_shared<Car>(engine,console);

	//TODO: values
	return 1;
}