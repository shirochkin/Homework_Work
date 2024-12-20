#include <string>
#include "Leaver.h"
#include <iostream>

namespace LeaverLibraryDynamic {
	LeaverLibrary_API Leaver::Leaver(std::string name) { Leaver::setName(name); };

	LeaverLibrary_API void Leaver::setName(std::string name) {
		this->Name = name;
	}

	LeaverLibrary_API std::string Leaver::leave() {
		std::string out = "До свидания, " + this->Name + "!";
		return out;
	}
}