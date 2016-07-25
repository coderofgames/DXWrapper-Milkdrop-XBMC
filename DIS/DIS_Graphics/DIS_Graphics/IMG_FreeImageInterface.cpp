#include "IMG_FreeImageInterface.h"
#include "FreeImage\Dist\FreeImage.h"

//==============================================================
//==============================================================
FreeImageInterface::FreeImageInterface()
{
	InitFreeImage();
}

//==============================================================
//==============================================================
FreeImageInterface::~FreeImageInterface()
{
	ShutdownFreeImage();
}

//==============================================================
//==============================================================
void FreeImageInterface::InitFreeImage()
{
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif
}

//==============================================================
//==============================================================
void FreeImageInterface::ShutdownFreeImage()
{
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif
}

//==============================================================
// taken from the free image examples, 
// the texture manager from the openGL directory 
// Original : Written by Ben English, benjamin.english@oit.edu
//
// modified for use with the ImageSurf object.
//==============================================================
bool FreeImageInterface::LoadImage( string &filename, ImageMipMapSurface &dest, IMG_FILE_LOAD_DESC *desc)
{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib = NULL;
	//pointer to the image data
	BYTE* bits = NULL;
	//image width and height
	unsigned int width =0, height =0, bpp=0;
	//OpenGL's image ID to map to
	FREE_IMAGE_TYPE image_type=FIT_UNKNOWN;
	FREE_IMAGE_COLOR_TYPE color_type;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename.c_str());
	//if the image failed to load, return failure
	if(!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	bpp = FreeImage_GetBPP(dib);

	image_type = FreeImage_GetImageType(dib);
	color_type = FreeImage_GetColorType(dib);


	desc->Width = width;
	desc->Height = height;

	//if this somehow one of these failed (they shouldn't), return failure
	if((bits == NULL) || (width == 0) || 
		(height == 0) || (bpp == 0))
	{
		FreeImage_Unload(dib);
		return false;
	}

	if( image_type == FIT_UNKNOWN )
	{
		FreeImage_Unload(dib);
		return false;
	}

	bool formatFound = false;
	int bytes_per_pixel= 0;

	switch( image_type )
	{
	case FIT_UNKNOWN:  	// unknown type
	case FIT_UINT32:// array of unsigned long	: unsigned 32-bit
	case FIT_INT32:	// array of long			: signed 32-bit
	case FIT_COMPLEX:// array of FICOMPLEX		: 2 x 64-bit IEEE floating point
	case FIT_DOUBLE: // array of double			: 64-bit IEEE floating point
	default: break;

	case FIT_BITMAP:  // standard image			: 1-, 4-, 8-, 16-, 24-, 32-bit
		{
			formatFound = true;

			// section from OGRE
                if (color_type == FIC_MINISWHITE || color_type == FIC_MINISBLACK)
                {
                        FIBITMAP* newBitmap = FreeImage_ConvertToGreyscale(dib);
                        // free old bitmap and replace
                        FreeImage_Unload(dib);
                        dib = newBitmap;
                        // get new formats
                        bpp = FreeImage_GetBPP(dib);
						bits = FreeImage_GetBits(dib);
                }
                // Perform any colour conversions for RGB
				else if (bpp < 8 || color_type == FIC_PALETTE || color_type == FIC_CMYK)
                {
					FIBITMAP* newBitmap =  NULL;    
					if (FreeImage_IsTransparent(dib))
                    {
						// convert to 32 bit to preserve the transparency 
                        // (the alpha byte will be 0 if pixel is transparent)
                        newBitmap = FreeImage_ConvertTo32Bits(dib);
                    }
                    else
                    {
						// no transparency - only 3 bytes are needed
						newBitmap = FreeImage_ConvertTo24Bits(dib);
                        
					}

                    // free old bitmap and replace
                    FreeImage_Unload(dib);
                    dib = newBitmap;
                    // get new formats
                    bpp = FreeImage_GetBPP(dib);
					bits = FreeImage_GetBits(dib);
				}
                
				desc->Bpp = bpp;

				
				// by this stage, 8-bit is greyscale, 16/24/32 bit are RGB[A]
                switch(bpp)
                {
					case 8:
						desc->Format= DIS_FORMAT::DIS_FMT_L8;
						bytes_per_pixel = 1;
                    break;
                    case 16:
						bytes_per_pixel = 2;
						// Determine 555 or 565 from green mask
                        // cannot be 16-bit greyscale since that's FIT_UINT16
                        if(FreeImage_GetGreenMask(dib) == FI16_565_GREEN_MASK)
                        {
							desc->Format= DIS_FORMAT::DIS_FMT_R5G6B5; 
                        }
                        else
                        {
							
							desc->Format= DIS_FORMAT::DIS_FMT_A1R5G5B5; 
						}
                        break;
					case 24:
						bytes_per_pixel = 3;
						// FreeImage differs per platform
                        //     PF_BYTE_BGR[A] for little endian (== PF_ARGB native)
                        //     PF_BYTE_RGB[A] for big endian (== PF_RGBA native)
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
                        imgData->format = PF_BYTE_RGB;
						desc->Format= DIS_FORMAT::DIS_FMT_R8G8B8; 

#else
                        //imgData->format = PF_BYTE_BGR;
						desc->Format= DIS_FORMAT::DIS_FMT_R8G8B8;
#endif	


                        break;
					case 32:
						bytes_per_pixel =4;
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
                    //imgData->format = PF_BYTE_RGBA;
					desc->Format= DIS_FORMAT::DIS_FMT_A8R8G8B8;
#else
                    //imgData->format = PF_BYTE_BGRA;
					desc->Format= DIS_FORMAT::DIS_FMT_A8B8G8R8;
#endif
                    break;
                                
                                
				};
		}
		break;
	case FIT_UINT16:	// array of unsigned short	: unsigned 16-bit
	case FIT_INT16:	// array of short			: signed 16-bit
		{
			bytes_per_pixel = 2;
			formatFound = true;
			desc->Format = DIS_FORMAT::DIS_FMT_L16;
		}
		break;
	case FIT_FLOAT:	
		{
			bytes_per_pixel = 4;
			formatFound = true; 
			desc->Format = DIS_FORMAT::DIS_FMT_R32F;
		}	
		break;// array of float			: 32-bit IEEE floating point
	case FIT_RGB16:	
		{
			bytes_per_pixel= 8;
			formatFound = true; 
			desc->Format = DIS_FORMAT::DIS_FMT_A16B16G16R16F;
		}
		break;// 48-bit RGB image			: 3 x 16-bit
	case FIT_RGBA16:	
		{
			bytes_per_pixel= 8;
			formatFound = true; 
			desc->Format = DIS_FORMAT::DIS_FMT_A16B16G16R16;
		}
		break;// 64-bit RGBA image		: 4 x 16-bit
	case FIT_RGBF:	
		{
			bytes_per_pixel= 16;
			formatFound = true; 
			desc->Format = DIS_FORMAT::DIS_FMT_A32B32G32R32F;

		}
		break;// 96-bit RGB float image	: 3 x 32-bit IEEE floating point
	case FIT_RGBAF:
		{
			bytes_per_pixel= 16;
			formatFound = true; 
			desc->Format = DIS_FORMAT::DIS_FMT_A32B32G32R32F;
		}
		break;// 128-bit RGBA float image	: 4 x 32-bit IEEE floating point
	};

	int bytesPerPixel = bytes_per_pixel;

	if( (bytesPerPixel == 0) || (formatFound == false))
	{
		FreeImage_Unload(dib);
		return false;
	}

	// 1) Do we need to rescale? use width and height to detect power of two
	// and rescale using
	// DLL_API FIBITMAP *DLL_CALLCONV FreeImage_Rescale(FIBITMAP *dib, int dst_width, int dst_height, FREE_IMAGE_FILTER filter);
	bool isPow2Width = ispow2(width);
	bool isPow2Height = ispow2(height);

	if(  !isPow2Width || !isPow2Height )
	{
		unsigned int NewWidth = width;
		unsigned int NewHeight = height;

		if( !isPow2Width )
		{
			unsigned int smallerPowWidth = pow2_smaller(width);
			unsigned int biggerPowWidth = pow2_bigger(width);
				
			unsigned int smallerDifferenceW = width - smallerPowWidth;
			unsigned int biggerDifferenceW = biggerPowWidth - width;

			NewWidth = smallerDifferenceW > biggerDifferenceW ? biggerPowWidth : smallerPowWidth ;
		}

		if( !isPow2Height )
		{
			unsigned int smallerPowHeight = pow2_smaller(height);
			unsigned int biggerPowHeight = pow2_bigger(height);
				
			unsigned int smallerDifferenceH = height - smallerPowHeight;
			unsigned int biggerDifferenceH = biggerPowHeight - height;

			unsigned int NewHeight = smallerDifferenceH > biggerDifferenceH ? biggerPowHeight : smallerPowHeight;
		}

		bool oldWidthGreater = (width>height);
		bool newWidthGreater = (NewWidth > NewHeight);
		float old_aspect = (oldWidthGreater?width/height:height/width);
		float new_aspect = (newWidthGreater? NewWidth/NewHeight: NewHeight/NewWidth);

		if( (old_aspect != new_aspect) || 
			(newWidthGreater && !oldWidthGreater) )
		{
			// fail
			FreeImage_Unload(dib);
			return false;
		}
		
		FIBITMAP *newDib = FreeImage_Rescale(dib, NewWidth, NewHeight, FILTER_BILINEAR );	
		FreeImage_Unload(dib);
		dib = newDib;

		width = NewWidth;
		height = NewHeight;

		bits = FreeImage_GetBits(dib);

	}

	// 2) are we creating mipmaps? If yes then create the surf to have
	// mipmap levels, and copy over pixels after a resize operation
	if( !dest.Create( width, height, bytes_per_pixel, 1 ) )
	{
		FreeImage_Unload(dib);
		return false;
	}

/*	if( dest.GetTotalSize() > sizeof(bits) )
	{
		FreeImage_Unload(dib);
		return false;
	}*/
//	void *destPtr = dest.GetRawPtr();

	switch( bytes_per_pixel )
	{
	case 1:
		{
		}
		break;
	case 2:
		{
		}
		break;
	case 3:
		{
		}
		break;
	case 4:
		{
		}
		break;
	case 8:
		{
		}
		break;
	case 16:
		{
		}
		break;
	};

	int numMipLevels = dest.GetNumLevels();

	int currWidth = width;
	int currHeight = height;
	for( int i = 0; (i < numMipLevels) && (currWidth > 1) && (currHeight>1); i++ )
	{
		if( (currWidth < width) || (currHeight < height))
		{
			FIBITMAP *newDib = FreeImage_Rescale(dib, currWidth, currHeight, FILTER_BILINEAR );	
			FreeImage_Unload(dib);
			dib = newDib;

			width = currWidth;
			height = currHeight;
			bits = FreeImage_GetBits(dib);
		}

		ImageSurf *pSurf = dest.GetSurfaceLevel(i);
		if( pSurf )
		{
			memcpy( pSurf->GetRawPtr(), (void*)bits, pSurf->GetTotalSize() );
		}
		else
		{
			FreeImage_Unload(dib);
			dest.Destroy();
			return false;
		}
		if( currWidth > 1 )
		{
			currWidth >>= 1;
		}

		if( currHeight > 1 )
		{
			currHeight >>= 1;
		}
	}

	FreeImage_Unload(dib);

	return true;
}
