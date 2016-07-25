#include "DISX_Texture.h"
#include "IMG_LoadFromFile.h"


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_ComputeNormalMap(
  _Out_  LPTEXTURE2D pTexture,
  _In_   LPTEXTURE2D pSrcTexture,
  _In_   const DIS_PALETTEENTRY *pSrcPalette,
  _In_   UInt32 Flags,
  _In_   UInt32 Channel,
  _In_   float Amplitude
)
{
	return DIS_OK;
}


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateCubeTextureFromFile(
  _In_   LPDEVICE pDevice,
  _In_   M_CTSTR pSrcFile,
  _Out_  LPCUBETEXTURE2D *ppCubeTexture
)
{
	return DISX_CreateCubeTextureFromFileEx(
			pDevice, pSrcFile, DISX_DEFAULT, DISX_DEFAULT, 0, DIS_FMT_UNKNOWN, 
			DIS_POOL_MANAGED, DISX_DEFAULT, DISX_DEFAULT, 0, NULL, NULL, 
			ppCubeTexture);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateCubeTextureFromFileEx(
  _In_   LPDEVICE pDevice,
  _In_   M_CTSTR pSrcFile,
  _In_   UInt32 Size,
  _In_   UInt32 MipLevels,
  _In_   UInt32 Usage,
  _In_   DIS_FORMAT Format,
  _In_   DIS_POOL Pool,
  _In_   UInt32 Filter,
  _In_   UInt32 MipFilter,
  _In_   DIS_COLOR ColorKey,
  _Out_  DISX_IMAGE_INFO *pSrcInfo,
  _Out_  DIS_PALETTEENTRY *pPalette,
  _Out_  LPCUBETEXTURE2D *ppCubeTexture
)
{
	DIS_RESULT dr = pDevice->CreateCubeTexture(Size, MipLevels, Usage, Format, 
								Pool, ppCubeTexture, 0);

	if( dr == DIS_FAIL )
	{
		return dr;
	}


	return DIS_OK;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateCubeTextureFromFileInMemory(
  _In_   LPDEVICE pDevice,
  _In_   void* pSrcData,
  _In_   UInt32 SrcDataSize,
  _Out_  LPCUBETEXTURE2D *ppCubeTexture
)
{
	return DISX_CreateCubeTextureFromFileInMemoryEx(
			pDevice, pSrcData, SrcDataSize, DISX_DEFAULT, DISX_DEFAULT, 0, 
			DIS_FMT_UNKNOWN, DIS_POOL_MANAGED, DISX_DEFAULT, DISX_DEFAULT, 0, 
			NULL, NULL, ppCubeTexture);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateCubeTextureFromFileInMemoryEx(
  _In_     LPDEVICE pDevice,
  _In_     void* pSrcData,
  _In_     UInt32 SrcDataSize,
  _In_     UInt32 Size,
  _In_     UInt32 MipLevels,
  _In_     UInt32 Usage,
  _In_     DIS_FORMAT Format,
  _In_     DIS_POOL Pool,
  _In_     UInt32 Filter,
  _In_     UInt32 MipFilter,
  _In_     DIS_COLOR ColorKey,
  _Inout_  DISX_IMAGE_INFO *pSrcInfo,
  _Out_    DIS_PALETTEENTRY *pPalette,
  _Out_    LPCUBETEXTURE2D *ppCubeTexture
)
{
	return DIS_OK;
}



//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateTextureFromFile(
  _In_   LPDEVICE pDevice,
  _In_   M_CTSTR pSrcFile,
  _Out_  LPTEXTURE2D *ppTexture
)
{
	return DISX_CreateTextureFromFileEx(
			pDevice, pSrcFile, DISX_DEFAULT, DISX_DEFAULT, DISX_DEFAULT, 0, 
			DIS_FMT_UNKNOWN, DIS_POOL_DEFAULT, DISX_DEFAULT, DISX_DEFAULT, 
			0, NULL, NULL, ppTexture);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateTextureFromFileEx(
  _In_     LPDEVICE pDevice,
  _In_     M_CTSTR pSrcFile,
  _In_     UInt32 Width,
  _In_     UInt32 Height,
  _In_     UInt32 MipLevels,
  _In_     UInt32 Usage,
  _In_     DIS_FORMAT Format,
  _In_     DIS_POOL Pool,
  _In_     UInt32 Filter,
  _In_     UInt32 MipFilter,
  _In_     DIS_COLOR ColorKey,
  _Inout_  DISX_IMAGE_INFO *pSrcInfo,
  _Out_    DIS_PALETTEENTRY *pPalette,
  _Out_    LPTEXTURE2D *ppTexture
)
{
	ImageMipMapSurface img;

	IMG_FILE_LOAD_DESC desc;
	
	if( !LoadImageFromFile(string(pSrcFile), img, &desc))
	{
		return DIS_FAIL;
	}

	DIS_FORMAT fmt = desc.Format;
	if( fmt == DIS_FORMAT::DIS_FMT_R8G8B8 )
		fmt = DIS_FORMAT::DIS_FMT_A8R8G8B8;

	DIS_RESULT dr;
	dr = pDevice->CreateTexture(desc.Width, desc.Height, img.GetNumLevels(), Usage, desc.Format, Pool, &(*ppTexture), 0);

	if( dr != DIS_OK )
	{
		img.Destroy();
		return dr;
	}

	if( img.GetNumLevels() == 1 )
	{

		DIS_LOCKED_RECT lockedRect;
		DIS_Rect pRegion;
		pRegion.x1 = 0;
		pRegion.y1 = 0;
		pRegion.x2 = desc.Width;
		pRegion.y2 = desc.Height;
		dr =(*ppTexture)->LockRect(0,&lockedRect,&pRegion, 0);
		if( dr != DIS_OK )
		{
			(*ppTexture)->Release();
			delete (*ppTexture);
			img.Destroy();
			return dr;
		}


		switch( desc.Format )
		{
		default:
		case DIS_FMT_A8R8G8B8:
		{
			memcpy( (void*)lockedRect.pBits, img.GetRawPtr(0), img.GetTotalSize());
		}
		break;
		case DIS_FORMAT::DIS_FMT_R8G8B8:
			{
				struct pixel
				{
					Byte r,g,b;
				};
				struct destpixel
				{
					Byte a,r,g,b;
				};
				int sourcePitch = img.GetPixelSize();
				int destPitch = lockedRect.Pitch;
				destpixel*  destPtr= (destpixel*)lockedRect.pBits;
				pixel*  sourcePtr= (pixel*)img.GetRawPtr(0);
				for( int i = 0; i < desc.Height; i++ )
				{
					for( int j = 0; j < desc.Width; j++ )
					{
						destPtr[i*desc.Width + j].r = sourcePtr[i*desc.Width + j].r;
						destPtr[i*desc.Width + j].g = sourcePtr[i*desc.Width + j].g;
						destPtr[i*desc.Width + j].b = sourcePtr[i*desc.Width + j].b;
					}
				}	
	
			}
			break;
		};

		(*ppTexture)->UnlockRect(0);
	}
	else
	{
		for( int i = 0; i < img.GetNumLevels() ; i++ )
		{
			ImageSurf *pSurf = img.GetSurfaceLevel(i);

			if( !pSurf )
			{
				img.Destroy();
				(*ppTexture)->Release();
				delete (*ppTexture);
				return DIS_FAIL;
			}

			DIS_LOCKED_RECT lockedRect;
			DIS_Rect pRegion;
			pRegion.x1 = 0;
			pRegion.y1 = 0;
			pRegion.x2 = pSurf->GetWidth();
			pRegion.y2 = pSurf->GetHeight();
			dr =(*ppTexture)->LockRect(i,&lockedRect,&pRegion, 0);
			if( dr != DIS_OK )
			{
				(*ppTexture)->Release();
				delete (*ppTexture);
				img.Destroy();
				return dr;
			}

			switch( desc.Format )
			{
			default:
			case DIS_FMT_A8R8G8B8:
			{
				memcpy( (void*)lockedRect.pBits, pSurf->GetRawPtr(), pSurf->GetTotalSize());
			}
			break;
			case DIS_FORMAT::DIS_FMT_R8G8B8:
				{
					struct pixel
					{
						Byte r,g,b;
					};
					struct destpixel
					{
						Byte a,r,g,b;
					};
					int sourcePitch = pSurf->GetPixelSize();
					int destPitch = lockedRect.Pitch;
					destpixel*  destPtr= (destpixel*)lockedRect.pBits;
					pixel*  sourcePtr= (pixel*)pSurf->GetRawPtr();
					for( int i = 0; i < pSurf->GetHeight(); i++ )
					{
						for( int j = 0; j < pSurf->GetWidth(); j++ )
						{
							destPtr[i*pSurf->GetWidth() + j].r = sourcePtr[i*pSurf->GetWidth() + j].r;
							destPtr[i*pSurf->GetWidth() + j].g = sourcePtr[i*pSurf->GetWidth() + j].g;
							destPtr[i*pSurf->GetWidth() + j].b = sourcePtr[i*pSurf->GetWidth() + j].b;
						}
					}	
	
				}
				break;
			};

			(*ppTexture)->UnlockRect(i);
		}
	}

	img.Destroy();

	return DIS_OK;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateTextureFromFileInMemory(
  _In_   LPDEVICE pDevice,
  _In_   void* pSrcData,
  _In_   UInt32 SrcDataSize,
  _Out_  LPTEXTURE2D *ppTexture
)
{
	return DISX_CreateTextureFromFileInMemoryEx(
			pDevice, pSrcData, SrcDataSize, DISX_DEFAULT, DISX_DEFAULT, 
			DISX_DEFAULT, 0, DIS_FMT_UNKNOWN, DIS_POOL_MANAGED, DISX_DEFAULT, 
			DISX_DEFAULT, 0, NULL, NULL, ppTexture);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateTextureFromFileInMemoryEx(
  _In_     LPDEVICE pDevice,
  _In_     void* pSrcData,
  _In_     UInt32 SrcDataSize,
  _In_     UInt32 Width,
  _In_     UInt32 Height,
  _In_     UInt32 MipLevels,
  _In_     UInt32 Usage,
  _In_     DIS_FORMAT Format,
  _In_     DIS_POOL Pool,
  _In_     UInt32 Filter,
  _In_     UInt32 MipFilter,
  _In_     DIS_COLOR ColorKey,
  _Inout_  DISX_IMAGE_INFO *pSrcInfo,
  _Out_    DIS_PALETTEENTRY *pPalette,
  _Out_    LPTEXTURE2D *ppTexture
)
{
	return DIS_OK;
}




//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateVolumeTextureFromFile(
  _In_   LPDEVICE pDevice,
  _In_   M_CTSTR pSrcFile,
  _Out_  LPVOLUMETEXTURE *ppVolumeTexture
)
{
	return DISX_CreateVolumeTextureFromFileEx(
			pDevice, pSrcFile, DISX_DEFAULT, DISX_DEFAULT, DISX_DEFAULT, 
			DISX_DEFAULT, 0, DIS_FMT_UNKNOWN, DIS_POOL_MANAGED, 
			DISX_DEFAULT, DISX_DEFAULT, 0, NULL, NULL, ppVolumeTexture);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateVolumeTextureFromFileEx(
  _In_     LPDEVICE pDevice,
  _In_     M_CTSTR pSrcFile,
  _In_     UInt32 Width,
  _In_     UInt32 Height,
  _In_     UInt32 Depth,
  _In_     UInt32 MipLevels,
  _In_     UInt32 Usage,
  DIS_FORMAT Format,
  _In_     DIS_POOL Pool,
  _In_     UInt32 Filter,
  _In_     UInt32 MipFilter,
  _In_     DIS_COLOR ColorKey,
  _Inout_  DISX_IMAGE_INFO *pSrcInfo,
  _Out_    DIS_PALETTEENTRY *pPalette,
  _Out_    LPVOLUMETEXTURE *ppTexture
)
{
	return DIS_OK;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateVolumeTextureFromFileInMemory(
  _In_   LPDEVICE pDevice,
  _In_   void* pSrcFile,
  _In_   UInt32 SrcData,
  _Out_  LPVOLUMETEXTURE ppVolumeTexture
)
{
	return DISX_CreateVolumeTextureFromFileInMemoryEx(
			pDevice, pSrcFile, SrcData, DISX_DEFAULT, DISX_DEFAULT, DISX_DEFAULT, 
			DISX_DEFAULT, 0, DIS_FMT_UNKNOWN, DIS_POOL_MANAGED, DISX_DEFAULT, 
			DISX_DEFAULT, 0, NULL, NULL, &ppVolumeTexture);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_CreateVolumeTextureFromFileInMemoryEx(
  _In_     LPDEVICE pDevice,
  _In_     void* pSrcData,
  _In_     UInt32 SrcDataSize,
  _In_     UInt32 Width,
  _In_     UInt32 Height,
  _In_     UInt32 Depth,
  _In_     UInt32 MipLevels,
  _In_     UInt32 Usage,
  _In_     DIS_FORMAT Format,
  _In_     DIS_POOL Pool,
  _In_     UInt32 Filter,
  _In_     UInt32 MipFilter,
  _In_     DIS_COLOR ColorKey,
  _Inout_  DISX_IMAGE_INFO *pSrcInfo,
  _Out_    DIS_PALETTEENTRY *pPalette,
  _Out_    LPVOLUMETEXTURE *ppVolumeTexture
)
{
	return DIS_OK;
}





//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_FilterTexture(
  _In_   LPBASETEXTURE pBaseTexture,
  _Out_  const DIS_PALETTEENTRY *pPalette,
  _In_   UInt32 SrcLevel,
  _In_   UInt32 MipFilter
)
{
	return DIS_OK;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_GetImageInfoFromFile(
  _In_  M_CSTR pSrcFile,
  _In_  DISX_IMAGE_INFO *pSrcInfo
)
{
	return DIS_OK;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_GetImageInfoFromFileInMemory(
  _In_  void* pSrcData,
  _In_  UInt32 SrcDataSize,
  _In_  DISX_IMAGE_INFO *pSrcInfo
)
{
	return DIS_OK;
}






  
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_SaveTextureToFile(
  _In_  M_CTSTR pDestFile,
  _In_  DISX_IMAGE_FILEFORMAT DestFormat,
  _In_  LPBASETEXTURE pSrcTexture,
  _In_  const DIS_PALETTEENTRY *pSrcPalette
)
{
	return DIS_OK;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_SaveTextureToFileInMemory(
  _Out_  LPDISX_BUFFER *ppDestBuf,
  _In_   DISX_IMAGE_FILEFORMAT DestFormat,
  _In_   LPBASETEXTURE pSrcTexture,
  _In_   const DIS_PALETTEENTRY *pSrcPalette
)
{
	return DIS_OK;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_SaveVolumeToFile(
  _In_  M_CTSTR pDestFile,
  _In_  DISX_IMAGE_FILEFORMAT DestFormat,
  _In_  LPVOLUMETEXTURE pSrcVolume,
  _In_  const DIS_PALETTEENTRY *pSrcPalette,
  _In_  const DIS_BOX *pSrcBox
)
{
	return DIS_OK;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
DIS_RESULT DISX_SaveVolumeToFileInMemory(
  _Out_  LPDISX_BUFFER *ppDestBuf,
  _In_   DISX_IMAGE_FILEFORMAT DestFormat,
  _In_   LPVOLUMETEXTURE pSrcVolume,
  _In_   const DIS_PALETTEENTRY *pSrcPalette,
  _In_   const DIS_BOX *pSrcBox
)
{
	return DIS_OK;
}