#ifndef FREE_IMAGE_INTERFACE_H
#define FREE_IMAGE_INTERFACE_H


#include <string>

using std::string;


#include "IMG_ImageSurf.h"


class FreeImageInterface
{
public:

	FreeImageInterface();
	~FreeImageInterface();

	void InitFreeImage();
	void ShutdownFreeImage();

	bool LoadImage( string &filename, ImageMipMapSurface &dest, IMG_FILE_LOAD_DESC *desc);
//	bool LoadImage( string &filename, ImageMipMapSurface &dest, IMG_FILE_LOAD_DESC *desc);

};


#endif

