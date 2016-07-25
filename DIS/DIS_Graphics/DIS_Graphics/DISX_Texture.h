#ifndef DISX_FUNCTIONS_H
#define DISX_FUNCTIONS_H

#include "DIS_RenderStates.h"
#include "DIS_Device.h"
#include <float.h> // for FLT_MAX // TEMPORARY

#define _In_
#define _Inout_
#define _Out_



typedef enum DISX_IMAGE_FILEFORMAT { 
  DISX_IFF_BMP          = 0,
  DISX_IFF_JPG          = 1,
  DISX_IFF_TGA          = 2,
  DISX_IFF_PNG          = 3,
  DISX_IFF_DDS          = 4,
  DISX_IFF_PPM          = 5,
  DISX_IFF_DIB          = 6,
  DISX_IFF_HDR          = 7,
  DISX_IFF_PFM          = 8,
  DISX_IFF_FORCE_DWORD  = 0x7fffffff
} DISX_IMAGE_FILEFORMAT, *LPDISX_IMAGE_FILEFORMAT;

typedef struct DISX_IMAGE_INFO {
  UInt32                 Width;
  UInt32                 Height;
  UInt32                 Depth;
  UInt32                 MipLevels;
  DIS_FORMAT            Format;
  DIS_RESOURCETYPE      ResourceType;
  DISX_IMAGE_FILEFORMAT ImageFileFormat;
} DISX_IMAGE_INFO, *LPDISX_IMAGE_INFO;



#ifndef LPDISX_BUFFER
typedef unsigned char* LPDISX_BUFFER;
#endif

#define DISX_DEFAULT            ((UInt32) -1)
#define DISX_DEFAULT_NONPOW2    ((UInt32) -2)
#define DISX_DEFAULT_FLOAT      FLT_MAX
#define DISX_FROM_FILE          ((UINT) -3)
#define DISXFMT_FROM_FILE        ((DIS_FORMAT) -3)

/*
pTexture [out]
Type: LPTEXTURE2D
Pointer to an IDiDIS_Rect3DTexture9 interface, representing the destination texture.
pSrcTexture [in]
Type: LPTEXTURE2D
Pointer to an IDiDIS_Rect3DTexture9 interface, representing the source height-map texture.
pSrcPalette [in]
Type: const DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY type that contains the source palette of 256 colors or NULL.
Flags [in]
Type: UInt32
One or more DISX__NORMALMAP flags that control generation of normal maps.
Channel [in]
Type: UInt32
One DISX__CHANNEL flag specifying the source of height information.
Amplitude [in]
Type: float
Constant value multiplier that increases (or decreases) the values in the normal map. Higher values usually make bumps more visible, lower values usually make bumps less visible.
*/
DIS_RESULT DISX_ComputeNormalMap(
  _Out_  LPTEXTURE2D pTexture,
  _In_   LPTEXTURE2D pSrcTexture,
  _In_   const DIS_PALETTEENTRY *pSrcPalette,
  _In_   UInt32 Flags,
  _In_   UInt32 Channel,
  _In_   float Amplitude
);


/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the cube texture.
pSrcFile [in]
Type: LPCTSTR
Pointer to a string that specifies the filename. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks.
ppCubeTexture [out]
Type: LPCUBETEXTURE2D*
Address of a pointer to an IDiDIS_Rect3DCubeTexture9 interface, representing the created cube texture object.
Return value
Type: DIS_RESULT
If the function succeeds, the return value is D3D_OK. If the function fails, the return value can be one of the following values: D3DERR_INVALIDCALL, D3DERR_NOTAVAILABLE, D3DERR_OUTOFVIDEOMEMORY, DISX_ERR_INVALIDDATA, E_OUTOFMEMORY.
*/
DIS_RESULT DISX_CreateCubeTextureFromFile(
  _In_   LPDEVICE pDevice,
  _In_   M_CTSTR pSrcFile,
  _Out_  LPCUBETEXTURE2D *ppCubeTexture
);

