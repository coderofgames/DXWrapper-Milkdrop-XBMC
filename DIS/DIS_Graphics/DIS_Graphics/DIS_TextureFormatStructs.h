#include "DIS_RenderStates.h"


class BaseTexture
{
public:
	BaseTexture()
	{
	}
	~BaseTexture()
	{
	}
};

template <class T> 
class BaseTexture2D : public BaseTexture
{
public:

	BaseTexture2D() 
	{
		m_width = m_height = m_sizeInBytes = 0;
		m_data = 0;
		m_ok = false;
	}

	~BaseTexture2D()
	{
		Delete();
	}

	void Delete()
	{
		if( m_data )
		{
			delete m_data;
			m_data = NULL;
			m_width = m_height = m_sizeInBytes = 0;
			m_ok = false;
		}
	}

	bool Create(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_sizeInBytes = m_width * m_height * sizeof(T);

		m_data = new T[ m_width * m_height ];

		if( !m_data )
		{
			m_width = m_height = m_sizeInBytes = 0;
			m_ok = false;
			return false;
		}
		
		m_ok = true;

		return true;
	}

	bool SetPixel( T &pixel, int X, int Y )
	{
		if( !m_ok ) return false;

		if( (X < 0) || (X >= m_width) ) return false;

		if( (Y < 0) || (Y >= m_height) ) return false;

		m_data[ Y*m_width + X ] = pixel;

		return true;
	}

	const T* GetPixel( int X, int Y )
	{
		if( !m_ok ) return 0;

		if( (X < 0) || (X >= m_width) ) return 0;

		if( (Y < 0) || (Y >= m_height) ) return 0;

		return (const T*)&m_data[ Y*m_width + X ];
	}

	T* GetDataPtr() { return m_data; }
	bool IsOk() { return m_ok; }
	int GetPitch() { return m_sizeInBytes * m_width; }
	int GetSizeInBytes() { return m_sizeInBytes; }
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }

	bool m_ok;
	int m_width;
	int m_height;
	int m_sizeInBytes;

	T* m_data;
};
#define DECLARE_TEXTURE_TYPE_2D(a)	class Texture_##a##_2D : public BaseTexture2D<a>								\
								{														\
								public:													\
									Texture_##a##_2D() : BaseTexture2D<a>(){}					\
									~Texture_##a##_2D(){}												\
								};		


template <class T> 
class BaseTexture3D : public BaseTexture
{
public:

	BaseTexture3D() 
	{
		m_width = m_height = m_depth = m_sizeInBytes = 0;
		m_data = 0;
		m_ok = false;
	}

	~BaseTexture3D()
	{
		Delete();
	}

	void Delete()
	{
		if( m_data )
		{
			delete m_data;
			m_data = NULL;
			m_width = m_height = m_depth = m_sizeInBytes = 0;
			m_ok = false;
		}
	}

	bool Create(int width, int height, int depth)
	{
		m_width = width;
		m_height = height;
		m_depth = depth;
		m_sizeInBytes = m_width * m_height * m_depth * sizeof(T);

		m_data = new T[ m_width * m_height * m_depth ];

		if( !m_data )
		{
			m_width = m_height = m_depth = m_sizeInBytes = 0;
			m_ok = false;
			return false;
		}
		
		m_ok = true;

		return true;
	}

	bool SetPixel( T &pixel, int X, int Y, int Z )
	{
		if( !m_ok ) return false;

		if( (X < 0) || (X >= m_width) ) return false;

		if( (Y < 0) || (Y >= m_height) ) return false;

		if( (Z < 0) || (Z >= m_depth) ) return false;

		m_data[ (Z* m_depth + Y)*m_width + X ] = pixel;

		return true;
	}

	const T* GetPixel( int X, int Y, int Z )
	{
		if( !m_ok ) return 0;

		if( (X < 0) || (X >= m_width) ) return 0;

		if( (Y < 0) || (Y >= m_height) ) return 0;

		if( (Z < 0) || (Z >= m_depth) ) return 0;

		return (const T*)&m_data[ (Z* m_depth + Y)*m_width + X ];
	}

