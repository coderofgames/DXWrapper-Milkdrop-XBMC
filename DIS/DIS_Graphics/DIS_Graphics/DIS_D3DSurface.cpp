#include "DIS_D3DSurface.h"
#include "DIS_RenderStates.h"

//============================================================
// ImageSurfaceD3D Resource
//============================================================

ImageSurfaceD3D::ImageSurfaceD3D() : ImageSurface()
{
}

ImageSurfaceD3D::~ImageSurfaceD3D()
{
}

bool ImageSurfaceD3D::UploadToGPU()
{
	m_pool = DIS_POOL_DEFAULT;
	return true;
}



//============================================================
// CubeImageSurfaceD3D Resource
//============================================================

CubeImageSurfaceD3D::CubeImageSurfaceD3D() : CubeImageSurface()
{
}

CubeImageSurfaceD3D::~CubeImageSurfaceD3D()
{
}

bool CubeImageSurfaceD3D::UploadToGPU()
{
	m_pool = DIS_POOL_DEFAULT;
	return true;
}


//============================================================
// ImageVolumeD3D Resource
//============================================================

ImageVolumeD3D::ImageVolumeD3D() : ImageVolume()
{
}

ImageVolumeD3D::~ImageVolumeD3D()
{
}

bool ImageVolumeD3D::UploadToGPU()
{
	m_pool = DIS_POOL_DEFAULT;
	return true;
}