/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the cube texture.
pSrcFile [in]
Type: LPCTSTR
Pointer to a string that specifies the filename. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks.
Size [in]
Type: UInt32
Width and height of the cube texture, in pixels. For example, if the cube texture is an 8-pixel by 8-pixel cube, the value for this parameter should be 8. If this value is 0 or DISX__DEFAULT, the dimensions are taken from the file.
MipLevels [in]
Type: UInt32
Number of mip levels requested. If this value is zero or DISX__DEFAULT, a complete mipmap chain is created.
Usage [in]
Type: UInt32
0 or D3DUSAGE_RENDERTARGET, or D3DUSAGE_DYNAMIC. Setting this flag to D3DUSAGE_RENDERTARGET indicates that the surface is to be used as a render target. The resource can then be passed to the pNewRenderTarget parameter of the SetRenderTarget method. If D3DUSAGE_RENDERTARGET is specified, the application should check that the device supports this operation by calling CheckDeviceFormat. D3DUSAGE_DYNAMIC indicates that the surface should be handled dynamically. For more information about using dynamic textures, see Using Dynamic Textures.
Format [in]
Type: DIS_FORMAT
Member of the DIS_FORMAT enumerated type, describing the requested pixel format for the cube texture. The returned cube texture might have a different format from that specified by Format. Applications should check the format of the returned cube texture. If D3DFMT_UNKNOWN, the format is taken from the file. If D3DFMT_FROM_FILE, the format is taken exactly as it is in the file, and the call will fail if this violates device capabilities.
Pool [in]
Type: DIS_POOL
Member of the DIS_POOL enumerated type, describing the memory class into which the cube texture should be placed.
Filter [in]
Type: UInt32
A combination of one or more DISX__FILTER constants, controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_TRIANGLE | DISX__FILTER_DITHER.
MipFilter [in]
Type: UInt32
A combination of one or more DISX__FILTER constants controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_BOX. In addition, use bits 27-31 to specify the number of mip levels to be skipped (from the top of the mipmap chain) when a .dds texture is loaded into memory; this allows you to skip up to 32 levels.
ColorKey [in]
Type: DIS_COLOR
DIS_COLOR value to replace with transparent black, or 0 to disable the colorkey. This is always a 32-bit ARGB color, independent of the source image format. Alpha is significant, and should usually be set to FF for opaque color keys. Thus, for opaque black, the value would be equal to 0xFF000000.
pSrcInfo [out]
Type: DISX_IMAGE_INFO*
Pointer to a DISX_IMAGE_INFO structure to be filled with a description of the data in the source image file, or NULL.
pPalette [out]
Type: DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure, representing a 256-color palette to fill in, or NULL.
ppCubeTexture [out]
Type: LPCUBETEXTURE2D*
Address of a pointer to an IDiDIS_Rect3DCubeTexture9 interface, representing the created cube texture object.
*/
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
);

/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the cube texture.
pSrcData [in]
Type: void*
Pointer to the file in memory from which to create the cubemap. See Remarks.
SrcDataSize [in]
Type: UInt32
Size of the file in memory, in bytes.
ppCubeTexture [out]
Type: LPCUBETEXTURE2D*
Address of a pointer to an IDiDIS_Rect3DCubeTexture9 interface, representing the created cube texture object.
*/
DIS_RESULT DISX_CreateCubeTextureFromFileInMemory(
  _In_   LPDEVICE pDevice,
  _In_   void* pSrcData,
  _In_   UInt32 SrcDataSize,
  _Out_  LPCUBETEXTURE2D *ppCubeTexture
);

