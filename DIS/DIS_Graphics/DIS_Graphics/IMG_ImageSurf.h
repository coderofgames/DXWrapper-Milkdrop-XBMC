#ifndef IMG_IMAGE_SURF_H
#define IMG_IMAGE_SURF_H

#include "DIS_RenderStates.h"
#include <math.h>

typedef struct IMG_FILE_LOAD_DESC
{
	DIS_FORMAT Format;
	UInt32 Bpp;
	UInt32 Width;
	UInt32 Height;

}IMG_FILE_LOAD_DESC;

inline
unsigned int NextPow2_fast( unsigned x ) {
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return ++x;
}

inline
unsigned int NextPow2_log( int n )
{
	return (unsigned int) pow( 2, ceil( log( float(n) ) / log( float(2) ) ) );
}

inline
unsigned int pow2_smaller(unsigned int n)
{
  unsigned int x = 1;

  while((x<<1) < n) {
    x <<= 1;
  }

  return x;
}  

inline
unsigned int pow2_bigger(unsigned int n)
{
  unsigned int x = 1;

  while(x < n) {
    x <<= 1;
  }

  return x;
}  


inline bool ispow2( unsigned int x )
{
    return ((x != 0) && !(x & (x - 1)));
}

class ImageSurf
{
public:

	ImageSurf()
	{
		m_data = 0;
		m_ok = false;
		m_width = 0;
		m_height = 0;
		m_bytesPerPixel = 0;
		m_totalSize = 0;
	}

	~ImageSurf()
	{
		Destroy();
	}

	bool Create( int width, int height, int bytesPerPixel )
	{
		m_width = width;
		m_height = height;
		m_bytesPerPixel = bytesPerPixel;
		m_totalSize = m_width*m_height*m_bytesPerPixel;

		m_data = (unsigned char*)malloc(m_totalSize);

		if( m_data )
		{
			m_ok = true;
		}
		else
		{
			m_ok = false;
		}
		
		return m_ok ;
	}

	void Destroy()
	{
		if( m_data )
		{
			delete [] m_data;
			m_data = 0;
			m_ok = false;
			m_totalSize = 0;
			m_bytesPerPixel = 0;
			m_width = 0;
			m_height = 0;
		}
	}


	bool SetPixel(void *dat, int X, int Y)
	{
		if( !m_ok ) return false;

		if( (X >= 0) && (X < m_width) && 
			(Y >= 0) && (Y < m_height) )
		{
			if( sizeof(dat) == m_bytesPerPixel )
			{
				memcpy( (m_data + Y*m_width + X), dat, m_bytesPerPixel);
				return true;
			}
			return false;
		}
		
		return false;
	}

	void* GetPixelPtr( int X, int Y )
	{
		if( !m_ok ) return false;

		if( (X >= 0) && (X < m_width) && 
			(Y >= 0) && (Y < m_height) )
		{
			return m_data + Y*m_width + X;
		}

		return 0;
	}

	bool GetPixel(void* out, int X, int Y)
	{
		if( !m_ok ) return false;

		if( (X >= 0) && (X < m_width) && 
			(Y >= 0) && (Y < m_height) )
		{
			if( sizeof(out) == m_bytesPerPixel )
			{
				memcpy(out, m_data + Y*m_width + X, m_bytesPerPixel);
				return true;
			}
			return false;
		}
		return false;
	}

	bool	IsOK()				{ return m_ok; }
	void*	GetRawPtr()			{ return m_data; }
	int		GetPixelSize()		{ return m_bytesPerPixel; }
	int		GetWidth()			{ return m_width; }
	int		GetHeight()			{ return m_height; }
	int		GetTotalSize()		{ return m_totalSize; }

private:

	bool	m_ok;
	int		m_bytesPerPixel;
	int		m_width;
	int		m_height;
	int		m_totalSize;

	unsigned char *m_data;
};

#include <vector>
using std::vector;

class ImageMipMapSurface
{
public:

	ImageMipMapSurface()
	{
		m_Width = 0;
		m_Height = 0;
		m_numSurfaceLevels = 0;
		m_ok = false;
	}

	~ImageMipMapSurface()
	{
		Destroy();
	}

	void Destroy()
	{
		for( int i = 0; i < m_surfaceLevels.size(); i++ )
		{
			if( m_surfaceLevels[i] )
			{
				delete m_surfaceLevels[i];
				m_surfaceLevels[i] = NULL;
			}
		}
		m_surfaceLevels.clear();
		m_ok = false;
	}

	// assuming a power of 2 input
	bool Create( int width, int height, int bytesPerPixel, int numLevels)
	{
		if( !ispow2(width) || !ispow2(height) )
		{
			return false;
		}
		m_Width = width;
		m_Height = height;
		m_bytesPerPixel = bytesPerPixel;
		
		int currWidth = width;
		int currHeight = height;
		int totalSize = 0;
		for( int i = 0; (currWidth>1)&&(currHeight>1); i++ )
		{
			ImageSurf* pSurf = new ImageSurf();

			totalSize += currWidth*currHeight*bytesPerPixel;
			
			pSurf->Create(currWidth, currHeight, bytesPerPixel);
			this->m_surfaceLevels.push_back(pSurf);
			if( currWidth > 1 )
			{
				currWidth >>= 1;
			}
			if( currHeight > 1 )
			{
				currHeight >>= 1;
			}
		}

		m_totalSize = totalSize;

		m_ok = true;
		
		return m_ok ;
	}

	void*	GetRawPtr(unsigned int level)	
	{ 
		if( (level >= 0) && (level < m_surfaceLevels.size()) &&
			m_surfaceLevels[level] && 
			m_surfaceLevels[level]->IsOK() )
		{
			return m_surfaceLevels[level]->GetRawPtr();
		}
		
		return 0;
	}

	

	ImageSurf* GetSurfaceLevel( int level )
	{
		if( (level >= 0) && (level < m_surfaceLevels.size()) &&
			m_surfaceLevels[level] && 
			m_surfaceLevels[level]->IsOK() )
		{
			return m_surfaceLevels[level];
		}
		return 0;
	}
	

	int GetNumLevels() { return m_surfaceLevels.size(); }
	bool	IsOK()				{ return m_ok; }
	
	int		GetPixelSize()		{ return m_bytesPerPixel; }
	int		GetWidth()			{ return m_Width; }
	int		GetHeight()			{ return m_Height; }
	int		GetTotalSize()		{ return m_totalSize; }

	unsigned int				m_totalSize;
	unsigned int				m_Width;
	unsigned int				m_Height;
	unsigned int				m_numSurfaceLevels;
	unsigned int				m_bytesPerPixel;
	bool						m_ok;

	vector<ImageSurf*> m_surfaceLevels;
};
#endif