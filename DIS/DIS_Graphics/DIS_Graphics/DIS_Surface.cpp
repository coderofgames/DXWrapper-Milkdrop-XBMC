#include "DIS_RenderStates.h"
#include "DIS_Surface.h"

//============================================================
// Helper Function to resolve format
//============================================================
Int32 BppFromFormat( int format )
{
	switch( format )
	{
		case DIS_FMT_UNKNOWN              : return 0;

		case DIS_FMT_R8G8B8               : return 24;
		case DIS_FMT_A8R8G8B8             :return 32;
		case DIS_FMT_X8R8G8B8             :return 32;
		case DIS_FMT_R5G6B5               :return 16;
		case DIS_FMT_X1R5G5B5             :return 16;
		case DIS_FMT_A1R5G5B5             :return 16;
		case DIS_FMT_A4R4G4B4             :return 16;// 26:
		case DIS_FMT_R3G3B2               :return 8;// 27:
		case DIS_FMT_A8                   :return 8;// 28:
		case DIS_FMT_A8R3G3B2             :return 16;// 29:
		case DIS_FMT_X4R4G4B4             :return 16;// 30:
		case DIS_FMT_A2B10G10R10          :return 32;// 31:
		case DIS_FMT_A8B8G8R8             :return 32;// 32:
		case DIS_FMT_X8B8G8R8             :return 32;// 33:
		case DIS_FMT_G16R16               :return 32;// 34:
		case DIS_FMT_A2R10G10B10          :return 32;// 35:
		case DIS_FMT_A16B16G16R16         :return 64;// 36:

		case DIS_FMT_A8P8                 :return 16;// 40:
		case DIS_FMT_P8                   :return 8;// 41:

		case DIS_FMT_L8                   :return 8;// 50:
		case DIS_FMT_A8L8                 :return 16;// 51:
		case DIS_FMT_A4L4                 :return 8;// 52:

		case DIS_FMT_V8U8                 :return 16;// 60:
		case DIS_FMT_L6V5U5               :return 16;// 61:
		case DIS_FMT_X8L8V8U8             :return 32;// 62:
		case DIS_FMT_Q8W8V8U8             :return 32;// 63:
		case DIS_FMT_V16U16               :return 32;// 64:
		case DIS_FMT_A2W10V10U10          :return 32;// 67:

		case DIS_FMT_UYVY                 :return 32;// MAKEFOURCC('U': 'Y': 'V': 'Y'):
		case DIS_FMT_R8G8_B8G8            :return 32;// MAKEFOURCC('R': 'G': 'B': 'G'):
		case DIS_FMT_YUY2                 :return 0;// MAKEFOURCC('Y': 'U': 'Y': '2'):
		case DIS_FMT_G8R8_G8B8            :return 32;// MAKEFOURCC('G': 'R': 'G': 'B'):
		case DIS_FMT_DXT1                 :return 32;// MAKEFOURCC('D': 'X': 'T': '1'):
		case DIS_FMT_DXT2                 :return 32;// MAKEFOURCC('D': 'X': 'T': '2'):
		case DIS_FMT_DXT3                 :return 32;// MAKEFOURCC('D': 'X': 'T': '3'):
		case DIS_FMT_DXT4                 :return 16;// MAKEFOURCC('D': 'X': 'T': '4'):
		case DIS_FMT_DXT5                 :return 32;// MAKEFOURCC('D': 'X': 'T': '5'):

		case DIS_FMT_D16_LOCKABLE         :return 16;// 70:
		case DIS_FMT_D32                  :return 32;// 71:
		case DIS_FMT_D15S1                :return 16;// 73:
		case DIS_FMT_D24S8                :return 32;// 75:
		case DIS_FMT_D24X8                :return 32;// 77:
		case DIS_FMT_D24X4S4              :return 32;// 79:
		case DIS_FMT_D16                  :return 16;// 80:

		case DIS_FMT_D32F_LOCKABLE        :return 32;// 82:
		case DIS_FMT_D24FS8               :return 32;// 83:



		case DIS_FMT_L16                  :return 16;// 81:

		case DIS_FMT_VERTEXDATA           :return 0;//100:
		case DIS_FMT_INDEX16              :return 16;//101:
		case DIS_FMT_INDEX32              :return 32;//102:

		case DIS_FMT_Q16W16V16U16         :return 64;//110:

		case DIS_FMT_MULTI2_ARGB8         :return 32;// MAKEFOURCC('M':'E':'T':'1'):

		case DIS_FMT_R16F                 :return 16;// 111:
		case DIS_FMT_G16R16F              :return 32;// 112:
		case DIS_FMT_A16B16G16R16F        :return 64;// 113:

		case DIS_FMT_R32F                 :return 32;// 114:
		case DIS_FMT_G32R32F              :return 64;// 115:
		case DIS_FMT_A32B32G32R32F        :return 128;// 116:

		case DIS_FMT_CxV8U8               :return 32;// 117:
	//#if !defined(case DIS__case DISABLE_9EX)
		case DIS_FMT_D32_LOCKABLE         :return 32;// 84:
		case DIS_FMT_S8_LOCKABLE          :return 8;// 85:

		case DIS_FMT_A1                   :return 1;// 118:
		case DIS_FMT_A2B10G10R10_XR_BIAS  :return 32;// 119:
		case DIS_FMT_BINARYBUFFER         :return 1;// 199:
		default: return 32;
	};
};