/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the cube texture.
pSrcData [in]
Type: void*
Pointer to the file in memory from which to create the cube texture. See Remarks.
SrcDataSize [in]
Type: UInt32
Size of the file in memory, in bytes.
Size [in]
Type: UInt32
Width (or height) in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file.
MipLevels [in]
Type: UInt32
Number of mip levels requested. If this value is zero or DISX__DEFAULT, a complete mipmap chain is created.
Usage [in]
Type: UInt32
0, D3DUSAGE_RENDERTARGET, or D3DUSAGE_DYNAMIC. Setting this flag to D3DUSAGE_RENDERTARGET indicates that the surface is to be used as a render target. The resource can then be passed to the pNewRenderTarget parameter of the SetRenderTarget method. If D3DUSAGE_RENDERTARGET is specified, the application should check that the device supports this operation by calling CheckDeviceFormat. For more information about using dynamic textures, see Using Dynamic Textures.
Format [in]
Type: DIS_FORMAT
Member of the DIS_FORMAT enumerated type, describing the requested pixel format for the cube texture. The returned texture might have a different format from that specified by Format. Applications should check the format of the returned texture. If D3DFMT_UNKNOWN, the format is taken from the file. If D3DFMT_FROM_FILE, the format is taken exactly as it is in the file, and the call will fail if this violates device capabilities.
Pool [in]
Type: DIS_POOL
Member of the DIS_POOL enumerated type, describing the memory class into which the cube texture should be placed.
Filter [in]
Type: UInt32
A combination of one or more DISX__FILTER controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_TRIANGLE | DISX__FILTER_DITHER.
MipFilter [in]
Type: UInt32
A combination of one or more DISX__FILTER controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_BOX. In addition, use bits 27-31 to specify the number of mip levels to be skipped (from the top of the mipmap chain) when a .dds texture is loaded into memory; this allows you to skip up to 32 levels.
ColorKey [in]
Type: DIS_COLOR
DIS_COLOR value to replace with transparent black, or 0 to disable the colorkey. This is always a 32-bit ARGB color, independent of the source image format. Alpha is significant, and should usually be set to FF for opaque color keys. Thus, for opaque black, the value would be equal to 0xFF000000.
pSrcInfo [in, out]
Type: DISX_IMAGE_INFO*
Pointer to a DISX_IMAGE_INFO structure to be filled with a description of the data in the source image file, or NULL.
pPalette [out]
Type: DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure, representing a 256-color palette to fill in, or NULL. See Remarks.
ppCubeTexture [out]
Type: LPCUBETEXTURE2D*
Address of a pointer to an IDiDIS_Rect3DCubeTexture9 interface, representing the created cube texture object.
*/
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
);



/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the texture.
pSrcFile [in]
Type: LPCTSTR
Pointer to a string that specifies the filename. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks.
ppTexture [out]
Type: LPTEXTURE2D*
Address of a pointer to an IDiDIS_Rect3DTexture9 interface, representing the created texture object.
*/
DIS_RESULT DISX_CreateTextureFromFile(
  _In_   LPDEVICE pDevice,
  _In_   M_CTSTR pSrcFile,
  _Out_  LPTEXTURE2D *ppTexture
);

/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the texture.
pSrcFile [in]
Type: LPCTSTR
Pointer to a string that specifies the filename. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks.
Width [in]
Type: UInt32
Width in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file and rounded up to a power of two. If the device supports non-power of 2 textures and DISX__DEFAULT_NONPOW2 is specified, the size will not be rounded.
Height [in]
Type: UInt32
Height, in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file and rounded up to a power of two. If the device supports non-power of 2 textures and DISX__DEFAULT_NONPOW2 is sepcified, the size will not be rounded.
MipLevels [in]
Type: UInt32
Number of mip levels requested. If this value is zero or DISX__DEFAULT, a complete mipmap chain is created. If DISX__FROM_FILE, the size will be taken exactly as it is in the file, and the call will fail if this violates device capabilities.
Usage [in]
Type: UInt32
0, D3DUSAGE_RENDERTARGET, or D3DUSAGE_DYNAMIC. Setting this flag to D3DUSAGE_RENDERTARGET indicates that the surface is to be used as a render target. The resource can then be passed to the pNewRenderTarget parameter of the SetRenderTarget method. If either D3DUSAGE_RENDERTARGET or D3DUSAGE_DYNAMIC is specified, Pool must be set to DIS_POOL_DEFAULT, and the application should check that the device supports this operation by calling CheckDeviceFormat. D3DUSAGE_DYNAMIC indicates that the surface should be handled dynamically. See Using Dynamic Textures.
Format [in]
Type: DIS_FORMAT
Member of the DIS_FORMAT enumerated type, describing the requested pixel format for the texture. The returned texture might have a different format from that specified by Format. Applications should check the format of the returned texture. If D3DFMT_UNKNOWN, the format is taken from the file. If D3DFMT_FROM_FILE, the format is taken exactly as it is in the file, and the call will fail if this violates device capabilities.
Pool [in]
Type: DIS_POOL
Member of the DIS_POOL enumerated type, describing the memory class into which the texture should be placed.
Filter [in]
Type: UInt32
A combination of one or more DISX__FILTER constants controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_TRIANGLE | DISX__FILTER_DITHER.
MipFilter [in]
Type: UInt32
A combination of one or more DISX__FILTER constants controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_BOX. In addition, use bits 27-31 to specify the number of mip levels to be skipped (from the top of the mipmap chain) when a .dds texture is loaded into memory; this allows you to skip up to 32 levels.
ColorKey [in]
Type: DIS_COLOR
DIS_COLOR value to replace with transparent black, or 0 to disable the color key. This is always a 32-bit ARGB color, independent of the source image format. Alpha is significant and should usually be set to FF for opaque color keys. Thus, for opaque black, the value would be equal to 0xFF000000.
pSrcInfo [in, out]
Type: DISX_IMAGE_INFO*
Pointer to a DISX_IMAGE_INFO structure to be filled in with a description of the data in the source image file, or NULL.
pPalette [out]
Type: DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure, representing a 256-color palette to fill in, or NULL.
ppTexture [out]
Type: LPTEXTURE2D*
Address of a pointer to an IDiDIS_Rect3DTexture9 interface, representing the created texture object.
*/
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
);

