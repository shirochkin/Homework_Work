#pragma once
#ifdef LeaverLibraryDynamic_EXPORTS
#define LeaverLibrary_API __declspec(dllexport)
#else
#define LeaverLibrary_API __declspec(dllimport)
#endif

#include <string>

namespace LeaverLibraryDynamic {

LeaverLibrary_API class Leaver {

public:
	Leaver(std::string name);

	void setName(std::string name);

	std::string leave ();

	std::string Name;
};

}
