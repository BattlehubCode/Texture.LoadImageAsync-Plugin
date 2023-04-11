#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include "LoadImage.h"


ImageInfo Battlehub_LoadImage_GetInfo(const char* path)
{
	ImageInfo info;
	info.status = stbi_info(path, &info.width, &info.height, &info.channels);
	return info;
}

void Battlehub_LoadImage_Load(const char* path, void* outData, int channels, int mipmapCount)
{
	int width, height, n;
	unsigned char* pixeldata = stbi_load(path, &width, &height, &n, channels);
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