	T* GetDataPtr() { return m_data; }
	bool IsOk() { return m_ok; }
	int GetPitch() { return m_sizeInBytes * m_width; }
	int GetSizeInBytes() { return m_sizeInBytes; }
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	int GetDepth() { return m_depth; }

	bool m_ok;
	int m_width;
	int m_height;
	int m_depth;
	int m_sizeInBytes;

	T* m_data;
};

#define DECLARE_TEXTURE_TYPE_3D(a)	class Texture_##a##_3D : public BaseTexture3D<a>								\
								{														\
								public:													\
									Texture_##a##_3D() : BaseTexture3D<a>(){}					\
									~Texture_##a##_3D(){}												\
								};










//class BaseSurface
//typedef enum _DIS_FORMAT {
//    DIS_FMT_UNKNOWN              ,//  0,
//
//    DIS_FMT_R8G8B8               ,// 20,
	struct sFMT_R8G8B8
	{
		Byte r;
		Byte g;
		Byte b;
	};

	DECLARE_TEXTURE_TYPE_2D(sFMT_R8G8B8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_R8G8B8)	

	/*class Texture_R8G8B8_2D : public BaseTexture2D<sFMT_R8G8B8>
	{
	public:
		Texture_R8G8B8_2D() : BaseTexture2D<sFMT_R8G8B8>()
		{
		}

		~Texture_R8G8B8_2D(){}

	};*/
//
//
//    DIS_FMT_A8R8G8B8             ,// 21,
	struct sFMT_A8R8G8B8
	{
		Byte a;
		Byte r;
		Byte g;
		Byte b;
	};

	DECLARE_TEXTURE_TYPE_2D(sFMT_A8R8G8B8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A8R8G8B8)
	/*
	class Texture_A8R8G8B8_2D : public BaseTexture2D<sFMT_A8R8G8B8>
	{
	public:
		Texture_A8R8G8B8_2D() : BaseTexture2D<sFMT_A8R8G8B8>()
		{
		}

		~Texture_A8R8G8B8_2D(){}

	};*/
//    DIS_FMT_X8R8G8B8             ,// 22,
	struct sFMT_X8R8G8B8
	{
		Byte x;
		Byte r;
		Byte g;
		Byte b;
	};

	DECLARE_TEXTURE_TYPE_2D(sFMT_X8R8G8B8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_X8R8G8B8)
	/*
	class Texture_X8R8G8B8_2D : public BaseTexture2D<sFMT_X8R8G8B8>
	{
	public:
		Texture_X8R8G8B8_2D() : BaseTexture2D<sFMT_X8R8G8B8>()
		{
		}

		~Texture_X8R8G8B8_2D(){}

	};*/
//    DIS_FMT_R5G6B5               ,// 23,
	struct sFMT_R5G6B5
	{
		Byte r : 5;
		Byte g : 5;
		Byte b : 5;
	};

	DECLARE_TEXTURE_TYPE_2D(sFMT_R5G6B5)

	DECLARE_TEXTURE_TYPE_3D(sFMT_R5G6B5)
	
	/*class Texture_R5G6B5_2D : public BaseTexture2D<sFMT_R5G6B5>
	{
	public:
		Texture_R5G6B5_2D() : BaseTexture2D<sFMT_R5G6B5>()
		{
		}

		~Texture_R5G6B5_2D(){}

	};*/
//    DIS_FMT_X1R5G5B5             ,// 24,
	struct sFMT_X1R5G5B5
	{
		Byte x : 1;
		Byte r : 5;
		Byte g : 5;
		Byte b : 5;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_X1R5G5B5)

	DECLARE_TEXTURE_TYPE_3D(sFMT_X1R5G5B5)
	/*
	class Texture_X1R5G5B5_2D : public BaseTexture2D<sFMT_X1R5G5B5>
	{
	public:
		Texture_X1R5G5B5_2D() : BaseTexture2D<sFMT_X1R5G5B5>()
		{
		}

		~Texture_X1R5G5B5_2D(){}

	};*/