/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface representing the device to be associated with the texture.
pSrcData [in]
Type: void*
Pointer to the file in memory from which to create the texture.
SrcDataSize [in]
Type: UInt32
Size in bytes of the file in memory.
ppTexture [out]
Type: LPTEXTURE2D*
Address of a pointer to an IDiDIS_Rect3DTexture9 interface representing the created texture object.
*/
DIS_RESULT DISX_CreateTextureFromFileInMemory(
  _In_   LPDEVICE pDevice,
  _In_   void* pSrcData,
  _In_   UInt32 SrcDataSize,
  _Out_  LPTEXTURE2D *ppTexture
);

/*
Device [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the texture.
pSrcData [in]
Type: void*
Pointer to the file in memory from which to create the texture.
SrcDataSize [in]
Type: UInt32
Size of the file in memory, in bytes.
Width [in]
Type: UInt32
Width in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file.
Height [in]
Type: UInt32
Height, in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file.
MipLevels [in]
Type: UInt32
Number of mip levels requested. If this value is zero or DISX__DEFAULT, a complete mipmap chain is created.
Usage [in]
Type: UInt32
0, D3DUSAGE_RENDERTARGET, or D3DUSAGE_DYNAMIC. Setting this flag to D3DUSAGE_RENDERTARGET indicates that the surface is to be used as a render target. The resource can then be passed to the pNewRenderTarget parameter of the SetRenderTarget method. If either D3DUSAGE_RENDERTARGET or D3DUSAGE_DYNAMIC is specified, Pool must be set to DIS_POOL_DEFAULT, and the application should check that the device supports this operation by calling CheckDeviceFormat. For more information about using dynamic textures, see Using Dynamic Textures.
Format [in]
Type: DIS_FORMAT
Member of the DIS_FORMAT enumerated type, describing the requested pixel format for the texture. The returned texture might have a different format from that specified by Format. Applications should check the format of the returned texture. If D3DFMT_UNKNOWN, the format is taken from the file. If D3DFMT_FROM_FILE, the format is taken exactly as it is in the file, and the call will fail if this violates device capabilities.
Pool [in]
Type: DIS_POOL
Member of the DIS_POOL enumerated type, describing the memory class into which the texture should be placed.
Filter [in]
Type: UInt32
Combination of one or more flags controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_TRIANGLE | DISX__FILTER_DITHER. Each valid filter must contain one of the flags in DISX__FILTER.
MipFilter [in]
Type: UInt32
Combination of one or more flags controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_BOX. Each valid filter must contain one of the flags in DISX__FILTER. In addition, use bits 27-31 to specify the number of mip levels to be skipped (from the top of the mipmap chain) when a .dds texture is loaded into memory; this allows you to skip up to 32 levels.
ColorKey [in]
Type: DIS_COLOR
DIS_COLOR value to replace with transparent black, or 0 to disable the colorkey. This is always a 32-bit ARGB color, independent of the source image format. Alpha is significant and should usually be set to FF for opaque color keys. Thus, for opaque black, the value would be equal to 0xFF000000.
pSrcInfo [in, out]
Type: DISX_IMAGE_INFO*
Pointer to a DISX_IMAGE_INFO structure to be filled with a description of the data in the source image file, or NULL.
pPalette [out]
Type: DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure, representing a 256-color palette to fill in, or NULL. See Remarks.
ppTexture [out]
Type: LPTEXTURE2D*
Address of a pointer to an IDiDIS_Rect3DTexture9 interface, representing the created texture object.
*/
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
);




