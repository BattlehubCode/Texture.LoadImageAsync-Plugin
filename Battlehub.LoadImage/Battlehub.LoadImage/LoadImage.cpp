#define STBI_WINDOWS_UTF8
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include "LoadImage.h"

int CalculateMipmapCount(int width, int height)
{
	int maxDimension = fmax(width, height);
	int mipLevels = (int)log2(maxDimension) + 1;
	return mipLevels;
}

int CalculateMipmapArraySize(int width, int height, int channels, int mipmapCount)
{
	int totalSize = 0;
	int currentWidth = width;
	int currentHeight = height;

	for (int i = 0; i < mipmapCount; i++)
	{
		totalSize += currentWidth * currentHeight * channels;
		currentWidth = fmax(1, currentWidth / 2);
		currentHeight = fmax(1, currentHeight / 2);
	}

	return totalSize;
}

void GenerateMipmaps(unsigned char* bytes, int width, int height, int channels, int mipmapCount)
{
	for (int i = 0; i < mipmapCount - 1; ++i)
	{
		stbir_resize_uint8(bytes, width, height, 0, bytes + width * height * channels, width / 2, height / 2, 0, channels);
		bytes += width * height * channels;
		width /= 2;
		height /= 2;
	}
}

ImageInfo Battlehub_LoadImage_GetInfo(const Char* file)
{
#if _WIN32
	char path[1024] = "";
	stbi_convert_wchar_to_utf8(path, 1024, file);
#else
	const char* path = file;
#endif
	ImageInfo info;
	info.status = stbi_info(path, &info.width, &info.height, &info.channels);
	return info;
}


void Battlehub_LoadImage_Load(const Char* file, void* outData, int channels, int mipmapCount, int width, int height)
{
#if _WIN32
	char path[1024] = "";
	stbi_convert_wchar_to_utf8(path, 1024, file);
#else
	const char* path = file;
#endif

	stbi_set_flip_vertically_on_load(1);

	int srcWidth, srcHeight, srcChannels;
	stbi_uc* data = stbi_load(path, &srcWidth, &srcHeight, &srcChannels, channels);
	if (data == NULL)
	{
		return;
	}

	bool resize = width > 0 || height > 0;
	
	if (width <= 0)
	{
		width = srcWidth;
	}	

	if (height <= 0)
	{
		height = srcHeight;
	}
	
	if (channels <= 0)
	{
		channels = srcChannels;
	}
	
	stbi_uc* ptr = (stbi_uc*)outData;
	if (resize)
	{
		stbir_resize_uint8(data, srcWidth, srcHeight, 0, ptr, width , height, 0, channels);
	}
	else
	{
		memcpy(ptr, data, width * height * channels);
	}
	
	stbi_image_free(data);
	
	if (mipmapCount > 1)
	{
		GenerateMipmaps(ptr, width, height, channels, mipmapCount);
	}
}

ImageInfo Battlehub_LoadImage_Load_From_Memory(void* inData, int size, bool mipChain, void** outData)
{
	stbi_set_flip_vertically_on_load(1);

	ImageInfo info = { 0 };

	stbi_uc* ptr = (stbi_uc*)inData;
	stbi_uc* data = stbi_load_from_memory(ptr, size, &info.width, &info.height, &info.channels, 0);
	if (data == NULL)
	{
		return info;
	}

	int mipmapCount = 1;
	if (mipChain)
	{
		mipmapCount = CalculateMipmapCount(info.width, info.height);
	}

	size = CalculateMipmapArraySize(info.width, info.height, info.channels, mipmapCount);
	ptr = (stbi_uc*)malloc(size);
	if (ptr == NULL)
	{
		stbi_image_free(data);
		return info;
	}

	memcpy(ptr, data, info.width * info.height * info.channels);
	stbi_image_free(data);

	if (mipChain)
	{
		GenerateMipmaps(ptr, info.width, info.height, info.channels, mipmapCount);
	}

	*outData = ptr;
	info.status = 1;
	return info;
}

void Battlehub_LoadImage_Free_Memory(void* data)
{
	free(data);
}