//    DIS_FMT_A1R5G5B5             ,// 25,
	struct sFMT_A1R5G5B5
	{
		Byte a : 1;
		Byte r : 5;
		Byte g : 5;
		Byte b : 5;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A1R5G5B5)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A1R5G5B5)
	/*class Texture_A1R5G5B5_2D : public BaseTexture2D<sFMT_A1R5G5B5>
	{
	public:
		Texture_A1R5G5B5_2D() : BaseTexture2D<sFMT_A1R5G5B5>()
		{
		}

		~Texture_A1R5G5B5_2D(){}

	};*/
//    DIS_FMT_A4R4G4B4             ,// 26,
	struct sFMT_A4R4G4B4
	{
		Byte a : 4;
		Byte r : 4;
		Byte g : 4;
		Byte b : 4;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A4R4G4B4)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A4R4G4B4)
	/*class Texture_A4R4G4B4_2D : public BaseTexture2D<sFMT_A4R4G4B4>
	{
	public:
		Texture_A4R4G4B4_2D() : BaseTexture2D<sFMT_A4R4G4B4>()
		{
		}

		~Texture_A4R4G4B4_2D(){}

	};*/
//    DIS_FMT_R3G3B2               ,// 27,
	struct sFMT_R3G3B2
	{
		Byte r : 3;
		Byte g : 3;
		Byte b : 2;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_R3G3B2)

	DECLARE_TEXTURE_TYPE_3D(sFMT_R3G3B2)
	/*class Texture_R3G3B2_2D : public BaseTexture2D<sFMT_R3G3B2>
	{
	public:
		Texture_R3G3B2_2D() : BaseTexture2D<sFMT_R3G3B2>()
		{
		}

		~Texture_R3G3B2_2D(){}

	};*/
//    DIS_FMT_A8                   ,// 28,
	struct sFMT_A8
	{
		Byte a;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A8)
	/*class Texture_A8_2D : public BaseTexture2D<sFMT_A8>
	{
	public:
		Texture_A8_2D() : BaseTexture2D<sFMT_A8>()
		{
		}

		~Texture_A8_2D(){}

	};*/
//    DIS_FMT_A8R3G3B2             ,// 29,
	struct sFMT_A8R3G3B2 
	{
		Byte a;
		Byte r : 3;
		Byte g : 3;
		Byte b : 2;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A8R3G3B2)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A8R3G3B2)
	/*class Texture_A8R3G3B2_2D : public BaseTexture2D<sFMT_A8R3G3B2>
	{
	public:
		Texture_A8R3G3B2_2D() : BaseTexture2D<sFMT_A8R3G3B2>()
		{
		}

		~Texture_A8R3G3B2_2D(){}

	};*/
//    DIS_FMT_X4R4G4B4             ,// 30,
	struct sFMT_X4R4G4B4  
	{
		Byte x : 4;
		Byte r : 4;
		Byte g : 4;
		Byte b : 4;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_X4R4G4B4)

	DECLARE_TEXTURE_TYPE_3D(sFMT_X4R4G4B4)
	/*class Texture_X4R4G4B4_2D : public BaseTexture2D<sFMT_X4R4G4B4>
	{
	public:
		Texture_X4R4G4B4_2D() : BaseTexture2D<sFMT_X4R4G4B4>()
		{
		}

		~Texture_X4R4G4B4_2D(){}

	};*/
//    DIS_FMT_A2B10G10R10          ,// 31,
	struct sFMT_A2B10G10R10 
	{
		Byte a : 2;
		UInt16 b : 10;
		UInt16 g : 10;
		UInt16 r : 10;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A2B10G10R10)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A2B10G10R10)
	/*class Texture_A2B10G10R10_2D : public BaseTexture2D<sFMT_A2B10G10R10>
	{
	public:
		Texture_A2B10G10R10_2D() : BaseTexture2D<sFMT_A2B10G10R10>()
		{
		}

		~Texture_A2B10G10R10_2D(){}

	};*/