/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the volume texture.
pSrcFile [in]
Type: LPCTSTR
Pointer to a string that specifies the file name. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks.
ppVolumeTexture [out]
Type: LPVOLUMETEXTURE*
Address of a pointer to an IDiDIS_Rect3DVolumeTexture9 interface representing the created texture object.
*/
DIS_RESULT DISX_CreateVolumeTextureFromFile(
  _In_   LPDEVICE pDevice,
  _In_   M_CTSTR pSrcFile,
  _Out_  LPVOLUMETEXTURE *ppVolumeTexture
);

/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the texture.
pSrcFile [in]
Type: LPCTSTR
Pointer to a string that specifies the filename. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks.
Width [in]
Type: UInt32
Width in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
Height [in]
Type: UInt32
Height, in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
Depth [in]
Type: UInt32
Depth, in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
MipLevels [in]
Type: UInt32
Number of mip levels requested. If this value is zero or DISX__DEFAULT, a complete mipmap chain is created.
Usage [in]
Type: UInt32
0, D3DUSAGE_RENDERTARGET, or D3DUSAGE_DYNAMIC. Setting this flag to D3DUSAGE_RENDERTARGET indicates that the surface is to be used as a render target. The resource can then be passed to the pNewRenderTarget parameter of the SetRenderTarget method. If either D3DUSAGE_RENDERTARGET or D3DUSAGE_DYNAMIC is specified, Pool must be set to DIS_POOL_DEFAULT, and the application should check that the device supports this operation by calling CheckDeviceFormat. D3DUSAGE_DYNAMIC indicates that the surface should be handled dynamically. For more information about using dynamic textures, see Using Dynamic Textures.
Format
Type: DIS_FORMAT
Member of the DIS_FORMAT enumerated type, describing the requested pixel format for the texture. The returned texture might have a different format from that specified by Format. Applications should check the format of the returned texture. If D3DFMT_UNKNOWN, the format is taken from the file. If D3DFMT_FROM_FILE, the format is taken exactly as it is in the file, and the call will fail if this violates device capabilities.
Pool [in]
Type: DIS_POOL
Member of the DIS_POOL enumerated type, describing the memory class into which the texture should be placed.
Filter [in]
Type: UInt32
A combination of one or more DISX__FILTER controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_TRIANGLE | DISX__FILTER_DITHER.
MipFilter [in]
Type: UInt32
A combination of one or more DISX__FILTER controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_BOX. In addition, use bits 27-31 to specify the number of mip levels to be skipped (from the top of the mipmap chain) when a .dds texture is loaded into memory; this allows you to skip up to 32 levels.
ColorKey [in]
Type: DIS_COLOR
DIS_COLOR value to replace with transparent black, or 0 to disable the colorkey. This is always a 32-bit ARGB color, independent of the source image format. Alpha is significant and should usually be set to FF for opaque color keys. Thus, for opaque black, the value would be equal to 0xFF000000.
pSrcInfo [in, out]
Type: DISX_IMAGE_INFO*
Pointer to a DISX_IMAGE_INFO structure to be filled in with a description of the data in the source image file, or NULL.
pPalette [out]
Type: DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure, representing a 256-color palette to fill in, or NULL.
ppTexture [out]
Type: LPVOLUMETEXTURE*
Address of a pointer to an IDiDIS_Rect3DVolumeTexture9 interface, representing the created texture object.
*/
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
);

/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the volume texture.
pSrcFile [in]
Type: void*
Pointer to the file in memory from which to create the volume texture.
SrcData [in]
Type: UInt32
Size of the file in memory, in bytes.
ppVolumeTexture [out]
Type: LPVOLUMETEXTURE
Address of a pointer to an IDiDIS_Rect3DVolumeTexture9 interface, representing the created texture object.
*/
DIS_RESULT DISX_CreateVolumeTextureFromFileInMemory(
  _In_   LPDEVICE pDevice,
  _In_   void* pSrcFile,
  _In_   UInt32 SrcData,
  _Out_  LPVOLUMETEXTURE ppVolumeTexture
);

