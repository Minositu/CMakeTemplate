
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
    dothing(0);
    createWindow("Test", 0, 0, 450, 450);

    processMessages();

    shutdownWindow();
    return 0;
}