//    DIS_FMT_A8B8G8R8             ,// 32,
	struct sFMT_A8B8G8R8 
	{
		Byte a ;
		Byte b ;
		Byte g ;
		Byte r ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A8B8G8R8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A8B8G8R8)
	/*class Texture_A8B8G8R8_2D : public BaseTexture2D<sFMT_A8B8G8R8>
	{
	public:
		Texture_A8B8G8R8_2D() : BaseTexture2D<sFMT_A8B8G8R8>()
		{
		}

		~Texture_A8B8G8R8_2D(){}

	};*/
//    DIS_FMT_X8B8G8R8             ,// 33,
	struct sFMT_X8B8G8R8 
	{
		Byte x ;
		Byte b ;
		Byte g ;
		Byte r ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_X8B8G8R8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_X8B8G8R8)
	/*class Texture_X8B8G8R8_2D : public BaseTexture2D<sFMT_X8B8G8R8>
	{
	public:
		Texture_X8B8G8R8_2D() : BaseTexture2D<sFMT_X8B8G8R8>()
		{
		}

		~Texture_X8B8G8R8_2D(){}

	};*/
//    DIS_FMT_G16R16               ,// 34,
	struct sFMT_G16R16 
	{
		UInt16 g ;
		UInt16 r ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_G16R16)

	DECLARE_TEXTURE_TYPE_3D(sFMT_G16R16)
	/*class Texture_G16R16_2D : public BaseTexture2D<sFMT_G16R16>
	{
	public:
		Texture_G16R16_2D() : BaseTexture2D<sFMT_G16R16>()
		{
		}

		~Texture_G16R16_2D(){}

	};*/
//    DIS_FMT_A2R10G10B10          ,// 35,
	struct sFMT_A2R10G10B10  
	{
		Byte a : 2;
		UInt16 r : 10;
		UInt16 g : 10;
		UInt16 b : 10;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A2R10G10B10)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A2R10G10B10)
	/*class Texture_A2R10G10B10_2D : public BaseTexture2D<sFMT_A2R10G10B10>
	{
	public:
		Texture_A2R10G10B10_2D() : BaseTexture2D<sFMT_A2R10G10B10>()
		{
		}

		~Texture_A2R10G10B10_2D(){}

	};*/
//    DIS_FMT_A16B16G16R16         ,// 36,
	struct sFMT_A16B16G16R16   
	{
		UInt16 a;
		UInt16 b;
		UInt16 g;
		UInt16 r;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A16B16G16R16)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A16B16G16R16)
	/*class Texture_A16B16G16R16_2D : public BaseTexture2D<sFMT_A16B16G16R16>
	{
	public:
		Texture_A16B16G16R16_2D() : BaseTexture2D<sFMT_A16B16G16R16>()
		{
		}

		~Texture_A16B16G16R16_2D(){}

	};*/
//
//    DIS_FMT_A8P8                 ,// 40,
	struct sFMT_A8P8  
	{
		Byte a;
		Byte p;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A8P8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A8P8)

//    DIS_FMT_P8                   ,// 41,
	struct sFMT_P8  
	{
		Byte p;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_P8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_P8)
//
//    DIS_FMT_L8                   ,// 50,
	struct sFMT_L8  
	{
		Byte l;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_L8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_L8)
//    DIS_FMT_A8L8                 ,// 51,
	struct sFMT_A8L8 
	{
		Byte a;
		Byte l;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A8L8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A8L8)
//    DIS_FMT_A4L4                 ,// 52,
	struct sFMT_A4L4 
	{
		Byte a : 4;
		Byte l : 4;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A4L4)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A4L4)
//
//    DIS_FMT_V8U8                 ,// 60,
	struct sFMT_V8U8 
	{
		Byte v ;
		Byte u ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_V8U8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_V8U8)
//    DIS_FMT_L6V5U5               ,// 61,
	struct sFMT_L6V5U5 
	{
		Byte l : 6;
		Byte v : 5;
		Byte u : 5;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_L6V5U5)

	DECLARE_TEXTURE_TYPE_3D(sFMT_L6V5U5)
