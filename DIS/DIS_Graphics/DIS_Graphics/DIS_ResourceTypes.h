#ifndef DIS_RESOURCE_TYPES_H
#define DIS_RESOURCE_TYPES_H

#include "DIS_RenderStates.h"

class DIS_Resource;

class DIS_ResourceManager
{
public:

	DIS_ResourceManager(){}
	~DIS_ResourceManager(){}

	virtual void AddResource(DIS_Resource *resource)=0;

	virtual void ReleaseResource(int resID)=0;
};

class DIS_Resource
{
public:

	virtual void Release()=0;

//private:
	void SetResourceManager(DIS_ResourceManager *resourceManager)
	{
		m_resourceManager = resourceManager;
		m_resourceManager->AddResource(this);
	}
	
	void SetId( int resID )
	{
		// All resources have a unique ID
		id = resID;
	}

	void ReleaseMe()
	{
		// All resources should remove themselves from
		// the resource manager when called to by the user
		m_resourceManager->ReleaseResource(id);
	}

	DIS_ResourceManager *m_resourceManager;
	int id;
};

typedef DIS_Resource* LPRESOURCE;


class ResourceBuffer : public DIS_Resource
{
public:


	virtual void* GetBufferPointer() = 0;
};
typedef ResourceBuffer* LPBUFFER;

enum RESOURCE_TEXTURE_TYPE
{
	BASE_TEXTURE_TYPE=0,
	SURFACE_TEXTURE_TYPE=1,
	TEXTURE2D_TEXTURE_TYPE=2,
	CUBE_TEXTURE_TYPE=3,
	VOLUME_TEXTURE_TYPE=4,
	FORCE_DWORD = 0xffffffff
};

class DIS_BaseTexture :  public DIS_Resource
{
public:
	int GetTextureType(){ return m_textureType;}

	int m_textureType;
};
typedef DIS_BaseTexture *LPBASETEXTURE;



class Surface2D : public DIS_BaseTexture
{
public:

};
typedef Surface2D *LPSURFACE2D;



class Texture1D : public DIS_BaseTexture
{
public:

};
typedef Texture1D *LPTEXTURE1D;



class Texture2D : public DIS_BaseTexture
{
public:

	virtual DIS_RESULT GetSurfaceLevel(
	unsigned int Level,
	LPSURFACE2D *ppSurfaceLevel) = 0;

	virtual DIS_RESULT LockRect(
						UInt32 Level,
						DIS_LOCKED_RECT *pLockedRect,
						const DIS_Rect *pRect,
						Int32 Flags
						)=0;

	virtual DIS_RESULT UnlockRect(
						UInt32 Level
						)=0;

};
typedef Texture2D *LPTEXTURE2D;




class CubeTexture2D : public DIS_BaseTexture
{
public:
};
typedef CubeTexture2D *LPCUBETEXTURE2D;




class VolumeTexture : public DIS_BaseTexture
{
public:

	virtual DIS_RESULT LockBox(
					UInt32 Level,
					DIS_LOCKED_BOX *pLockedVolume,
					const DIS_BOX *pBox,
					UInt32 Flags
					)=0;

	virtual DIS_RESULT UnlockBox(
						UInt32 Level
						)=0;

};
typedef VolumeTexture *LPVOLUMETEXTURE;





class _VertexBuffer :  public DIS_Resource
{
public:

	virtual DIS_RESULT Lock(
					UInt32 OffsetToLock,
					UInt32 SizeToLock,
					void **ppbData,
					UInt32 Flags
					)=0;

	virtual DIS_RESULT Unlock()=0;
};
typedef _VertexBuffer *LPVERTEXBUFFER;




class _IndexBuffer :  public DIS_Resource
{
public:

	virtual DIS_RESULT Lock(
					UInt32 OffsetToLock,
					UInt32 SizeToLock,
					void **ppbData,
					UInt32 Flags
					)=0;

	virtual DIS_RESULT Unlock()=0;
};
typedef _IndexBuffer *LPINDEXBUFFER;


class BaseShader : public DIS_Resource
{
public:
	virtual DIS_RESULT GetFunction(
		void *pData,
		UInt32 *pSizeOfData) = 0;
};

class VertexShader :  public BaseShader
{
public:


};
typedef VertexShader* LPVERTEXSHADER;




class PixelShader :  public BaseShader
{
public:

};
typedef PixelShader* LPPIXELSHADER;




class Query :  public DIS_Resource
{
public:
};
typedef Query *LPQUERY;




class StateBlock :  public DIS_Resource
{
public:
};
typedef StateBlock *LPSTATEBLOCK;




class VertexDecleration :  public DIS_Resource
{
public:
};
typedef VertexDecleration *LPVERTEXDECLERATION;




class SwapChain :  public DIS_Resource
{
public:
};
typedef SwapChain *LPSWAPCHAIN;






DIS_ResourceManager* CreateResourceManager( DIS_ResourceManager* resourceManager );

#endif