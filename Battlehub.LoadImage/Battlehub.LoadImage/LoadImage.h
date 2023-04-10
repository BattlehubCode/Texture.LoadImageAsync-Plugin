#pragma once

#define DLLExport __declspec(dllexport)

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