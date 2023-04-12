#define STBI_WINDOWS_UTF8
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include "LoadImage.h"

ImageInfo Battlehub_LoadImage_GetInfo(const Char* file)
{
#if _WIN32
	char path[1024] = "";
	stbi_convert_wchar_to_utf8(path, 1024, file);
#else
	char* path = file;
#endif
	ImageInfo info;
	info.status = stbi_info(path, &info.width, &info.height, &info.channels);
	return info;
}

void Battlehub_LoadImage_Load(const Char* file, void* outData, int channels, int mipmapCount)
{
#if _WIN32
	char path[1024] = "";
	stbi_convert_wchar_to_utf8(path, 1024, file);
#else
	char* path = file;
#endif

	stbi_set_flip_vertically_on_load(1);

	int width, height, n;
	unsigned char* pixeldata = stbi_load(path, &width, &height, &n, channels);
	if (pixeldata == nullptr)
	{
		return;
	}

	unsigned char* ptr = (unsigned char*)outData;
	memcpy(ptr, pixeldata, width * height * channels);
	stbi_image_free(pixeldata);

	for (int i = 0; i < mipmapCount - 1; ++i)
	{
		stbir_resize_uint8(ptr, width, height, 0, ptr + width * height * channels, width / 2, height / 2, 0, channels);
		ptr += width * height * channels;
		width /= 2;
		height /= 2;
	}
}
