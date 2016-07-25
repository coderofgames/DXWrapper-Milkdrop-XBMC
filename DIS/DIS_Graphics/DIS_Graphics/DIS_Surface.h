#ifndef DIS_SURFACE_H
#define DIS_SURFACE_H

#include <memory>

#include "DIS_BaseSurface.h"

typedef struct DIS_IMAGE_SURFACE_DESC
{
	int		m_resourceType;
	int		m_pool;
	int		m_bitsPerPixel;
	int		m_width;
	int		m_height;
	int		m_totalSize;
	int		m_format;
}DIS_IMAGE_SURFACE_DESC;

typedef struct DIS_CUBE_SURFACE_DESC
{
	int		m_resourceType;
	int		m_pool;
	int		m_bitsPerPixel;
	int		m_width;
	int		m_height;
	int		m_totalSize;
	int		m_format;
}DIS_CUBE_SURFACE_DESC;

typedef struct DIS_IMAGE_VOLUME_DESC
{
	int		m_resourceType;
	int		m_pool;
	int		m_bitsPerPixel;
	int		m_width;
	int		m_height;
	int		m_depth;
	int		m_totalSize;
	int		m_format;
}DIS_IMAGE_VOLUME_DESC;

//============================================================
// Image Surface Resource
//============================================================
class ImageSurface : public BaseSurface
{
public:

	ImageSurface();
	~ImageSurface();


	void* GetPixelPtr( int X, int Y );
		
	bool	Create( int width, int height, int format );
	void	Destroy();
	bool	GetSurfaceDescription( DIS_IMAGE_SURFACE_DESC *desc );


	void*	GetRawPtr()			{ return m_data; }
	int		GetPixelSizeBPP()		{ return m_bitsPerPixel; }
	int		GetWidth()			{ return m_width; }
	int		GetHeight()			{ return m_height; }
	int		GetTotalSize()		{ return m_totalSize; }


private:


	int		m_bitsPerPixel;
	int		m_width;
	int		m_height;
	int		m_totalSize;



	unsigned char *m_data;
};

//============================================================
// Cube Image Surface Resource
//============================================================
class CubeImageSurface : public BaseSurface
{
public:

	CubeImageSurface();
	~CubeImageSurface();

	void Destroy();

	bool Create( int width, int height, int format );

	ImageSurface* GetFace(int i);

	bool	GetSurfaceDescription( DIS_CUBE_SURFACE_DESC *desc );


	ImageSurface *m_faces[6];
};

//============================================================
// Image Volume Resource
//============================================================
class ImageVolume :public BaseSurface
{
public:

	ImageVolume();
	~ImageVolume();


	void* GetPixelPtr( int X, int Y, int Z );
		
	bool	Create( int width, int height, int depth, int format );
	void	Destroy();


	void*	GetRawPtr()			{ return m_data; }
	int		GetPixelSizeBPP()		{ return m_bitsPerPixel; }
	int		GetWidth()			{ return m_width; }
	int		GetHeight()			{ return m_height; }
	int		GetDepth()			{ return m_depth; }
	int		GetTotalSize()		{ return m_totalSize; }

	bool	GetSurfaceDescription( DIS_IMAGE_VOLUME_DESC *desc );

private:

	int		m_bitsPerPixel;
	int		m_width;
	int		m_height;
	int		m_depth;
	int		m_totalSize;



	unsigned char *m_data;
};

#endif