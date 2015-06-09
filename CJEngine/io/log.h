#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#define LOG(msg) {OutputDebugString(msg);}
#endif

#ifndef LOG
#define LOG(msg) {}
#endif
