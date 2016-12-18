#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport)
#endif
#else
#define DLL_PUBLIC 
#endif

#include <iostream>

extern "C" DLL_PUBLIC bool API_Initialize(void) {
	// When Plugin gets loaded
	std::cout << "Loaded My Plugin" << std::endl;
	return true;
}

extern "C" DLL_PUBLIC bool API_Close(void) {
	// When plugin gets unloaded
	std::cout << "Closed My Plugin" << std::endl;
	return true;
}

extern "C" DLL_PUBLIC bool API_OnTick(void) {
	// Every server tick this gets called
	return true;
}