/*
pDevice [in]
Type: LPDEVICE
Pointer to an IDiDIS_Rect3DDevice9 interface, representing the device to be associated with the texture.
pSrcData [in]
Type: void*
Pointer to the file in memory from which to create the volume texture.
SrcDataSize [in]
Type: UInt32
Size of the file in memory, in bytes.
Width [in]
Type: UInt32
Width in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
Height [in]
Type: UInt32
Height, in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
Depth [in]
Type: UInt32
Depth, in pixels. If this value is zero or DISX__DEFAULT, the dimensions are taken from the file. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
MipLevels [in]
Type: UInt32
Number of mip levels requested. If this value is zero or DISX__DEFAULT, a complete mipmap chain is created.
Usage [in]
Type: UInt32
0, D3DUSAGE_RENDERTARGET, or D3DUSAGE_DYNAMIC. Setting this flag to D3DUSAGE_RENDERTARGET indicates that the surface is to be used as a render target. The resource can then be passed to the pNewRenderTarget parameter of the SetRenderTarget method. If either D3DUSAGE_RENDERTARGET or D3DUSAGE_DYNAMIC is specified, Pool must be set to DIS_POOL_DEFAULT, and the application should check that the device supports this operation by calling CheckDeviceFormat. D3DUSAGE_DYNAMIC indicates that the surface should be handled dynamically. For more information about using dynamic textures, see Using Dynamic Textures.
Format [in]
Type: DIS_FORMAT
Member of the DIS_FORMAT enumerated type, describing the requested pixel format for the texture. The returned texture might have a different format from that specified by Format. Applications should check the format of the returned texture. If D3DFMT_UNKNOWN, the format is taken from the file. If D3DFMT_FROM_FILE, the format is taken exactly as it is in the file, and the call will fail if this violates device capabilities.
Pool [in]
Type: DIS_POOL
Member of the DIS_POOL enumerated type, describing the memory class into which the texture should be placed.
Filter [in]
Type: UInt32
Combination of one or more DISX__FILTER controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_TRIANGLE | DISX__FILTER_DITHER.
MipFilter [in]
Type: UInt32
Combination of one or more DISX__FILTER controlling how the image is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_BOX. In addition, use bits 27-31 to specify the number of mip levels to be skipped (from the top of the mipmap chain) when a .dds texture is loaded into memory; this allows you to skip up to 32 levels.
ColorKey [in]
Type: DIS_COLOR
DIS_COLOR value to replace with transparent black, or 0 to disable the colorkey. This is always a 32-bit ARGB color, independent of the source image format. Alpha is significant and should usually be set to FF for opaque color keys. Thus, for opaque black, the value would be equal to 0xFF000000.
pSrcInfo [in, out]
Type: DISX_IMAGE_INFO*
Pointer to a DISX_IMAGE_INFO structure to be filled in with a description of the data in the source image file, or NULL.
pPalette [out]
Type: DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure, representing a 256-color palette to fill in, or NULL.
ppVolumeTexture [out]
Type: LPVOLUMETEXTURE*
Address of a pointer to an IDiDIS_Rect3DVolumeTexture9 interface, representing the created texture object.
*/
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
);





/*
pTexture [out]
Type: LPCUBETEXTURE2D
Pointer to an IDiDIS_Rect3DCubeTexture9 interface, representing the filled texture.
pFunction [in]
Type: LPDISX_FILL3D
Pointer to a user-provided evaluator function, which will be used to compute the value of each texel. The function follows the prototype of LPDISX_FILL3D.
pData [in]
Type: LPVOID
Pointer to an arbitrary block of user-defined data. This pointer will be passed to the function provided in pFunction.
*/
/*DIS_RESULT DISX_FillCubeTexture(
  _Out_  LPCUBETEXTURE2D pTexture,
  _In_   LPDISX_FILL3D pFunction,
  _In_   LPVOID pData
);*/

/*
pTexture [in]
Type: LPCUBETEXTURE2D
Pointer to an IDiDIS_Rect3DCubeTexture9 object, representing the texture to be filled.
pTextureShader [in]
Type: LPDISX_TEXTURESHADER
Pointer to a IDISX_TextureShader texture shader object.
*/
/*DIS_RESULT DISX_FillCubeTextureTX(
  _In_  LPCUBETEXTURE2D pTexture,
  _In_  LPDISX_TEXTURESHADER pTextureShader
);*/

/*
pTexture [out]
Type: LPTEXTURE2D
Pointer to an IDiDIS_Rect3DTexture9 interface, representing the filled texture.
pFunction [in]
Type: LPDISX_FILL2D
Pointer to a user-provided evaluator function, which will be used to compute the value of each texel. The function follows the prototype of LPDISX_FILL2D.
pData [in]
Type: LPVOID
Pointer to an arbitrary block of user-defined data. This pointer will be passed to the function provided in pFunction.
*/
/*DIS_RESULT DISX_FillTexture(
  _Out_  LPTEXTURE2D pTexture,
  _In_   LPDISX_FILL2D pFunction,
  _In_   LPVOID pData
);*/


