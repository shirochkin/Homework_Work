#pragma once
#include <string>

class Greeter {
public:
	Greeter(std::string name);

	void setName(std::string name);

	std::string greet();

	std::string Name;
};