//============================================================
// Image Surface Resource
//============================================================

ImageSurface::ImageSurface() : BaseSurface()
{
	m_data = 0;
	m_width = 0;
	m_height = 0;
	m_bitsPerPixel = 0;
	m_totalSize = 0;
	m_pool = DIS_POOL_SYSTEMMEM;
	m_resourceType = DIS_RTYPE_TEXTURE;
}

ImageSurface::~ImageSurface()
{
	Destroy();
}

bool ImageSurface::Create( int width, int height, int format )
{
	m_format = format;
	m_width = width;
	m_height = height;
	m_bitsPerPixel = BppFromFormat(format);
		
	if( m_bitsPerPixel == 0 )
	{
		m_format = 0;
		m_width = 0;
		m_height = 0;
		m_bitsPerPixel = 0;
		return false;
	}

	m_totalSize = m_width * m_height * m_bitsPerPixel/8;

	m_data = (unsigned char*)malloc(m_totalSize);

	if( sizeof(m_data) == m_totalSize )
	{
		m_ok = true;
		return true;
	}

	return false;
}

void ImageSurface::Destroy()
{
	if( m_data )
	{
		delete [] m_data;
		m_data = 0;
		m_ok = false;
		m_totalSize = 0;
		m_bitsPerPixel = 0;
		m_width = 0;
		m_height = 0;
	}
}

bool ImageSurface::GetSurfaceDescription( DIS_IMAGE_SURFACE_DESC *desc )
{
	if( !m_ok ) return false;

	desc->m_bitsPerPixel	= m_bitsPerPixel;
	desc->m_width			= m_width;
	desc->m_height			= m_height;
	desc->m_pool			= m_pool;
	desc->m_totalSize		= m_totalSize;
	desc->m_resourceType	= m_resourceType;
	desc->m_format			= m_format;

	return true;
}

void* ImageSurface::GetPixelPtr( int X, int Y )
{
	if( !m_ok ) return false;

	if( !(m_pool == DIS_POOL_SYSTEMMEM) ) return false;

	if( (X >= 0) && (X < m_width) && 
		(Y >= 0) && (Y < m_height) )
	{
		return m_data + Y*m_width + X;
	}

	return 0;
}

//============================================================
// Cube Map Image Surface Resource
//============================================================

CubeImageSurface::CubeImageSurface() : BaseSurface()
{
	for( int i = 0; i < 6; i++ )
	{			
		m_faces[i] = 0;	
	}
	m_pool = DIS_POOL_SYSTEMMEM;
	m_resourceType = DIS_RTYPE_CUBETEXTURE;
}

CubeImageSurface::~CubeImageSurface()
{
	Destroy();
}

