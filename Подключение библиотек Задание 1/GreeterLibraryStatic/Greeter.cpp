#include <string>
#include "Greeter.h"
#include <iostream>

Greeter::Greeter(std::string name) { Greeter::setName(name); };

void Greeter::setName(std::string name) {
	this->Name = name;
}

std::string Greeter::greet() {
std::string out = "Здравствуйте, " + this->Name + "!";
return out;
}

