#include <jni.h>
#include <string>

// This is the JNI function that Kotlin/Java code will call.
// The name must follow the pattern: Java_PackageName_ActivityName_MethodName
// Make sure to replace MainActivity with your actual phone activity name if it's different.
extern "C" JNIEXPORT jstring JNICALL
Java_com_eeshvardasikcm_apmenergytracker_MainActivity_stringFromJNI(
    JNIEnv* env,
    jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
