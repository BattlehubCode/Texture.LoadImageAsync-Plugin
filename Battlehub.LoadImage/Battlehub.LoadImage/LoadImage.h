#pragma once

#if defined(__MACH__) || defined(__ANDROID__) || defined(__linux__)
#define DLLExport
#else
#define DLLExport __declspec(dllexport)
#endif


struct ImageInfo
{
    int status;
    int width;
    int height;
    int channels;
};

extern "C"
{
    DLLExport ImageInfo Battlehub_LoadImage_GetInfo(const char* path);

    DLLExport void Battlehub_LoadImage_Load(const char* path, void* bytes, int channels, int mipLevels);
}