/*
pTexture [in, out]
Type: LPTEXTURE2D
Pointer to an IDiDIS_Rect3DTexture9 object, representing the texture to be filled.
pTextureShader [in]
Type: LPDISX_TEXTURESHADER
Pointer to a IDISX_TextureShader texture shader object.
*/
/*DIS_RESULT DISX_FillTextureTX(
  _Inout_  LPTEXTURE2D pTexture,
  _In_     LPDISX_TEXTURESHADER pTextureShader
);*/

/*
pTexture [out]
Type: LPVOLUMETEXTURE
Pointer to an IDiDIS_Rect3DVolumeTexture9 interface, representing the filled texture.
pFunction [in]
Type: LPDISX_FILL3D
Pointer to a user-provided evaluator function, which will be used to compute the value of each texel. The function follows the prototype of LPDISX_FILL3D.
pData [in]
Type: LPVOID
Pointer to an arbitrary block of user-defined data. This pointer will be passed to the function provided in pFunction.
*/
/*DIS_RESULT DISX_FillVolumeTexture(
  _Out_  LPVOLUMETEXTURE pTexture,
  _In_   LPDISX_FILL3D pFunction,
  _In_   LPVOID pData
);*/

/*
*/
/*DIS_RESULT DISX_FillVolumeTextureTX(
  _In_  LPVOLUMETEXTURE pTexture,
  _In_  LPDISX_TEXTURESHADER pTextureShader
);*/

/*
pBaseTexture [in]
Type: LPBASETEXTURE
Pointer to an IDiDIS_Rect3DBaseTexture9 interface that represents the texture object to filter.
pPalette [out]
Type: const DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure that represents a 256-color palette to fill in, or NULL for nonpalettized formats. If a palette is not specified, the default DiDIS_Rect3D palette (an all opaque white palette) is provided. See Remarks.
SrcLevel [in]
Type: UInt32
Level whose image is used to generate the subsequent levels. Specifying DISX__DEFAULT for this parameter is equivalent to specifying 0.
MipFilter [in]
Type: UInt32
Combination of one or more DISX__FILTER controlling how the mipmap is filtered. Specifying DISX__DEFAULT for this parameter is the equivalent of specifying DISX__FILTER_BOX if the texture size is a power of two, and DISX__FILTER_BOX | DISX__FILTER_DITHER otherwise.
*/
DIS_RESULT DISX_FilterTexture(
  _In_   LPBASETEXTURE pBaseTexture,
  _Out_  const DIS_PALETTEENTRY *pPalette,
  _In_   UInt32 SrcLevel,
  _In_   UInt32 MipFilter
);

/*
pSrcFile [in]
Type: LPCSTR
File name of image to retrieve information about. If UNICODE or _UNICODE are defined, this parameter type is LPCWSTR, otherwise, the type is LPCSTR.
pSrcInfo [in]
Type: DISX_IMAGE_INFO*
Pointer to a DISX_IMAGE_INFO structure to be filled with the description of the data in the source file.
*/
DIS_RESULT DISX_GetImageInfoFromFile(
  _In_  M_CSTR pSrcFile,
  _In_  DISX_IMAGE_INFO *pSrcInfo
);

/*
pSrcData [in]
Type: void*
VOID pointer to the source file in memory.
SrcDataSize [in]
Type: UInt32
Size of file in memory, in bytes. .
pSrcInfo [in]
Type: DISX_IMAGE_INFO*
Pointer to a DISX_IMAGE_INFO structure to be filled with the description of the data in the source file.
*/
DIS_RESULT DISX_GetImageInfoFromFileInMemory(
  _In_  void* pSrcData,
  _In_  UInt32 SrcDataSize,
  _In_  DISX_IMAGE_INFO *pSrcInfo
);






  
/*
pDestFile [in]
Type: LPCTSTR
Pointer to a string that specifies the file name of the destination image. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks.
DestFormat [in]
Type: DISX_IMAGE_FILEFORMAT
DISX_IMAGE_FILEFORMAT specifying the file format to use when saving. This function supports saving to all DISX_IMAGE_FILEFORMAT formats except Portable Pixmap (.ppm) and Targa/Truevision Graphics Adapter (.tga).
pSrcTexture [in]
Type: LPBASETEXTURE
Pointer to IDiDIS_Rect3DBaseTexture9 interface, containing the texture to be saved.
pSrcPalette [in]
Type: const DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure containing a palette of 256 colors. This parameter can be NULL.
*/
DIS_RESULT DISX_SaveTextureToFile(
  _In_  M_CTSTR pDestFile,
  _In_  DISX_IMAGE_FILEFORMAT DestFormat,
  _In_  LPBASETEXTURE pSrcTexture,
  _In_  const DIS_PALETTEENTRY *pSrcPalette
);

