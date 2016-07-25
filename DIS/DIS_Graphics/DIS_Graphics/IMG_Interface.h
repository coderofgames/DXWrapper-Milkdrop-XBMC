#ifndef IMG_INTERFACE_H
#define IMG_INTERFACE_H

#include <stdlib.h>


#define GET_ACCESSOR(propName, propType) propType get##propName() const { return  (propType)##propName; }
#define SET_ACCESSOR(propName, propType) void set##propName(const propType &newVal) { ##propName = newVal; }
#define GET_SET_ACCESSOR(propName, propType) propType propName;GET_ACCESSOR(propName, propType) SET_ACCESSOR(propName,propType)

class VIS_Image
{
public:

	VIS_Image()
	{
		m_bAllocated = false;
		m_bOk = true;
	}

	int GetFormatSizeInBytes( int format )
	{
		return 4;
	}
	bool CreateImage( int width, int height, int format )
	{
		m_width = width;
		m_height = height;
		m_format = format;

		m_pixelSizeInBytes = this->GetFormatSizeInBytes(format);
		m_dataSize = width * height * m_pixelSizeInBytes;

		return Allocate(m_dataSize);
	}
	bool Allocate(int size)
	{
		data = malloc(size);
		if( data )
		{
			m_bOk = true;
			m_bAllocated = true;
		}
		else
		{
			m_bOk = false;
			m_bAllocated = false;
		}

		return m_bOk;
	}

	void Release()
	{
		free(data);
		m_bAllocated = false;
		m_bOk = false;
	}

	//GET_SET_ACCESSOR(m_width, int);


	GET_ACCESSOR( m_width, int );
	GET_ACCESSOR( m_height, int );
	GET_ACCESSOR( m_format, int );
	GET_ACCESSOR( m_pixelSizeInBytes, int );
	GET_ACCESSOR( m_dataSize, int );

	
	int m_width;
	int m_height;
	int m_format;
	int m_pixelSizeInBytes;
	int m_dataSize;
	bool m_bOk;
	bool m_bAllocated;

	

	void* data;
};

template <class T>
void PutPixel( VIS_Image *img, int X, int Y, T data )
{
}

#endif