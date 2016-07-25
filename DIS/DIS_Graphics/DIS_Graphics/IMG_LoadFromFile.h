#ifndef IMG_LOAD_FROM_FILE_H
#define IMG_LOAD_FROM_FILE_H


#include "IMG_ImageSurf.h"
#include <string>

using std::string;



bool LoadImageFromFile( string &filename, ImageMipMapSurface &dest, IMG_FILE_LOAD_DESC *desc);

#endif