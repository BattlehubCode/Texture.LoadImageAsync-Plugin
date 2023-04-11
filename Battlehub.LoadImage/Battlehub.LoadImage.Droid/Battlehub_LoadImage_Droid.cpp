#include "Battlehub_LoadImage_Droid.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Battlehub_LoadImage_Droid", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Battlehub_LoadImage_Droid", __VA_ARGS__))

extern "C" {
	/* This trivial function returns the platform ABI for which this dynamic native library is compiled.*/
	const char * Battlehub_LoadImage_Droid::getPlatformABI()
	{
	#if defined(__arm__)
	#if defined(__ARM_ARCH_7A__)
	#if defined(__ARM_NEON__)
		#define ABI "armeabi-v7a/NEON"
	#else
		#define ABI "armeabi-v7a"
	#endif
	#else
		#define ABI "armeabi"
	#endif
	#elif defined(__i386__)
		#define ABI "x86"
	#else
		#define ABI "unknown"
	#endif
		LOGI("This dynamic shared library is compiled with ABI: %s", ABI);
		return "This native library is compiled with ABI: %s" ABI ".";
	}

	void Battlehub_LoadImage_Droid()
	{
	}

	Battlehub_LoadImage_Droid::Battlehub_LoadImage_Droid()
	{
	}

	Battlehub_LoadImage_Droid::~Battlehub_LoadImage_Droid()
	{
	}
}
