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
	LeaverLibrary_API Leaver(std::string name);

	LeaverLibrary_API void setName(std::string name);

	LeaverLibrary_API std::string leave ();

	std::string Name;
};

}
