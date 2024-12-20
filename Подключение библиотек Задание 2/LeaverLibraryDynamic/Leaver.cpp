#include <string>
#include "Leaver.h"
#include <iostream>

namespace LeaverLibraryDynamic {
	Leaver::Leaver(std::string name) { Leaver::setName(name); };

	void Leaver::setName(std::string name) {
		this->Name = name;
	}

	std::string Leaver::leave() {
		std::string out = "�� ��������, " + this->Name + "!";
		return out;
	}
}