//    DIS_FMT_X8L8V8U8             ,// 62,
	struct sFMT_X8L8V8U8  
	{
		Byte x;
		Byte l ;
		Byte v ;
		Byte u ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_X8L8V8U8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_X8L8V8U8)
//    DIS_FMT_Q8W8V8U8             ,// 63,
	struct sFMT_Q8W8V8U8  
	{
		Byte q;
		Byte w ;
		Byte v ;
		Byte u ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_Q8W8V8U8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_Q8W8V8U8)
//    DIS_FMT_V16U16               ,// 64,
	struct sFMT_V16U16  
	{
		UInt16 v ;
		UInt16 u ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_V16U16)

	DECLARE_TEXTURE_TYPE_3D(sFMT_V16U16)
//    DIS_FMT_A2W10V10U10          ,// 67,
	struct sFMT_A2W10V10U10 
	{
		Byte   a : 2;
		UInt16 w : 10;
		UInt16 v : 10;
		UInt16 u : 10;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A2W10V10U10)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A2W10V10U10)
//
//    DIS_FMT_UYVY                 ,// MAKEFOURCC('U', 'Y', 'V', 'Y'),
//    DIS_FMT_R8G8_B8G8            ,// MAKEFOURCC('R', 'G', 'B', 'G'),
	struct sFMT_R8G8_B8G8 
	{
		Byte r ;
		Byte g1 ;
		Byte b ;
		Byte g2 ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_R8G8_B8G8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_R8G8_B8G8)
//    DIS_FMT_YUY2                 ,// MAKEFOURCC('Y', 'U', 'Y', '2'),
//    DIS_FMT_G8R8_G8B8            ,// MAKEFOURCC('G', 'R', 'G', 'B'),
	struct sFMT_G8R8_G8B8 
	{
		Byte g1 ;
		Byte r ;
		Byte g2 ;
		Byte b ;
	};

	DECLARE_TEXTURE_TYPE_2D(sFMT_G8R8_G8B8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_G8R8_G8B8)
//    DIS_FMT_DXT1                 ,// MAKEFOURCC('D', 'X', 'T', '1'),
//    DIS_FMT_DXT2                 ,// MAKEFOURCC('D', 'X', 'T', '2'),
//    DIS_FMT_DXT3                 ,// MAKEFOURCC('D', 'X', 'T', '3'),
//    DIS_FMT_DXT4                 ,// MAKEFOURCC('D', 'X', 'T', '4'),
//    DIS_FMT_DXT5                 ,// MAKEFOURCC('D', 'X', 'T', '5'),
//
//    DIS_FMT_D16_LOCKABLE         ,// 70,
	struct sFMT_D16_LOCKABLE 
	{
		UInt16 d ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D16_LOCKABLE)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D16_LOCKABLE)
//    DIS_FMT_D32                  ,// 71,
	struct sFMT_D32 
	{
		UInt32 d ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D32)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D32)
//    DIS_FMT_D15S1                ,// 73,
	struct sFMT_D15S1 
	{
		UInt16 d : 15 ;
		Byte   s : 1;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D15S1)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D15S1)
//    DIS_FMT_D24S8                ,// 75,
	struct sFMT_D24S8 
	{
		UInt32 d : 24 ;
		Byte   s;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D24S8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D24S8)
//    DIS_FMT_D24X8                ,// 77,
	struct sFMT_D24X8 
	{
		UInt32 d : 24 ;
		Byte   x;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D24X8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D24X8)
//    DIS_FMT_D24X4S4              ,// 79,
	struct sFMT_D24X4S4 
	{
		UInt32 d : 24 ;
		Byte   x : 4;
		Byte   s : 4;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D24X4S4)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D24X4S4)
//    DIS_FMT_D16                  ,// 80,
	struct sFMT_D16 
	{
		UInt16 d  ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D16)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D16)
