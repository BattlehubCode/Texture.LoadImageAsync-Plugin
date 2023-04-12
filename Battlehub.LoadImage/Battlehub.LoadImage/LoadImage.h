#pragma once

#if _WIN32 
#define DLLExport __declspec(dllexport)
typedef wchar_t Char;
#else
#define DLLExport
typedef char Char;
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
    DLLExport ImageInfo Battlehub_LoadImage_GetInfo(const Char* path);

    DLLExport void Battlehub_LoadImage_Load(const Char* path, void* bytes, int channels, int mipLevels);
}