#include <stdio.h>
#include <jni.h>
#ifdef PLATFORM_ANDROID
#include <android/log.h>
#endif


int dothing(int thing)
{
    printf("%d has been done!\n", thing);
    return thing + 1;
}

#ifndef PLATFORM_ANDROID
JNIEXPORT jint JNICALL
Java_NativeMethods_TestFunction(JNIEnv* env, jclass clazz, int test)
{
    printf("C code called! Pre result: %d\n", test);
    printf("C code called! Result: %d\n", test + 1);
    return test + 1;
}

#else
JNIEXPORT void JNICALL
Java_org_example_cpp_AppActivity_didRegister(JNIEnv *env, jclass clazz, jstring str, jstring str2) 
{
    __android_log_print(ANDROID_LOG_INFO, "Example", "didRegisterCalled!!!!!");
}
#endif