//
//    DIS_FMT_D32F_LOCKABLE        ,// 82,
	struct sFMT_D32F_LOCKABLE  
	{
		Float d  ;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D32F_LOCKABLE)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D32F_LOCKABLE)
//    DIS_FMT_D24FS8               ,// 83,
	struct sFMT_D24FS8 
	{
		UInt32 d :24 ;
		Byte s;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_D24FS8)

	DECLARE_TEXTURE_TYPE_3D(sFMT_D24FS8)
//
//
//
//    DIS_FMT_L16                  ,// 81,
	struct sFMT_L16 
	{
		UInt16 l  ;

	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_L16)

	DECLARE_TEXTURE_TYPE_3D(sFMT_L16)
//
//    DIS_FMT_VERTEXDATA           ,//100,
//    DIS_FMT_INDEX16              ,//101,
	struct sFMT_INDEX16 
	{
		UInt16 Idx  ;

	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_INDEX16)

	DECLARE_TEXTURE_TYPE_3D(sFMT_INDEX16)
//    DIS_FMT_INDEX32              ,//102,
	struct sFMT_INDEX32 
	{
		UInt32 Idx  ;

	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_INDEX32)

	DECLARE_TEXTURE_TYPE_3D(sFMT_INDEX32)
//
//    DIS_FMT_Q16W16V16U16         ,//110,
	struct sFMT_Q16W16V16U16 
	{
		UInt16 q,w,v,u  ;

	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_Q16W16V16U16)

	DECLARE_TEXTURE_TYPE_3D(sFMT_Q16W16V16U16)
//
//    DIS_FMT_MULTI2_ARGB8         ,// MAKEFOURCC('M','E','T','1'),
//

//    DIS_FMT_R16F                 ,// 111,
	struct sFMT_R16F
	{
		Float r;

	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_R16F)

	DECLARE_TEXTURE_TYPE_3D(sFMT_R16F)
//    DIS_FMT_G16R16F              ,// 112,
	struct sFMT_G16R16F
	{
		UInt16 g;
		UInt16 r;

	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_G16R16F)

	DECLARE_TEXTURE_TYPE_3D(sFMT_G16R16F)
//    DIS_FMT_A16B16G16R16F        ,// 113,
	struct sFMT_A16B16G16R16F
	{
		UInt16 a;
		UInt16 b;
		UInt16 g;
		UInt16 r;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A16B16G16R16F)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A16B16G16R16F)
//
//    DIS_FMT_R32F                 ,// 114,
	struct sFMT_R32F 
	{
		Float r;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_R32F)
//    DIS_FMT_G32R32F              ,// 115,
	struct sFMT_G32R32F
	{
		Float g;
		Float r;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_G32R32F)

	DECLARE_TEXTURE_TYPE_3D(sFMT_G32R32F)
//    DIS_FMT_A32B32G32R32F        ,// 116,
	struct sFMT_A32B32G32R32F 
	{
		Float a;
		Float b;
		Float g;
		Float r;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A32B32G32R32F)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A32B32G32R32F)
//
//    DIS_FMT_CxV8U8               ,// 117,
////#if !defined(DIS__DISABLE_9EX)
//    DIS_FMT_D32_LOCKABLE         ,// 84,
//    DIS_FMT_S8_LOCKABLE          ,// 85,
	struct sFMT_S8_LOCKABLE 
	{
		Byte s;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_S8_LOCKABLE)

	DECLARE_TEXTURE_TYPE_3D(sFMT_S8_LOCKABLE)
//
//    DIS_FMT_A1                   ,// 118,
	struct sFMT_A1
	{
		Byte a : 1;
	};
	DECLARE_TEXTURE_TYPE_2D(sFMT_A1)

	DECLARE_TEXTURE_TYPE_3D(sFMT_A1)
//    DIS_FMT_A2B10G10R10_XR_BIAS  ,// 119,

//    DIS_FMT_BINARYBUFFER         ,// 199,
//
//
//    DIS_FMT_FORCE_DWORD          =0x7fffffff
//} DIS_FORMAT;

