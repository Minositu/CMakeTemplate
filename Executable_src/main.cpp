
// shared library include
#include <sharedLibrary.h>

// static library include
#include <dothing.h>

// std
#include <stdio.h>
#include <string.h>

int main()
{
    printf("HelloWorld!\n");
    int thing = 0;
    thing = dothing(thing);
    thing = doAnotherThing(thing);
    #ifndef PLATFORM_ANDROID
    createWindow("CMakeExample", thing, thing, 450, 450);

    processMessages();

    shutdownWindow();
    #endif
    return 0;
}