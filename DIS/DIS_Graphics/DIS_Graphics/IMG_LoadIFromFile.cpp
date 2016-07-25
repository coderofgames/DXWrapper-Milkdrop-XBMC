#include "IMG_LoadFromFile.h"
#include "IMG_FreeImageInterface.h"

FreeImageInterface imageInterface;

bool LoadImageFromFile( string &filename, ImageMipMapSurface &dest, IMG_FILE_LOAD_DESC *desc)
{
	return imageInterface.LoadImage(filename, dest, desc);

}