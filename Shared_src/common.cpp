#include <iostream>

#ifdef PLATFORM_WIN32
#ifdef EXPORT_API
#define API __declspec( dllexport )
#else
#define API __declspec( dllimport )
#endif
#else
#define API
#endif

int API doAnotherThing(int thing)
{
    std::cout << thing << " has been done!" << std::endl;
    return thing;
}