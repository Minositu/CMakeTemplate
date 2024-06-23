#include <stdio.h>
#ifdef PLATFORM_ANDROID
#include <jni.h>
#include <android/log.h>
#endif


int dothing(int thing)
{
    printf("%d has been done!\n", thing);
    return thing + 1;
}

#ifdef PLATFORM_ANDROID
JNIEXPORT void JNICALL
Java_org_example_cpp_AppActivity_didRegister(JNIEnv *env, jclass clazz, jstring str, jstring str2) 
{
    __android_log_print(ANDROID_LOG_INFO, "Example", "didRegisterCalled!!!!!");
}
#endif