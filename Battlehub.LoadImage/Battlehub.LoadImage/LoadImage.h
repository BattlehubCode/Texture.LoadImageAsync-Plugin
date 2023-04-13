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

    DLLExport void Battlehub_LoadImage_Load(const Char* path, void* bytes, int channels, int mipmapCount);

    DLLExport ImageInfo Battlehub_LoadImage_Load_From_Memory(void* bytes, int size, bool mipChain, void** outBytes);

    DLLExport void Battlehub_LoadImage_Free_Memory(void* data);
}