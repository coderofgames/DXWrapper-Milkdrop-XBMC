#ifndef DIS_D3DSURFACE_H
#define DIS_D3DSURFACE_H

#include "DIS_Surface.h"

class ImageSurfaceD3D : public ImageSurface
{
public:
	ImageSurfaceD3D();
	~ImageSurfaceD3D();

	bool UploadToGPU();
};


class CubeImageSurfaceD3D : public CubeImageSurface
{
public:

	CubeImageSurfaceD3D();
	~CubeImageSurfaceD3D();

	bool UploadToGPU();
};



class ImageVolumeD3D : public ImageVolume
{
public:

	ImageVolumeD3D();
	~ImageVolumeD3D();

	bool UploadToGPU();
};

#endif