/*
ppDestBuf [out]
Type: LPDISX_BUFFER*
Address of a pointer to an IDISX_Buffer that will store the image.
DestFormat [in]
Type: DISX_IMAGE_FILEFORMAT
DISX_IMAGE_FILEFORMAT specifying the file format to use when saving. This function supports saving to all DISX_IMAGE_FILEFORMAT formats except Portable Pixmap (.ppm) and Targa/Truevision Graphics Adapter (.tga).
pSrcTexture [in]
Type: LPBASETEXTURE
Pointer to IDiDIS_Rect3DBaseTexture9 interface containing the image to be saved.
pSrcPalette [in]
Type: const DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure containing a palette of 256 colors. This parameter can be NULL.
*/
DIS_RESULT DISX_SaveTextureToFileInMemory(
  _Out_  LPDISX_BUFFER *ppDestBuf,
  _In_   DISX_IMAGE_FILEFORMAT DestFormat,
  _In_   LPBASETEXTURE pSrcTexture,
  _In_   const DIS_PALETTEENTRY *pSrcPalette
);

/*
pDestFile [in]
Type: LPCTSTR
Pointer to a string that specifies the file name of the destination image. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks.
DestFormat [in]
Type: DISX_IMAGE_FILEFORMAT
DISX_IMAGE_FILEFORMAT specifying the file format to use when saving. This function supports saving to all DISX_IMAGE_FILEFORMAT formats except Portable Pixmap (.ppm) and Targa/Truevision Graphics Adapter (.tga).
pSrcVolume [in]
Type: LPVOLUMETEXTURE
Pointer to IDiDIS_Rect3DVolume9 interface containing the image to be saved.
pSrcPalette [in]
Type: const DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure containing a palette of 256 colors. This parameter can be NULL.
pSrcBox [in]
Type: const DIS_BOX*
Pointer to a DIS_BOX structure. Specifies the source box. Set this parameter to NULL to specify the entire volume.
*/
DIS_RESULT DISX_SaveVolumeToFile(
  _In_  M_CTSTR pDestFile,
  _In_  DISX_IMAGE_FILEFORMAT DestFormat,
  _In_  LPVOLUMETEXTURE pSrcVolume,
  _In_  const DIS_PALETTEENTRY *pSrcPalette,
  _In_  const DIS_BOX *pSrcBox
);

/*
ppDestBuf [out]
Type: LPDISX_BUFFER*
Address of a pointer to an IDISX_Buffer buffer that will store the image.
DestFormat [in]
Type: DISX_IMAGE_FILEFORMAT
DISX_IMAGE_FILEFORMAT specifying the file format to use when saving. This function supports saving to all DISX_IMAGE_FILEFORMAT formats except Portable Pixmap (.ppm) and Targa/Truevision Graphics Adapter (.tga).
pSrcVolume [in]
Type: LPVOLUMETEXTURE
Pointer to IDiDIS_Rect3DVolume9 interface containing the image to be saved.
pSrcPalette [in]
Type: const DIS_PALETTEENTRY*
Pointer to a DIS_PALETTEENTRY structure containing a palette of 256 colors. This parameter can be NULL.
pSrcBox [in]
Type: const DIS_BOX*
Pointer to a DIS_BOX structure. Specifies the source box. Set this parameter to NULL to specify the entire volume.
*/
DIS_RESULT DISX_SaveVolumeToFileInMemory(
  _Out_  LPDISX_BUFFER *ppDestBuf,
  _In_   DISX_IMAGE_FILEFORMAT DestFormat,
  _In_   LPVOLUMETEXTURE pSrcVolume,
  _In_   const DIS_PALETTEENTRY *pSrcPalette,
  _In_   const DIS_BOX *pSrcBox
);

#endif