void CubeImageSurface::Destroy()
{
	for( int i = 0; i < 6; i++ )
	{
		if( m_faces[i] )
		{
			delete m_faces[i];
			m_faces[i] = 0;
			m_ok = false;
		}
	}
}

bool CubeImageSurface::Create( int width, int height, int format )
{
	for( int i = 0; i < 6; i++ )
	{
		m_faces[i] = new ImageSurface();
		
		if( !m_faces[i]->Create(width, height, format))
		{
			m_ok=false;
			return false;
		}
	}
	m_ok = true;
}

bool CubeImageSurface::GetSurfaceDescription( DIS_CUBE_SURFACE_DESC *desc )
{
	if( !m_ok ) return false;

	for( int i = 0; i < 6; i++ )
	{
		if( !m_faces[i] || (m_faces[i] && !m_faces[i]->IsOk()) )
		{
			return false;
		}
	}

	desc->m_bitsPerPixel	= m_faces[0]->GetPixelSizeBPP();
	desc->m_width			= m_faces[0]->GetWidth();
	desc->m_height			= m_faces[0]->GetHeight();
	desc->m_pool			= m_faces[0]->GetPool();
	desc->m_totalSize		= m_faces[0]->GetTotalSize();
	desc->m_resourceType	= m_faces[0]->GetResourceType();
	desc->m_format			= m_faces[0]->GetFormat();

	return true;
}

ImageSurface* CubeImageSurface::GetFace(int i)
{
	if( !m_ok ) return 0;

	if( !(m_pool == DIS_POOL_SYSTEMMEM) ) return 0;

	if( (i < 0) || (i > 5) ) return 0;

	return m_faces[i];
}

//============================================================
// Image Volume resource
//============================================================

ImageVolume::ImageVolume() : BaseSurface()
{
	m_data = 0;
	m_width = 0;
	m_height = 0;
	m_depth = 0;
	m_bitsPerPixel = 0;
	m_totalSize = 0;
	m_pool = DIS_POOL_SYSTEMMEM;
	m_resourceType = DIS_RTYPE_VOLUMETEXTURE;
}

ImageVolume::~ImageVolume()
{
	Destroy();
}


bool ImageVolume::Create( int width, int height, int depth, int format )
{
	m_format = format;
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_bitsPerPixel = BppFromFormat(format);
		
	if( m_bitsPerPixel == 0 )
	{
		m_format = 0;
		m_width = 0;
		m_height = 0;
		m_depth = 0;
		m_bitsPerPixel = 0;
		return false;
	}

	m_totalSize = m_width * m_height * m_depth * m_bitsPerPixel/8;

	m_data = (unsigned char*)malloc(m_totalSize);

	if( sizeof(m_data) == m_totalSize )
	{
		m_ok = true;
		return true;
	}

	return false;
}

void ImageVolume::Destroy()
{
	if( m_data )
	{
		delete [] m_data;
		m_data = 0;
		m_ok = false;
		m_totalSize = 0;
		m_bitsPerPixel = 0;
		m_width = 0;
		m_height = 0;
		m_depth = 0;
	}
}

bool ImageVolume::GetSurfaceDescription( DIS_IMAGE_VOLUME_DESC *desc )
{
	if( !m_ok ) return false;

	desc->m_bitsPerPixel	= m_bitsPerPixel;
	desc->m_width			= m_width;
	desc->m_height			= m_height;
	desc->m_depth			= m_depth;
	desc->m_pool			= m_pool;
	desc->m_totalSize		= m_totalSize;
	desc->m_resourceType	= m_resourceType;
	desc->m_format			= m_format;

	return true;
}

void* ImageVolume::GetPixelPtr( int X, int Y, int Z )
{
	if( !m_ok ) return false;

	if( !(m_pool == DIS_POOL_SYSTEMMEM)) return false;

	if( (X >= 0) && (X < m_width) && 
		(Y >= 0) && (Y < m_height) &&
		(Z >= 0) && (Z < m_depth) )
	{
		return m_data + (Z*m_depth + Y)*m_width + X;
	}

	return 0;
}

