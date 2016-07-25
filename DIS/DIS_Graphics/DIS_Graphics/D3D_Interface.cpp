#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#include "DIS_RenderStates.h"
#include "D3D_Interface.h"
#include "D3D_Conversion.h"
#include "DIS_Effect.h"
#include "DIS_Mesh.h"
#include "DISX_Shader.h"

#include <d3d9.h>
#include <d3dx9.h>


// The inverse conversion object, the forward conversions are 
// handled by the D3D_DeviceInterface object (see below)
DIS_D3DConversion to_DIS;
DIS_ResourceManager *m_ResourceManager;

//----------------------------------------------------------------------------------
//	State Management Objects
//----------------------------------------------------------------------------------


class BlendState : public IRenderStateSetter
{
public:
	BlendState( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetBlendState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetBlendState(A, B);
	}
};

class RasterState : public IRenderStateSetter
{
public:
	RasterState( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState( UInt32 A, UInt32 B )
	{
		return this->m_pDevice->SetRasterizerState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetRasterizerState(A, B);
	}
};

class StencilState : public IRenderStateSetter
{
public:
	StencilState( D3D_DeviceInterface* pDevice) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetStencilState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetStencilState(A, B);
	}
};

class ValueState : public IRenderStateSetter
{
public:
	ValueState( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetValueState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetValueState(A, B);
	}
};

class FillModeState : public IRenderStateSetter
{
public:
	FillModeState ( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetFillModeState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetFillModeState(A, B);
	}
};

class ShadeModeState : public IRenderStateSetter
{
public:
	ShadeModeState  ( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetShadeModeState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetShadeModeState(A, B);
	}
};

class CompareFuncState : public IRenderStateSetter
{
public:
	CompareFuncState  ( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetCompareFuncState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetCompareFuncState(A, B);
	}
};

class FixedState : public IRenderStateSetter
{
public:
	FixedState ( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetFixedState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetFixedState(A, B);
	}
};

class FogModeState : public IRenderStateSetter
{
public:
	FogModeState ( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetFogModeState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetFogModeState(A, B);
	}
};


class PatchEdgeState : public IRenderStateSetter
{
public:
	PatchEdgeState( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetPatchEdgeState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetPatchEdgeState(A, B);
	}
};
class PatchDegreeState : public IRenderStateSetter
{
public:
	PatchDegreeState( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetPatchDegreeState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetPatchDegreeState(A, B);
	}
};

class MaterialColorSourceState : public IRenderStateSetter
{
public:
	MaterialColorSourceState( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetMaterialColorSourceState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetMaterialColorSourceState(A, B);
	}
};

class VertexBlendState : public IRenderStateSetter
{
public:
	VertexBlendState( D3D_DeviceInterface* pDevice ) : IRenderStateSetter( pDevice )
	{
	}

	DIS_RESULT SetState(UInt32 A, UInt32 B)
	{
		return this->m_pDevice->SetVertexBlendState(A, B);
	}

	DIS_RESULT GetState(UInt32 A, UInt32 *B)
	{
		return this->m_pDevice->GetVertexBlendState(A, B);
	}
};



//----------------------------------------------------------------------------------
//	Namespace specific class implementations of API objects
//----------------------------------------------------------------------------------

// Base Texture, used for pointers to texture of unspecified type
class D3D9_BaseTexture: public DIS_BaseTexture
{
public:

	D3D9_BaseTexture()
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::BASE_TEXTURE_TYPE;
	}

	D3D9_BaseTexture(LPDIRECT3DBASETEXTURE9 pTexture, 
					DIS_ResourceManager *resourceManager)
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::BASE_TEXTURE_TYPE;
		
		SetResourceManager(resourceManager);
		pBaseTexture = pTexture;
	}

	~D3D9_BaseTexture()
	{
		if(pBaseTexture) 
		{
			pBaseTexture->Release();
			pBaseTexture = NULL;
		}
	}


	void Release()
	{	
		this->ReleaseMe();
	}
	LPDIRECT3DBASETEXTURE9 pBaseTexture;
};

typedef D3D9_BaseTexture* LPBASETEXTURE_D3D9; 


// surface type, this is here for legacy reasons
class D3D9_Surface2D : public Surface2D 
{
public:
	D3D9_Surface2D() 
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::SURFACE_TEXTURE_TYPE;
		pd3dSurface = NULL;
	}
	D3D9_Surface2D(LPDIRECT3DSURFACE9 pSurface, 
					DIS_ResourceManager *resourceManager)
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::SURFACE_TEXTURE_TYPE;

		SetResourceManager(resourceManager);
		pd3dSurface = pSurface;
	}
	virtual ~D3D9_Surface2D()
	{
		if(pd3dSurface ) 
		{
			pd3dSurface ->Release();
			pd3dSurface  = NULL;
		}
	}


	virtual void Release()
	{
		ReleaseMe();
	}

	LPDIRECT3DSURFACE9 pd3dSurface;
};

typedef D3D9_Surface2D *LPSURFACE2D_D3D9; 

class InternalMemoryManager
{
public:

	virtual void Remove(DIS_Resource *res) = 0;
};


class D3D9_Surface2D_Getter : public D3D9_Surface2D
{
public:
	D3D9_Surface2D_Getter()
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::SURFACE_TEXTURE_TYPE;
		pd3dSurface = NULL;
		removalLock = false;
		m_memMan = NULL;
	}
	D3D9_Surface2D_Getter(LPDIRECT3DSURFACE9 pSurface,
		DIS_ResourceManager *resourceManager)
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::SURFACE_TEXTURE_TYPE;

		SetResourceManager(resourceManager);
		pd3dSurface = pSurface;
		m_memMan = NULL;
	}
	void Release()
	{
		if (!removalLock)
		{
			if (this->pd3dSurface)
			{
				this->pd3dSurface->Release();
				this->pd3dSurface = NULL;
			}

			if (m_memMan)
				m_memMan->Remove(this);
		}
	}

	void LockForRelease()
	{
		removalLock = true;
	}

	void unlockforRelease()
	{
		removalLock = false;
	}


	void SetMemoryManager(InternalMemoryManager *mm)
	{
		m_memMan = mm;
	}


	bool removalLock;
	InternalMemoryManager* m_memMan;
};

// Texture2D object
class D3D9_Texture2D : public Texture2D 
{
public:

	D3D9_Surface2D_Getter *m_surfaceLevelGetter;

	D3D9_Texture2D () 
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::TEXTURE2D_TEXTURE_TYPE;
		pd3dTexture = NULL;
		m_surfaceLevelGetter = NULL;

	}
	D3D9_Texture2D(LPDIRECT3DTEXTURE9 pTexture, 
					DIS_ResourceManager *resourceManager)
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::TEXTURE2D_TEXTURE_TYPE;

		SetResourceManager(resourceManager);
		pd3dTexture = pTexture;

		m_surfaceLevelGetter = new D3D9_Surface2D_Getter();
		m_surfaceLevelGetter->SetResourceManager(resourceManager);
	}
	~D3D9_Texture2D ()
	{
		if(pd3dTexture) 
		{
			pd3dTexture->Release();
			pd3dTexture  = NULL;
		}
	}

	DIS_RESULT GetSurfaceLevel(
		UINT Level,
		LPSURFACE2D *ppSurfaceLevel)
	{
		if (this->m_surfaceLevelGetter == NULL)
		{
			m_surfaceLevelGetter = new D3D9_Surface2D_Getter();
			m_surfaceLevelGetter->SetResourceManager(this->m_resourceManager);
		}

		
		HRESULT hr = this->pd3dTexture->GetSurfaceLevel(Level, &m_surfaceLevelGetter->pd3dSurface);
		if (hr == S_OK)
		{
			*ppSurfaceLevel = m_surfaceLevelGetter;
		}

		return HR_to_DR(hr);
	}

	DIS_RESULT LockRect(
						UInt32 Level,
						DIS_LOCKED_RECT *pLockedRect,
						const DIS_Rect *pRect,
						Int32 Flags
						)
	{
		if(pd3dTexture == NULL )
			return DIS_FAIL;

		D3DLOCKED_RECT d3dLockedRect;
		D3DRECT d3dRect;

		HRESULT hr; 
		Int32 d3dFlags = 0;

		if( Flags & DIS_LOCK_DISCARD )
		{
			d3dFlags |= D3DLOCK_DISCARD;
		}
		if( Flags & DIS_LOCK_NO_DIRTY_UPDATE )
		{
			d3dFlags |= D3DLOCK_NO_DIRTY_UPDATE;
		}
		if( Flags & DIS_LOCK_NOSYSLOCK )
		{
			d3dFlags |= D3DLOCK_NOSYSLOCK;
		}
		if( Flags & DIS_LOCK_READONLY)
		{
			d3dFlags |= D3DLOCK_READONLY;
		}		
		if( pRect )
		{
			d3dRect.x1 = pRect->x1;
			d3dRect.x2 = pRect->x2;
			d3dRect.y1 = pRect->y1;
			d3dRect.y2 = pRect->y2;

			hr = pd3dTexture->LockRect(
						Level,
						&d3dLockedRect,
						(const RECT*)&d3dRect,
						d3dFlags);
		}
		else
		{
			hr = pd3dTexture->LockRect(
						Level,
						&d3dLockedRect,
						0,
						d3dFlags);
		}



		pLockedRect->pBits = d3dLockedRect.pBits;
		pLockedRect->Pitch = d3dLockedRect.Pitch;

		return HR_to_DR(hr);
	}

	DIS_RESULT UnlockRect(
						UInt32 Level
						)
	{
		HRESULT hr = pd3dTexture->UnlockRect(Level);
		return HR_to_DR(hr);
	}
	
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture)
	{
		pd3dTexture = pTexture;
	}

	void Release()
	{
		ReleaseMe();
	}

	LPDIRECT3DTEXTURE9 pd3dTexture;
};

typedef D3D9_Texture2D *LPTEXTURE2D_D3D9;


// cube texture 2D object
class D3D9_CubeTexture2D : public CubeTexture2D 
{
public:
	D3D9_CubeTexture2D  () 
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::CUBE_TEXTURE_TYPE;
		pd3dCubeTexture = NULL;
	}
	D3D9_CubeTexture2D(LPDIRECT3DCUBETEXTURE9 pCubeTexture, 
					DIS_ResourceManager *resourceManager)
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::CUBE_TEXTURE_TYPE;

		SetResourceManager(resourceManager);
		pd3dCubeTexture = pCubeTexture;
	}
	~D3D9_CubeTexture2D  ()
	{
		if(pd3dCubeTexture) 
		{
			pd3dCubeTexture->Release();
			pd3dCubeTexture = NULL;
		}
	}

	void Release()
	{
		ReleaseMe();
	}

	LPDIRECT3DCUBETEXTURE9 pd3dCubeTexture;
};

typedef D3D9_CubeTexture2D *LPCUBETEXTURE2D_D3D9;


// volume texture object
class D3D9_VolumeTexture : public VolumeTexture 
{
public:
	D3D9_VolumeTexture   () 
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::VOLUME_TEXTURE_TYPE;

		pd3dVolumeTexture = NULL;
	}
	D3D9_VolumeTexture(LPDIRECT3DVOLUMETEXTURE9 pVolumeTexture, 
					DIS_ResourceManager *resourceManager)
	{
		this->m_textureType = RESOURCE_TEXTURE_TYPE::VOLUME_TEXTURE_TYPE;

		SetResourceManager(resourceManager);
		pd3dVolumeTexture = pVolumeTexture;
	}
	~D3D9_VolumeTexture   ()
	{
		if(pd3dVolumeTexture) 
		{
			pd3dVolumeTexture->Release();
			pd3dVolumeTexture = NULL;
		}
	}
	
	DIS_RESULT LockBox(
					UInt32 Level,
					DIS_LOCKED_BOX *pLockedVolume,
					const DIS_BOX *pBox,
					UInt32 Flags
					) 
	{
		D3DLOCKED_BOX d3dLockedBox;
		D3DBOX d3dBox;
		UInt32 d3dFlags = 0;
		if (Flags & DIS_LOCK_DISCARD)
		{
			d3dFlags |= D3DLOCK_DISCARD;
		}
		if (Flags & DIS_LOCK_NO_DIRTY_UPDATE)
		{
			d3dFlags |= D3DLOCK_NO_DIRTY_UPDATE;
		}
		if (Flags & DIS_LOCK_NOSYSLOCK)
		{
			d3dFlags |= D3DLOCK_NOSYSLOCK;
		}
		if (Flags & DIS_LOCK_READONLY)
		{
			d3dFlags |= D3DLOCK_READONLY;
		}
		if (pBox)
		{
			d3dBox.Back = pBox->Back;
			d3dBox.Bottom = pBox->Bottom;
			d3dBox.Front = pBox->Front;
			d3dBox.Left = pBox->Left;
			d3dBox.Right = pBox->Right;
			d3dBox.Top = pBox->Top;
			HRESULT hr = pd3dVolumeTexture->LockBox(
				Level,
				&d3dLockedBox,
				(const D3DBOX *)&d3dBox,
				d3dFlags);

			pLockedVolume->SlicePitch = d3dLockedBox.SlicePitch;
			pLockedVolume->RowPitch = d3dLockedBox.RowPitch;
			pLockedVolume->pBits = d3dLockedBox.pBits;

			return HR_to_DR(hr);
		}
		else
		{
			HRESULT hr = pd3dVolumeTexture->LockBox(
				Level,
				&d3dLockedBox,
				0,
				d3dFlags);

			pLockedVolume->SlicePitch = d3dLockedBox.SlicePitch;
			pLockedVolume->RowPitch = d3dLockedBox.RowPitch;
			pLockedVolume->pBits = d3dLockedBox.pBits;

			return HR_to_DR(hr);
		}

		return DIS_FAIL;


	}

	DIS_RESULT UnlockBox(
						UInt32 Level
						)
	{
		HRESULT hr = pd3dVolumeTexture->UnlockBox(Level);
		return HR_to_DR(hr);
	}

	void Release()
	{
		ReleaseMe();
	}

	LPDIRECT3DVOLUMETEXTURE9 pd3dVolumeTexture;
};

typedef D3D9_VolumeTexture *LPVOLUMETEXTURE_D3D9;

class D3D9_Buffer : public ResourceBuffer
{
public:
	D3D9_Buffer() : ResourceBuffer()
	{
		pd3dBuffer = NULL;
	}
	D3D9_Buffer(LPD3DXBUFFER pBuffer,
		DIS_ResourceManager *resourceManager)
	{


		SetResourceManager(resourceManager);
		pd3dBuffer = pBuffer;
	}
	~D3D9_Buffer()
	{
		if(pd3dBuffer) 
		{
			pd3dBuffer->Release();
			pd3dBuffer = NULL;
		}
	}

	void * GetBufferPointer()
	{
		if( !pd3dBuffer )
		{
			return 0;
		}

		return pd3dBuffer->GetBufferPointer();
	}
	void Release()
	{
		ReleaseMe();
	}
	LPD3DXBUFFER pd3dBuffer;
};
typedef D3D9_Buffer *LPBUFFER_D3D9;

// VertexBuffer object
class D3D9_VertexBuffer : public _VertexBuffer
{
public:

	D3D9_VertexBuffer    () 
	{
		pd3dVertexBuffer = NULL;
	}
	D3D9_VertexBuffer(LPDIRECT3DVERTEXBUFFER9 *pVertexBuffer, 
					DIS_ResourceManager *resourceManager)
	{
		SetResourceManager(resourceManager);
		pd3dVertexBuffer = *pVertexBuffer;
	}
	~D3D9_VertexBuffer    ()
	{
		if(pd3dVertexBuffer) 
		{
			pd3dVertexBuffer->Release();
			pd3dVertexBuffer = NULL;
		}
	}

	void Release()
	{
		ReleaseMe();
	}

	DIS_RESULT Lock(
			UInt32 OffsetToLock,
			UInt32 SizeToLock,
			void **ppbData,
			UInt32 Flags
			)
	{
		UInt32 d3dFlags = 0;

		if( Flags & DIS_LOCK_DISCARD )
		{
			d3dFlags |= D3DLOCK_DISCARD;
		}
		if( Flags & DIS_LOCK_NO_DIRTY_UPDATE )
		{
			d3dFlags |= D3DLOCK_NO_DIRTY_UPDATE;
		}
		if( Flags & DIS_LOCK_NOSYSLOCK )
		{
			d3dFlags |= D3DLOCK_NOSYSLOCK;
		}
		if( Flags & DIS_LOCK_READONLY )
		{
			d3dFlags |= D3DLOCK_READONLY;
		}
		if( Flags & DIS_LOCK_NOOVERWRITE)
		{
			d3dFlags |= D3DLOCK_NOOVERWRITE;
		}

		VOID* ppData = NULL;
		HRESULT hr = pd3dVertexBuffer->Lock(OffsetToLock, SizeToLock, 
			(void**)&ppData, d3dFlags);

		*ppbData = ppData;

		return HR_to_DR(hr);
	}

	DIS_RESULT Unlock()
	{
		HRESULT hr = pd3dVertexBuffer->Unlock();
		return HR_to_DR(hr);
	}


	LPDIRECT3DVERTEXBUFFER9 pd3dVertexBuffer;
};

typedef D3D9_VertexBuffer *LPVERTEXBUFFER_D3D9;



// Index buffer object
class D3D9_IndexBuffer : public _IndexBuffer
{
public:
	D3D9_IndexBuffer     () 
	{
		pd3dIndexBuffer = NULL;
	}
	D3D9_IndexBuffer(LPDIRECT3DINDEXBUFFER9 pIndexBuffer, 
					DIS_ResourceManager *resourceManager)
	{
		SetResourceManager(resourceManager);
		pd3dIndexBuffer = pIndexBuffer;
	}
	~D3D9_IndexBuffer     ()
	{
		if(pd3dIndexBuffer ) 
		{
			pd3dIndexBuffer->Release();
			pd3dIndexBuffer  = NULL;
		}
	}
	
	void Release()
	{
		ReleaseMe();
	}

	DIS_RESULT Lock(
			UInt32 OffsetToLock,
			UInt32 SizeToLock,
			void **ppbData,
			UInt32 Flags
			)
	{
		UInt32 d3dFlags = 0;

		if( Flags & DIS_LOCK_DISCARD )
		{
			d3dFlags |= D3DLOCK_DISCARD;
		}
		if( Flags & DIS_LOCK_NO_DIRTY_UPDATE )
		{
			d3dFlags |= D3DLOCK_NO_DIRTY_UPDATE;
		}
		if( Flags & DIS_LOCK_NOSYSLOCK )
		{
			d3dFlags |= D3DLOCK_NOSYSLOCK;
		}
		if( Flags & DIS_LOCK_READONLY )
		{
			d3dFlags |= D3DLOCK_READONLY;
		}
		if( Flags & DIS_LOCK_NOOVERWRITE)
		{
			d3dFlags |= D3DLOCK_NOOVERWRITE;
		}

		HRESULT hr = pd3dIndexBuffer->Lock(OffsetToLock, SizeToLock, 
											ppbData, d3dFlags);

		return HR_to_DR(hr);
	}

	DIS_RESULT Unlock()
	{
		HRESULT hr = pd3dIndexBuffer->Unlock();
		return HR_to_DR(hr);
	}

	LPDIRECT3DINDEXBUFFER9 pd3dIndexBuffer;
};

typedef D3D9_IndexBuffer *LPINDEXBUFFER_D3D9;



// Vertex Shader object
class D3D9_VertexShader : public VertexShader
{
public:
	D3D9_VertexShader     () 
	{
		pd3dVertexShader = NULL;
	}
	D3D9_VertexShader(LPDIRECT3DVERTEXSHADER9 pVertexShader, 
					DIS_ResourceManager *resourceManager)
	{
		SetResourceManager(resourceManager);
		pd3dVertexShader = pVertexShader;
	}
	~D3D9_VertexShader     ()
	{
		if(pd3dVertexShader ) 
		{
			pd3dVertexShader->Release();
			pd3dVertexShader = NULL;
		}
	}

	void Release()
	{
		ReleaseMe();
	
	}

	DIS_RESULT GetFunction(
		void *pData,
		UInt32 *pSizeOfData)
	{
		if( !pd3dVertexShader )
		{
			return DIS_FAIL;
		}
		HRESULT hr = pd3dVertexShader->GetFunction(pData, pSizeOfData);
		return HR_to_DR(hr);
	}
	
	LPDIRECT3DVERTEXSHADER9 pd3dVertexShader;
};
typedef D3D9_VertexShader *LPVERTEXSHADER_D3D9;


// pixel shader object
class D3D9_PixelShader : public PixelShader
{
public:
	D3D9_PixelShader      () 
	{
		pd3dPixelShader = NULL;
	}
	D3D9_PixelShader(LPDIRECT3DPIXELSHADER9 pPixelShader, 
					DIS_ResourceManager *resourceManager)
	{
		SetResourceManager(resourceManager);
		pd3dPixelShader = pPixelShader;
	}
	~D3D9_PixelShader      ()
	{
		if(pd3dPixelShader) 
		{
			pd3dPixelShader->Release();
			pd3dPixelShader = NULL;
		}
	}

	void Release()
	{
		ReleaseMe();
	}

	DIS_RESULT GetFunction(
		void *pData,
		UInt32 *pSizeOfData)
	{
		if( !pd3dPixelShader )
		{
			return DIS_FAIL;
		}
		HRESULT hr = pd3dPixelShader->GetFunction(pData, pSizeOfData);
		return HR_to_DR(hr);
	}

	LPDIRECT3DPIXELSHADER9 pd3dPixelShader;
};

typedef D3D9_PixelShader *LPPIXELSHADER_D3D9;



// Query object
class D3D9_Query : public Query
{
public:
	D3D9_Query      () 
	{
		pd3dQuery = NULL;
	}
	D3D9_Query(LPDIRECT3DQUERY9 pQuery, 
					DIS_ResourceManager *resourceManager)
	{
		SetResourceManager(resourceManager);
		pd3dQuery = pQuery;
	}
	~D3D9_Query      ()
	{
		if(pd3dQuery) 
		{
			pd3dQuery->Release();
			pd3dQuery = NULL;
		}
	}
	void Release()
	{
		ReleaseMe();
	}
	LPDIRECT3DQUERY9 pd3dQuery;
};

typedef D3D9_Query *LPQUERY_D3D9;



// stateblock object
class D3D9_StateBlock: public StateBlock
{
public:
	D3D9_StateBlock      () 
	{
		pd3dStateBlock = NULL;
	}
	D3D9_StateBlock(LPDIRECT3DSTATEBLOCK9 pStateBlock, 
					DIS_ResourceManager *resourceManager)
	{
		SetResourceManager(resourceManager);
		pd3dStateBlock = pStateBlock;
	}
	~D3D9_StateBlock      ()
	{
		if(pd3dStateBlock ) 
		{
			pd3dStateBlock->Release();
			pd3dStateBlock  = NULL;
		}
	}
	void Release()
	{
		ReleaseMe();
	}
	LPDIRECT3DSTATEBLOCK9 pd3dStateBlock;
};

typedef D3D9_StateBlock *LPSTATEBLOCK_D3D9;


// Vertex Decleration object
class D3D9_VertexDecleration : public VertexDecleration
{
public:
	D3D9_VertexDecleration      () 
	{
		pd3dVertexDecl = NULL;
	}
	D3D9_VertexDecleration(LPDIRECT3DVERTEXDECLARATION9 pVertexDecl, 
					DIS_ResourceManager *resourceManager)
	{
		SetResourceManager(resourceManager);
		pd3dVertexDecl = pVertexDecl;
	}
	~D3D9_VertexDecleration      ()
	{
		if(pd3dVertexDecl) 
		{
			pd3dVertexDecl->Release();
			pd3dVertexDecl  = NULL;
		}
	}
	void Release()
	{
		ReleaseMe();
	}
	LPDIRECT3DVERTEXDECLARATION9 pd3dVertexDecl;
};

typedef D3D9_VertexDecleration *LPVERTEXDECLERATION_D3D9;



// swap chain object
class D3D9_SwapChain : public SwapChain
{
public:

	D3D9_SwapChain      () 
	{
		pd3dSwapChain = NULL;
	}
	D3D9_SwapChain(LPDIRECT3DSWAPCHAIN9 pSwapChain, 
					DIS_ResourceManager *resourceManager)
	{
		SetResourceManager(resourceManager);
		pd3dSwapChain = pSwapChain;
	}
	~D3D9_SwapChain      ()
	{
		if(pd3dSwapChain) 
		{
			pd3dSwapChain->Release();
			pd3dSwapChain  = NULL;
		}
	}
	void Release()
	{
		ReleaseMe();
	}
	LPDIRECT3DSWAPCHAIN9 pd3dSwapChain;
};

typedef D3D9_SwapChain *LPSWAPCHAIN_D3D9;




class D3D9DISMesh : public DISX_Mesh
{
public:

	D3D9DISMesh()
	{
		pd3dMesh = NULL;
		m_pd3dDevice = *GetDeviceD3D();

	}

	LPD3DXMESH pd3dMesh;
	LPDIRECT3DDEVICE9 m_pd3dDevice;

	D3D9_IndexBuffer m_indexBufferGetter;
	D3D9_VertexBuffer m_vertexBufferGetter;
	D3D9_Buffer		m_bufferGetter;

	DIS_RESULT CloneMesh(
			UInt32 Options,  //   [in] A combination of one or more D3DXMESH flags specifying creation options for the mesh.
			const DIS_VERTEXELEMENT *pDeclaration,//[in]     An array of D3DVERTEXELEMENT9 elements, which specify the vertex format for the vertices in the output mesh.     
			LPDEVICE pDevice,//  [in]           Pointer to an IDirect3DDevice9 interface, representing the device object associated with the mesh.
			LPDISXMESH *ppCloneMesh // [out, retval]  Address of a pointer to an ID3DXMesh interface, representing the cloned mesh.
	)
	{
		
		
		DWORD options;

		if( *ppCloneMesh == NULL )
		{
			*ppCloneMesh = new D3D9DISMesh();
		}

		if( Options & DISX_MESH_32BIT )
		{
			options |= D3DXMESH_32BIT;
		}
		if( Options & DISX_MESH_DONOTCLIP  )
		{
			options |= D3DXMESH_DONOTCLIP ;
		}
		if( Options & DISX_MESH_RTPATCHES)
		{
			options |= D3DXMESH_RTPATCHES;
		}
		if( Options & DISX_MESH_NPATCHES)
		{
			options |= D3DXMESH_NPATCHES;
		}
		if( Options & DISX_MESH_POINTS )
		{
			options |= D3DXMESH_POINTS;
		}
		if( Options & DISX_MESH_IB_DYNAMIC )
		{
			options |= D3DXMESH_IB_DYNAMIC;
		}
		if( Options & DISX_MESH_IB_MANAGED )
		{
			options |= D3DXMESH_IB_MANAGED;
		}
		if( Options & DISX_MESH_IB_WRITEONLY)
		{
			options |= D3DXMESH_IB_WRITEONLY;
		}
		if( Options & DISX_MESH_IB_SYSTEMMEM)
		{
			options |= D3DXMESH_IB_SYSTEMMEM;
		}
		if( Options & DISX_MESH_VB_DYNAMIC )
		{
			options |= D3DXMESH_VB_DYNAMIC ;
		}
		if( Options & DISX_MESH_VB_MANAGED)
		{
			options |= D3DXMESH_VB_MANAGED ;
		}

		if( Options & DISX_MESH_VB_WRITEONLY)
		{
			options |= D3DXMESH_VB_WRITEONLY ;
		}
		if( Options & DISX_MESH_VB_SYSTEMMEM)
		{
			options |= D3DXMESH_VB_SYSTEMMEM ;
		}
		D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];

		pd3dMesh->GetDeclaration( decl );

		// messy conversion due to ToD3D conversion being
		// stored in the device wrapper below
		for( int i = 0; i < MAX_FVF_DECL_SIZE; i++ )
		{
			switch( pDeclaration[i].Method )
			{
			case DIS_DECLMETHOD_DEFAULT: decl[i].Method = D3DDECLMETHOD_DEFAULT; break;
			case DIS_DECLMETHOD_PARTIALU: decl[i].Method = D3DDECLMETHOD_PARTIALU;break;
			case DIS_DECLMETHOD_PARTIALV: decl[i].Method = D3DDECLMETHOD_PARTIALV;break;
			case DIS_DECLMETHOD_CROSSUV: decl[i].Method = D3DDECLMETHOD_CROSSUV;break;
			case DIS_DECLMETHOD_UV: decl[i].Method = D3DDECLMETHOD_UV;break;
			case DIS_DECLMETHOD_LOOKUP: decl[i].Method = D3DDECLMETHOD_LOOKUP;break;
			case DIS_DECLMETHOD_LOOKUPPRESAMPLED: decl[i].Method = D3DDECLMETHOD_LOOKUPPRESAMPLED;break;
			default: decl[i].Method = D3DDECLMETHOD_DEFAULT;break;
			}
			
			
			decl[i].Offset = pDeclaration[i].Offset;
			decl[i].Stream = pDeclaration[i].Stream;
			
			switch( pDeclaration[i].Type )
			{
			case DIS_DECLTYPE_FLOAT1:    decl[i].Type = D3DDECLTYPE_FLOAT1; break;
			case DIS_DECLTYPE_FLOAT2:   decl[i].Type = D3DDECLTYPE_FLOAT2  ; break;
			case DIS_DECLTYPE_FLOAT3:   decl[i].Type = D3DDECLTYPE_FLOAT3; break;
			case DIS_DECLTYPE_FLOAT4:   decl[i].Type = D3DDECLTYPE_FLOAT4; break;
			case DIS_DECLTYPE_DIS_COLOR:   decl[i].Type = D3DDECLTYPE_D3DCOLOR; break;
			case DIS_DECLTYPE_UBYTE4:   decl[i].Type = D3DDECLTYPE_UBYTE4; break;
			case DIS_DECLTYPE_SHORT2:   decl[i].Type = D3DDECLTYPE_SHORT2; break;
			case DIS_DECLTYPE_SHORT4:   decl[i].Type = D3DDECLTYPE_SHORT4; break;
			case DIS_DECLTYPE_UBYTE4N :   decl[i].Type = D3DDECLTYPE_UBYTE4N; break;
			case DIS_DECLTYPE_SHORT2N:   decl[i].Type = D3DDECLTYPE_SHORT2N; break;
			case DIS_DECLTYPE_SHORT4N :   decl[i].Type = D3DDECLTYPE_SHORT4N; break;
			case DIS_DECLTYPE_USHORT2N :   decl[i].Type = D3DDECLTYPE_USHORT2N; break;
			case DIS_DECLTYPE_USHORT4N:   decl[i].Type = D3DDECLTYPE_USHORT4N; break;
			case DIS_DECLTYPE_UDEC3:   decl[i].Type = D3DDECLTYPE_UDEC3; break;
			case DIS_DECLTYPE_DEC3N:   decl[i].Type = D3DDECLTYPE_DEC3N; break;
			case DIS_DECLTYPE_FLOAT16_2:   decl[i].Type = D3DDECLTYPE_FLOAT16_2; break;
			case DIS_DECLTYPE_FLOAT16_4:   decl[i].Type = D3DDECLTYPE_FLOAT16_4; break;
			case  D3DDECLTYPE_UNUSED :   decl[i].Type = D3DDECLTYPE_UNUSED ; break;
			default:    decl[i].Type = DIS_DECLTYPE_FLOAT1; break;
			}
			
			switch( pDeclaration[i].Usage )
			{
			case DIS_DECLUSAGE_POSITION: decl[i].Usage= D3DDECLUSAGE_POSITION;break;
			case DIS_DECLUSAGE_BLENDWEIGHT: decl[i].Usage= D3DDECLUSAGE_BLENDWEIGHT;break;
			case DIS_DECLUSAGE_BLENDINDICES: decl[i].Usage= D3DDECLUSAGE_BLENDINDICES;break;
			case DIS_DECLUSAGE_NORMAL: decl[i].Usage= D3DDECLUSAGE_NORMAL;break;
			case DIS_DECLUSAGE_PSIZE: decl[i].Usage= D3DDECLUSAGE_PSIZE;break;
			case DIS_DECLUSAGE_TEXCOORD: decl[i].Usage= D3DDECLUSAGE_TEXCOORD;break;
			case DIS_DECLUSAGE_TANGENT: decl[i].Usage= D3DDECLUSAGE_TANGENT;break;
			case DIS_DECLUSAGE_BINORMAL: decl[i].Usage= D3DDECLUSAGE_BINORMAL;break;
			case DIS_DECLUSAGE_TESSFACTOR : decl[i].Usage= D3DDECLUSAGE_TESSFACTOR;break;
			case DIS_DECLUSAGE_POSITIONT: decl[i].Usage= D3DDECLUSAGE_POSITIONT;break;
			case DIS_DECLUSAGE_COLOR: decl[i].Usage= D3DDECLUSAGE_COLOR;break;
			case DIS_DECLUSAGE_FOG: decl[i].Usage= D3DDECLUSAGE_FOG;break;
			case DIS_DECLUSAGE_DEPTH: decl[i].Usage= D3DDECLUSAGE_DEPTH;break;
			case DIS_DECLUSAGE_SAMPLE: decl[i].Usage= D3DDECLUSAGE_SAMPLE;break;
			default: decl[i].Usage= D3DDECLUSAGE_POSITION;break;
			}

			decl[i].UsageIndex = pDeclaration[i].UsageIndex;
		}

		HRESULT hr = pd3dMesh->CloneMesh(
								options, 
								decl,
								m_pd3dDevice,
								&((D3D9DISMesh*)(*ppCloneMesh))->pd3dMesh);

		return HR_to_DR(hr);
	}

//Clones a mesh using a flexible vertex format (FVF) code.
	DIS_RESULT CloneMeshFVF(
			UInt32 Options,//  [in] A combination of one or more D3DXMESH flags specifying creation options for the mesh.
			UInt32 FVF, // [in]      Combination of FVF codes, which specifies the vertex format for the vertices in the output mesh. For the values of the codes, see D3DFVF.     
			LPDEVICE pDevice,//[in]     Pointer to an IDirect3DDevice9 interface representing the device object associated with the mesh.      
			LPDISXMESH *ppCloneMesh//[out, retval]  Address of a pointer to an ID3DXMesh interface, representing the cloned mesh.
	)
	{
		DWORD options;

		if( *ppCloneMesh == NULL )
		{
			*ppCloneMesh = new D3D9DISMesh();
		}

		if( Options & DISX_MESH_32BIT )
		{
			options |= D3DXMESH_32BIT;
		}
		if( Options & DISX_MESH_DONOTCLIP  )
		{
			options |= D3DXMESH_DONOTCLIP ;
		}
		if( Options & DISX_MESH_RTPATCHES)
		{
			options |= D3DXMESH_RTPATCHES;
		}
		if( Options & DISX_MESH_NPATCHES)
		{
			options |= D3DXMESH_NPATCHES;
		}
		if( Options & DISX_MESH_POINTS )
		{
			options |= D3DXMESH_POINTS;
		}
		if( Options & DISX_MESH_IB_DYNAMIC )
		{
			options |= D3DXMESH_IB_DYNAMIC;
		}
		if( Options & DISX_MESH_IB_MANAGED )
		{
			options |= D3DXMESH_IB_MANAGED;
		}
		if( Options & DISX_MESH_IB_WRITEONLY)
		{
			options |= D3DXMESH_IB_WRITEONLY;
		}
		if( Options & DISX_MESH_IB_SYSTEMMEM)
		{
			options |= D3DXMESH_IB_SYSTEMMEM;
		}
		if( Options & DISX_MESH_VB_DYNAMIC )
		{
			options |= D3DXMESH_VB_DYNAMIC ;
		}
		if( Options & DISX_MESH_VB_MANAGED)
		{
			options |= D3DXMESH_VB_MANAGED ;
		}

		if( Options & DISX_MESH_VB_WRITEONLY)
		{
			options |= D3DXMESH_VB_WRITEONLY ;
		}
		if( Options & DISX_MESH_VB_SYSTEMMEM)
		{
			options |= D3DXMESH_VB_SYSTEMMEM ;
		}

		HRESULT hr = pd3dMesh->CloneMeshFVF(
								Options, 
								FVF,
								m_pd3dDevice,
								&((D3D9DISMesh*)(*ppCloneMesh))->pd3dMesh);
                                                                     

		return HR_to_DR(hr);
	}
//Converts mesh adjacency information to an array of point representatives.
	DIS_RESULT ConvertAdjacencyToPointReps(
			const UInt32 *pAdjacency, //   [in] Pointer to an array of three DWORDs per face that specify the three neighbors for each face in the mesh. The number of bytes in this array must be at least 3 * ID3DXBaseMesh::GetNumFaces * sizeof(DWORD).
			UInt32 *pPRep // [in, out]  Pointer to an array of one DWORD per vertex of the mesh that will be filled with point representative data.
	)
	{
		HRESULT hr;

		hr = pd3dMesh->ConvertAdjacencyToPointReps( 
							(DWORD*)pAdjacency, 
							(DWORD*)pPRep);

		return HR_to_DR(hr);
	}


	//Converts point representative data to mesh adjacency information.
	DIS_RESULT ConvertPointRepsToAdjacency(
		const UInt32 *pPRep, //   [in]Pointer to an array of one DWORD per vertex of the mesh that contains point representative data. This parameter is optional. Supplying a NULL value will cause this parameter to be interpreted as an "identity" array.
		UInt32 *pAdjacency //  [in, out]Pointer to an array of three DWORDs per face that specify the three neighbors for each face in the mesh. The number of bytes in this array must be at least 3 * ID3DXBaseMesh::GetNumFaces * sizeof(DWORD).
	)
	{
		HRESULT hr;
		hr = pd3dMesh->ConvertPointRepsToAdjacency( 
							(DWORD*)pPRep, 
							(DWORD*)pAdjacency );
		
		return HR_to_DR(hr);
	}

	//Draws a subset of a mesh.
	DIS_RESULT DrawSubset(
		UInt32 AttribId //   [in] 
	)
	{
		HRESULT hr;
		hr = pd3dMesh->DrawSubset( (DWORD) AttribId );
		return HR_to_DR(hr);
	}

	//Generate a list of mesh edges, as well as a list of faces that share each edge.
	DIS_RESULT GenerateAdjacency(
		float Epsilon, //  [in]  Specifies that vertices that differ in position by less than epsilon should be treated as coincident.
		UInt32 *pAdjacency //   [in]  Pointer to an array of three DWORDs per face to be filled with the indices of adjacent faces. The number of bytes in this array must be at least 3 * ID3DXBaseMesh::GetNumFaces * sizeof(DWORD).
	)
	{
		HRESULT hr;
		hr = pd3dMesh->GenerateAdjacency( Epsilon, (DWORD*)pAdjacency );

		return HR_to_DR(hr);
	}

	//Retrieves either an attribute table for a mesh, or the number of entries stored in an attribute table for a mesh.
	DIS_RESULT GetAttributeTable(
		DISX_ATTRIBUTERANGE *pAttribTable,  //[in, out]  Pointer to an array of D3DXATTRIBUTERANGE structures, representing the entries in the mesh's attribute table. Specify NULL to retrieve the value for pAttribTableSize.
		UInt32 *pAttribTableSize//  [in, out]  Pointer to either the number of entries stored in pAttribTable or a value to be filled in with the number of entries stored in the attribute table for the mesh.
	)
	{
		//TODO
		HRESULT hr;

		if( pAttribTable == NULL )
		{
			hr = pd3dMesh->GetAttributeTable( 
							0, 
							(DWORD*)pAttribTableSize ); 

			return HR_to_DR(hr);
		}

		D3DXATTRIBUTERANGE attribTable[1024]; // 

		hr = pd3dMesh->GetAttributeTable( 
							attribTable, 
							(DWORD*)pAttribTableSize ); 
		
		if( *pAttribTableSize == 0 )
		{
			return DIS_FAIL;
		}

		for( int i = 0; i < *pAttribTableSize; i++ )
		{
			pAttribTable[i].AttribId = attribTable[i].AttribId;
			pAttribTable[i].FaceCount = attribTable[i].FaceCount;
			pAttribTable[i].FaceStart = attribTable[i].FaceStart;
			pAttribTable[i].VertexCount = attribTable[i].VertexCount;
			pAttribTable[i].VertexStart = attribTable[i].VertexStart;
		}

		return HR_to_DR(hr);
	}
	
	//Retrieves a declaration describing the vertices in the mesh.
	DIS_RESULT GetDeclaration(
		DIS_VERTEXELEMENT *Declaration //   [in, out]  
	)
	{
		HRESULT hr = S_OK;
		D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
		pd3dMesh->GetDeclaration( decl );
		for( int i = 0; i < MAX_FVF_DECL_SIZE; i++ )
		{
			Declaration[i].Method = (Byte)to_DIS.DeclMethod( (D3DDECLMETHOD)decl[i].Method );
			Declaration[i].Offset = decl[i].Offset;
			Declaration[i].Stream = decl[i].Stream;
			Declaration[i].Type = (Byte)to_DIS.DeclType( (D3DDECLTYPE)decl[i].Type );
			Declaration[i].Usage = to_DIS.DeclUsage( (D3DDECLUSAGE)decl[i].Usage );
			Declaration[i].UsageIndex = decl[i].UsageIndex;
		}
		return HR_to_DR(hr);
	}

	//Retrieves the device associated with the mesh.
	//GetDevice	

	//Gets the fixed function vertex value.
	UInt32 GetFVF()
	{
		return pd3dMesh->GetFVF();
	}



	//Retrieves the data in an index buffer.
	DIS_RESULT GetIndexBuffer(
		LPINDEXBUFFER *ppIB //   [out, retval]  
	)
	{
		HRESULT hr = S_OK;
		
		pd3dMesh->GetIndexBuffer( &m_indexBufferGetter.pd3dIndexBuffer );
		*ppIB = &m_indexBufferGetter;

		return HR_to_DR(hr);
	}


	//Gets the number of bytes per vertex.
	UInt32 GetNumBytesPerVertex()
	{
		return pd3dMesh->GetNumBytesPerVertex();
	}

	//Retrieves the number of faces in the mesh.
	UInt32 GetNumFaces()
	{
		return pd3dMesh->GetNumFaces();
	}
	
	//Retrieves the number of vertices in the mesh.
	UInt32 GetNumVertices()
	{
		return pd3dMesh->GetNumVertices();
	}

	//Retrieves the mesh options enabled for this mesh at creation time.
	UInt32 GetOptions()
	{
		return pd3dMesh->GetOptions();
	}

	//Retrieves the vertex buffer associated with the mesh.
	DIS_RESULT GetVertexBuffer(
		LPVERTEXBUFFER *ppVB // [out, retval]
	)
	{
		HRESULT hr = S_OK;
		pd3dMesh->GetVertexBuffer( &m_vertexBufferGetter.pd3dVertexBuffer );
		*ppVB = &m_vertexBufferGetter;
		
		return HR_to_DR(hr);
	}

	//Locks an index buffer and obtains a pointer to the index buffer memory.
	DIS_RESULT LockIndexBuffer(
		UInt32 Flags, /* [in] 
		Combination of zero or more locking flags that describe the type of lock to perform. For this method, the valid flags are:
		D3DLOCK_DISCARD
		D3DLOCK_NO_DIRTY_UPDATE
		D3DLOCK_NOSYSLOCK
		D3DLOCK_READONLY
		For a description of the flags, see D3DLOCK.*/   
		void **ppData // [out, retval]
	)
	{
		HRESULT hr;
		DWORD flags = 0;

		if( Flags & DIS_LOCK_DISCARD )
		{
			flags |= D3DLOCK_DISCARD;
		}
		if( Flags & DIS_LOCK_NO_DIRTY_UPDATE )
		{
			flags |= D3DLOCK_NO_DIRTY_UPDATE;
		}
		if( Flags & DIS_LOCK_NOSYSLOCK )
		{
			flags |= D3DLOCK_NOSYSLOCK;
		}
		if( Flags & DIS_LOCK_READONLY )
		{
			flags |= D3DLOCK_READONLY;
		}

		hr = pd3dMesh->LockIndexBuffer( flags, &(*ppData) );
		
		return HR_to_DR(hr);
	
	}

	//Locks a vertex buffer and obtains a pointer to the vertex buffer memory.
	DIS_RESULT LockVertexBuffer(
		UInt32 Flags, /*  [in]  
		Combination of zero or more locking flags that describe the type of lock to perform. For this method, the valid flags are:
		D3DLOCK_DISCARD
		D3DLOCK_NO_DIRTY_UPDATE
		D3DLOCK_NOSYSLOCK
		D3DLOCK_READONLY
		D3DLOCK_NOOVERWRITE         */
		void **ppData //   [out, retval]  
		)
	{
		HRESULT hr;
		DWORD flags = 0;

		if( Flags & DIS_LOCK_DISCARD )
		{
			flags |= D3DLOCK_DISCARD;
		}
		if( Flags & DIS_LOCK_NO_DIRTY_UPDATE )
		{
			flags |= D3DLOCK_NO_DIRTY_UPDATE;
		}
		if( Flags & DIS_LOCK_NOSYSLOCK )
		{
			flags |= D3DLOCK_NOSYSLOCK;
		}
		if( Flags & DIS_LOCK_READONLY )
		{
			flags |= D3DLOCK_READONLY;
		}

		hr = pd3dMesh->LockVertexBuffer( flags, &(*ppData) );
		return HR_to_DR(hr);
	}

	//Unlocks an index buffer.
	DIS_RESULT UnlockIndexBuffer()
	{
		HRESULT hr;
		hr = pd3dMesh->UnlockIndexBuffer();
		return HR_to_DR(hr);
	}
	
	//Unlocks a vertex buffer.
	DIS_RESULT UnlockVertexBuffer()
	{
		HRESULT hr;
		hr = pd3dMesh->UnlockVertexBuffer();
		return HR_to_DR(hr);
	}

	//This method allows the user to change the mesh declaration without changing the data layout of the vertex buffer. The call is valid only if the old and new declaration formats have the same vertex size.
	DIS_RESULT UpdateSemantics(
		DIS_VERTEXELEMENT *Declaration // [in, out]  
	)
	{

		// TODO
		HRESULT hr;
		//D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];

		return DIS_FAIL;
		/*for( int i = 0; i < MAX_FVF_DECL_SIZE; i++ )
		{
			decl[i].Method = 
		}*/
		//hr = pd3dMesh->UpdateSemantics(decl);
		//return HR_to_DR(hr);
	}


//Locks the mesh buffer that contains the mesh attribute data, and returns a pointer to it.
	DIS_RESULT LockAttributeBuffer(
		UInt32 Flags, //   [in]   
	/*
		Combination of zero or more locking flags that describe the type of lock to perform. For this method, the valid flags are:
		D3DLOCK_DISCARD
		D3DLOCK_NO_DIRTY_UPDATE
		D3DLOCK_NOSYSLOCK
		D3DLOCK_READONLY
	*/
		UInt32 **ppData //   [out]  //Address of a pointer to a buffer containing a DWORD for each face in the mesh.
	)
	{
		HRESULT hr;
		DWORD flags = 0;

		if( Flags & DIS_LOCK_DISCARD )
		{
			flags |= D3DLOCK_DISCARD;
		}
		if( Flags & DIS_LOCK_NO_DIRTY_UPDATE )
		{
			flags |= D3DLOCK_NO_DIRTY_UPDATE;
		}
		if( Flags & DIS_LOCK_NOSYSLOCK )
		{
			flags |= D3DLOCK_NOSYSLOCK;
		}
		if( Flags & DIS_LOCK_READONLY )
		{
			flags |= D3DLOCK_READONLY;
		}
		
		hr = pd3dMesh->LockAttributeBuffer( flags, (DWORD**)&(*ppData));
		
		return HR_to_DR(hr);
	}
	

	
	//Generates a new mesh with reordered faces and vertices to optimize drawing performance.
	DIS_RESULT Optimize(
		UInt32 Flags, // [in]   //Specifies the type of optimization to perform. This parameter can be set to a combination of one or more flags from D3DXMESHOPT and D3DXMESH (except D3DXMESH_32BIT, D3DXMESH_IB_WRITEONLY, and D3DXMESH_WRITEONLY).    
		const UInt32 *pAdjacencyIn, // [in]    Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the source mesh. If the edge has no adjacent faces, the value is 0xffffffff. See Remarks.   
		UInt32 *pAdjacencyOut, // [in, out]  Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the optimized mesh. If the edge has no adjacent faces, the value is 0xffffffff.
		UInt32 *pFaceRemap, // [in, out]  An array of DWORDs, one per face, that identifies the original mesh face that corresponds to each face in the optimized mesh. If the value supplied for this argument is NULL, face remap data is not returned.
		LPBUFFER *ppVertexRemap, //[out]      Address of a pointer to an ID3DXBuffer interface, which contains a DWORD for each vertex that specifies how the new vertices map to the old vertices. This remap is useful if you need to alter external data based on the new vertex mapping.
		LPDISXMESH *ppOptMesh //[out]      Address of a pointer to an ID3DXMesh interface, representing the optimized mesh.
	);


	//Generates a mesh with reordered faces and vertices to optimize drawing performance. This method reorders the existing mesh.
	DIS_RESULT OptimizeInplace(
		UInt32 Flags,//  [in]   Combination of one or more D3DXMESHOPT flags, specifying the type of optimization to perform.
		const UInt32 *pAdjacencyIn, //   [in]   Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the source mesh. If the edge has no adjacent faces, the value is 0xffffffff.
		UInt32 *pAdjacencyOut, //   [out]  Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the optimized mesh. If the edge has no adjacent faces, the value is 0xffffffff. If the value supplied for this argument is NULL, adjacency data is not returned.
		UInt32 *pFaceRemap, //   [out]  An array of DWORDs, one per face, that identifies the original mesh face that corresponds to each face in the optimized mesh. If the value supplied for this argument is NULL, face remap data is not returned.
		LPBUFFER *ppVertexRemap //   [out]  Address of a pointer to an ID3DXBuffer interface, which contains a DWORD for each vertex that specifies how the new vertices map to the old vertices. This remap is useful if you need to alter external data based on the new vertex mapping. If the value supplied for this argument is NULL, vertex remap data is not returned.
	);
	
	//Sets the attribute table for a mesh and the number of entries stored in the table.
	DIS_RESULT SetAttributeTable(
		const DISX_ATTRIBUTERANGE *pAttribTable, //   [in]  Pointer to an array of D3DXATTRIBUTERANGE structures, representing the entries in the mesh attribute table.
		UInt32 cAttribTableSize //   [in]  Number of attributes in the mesh attribute table.
	)
	{
		HRESULT hr;
		D3DXATTRIBUTERANGE attribTable[1024]; // for now
		for( int i = 0; i < 1024; i++ )
		{
			attribTable[i].AttribId = pAttribTable[i].AttribId;
			attribTable[i].FaceCount = pAttribTable[i].FaceCount;
			attribTable[i].FaceStart = pAttribTable[i].FaceStart;
			attribTable[i].VertexCount = pAttribTable[i].VertexCount;
			attribTable[i].VertexStart = pAttribTable[i].VertexStart;
		}

		hr = pd3dMesh->SetAttributeTable(attribTable, cAttribTableSize);
		return HR_to_DR(hr);
	}


	//Unlocks an attribute buffer.
	DIS_RESULT UnlockAttributeBuffer()
	{
		HRESULT hr;
		hr = pd3dMesh->UnlockAttributeBuffer();
		return HR_to_DR(hr);
	}
};


D3D9DISMesh m_disMeshGetter;

//Generates a new mesh with reordered faces and vertices to optimize drawing performance.
DIS_RESULT D3D9DISMesh::Optimize(
		UInt32 Flags, // [in]   //Specifies the type of optimization to perform. This parameter can be set to a combination of one or more flags from D3DXMESHOPT and D3DXMESH (except D3DXMESH_32BIT, D3DXMESH_IB_WRITEONLY, and D3DXMESH_WRITEONLY).    
		const UInt32 *pAdjacencyIn, // [in]    Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the source mesh. If the edge has no adjacent faces, the value is 0xffffffff. See Remarks.   
		UInt32 *pAdjacencyOut, // [in, out]  Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the optimized mesh. If the edge has no adjacent faces, the value is 0xffffffff.
		UInt32 *pFaceRemap, // [in, out]  An array of DWORDs, one per face, that identifies the original mesh face that corresponds to each face in the optimized mesh. If the value supplied for this argument is NULL, face remap data is not returned.
		LPBUFFER *ppVertexRemap, //[out]      Address of a pointer to an ID3DXBuffer interface, which contains a DWORD for each vertex that specifies how the new vertices map to the old vertices. This remap is useful if you need to alter external data based on the new vertex mapping.
		LPDISXMESH *ppOptMesh //[out]      Address of a pointer to an ID3DXMesh interface, representing the optimized mesh.
	)
{
	HRESULT hr;
	DWORD flags = 0;
  
	if( Flags & D3DXMESHOPT_COMPACT )
	{
		flags |= D3DXMESHOPT_COMPACT;
	}
	if( Flags & DISX_MESHOPT_ATTRSORT )
	{
		flags |= D3DXMESHOPT_ATTRSORT;
	}
	if( Flags & DISX_MESHOPT_VERTEXCACHE )
	{
		flags |= D3DXMESHOPT_VERTEXCACHE ;
	}
	if( Flags & DISX_MESHOPT_STRIPREORDER )
	{
		flags |= D3DXMESHOPT_STRIPREORDER;
	}
	if( Flags & DISX_MESHOPT_IGNOREVERTS )
	{
		flags |= D3DXMESHOPT_IGNOREVERTS ;
	}
	if( Flags & DISX_MESHOPT_DONOTSPLIT )
	{
		flags |= D3DXMESHOPT_DONOTSPLIT ;
	}
	if( Flags & DISX_MESHOPT_DEVICEINDEPENDENT )
	{
		flags |= D3DXMESHOPT_DEVICEINDEPENDENT;
	}


	
	hr = pd3dMesh->Optimize( 
					flags, 
					(const DWORD*)pAdjacencyIn, 
					(DWORD*)pAdjacencyOut, 
					(DWORD*)pFaceRemap, 
					&m_bufferGetter.pd3dBuffer, 
					&m_disMeshGetter.pd3dMesh);

	*ppOptMesh = &m_disMeshGetter;
	*ppVertexRemap = &m_bufferGetter;

	return HR_to_DR(hr);
}


DIS_RESULT D3D9DISMesh::OptimizeInplace(
		UInt32 Flags,//  [in]   Combination of one or more D3DXMESHOPT flags, specifying the type of optimization to perform.
		const UInt32 *pAdjacencyIn, //   [in]   Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the source mesh. If the edge has no adjacent faces, the value is 0xffffffff.
		UInt32 *pAdjacencyOut, //   [out]  Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the optimized mesh. If the edge has no adjacent faces, the value is 0xffffffff. If the value supplied for this argument is NULL, adjacency data is not returned.
		UInt32 *pFaceRemap, //   [out]  An array of DWORDs, one per face, that identifies the original mesh face that corresponds to each face in the optimized mesh. If the value supplied for this argument is NULL, face remap data is not returned.
		LPBUFFER *ppVertexRemap //   [out]  Address of a pointer to an ID3DXBuffer interface, which contains a DWORD for each vertex that specifies how the new vertices map to the old vertices. This remap is useful if you need to alter external data based on the new vertex mapping. If the value supplied for this argument is NULL, vertex remap data is not returned.
	)
{
	HRESULT hr;
	DWORD flags = 0;
	if( Flags & D3DXMESHOPT_COMPACT )
	{
		flags |= D3DXMESHOPT_COMPACT;
	}
	if( Flags & DISX_MESHOPT_ATTRSORT )
	{
		flags |= D3DXMESHOPT_ATTRSORT;
	}
	if( Flags & DISX_MESHOPT_VERTEXCACHE )
	{
		flags |= D3DXMESHOPT_VERTEXCACHE ;
	}
	if( Flags & DISX_MESHOPT_STRIPREORDER )
	{
		flags |= D3DXMESHOPT_STRIPREORDER;
	}
	if( Flags & DISX_MESHOPT_IGNOREVERTS )
	{
		flags |= D3DXMESHOPT_IGNOREVERTS ;
	}
	if( Flags & DISX_MESHOPT_DONOTSPLIT )
	{
		flags |= D3DXMESHOPT_DONOTSPLIT ;
	}
	if( Flags & DISX_MESHOPT_DEVICEINDEPENDENT )
	{
		flags |= D3DXMESHOPT_DEVICEINDEPENDENT;
	}

	m_disMeshGetter.m_pd3dDevice = *GetDeviceD3D();
	m_disMeshGetter.pd3dMesh = 0;
	
	hr = pd3dMesh->OptimizeInplace( 
					flags, 
					(const DWORD*)pAdjacencyIn, 
					(DWORD*)pAdjacencyOut, 
					(DWORD*)pFaceRemap, 
					&m_bufferGetter.pd3dBuffer);

	*ppVertexRemap = &m_bufferGetter;
	return HR_to_DR(hr);
}

// Effect object
class D3D9Effect : public DIS_Effect
{
public:
	LPD3DXEFFECT m_pD3DEffect;

	D3D9Effect(DIS_ResourceManager *resourceManager)
	{
		this->SetResourceManager( resourceManager );
		this->m_resourceManager->AddResource(this);
	}

	void Release()
	{
		this->ReleaseMe();
	}

// Descs
	DIS_RESULT GetDesc(DISX_EFFECT_DESC* pDesc)
	{
		HRESULT hr;
		D3DXEFFECT_DESC effectDesc;
		hr = m_pD3DEffect->GetDesc(&effectDesc);
		
		pDesc->Creator = effectDesc.Creator;
		pDesc->Functions = effectDesc.Functions;
		pDesc->Parameters = effectDesc.Parameters;
		pDesc->Techniques = effectDesc.Techniques;

		return HR_to_DR(hr);
	}

	DIS_RESULT GetParameterDesc(DIS_HANDLE hParameter, DISX_PARAMETER_DESC* pDesc)	
	{
		HRESULT hr;
		D3DXPARAMETER_DESC paramDesc;
		hr = m_pD3DEffect->GetParameterDesc(D3DXHANDLE(hParameter),&paramDesc);

		pDesc->Annotations = paramDesc.Annotations;
		pDesc->Bytes = paramDesc.Bytes;
		switch( paramDesc.Class )
		{
		case D3DXPC_SCALAR: pDesc->Class = DISX_PC_SCALAR; break;
		case D3DXPC_VECTOR: pDesc->Class = DISX_PC_VECTOR;break;
		case D3DXPC_MATRIX_ROWS: pDesc->Class = DISX_PC_MATRIX_ROWS;break;
		case D3DXPC_MATRIX_COLUMNS: pDesc->Class = DISX_PC_MATRIX_COLUMNS;break;
		case D3DXPC_OBJECT: pDesc->Class = DISX_PC_OBJECT;break;
		case D3DXPC_STRUCT: pDesc->Class = DISX_PC_STRUCT;break;
		default:pDesc->Class = DISX_PC_SCALAR;break;
		};
		//pDesc->Class = 
		pDesc->Columns = paramDesc.Columns;
		pDesc->Elements = paramDesc.Elements;
		pDesc->Flags = paramDesc.Flags;
		pDesc->Name = paramDesc.Name;
		pDesc->Rows = paramDesc.Rows;
		pDesc->Semantic = paramDesc.Semantic;
		pDesc->StructMembers = paramDesc.StructMembers;
		//pDesc->Type =
		switch( paramDesc.Type )
		{
		case D3DXPT_VOID: pDesc->Type = DISX_PT_VOID;break;
		case D3DXPT_BOOL: pDesc->Type = DISX_PT_BOOL;break;
		case D3DXPT_INT: pDesc->Type = DISX_PT_INT;break;
		case D3DXPT_FLOAT: pDesc->Type = DISX_PT_FLOAT;break;
		case D3DXPT_STRING: pDesc->Type = DISX_PT_STRING;break;
		case D3DXPT_TEXTURE: pDesc->Type = DISX_PT_TEXTURE;break;
		case D3DXPT_TEXTURE1D: pDesc->Type = DISX_PT_TEXTURE1D;break;
		case D3DXPT_TEXTURE2D: pDesc->Type = DISX_PT_TEXTURE2D;break;
		case D3DXPT_TEXTURE3D: pDesc->Type = DISX_PT_TEXTURE3D;break;
		case D3DXPT_TEXTURECUBE: pDesc->Type = DISX_PT_TEXTURECUBE;break;
		case D3DXPT_SAMPLER: pDesc->Type = DISX_PT_SAMPLER;break;
		case D3DXPT_SAMPLER1D: pDesc->Type = DISX_PT_SAMPLER1D;break;
		case D3DXPT_SAMPLER2D: pDesc->Type = DISX_PT_SAMPLER2D;break;
		case D3DXPT_SAMPLER3D: pDesc->Type = DISX_PT_SAMPLER3D;break;
		case D3DXPT_SAMPLERCUBE: pDesc->Type = DISX_PT_SAMPLERCUBE;break;
		case D3DXPT_PIXELSHADER: pDesc->Type = DISX_PT_PIXELSHADER;break;
		case D3DXPT_VERTEXSHADER: pDesc->Type = DISX_PT_VERTEXSHADER;break;
		case D3DXPT_PIXELFRAGMENT: pDesc->Type = DISX_PT_PIXELFRAGMENT;break;
		case D3DXPT_VERTEXFRAGMENT: pDesc->Type = DISX_PT_VERTEXFRAGMENT;break;
		case D3DXPT_UNSUPPORTED: pDesc->Type = DISX_PT_UNSUPPORTED;break;
		default: pDesc->Type = DISX_PT_UNSUPPORTED;break;
		};
		return HR_to_DR(hr);
	}
	DIS_RESULT GetTechniqueDesc(DIS_HANDLE hTechnique, DISX_TECHNIQUE_DESC* pDesc)
	{
		HRESULT hr;
		D3DXTECHNIQUE_DESC techniqueDesc;
		hr = m_pD3DEffect->GetTechniqueDesc(D3DXHANDLE(hTechnique),&techniqueDesc);
		
		pDesc->Annotations = techniqueDesc.Annotations;
		pDesc->Name = techniqueDesc.Name;
		pDesc->Passes = techniqueDesc.Passes;
		
		return HR_to_DR(hr);
	}
	DIS_RESULT GetPassDesc(DIS_HANDLE hPass, DISX_PASS_DESC* pDesc)
	{
		HRESULT hr;
		D3DXPASS_DESC passDesc;
		hr = m_pD3DEffect->GetPassDesc(D3DXHANDLE(hPass),&passDesc);
		
		pDesc->Annotations = passDesc.Annotations;
		pDesc->Name = passDesc.Name;
		pDesc->pPixelShaderFunction = (const UInt32*) passDesc.pPixelShaderFunction;
		pDesc->pVertexShaderFunction = (const UInt32*) passDesc.pVertexShaderFunction;

		return HR_to_DR(hr);
	}
	DIS_RESULT GetFunctionDesc(DIS_HANDLE hShader, DISX_FUNCTION_DESC* pDesc)
	{
		HRESULT hr;
		D3DXFUNCTION_DESC funcDesc;
		hr = m_pD3DEffect->GetFunctionDesc(D3DXHANDLE(hShader),&funcDesc);
		
		pDesc->Annotations = funcDesc.Annotations;
		pDesc->Name = funcDesc.Name;

		return HR_to_DR(hr);
	}
	// Handle operations
	DIS_HANDLE GetParameter( DIS_HANDLE hParameter, UInt32 Index)
	{
		return (DIS_HANDLE)m_pD3DEffect->GetParameter(D3DXHANDLE(hParameter), Index);	
	}
	DIS_HANDLE GetParameterByName( DIS_HANDLE hParameter, M_CSTR pName)
	{
		return (DIS_HANDLE)m_pD3DEffect->GetParameterByName(D3DXHANDLE(hParameter), pName);
	}
	DIS_HANDLE GetParameterBySemantic( DIS_HANDLE hParameter, M_CSTR pSemantic)
	{
		return (DIS_HANDLE)m_pD3DEffect->GetParameterBySemantic(D3DXHANDLE(hParameter), pSemantic);
	}
	DIS_HANDLE GetParameterElement( DIS_HANDLE hParameter, UInt32 Index)
	{
		return (DIS_HANDLE)m_pD3DEffect->GetParameterElement(D3DXHANDLE(hParameter), Index);
	}
	DIS_HANDLE GetTechnique( UInt32 Index)
	{
		return (DIS_HANDLE)m_pD3DEffect->GetTechnique(Index);
	}
	DIS_HANDLE GetTechniqueByName( M_CSTR pName)
	{
		return (DIS_HANDLE)m_pD3DEffect->GetTechniqueByName(pName);
	}
	DIS_HANDLE GetPass( DIS_HANDLE hTechnique, UInt32 Index)
	{
		return (DIS_HANDLE)m_pD3DEffect->GetPass(D3DXHANDLE(hTechnique), Index);
	}
	DIS_HANDLE GetPassByName( DIS_HANDLE hTechnique, M_CSTR pName)
	{
		return (DIS_HANDLE)m_pD3DEffect->GetPassByName(D3DXHANDLE(hTechnique), pName);
	}
	DIS_HANDLE GetFunction( UInt32 Index )
	{
		return (DIS_HANDLE)m_pD3DEffect->GetFunction(Index);
	}
	DIS_HANDLE GetFunctionByName( M_CSTR pName )
	{
		return (DIS_HANDLE)m_pD3DEffect->GetFunctionByName(pName);
	}
	DIS_HANDLE GetAnnotation( DIS_HANDLE hObject, UInt32 Index )
	{
		return (DIS_HANDLE)m_pD3DEffect->GetAnnotation(D3DXHANDLE(hObject),Index);
	}
	DIS_HANDLE GetAnnotationByName( DIS_HANDLE hObject, M_CSTR pName )
	{
		return (DIS_HANDLE)m_pD3DEffect->GetAnnotationByName(D3DXHANDLE(hObject),pName);
	}
	// Get/Set Parameters
	DIS_RESULT SetValue( DIS_HANDLE hParameter, const void* pData, UInt32 Bytes )
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetValue(D3DXHANDLE(hParameter),pData, Bytes);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetValue( DIS_HANDLE hParameter, void* pData, UInt32 Bytes )
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetValue(D3DXHANDLE(hParameter),pData, Bytes);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetBool( DIS_HANDLE hParameter, bool b ) 
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetBool(D3DXHANDLE(hParameter),b);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetBool( DIS_HANDLE hParameter, bool* pb )   
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetBool(D3DXHANDLE(hParameter),(BOOL*)&(*pb));
		return HR_to_DR(hr);
	}
	DIS_RESULT SetBoolArray( DIS_HANDLE hParameter, const bool* pb, UInt32 Count )   
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetBoolArray(D3DXHANDLE(hParameter), (const BOOL*)pb, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetBoolArray( DIS_HANDLE hParameter, bool* pb, UInt32 Count )
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetBoolArray(D3DXHANDLE(hParameter), (BOOL*)pb, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetInt( DIS_HANDLE hParameter, Int32 n )
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetInt(D3DXHANDLE(hParameter), n);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetInt( DIS_HANDLE hParameter, Int32* pn )
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetInt(D3DXHANDLE(hParameter), pn);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetIntArray( DIS_HANDLE hParameter, const Int32* pn, UInt32 Count)
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetIntArray(D3DXHANDLE(hParameter), (const INT*)pn, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetIntArray( DIS_HANDLE hParameter, Int32* pn, UInt32 Count)
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetIntArray(D3DXHANDLE(hParameter), (INT*)pn, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetFloat( DIS_HANDLE hParameter, float f)
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetFloat(D3DXHANDLE(hParameter), f);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetFloat( DIS_HANDLE hParameter, float* pf)
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetFloat(D3DXHANDLE(hParameter), pf);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetFloatArray( DIS_HANDLE hParameter, const float* pf, UInt32 Count)
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetFloatArray(D3DXHANDLE(hParameter), (const float*)pf, Count);
		return HR_to_DR(hr);

	}
	DIS_RESULT GetFloatArray( DIS_HANDLE hParameter, float* pf, UInt32 Count)
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetFloatArray(D3DXHANDLE(hParameter), (float*)pf, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetVector( DIS_HANDLE hParameter, const DISX_VECTOR4* pVector)
	{
		HRESULT hr;
		D3DXVECTOR4 v = D3DXVECTOR4(pVector->x, pVector->y, pVector->z,pVector->w);
		hr = m_pD3DEffect->SetVector(D3DXHANDLE(hParameter), &v);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetVector( DIS_HANDLE hParameter, DISX_VECTOR4* pVector)
	{
		HRESULT hr;
		D3DXVECTOR4 v;
		hr = m_pD3DEffect->GetVector( D3DXHANDLE(hParameter), &v );
		*pVector = DISX_VECTOR4(pVector->x, pVector->y, pVector->z,pVector->w);
		
		return HR_to_DR(hr);
	}
	DIS_RESULT SetVectorArray( DIS_HANDLE hParameter, const DISX_VECTOR4* pVector, UInt32 Count)
	{
		HRESULT hr;
		
		hr = m_pD3DEffect->SetVectorArray( D3DXHANDLE(hParameter), (const D3DXVECTOR4*)pVector, Count );
		

		return HR_to_DR(hr);
	}
	DIS_RESULT GetVectorArray( DIS_HANDLE hParameter, DISX_VECTOR4* pVector, UInt32 Count)
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetVectorArray( D3DXHANDLE(hParameter), (D3DXVECTOR4*)pVector, Count );
		return HR_to_DR(hr);
	}
	DIS_RESULT SetMatrix( DIS_HANDLE hParameter, const DISX_MATRIX* pMatrix)
	{
		HRESULT hr;
		D3DXMATRIX m;
		Copy_DIS_MATRIX_To_D3DMATRIX(*pMatrix, m);
		hr = m_pD3DEffect->SetMatrix( D3DXHANDLE(hParameter), &m);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetMatrix( DIS_HANDLE hParameter, DISX_MATRIX* pMatrix )
	{
		HRESULT hr;
		D3DXMATRIX m;
		
		hr = m_pD3DEffect->GetMatrix( D3DXHANDLE(hParameter), &m);
		Copy_D3DMATRIX_To_DIS_MATRIX( m, *pMatrix);
		
		return HR_to_DR(hr);
	}
	DIS_RESULT SetMatrixArray( DIS_HANDLE hParameter, const DISX_MATRIX* pMatrix, UInt32 Count )
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetMatrixArray( D3DXHANDLE(hParameter), (const D3DXMATRIX*)pMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetMatrixArray(  DIS_HANDLE hParameter, DISX_MATRIX* pMatrix, UInt32 Count )
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetMatrixArray( D3DXHANDLE(hParameter), (D3DXMATRIX*)pMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetMatrixPointerArray( DIS_HANDLE hParameter, const DISX_MATRIX** ppMatrix, UInt32 Count )
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetMatrixPointerArray( D3DXHANDLE(hParameter), (const D3DXMATRIX**)ppMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetMatrixPointerArray( DIS_HANDLE hParameter, DISX_MATRIX** ppMatrix, UInt32 Count ) 
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetMatrixPointerArray( D3DXHANDLE(hParameter), (D3DXMATRIX**)ppMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetMatrixTranspose( DIS_HANDLE hParameter, const DISX_MATRIX* pMatrix )
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetMatrixTranspose( D3DXHANDLE(hParameter), (const D3DXMATRIX*)pMatrix);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetMatrixTranspose( DIS_HANDLE hParameter, DISX_MATRIX* pMatrix )
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetMatrixTranspose( D3DXHANDLE(hParameter), (D3DXMATRIX*)pMatrix);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetMatrixTransposeArray( DIS_HANDLE hParameter, const DISX_MATRIX* pMatrix, UInt32 Count )
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetMatrixTransposeArray( D3DXHANDLE(hParameter), (const D3DXMATRIX*)pMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetMatrixTransposeArray( DIS_HANDLE hParameter, DISX_MATRIX* pMatrix, UInt32 Count )
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetMatrixTransposeArray( D3DXHANDLE(hParameter), (D3DXMATRIX*)pMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetMatrixTransposePointerArray( DIS_HANDLE hParameter, const DISX_MATRIX** ppMatrix, UInt32 Count )
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetMatrixTransposePointerArray( D3DXHANDLE(hParameter), (const D3DXMATRIX**)ppMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetMatrixTransposePointerArray( DIS_HANDLE hParameter, DISX_MATRIX** ppMatrix, UInt32 Count ) 
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetMatrixTransposePointerArray( D3DXHANDLE(hParameter), (D3DXMATRIX**)ppMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetString( DIS_HANDLE hParameter, M_CSTR pString )
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetString( D3DXHANDLE(hParameter), pString);
		return HR_to_DR(hr);
	}
	DIS_RESULT GetString( DIS_HANDLE hParameter, M_CSTR* ppString )
	{
		HRESULT hr;
		hr = m_pD3DEffect->GetString( D3DXHANDLE(hParameter), ppString);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetTexture( DIS_HANDLE hParameter, LPBASETEXTURE pTexture ) 
	{

		HRESULT hr;
		switch( pTexture->GetTextureType() )
		{
		case RESOURCE_TEXTURE_TYPE::TEXTURE2D_TEXTURE_TYPE:
			{
				hr = m_pD3DEffect->SetTexture( D3DXHANDLE(hParameter), LPTEXTURE2D_D3D9(pTexture)->pd3dTexture);
			}
			break;
		case RESOURCE_TEXTURE_TYPE::CUBE_TEXTURE_TYPE:
			{
				hr = m_pD3DEffect->SetTexture( D3DXHANDLE(hParameter), LPCUBETEXTURE2D_D3D9(pTexture)->pd3dCubeTexture);
			}
			break;
		case RESOURCE_TEXTURE_TYPE::VOLUME_TEXTURE_TYPE:
			{
				hr = m_pD3DEffect->SetTexture( D3DXHANDLE(hParameter), LPVOLUMETEXTURE_D3D9(pTexture)->pd3dVolumeTexture);
			}
			break;

		default: hr = E_FAIL; break;
		
		};
		
		return HR_to_DR(hr);
	}
	DIS_RESULT GetTexture( DIS_HANDLE hParameter, LPBASETEXTURE *ppTexture )
	{
		HRESULT hr;

		return HR_to_DR(hr);
	}
	DIS_RESULT GetPixelShader( DIS_HANDLE hParameter, LPPIXELSHADER *ppPShader )
	{
		// GET FROM RESOURCE MANAGER
		if( *ppPShader == NULL )
		{
			return DIS_FAIL;
		}
		HRESULT hr = E_FAIL;

		return HR_to_DR(hr);
	}
	DIS_RESULT GetVertexShader( DIS_HANDLE hParameter, LPVERTEXSHADER *ppVShader)
	{
		// GET FROM RESOURCE MANAGER
		HRESULT hr = E_FAIL;

		return HR_to_DR(hr);
	}

	//Set Range of an Array to pass to device
	//Usefull for sending only a subrange of an array down to the device
	DIS_RESULT SetArrayRange(  DIS_HANDLE hParameter, UInt32 uStart, UInt32 uEnd)
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetArrayRange( (D3DXHANDLE)hParameter, uStart, uEnd);
		return HR_to_DR(hr);
	}
	// IDISX_BaseEffect
    
    
	// Pool
	//DIS_RESULT GetPool(  LPDISX_EFFECTPOOL* ppPool)  ;

	// Selecting and setting a technique
	DIS_RESULT SetTechnique( DIS_HANDLE hTechnique)
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetTechnique( (D3DXHANDLE)hTechnique );
		return HR_to_DR(hr);
	}

	DIS_HANDLE GetCurrentTechnique()
	{
		
		return (DIS_HANDLE)m_pD3DEffect->GetCurrentTechnique();
		
	}
	DIS_RESULT ValidateTechnique( DIS_HANDLE hTechnique )
	{
		HRESULT hr;
		hr = m_pD3DEffect->ValidateTechnique( (D3DXHANDLE)hTechnique );
		return HR_to_DR(hr);
	}
	DIS_RESULT FindNextValidTechnique(  DIS_HANDLE hTechnique, DIS_HANDLE *pTechnique)
	{
		HRESULT hr;
		hr = m_pD3DEffect->FindNextValidTechnique( (D3DXHANDLE)hTechnique, (D3DXHANDLE*)pTechnique );
		return HR_to_DR(hr);
	}
	bool IsParameterUsed(  DIS_HANDLE hParameter, DIS_HANDLE hTechnique) 
	{
		return m_pD3DEffect->IsParameterUsed( (D3DXHANDLE)hParameter, (D3DXHANDLE)hTechnique );
	}

	// Using current technique
	// Begin           starts active technique
	// BeginPass       begins a pass
	// CommitChanges   updates changes to any set calls in the pass. This should be called before
	//                 any DrawPrimitive call to d3d
	// EndPass         ends a pass
	// End             ends active technique
	DIS_RESULT Begin(  UInt32 *pPasses, UInt32 Flags)
	{
		HRESULT hr;
		hr = m_pD3DEffect->Begin( pPasses, Flags );
		return HR_to_DR(hr);
	}
	DIS_RESULT BeginPass(  UInt32 Pass )
	{
		HRESULT hr;
		hr = m_pD3DEffect->BeginPass( Pass );
		return HR_to_DR(hr);
	}
	DIS_RESULT CommitChanges()
	{
		HRESULT hr;
		hr = m_pD3DEffect->CommitChanges();
		return HR_to_DR(hr);
	}
	DIS_RESULT EndPass()
	{
		HRESULT hr;
		hr = m_pD3DEffect->EndPass();
		return HR_to_DR(hr);
	}
	DIS_RESULT End()
	{
		HRESULT hr;
		hr = m_pD3DEffect->End();
		return HR_to_DR(hr);
	}

	// Managing D3D Device

	// Parameter blocks
	DIS_RESULT BeginParameterBlock()
	{
		HRESULT hr;
		hr = m_pD3DEffect->BeginParameterBlock();
		return HR_to_DR(hr);
	}
	DIS_HANDLE EndParameterBlock()
	{

		return (DIS_HANDLE) m_pD3DEffect->EndParameterBlock();
//		return HR_to_DR(hr);
	}
	DIS_RESULT ApplyParameterBlock(  DIS_HANDLE hParameterBlock)
	{
		HRESULT hr;
		hr = m_pD3DEffect->ApplyParameterBlock( (D3DXHANDLE)hParameterBlock );
		return HR_to_DR(hr);
	}
	DIS_RESULT DeleteParameterBlock(  DIS_HANDLE hParameterBlock)
	{
		HRESULT hr;
		hr = m_pD3DEffect->DeleteParameterBlock( (D3DXHANDLE)hParameterBlock );
		return HR_to_DR(hr);
	}

	// Cloning
	//STDMETHOD(CloneEffect)(  LPDIRECT3DDEVICE9 pDevice, LPDISX_EFFECT* ppEffect)  ;
    
	// Fast path for setting variables directly in IDISX_Effect
	DIS_RESULT SetRawValue(  DIS_HANDLE hParameter, const void* pData, UInt32 ByteOffset, UInt32 Bytes)
	{
		HRESULT hr;
		hr = m_pD3DEffect->SetRawValue( (D3DXHANDLE)hParameter, pData, ByteOffset, Bytes );
		return HR_to_DR(hr);
	}

};



void CopyConstantDesc(D3DXCONSTANT_DESC &Desc,DISX_CONSTANT_DESC* pConstantDesc)
{
	pConstantDesc->Bytes = Desc.Bytes;
	switch (Desc.Class)
	{
	case D3DXPARAMETER_CLASS::D3DXPC_VECTOR:
	{
		pConstantDesc->Class = DISX_PARAMETER_CLASS::DISX_PC_VECTOR;
		break;
	}
	case D3DXPARAMETER_CLASS::D3DXPC_STRUCT:
	{
		pConstantDesc->Class = DISX_PARAMETER_CLASS::DISX_PC_STRUCT;
		break;
	}
	case D3DXPARAMETER_CLASS::D3DXPC_SCALAR:
	{
		pConstantDesc->Class = DISX_PARAMETER_CLASS::DISX_PC_SCALAR;
		break;
	}
	case D3DXPARAMETER_CLASS::D3DXPC_OBJECT:
	{
		pConstantDesc->Class = DISX_PARAMETER_CLASS::DISX_PC_OBJECT;
		break;
	}
	case D3DXPARAMETER_CLASS::D3DXPC_MATRIX_ROWS:
	{
		pConstantDesc->Class = DISX_PARAMETER_CLASS::DISX_PC_MATRIX_ROWS;
		break;
	}
	case D3DXPARAMETER_CLASS::D3DXPC_MATRIX_COLUMNS:
	{
		pConstantDesc->Class = DISX_PARAMETER_CLASS::DISX_PC_MATRIX_COLUMNS;
		break;
	}
	case D3DXPARAMETER_CLASS::D3DXPC_FORCE_DWORD:
	{
		pConstantDesc->Class = DISX_PARAMETER_CLASS::DISX_PC_FORCE_DWORD;
		break;
	}


	};

	pConstantDesc->Columns = Desc.Columns;
	pConstantDesc->DefaultValue = Desc.DefaultValue;
	pConstantDesc->Elements = Desc.Elements;
	pConstantDesc->Name = Desc.Name;
	pConstantDesc->RegisterCount = Desc.RegisterCount;
	pConstantDesc->RegisterIndex = Desc.RegisterIndex;


	switch (Desc.RegisterSet)
	{
	case D3DXREGISTER_SET::D3DXRS_BOOL: pConstantDesc->RegisterSet = DISX_REGISTER_SET::DISX_RS_BOOL; break;
	case D3DXREGISTER_SET::D3DXRS_FLOAT4: pConstantDesc->RegisterSet = DISX_REGISTER_SET::DISX_RS_FLOAT4; break;
	case D3DXREGISTER_SET::D3DXRS_FORCE_DWORD: pConstantDesc->RegisterSet = DISX_REGISTER_SET::DISX_RS_FORCE_DWORD; break;
	case D3DXREGISTER_SET::D3DXRS_INT4: pConstantDesc->RegisterSet = DISX_REGISTER_SET::DISX_RS_INT4; break;
	case D3DXREGISTER_SET::D3DXRS_SAMPLER: pConstantDesc->RegisterSet = DISX_REGISTER_SET::DISX_RS_SAMPLER; break;
	}

	pConstantDesc->Rows = Desc.Rows;
	pConstantDesc->StructMembers = Desc.StructMembers;

	switch (Desc.Type)
	{
	case D3DXPARAMETER_TYPE::D3DXPT_BOOL:pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_BOOL; break;
	case D3DXPARAMETER_TYPE::D3DXPT_VOID:pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_VOID; break;

	case D3DXPARAMETER_TYPE::D3DXPT_INT: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_INT; break;
	case D3DXPARAMETER_TYPE::D3DXPT_FLOAT: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_FLOAT; break;
	case D3DXPARAMETER_TYPE::D3DXPT_STRING: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_STRING; break;
	case D3DXPARAMETER_TYPE::D3DXPT_TEXTURE: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_TEXTURE; break;
	case D3DXPARAMETER_TYPE::D3DXPT_TEXTURE1D: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_TEXTURE1D; break;
	case D3DXPARAMETER_TYPE::D3DXPT_TEXTURE2D: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_TEXTURE2D; break;
	case D3DXPARAMETER_TYPE::D3DXPT_TEXTURE3D: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_TEXTURE3D; break;
	case D3DXPARAMETER_TYPE::D3DXPT_TEXTURECUBE: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_TEXTURECUBE; break;
	case D3DXPARAMETER_TYPE::D3DXPT_SAMPLER: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_SAMPLER; break;
	case D3DXPARAMETER_TYPE::D3DXPT_SAMPLER1D: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_SAMPLER1D; break;
	case D3DXPARAMETER_TYPE::D3DXPT_SAMPLER2D: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_SAMPLER2D; break;
	case D3DXPARAMETER_TYPE::D3DXPT_SAMPLER3D: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_SAMPLER3D; break;
	case D3DXPARAMETER_TYPE::D3DXPT_SAMPLERCUBE: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_SAMPLERCUBE; break;
	case D3DXPARAMETER_TYPE::D3DXPT_PIXELSHADER: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_PIXELSHADER; break;
	case D3DXPARAMETER_TYPE::D3DXPT_VERTEXSHADER: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_VERTEXSHADER; break;
	case D3DXPARAMETER_TYPE::D3DXPT_PIXELFRAGMENT: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_PIXELFRAGMENT; break;
	case D3DXPARAMETER_TYPE::D3DXPT_VERTEXFRAGMENT: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_VERTEXFRAGMENT; break;
	case D3DXPARAMETER_TYPE::D3DXPT_UNSUPPORTED: pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_UNSUPPORTED; break;

		// force 32-bit size enum
	case D3DXPARAMETER_TYPE::D3DXPT_FORCE_DWORD:pConstantDesc->Type = DISX_PARAMETER_TYPE::DISX_PT_FORCE_DWORD; break;
	}
}

class D3D9_ConstantTable : public DISX_ConstantTable
{
public:

	LPD3DXCONSTANTTABLE m_pD3DConstantTable;

	D3D9_ConstantTable(DIS_ResourceManager *resourceManager)
	{
		this->SetResourceManager(resourceManager);
		this->m_resourceManager->AddResource(this);
	}

	void Release()
	{
		this->ReleaseMe();
	}


	// Buffer
	 LPVOID GetBufferPointer(void)   	{
		 return this->m_pD3DConstantTable->GetBufferPointer();
		
	}
	 DWORD GetBufferSize(void)   	{
		 return m_pD3DConstantTable->GetBufferSize();
	}

	// Descs
	 DIS_RESULT GetDesc(DISX_CONSTANTTABLE_DESC *pDesc)   	{

		 D3DXCONSTANTTABLE_DESC Desc;
		 HRESULT hr = this->m_pD3DConstantTable->GetDesc(&Desc);
		 if (hr == S_OK)
		 {
			 pDesc->Constants = Desc.Constants;
			 pDesc->Creator = Desc.Creator;
			 pDesc->Version = Desc.Version;
			 return DIS_OK;
		 }
		 
		 return DIS_FAIL;
	}
	 DIS_RESULT GetConstantDesc(DISX_HANDLE hConstant, DISX_CONSTANT_DESC *pConstantDesc, UINT *pCount)  	{
		 D3DXCONSTANT_DESC Desc;
		 D3DXHANDLE handle=(D3DXHANDLE)hConstant;
		 UINT count;
		 HRESULT hr = this->m_pD3DConstantTable->GetConstantDesc(handle, &Desc, &count);
		 if (hr == S_OK)
		 {
			 if (!pCount) return DIS_FAIL;
			 if (!pConstantDesc) return DIS_FAIL;

			 *pCount = count;
			 hConstant = (DISX_HANDLE)handle;
			 CopyConstantDesc(Desc, pConstantDesc);
		
			 return DIS_OK;
		 }

		 return DIS_FAIL;
	}
	 UINT GetSamplerIndex(DISX_HANDLE hConstant)   	{
		
		 return this->m_pD3DConstantTable->GetSamplerIndex((D3DXHANDLE)hConstant);
		 
	}

	// Handle operations
	DISX_HANDLE GetConstant(DISX_HANDLE hConstant, UINT Index) 	{
		return (DISX_HANDLE)this->m_pD3DConstantTable->GetConstant((D3DXHANDLE)hConstant, Index);
	}
	DISX_HANDLE GetConstantByName(DISX_HANDLE hConstant, LPCSTR pName)	{
		if (pName == NULL)return hConstant;
		return (DISX_HANDLE)this->m_pD3DConstantTable->GetConstantByName((D3DXHANDLE)hConstant, pName);
	}
	DISX_HANDLE GetConstantElement(DISX_HANDLE hConstant, UINT Index)	{
		return (DISX_HANDLE)this->m_pD3DConstantTable->GetConstantElement((D3DXHANDLE)hConstant, Index);
	}

	// Set Constants
	DIS_RESULT SetDefaults(LPDEVICE pDevice)  	{
		HRESULT hr = this->m_pD3DConstantTable->SetDefaults(*GetDeviceD3D());
		return HR_to_DR(hr);
	}
	DIS_RESULT SetValue(LPDEVICE pDevice, DISX_HANDLE hConstant, LPCVOID pData, UINT Bytes)  	{
		HRESULT hr = this->m_pD3DConstantTable->SetValue(*GetDeviceD3D(), (D3DXHANDLE)hConstant, pData, Bytes);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetBool(LPDEVICE pDevice, DISX_HANDLE hConstant, BOOL b)  	{
		HRESULT hr = this->m_pD3DConstantTable->SetBool(*GetDeviceD3D(), (D3DXHANDLE)hConstant, b);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetBoolArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST BOOL* pb, UINT Count)  	{
		if (pb == NULL || sizeof(pb) > Count* sizeof(bool)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetBoolArray(*GetDeviceD3D(), (D3DXHANDLE)hConstant, pb, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetInt(LPDEVICE pDevice, DISX_HANDLE hConstant, INT n)  	{
		HRESULT hr = this->m_pD3DConstantTable->SetInt(*GetDeviceD3D(), (D3DXHANDLE)hConstant, n);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetIntArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST INT* pn, UINT Count) 	{
		if (pn == NULL || sizeof(pn) > Count* sizeof(INT)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetIntArray(*GetDeviceD3D(), (D3DXHANDLE)hConstant, pn, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetFloat(LPDEVICE pDevice, DISX_HANDLE hConstant, FLOAT f)  	{
		HRESULT hr = this->m_pD3DConstantTable->SetFloat(*GetDeviceD3D(), (D3DXHANDLE)hConstant, f);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetFloatArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST FLOAT* pf, UINT Count)  	{
		if (pf == NULL || sizeof(pf) > Count* sizeof(FLOAT)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetFloatArray(*GetDeviceD3D(), (D3DXHANDLE)hConstant, pf, Count);
		return HR_to_DR(hr);
	}
		 
	DIS_RESULT SetVector(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_VECTOR4* pVector)  	{
		if (pVector == NULL ) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetVector(*GetDeviceD3D(), (D3DXHANDLE)hConstant, (const D3DXVECTOR4*)pVector);
		return HR_to_DR(hr);
		 }
		 
	DIS_RESULT SetVectorArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_VECTOR4* pVector, UINT Count) 	{
		if (pVector == NULL || sizeof(pVector) > Count* sizeof(DISX_VECTOR4)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetVectorArray(*GetDeviceD3D(), (D3DXHANDLE)hConstant, (const D3DXVECTOR4*)pVector, Count);
		return HR_to_DR(hr);
		 }
		 
	DIS_RESULT SetMatrix(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix)  	{
		if (pMatrix == NULL) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetMatrix(*GetDeviceD3D(), (D3DXHANDLE)hConstant, (const D3DXMATRIX*)pMatrix);
		return HR_to_DR(hr);
		 }
		
	DIS_RESULT SetMatrixArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix, UINT Count) 	{
		if (pMatrix == NULL || sizeof(pMatrix) > Count* sizeof(DISX_MATRIX)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetMatrixArray(*GetDeviceD3D(), (D3DXHANDLE)hConstant, (const D3DXMATRIX*)pMatrix, Count);
		return HR_to_DR(hr);
		 }
		 
	DIS_RESULT SetMatrixPointerArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX** ppMatrix, UINT Count)  	{
		//if (ppMatrix == NULL || sizeof(ppMatrix) > Count* sizeof((DISX_MATRIX*))) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetMatrixPointerArray(*GetDeviceD3D(), (D3DXHANDLE)hConstant, (const D3DXMATRIX**)ppMatrix, Count);
		return HR_to_DR(hr);
		 }
		
	DIS_RESULT SetMatrixTranspose(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix)  	{
		if (pMatrix == NULL) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetMatrixTranspose(*GetDeviceD3D(), (D3DXHANDLE)hConstant, (const D3DXMATRIX*)pMatrix);
		return HR_to_DR(hr);
		 }
		 
	DIS_RESULT SetMatrixTransposeArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix, UINT Count)  	{
		if (pMatrix == NULL || sizeof(pMatrix) > Count* sizeof(DISX_MATRIX)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DConstantTable->SetMatrixTransposeArray(*GetDeviceD3D(), (D3DXHANDLE)hConstant, (const D3DXMATRIX*)pMatrix, Count);
		return HR_to_DR(hr);
		 }
		 DIS_RESULT SetMatrixTransposePointerArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX** ppMatrix, UINT Count)  	{
			 HRESULT hr = this->m_pD3DConstantTable->SetMatrixTransposePointerArray(*GetDeviceD3D(), (D3DXHANDLE)hConstant, (const D3DXMATRIX**)ppMatrix, Count);
			 return HR_to_DR(hr);
		 }

};



class D3D9_TextureShader : public DISX_TextureShader 
{
public:

	LPD3DXTEXTURESHADER m_pD3DTextureShader;

	D3D9_TextureShader(DIS_ResourceManager *resourceManager)
	{
		this->SetResourceManager(resourceManager);
		this->m_resourceManager->AddResource(this);
	}

	void Release()
	{
		this->ReleaseMe();
	}

	// Gets
	DIS_RESULT GetFunction(LPBUFFER *ppFunction)	{
		
		if (ppFunction == NULL)
		{
			return DIS_FAIL;
		}

		LPD3DXBUFFER pBuffer =0;

		HRESULT hr = this->m_pD3DTextureShader->GetFunction(&pBuffer);

		if (hr == S_OK)
		{
			(*ppFunction) = new D3D9_Buffer(pBuffer, this->m_resourceManager);
			

			return DIS_OK;
		}

		return DIS_FAIL;
	}
	DIS_RESULT GetConstantBuffer(LPBUFFER *ppConstantBuffer)	{
		if (ppConstantBuffer == NULL)
		{
			return DIS_FAIL;
		}

		LPD3DXBUFFER pBuffer = 0;

		HRESULT hr = this->m_pD3DTextureShader->GetConstantBuffer(&pBuffer);

		if (hr == S_OK)
		{
			(*ppConstantBuffer) = new D3D9_Buffer(pBuffer, this->m_resourceManager);

			return DIS_OK;
		}

		return DIS_FAIL;
	}

	// Descs
	DIS_RESULT GetDesc(DISX_CONSTANTTABLE_DESC *pDesc)	{
		D3DXCONSTANTTABLE_DESC desc;
		this->m_pD3DTextureShader->GetDesc(&desc);
		
		if (pDesc == NULL)
		{
			return DIS_FAIL;
		}
		else
		{
			pDesc->Constants = desc.Constants;
			pDesc->Creator = desc.Creator;
			pDesc->Version = desc.Version;
			return DIS_OK;
		}
		return DIS_OK;
	};
	DIS_RESULT GetConstantDesc(DISX_HANDLE hConstant, DISX_CONSTANT_DESC *pConstantDesc, UINT *pCount)	{
		D3DXCONSTANT_DESC desc;
		HRESULT hr = this->m_pD3DTextureShader->GetConstantDesc((D3DXHANDLE)hConstant, &desc, pCount);

		if (hr == S_OK)
		{
			CopyConstantDesc(desc, pConstantDesc);
			return DIS_OK;
		}
		
		return DIS_FAIL;
	}



	DISX_HANDLE GetConstant(DISX_HANDLE hConstant, UINT Index) 	{
		
		return (DISX_HANDLE)this->m_pD3DTextureShader->GetConstant((D3DXHANDLE)hConstant, Index);
	}
	DISX_HANDLE GetConstantByName(DISX_HANDLE hConstant, LPCSTR pName)	{
		if (pName == NULL)return hConstant;
		return (DISX_HANDLE)this->m_pD3DTextureShader->GetConstantByName((D3DXHANDLE)hConstant, pName);
	}
	DISX_HANDLE GetConstantElement(DISX_HANDLE hConstant, UINT Index)	{
		return (DISX_HANDLE)this->m_pD3DTextureShader->GetConstantElement((D3DXHANDLE)hConstant, Index);
	}

	// Set Constants
	DIS_RESULT SetDefaults()
	{
		HRESULT hr = this->m_pD3DTextureShader->SetDefaults();
		return HR_to_DR(hr);
	}
	DIS_RESULT SetValue(LPDEVICE pDevice, DISX_HANDLE hConstant, LPCVOID pData, UINT Bytes)  	{
		HRESULT hr = this->m_pD3DTextureShader->SetValue((D3DXHANDLE)hConstant, pData, Bytes);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetBool(LPDEVICE pDevice, DISX_HANDLE hConstant, BOOL b)  	{
		HRESULT hr = this->m_pD3DTextureShader->SetBool((D3DXHANDLE)hConstant, b);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetBoolArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST BOOL* pb, UINT Count)  	{
		if (pb == NULL || sizeof(pb) > Count* sizeof(bool)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetBoolArray((D3DXHANDLE)hConstant, pb, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetInt(LPDEVICE pDevice, DISX_HANDLE hConstant, INT n)  	{
		HRESULT hr = this->m_pD3DTextureShader->SetInt((D3DXHANDLE)hConstant, n);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetIntArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST INT* pn, UINT Count) 	{
		if (pn == NULL || sizeof(pn) > Count* sizeof(INT)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetIntArray((D3DXHANDLE)hConstant, pn, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetFloat(LPDEVICE pDevice, DISX_HANDLE hConstant, FLOAT f)  	{
		HRESULT hr = this->m_pD3DTextureShader->SetFloat((D3DXHANDLE)hConstant, f);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetFloatArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST FLOAT* pf, UINT Count)  	{
		if (pf == NULL || sizeof(pf) > Count* sizeof(FLOAT)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetFloatArray((D3DXHANDLE)hConstant, pf, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetVector(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_VECTOR4* pVector)  	{
		if (pVector == NULL) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetVector((D3DXHANDLE)hConstant, (const D3DXVECTOR4*)pVector);
		return HR_to_DR(hr);
	}

	DIS_RESULT SetVectorArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_VECTOR4* pVector, UINT Count) 	{
		if (pVector == NULL || sizeof(pVector) > Count* sizeof(DISX_VECTOR4)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetVectorArray((D3DXHANDLE)hConstant, (const D3DXVECTOR4*)pVector, Count);
		return HR_to_DR(hr);
	}

	DIS_RESULT SetMatrix(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix)  	{
		if (pMatrix == NULL) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetMatrix((D3DXHANDLE)hConstant, (const D3DXMATRIX*)pMatrix);
		return HR_to_DR(hr);
	}

	DIS_RESULT SetMatrixArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix, UINT Count) 	{
		if (pMatrix == NULL || sizeof(pMatrix) > Count* sizeof(DISX_MATRIX)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetMatrixArray((D3DXHANDLE)hConstant, (const D3DXMATRIX*)pMatrix, Count);
		return HR_to_DR(hr);
	}

	DIS_RESULT SetMatrixPointerArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX** ppMatrix, UINT Count)  	{
		//if (ppMatrix == NULL || sizeof(ppMatrix) > Count* sizeof((DISX_MATRIX*))) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetMatrixPointerArray((D3DXHANDLE)hConstant, (const D3DXMATRIX**)ppMatrix, Count);
		return HR_to_DR(hr);
	}

	DIS_RESULT SetMatrixTranspose(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix)  	{
		if (pMatrix == NULL) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetMatrixTranspose((D3DXHANDLE)hConstant, (const D3DXMATRIX*)pMatrix);
		return HR_to_DR(hr);
	}


	DIS_RESULT SetMatrixTransposeArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix, UINT Count)  	{
		if (pMatrix == NULL || sizeof(pMatrix) > Count* sizeof(DISX_MATRIX)) return DIS_FAIL;
		HRESULT hr = this->m_pD3DTextureShader->SetMatrixTransposeArray( (D3DXHANDLE)hConstant, (const D3DXMATRIX*)pMatrix, Count);
		return HR_to_DR(hr);
	}
	DIS_RESULT SetMatrixTransposePointerArray(LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX** ppMatrix, UINT Count)  	{
		HRESULT hr = this->m_pD3DTextureShader->SetMatrixTransposePointerArray( (D3DXHANDLE)hConstant, (const D3DXMATRIX**)ppMatrix, Count);
		return HR_to_DR(hr);
	}
};


DIS_RESULT
DISX_AssembleShaderFromFileA(
LPCSTR                          pSrcFile,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs)
{

	HRESULT hr = D3DXAssembleShaderFromFileA(pSrcFile,
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);

}

DIS_RESULT
DISX_AssembleShaderFromFileW(
LPCWSTR                         pSrcFile,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs)
{

	HRESULT hr = D3DXAssembleShaderFromFileW(pSrcFile, 
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);

}

#ifdef UNICODE
#define DISX_AssembleShaderFromFile DISX_AssembleShaderFromFileW
#else
#define DISX_AssembleShaderFromFile DISX_AssembleShaderFromFileA
#endif


DIS_RESULT
DISX_AssembleShaderFromResourceA(
HMODULE                         hSrcModule,
LPCSTR                          pSrcResource,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs)
{

	HRESULT hr = D3DXAssembleShaderFromResourceA(hSrcModule, pSrcResource,
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);

}

DIS_RESULT
DISX_AssembleShaderFromResourceW(
HMODULE                         hSrcModule,
LPCWSTR                         pSrcResource,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs)
{

	HRESULT hr = D3DXAssembleShaderFromResourceW(hSrcModule, pSrcResource,
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);

}

#ifdef UNICODE
#define DISX_AssembleShaderFromResource DISX_AssembleShaderFromResourceW
#else
#define DISX_AssembleShaderFromResource DISX_AssembleShaderFromResourceA
#endif


DIS_RESULT
DISX_AssembleShader(
LPCSTR                          pSrcData,
UINT                            SrcDataLen,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs)
{

	HRESULT hr = D3DXAssembleShader(pSrcData, SrcDataLen,
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);

}



//----------------------------------------------------------------------------
// DISX_CompileShader:
// ------------------
// Compiles a shader.
//
// Parameters:
//  pSrcFile
//      Source file name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module.
//  pSrcData
//      Pointer to source code.
//  SrcDataLen
//      Size of source code, in bytes.
//  pDefines
//      Optional NULL-terminated array of preprocessor macro definitions.
//  pInclude
//      Optional interface pointer to use for handling #include directives.
//      If this parameter is NULL, #includes will be honored when compiling
//      from file, and will error when compiling from resource or memory.
//  pFunctionName
//      Name of the entrypoint function where execution should begin.
//  pProfile
//      Instruction set to be used when generating code.  Currently supported
//      profiles are "vs_1_1", "vs_2_0", "vs_2_a", "vs_2_sw", "ps_1_1", 
//      "ps_1_2", "ps_1_3", "ps_1_4", "ps_2_0", "ps_2_a", "ps_2_sw", "tx_1_0"
//  Flags
//      See DISX_SHADER_xxx flags.
//  ppShader
//      Returns a buffer containing the created shader.  This buffer contains
//      the compiled shader code, as well as any embedded debug and symbol
//      table info.  (See DISX_GetShaderConstantTable)
//  ppErrorMsgs
//      Returns a buffer containing a listing of errors and warnings that were
//      encountered during the compile.  If you are running in a debugger,
//      these are the same messages you will see in your debug output.
//  ppConstantTable
//      Returns a IDISX_ConstantTable object which can be used to set
//      shader constants to the device.  Alternatively, an application can
//      parse the DISX_SHADER_CONSTANTTABLE block embedded as a comment within
//      the shader.
//----------------------------------------------------------------------------

DIS_RESULT
DISX_CompileShaderFromFileA(
LPCSTR                          pSrcFile,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
LPCSTR                          pFunctionName,
LPCSTR                          pProfile,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs,
LPDISX_CONSTANTTABLE*            ppConstantTable)
{

	HRESULT hr = D3DXCompileShaderFromFileA(pSrcFile,
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		pFunctionName,
		pProfile,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer,
		&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);

	return HR_to_DR(hr);

}

DIS_RESULT
DISX_CompileShaderFromFileW(
LPCWSTR                         pSrcFile,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
LPCSTR                          pFunctionName,
LPCSTR                          pProfile,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs,
LPDISX_CONSTANTTABLE*            ppConstantTable)
{

	HRESULT hr = D3DXCompileShaderFromFileW(pSrcFile,
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		pFunctionName,
		pProfile,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer,
		&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);

	return HR_to_DR(hr);

}

#ifdef UNICODE
#define DISX_CompileShaderFromFile DISX_CompileShaderFromFileW
#else
#define DISX_CompileShaderFromFile DISX_CompileShaderFromFileA
#endif


DIS_RESULT
DISX_CompileShaderFromResourceA(
HMODULE                         hSrcModule,
LPCSTR                          pSrcResource,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
LPCSTR                          pFunctionName,
LPCSTR                          pProfile,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs,
LPDISX_CONSTANTTABLE*            ppConstantTable)
{

	HRESULT hr = D3DXCompileShaderFromResourceA(hSrcModule,
		pSrcResource,
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		pFunctionName,
		pProfile,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer,
		&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);

	return HR_to_DR(hr);

}

DIS_RESULT
DISX_CompileShaderFromResourceW(
HMODULE                         hSrcModule,
LPCWSTR                         pSrcResource,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
LPCSTR                          pFunctionName,
LPCSTR                          pProfile,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs,
LPDISX_CONSTANTTABLE*            ppConstantTable)
{

	HRESULT hr = D3DXCompileShaderFromResourceW(hSrcModule,
		pSrcResource,
		(D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		pFunctionName,
		pProfile,
		Flags,
		&((D3D9_Buffer*)(*ppShader))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer,
		&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);

	return HR_to_DR(hr);

}

#ifdef UNICODE
#define DISX_CompileShaderFromResource DISX_CompileShaderFromResourceW
#else
#define DISX_CompileShaderFromResource DISX_CompileShaderFromResourceA
#endif


DIS_RESULT
DISX_CompileShader(
LPCSTR                          pSrcData,
UINT                            SrcDataLen,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
LPCSTR                          pFunctionName,
LPCSTR                          pProfile,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs,
LPDISX_CONSTANTTABLE*            ppConstantTable)
{

	LPD3DXCONSTANTTABLE pconst = NULL;


	LPD3DXBUFFER pBufShader = NULL;



	LPD3DXBUFFER pBufErrors = NULL;

	if (ppErrorMsgs == NULL || *ppErrorMsgs == NULL) pBufErrors = NULL;
	else pBufErrors = ((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer;



		HRESULT hr = D3DXCompileShader(pSrcData, 
			SrcDataLen, 
			(D3DXMACRO*)pDefines, 
			(LPD3DXINCLUDE)pInclude,
			pFunctionName, 
			pProfile,
			Flags,
			&pBufShader,
			&pBufErrors,
			&pconst);

		if (hr == S_OK)
		{
			*ppShader = new D3D9_Buffer(pBufShader, m_ResourceManager);

			//if (!ppConstantTable || *ppConstantTable == NULL)
			{
				*ppConstantTable = new D3D9_ConstantTable(m_ResourceManager);
				((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable = pconst;
			}
		}
		
		return HR_to_DR(hr);

}


//----------------------------------------------------------------------------
// DISX_DisassembleShader:
// ----------------------
// Takes a binary shader, and returns a buffer containing text assembly.
//
// Parameters:
//  pShader
//      Pointer to the shader byte code.
//  ShaderSizeInBytes
//      Size of the shader byte code in bytes.
//  EnableColorCode
//      Emit HTML tags for color coding the output?
//  pComments
//      Pointer to a comment string to include at the top of the shader.
//  ppDisassembly
//      Returns a buffer containing the disassembled shader.
//----------------------------------------------------------------------------

DIS_RESULT
DISX_DisassembleShader(
CONST DWORD*                    pShader,
BOOL                            EnableColorCode,
LPCSTR                          pComments,
LPBUFFER*                   ppDisassembly)
{
	HRESULT hr= D3DXDisassembleShader(pShader, EnableColorCode, pComments, &((D3D9_Buffer*)(*ppDisassembly))->pd3dBuffer);
	return HR_to_DR(hr);
}


//----------------------------------------------------------------------------
// DISX_GetPixelShaderProfile/DISX_GetVertexShaderProfile:
// -----------------------------------------------------
// Returns the name of the HLSL profile best suited to a given device.
//
// Parameters:
//  pDevice
//      Pointer to the device in question
//----------------------------------------------------------------------------

LPCSTR
DISX_GetPixelShaderProfile(
LPDEVICE               pDevice)
{
	return D3DXGetPixelShaderProfile(*GetDeviceD3D());

}

LPCSTR
DISX_GetVertexShaderProfile(
LPDEVICE pDevice)
{

	return D3DXGetVertexShaderProfile(*GetDeviceD3D());
}


//----------------------------------------------------------------------------
// DISX_FindShaderComment:
// ----------------------
// Searches through a shader for a particular comment, denoted by a FourCC in
// the first DWORD of the comment.  If the comment is not found, and no other
// error has occurred, S_FALSE is returned.
//
// Parameters:
//  pFunction
//      Pointer to the function DWORD stream
//  FourCC
//      FourCC used to identify the desired comment block.
//  ppData
//      Returns a pointer to the comment data (not including comment token
//      and FourCC).  Can be NULL.
//  pSizeInBytes
//      Returns the size of the comment data in bytes.  Can be NULL.
//----------------------------------------------------------------------------

DIS_RESULT
DISX_FindShaderComment(
CONST DWORD*                    pFunction,
DWORD                           FourCC,
LPCVOID*                        ppData,
UINT*                           pSizeInBytes)
{



	HRESULT hr = D3DXFindShaderComment(pFunction, FourCC,ppData,pSizeInBytes);


	return HR_to_DR(hr);

}


//----------------------------------------------------------------------------
// DISX_GetShaderSize:
// ------------------
// Returns the size of the shader byte-code, in bytes.
//
// Parameters:
//  pFunction
//      Pointer to the function DWORD stream
//----------------------------------------------------------------------------

UINT
DISX_GetShaderSize(
CONST DWORD*                    pFunction)
{



	HRESULT hr = D3DXGetShaderSize(pFunction);


	return HR_to_DR(hr);

}


//----------------------------------------------------------------------------
// DISX_GetShaderVersion:
// -----------------------
// Returns the shader version of a given shader.  Returns zero if the shader 
// function is NULL.
//
// Parameters:
//  pFunction
//      Pointer to the function DWORD stream
//----------------------------------------------------------------------------

DWORD
DISX_GetShaderVersion(
CONST DWORD*                    pFunction)
{
	


		HRESULT hr = D3DXGetShaderVersion(pFunction);


		return HR_to_DR(hr);
	
}

//----------------------------------------------------------------------------
// DISX_GetShaderSemantics:
// -----------------------
// Gets semantics for all input elements referenced inside a given shader.
//
// Parameters:
//  pFunction
//      Pointer to the function DWORD stream
//  pSemantics
//      Pointer to an array of DISX_SEMANTIC structures.  The function will
//      fill this array with the semantics for each input element referenced
//      inside the shader.  This array is assumed to contain at least
//      MAXD3DDECLLENGTH elements.
//  pCount
//      Returns the number of elements referenced by the shader
//----------------------------------------------------------------------------

DIS_RESULT
DISX_GetShaderInputSemantics(
CONST DWORD*                    pFunction,
DISX_SEMANTIC*                   pSemantics,
UINT*                           pCount)
{
	D3DXSEMANTIC sem;

	HRESULT hr = D3DXGetShaderInputSemantics(pFunction, &sem, pCount);
	//&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);

	if (hr != S_OK)return DIS_FAIL;

	pSemantics->Usage = sem.Usage;
	pSemantics->UsageIndex = sem.UsageIndex;

	return HR_to_DR(hr);
}

DIS_RESULT
DISX_GetShaderOutputSemantics(
CONST DWORD*                    pFunction,
DISX_SEMANTIC*                   pSemantics,
UINT*                           pCount)
{
	D3DXSEMANTIC sem;
	
	HRESULT hr = D3DXGetShaderOutputSemantics(pFunction, &sem, pCount);
	//&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);

	if (hr != S_OK)return DIS_FAIL;

	pSemantics->Usage = sem.Usage;
	pSemantics->UsageIndex = sem.UsageIndex;

	return HR_to_DR(hr);
}


//----------------------------------------------------------------------------
// DISX_GetShaderSamplers:
// ----------------------
// Gets semantics for all input elements referenced inside a given shader.
//
// pFunction
//      Pointer to the function DWORD stream
// pSamplers
//      Pointer to an array of LPCSTRs.  The function will fill this array
//      with pointers to the sampler names contained within pFunction, for
//      each sampler referenced inside the shader.  This array is assumed to
//      contain at least 16 elements.
// pCount
//      Returns the number of samplers referenced by the shader
//----------------------------------------------------------------------------

DIS_RESULT
DISX_GetShaderSamplers(
CONST DWORD*                    pFunction,
LPCSTR*                         pSamplers,
UINT*                           pCount)
{
	HRESULT hr = D3DXGetShaderSamplers(pFunction, pSamplers, pCount);
		//&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);


	return HR_to_DR(hr);
}


//----------------------------------------------------------------------------
// DISX_GetShaderConstantTable:
// ---------------------------
// Gets shader constant table embedded inside shader.  A constant table is
// generated by DISX_AssembleShader and DISX_CompileShader, and is embedded in
// the body of the shader.
//
// Parameters:
//  pFunction
//      Pointer to the function DWORD stream
//  Flags
//      See DISX_CONSTTABLE_xxx
//  ppConstantTable
//      Returns a IDISX_ConstantTable object which can be used to set
//      shader constants to the device.  Alternatively, an application can
//      parse the DISX_SHADER_CONSTANTTABLE block embedded as a comment within
//      the shader.
//----------------------------------------------------------------------------

DIS_RESULT
DISX_GetShaderConstantTable(
CONST DWORD*                    pFunction,
LPDISX_CONSTANTTABLE*            ppConstantTable)
{
	HRESULT hr = D3DXGetShaderConstantTable(pFunction, 
		&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);


	return HR_to_DR(hr);
}

DIS_RESULT
DISX_GetShaderConstantTableEx(
CONST DWORD*                    pFunction,
DWORD                           Flags,
LPDISX_CONSTANTTABLE*            ppConstantTable)
{
	HRESULT hr = D3DXGetShaderConstantTableEx(pFunction, Flags,
		&((D3D9_ConstantTable*)(*ppConstantTable))->m_pD3DConstantTable);


	return HR_to_DR(hr);
}



//----------------------------------------------------------------------------
// DISX_CreateTextureShader:
// ------------------------
// Creates a texture shader object, given the compiled shader.
//
// Parameters
//  pFunction
//      Pointer to the function DWORD stream
//  ppTextureShader
//      Returns a IDISX_TextureShader object which can be used to procedurally 
//      fill the contents of a texture using the DISX_FillTextureTX functions.
//----------------------------------------------------------------------------

DIS_RESULT
DISX_CreateTextureShader(
CONST DWORD*                    pFunction,
LPDISX_TEXTURESHADER*            ppTextureShader)
{
	HRESULT hr = D3DXCreateTextureShader(pFunction,
		&((D3D9_TextureShader*)(*ppTextureShader))->m_pD3DTextureShader);


	return HR_to_DR(hr);
}


//----------------------------------------------------------------------------
// DISX_PreprocessShader:
// ---------------------
// Runs the preprocessor on the specified shader or effect, but does
// not actually compile it.  This is useful for evaluating the #includes
// and #defines in a shader and then emitting a reformatted token stream
// for debugging purposes or for generating a self-contained shader.
//
// Parameters:
//  pSrcFile
//      Source file name
//  hSrcModule
//      Module handle. if NULL, current module will be used
//  pSrcResource
//      Resource name in module
//  pSrcData
//      Pointer to source code
//  SrcDataLen
//      Size of source code, in bytes
//  pDefines
//      Optional NULL-terminated array of preprocessor macro definitions.
//  pInclude
//      Optional interface pointer to use for handling #include directives.
//      If this parameter is NULL, #includes will be honored when assembling
//      from file, and will error when assembling from resource or memory.
//  ppShaderText
//      Returns a buffer containing a single large string that represents
//      the resulting formatted token stream
//  ppErrorMsgs
//      Returns a buffer containing a listing of errors and warnings that were
//      encountered during assembly.  If you are running in a debugger,
//      these are the same messages you will see in your debug output.
//----------------------------------------------------------------------------

DIS_RESULT
DISX_PreprocessShaderFromFileA(
LPCSTR                       pSrcFile,
CONST DISX_MACRO*             pDefines,
LPDISX_INCLUDE                pInclude,
LPBUFFER*                ppShaderText,
LPBUFFER*                ppErrorMsgs)
{
	HRESULT hr = D3DXPreprocessShaderFromFileA(pSrcFile,
		(const D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		&((D3D9_Buffer*)(*ppShaderText))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);
}

DIS_RESULT
DISX_PreprocessShaderFromFileW(
LPCWSTR                      pSrcFile,
CONST DISX_MACRO*             pDefines,
LPDISX_INCLUDE                pInclude,
LPBUFFER*                ppShaderText,
LPBUFFER*                ppErrorMsgs)
{
	HRESULT hr = D3DXPreprocessShaderFromFileW(pSrcFile,
		(const D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		&((D3D9_Buffer*)(*ppShaderText))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);
}

#ifdef UNICODE
#define DISX_PreprocessShaderFromFile DISX_PreprocessShaderFromFileW
#else
#define DISX_PreprocessShaderFromFile DISX_PreprocessShaderFromFileA
#endif

DIS_RESULT
DISX_PreprocessShaderFromResourceA(
HMODULE                      hSrcModule,
LPCSTR                       pSrcResource,
CONST DISX_MACRO*             pDefines,
LPDISX_INCLUDE                pInclude,
LPBUFFER*                ppShaderText,
LPBUFFER*                ppErrorMsgs)
{
	HRESULT hr = D3DXPreprocessShaderFromResourceA(hSrcModule,
		pSrcResource,
		(const D3DXMACRO*)pDefines,
		(LPD3DXINCLUDE)pInclude,
		&((D3D9_Buffer*)(*ppShaderText))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);
}

DIS_RESULT
DISX_PreprocessShaderFromResourceW(
HMODULE                      hSrcModule,
LPCWSTR                      pSrcResource,
CONST DISX_MACRO*             pDefines,
LPDISX_INCLUDE                pInclude,
LPBUFFER*                ppShaderText,
LPBUFFER*                ppErrorMsgs)
{
	HRESULT hr = D3DXPreprocessShaderFromResourceW(hSrcModule, 
		pSrcResource,
		(const D3DXMACRO*)pDefines, 
		(LPD3DXINCLUDE)pInclude,
		&((D3D9_Buffer*)(*ppShaderText))->pd3dBuffer,
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);
}

#ifdef UNICODE
#define DISX_PreprocessShaderFromResource DISX_PreprocessShaderFromResourceW
#else
#define DISX_PreprocessShaderFromResource DISX_PreprocessShaderFromResourceA
#endif

DIS_RESULT
DISX_PreprocessShader(
LPCSTR                       pSrcData,
UINT                         SrcDataSize,
CONST DISX_MACRO*             pDefines,
LPDISX_INCLUDE                pInclude,
LPBUFFER*                ppShaderText,
LPBUFFER*                ppErrorMsgs)
{
	HRESULT hr =D3DXPreprocessShader(pSrcData, 
		SrcDataSize, (D3DXMACRO*)pDefines, 
		(LPD3DXINCLUDE)pInclude, 
		&((D3D9_Buffer*)(*ppShaderText))->pd3dBuffer, 
		&((D3D9_Buffer*)(*ppErrorMsgs))->pd3dBuffer);

	return HR_to_DR(hr);
}


/*

class DISX_Include
{
public:

	virtual DIS_RESULT Open(DISX_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) = 0;
	virtual DIS_RESULT Close(LPCVOID pData) = 0;
};

*/

//----------------------------------------------------------------------------------
//	Global instances 
//  State Management Objects
//  These are created and destroyed by the D3D_Interface class
//----------------------------------------------------------------------------------
BlendState*						blendState = NULL;
RasterState*					rasterState = NULL;
StencilState*					sState = NULL;
ValueState*						valueState = NULL;
FillModeState*					fillState = NULL;
ShadeModeState*					shadeState = NULL;
FixedState*						fixedState = NULL;
FogModeState*					fogModeState = NULL;
PatchDegreeState*				patchDegreeState = NULL;
CompareFuncState*				compareFuncState = NULL;
PatchEdgeState*					patchEdgeState = NULL;
VertexBlendState*				vertBlendState = NULL;
MaterialColorSourceState*		materialColorSourceState= NULL;

// These objects are global by design because 
// a) they are defined in this .cpp file, but hidden from the .h file.
// b) the big D3D_DeviceInterface class does not derive a subclass
// to avoid Virtual function call overheads and so it cannot contain them
// as members
// c) they must exist to serve the "Get()" requests on the Device because
// the objects exposed to the user are pointers to the abstract types, and 
// the Get request would require creation of an object when given a null pointer
D3D9_SwapChain				SwapChainWrapperForGetFunc;
D3D9_VertexDecleration		VertexDeclerationWrapperForGetFunc;
D3D9_StateBlock				StateBlockWrapperForGetFunc;
D3D9_Query					QueryWrapperForGetFunc;
D3D9_PixelShader			PixelShaderForGetFunc;
D3D9_VertexShader			VertexShaderForGetFunc;
D3D9_IndexBuffer			IndexBufferForGetFunc;
D3D9_VertexBuffer			VertexBufferForGetFunc;
D3D9_VolumeTexture			VolumeTextureForGetFunc;
D3D9_CubeTexture2D			CubeTextureForGetFunc;
D3D9_Texture2D				Texture2DForGetFunc;

const unsigned int MAX_NUM_RENDERTARGETS = 40;
class D3D9_Surface2D_GetterManager : public InternalMemoryManager
{
public:
	D3D9_Surface2D_GetterManager()
	{
		for (int i = 0; i < MAX_NUM_RENDERTARGETS; i++)
		{
			mGetter[i] = new D3D9_Surface2D_Getter();
			mGetter[i]->m_resourceManager = m_ResourceManager;
			mGetter[i]->pd3dSurface = NULL;
			mGetter[i]->m_memMan = this;
		}
		count = -1;
	
	}
	~D3D9_Surface2D_GetterManager()
	{
		for (int i = 0; i < MAX_NUM_RENDERTARGETS; i++)
		{
			delete mGetter[i];
		}
	}

	LPDIRECT3DSURFACE9 GetSurface(){
		if (count >= 0 && count < MAX_NUM_RENDERTARGETS)
		{
			return mGetter[count]->pd3dSurface;
		}
		else return NULL;
	}

	DIS_RESULT SetGetter(LPDIRECT3DSURFACE9 pSurf)
	{
		AddRef();
		if (count >= 0 && count < MAX_NUM_RENDERTARGETS)
		{
			mGetter[count]->pd3dSurface = pSurf;
			return DIS_OK;
		}
		else return DIS_RESULT::DIS_ERR_OUTOFVIDEOMEMORY;
	}

	D3D9_Surface2D_Getter* GetGetter()
	{
		if (count >= 0 && count < MAX_NUM_RENDERTARGETS)
		{
			return mGetter[count];
		}
		else return NULL;
	}

	void AddRef()
	{
		count++;
	}

	void Release() // need to re-lease the surface
	{
		mGetter[count]->Release();
		count--;
	}

	void Remove(DIS_Resource *res)
	{
		for (int i = 0; i <= count; i++)
		{
			if (mGetter[i] == res)
			{
				shuffleDownToVal(i);
			}
		}
		count--; 
	}

private:

	void shuffleDownToVal(int i)
	{
		if (i >= 0 && i <= count && count < MAX_NUM_RENDERTARGETS)
		{
			int x = i + 1;
			if (x > 0 && x <= count)
			{
				D3D9_Surface2D_Getter* temp = mGetter[i];
				
				for (int j = x; j < MAX_NUM_RENDERTARGETS; j++)
				{
					mGetter[j - 1] = mGetter[j];
				}

				mGetter[MAX_NUM_RENDERTARGETS - 1] = temp;
			}
		}
	}

	D3D9_Surface2D_Getter* mGetter[MAX_NUM_RENDERTARGETS];
	int count;

};
D3D9_Surface2D_Getter				Surface2DFrontBufferForGetFunc;
D3D9_Surface2D_Getter				Surface2DDepthStencilForGetFunc;
D3D9_Surface2D_Getter				Surface2DBackBufferForGetFunc;
//D3D9_Surface2D_Getter				Surface2DRenderTargetForGetFunc;
D3D9_BaseTexture			BaseTextureForGetFunc[8]; // up to 8 loaded

D3D9_Surface2D_GetterManager   Surface2DRenderTargetForGetFunc;
// The Device
LPDIRECT3DDEVICE9 pD3DDevice;




LPDIRECT3DDEVICE9* GetDeviceD3D()
{
	return &pD3DDevice;
}





//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
D3D_DeviceInterface::D3D_DeviceInterface()
{
	DIS_Backbuffer_type[0] = D3DBACKBUFFER_TYPE_MONO;
	DIS_Backbuffer_type[1] = D3DBACKBUFFER_TYPE_LEFT;
	DIS_Backbuffer_type[2] = D3DBACKBUFFER_TYPE_RIGHT;

	DIS_Subdiv_type[0] = D3DBASIS_BEZIER;
	DIS_Subdiv_type[1] = D3DBASIS_BSPLINE;
	DIS_Subdiv_type[2] = D3DBASIS_CATMULL_ROM;

	DIS_Blend_Func[0] = D3DBLEND_ZERO;
	DIS_Blend_Func[1] = D3DBLEND_ZERO;
	DIS_Blend_Func[2] = D3DBLEND_ONE;
	DIS_Blend_Func[3] = D3DBLEND_SRCCOLOR;
	DIS_Blend_Func[4] = D3DBLEND_INVSRCCOLOR;
	DIS_Blend_Func[5] = D3DBLEND_SRCALPHA;
	DIS_Blend_Func[6] = D3DBLEND_INVSRCALPHA;
	DIS_Blend_Func[7] = D3DBLEND_DESTALPHA;
	DIS_Blend_Func[8] = D3DBLEND_INVDESTALPHA;
	DIS_Blend_Func[9] = D3DBLEND_DESTCOLOR;
	DIS_Blend_Func[10] = D3DBLEND_INVDESTCOLOR;
	DIS_Blend_Func[11] = D3DBLEND_SRCALPHASAT;
	DIS_Blend_Func[12] = D3DBLEND_BOTHSRCALPHA;
	DIS_Blend_Func[13] = D3DBLEND_BOTHINVSRCALPHA;
	DIS_Blend_Func[14] = D3DBLEND_BLENDFACTOR;
	DIS_Blend_Func[15] = D3DBLEND_INVBLENDFACTOR;
	DIS_Blend_Func[16] = D3DBLEND_SRCCOLOR2;
	DIS_Blend_Func[17] = D3DBLEND_INVSRCCOLOR2;

	DIS_BlendOp[0] = D3DBLENDOP_ADD;
	DIS_BlendOp[1] = D3DBLENDOP_ADD;
	DIS_BlendOp[2] = D3DBLENDOP_SUBTRACT;
	DIS_BlendOp[3] = D3DBLENDOP_REVSUBTRACT;
	DIS_BlendOp[4] = D3DBLENDOP_MIN;
	DIS_BlendOp[5] = D3DBLENDOP_MAX;

	DIS_CmpFunc[0] = D3DCMP_NEVER;
	DIS_CmpFunc[1] = D3DCMP_NEVER;
	DIS_CmpFunc[2] = D3DCMP_LESS;
	DIS_CmpFunc[3] = D3DCMP_EQUAL;
	DIS_CmpFunc[4] = D3DCMP_LESSEQUAL;
	DIS_CmpFunc[5] = D3DCMP_GREATER;
	DIS_CmpFunc[6] = D3DCMP_NOTEQUAL;
	DIS_CmpFunc[7] = D3DCMP_GREATEREQUAL;
	DIS_CmpFunc[8] = D3DCMP_ALWAYS;

	DIS_ComposerOp[0] = D3DCOMPOSERECTS_COPY;
	DIS_ComposerOp[1] = D3DCOMPOSERECTS_COPY;
	DIS_ComposerOp[2] = D3DCOMPOSERECTS_OR;
	DIS_ComposerOp[3] = D3DCOMPOSERECTS_AND;
	DIS_ComposerOp[4] = D3DCOMPOSERECTS_NEG ;

	DIS_CubemapFace[0] = D3DCUBEMAP_FACE_POSITIVE_X;//   = 0,
	DIS_CubemapFace[1] = D3DCUBEMAP_FACE_NEGATIVE_X;//   = 1,
	DIS_CubemapFace[2] = D3DCUBEMAP_FACE_POSITIVE_Y;//   = 2,
	DIS_CubemapFace[3] = D3DCUBEMAP_FACE_NEGATIVE_Y;//   = 3,
	DIS_CubemapFace[4] = D3DCUBEMAP_FACE_POSITIVE_Z;//   = 4,
	DIS_CubemapFace[5] = D3DCUBEMAP_FACE_NEGATIVE_Z;//   = 5
	
	DIS_Cullmode[0] = D3DCULL_NONE;
	DIS_Cullmode[1] = D3DCULL_NONE;
	DIS_Cullmode[2] = D3DCULL_CW;
	DIS_Cullmode[3] = D3DCULL_CCW;

	DIS_DebugMonitor[0] = D3DDMT_ENABLE;
	DIS_DebugMonitor[2] = D3DDMT_DISABLE;

	DIS_DeclMethod[0] = D3DDECLMETHOD_DEFAULT;
	DIS_DeclMethod[1] = D3DDECLMETHOD_PARTIALU;
	DIS_DeclMethod[2] = D3DDECLMETHOD_PARTIALV;
	DIS_DeclMethod[3] = D3DDECLMETHOD_CROSSUV;
	DIS_DeclMethod[4] = D3DDECLMETHOD_UV;
	DIS_DeclMethod[5] = D3DDECLMETHOD_LOOKUP;
	DIS_DeclMethod[6] = D3DDECLMETHOD_LOOKUPPRESAMPLED;
	
	DIS_DeclType[0] =D3DDECLTYPE_FLOAT1     ;// 0,
	DIS_DeclType[1] =D3DDECLTYPE_FLOAT2     ;// 1,
	DIS_DeclType[2] =D3DDECLTYPE_FLOAT3     ;// 2,
	DIS_DeclType[3] =D3DDECLTYPE_FLOAT4     ;// 3,
	DIS_DeclType[4] =D3DDECLTYPE_D3DCOLOR   ;// 4,
	DIS_DeclType[5] =D3DDECLTYPE_UBYTE4     ;// 5,
	DIS_DeclType[6] =D3DDECLTYPE_SHORT2     ;// 6,
	DIS_DeclType[7] =D3DDECLTYPE_SHORT4     ;// 7,
	DIS_DeclType[8] =D3DDECLTYPE_UBYTE4N    ;// 8,
	DIS_DeclType[9] =D3DDECLTYPE_SHORT2N    ;// 9,
	DIS_DeclType[10] =D3DDECLTYPE_SHORT4N    ;// 10,
	DIS_DeclType[11] =D3DDECLTYPE_USHORT2N   ;// 11,
	DIS_DeclType[12] =D3DDECLTYPE_USHORT4N   ;// 12,
	DIS_DeclType[13] =D3DDECLTYPE_UDEC3      ;// 13,
	DIS_DeclType[14] =D3DDECLTYPE_DEC3N      ;// 14,
	DIS_DeclType[15] =D3DDECLTYPE_FLOAT16_2  ;// 15,
	DIS_DeclType[16] =D3DDECLTYPE_FLOAT16_4  ;// 16,
	DIS_DeclType[17] =D3DDECLTYPE_UNUSED     ;// 17
 
	DIS_DeclUsage[0] = D3DDECLUSAGE_POSITION      ;// 0,
	DIS_DeclUsage[1] = D3DDECLUSAGE_BLENDWEIGHT   ;// 1,
	DIS_DeclUsage[2] = D3DDECLUSAGE_BLENDINDICES  ;// 2,
	DIS_DeclUsage[3] = D3DDECLUSAGE_NORMAL        ;// 3,
	DIS_DeclUsage[4] = D3DDECLUSAGE_PSIZE         ;// 4,
	DIS_DeclUsage[5] = D3DDECLUSAGE_TEXCOORD      ;// 5,
	DIS_DeclUsage[6] = D3DDECLUSAGE_TANGENT       ;// 6,
	DIS_DeclUsage[7] = D3DDECLUSAGE_BINORMAL      ;// 7,
	DIS_DeclUsage[8] = D3DDECLUSAGE_TESSFACTOR    ;// 8,
	DIS_DeclUsage[9] = D3DDECLUSAGE_POSITIONT     ;// 9,
	DIS_DeclUsage[10] = D3DDECLUSAGE_COLOR         ;// 10,
	DIS_DeclUsage[11] = D3DDECLUSAGE_FOG           ;// 11,
	DIS_DeclUsage[12] = D3DDECLUSAGE_DEPTH         ;// 12,
	DIS_DeclUsage[13] = D3DDECLUSAGE_SAMPLE        ;// 13

	DIS_DegreeType[0] = D3DDEGREE_LINEAR     ;// 0,
	DIS_DegreeType[1] = D3DDEGREE_LINEAR     ;// 1,
	DIS_DegreeType[2] = D3DDEGREE_QUADRATIC  ;// 2,
	DIS_DegreeType[3] = D3DDEGREE_CUBIC      ;// 3,
	DIS_DegreeType[4] = D3DDEGREE_QUINTIC    ;// 4,
	
	DIS_DeviceType[0]=D3DDEVTYPE_HAL;// 0,
	DIS_DeviceType[1]=D3DDEVTYPE_HAL;// 1,
	DIS_DeviceType[2]=D3DDEVTYPE_NULLREF;// 2,
	DIS_DeviceType[3]=D3DDEVTYPE_REF          ;// 3,
	DIS_DeviceType[4]=D3DDEVTYPE_SW           ;// 4,

	DIS_DisplayRot[0]=D3DDISPLAYROTATION_IDENTITY;// 0,
	DIS_DisplayRot[1]=D3DDISPLAYROTATION_IDENTITY  ;// 1,
	DIS_DisplayRot[2]=D3DDISPLAYROTATION_90        ;// 2,
	DIS_DisplayRot[3]=D3DDISPLAYROTATION_180       ;// 3,
	DIS_DisplayRot[4]=D3DDISPLAYROTATION_270       ;// 4

	DIS_FillMode[0]=D3DFILL_SOLID;// 0,
	DIS_FillMode[1]=D3DFILL_POINT        ;// 1,
	DIS_FillMode[2]=D3DFILL_WIREFRAME    ;// 2,
	DIS_FillMode[3]=D3DFILL_SOLID        ;// 3,

	DIS_FogMode[0] = D3DFOG_NONE         ;// 0,
	DIS_FogMode[1] = D3DFOG_EXP          ;// 1,
	DIS_FogMode[2] = D3DFOG_EXP2         ;// 2,
	DIS_FogMode[3] = D3DFOG_LINEAR       ;// 3,	
	
    DIS_Format[0] = D3DFMT_UNKNOWN              ;////  0;//
    DIS_Format[1] = D3DFMT_R8G8B8               ;//// 20;//
    DIS_Format[2] = D3DFMT_A8R8G8B8             ;//// 21;//
    DIS_Format[3] = D3DFMT_X8R8G8B8             ;//// 22;//
    DIS_Format[4] = D3DFMT_R5G6B5               ;//// 23;//
    DIS_Format[5] = D3DFMT_X1R5G5B5             ;//// 24;//
    DIS_Format[6] = D3DFMT_A1R5G5B5             ;//// 25;//
    DIS_Format[7] = D3DFMT_A4R4G4B4             ;//// 26;//
    DIS_Format[8] = D3DFMT_R3G3B2               ;//// 27;//
    DIS_Format[9] = D3DFMT_A8                   ;//// 28;//
    DIS_Format[10] = D3DFMT_A8R3G3B2             ;//// 29;//
    DIS_Format[11] = D3DFMT_X4R4G4B4             ;//// 30;//
    DIS_Format[12] = D3DFMT_A2B10G10R10          ;//// 31;//
    DIS_Format[13] = D3DFMT_A8B8G8R8             ;//// 32;//
    DIS_Format[14] = D3DFMT_X8B8G8R8             ;//// 33;//
    DIS_Format[15] = D3DFMT_G16R16               ;//// 34;//
    DIS_Format[16] = D3DFMT_A2R10G10B10          ;//// 35;//
    DIS_Format[17] = D3DFMT_A16B16G16R16         ;//// 36;//
    DIS_Format[18] = D3DFMT_A8P8                 ;//// 40;//
    DIS_Format[19] = D3DFMT_P8                   ;//// 41;//
    DIS_Format[20] = D3DFMT_L8                   ;//// 50;//
    DIS_Format[21] = D3DFMT_A8L8                 ;//// 51;//
    DIS_Format[22] = D3DFMT_A4L4                 ;//// 52;//
    DIS_Format[23] = D3DFMT_V8U8                 ;//// 60;//
    DIS_Format[24] = D3DFMT_L6V5U5               ;//// 61;//
    DIS_Format[25] = D3DFMT_X8L8V8U8             ;//// 62;//
    DIS_Format[26] = D3DFMT_Q8W8V8U8             ;//// 63;//
    DIS_Format[27] = D3DFMT_V16U16               ;//// 64;//
    DIS_Format[28] = D3DFMT_A2W10V10U10          ;//// 67;//
    DIS_Format[29] = D3DFMT_UYVY                 ;//// MAKEFOURCC('U';// 'Y';// 'V';// 'Y');//
    DIS_Format[30] = D3DFMT_R8G8_B8G8            ;//// MAKEFOURCC('R';// 'G';// 'B';// 'G');//
    DIS_Format[31] = D3DFMT_YUY2                 ;//// MAKEFOURCC('Y';// 'U';// 'Y';// '2');//
    DIS_Format[32] = D3DFMT_G8R8_G8B8            ;//// MAKEFOURCC('G';// 'R';// 'G';// 'B');//
    DIS_Format[33] = D3DFMT_DXT1                 ;//// MAKEFOURCC('D';// 'X';// 'T';// '1');//
    DIS_Format[34] = D3DFMT_DXT2                 ;//// MAKEFOURCC('D';// 'X';// 'T';// '2');//
    DIS_Format[35] = D3DFMT_DXT3                 ;//// MAKEFOURCC('D';// 'X';// 'T';// '3');//
    DIS_Format[36] = D3DFMT_DXT4                 ;//// MAKEFOURCC('D';// 'X';// 'T';// '4');//
    DIS_Format[37] = D3DFMT_DXT5                 ;//// MAKEFOURCC('D';// 'X';// 'T';// '5');//
    DIS_Format[38] = D3DFMT_D16_LOCKABLE         ;//// 70;//
    DIS_Format[39] = D3DFMT_D32                  ;//// 71;//
    DIS_Format[40] = D3DFMT_D15S1                ;//// 73;//
    DIS_Format[41] = D3DFMT_D24S8                ;//// 75;//
    DIS_Format[42] = D3DFMT_D24X8                ;//// 77;//
    DIS_Format[43] = D3DFMT_D24X4S4              ;//// 79;//
    DIS_Format[44] = D3DFMT_D16                  ;//// 80;//
    DIS_Format[45] = D3DFMT_D32F_LOCKABLE        ;//// 82;//
    DIS_Format[46] = D3DFMT_D24FS8               ;//// 83;//
    DIS_Format[47] = D3DFMT_L16                  ;//// 81;//
    DIS_Format[48] = D3DFMT_VERTEXDATA           ;////100;//
    DIS_Format[49] = D3DFMT_INDEX16              ;////101;//
    DIS_Format[50] = D3DFMT_INDEX32              ;////102;//
    DIS_Format[51] = D3DFMT_Q16W16V16U16         ;////110;//
    DIS_Format[52] = D3DFMT_MULTI2_ARGB8         ;//// MAKEFOURCC('M';//'E';//'T';//'1');//
    DIS_Format[53] = D3DFMT_R16F                 ;//// 111;//
    DIS_Format[54] = D3DFMT_G16R16F              ;//// 112;//
    DIS_Format[55] = D3DFMT_A16B16G16R16F        ;//// 113;//
    DIS_Format[56] = D3DFMT_R32F                 ;//// 114;//
    DIS_Format[57] = D3DFMT_G32R32F              ;//// 115;//
    DIS_Format[58] = D3DFMT_A32B32G32R32F        ;//// 116;//
    DIS_Format[59] = D3DFMT_CxV8U8               ;//// 117;//
//#if !defined(DIS_Format[] = D3D_DISABLE_9EX)
    DIS_Format[60] = D3DFMT_D32_LOCKABLE         ;//// 84;//
    DIS_Format[61] = D3DFMT_S8_LOCKABLE          ;//// 85;//
    DIS_Format[62] = D3DFMT_A1                   ;//// 118;//
    DIS_Format[63] = D3DFMT_A2B10G10R10_XR_BIAS  ;//// 119;//
    DIS_Format[64] = D3DFMT_BINARYBUFFER         ;//// 199;//

	DIS_LightType[0]=D3DLIGHT_POINT		;// 0,
	DIS_LightType[1]=D3DLIGHT_POINT        ;// 1,
	DIS_LightType[2]=D3DLIGHT_SPOT         ;// 2,
	DIS_LightType[3]=D3DLIGHT_DIRECTIONAL  ;// 3,
	DIS_LightType[4]=D3DLIGHT_POINT;//D3DLIGHT_AREA_POINT		;// 4,
	DIS_LightType[5]=D3DLIGHT_POINT;//D3DLIGHT_AREA_SPOT ;// 5,
	DIS_LightType[6]=D3DLIGHT_POINT;//D3DLIGHT_VOLUME		;// 6,
	
	DIS_MaterialColorSource[0]=D3DMCS_MATERIAL;//     = 0,
	DIS_MaterialColorSource[1]=D3DMCS_COLOR1;//       = 1,
	DIS_MaterialColorSource[2]=D3DMCS_COLOR2;//       = 2,
	
	DIS_MultiSampleType[0] = D3DMULTISAMPLE_NONE          ;// 0,
	DIS_MultiSampleType[1] = D3DMULTISAMPLE_NONMASKABLE   ;// 1,
	DIS_MultiSampleType[2] = D3DMULTISAMPLE_2_SAMPLES     ;// 2,
	DIS_MultiSampleType[3] = D3DMULTISAMPLE_3_SAMPLES     ;// 3,
	DIS_MultiSampleType[4] = D3DMULTISAMPLE_4_SAMPLES     ;// 4,
	DIS_MultiSampleType[5] = D3DMULTISAMPLE_5_SAMPLES     ;// 5,
	DIS_MultiSampleType[6] = D3DMULTISAMPLE_6_SAMPLES     ;// 6,
	DIS_MultiSampleType[7] = D3DMULTISAMPLE_7_SAMPLES     ;// 7,
	DIS_MultiSampleType[8] = D3DMULTISAMPLE_8_SAMPLES     ;// 8,
	DIS_MultiSampleType[9] = D3DMULTISAMPLE_9_SAMPLES     ;// 9,
	DIS_MultiSampleType[10] = D3DMULTISAMPLE_10_SAMPLES    ;// 10,
	DIS_MultiSampleType[11] = D3DMULTISAMPLE_11_SAMPLES    ;// 11,
	DIS_MultiSampleType[12] = D3DMULTISAMPLE_12_SAMPLES    ;// 12,
	DIS_MultiSampleType[13] = D3DMULTISAMPLE_13_SAMPLES    ;// 13,
	DIS_MultiSampleType[14] = D3DMULTISAMPLE_14_SAMPLES    ;// 14,
	DIS_MultiSampleType[15] = D3DMULTISAMPLE_15_SAMPLES    ;// 15,
	DIS_MultiSampleType[16] = D3DMULTISAMPLE_16_SAMPLES    ;// 16,
	
	DIS_PatchEdgeStyle[0] = D3DPATCHEDGE_DISCRETE;//     = 0,
	DIS_PatchEdgeStyle[1] = D3DPATCHEDGE_CONTINUOUS;//   = 1,
	
	DIS_Pool[0] = D3DPOOL_DEFAULT;//      = 0,
	DIS_Pool[1] = D3DPOOL_MANAGED;//      = 1,
	DIS_Pool[2] = D3DPOOL_SYSTEMMEM;//    = 2,
	DIS_Pool[3] = D3DPOOL_SCRATCH; //     = 3,

	DIS_PrimitiveType[0]=D3DPT_POINTLIST  ;// 0,
	DIS_PrimitiveType[1]=D3DPT_POINTLIST      ;// 1,
	DIS_PrimitiveType[2]=D3DPT_LINELIST       ;// 2,
	DIS_PrimitiveType[3]=D3DPT_LINESTRIP      ;// 3,
	DIS_PrimitiveType[4]=D3DPT_TRIANGLELIST   ;// 4,
	DIS_PrimitiveType[5]=D3DPT_TRIANGLESTRIP  ;// 5,
	DIS_PrimitiveType[6]=D3DPT_TRIANGLEFAN    ;// 6,

	DIS_QueryType[0] = D3DQUERYTYPE_VCACHE ;// 0,
	DIS_QueryType[1] = D3DQUERYTYPE_VCACHE             ;// 1,
	DIS_QueryType[2] = D3DQUERYTYPE_RESOURCEMANAGER    ;// 2,
	DIS_QueryType[3] = D3DQUERYTYPE_VERTEXSTATS        ;// 3,
	DIS_QueryType[4] = D3DQUERYTYPE_EVENT              ;// 4,
	DIS_QueryType[5] = D3DQUERYTYPE_OCCLUSION          ;// 5,
	DIS_QueryType[6] = D3DQUERYTYPE_TIMESTAMP          ;// 6,
	DIS_QueryType[7] = D3DQUERYTYPE_TIMESTAMPDISJOINT  ;// 7,
	DIS_QueryType[8] = D3DQUERYTYPE_TIMESTAMPFREQ      ;// 8,
	DIS_QueryType[9] = D3DQUERYTYPE_PIPELINETIMINGS    ;// 9,
	DIS_QueryType[10] = D3DQUERYTYPE_INTERFACETIMINGS   ;// 10,
	DIS_QueryType[11] = D3DQUERYTYPE_VERTEXTIMINGS      ;// 11,
	DIS_QueryType[12] = D3DQUERYTYPE_PIXELTIMINGS       ;// 12,
	DIS_QueryType[13] = D3DQUERYTYPE_BANDWIDTHTIMINGS   ;// 13,
	DIS_QueryType[14] = D3DQUERYTYPE_CACHEUTILIZATION   ;// 14,
	DIS_QueryType[15] = D3DQUERYTYPE_MEMORYPRESSURE     ;// 15	



	blendState = new BlendState(this);
	rasterState = new RasterState(this);
	sState = new StencilState(this);
	valueState = new ValueState(this);
	fillState = new FillModeState(this);
	shadeState = new ShadeModeState(this);
	fixedState = new FixedState(this);
	fogModeState =  new FogModeState(this);
	patchDegreeState = new PatchDegreeState(this);
	compareFuncState = new CompareFuncState(this);
	patchEdgeState = new PatchEdgeState(this);
	vertBlendState = new VertexBlendState(this);
	materialColorSourceState= new MaterialColorSourceState(this);

	memset( (void*)m_RenderStateSetter, 0, sizeof(m_RenderStateSetter));

	m_RenderStateSetter[D3DRS_ZENABLE] = valueState;
	m_RenderStateSetter[D3DRS_FILLMODE] = fillState;  // new state
	m_RenderStateSetter[D3DRS_SHADEMODE] = shadeState; // new state
	m_RenderStateSetter[D3DRS_ZWRITEENABLE] = valueState; 
	m_RenderStateSetter[D3DRS_ALPHATESTENABLE] = valueState; 
	m_RenderStateSetter[D3DRS_LASTPIXEL] = valueState; 
	m_RenderStateSetter[D3DRS_SRCBLEND] = blendState; 
	m_RenderStateSetter[D3DRS_DESTBLEND] = blendState; 
	m_RenderStateSetter[D3DRS_CULLMODE] = rasterState; 
	m_RenderStateSetter[D3DRS_ZFUNC] = compareFuncState; 
	m_RenderStateSetter[D3DRS_ALPHAREF] = fixedState; 
	m_RenderStateSetter[D3DRS_ALPHAFUNC] = compareFuncState; 
	m_RenderStateSetter[D3DRS_DITHERENABLE] = valueState; 
	m_RenderStateSetter[D3DRS_ALPHABLENDENABLE] = valueState; 
	m_RenderStateSetter[D3DRS_FOGENABLE] = valueState; 
	m_RenderStateSetter[D3DRS_SPECULARENABLE] = valueState; 
	m_RenderStateSetter[D3DRS_FOGCOLOR] = valueState; 
	m_RenderStateSetter[D3DRS_FOGTABLEMODE] = fogModeState; // new state
	m_RenderStateSetter[D3DRS_FOGSTART] = valueState; 
	m_RenderStateSetter[D3DRS_FOGEND] = valueState; 
	m_RenderStateSetter[D3DRS_FOGDENSITY] = valueState; 
	m_RenderStateSetter[D3DRS_RANGEFOGENABLE] = valueState; 
	m_RenderStateSetter[D3DRS_STENCILENABLE] = valueState; 
	m_RenderStateSetter[D3DRS_STENCILFAIL] = sState; 
	m_RenderStateSetter[D3DRS_STENCILZFAIL] = sState; 
	m_RenderStateSetter[D3DRS_STENCILPASS] = sState; 
	m_RenderStateSetter[D3DRS_STENCILFUNC] = compareFuncState; 
	m_RenderStateSetter[D3DRS_STENCILREF] = valueState; 
	m_RenderStateSetter[D3DRS_STENCILMASK] = valueState; 
	m_RenderStateSetter[D3DRS_STENCILWRITEMASK] = valueState; 
	m_RenderStateSetter[D3DRS_TEXTUREFACTOR] = valueState; // new state
	m_RenderStateSetter[D3DRS_WRAP0] = valueState; 
	m_RenderStateSetter[D3DRS_WRAP1] = valueState; 
	m_RenderStateSetter[D3DRS_WRAP2] = valueState; 
	m_RenderStateSetter[D3DRS_WRAP3] = valueState; 
	m_RenderStateSetter[D3DRS_WRAP4] = valueState; 
	m_RenderStateSetter[D3DRS_WRAP5] = valueState; 
	m_RenderStateSetter[D3DRS_WRAP6] = valueState; 
	m_RenderStateSetter[D3DRS_WRAP7] = valueState;
	m_RenderStateSetter[D3DRS_CLIPPING] = valueState; 
	m_RenderStateSetter[D3DRS_LIGHTING] = valueState; 
	m_RenderStateSetter[D3DRS_AMBIENT] = valueState; 
	m_RenderStateSetter[D3DRS_FOGVERTEXMODE] = valueState;
	m_RenderStateSetter[D3DRS_COLORVERTEX] = valueState;
	m_RenderStateSetter[D3DRS_LOCALVIEWER] = valueState;
	m_RenderStateSetter[D3DRS_NORMALIZENORMALS] = valueState;
	m_RenderStateSetter[D3DRS_DIFFUSEMATERIALSOURCE] = materialColorSourceState;

	m_RenderStateSetter[D3DRS_SPECULARMATERIALSOURCE] = materialColorSourceState;
	m_RenderStateSetter[D3DRS_AMBIENTMATERIALSOURCE] = materialColorSourceState;
	m_RenderStateSetter[D3DRS_EMISSIVEMATERIALSOURCE] = materialColorSourceState;

	m_RenderStateSetter[D3DRS_VERTEXBLEND] = vertBlendState;
	m_RenderStateSetter[D3DRS_CLIPPLANEENABLE] = valueState;
	m_RenderStateSetter[D3DRS_POINTSIZE] = valueState;
	m_RenderStateSetter[D3DRS_POINTSIZE_MIN] = valueState;
	m_RenderStateSetter[D3DRS_POINTSPRITEENABLE] = valueState;
	m_RenderStateSetter[D3DRS_POINTSCALEENABLE] = valueState;
	m_RenderStateSetter[D3DRS_POINTSCALE_A] = valueState;
	m_RenderStateSetter[D3DRS_POINTSCALE_B] = valueState;
	m_RenderStateSetter[D3DRS_POINTSCALE_C] = valueState;

	m_RenderStateSetter[D3DRS_MULTISAMPLEANTIALIAS] = valueState;
	m_RenderStateSetter[D3DRS_MULTISAMPLEMASK] = valueState;
	m_RenderStateSetter[D3DRS_PATCHEDGESTYLE] = patchEdgeState; // new state

	m_RenderStateSetter[D3DRS_DEBUGMONITORTOKEN] = valueState;
	m_RenderStateSetter[D3DRS_POINTSIZE_MAX] = valueState;
	m_RenderStateSetter[D3DRS_INDEXEDVERTEXBLENDENABLE] = valueState;

	m_RenderStateSetter[D3DRS_COLORWRITEENABLE] = valueState;
	m_RenderStateSetter[D3DRS_TWEENFACTOR] = valueState;

	m_RenderStateSetter[D3DRS_BLENDOP] = blendState;
	m_RenderStateSetter[D3DRS_POSITIONDEGREE] = patchDegreeState;
	m_RenderStateSetter[D3DRS_NORMALDEGREE] = patchDegreeState;
	m_RenderStateSetter[D3DRS_SCISSORTESTENABLE] = valueState;

	m_RenderStateSetter[D3DRS_SLOPESCALEDEPTHBIAS] = valueState;
	m_RenderStateSetter[D3DRS_ANTIALIASEDLINEENABLE] = valueState;
	m_RenderStateSetter[D3DRS_MINTESSELLATIONLEVEL] = valueState;
	m_RenderStateSetter[D3DRS_MAXTESSELLATIONLEVEL] = valueState;
	m_RenderStateSetter[D3DRS_ADAPTIVETESS_X] = valueState;
	m_RenderStateSetter[D3DRS_ADAPTIVETESS_Y] = valueState;
	m_RenderStateSetter[D3DRS_ADAPTIVETESS_Z] = valueState;
	m_RenderStateSetter[D3DRS_ADAPTIVETESS_W] = valueState;

	m_RenderStateSetter[D3DRS_ENABLEADAPTIVETESSELLATION] = valueState;

	m_RenderStateSetter[D3DRS_ENABLEADAPTIVETESSELLATION] = valueState;
	m_RenderStateSetter[D3DRS_TWOSIDEDSTENCILMODE] = valueState;
	m_RenderStateSetter[D3DRS_CCW_STENCILFAIL] = sState;
	m_RenderStateSetter[D3DRS_CCW_STENCILZFAIL] = sState;
	m_RenderStateSetter[D3DRS_CCW_STENCILPASS] = sState;
	m_RenderStateSetter[D3DRS_CCW_STENCILFUNC] = compareFuncState;

	m_RenderStateSetter[D3DRS_COLORWRITEENABLE1] = valueState;
	m_RenderStateSetter[D3DRS_COLORWRITEENABLE2] = valueState;
	m_RenderStateSetter[D3DRS_COLORWRITEENABLE3] = valueState;
	m_RenderStateSetter[D3DRS_BLENDFACTOR] = valueState;
	m_RenderStateSetter[D3DRS_SRGBWRITEENABLE] = valueState;
	m_RenderStateSetter[D3DRS_DEPTHBIAS] = valueState;
	m_RenderStateSetter[D3DRS_WRAP8] = valueState;
	m_RenderStateSetter[D3DRS_WRAP9] = valueState;
	m_RenderStateSetter[D3DRS_WRAP10] = valueState;
	m_RenderStateSetter[D3DRS_WRAP11] = valueState;
	m_RenderStateSetter[D3DRS_WRAP12] = valueState;
	m_RenderStateSetter[D3DRS_WRAP13] = valueState;
	m_RenderStateSetter[D3DRS_WRAP14] = valueState;
	m_RenderStateSetter[D3DRS_WRAP15] = valueState;    
	m_RenderStateSetter[D3DRS_SEPARATEALPHABLENDENABLE] = valueState;
	m_RenderStateSetter[D3DRS_SRCBLENDALPHA] = blendState;
	m_RenderStateSetter[D3DRS_DESTBLENDALPHA] = blendState;
	m_RenderStateSetter[D3DRS_BLENDOPALPHA] = blendState;
 
	// back to enumerations
	DIS_RenderStateType[0] = D3DRS_ZENABLE                     ;//// 7;//
	DIS_RenderStateType[1] = D3DRS_FILLMODE                    ;//// 8;//
	DIS_RenderStateType[2] = D3DRS_SHADEMODE                   ;//// 9;//
	DIS_RenderStateType[3] = D3DRS_ZWRITEENABLE                ;//// 14;//
	DIS_RenderStateType[4] = D3DRS_ALPHATESTENABLE             ;//// 15;//
	DIS_RenderStateType[5] = D3DRS_LASTPIXEL                   ;//// 16;//
	DIS_RenderStateType[6] = D3DRS_SRCBLEND                    ;//// 19;//
	DIS_RenderStateType[7] = D3DRS_DESTBLEND                   ;//// 20;//
	DIS_RenderStateType[8] = D3DRS_CULLMODE                    ;//// 22;//
	DIS_RenderStateType[9] = D3DRS_ZFUNC                       ;//// 23;//
	DIS_RenderStateType[10] = D3DRS_ALPHAREF                    ;//// 24;//
	DIS_RenderStateType[11] = D3DRS_ALPHAFUNC                   ;//// 25;//
	DIS_RenderStateType[12] = D3DRS_DITHERENABLE                ;//// 26;//
	DIS_RenderStateType[13] = D3DRS_ALPHABLENDENABLE            ;//// 27;//
	DIS_RenderStateType[14] = D3DRS_FOGENABLE                   ;//// 28;//
	DIS_RenderStateType[15] = D3DRS_SPECULARENABLE              ;//// 29;//
	DIS_RenderStateType[16] = D3DRS_FOGCOLOR                    ;//// 34;//
	DIS_RenderStateType[17] = D3DRS_FOGTABLEMODE                ;//// 35;//
	DIS_RenderStateType[18] = D3DRS_FOGSTART                    ;//// 36;//
	DIS_RenderStateType[19] = D3DRS_FOGEND                      ;//// 37;//
	DIS_RenderStateType[20] = D3DRS_FOGDENSITY                  ;//// 38;//
	DIS_RenderStateType[21] = D3DRS_RANGEFOGENABLE              ;//// 48;//
	DIS_RenderStateType[22] = D3DRS_STENCILENABLE               ;//// 52;//
	DIS_RenderStateType[23] = D3DRS_STENCILFAIL                 ;//// 53;//
	DIS_RenderStateType[24] = D3DRS_STENCILZFAIL                ;//// 54;//
	DIS_RenderStateType[25] = D3DRS_STENCILPASS                 ;//// 55;//
	DIS_RenderStateType[26] = D3DRS_STENCILFUNC                 ;//// 56;//
	DIS_RenderStateType[27] = D3DRS_STENCILREF                  ;//// 57;//
	DIS_RenderStateType[28] = D3DRS_STENCILMASK                 ;//// 58;//
	DIS_RenderStateType[29] = D3DRS_STENCILWRITEMASK            ;//// 59;//
	DIS_RenderStateType[30] = D3DRS_TEXTUREFACTOR               ;//// 60;//
	DIS_RenderStateType[31] = D3DRS_WRAP0                       ;//// 128;//
	DIS_RenderStateType[32] = D3DRS_WRAP1                       ;//// 129;//
	DIS_RenderStateType[33] = D3DRS_WRAP2                       ;//// 130;//
	DIS_RenderStateType[34] = D3DRS_WRAP3                       ;//// 131;//
	DIS_RenderStateType[35] = D3DRS_WRAP4                       ;//// 132;//
	DIS_RenderStateType[36] = D3DRS_WRAP5                       ;//// 133;//
	DIS_RenderStateType[37] = D3DRS_WRAP6                       ;//// 134;//
	DIS_RenderStateType[38] = D3DRS_WRAP7                       ;//// 135;//
	DIS_RenderStateType[39] = D3DRS_CLIPPING                    ;//// 136;//
	DIS_RenderStateType[40] = D3DRS_LIGHTING                    ;//// 137;//
	DIS_RenderStateType[41] = D3DRS_AMBIENT                     ;//// 139;//
	DIS_RenderStateType[42] = D3DRS_FOGVERTEXMODE               ;//// 140;//
	DIS_RenderStateType[43] = D3DRS_COLORVERTEX                 ;//// 141;//
	DIS_RenderStateType[44] = D3DRS_LOCALVIEWER                 ;//// 142;//
	DIS_RenderStateType[45] = D3DRS_NORMALIZENORMALS            ;//// 143;//
	DIS_RenderStateType[46] = D3DRS_DIFFUSEMATERIALSOURCE       ;//// 145;//
	DIS_RenderStateType[47] = D3DRS_SPECULARMATERIALSOURCE      ;//// 146;//
	DIS_RenderStateType[48] = D3DRS_AMBIENTMATERIALSOURCE       ;//// 147;//
	DIS_RenderStateType[49] = D3DRS_EMISSIVEMATERIALSOURCE      ;//// 148;//
	DIS_RenderStateType[50] = D3DRS_VERTEXBLEND                 ;//// 151;//
	DIS_RenderStateType[51] = D3DRS_CLIPPLANEENABLE             ;//// 152;//
	DIS_RenderStateType[52] = D3DRS_POINTSIZE                   ;//// 154;//
	DIS_RenderStateType[53] = D3DRS_POINTSIZE_MIN               ;//// 155;//
	DIS_RenderStateType[54] = D3DRS_POINTSPRITEENABLE           ;//// 156;//
	DIS_RenderStateType[55] = D3DRS_POINTSCALEENABLE            ;//// 157;//
	DIS_RenderStateType[56] = D3DRS_POINTSCALE_A                ;//// 158;//
	DIS_RenderStateType[57] = D3DRS_POINTSCALE_B                ;//// 159;//
	DIS_RenderStateType[58] = D3DRS_POINTSCALE_C                ;//// 160;//
	DIS_RenderStateType[59] = D3DRS_MULTISAMPLEANTIALIAS        ;//// 161;//
	DIS_RenderStateType[60] = D3DRS_MULTISAMPLEMASK             ;//// 162;//
	DIS_RenderStateType[61] = D3DRS_PATCHEDGESTYLE              ;//// 163;//
	DIS_RenderStateType[62] = D3DRS_DEBUGMONITORTOKEN           ;//// 165;//
	DIS_RenderStateType[63] = D3DRS_POINTSIZE_MAX               ;//// 166;//
	DIS_RenderStateType[64] = D3DRS_INDEXEDVERTEXBLENDENABLE    ;//// 167;//
	DIS_RenderStateType[65] = D3DRS_COLORWRITEENABLE            ;//// 168;//
	DIS_RenderStateType[66] = D3DRS_TWEENFACTOR                 ;//// 170;//
	DIS_RenderStateType[67] = D3DRS_BLENDOP                     ;//// 171;//
	DIS_RenderStateType[68] = D3DRS_POSITIONDEGREE              ;//// 172;//
	DIS_RenderStateType[69] = D3DRS_NORMALDEGREE                ;//// 173;//
	DIS_RenderStateType[70] = D3DRS_SCISSORTESTENABLE           ;//// 174;//
	DIS_RenderStateType[71] = D3DRS_SLOPESCALEDEPTHBIAS         ;//// 175;//
	DIS_RenderStateType[72] = D3DRS_ANTIALIASEDLINEENABLE       ;//// 176;//
	DIS_RenderStateType[73] = D3DRS_MINTESSELLATIONLEVEL        ;//// 178;//
	DIS_RenderStateType[74] = D3DRS_MAXTESSELLATIONLEVEL        ;//// 179;//
	DIS_RenderStateType[75] = D3DRS_ADAPTIVETESS_X              ;//// 180;//
	DIS_RenderStateType[76] = D3DRS_ADAPTIVETESS_Y              ;//// 181;//
	DIS_RenderStateType[77] = D3DRS_ADAPTIVETESS_Z              ;//// 182;//
	DIS_RenderStateType[78] = D3DRS_ADAPTIVETESS_W              ;//// 183;//
	DIS_RenderStateType[79] = D3DRS_ENABLEADAPTIVETESSELLATION  ;//// 184;//
	DIS_RenderStateType[80] = D3DRS_TWOSIDEDSTENCILMODE         ;//// 185;//
	DIS_RenderStateType[81] = D3DRS_CCW_STENCILFAIL             ;//// 186;//
	DIS_RenderStateType[82] = D3DRS_CCW_STENCILZFAIL            ;//// 187;//
	DIS_RenderStateType[83] = D3DRS_CCW_STENCILPASS             ;//// 188;//
	DIS_RenderStateType[84] = D3DRS_CCW_STENCILFUNC             ;//// 189;//
	DIS_RenderStateType[85] = D3DRS_COLORWRITEENABLE1           ;//// 190;//
	DIS_RenderStateType[86] = D3DRS_COLORWRITEENABLE2           ;//// 191;//
	DIS_RenderStateType[87] = D3DRS_COLORWRITEENABLE3           ;//// 192;//
	DIS_RenderStateType[88] = D3DRS_BLENDFACTOR                 ;//// 193;//
	DIS_RenderStateType[89] = D3DRS_SRGBWRITEENABLE             ;//// 194;//
	DIS_RenderStateType[90] = D3DRS_DEPTHBIAS                   ;//// 195;//
	DIS_RenderStateType[91] = D3DRS_WRAP8                       ;//// 198;//
	DIS_RenderStateType[92] = D3DRS_WRAP9                       ;//// 199;//
	DIS_RenderStateType[93] = D3DRS_WRAP10                      ;//// 200;//
	DIS_RenderStateType[94] = D3DRS_WRAP11                      ;//// 201;//
	DIS_RenderStateType[95] = D3DRS_WRAP12                      ;//// 202;//
	DIS_RenderStateType[96] = D3DRS_WRAP13                      ;//// 203;//
	DIS_RenderStateType[97] = D3DRS_WRAP14                      ;//// 204;//
	DIS_RenderStateType[98] = D3DRS_WRAP15                      ;//// 205;//
	DIS_RenderStateType[99] = D3DRS_SEPARATEALPHABLENDENABLE    ;//// 206;//
	DIS_RenderStateType[100] = D3DRS_SRCBLENDALPHA               ;//// 207;//
	DIS_RenderStateType[101] = D3DRS_DESTBLENDALPHA              ;//// 208;//
	DIS_RenderStateType[102] = D3DRS_BLENDOPALPHA                ;//// 209;//

	DIS_ResourceType[0] = D3DRTYPE_SURFACE;//        = 0,
	DIS_ResourceType[1] = D3DRTYPE_VOLUME ;//        = 1,
	DIS_ResourceType[2] = D3DRTYPE_TEXTURE;//        = 2,
	DIS_ResourceType[3] = D3DRTYPE_VOLUMETEXTURE;//  = 3,
	DIS_ResourceType[4] = D3DRTYPE_CUBETEXTURE;//    = 4,
	DIS_ResourceType[5] = D3DRTYPE_VERTEXBUFFER;//   = 5,
	DIS_ResourceType[6] = D3DRTYPE_INDEXBUFFER;//    = 6,
	
	DIS_SamplerTextureType[0] = D3DSTT_UNKNOWN;
	DIS_SamplerTextureType[1] = D3DSTT_2D;
	DIS_SamplerTextureType[2] = D3DSTT_CUBE;
	DIS_SamplerTextureType[3] = D3DSTT_VOLUME;
	
	DIS_SampleStateType[0] = D3DSAMP_ADDRESSU ;// 0,
	DIS_SampleStateType[1] = D3DSAMP_ADDRESSU       ;// 1,
	DIS_SampleStateType[2] = D3DSAMP_ADDRESSV       ;// 2,
	DIS_SampleStateType[3] = D3DSAMP_ADDRESSW       ;// 3,
	DIS_SampleStateType[4] = D3DSAMP_BORDERCOLOR    ;// 4,
	DIS_SampleStateType[5] = D3DSAMP_MAGFILTER      ;// 5,
	DIS_SampleStateType[6] = D3DSAMP_MINFILTER      ;// 6,
	DIS_SampleStateType[7] = D3DSAMP_MIPFILTER      ;// 7,
	DIS_SampleStateType[8] = D3DSAMP_MIPMAPLODBIAS  ;// 8,
	DIS_SampleStateType[9] = D3DSAMP_MAXMIPLEVEL    ;// 9,
	DIS_SampleStateType[10] = D3DSAMP_MAXANISOTROPY  ;// 10,
	DIS_SampleStateType[11] = D3DSAMP_SRGBTEXTURE    ;// 11,
	DIS_SampleStateType[12] = D3DSAMP_ELEMENTINDEX   ;// 12,
	DIS_SampleStateType[13] = D3DSAMP_DMAPOFFSET     ;// 13,
	
	DIS_ScanlineOrdering[0] = D3DSCANLINEORDERING_PROGRESSIVE ;//= 0,
	DIS_ScanlineOrdering[1] = D3DSCANLINEORDERING_PROGRESSIVE ;// = 1,
	DIS_ScanlineOrdering[2] = D3DSCANLINEORDERING_INTERLACED ;//  = 2
	
	DIS_ShadeMode[0]=D3DSHADE_GOURAUD;// 0,
	DIS_ShadeMode[1]=D3DSHADE_FLAT         ;// 1,
	DIS_ShadeMode[2]=D3DSHADE_GOURAUD      ;// 2,
	DIS_ShadeMode[3]=D3DSHADE_PHONG        ;// 3,
	DIS_ShadeMode[4]=D3DSHADE_GOURAUD       ;// 4,
	
	DIS_StateBlockType[0]=D3DSBT_ALL           ;// 0,
	DIS_StateBlockType[1]=D3DSBT_ALL          ;// 1,
	DIS_StateBlockType[2]=D3DSBT_PIXELSTATE   ;// 2,
	DIS_StateBlockType[3]=D3DSBT_VERTEXSTATE  ;// 3,
	
	DIS_StencilOp[0] = D3DSTENCILOP_KEEP          ;// 0,
	DIS_StencilOp[1] = D3DSTENCILOP_KEEP         ;// 1,
	DIS_StencilOp[2] = D3DSTENCILOP_ZERO         ;// 2,
	DIS_StencilOp[3] = D3DSTENCILOP_REPLACE      ;// 3,
	DIS_StencilOp[4] = D3DSTENCILOP_INCRSAT      ;// 4,
	DIS_StencilOp[5] = D3DSTENCILOP_DECRSAT      ;// 5,
	DIS_StencilOp[6] = D3DSTENCILOP_INVERT       ;// 6,
	DIS_StencilOp[7] = D3DSTENCILOP_INCR         ;// 7,
	DIS_StencilOp[8] = D3DSTENCILOP_DECR         ;// 8,
	
	DIS_SwapEffect[0] = D3DSWAPEFFECT_DISCARD;// 0,
	DIS_SwapEffect[1] =  D3DSWAPEFFECT_DISCARD      ;// 1,
	DIS_SwapEffect[2] = D3DSWAPEFFECT_FLIP         ;// 2,
	DIS_SwapEffect[3] = D3DSWAPEFFECT_COPY         ;// 3,
	DIS_SwapEffect[4] = D3DSWAPEFFECT_OVERLAY      ;// 4,
	DIS_SwapEffect[5] = D3DSWAPEFFECT_FLIPEX       ;// 5,
	
	DIS_TextureAddress[0] = D3DTADDRESS_WRAP       ;// 0,
	DIS_TextureAddress[1] = D3DTADDRESS_WRAP         ;// 1,
	DIS_TextureAddress[2] = D3DTADDRESS_MIRROR       ;// 2,
	DIS_TextureAddress[3] = D3DTADDRESS_CLAMP        ;// 3,
	DIS_TextureAddress[4] = D3DTADDRESS_BORDER       ;// 4,
	DIS_TextureAddress[5] = D3DTADDRESS_MIRRORONCE   ;// 5,
	
	DIS_TextureFilterType[0] = D3DTEXF_NONE             ;// 0,
	DIS_TextureFilterType[1] = D3DTEXF_POINT            ;// 1,
	DIS_TextureFilterType[2] = D3DTEXF_LINEAR           ;// 2,
	DIS_TextureFilterType[3] = D3DTEXF_ANISOTROPIC      ;// 3,
	DIS_TextureFilterType[4] = D3DTEXF_PYRAMIDALQUAD    ;// 4,
	DIS_TextureFilterType[5] = D3DTEXF_GAUSSIANQUAD     ;// 5,
	DIS_TextureFilterType[6] = D3DTEXF_CONVOLUTIONMONO  ;// 6,
	
	DIS_TextureOp[0] = D3DTOP_DISABLE ;// 0,
	DIS_TextureOp[1] = D3DTOP_DISABLE                    ;// 1,
	DIS_TextureOp[2] = D3DTOP_SELECTARG1                 ;// 2,
	DIS_TextureOp[3] = D3DTOP_SELECTARG2                 ;// 3,
	DIS_TextureOp[4] = D3DTOP_MODULATE                   ;// 4,
	DIS_TextureOp[5] = D3DTOP_MODULATE2X                 ;// 5,
	DIS_TextureOp[6] = D3DTOP_MODULATE4X                 ;// 6,
	DIS_TextureOp[7] = D3DTOP_ADD                        ;// 7,
	DIS_TextureOp[8] = D3DTOP_ADDSIGNED                  ;// 8,
	DIS_TextureOp[9] = D3DTOP_ADDSIGNED2X                ;// 9,
	DIS_TextureOp[10] = D3DTOP_SUBTRACT                   ;// 10,
	DIS_TextureOp[11] = D3DTOP_ADDSMOOTH                  ;// 11,
	DIS_TextureOp[12] = D3DTOP_BLENDDIFFUSEALPHA          ;// 12,
	DIS_TextureOp[13] = D3DTOP_BLENDTEXTUREALPHA          ;// 13,
	DIS_TextureOp[14] = D3DTOP_BLENDFACTORALPHA           ;// 14,
	DIS_TextureOp[15] = D3DTOP_BLENDTEXTUREALPHAPM        ;// 15,
	DIS_TextureOp[16] = D3DTOP_BLENDCURRENTALPHA          ;// 16,
	DIS_TextureOp[17] = D3DTOP_PREMODULATE                ;// 17,
	DIS_TextureOp[18] = D3DTOP_MODULATEALPHA_ADDCOLOR     ;// 18,
	DIS_TextureOp[19] = D3DTOP_MODULATECOLOR_ADDALPHA     ;// 19,
	DIS_TextureOp[20] = D3DTOP_MODULATEINVALPHA_ADDCOLOR  ;// 20,
	DIS_TextureOp[21] = D3DTOP_MODULATEINVCOLOR_ADDALPHA  ;// 21,
	DIS_TextureOp[22] = D3DTOP_BUMPENVMAP                 ;// 22,
	DIS_TextureOp[23] = D3DTOP_BUMPENVMAPLUMINANCE        ;// 23,
	DIS_TextureOp[24] = D3DTOP_DOTPRODUCT3                ;// 24,
	DIS_TextureOp[25] = D3DTOP_MULTIPLYADD                ;// 25,
	DIS_TextureOp[26] = D3DTOP_LERP                       ;// 26,
	
	DIS_TextureStageStateType[0] = D3DTSS_COLOROP ;// 0;
	DIS_TextureStageStateType[1] = D3DTSS_COLOROP                ;// 1;
	DIS_TextureStageStateType[2] = D3DTSS_COLORARG1              ;// 2;
	DIS_TextureStageStateType[3] = D3DTSS_COLORARG2              ;// 3;
	DIS_TextureStageStateType[4] = D3DTSS_ALPHAOP                ;// 4;
	DIS_TextureStageStateType[5] = D3DTSS_ALPHAARG1              ;// 5;
	DIS_TextureStageStateType[6] = D3DTSS_ALPHAARG2              ;// 6;
	DIS_TextureStageStateType[7] = D3DTSS_BUMPENVMAT00           ;// 7;
	DIS_TextureStageStateType[8] = D3DTSS_BUMPENVMAT01           ;// 8;
	DIS_TextureStageStateType[9] = D3DTSS_BUMPENVMAT10           ;// 9;
	DIS_TextureStageStateType[10] = D3DTSS_BUMPENVMAT11           ;// 10;
	DIS_TextureStageStateType[11] = D3DTSS_TEXCOORDINDEX          ;// 11;
	DIS_TextureStageStateType[12] = D3DTSS_BUMPENVLSCALE          ;// 22;
	DIS_TextureStageStateType[13] = D3DTSS_BUMPENVLOFFSET         ;// 23;
	DIS_TextureStageStateType[14] = D3DTSS_TEXTURETRANSFORMFLAGS  ;// 24;
	DIS_TextureStageStateType[15] = D3DTSS_COLORARG0              ;// 26;
	DIS_TextureStageStateType[16] = D3DTSS_ALPHAARG0              ;// 27;
	DIS_TextureStageStateType[17] = D3DTSS_RESULTARG              ;// 28;
	DIS_TextureStageStateType[18] = D3DTSS_CONSTANT               ;// 32;
	
	DIS_TextureTransformFlags[0] = D3DTTFF_DISABLE      ;// 0,
	DIS_TextureTransformFlags[1] = D3DTTFF_COUNT1       ;// 1,
	DIS_TextureTransformFlags[2] = D3DTTFF_COUNT2       ;// 2,
	DIS_TextureTransformFlags[3] = D3DTTFF_COUNT3       ;// 3,
	DIS_TextureTransformFlags[4] = D3DTTFF_COUNT4       ;// 4,
	DIS_TextureTransformFlags[5] = D3DTTFF_PROJECTED    ;// 5,

	DIS_TransformStateType[0] = D3DTS_WORLD;
	DIS_TransformStateType[1] = D3DTS_WORLD;
	DIS_TransformStateType[2] = D3DTS_VIEW;
	DIS_TransformStateType[3] = D3DTS_PROJECTION;
	DIS_TransformStateType[4] = D3DTS_TEXTURE0;
	DIS_TransformStateType[5] = D3DTS_TEXTURE1;
	DIS_TransformStateType[6] = D3DTS_TEXTURE2;
	DIS_TransformStateType[7] = D3DTS_TEXTURE3;
	DIS_TransformStateType[8] = D3DTS_TEXTURE4;
	DIS_TransformStateType[9] = D3DTS_TEXTURE5;
	DIS_TransformStateType[10] = D3DTS_TEXTURE6;
	DIS_TransformStateType[11] = D3DTS_TEXTURE7;

	DIS_VertexBlendFlags[0] = D3DVBF_DISABLE   ;// 0,
	DIS_VertexBlendFlags[1] = D3DVBF_1WEIGHTS  ;// 1,
	DIS_VertexBlendFlags[2] = D3DVBF_2WEIGHTS  ;// 2,
	DIS_VertexBlendFlags[3] = D3DVBF_3WEIGHTS  ;// 3,
	DIS_VertexBlendFlags[4] = D3DVBF_TWEENING  ;// 4,
	DIS_VertexBlendFlags[5] = D3DVBF_0WEIGHTS  ;// 5
	
	DIS_ZBufferType[0] = D3DZB_FALSE;//        = 0,
	DIS_ZBufferType[1] = D3DZB_TRUE;//         = 1,
	DIS_ZBufferType[2] = D3DZB_USEW;//         = 2,


	DIS_Usage[0] = DIS_USAGE_NONE;
	DIS_Usage[1] = D3DUSAGE_AUTOGENMIPMAP;
	DIS_Usage[2] = D3DUSAGE_DEPTHSTENCIL;
	DIS_Usage[3] = D3DUSAGE_DMAP;
	DIS_Usage[4] = D3DUSAGE_DONOTCLIP;
	DIS_Usage[5] = D3DUSAGE_DYNAMIC;
	DIS_Usage[6] = D3DUSAGE_NONSECURE;
	DIS_Usage[7] = D3DUSAGE_NPATCHES;
	DIS_Usage[8] = D3DUSAGE_POINTS;
	DIS_Usage[9] = D3DUSAGE_RENDERTARGET;
	DIS_Usage[10] = D3DUSAGE_RTPATCHES;
	DIS_Usage[11] = D3DUSAGE_SOFTWAREPROCESSING;
	DIS_Usage[12] = D3DUSAGE_TEXTAPI;
	DIS_Usage[13] = D3DUSAGE_WRITEONLY;
	DIS_Usage[14] = D3DUSAGE_RESTRICTED_CONTENT;
	DIS_Usage[15] = D3DUSAGE_RESTRICT_SHARED_RESOURCE;
	DIS_Usage[16] = D3DUSAGE_RESTRICT_SHARED_RESOURCE_DRIVER;

	m_ResourceManager = CreateResourceManager(m_ResourceManager);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
D3D_DeviceInterface::~D3D_DeviceInterface()
{
	delete blendState;
	delete rasterState;
	delete sState;
	delete valueState;
	delete shadeState;
	delete fixedState;
	delete fogModeState;
	delete patchDegreeState;
	delete compareFuncState;
	delete patchEdgeState;
	delete vertBlendState;
	delete materialColorSourceState;

	delete m_ResourceManager;

	if( pD3DDevice )
	{
		pD3DDevice->Release();
		pD3DDevice = NULL;
	}
}



//-------------------------------------------------------------------------------------
// SetBlendState
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetBlendState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	D3DBLENDOP blend = (D3DBLENDOP)this->DIS_BlendOp[ DIS_BLENDOP(B) ];

	HRESULT hr = pD3DDevice->SetRenderState(rs, blend);
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// SetStencilState
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetStencilState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	D3DSTENCILOP stencil = (D3DSTENCILOP)this->DIS_StencilOp[ DIS_STENCILOP(B) ];

	HRESULT hr = pD3DDevice->SetRenderState(rs, stencil);
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// SetRasterizerState
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetRasterizerState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	D3DCULL cull = (D3DCULL)this->DIS_Cullmode[ DIS_CULL(B) ];

	HRESULT hr = pD3DDevice->SetRenderState(rs, cull);
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// SetValueState
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetValueState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->SetRenderState(rs, B);
	return HR_to_DR(hr);;
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::SetFillModeState( UInt32 A, UInt32 B )
{
	UInt32 val = 0;
	if( B & DIS_FILL_SOLID )
	{
		val |= D3DFILL_SOLID;
	}
	if( B & DIS_FILL_WIREFRAME )
	{
		val |= D3DFILL_WIREFRAME;
	}
	if( B & DIS_FILL_POINT )
	{
		val |= D3DFILL_POINT;
	}
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	//D3DFILLMODE fill = (D3DFILLMODE)this->DIS_FillMode[ DIS_FILLMODE(B) ];
	HRESULT hr = pD3DDevice->SetRenderState(rs, val);
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::SetShadeModeState( UInt32 A, UInt32 B )
{
	UInt32 val = 0;
	if( B & DIS_SHADE_FLAT )
	{
		val |= D3DSHADE_FLAT;
	}
	if( B & DIS_SHADE_GOURAUD  )
	{
		val |= D3DSHADE_GOURAUD  ;
	}
	if( B & DIS_SHADE_PHONG )
	{
		val |= D3DSHADE_PHONG;
	}
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	//D3DSHADEMODE shade = (D3DFILLMODE)this->DIS_ShadeMode[ DIS_SHADEMODE(B) ];
	HRESULT hr = pD3DDevice->SetRenderState(rs, val);
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::SetFixedState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->SetRenderState(rs, B);
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::SetFogModeState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	D3DFOGMODE fog = (D3DFOGMODE)this->DIS_FogMode[ DIS_FOGMODE(B) ];
	HRESULT hr = pD3DDevice->SetRenderState(rs, fog);
	return HR_to_DR(hr);;
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetPatchDegreeState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	D3DDEGREETYPE Degree = (D3DDEGREETYPE)this->DIS_DegreeType[ DIS_DEGREETYPE(B) ];	
	HRESULT hr = pD3DDevice->SetRenderState(rs, Degree );
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::SetCompareFuncState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	D3DCMPFUNC cmp = (D3DCMPFUNC)this->DIS_CmpFunc[ DIS_CMPFUNC(B) ];	
	HRESULT hr = pD3DDevice->SetRenderState(rs, cmp );
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::SetPatchEdgeState( UInt32 A, UInt32 B )
{
	D3DPATCHEDGESTYLE edgeStyle = D3DPATCHEDGE_DISCRETE;  
	if( DIS_PATCHEDGESTYLE (B) ==  DIS_PATCHEDGE_DISCRETE )
	{
		edgeStyle = D3DPATCHEDGE_DISCRETE;  

	}
	else if( DIS_PATCHEDGESTYLE (B) ==  DIS_PATCHEDGE_CONTINUOUS)
	{
		edgeStyle = D3DPATCHEDGE_CONTINUOUS;  
	}
	
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->SetRenderState(rs, edgeStyle);
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::SetMaterialColorSourceState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	D3DMATERIALCOLORSOURCE  mcs = (D3DMATERIALCOLORSOURCE )this->DIS_MaterialColorSource[ DIS_MATERIALCOLORSOURCE(B) ];	
	HRESULT hr = pD3DDevice->SetRenderState(rs, mcs);
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::SetVertexBlendState( UInt32 A, UInt32 B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	D3DVERTEXBLENDFLAGS blendFlags = (D3DVERTEXBLENDFLAGS  )this->DIS_VertexBlendFlags[ DIS_VERTEXBLENDFLAGS(B) ];	
	
	HRESULT hr = pD3DDevice->SetRenderState(rs, blendFlags );
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetBlendState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = (DIS_BLENDOP)to_DIS.BlendOp( D3DBLENDOP(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetStencilState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = (DIS_STENCILOP)to_DIS.dStencilOp( D3DSTENCILOP(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetRasterizerState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = (DIS_CULL)to_DIS.CullMode( D3DCULL(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetValueState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	//*B = (DIS_FILLMODE)to_DIS.FillMode( D3DFILLMODE(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetFillModeState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = (DIS_FILLMODE)to_DIS.FillMode( D3DFILLMODE(*B) );


	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetShadeModeState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = (DIS_SHADEMODE)to_DIS.dShadeMode( D3DSHADEMODE(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetFixedState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	//*B = (DIS_FOGMODE)to_DIS( D3DFOGMODE(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetFogModeState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = (DIS_FOGMODE)to_DIS.FogMode( D3DFOGMODE(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetPatchDegreeState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = (DIS_DEGREETYPE)to_DIS.DegreeType( D3DDEGREETYPE(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetCompareFuncState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = (DIS_CMPFUNC)to_DIS.CompareFunc( D3DCMPFUNC(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetPatchEdgeState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	if( D3DPATCHEDGESTYLE (*B) ==  D3DPATCHEDGE_DISCRETE)
	{
		*B = DIS_PATCHEDGE_DISCRETE;  

	}
	else if( D3DPATCHEDGESTYLE (*B) ==  D3DPATCHEDGE_CONTINUOUS)
	{
		*B = DIS_PATCHEDGE_CONTINUOUS;  
	}

	//*B = to_DIS.dVertexBlendFlags( D3DVERTEXBLENDFLAGS(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetMaterialColorSourceState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(*B) );
	
	return HR_to_DR(hr);
}

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT	D3D_DeviceInterface::GetVertexBlendState( UInt32 A, UInt32 *B )
{
	D3DRENDERSTATETYPE rs = (D3DRENDERSTATETYPE)this->DIS_RenderStateType[ DIS_RENDERSTATETYPE(A)];
	HRESULT hr = pD3DDevice->GetRenderState(rs, (DWORD*)B );

	*B = to_DIS.dVertexBlendFlags( D3DVERTEXBLENDFLAGS(*B) );
	
	return HR_to_DR(hr);
}


// Begins a scene.

//-------------------------------------------------------------------------------------
// D3D_DeviceInterface
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::BeginScene()
{
	HRESULT hr = pD3DDevice->BeginScene();
	
	return HR_to_DR( hr );
}

//-------------------------------------------------------------------------------------
// Signals Direct3D to begin recording a device-state block.
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::BeginStateBlock()
{
	HRESULT hr = pD3DDevice->BeginStateBlock();
	
	return HR_to_DR( hr );
}
	
//-------------------------------------------------------------------------------------
//Clears one or more surfaces such as a render target, multiple render targets, a stencil buffer, and a depth buffer.
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::Clear(  UInt32 Count,		// [in] Number of rectangles in the array at pRects. Must be set to 0 if pRects is NULL. May not be 0 if pRects is a valid pointer.
	const DIS_Rect *pRects,				// [in] Pointer to an array of DIS_Rect structures that describe the rectangles to clear. Set a rectangle to the dimensions of the rendering target to clear the entire surface. Each rectangle uses screen coordinates that correspond to points on the render target. Coordinates are clipped to the bounds of the viewport rectangle. To indicate that the entire viewport rectangle is to be cleared, set this parameter to NULL and Count to 0.
	UInt32 Flags,						// [in] Combination of one or more DIS_CLEAR flags that specify the surface(s) that will be cleared.
	DIS_COLOR Color,					// [in] Clear a render target to this ARGB color
	float Z,							// [in] Clear the depth buffer to this new z value which ranges from 0 to 1. See remarks.
	UInt32 Stencil)					// [in] Clear the stencil buffer to this new value which ranges from 0 to 2n-1 (n is the bit depth of the stencil buffer). See remarks.
{
	HRESULT hr = pD3DDevice->Clear(Count, (D3DRECT*)pRects, 
									Flags, Color, Z, Stencil);
	
	return HR_to_DR( hr );
	
}

//-------------------------------------------------------------------------------------
//Allows an application to fill a rectangular area of a DIS_POOL_DEFAULT surface with a specified color.
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::ColorFill (   LPSURFACE2D pSurface, //[in] Pointer to the surface to be filled.
	const DIS_Rect *pRect,						//[in] Pointer to the source rectangle. Using NULL means that the entire surface will be filled.
	DIS_COLOR color)							//[in] Color used for filling.
{
	
	HRESULT hr = pD3DDevice->ColorFill( LPSURFACE2D_D3D9(pSurface)->pd3dSurface, 
										(const RECT*)pRect, color);
	
	return HR_to_DR( hr );
}

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
//Creates a cube texture resource.
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateCubeTexture(  UInt32 EdgeLength,	//[in]Size of the edges of all the top-level faces of the cube texture. The pixel dimensions of subsequent levels of each face will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0 (zero), 1 will be taken instead.
	UInt32 Levels,							//[in]Number of levels in each face of the cube texture. If this is zero, DIS_3D will generate all cube texture sublevels down to 1x1 pixels for each face for hardware that supports mipmapped cube textures. Call IDirect3DBaseTexture9::GetLevelCount to see the number of levels generated.
	UInt32 Usage,							//[in] Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants. It is good practice to match the usage parameter in CreateCubeTexture with the behavior flags in IDirect3D9::CreateDevice. For more information, see Remarks.
	DIS_FORMAT Format,						//[in]Member of the D3DFORMAT enumerated type, describing the format of all levels in all faces of the cube texture.
	DIS_POOL Pool,							//[in]Member of the D3DPOOL enumerated type, describing the memory class into which the cube texture should be placed.
	LPCUBETEXTURE2D *ppCubeTexture,			//[out, retval]  Address of a pointer to an IDirect3DCubeTexture9 interface, representing the created cube texture resource.
    DIS_HANDLE *pSharedHandle	)			//[in]Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources.
{
	if( *ppCubeTexture )
	{
		// decide what to do with this
		return DIS_FAIL;
	}
	

	LPDIRECT3DCUBETEXTURE9 pd3dCubeTexture = NULL;
	HRESULT hr = pD3DDevice->CreateCubeTexture(
							EdgeLength, 
							Levels, 
							DIS_Usage[ Usage ], 
							(D3DFORMAT) DIS_Format[ Format ],
							(D3DPOOL) DIS_Pool[ Pool ], 
							&pd3dCubeTexture, 
							pSharedHandle);

	if( hr != D3D_OK )
	{

		if( pd3dCubeTexture )
		{
			pd3dCubeTexture->Release();
			pd3dCubeTexture = NULL;
		}
		return HR_to_DR( hr );
	}

	*ppCubeTexture = new D3D9_CubeTexture2D(pd3dCubeTexture, m_ResourceManager);
		
	return HR_to_DR( hr );
}


//Creates a depth-stencil resource.
//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateDepthStencilSurface(
	UInt32 Width,							//[in]       Width of the depth-stencil surface, in pixels.    
	UInt32 Height,							//[in]        Height of the depth-stencil surface, in pixels.   
	DIS_FORMAT Format,						//[in] Member of the D3DFORMAT enumerated type, describing the format of the depth-stencil surface. This value must be one of the enumerated depth-stencil formats for this device.          
	DIS_MULTISAMPLE_TYPE MultiSample,		//[in] Member of the D3DMULTISAMPLE_TYPE enumerated type, describing the multisampling buffer type. This value must be one of the allowed multisample types. When this surface is passed to IDirect3DDevice9::SetDepthStencilSurface, its multisample type must be the same as that of the render target set by IDirect3DDevice9::SetRenderTarget.          
	UInt32 MultisampleQuality,				//[in]Quality level. The valid range is between zero and one less than the level returned by pQualityLevels used by IDirect3D9::CheckDeviceMultiSampleType. Passing a larger value returns the error D3DERR_INVALIDCALL. The MultisampleQuality values of paired render targets, depth stencil surfaces, and the MultiSample type must all match.           
	bool Discard,							//[in] Set this flag to TRUE to enable z-buffer discarding, and FALSE otherwise.	 If this flag is set, the contents of the depth stencil buffer will be invalid after calling either IDirect3DDevice9::Present or IDirect3DDevice9::SetDepthStencilSurface with a different depth surface. This flag has the same behavior as the constant, D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL, in D3DPRESENTFLAG.          
	LPSURFACE2D *ppSurface,					//[out, retval]  Address of a pointer to an IDirect3DSurface9 interface, representing the created depth-stencil surface resource.
	DIS_HANDLE *pSharedHandle				//[in]  Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources.         
	)
{
	if( *ppSurface )
	{
		// work out what to do with this
		return DIS_FAIL;
	}


	LPDIRECT3DSURFACE9 pd3dSurface = NULL;
	HRESULT hr = pD3DDevice->CreateDepthStencilSurface(
							Width, 
							Height, 
							D3DFORMAT( DIS_Format[ Format ] ),
							D3DMULTISAMPLE_TYPE(DIS_MultiSampleType[ MultiSample ]), 
							MultisampleQuality, Discard,
							&pd3dSurface, 
							pSharedHandle);

	if( hr != D3D_OK )
	{

		if( pd3dSurface )
		{
			pd3dSurface->Release();
			pd3dSurface = NULL;
		}
		return HR_to_DR( hr );
	}
	
	*ppSurface  = new D3D9_Surface2D(pd3dSurface, m_ResourceManager);
	
	return HR_to_DR( hr );

}


//Creates an index buffer.
//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateIndexBuffer(
        UInt32 Length,						//[in]Size of the index buffer, in bytes.
        UInt32 Usage,						//[in]Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants. It is good practice to match the usage parameter in CreateIndexBuffer with the behavior flags in IDirect3D9::CreateDevice. For more information, see Remarks.
        DIS_FORMAT Format,					//[in] Member of the DIS_FORMAT enumerated type, describing the format of the index buffer. For more information, see Remarks. The valid settings are the following: DIS_FMT_INDEX16, DIS_FMT_INDEX32
        DIS_POOL Pool,						//[in] Member of the DIS_POOL enumerated type, describing a valid memory class into which to place the resource.
		LPINDEXBUFFER *ppIndexBuffer,		//[out, retval]Address of a pointer to an IDirect3DIndexBuffer9 interface, representing the created index buffer resource.
        DIS_HANDLE *pSharedHandle)			//[in] Reserved. Set this parameter to NULL. This parameter can be used in DIS_3D 9 for Windows Vista to share resources.    
{
	if( *ppIndexBuffer )
	{
		// work out what to do here
		return DIS_FAIL;
	}
	
	UInt32 usage = 0;
	if( Usage & DIS_USAGE::DIS_USAGE_WRITEONLY )
	{
		usage |= D3DUSAGE_WRITEONLY;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_DYNAMIC )
	{
		usage |= D3DUSAGE_DYNAMIC;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_AUTOGENMIPMAP )
	{
		usage |= D3DUSAGE_AUTOGENMIPMAP ;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_RENDERTARGET )
	{
		usage |= D3DUSAGE_RENDERTARGET;
	}

	D3DFORMAT fornat = D3DFORMAT( DIS_Format[ Format ] );
	D3DPOOL pool = D3DPOOL( DIS_Pool[ Pool ] );


	LPDIRECT3DINDEXBUFFER9 pd3dIndexBuffer = NULL;
	HRESULT hr = pD3DDevice->CreateIndexBuffer(
								Length, 
								usage, 
								fornat,
								pool, 
								&pd3dIndexBuffer, 
								pSharedHandle);

	if( hr != D3D_OK )
	{

		if( pd3dIndexBuffer )
		{
			pd3dIndexBuffer->Release();
			pd3dIndexBuffer = NULL;
		}
		return HR_to_DR( hr );
	}
	
	*ppIndexBuffer = new D3D9_IndexBuffer(pd3dIndexBuffer, m_ResourceManager);
	
	return HR_to_DR( hr );
	
}

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateOffscreenPlainSurface(//Create an off-screen surface.
        UInt32 Width,						//[in] Width of the surface.
            UInt32 Height,						//[in]Height of the surface.
            DIS_FORMAT Format,					//[in]Format of the surface. See DIS_FORMAT.
            DIS_POOL Pool,						//[in]Member of the DIS_POOL enumerated type, describing a valid memory class into which to place the resource.
		LPSURFACE2D *ppSurface,				// [out, retval] 
        DIS_HANDLE *pSharedHandle)			//[in]Reserved. Set this parameter to NULL. This parameter can be used in DIS_3D 9 for Windows Vista to share resources.
{
	if( *ppSurface )
	{
		return DIS_FAIL;
	}
	

	LPDIRECT3DSURFACE9 pd3dSurface = NULL;
	HRESULT hr = pD3DDevice->CreateOffscreenPlainSurface(
								Width, 
								Height, 
								D3DFORMAT( DIS_Format[ Format ] ),
								D3DPOOL( DIS_Pool[ Pool ] ), 
								&pd3dSurface, 
								pSharedHandle);

	if( hr != D3D_OK )
	{
		if( pd3dSurface )
		{
			pd3dSurface->Release();
			pd3dSurface = NULL;
		}
		return HR_to_DR( hr );
	}

	*ppSurface = new D3D9_Surface2D(pd3dSurface, m_ResourceManager);

	return HR_to_DR( hr );
	
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreatePixelShader(//Creates a pixel shader.
		const UInt32 *pFunction,				//[in] Pointer to the pixel shader function token array, specifying the blending operations. This value cannot be NULL.
		LPPIXELSHADER *ppShader)				// [out, retval]Pointer to the returned pixel shader interface. See LPPIXELSHADER.

{
	/*if( *ppShader )
	{
		return DIS_FAIL;
	}*/
	

	LPDIRECT3DPIXELSHADER9 pd3dPixelShader = NULL;
	HRESULT hr = pD3DDevice->CreatePixelShader(
								(const DWORD*)pFunction, 
								&pd3dPixelShader);

	if( hr != D3D_OK )
	{
		if( pd3dPixelShader )
		{
			pd3dPixelShader->Release();
			pd3dPixelShader = NULL;
		}
		return HR_to_DR( hr );
	}
	
	*ppShader = new D3D9_PixelShader(pd3dPixelShader, m_ResourceManager);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateQuery(//Creates a status query.
        DIS_QUERYTYPE Type,					//[in] Identifies the query type. For more information, see DIS_QUERYTYPE.
		LPQUERY *ppQuery)					//[out, retval]Returns a pointer to the query interface that manages the query object. See LPQUERY. This parameter can be set to NULL to see if a query is supported. If the query is not supported, the method returns D3DERR_NOTAVAILABLE.
{
	if( *ppQuery )
	{
		return DIS_FAIL;
	}
	

	LPDIRECT3DQUERY9 pd3dQuery = NULL;
	HRESULT hr = pD3DDevice->CreateQuery(
								D3DQUERYTYPE( DIS_QueryType[ Type ] ), 
								&pd3dQuery);

	if( hr != D3D_OK )
	{
		if( pd3dQuery )
		{
			pd3dQuery->Release();
			pd3dQuery = NULL;
		}
		return HR_to_DR( hr );
	}
	
	*ppQuery = new D3D9_Query(pd3dQuery, m_ResourceManager);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateRenderTarget(//Creates a render-target surface.
    UInt32 Width,						//[in] Width of the render-target surface, in pixels.
    UInt32 Height,						//[in] Height of the render-target surface, in pixels.
    DIS_FORMAT Format,					//[in]Member of the D3DFORMAT enumerated type, describing the format of the render target.
    DIS_MULTISAMPLE_TYPE MultiSample,	//[in] Member of the D3DMULTISAMPLE_TYPE enumerated type, which describes the multisampling buffer type. This parameter specifies the antialiasing type for this render target. When this surface is passed to IDirect3DDevice9::SetRenderTarget, its multisample type must be the same as that of the depth-stencil set by IDirect3DDevice9::SetDepthStencilSurface.
    UInt32 MultisampleQuality,			//[in]Quality level. The valid range is between zero and one less than the level returned by pQualityLevels used by IDirect3D9::CheckDeviceMultiSampleType. Passing a larger value returns the error, D3DERR_INVALIDCALL. The MultisampleQuality values of paired render targets, depth stencil surfaces, and the multisample type must all match.
    bool Lockable,						//[in]Render targets are not lockable unless the application specifies TRUE for Lockable. Note that lockable render targets reduce performance on some graphics hardware. The readback performance (moving data from video memory to system memory) depends on the type of hardware used (AGP vs. PCI Express) and is usually far lower than upload performance (moving data from system to video memory). If you need read access to render targets, use GetRenderTargetData instead of lockable render targets.
	LPSURFACE2D *ppSurface,				//[out, retval]Address of a pointer to an LPSURFACE2D interface.
    DIS_HANDLE *pSharedHandle)			//[in]Reserved. Set this parameter to NULL. This parameter can be used in DIS_3D 9 for Windows Vista to share resources.
{

	if( *ppSurface )
	{
		return DIS_FAIL;
	}
	

	LPDIRECT3DSURFACE9 pd3dSurface = NULL;
	HRESULT hr = pD3DDevice->CreateRenderTarget(
								Width, 
								Height, 
								D3DFORMAT( DIS_Format[ Format ] ),
								D3DMULTISAMPLE_TYPE( DIS_MultiSampleType[MultiSample]), 
								MultisampleQuality,
								Lockable, 
								&pd3dSurface, 
								pSharedHandle);

	if( hr != D3D_OK )
	{
		if( pd3dSurface )
		{
			pd3dSurface->Release();
			pd3dSurface = NULL;
		}
		return HR_to_DR( hr );
	}

	*ppSurface = new D3D9_Surface2D(pd3dSurface, m_ResourceManager);
	
	
	return HR_to_DR( hr );
	//return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateStateBlock(//Creates a new state block that contains the values for all device states, vertex-related states, or pixel-related states.
	DIS_STATEBLOCKTYPE Type,			//[in] Type of state data that the method should capture. This parameter can be set to a value defined in the D3DSTATEBLOCKTYPE enumerated type.
	LPSTATEBLOCK  *ppSB)					//[out, retval]Pointer to a state block interface. See IDirect3DStateBlock9.
{
	if( *ppSB )
	{
		return DIS_FAIL;
	}
	

	LPDIRECT3DSTATEBLOCK9 pd3dStateBlock = NULL;
	HRESULT hr = pD3DDevice->CreateStateBlock(
								D3DSTATEBLOCKTYPE( DIS_StateBlockType[ Type ] ), 
								&pd3dStateBlock);

	if( hr != D3D_OK )
	{
		if( pd3dStateBlock )
		{
			pd3dStateBlock->Release();
			pd3dStateBlock = NULL;
		}
		return HR_to_DR( hr );
	}
	
	*ppSB = new D3D9_StateBlock(pd3dStateBlock, m_ResourceManager);
	
	return HR_to_DR( hr );
}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateTexture(//Creates a texture resource.
	UInt32 Width,						//[in]   Width of the top-level of the texture, in pixels. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0, 1 will be taken instead.       
	UInt32 Height,						//[in]  Height of the top-level of the texture, in pixels. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0, 1 will be taken instead.        
	UInt32 Levels,						//[in]  Number of levels in the texture. If this is zero, Direct3D will generate all texture sublevels down to 1 by 1 pixels for hardware that supports mipmapped textures. Call IDirect3DBaseTexture9::GetLevelCount to see the number of levels generated.         
	UInt32 Usage,						//[in]    Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants. It is good practice to match the usage parameter with the behavior flags in IDirect3D9::CreateDevice.      
	DIS_FORMAT Format,						//[in]     Member of the D3DFORMAT enumerated type, describing the format of all levels in the texture.      
	DIS_POOL Pool,						//[in]  Member of the D3DPOOL enumerated type, describing the memory class into which the texture should be placed.        
	LPTEXTURE2D *ppTexture,				//[out, retval] Pointer to an IDirect3DTexture9 interface, representing the created texture resource. 
	DIS_HANDLE *pSharedHandle)			//[in]  Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources. 
{
	if( *ppTexture )
	{
		return DIS_FAIL;
	}
	UInt32 usage = 0;// D3DUSAGE_WRITEONLY;
	if( Usage & DIS_USAGE::DIS_USAGE_WRITEONLY )
	{
		usage |= D3DUSAGE_WRITEONLY;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_DYNAMIC )
	{
		usage |= D3DUSAGE_DYNAMIC;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_AUTOGENMIPMAP )
	{
		usage |= D3DUSAGE_AUTOGENMIPMAP ;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_RENDERTARGET )
	{
		usage |= D3DUSAGE_RENDERTARGET;
	}
	
	 
	D3DFORMAT format = D3DFORMAT( DIS_Format[ Format ] );
	D3DPOOL pool = D3DPOOL( DIS_Pool[ Pool ] );
	
	LPDIRECT3DTEXTURE9 pTex = NULL;
	HRESULT hr = pD3DDevice->CreateTexture(
								Width, 
								Height, 
								Levels, 
								usage,
								format,
								pool, 
								&pTex, 
								0);
	
	if( hr != D3D_OK )
	{
		if( pTex )
		{
			pTex->Release();
			pTex = NULL;
		}
		return HR_to_DR( hr );
	}

	*ppTexture = new D3D9_Texture2D(pTex, m_ResourceManager);

	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateVertexBuffer(	//Creates a vertex buffer.
	UInt32 Length,						//[in] Size of the vertex buffer, in bytes. For FVF vertex buffers, Length must be large enough to contain at least one vertex, but it need not be a multiple of the vertex size. Length is not validated for non-FVF buffers. See Remarks.
	UInt32 Usage,						//[in] Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants. It is good practice to match the usage parameter in CreateVertexBuffer with the behavior flags in IDirect3D9::CreateDevice. For more information, see Remarks.
	UInt32 FVF,							//[in] Combination of D3DFVF, a usage specifier that describes the vertex format of the vertices in this buffer. If this parameter is set to a valid FVF code, the created vertex buffer is an FVF vertex buffer (see Remarks). Otherwise, if this parameter is set to zero, the vertex buffer is a non-FVF vertex buffer.
	DIS_POOL Pool,						//[in]Member of the D3DPOOL enumerated type, describing a valid memory class into which to place the resource. Do not set to D3DPOOL_SCRATCH.
	LPVERTEXBUFFER *ppVertexBuffer,	//[out, retval] Address of a pointer to an IDirect3DVertexBuffer9 interface, representing the created vertex buffer resource.
	DIS_HANDLE *pSharedHandle)			//[in]  Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources.
{
	if( *ppVertexBuffer )
	{
		return DIS_FAIL;
	}
	
	UInt32 usage = 0;
	if( Usage & DIS_USAGE::DIS_USAGE_WRITEONLY )
	{
		usage |= D3DUSAGE_WRITEONLY;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_DYNAMIC )
	{
		usage |= D3DUSAGE_DYNAMIC;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_AUTOGENMIPMAP )
	{
		usage |= D3DUSAGE_AUTOGENMIPMAP ;
	}
	if( Usage & DIS_USAGE::DIS_USAGE_RENDERTARGET )
	{
		usage |= D3DUSAGE_RENDERTARGET;
	}


	D3DPOOL pool = D3DPOOL( DIS_Pool[ Pool ] );

	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;

	HRESULT hr = pD3DDevice->CreateVertexBuffer(
								Length, 
								usage, 
								FVF, 
								pool, 												
								&pVB, 
								pSharedHandle);

	if( hr != D3D_OK )
	{
		if( pVB )
		{
			pVB->Release();
			pVB = NULL;
		}
		return HR_to_DR( hr );
	}
	

	*ppVertexBuffer = new D3D9_VertexBuffer(&pVB, m_ResourceManager);

	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateVertexDeclaration(//Create a vertex shader declaration from the device and the vertex elements.
    const DIS_VERTEXELEMENT *pVertexElements,//[in] If the method succeeds, the return value is D3D_OK. If the method fails, the return value can be D3DERR_INVALIDCALL
	LPVERTEXDECLERATION *ppDecl) //[out, retval]See the Vertex Declaration (Direct3D 9) page for a detailed description of how to map vertex declarations between different versions of DirectX.
{
	if( *ppDecl )
	{
		return DIS_FAIL;
	}


	LPDIRECT3DVERTEXDECLARATION9 pvd = NULL;




	HRESULT hr = pD3DDevice->CreateVertexDeclaration(
								(const D3DVERTEXELEMENT9*)pVertexElements, &pvd);
	


	if( hr != D3D_OK )
	{
		if( pvd )
		{
			pvd->Release();
			pvd = NULL;
		}
		return HR_to_DR( hr );
	}

	*ppDecl = new D3D9_VertexDecleration(pvd, m_ResourceManager);

	return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateVertexShader(//Creates a vertex shader.
	const UInt32 *pFunction,//[in] Pointer to an array of tokens that represents the vertex shader, including any embedded debug and symbol table information.
								//Use a function such as D3DXCompileShader to create the array from a HLSL shader.
								//Use a function like D3DXAssembleShader to create the token array from an assembly language shader.
								//Use a function like ID3DXEffectCompiler::CompileShader to create the array from an effect.
	LPVERTEXSHADER *ppShader)//[out, retval]Pointer to the returned vertex shader interface (see LPVERTEXSHADER).

{
	/*if( *ppShader )
	{
		return DIS_FAIL;
	}*/


	LPDIRECT3DVERTEXSHADER9 pVShader = NULL;
	HRESULT hr = pD3DDevice->CreateVertexShader( 
								(const DWORD*)pFunction, 
								&pVShader);

	if( hr != D3D_OK )
	{
		if( pVShader )
		{
			pVShader->Release();
			pVShader = NULL;
		}
		return HR_to_DR( hr );
	}
	
	*ppShader = new D3D9_VertexShader(pVShader, m_ResourceManager);

	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::CreateVolumeTexture(	//Creates a volume texture resource.
	UInt32 Width,					//[in] Width of the top-level of the volume texture, in pixels. This value must be a power of two if the D3DPTEXTURECAPS_VOLUMEMAP_POW2 member of D3DCAPS9 is set. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by two results in 0 (zero), 1 will be taken instead. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
	UInt32 Height,					//[in]Height of the top-level of the volume texture, in pixels. This value must be a power of two if the D3DPTEXTURECAPS_VOLUMEMAP_POW2 member of D3DCAPS9 is set. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0 (zero), 1 will be taken instead. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9
	UInt32 Depth,					//[in]Depth of the top-level of the volume texture, in pixels. This value must be a power of two if the D3DPTEXTURECAPS_VOLUMEMAP_POW2 member of D3DCAPS9 is set. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0 (zero), 1 will be taken instead. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
	UInt32 Levels,					//[in] Number of levels in the texture. If this is zero, Direct3D will generate all texture sublevels down to 1x1 pixels for hardware that supports mipmapped volume textures. Call IDirect3DBaseTexture9::GetLevelCount to see the number of levels generated.
	UInt32 Usage,					//[in]Usage can be 0, which indicates no usage value. If usage is desired, use D3DUSAGE_DYNAMIC or D3DUSAGE_SOFTWAREPROCESSING. For more information, see D3DUSAGE.
	DIS_FORMAT Format,					//[in] Member of the D3DFORMAT enumerated type, describing the format of all levels in the volume texture.
	DIS_POOL Pool,						//[in]Member of the D3DPOOL enumerated type, describing the memory class into which the volume texture should be placed.
	LPVOLUMETEXTURE *ppVolumeTexture,	//[out, retval]Address of a pointer to an IDirect3DVolumeTexture9 interface, representing the created volume texture resource.
	DIS_HANDLE *pSharedHandle)			//[in]Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources.
{
	if( *ppVolumeTexture )
	{
		return DIS_FAIL;
	}
	UInt32 usage = 0;// = D3DUSAGE_DYNAMIC;
	if (Usage & DIS_USAGE::DIS_USAGE_WRITEONLY)
	{
		usage |= D3DUSAGE_WRITEONLY;
	}
	if (Usage & DIS_USAGE::DIS_USAGE_DYNAMIC)
	{
		usage |= D3DUSAGE_DYNAMIC;
	}
	if (Usage & DIS_USAGE::DIS_USAGE_AUTOGENMIPMAP)
	{
		usage |= D3DUSAGE_AUTOGENMIPMAP;
	}
	if (Usage & DIS_USAGE::DIS_USAGE_RENDERTARGET)
	{
		usage |= D3DUSAGE_RENDERTARGET;
	}


	D3DFORMAT format = D3DFORMAT(DIS_Format[Format]);
	D3DPOOL pool = D3DPOOL(DIS_Pool[Pool]);
	
	LPDIRECT3DVOLUMETEXTURE9 pd3dVolTex = NULL;
	HRESULT hr = pD3DDevice->CreateVolumeTexture(
								Width, 
								Height, 
								Depth, 
								Levels, 
								usage,
								format,
								pool,
								&pd3dVolTex,
								pSharedHandle);

	if( hr != D3D_OK )
	{
		if( pd3dVolTex )
		{
			pd3dVolTex->Release();
			pd3dVolTex = NULL;
		}
		return HR_to_DR( hr );
	}
	
	*ppVolumeTexture = new D3D9_VolumeTexture(pd3dVolTex, m_ResourceManager);

	return HR_to_DR( hr );

}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::DeletePatch( UInt32 Handle)// [in]//Frees a cached high-order patch.
{
	HRESULT hr = pD3DDevice->DeletePatch(Handle);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::DrawIndexedPrimitive(//Based on indexing, renders the specified geometric primitive into an array of vertices.
	DIS_PRIMITIVETYPE Type,		//[in] Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render. D3DPT_POINTLIST is not supported with this method. See Remarks.
	UInt32 BaseVertexIndex,		//[in]Offset from the start of the vertex buffer to the first vertex. See Scenario 4.
	UInt32 MinIndex,			//[in] Minimum vertex index for vertices used during this call. This is a zero based index relative to BaseVertexIndex.
	UInt32 NumVertices,			//[in]Number of vertices used during this call. The first vertex is located at index: BaseVertexIndex + MinIndex.
	UInt32 StartIndex,			//[in]Index of the first index to use when accesssing the vertex buffer. Beginning at StartIndex to index vertices from the vertex buffer.
	UInt32 PrimitiveCount)			//[in] Number of primitives to render. The number of vertices used is a function of the primitive count and the primitive type. The maximum number of primitives allowed is determined by checking the MaxPrimitiveCount member of the D3DCAPS9 structure.
{
	HRESULT hr = pD3DDevice->DrawIndexedPrimitive(
								D3DPRIMITIVETYPE(DIS_PrimitiveType[ Type ]), 
								BaseVertexIndex, 
								MinIndex, 
								NumVertices, 
								StartIndex, 
								PrimitiveCount);
	
	return HR_to_DR( hr );
	
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::DrawIndexedPrimitiveUP(//Renders the specified geometric primitive with data specified by a user memory pointer.
	DIS_PRIMITIVETYPE PrimitiveType,		//[in] Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render.
	UInt32 MinVertexIndex,					//[in] Minimum vertex index. This is a zero-based index.
	UInt32 NumVertices,						//[in] Number of vertices used during this call. The first vertex is located at index: MinVertexIndex.
	UInt32 PrimitiveCount,					//[in] Number of primitives to render. The maximum number of primitives allowed is determined by checking the MaxPrimitiveCount member of the D3DCAPS9 structure (the number of indices is a function of the primitive count and the primitive type).
	const void *pIndexData,					//[in] User memory pointer to the index data.
	DIS_FORMAT IndexDataFormat,				//[in] Member of the D3DFORMAT enumerated type, describing the format of the index data. The valid settings are either:
	const void *pVertexStreamZeroData,		//[in] User memory pointer to the vertex data. The vertex data must be in stream 0.
	UInt32 VertexStreamZeroStride)			//[in] The number of bytes of data for each vertex. This value may not be 0.
{
	HRESULT hr = pD3DDevice->DrawIndexedPrimitiveUP(
								D3DPRIMITIVETYPE(DIS_PrimitiveType[ PrimitiveType ]), 
								MinVertexIndex, 
								NumVertices,
								PrimitiveCount, 
								pIndexData, 
								D3DFORMAT( DIS_Format[IndexDataFormat] ), 
								pVertexStreamZeroData,
								VertexStreamZeroStride);
	
	return HR_to_DR( hr );
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT  D3D_DeviceInterface::DrawPrimitive(//Renders a sequence of nonindexed, geometric primitives of the specified type from the current set of data input streams.
	DIS_PRIMITIVETYPE PrimitiveType,//[in]Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render.
	UInt32 StartVertex,//[in]Index of the first vertex to load. Beginning at StartVertex the correct number of vertices will be read out of the vertex buffer.
	UInt32 PrimitiveCount)//[in]Number of primitives to render. The maximum number of primitives allowed is determined by checking the MaxPrimitiveCount member of the D3DCAPS9 structure. PrimitiveCount is the number of primitives as determined by the primitive type. If it is a line list, each primitive has two vertices. If it is a triangle list, each primitive has three vertices.
{
	HRESULT hr = pD3DDevice->DrawPrimitive(
								D3DPRIMITIVETYPE(DIS_PrimitiveType[ PrimitiveType ]), 
								StartVertex, 
								PrimitiveCount );
	
	return HR_to_DR( hr );

}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT  D3D_DeviceInterface::DrawPrimitiveUP(//Renders data specified by a user memory pointer as a sequence of geometric primitives of the specified type.
	DIS_PRIMITIVETYPE PrimitiveType,// [in] Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render.
	UInt32 PrimitiveCount, //[in] Number of primitives to render. The maximum number of primitives allowed is determined by checking the MaxPrimitiveCount member of the D3DCAPS9 structure.
	const void *pVertexStreamZeroData,// [in] User memory pointer to the vertex data.
	UInt32 VertexStreamZeroStride)// [in] The number of bytes of data for each vertex. This value may not be 0.
{
	HRESULT hr = pD3DDevice->DrawPrimitiveUP(
								D3DPRIMITIVETYPE(DIS_PrimitiveType[ PrimitiveType ]), 
								PrimitiveCount,
								pVertexStreamZeroData,
								VertexStreamZeroStride);
	
	return HR_to_DR( hr );
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::DrawRectPatch(//Draws a rectangular patch using the currently set streams.
	UInt32 Handle,//[in]Handle to the rectangular patch to draw.
	const float *pNumSegs,//[in]Pointer to an array of four floating-point values that identify the number of segments each edge of the rectangle patch should be divided into when tessellated. See D3DRECTPATCH_INFO.
	const DIS_RECTPATCH_INFO *pRectPatchInfo)	//[in]Pointer to a D3DRECTPATCH_INFO structure, describing the rectangular patch to draw.
{
	D3DRECTPATCH_INFO inf;
	inf.Basis = (D3DBASISTYPE)this->DIS_DegreeType[ pRectPatchInfo->Basis ];
	inf.Degree = (D3DDEGREETYPE )this->DIS_DegreeType[ pRectPatchInfo->Degree ];
	inf.Height = pRectPatchInfo->Height;
	inf.StartVertexOffsetHeight = pRectPatchInfo->StartVertexOffsetHeight;
	inf.StartVertexOffsetWidth= pRectPatchInfo->StartVertexOffsetWidth;
	inf.Stride = pRectPatchInfo->Stride;
	
	HRESULT hr = pD3DDevice->DrawRectPatch(
								Handle, 
								pNumSegs, 
								&inf);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::DrawTriPatch( //Draws a triangular patch using the currently set streams.
	UInt32 Handle,//[in]Handle to the triangular patch to draw.
	const float *pNumSegs,//[in]Pointer to an array of three floating-point values that identify the number of segments each edge of the triangle patch should be divided into when tessellated. See D3DTRIPATCH_INFO.
	const DIS_TRIPATCH_INFO *pTriPatchInfo)	//[in]Pointer to a D3DTRIPATCH_INFO structure, describing the triangular high-order patch to draw.
{
	D3DTRIPATCH_INFO tpi;
	tpi.Basis = D3DBASISTYPE( this->DIS_PatchEdgeStyle[ pTriPatchInfo->Basis] );
	tpi.Degree = D3DDEGREETYPE( this->DIS_DegreeType[ pTriPatchInfo->Degree] );
	tpi.NumVertices = pTriPatchInfo->NumVertices;
	tpi.StartVertexOffset = pTriPatchInfo->StartVertexOffset;
	
	HRESULT hr = pD3DDevice->DrawTriPatch(
								Handle, 
								pNumSegs, 
								&tpi);
	
	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::EndScene() //Ends a scene that was begun by calling IDirect3DDevice9::BeginScene.
{
	HRESULT hr = pD3DDevice->EndScene();
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::EndStateBlock(//Signals Direct3D to stop recording a device-state block and retrieve a pointer to the state block interface.
	LPSTATEBLOCK *ppSB//[in, retval] 
	)
{

	HRESULT hr = pD3DDevice->EndStateBlock( 
								&(LPSTATEBLOCK_D3D9(ppSB)->pd3dStateBlock));
	
	return HR_to_DR( hr );
	
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::EvictManagedResources() //Evicts all managed resources, including both Direct3D and driver-managed resources.
{
	HRESULT hr = pD3DDevice->EvictManagedResources();
	
	return HR_to_DR( hr );
	//return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE UInt32 D3D_DeviceInterface::GetAvailableTextureMem()//Returns an estimate of the amount of available texture memory.
{
	return pD3DDevice->GetAvailableTextureMem();
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetBackBuffer( //Retrieves a back buffer from the device's swap chain.
		UInt32 iSwapChain,				//[in]An unsigned integer specifying the swap chain.
        UInt32 BackBuffer,				//[in]Index of the back buffer object to return. Back buffers are numbered from 0 to the total number of back buffers minus one. A value of 0 returns the first back buffer, not the front buffer. The front buffer is not accessible through this method. Use IDirect3DDevice9::GetFrontBufferData to retrieve a copy of the front buffer.
        DIS_BACKBUFFER_TYPE Type,		//[in]Stereo view is not supported in Direct3D 9, so the only valid value for this parameter is D3DBACKBUFFER_TYPE_MONO.
		LPSURFACE2D *ppBackBuffer)		// [out, retval]Address of a pointer to an IDirect3DSurface9 interface, representing the returned back buffer surface.
{
	
	HRESULT hr = pD3DDevice->GetBackBuffer(
								iSwapChain, 
								BackBuffer, 
								D3DBACKBUFFER_TYPE( DIS_Backbuffer_type[ Type ]),
								&Surface2DBackBufferForGetFunc.pd3dSurface);
	
	*ppBackBuffer = &Surface2DBackBufferForGetFunc;
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetClipPlane( //Retrieves the coefficients of a user-defined clipping plane for the device.
		UInt32 Index,			//[in] Index of the clipping plane for which the plane equation coefficients are retrieved.
		float *pPlane)			//[out]Pointer to a four-element array of values that represent the coefficients of the clipping plane in the form of the general plane equation. See Remarks.
{
	HRESULT hr = pD3DDevice->GetClipPlane(Index, pPlane);
	
	return HR_to_DR( hr );
	
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetClipStatus(LPCLIPSTATUS pClipStatus) //Retrieves the clip status.
{
	D3DCLIPSTATUS9 cs;
	HRESULT hr = pD3DDevice->GetClipStatus(&cs);
	
	pClipStatus->ClipIntersection = cs.ClipIntersection;
	pClipStatus->ClipUnion = cs.ClipUnion;

	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetCreationParameters( //Retrieves the creation parameters of the device.
	DIS_DEVICE_CREATION_PARAMETERS* pParemeters) // note: get the HWND done
{
	D3DDEVICE_CREATION_PARAMETERS dcp;
	HRESULT hr = pD3DDevice->GetCreationParameters(&dcp);
	
	pParemeters->AdapterOrdinal = dcp.AdapterOrdinal;
	pParemeters->BehaviorFlags = dcp.BehaviorFlags;
	pParemeters->DeviceType = to_DIS.DeviceType( dcp.DeviceType );
	pParemeters->hFocusWindow = (DIS_HWND)dcp.hFocusWindow;
	
	return HR_to_DR( hr );
	//return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetCurrentTexturePalette(UInt32 *pPaletteNumber) //Retrieves the current texture palette.
{
	HRESULT hr = pD3DDevice->GetCurrentTexturePalette(pPaletteNumber);
	
	return HR_to_DR( hr );
	//return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetDepthStencilSurface( //Gets the depth-stencil surface owned by the Direct3DDevice object.
	LPSURFACE2D *ppZStencilSurface//[out, retval]  Address of a pointer to an IDirect3DSurface9 interface, representing the returned depth-stencil surface.
	)
{

	HRESULT hr = pD3DDevice->GetDepthStencilSurface(
								&Surface2DDepthStencilForGetFunc.pd3dSurface);
	
	*ppZStencilSurface = &Surface2DDepthStencilForGetFunc;
	
	return HR_to_DR( hr );
}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetDeviceCaps( //Retrieves the capabilities of the rendering device.
	DIS_CAPS *pCaps)//[out]Pointer to a D3DCAPS9 structure, describing the returned device.
{
	D3DCAPS9 caps;
	HRESULT hr = pD3DDevice->GetDeviceCaps(&caps);
	
	pCaps->AdapterOrdinal = caps.AdapterOrdinal;
	pCaps->AdapterOrdinalInGroup = caps.AdapterOrdinalInGroup;
	pCaps->AlphaCmpCaps = caps.AlphaCmpCaps;
	pCaps->Caps = caps.Caps;
	pCaps->Caps2 = caps.Caps2;
	pCaps->Caps3 = caps.Caps3;
	pCaps->CubeTextureFilterCaps = caps.CubeTextureFilterCaps;
	pCaps->CursorCaps = caps.CursorCaps;
	pCaps->DeclTypes = caps.DeclTypes;
	pCaps->DestBlendCaps = caps.DestBlendCaps;
	pCaps->DevCaps = caps.DevCaps;
	pCaps->DevCaps2 = caps.DevCaps2;
	pCaps->DeviceType = to_DIS.DeviceType(caps.DeviceType);
	pCaps->ExtentsAdjust = caps.ExtentsAdjust;
	pCaps->FVFCaps = caps.FVFCaps; 
	pCaps->GuardBandBottom = caps.GuardBandBottom;
	pCaps->GuardBandLeft = caps.GuardBandLeft;
	pCaps->GuardBandRight = caps.GuardBandRight;
	pCaps->GuardBandTop = caps.GuardBandTop;
	pCaps->LineCaps = caps.LineCaps;
	pCaps->MasterAdapterOrdinal= caps.MasterAdapterOrdinal;
	pCaps->MaxActiveLights = caps.MaxActiveLights;
	pCaps->MaxAnisotropy = caps.MaxAnisotropy;
	pCaps->MaxPixelShader30InstructionSlots = caps.MaxPixelShader30InstructionSlots;
	pCaps->MaxPointSize = caps.MaxPointSize;
	pCaps->MaxPrimitiveCount = caps.MaxPrimitiveCount;
	//caps.MaxNpatchTessellationLevel;
	pCaps->MaxPShaderInstructionsExecuted = caps.MaxPShaderInstructionsExecuted;
	pCaps->MaxSimultaneousTextures = caps.MaxSimultaneousTextures;
	pCaps->MaxStreams = caps.MaxStreams;
	pCaps->MaxStreamStride = caps.MaxStreamStride;
	pCaps->MaxTextureAspectRatio = caps.MaxTextureAspectRatio;
	pCaps->MaxTextureBlendStages = caps.MaxTextureBlendStages;
	pCaps->MaxTextureHeight = caps.MaxTextureHeight;
	pCaps->MaxTextureRepeat = caps.MaxTextureRepeat;
	pCaps->MaxTextureWidth = caps.MaxTextureWidth;
	pCaps->MaxUserClipPlanes = caps.MaxUserClipPlanes;
	pCaps->MaxVertexBlendMatrices = caps.MaxVertexBlendMatrices;
	pCaps->MaxVertexIndex = caps.MaxVertexIndex;
	pCaps->MaxVertexShader30InstructionSlots = caps.MaxVertexShader30InstructionSlots;
	pCaps->MaxVertexShaderConst = caps.MaxVertexShaderConst;
	pCaps->MaxVertexW = caps.MaxVertexW;
	pCaps->MaxVolumeExtent = caps.MaxVolumeExtent;
	pCaps->MaxVShaderInstructionsExecuted = caps.MaxVShaderInstructionsExecuted;
	pCaps->NumberOfAdaptersInGroup = caps.NumberOfAdaptersInGroup;
	pCaps->NumSimultaneousRTs = caps.NumSimultaneousRTs;
	pCaps->PixelShader1xMaxValue = caps.PixelShader1xMaxValue;
	pCaps->PixelShaderVersion = caps.PixelShaderVersion;
	pCaps->PresentationIntervals = caps.PresentationIntervals;
	pCaps->PrimitiveMiscCaps = caps.PrimitiveMiscCaps;
	//pCaps->PS20Caps = caps.PS20Caps;
//pCaps->DeviceType = to_DIS.DeviceType(caps.DeviceType);
	pCaps->RasterCaps = caps.RasterCaps;
	pCaps->ShadeCaps = caps.ShadeCaps;
	pCaps->SrcBlendCaps = caps.SrcBlendCaps;
	pCaps->StencilCaps = caps.StencilCaps;
	pCaps->StretchRectFilterCaps = caps.StretchRectFilterCaps;
	pCaps->TextureAddressCaps = caps.TextureAddressCaps;
	pCaps->TextureCaps = caps.TextureCaps;
	pCaps->TextureFilterCaps = caps.TextureFilterCaps;
	pCaps->TextureOpCaps = caps.TextureOpCaps;
	pCaps->VertexProcessingCaps = caps.VertexProcessingCaps;
	pCaps->VertexShaderVersion = caps.VertexShaderVersion;
	pCaps->VertexTextureFilterCaps = caps.VertexTextureFilterCaps;
	pCaps->VolumeTextureAddressCaps = caps.VolumeTextureAddressCaps;
	pCaps->VolumeTextureFilterCaps = caps.VolumeTextureFilterCaps;
	//pCaps->VS20Caps = caps.VS20Caps;
//pCaps->DeviceType = to_DIS.DeviceType(caps.DeviceType);
	pCaps->ZCmpCaps = caps.ZCmpCaps;

	return HR_to_DR( hr );

}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
//bool GetDirect3D(); //Returns an interface to the instance of the Direct3D object that created the device.
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetDisplayMode(//Retrieves the display mode's spatial resolution, color resolution, and refresh frequency.
	UInt32  iSwapChain,				//[in]An unsigned integer specifying the swap chain.
	DIS_DISPLAYMODE *pMode)			//[out]  Pointer to a D3DDISPLAYMODE structure containing data about the display mode of the adapter. As opposed to the display mode of the device, which may not be active if the device does not own full-screen mode.
{
	D3DDISPLAYMODE mode;
	HRESULT hr = pD3DDevice->GetDisplayMode(
								iSwapChain, 
								&mode);


	pMode->Format = to_DIS.dFormat(mode.Format);
	pMode->Width = mode.Width;
	pMode->Height = mode.Height;
	pMode->RefreshRate = mode.RefreshRate;

	return HR_to_DR( hr );
	//return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetFrontBufferData( //Generates a copy of the device's front buffer and places that copy in a system memory buffer provided by the application.
	UInt32  iSwapChain,				//[in] An unsigned integer specifying the swap chain.
	LPSURFACE2D pDestSurface)		//	[in] Pointer to an IDirect3DSurface9 interface that will receive a copy of the contents of the front buffer. The data is returned in successive rows with no intervening space, starting from the vertically highest row on the device's output to the lowest.
//For windowed mode, the size of the destination surface should be the size of the desktop. For full-screen mode, the size of the destination surface should be the screen size.
{

	if( pDestSurface == NULL )
	{
		// work out what to do with this :/
	//	pDestSurface = new D3D9_Surface2D;
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->GetFrontBufferData(
								iSwapChain, 
								LPSURFACE2D_D3D9(pDestSurface)->pd3dSurface);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetFVF(UInt32 *pFVF) //Gets the fixed vertex function declaration.
{
	HRESULT hr = pD3DDevice->GetFVF((DWORD*)pFVF);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetGammaRamp( //Retrieves the gamma correction ramp for the swap chain.
    UInt32  iSwapChain, //[in]An unsigned integer specifying the swap chain.
	DIS_GAMMARAMP *pRamp)//	[in, out]Pointer to an application-supplied D3DGAMMARAMP structure to fill with the gamma correction ramp.
{
	D3DGAMMARAMP rmp;
	pD3DDevice->GetGammaRamp(iSwapChain, &rmp);
	
	for( int i=0; i< 256; i++ )
	{
		pRamp->red[i] = rmp.red[i];
		pRamp->green[i] = rmp.green[i];
		pRamp->blue[i] = rmp.blue[i];
	}

	return DIS_OK;
	
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetIndices(  //Retrieves index data.
	LPINDEXBUFFER *ppIndexData)//[out]Address of a pointer to an IDirect3DIndexBuffer9 interface, representing the returned index data.
{
	HRESULT hr = pD3DDevice->GetIndices(
								&IndexBufferForGetFunc.pd3dIndexBuffer);
	
	*ppIndexData = &IndexBufferForGetFunc;
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetLight( //Retrieves a set of lighting properties that this device uses.
	UInt32 Index, //[in]Zero-based index of the lighting property set to retrieve. This method will fail if a lighting property has not been set for this index by calling the IDirect3DDevice9::SetLight method.
	DIS_LIGHT  *pLight)//[in]Pointer to a D3DLIGHT9 structure that is filled with the retrieved lighting-parameter set.
{
	D3DLIGHT9 light;
	HRESULT hr = pD3DDevice->GetLight(Index, &light);
	
	pLight->Ambient.r = light.Ambient.r;
	pLight->Ambient.g = light.Ambient.g;
	pLight->Ambient.b = light.Ambient.b;
	pLight->Ambient.a = light.Ambient.a;

	pLight->Diffuse.r = light.Diffuse.r;
	pLight->Diffuse.g = light.Diffuse.g;
	pLight->Diffuse.b = light.Diffuse.b;
	pLight->Diffuse.a = light.Diffuse.a;

	pLight->Specular.r = light.Specular.r;
	pLight->Specular.g = light.Specular.g;
	pLight->Specular.b = light.Specular.b;
	pLight->Specular.a = light.Specular.a;

	pLight->Position.x = light.Position.x;
	pLight->Position.y = light.Position.y;
	pLight->Position.z = light.Position.z;

	pLight->Direction.x = light.Direction.x;
	pLight->Direction.y = light.Direction.y;
	pLight->Direction.z = light.Direction.z;

	pLight->Attenuation0 = light.Attenuation0;
	pLight->Attenuation1 = light.Attenuation1;
	pLight->Attenuation2 = light.Attenuation2;

	pLight->Falloff = light.Falloff;
	pLight->Phi = light.Phi;
	pLight->Range = light.Range;
	pLight->Theta = light.Theta;
	pLight->Type = to_DIS.LightType( light.Type );
	
	return HR_to_DR( hr );
	
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetLightEnable( //Retrieves the activity status - enabled or disabled - for a set of lighting parameters within a device.
	UInt32 Index,//[in] Zero-based index of the set of lighting parameters that are the target of this method.
	bool *pEnable)	//[out, retval]Pointer to a variable to fill with the status of the specified lighting parameters. After the call, a nonzero value at this address indicates that the specified lighting parameters are enabled; a value of 0 indicates that they are disabled.
{
	HRESULT hr = pD3DDevice->GetLightEnable(Index, (BOOL*)pEnable);
	
	return HR_to_DR( hr );
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetMaterial( //Retrieves the current material properties for the device.
	DIS_MATERIAL  *pMaterial) // Pointer to a D3DMATERIAL9 structure to fill with the currently set material properties.
{
	D3DMATERIAL9 mat;
	HRESULT hr = pD3DDevice->GetMaterial(&mat);
	
	pMaterial->Ambient.r = mat.Ambient.r;
	pMaterial->Ambient.g = mat.Ambient.g;
	pMaterial->Ambient.b = mat.Ambient.b;
	pMaterial->Ambient.a = mat.Ambient.a;

	pMaterial->Diffuse.r = mat.Diffuse.r;
	pMaterial->Diffuse.g = mat.Diffuse.g;
	pMaterial->Diffuse.b = mat.Diffuse.b;
	pMaterial->Diffuse.a = mat.Diffuse.a;

	pMaterial->Specular.r = mat.Specular.r;
	pMaterial->Specular.g = mat.Specular.g;
	pMaterial->Specular.b = mat.Specular.b;
	pMaterial->Specular.a = mat.Specular.a;

	pMaterial->Emissive.r = mat.Emissive.r;
	pMaterial->Emissive.g = mat.Emissive.g;
	pMaterial->Emissive.b = mat.Emissive.b;
	pMaterial->Emissive.a = mat.Emissive.a;
	
	pMaterial->Power = mat.Power;
	
	return HR_to_DR( hr );
	
	
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE float D3D_DeviceInterface::GetNPatchMode() //Gets the N-patch mode segments.
{
	return pD3DDevice->GetNPatchMode();
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE UInt32 D3D_DeviceInterface::GetNumberOfSwapChains() //Gets the number of implicit swap chains.
{
	return pD3DDevice->GetNumberOfSwapChains();
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetPaletteEntries( //Retrieves palette entries.
    UInt32 PaletteNumber,//[in]An ordinal value identifying the particular palette to retrieve.
	DIS_PALETTEENTRY *pEntries)//[in, out]Pointer to a PALETTEENTRY structure, representing the returned palette entries.
{
	PALETTEENTRY pE;
	
	HRESULT hr = pD3DDevice->GetPaletteEntries(PaletteNumber, &pE);
	
	pEntries->peRed = pE.peRed;
	pEntries->peGreen = pE.peGreen;
	pEntries->peBlue = pE.peBlue;
	pEntries->peFlags = pE.peFlags;

	return HR_to_DR( hr );
		
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetPixelShader( //Retrieves the currently set pixel shader.
	LPPIXELSHADER *ppShader //[out, retval]If the method succeeds, the return value is D3D_OK. If the method fails, the return value can be D3DERR_INVALIDCALL.
	)
{
	HRESULT hr = pD3DDevice->GetPixelShader(
			&PixelShaderForGetFunc.pd3dPixelShader);
	
	*ppShader = &PixelShaderForGetFunc;//new D3D9_PixelShader(pd3dPixelShader, m_ResourceManager);

	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetPixelShaderConstantB( //Gets a Boolean shader constant.
    UInt32 StartRegister,//[in] Register number that will contain the first constant value.
	bool *pConstantData,//[in, out]Pointer to an array of constants.
    UInt32 BoolCount//[in] Number of Boolean values in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->GetPixelShaderConstantB(StartRegister, 
											(BOOL*)pConstantData, BoolCount);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetPixelShaderConstantF( //Gets a floating-point shader constant.
    UInt32 StartRegister,//[in]Register number that will contain the first constant value.
	float *pConstantData,//[in, out]Pointer to an array of constants.
	UInt32 Vector4fCount//[in]Number of four float vectors in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->GetPixelShaderConstantF(StartRegister, 
											pConstantData, Vector4fCount);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetPixelShaderConstantI( //Gets an integer shader constant.
    UInt32 StartRegister,//[in] Register number that will contain the first constant value.
	int *pConstantData,//[in, out]Pointer to an array of constants.
        UInt32 Vector4iCount//[in]Number of four integer vectors in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->GetPixelShaderConstantI(StartRegister, 
											pConstantData, Vector4iCount);
	
	return HR_to_DR( hr );
	
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetRasterStatus( //Returns information describing the raster of the monitor on which the swap chain is presented.
	UInt32  iSwapChain,//[in]An unsigned integer specifying the swap chain.
	DIS_RASTER_STATUS *pRasterStatus // [out]Pointer to a D3DRASTER_STATUS structure filled with information about the position or other status of the raster on the monitor driven by this adapter.
	)
{
	D3DRASTER_STATUS rs;
	HRESULT hr = pD3DDevice->GetRasterStatus(iSwapChain, &rs);
	
	pRasterStatus->InVBlank = rs.InVBlank;
	pRasterStatus->ScanLine = rs.ScanLine;

	return HR_to_DR( hr );

	
}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetRenderState( //Retrieves a render-state value for a device.
    DIS_RENDERSTATETYPE State,//[in]Device state variable that is being queried. This parameter can be any member of the D3DRENDERSTATETYPE enumerated type.
	UInt32 *pValue//[out, retval] Pointer to a variable that receives the value of the queried render state variable when the method returns.
	)	
{

	D3DRENDERSTATETYPE d3dState = D3DRENDERSTATETYPE(DIS_RenderStateType[ State ]);
	DWORD value;
	/*HRESULT hr = pD3DDevice->GetRenderState(
								d3dState, 
								&value);
								*/
#ifndef SLOW_MODE
	HRESULT hr = m_RenderStateSetter[d3dState]->GetState((UInt32)State, (UInt32*)&value);

#else
	switch( d3dState )
	{
	case D3DRS_ZENABLE: 
		{
//Depth-buffering state as one member of the D3DZBUFFERTYPE enumerated type. Set this state to D3DZB_TRUE to enable z-buffering, D3DZB_USEW to enable w-buffering, or D3DZB_FALSE to disable depth buffering.
//The default value for this render state is D3DZB_TRUE if a depth stencil was created along with the swap chain by setting the EnableAutoDepthStencil member of the D3DPRESENT_PARAMETERS structure to TRUE, and D3DZB_FALSE otherwise.
			if( value == D3DZB_TRUE )
			{
				*pValue = DIS_ZB_TRUE;
			}
			else
			{
				*pValue = DIS_ZB_FALSE;
			}
		}
		break;
	case D3DRS_FILLMODE:
		{
//One or more members of the D3DFILLMODE enumerated type. The default value is D3DFILL_SOLID
			*pValue = to_DIS.FillMode( (D3DFILLMODE)value );
		}
		break;

	case D3DRS_SHADEMODE:
		{
			*pValue = to_DIS.dShadeMode( (D3DSHADEMODE)value );
//One or more members of the D3DSHADEMODE enumerated type. The default value is D3DSHADE_GOURAUD
		}
		break;

	case D3DRS_ZWRITEENABLE:
		{
			*pValue = value;
//TRUE to enable the application to write to the depth buffer. The default value is TRUE. This member enables an application to prevent the system from updating the depth buffer with new depth values. If FALSE, depth comparisons are still made according to the render state D3DRS_ZFUNC, assuming that depth buffering is taking place, but depth values are not written to the buffer.
		}
		break;
	case D3DRS_ALPHATESTENABLE:
		{
			*pValue = value;
//TRUE to enable per pixel alpha testing. If the test passes, the pixel is processed by the frame buffer. Otherwise, all frame-buffer processing is skipped for the pixel.
//The test is done by comparing the incoming alpha value with the reference alpha value, using the comparison function provided by the D3DRS_ALPHAFUNC render state. The reference alpha value is determined by the value set for D3DRS_ALPHAREF. For more information, see Alpha Testing State (Direct3D 9).
//The default value of this parameter is FALSE.
		}
		break;
	case D3DRS_LASTPIXEL:
		{
			*pValue = value;
//The default value is TRUE, which enables drawing of the last pixel in a line. To prevent drawing of the last pixel, set this value to FALSE. For more information, see Outline and Fill State (Direct3D 9).
		}
		break;

	case D3DRS_SRCBLEND:
		{
			*pValue = to_DIS.BlendType( D3DBLEND( value ) );
//One member of the D3DBLEND enumerated type. The default value is D3DBLEND_ONE
		}
		break;
	case D3DRS_DESTBLEND:
		{
			*pValue = to_DIS.BlendType( D3DBLEND( value ) );
//One member of the D3DBLEND enumerated type. The default value is D3DBLEND_ZERO.
		}
		break;
	case D3DRS_CULLMODE:
		{
			*pValue = to_DIS.CullMode( D3DCULL( value ) );
//Specifies how back-facing triangles are culled, if at all. This can be set to one member of the D3DCULL enumerated type. The default value is D3DCULL_CCW.
		}
		break;

	case D3DRS_ZFUNC:
		{
			*pValue = to_DIS.CompareFunc( D3DCMPFUNC( value ) );
//One member of the D3DCMPFUNC enumerated type. The default value is D3DCMP_LESSEQUAL. This member enables an application to accept or reject a pixel, based on its distance from the camera.
//The depth value of the pixel is compared with the depth-buffer value. If the depth value of the pixel passes the comparison function, the pixel is written.
//The depth value is written to the depth buffer only if the render state is TRUE.
//Software rasterizers and many hardware accelerators work faster if the depth test fails, because there is no need to filter and modulate the texture if the pixel is not going to be rendered.
		}
		break;
	case D3DRS_ALPHAREF:
		{
			*pValue = value;
//Value that specifies a reference alpha value against which pixels are tested when alpha testing is enabled. This is an 8-bit value placed in the low 8 bits of the DWORD render-state value. Values can range from 0x00000000 through 0x000000FF. The default value is 0.
		}
		break;
	case D3DRS_ALPHAFUNC:
		{
			*pValue = to_DIS.CompareFunc( D3DCMPFUNC( value ) );
//One member of the D3DCMPFUNC enumerated type. The default value is D3DCMP_ALWAYS. This member enables an application to accept or reject a pixel, based on its alpha value.
		}
		break;

	case D3DRS_DITHERENABLE:
		{
			*pValue = value;
//TRUE to enable dithering. The default value is FALSE.
		}
		break;

	case D3DRS_ALPHABLENDENABLE:
		{
			*pValue = value;
//TRUE to enable alpha-blended transparency. The default value is FALSE.
//The type of alpha blending is determined by the D3DRS_SRCBLEND and D3DRS_DESTBLEND render states.
		}
		break;
	case D3DRS_FOGENABLE:
		{
			*pValue = value;
//TRUE to enable fog blending. The default value is FALSE. For more information about using fog blending, see Fog.
		}
		break;
	case D3DRS_SPECULARENABLE:
		{
			*pValue = value;
//TRUE to enable specular highlights. The default value is FALSE.
//Specular highlights are calculated as though every vertex in the object being lit is at the object's origin. This gives the expected results as long as the object is modeled around the origin and the distance from the light to the object is relatively large. In other cases, the results as undefined.
//When this member is set to TRUE, the specular color is added to the base color after the texture cascade but before alpha blending.
		}
		break;
	case D3DRS_FOGCOLOR:
		{
			*pValue = value;
//Value whose type is D3DCOLOR. The default value is 0. For more information about fog color, see Fog Color (Direct3D 9).
		}
		break;
	
	case D3DRS_FOGTABLEMODE:
		{
			*pValue = to_DIS.FogMode( D3DFOGMODE( value ));
//The fog formula to be used for pixel fog. Set to one of the members of the D3DFOGMODE enumerated type. The default value is D3DFOG_NONE. For more information about pixel fog, see Pixel Fog (Direct3D 9).
		}
		break;
	case D3DRS_FOGSTART:
		{
			*pValue = value;
//Depth at which pixel or vertex fog effects begin for linear fog mode. The default value is 0.0f. Depth is specified in world space for vertex fog and either device space [0.0, 1.0] or world space for pixel fog. For pixel fog, these values are in device space when the system uses z for fog calculations and world-world space when the system is using eye-relative fog (w-fog). For more information, see Fog Parameters (Direct3D 9) and Eye-Relative vs. Z-based Depth.
//Values for this render state are floating-point values. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
//pDevice9->SetRenderState(D3DRS_FOGSTART, 
//                         *((DWORD*) (&fFogStart)));
		}
		break;
	case D3DRS_FOGEND:
		{
			*pValue = value;
//Depth at which pixel or vertex fog effects end for linear fog mode. The default value is 1.0f. Depth is specified in world space for vertex fog and either device space [0.0, 1.0] or world space for pixel fog. For pixel fog, these values are in device space when the system uses z for fog calculations and in world space when the system is using eye-relative fog (w-fog). For more information, see Fog Parameters (Direct3D 9) and Eye-Relative vs. Z-based Depth.
//Values for this render state are floating-point values. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
//m_pDevice9->SetRenderState(D3DRS_FOGEND, *((DWORD*) (&fFogEnd)));
		}
		break;
	case D3DRS_FOGDENSITY:
		{
			*pValue = value;
//Fog density for pixel or vertex fog used in the exponential fog modes (D3DFOG_EXP and D3DFOG_EXP2). Valid density values range from 0.0 through 1.0. The default value is 1.0. For more information, see Fog Parameters (Direct3D 9).
//Values for this render state are floating-point values. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
//    m_pDevice9->SetRenderState(D3DRS_FOGDENSITY, *((DWORD*) (&fFogDensity)));
		}
		break;
	case D3DRS_RANGEFOGENABLE:
		{
			*pValue = value;
//TRUE to enable range-based vertex fog. The default value is FALSE, in which case the system uses depth-based fog. In range-based fog, the distance of an object from the viewer is used to compute fog effects, not the depth of the object (that is, the z-coordinate) in the scene. In range-based fog, all fog methods work as usual, except that they use range instead of depth in the computations.
//Range is the correct factor to use for fog computations, but depth is commonly used instead because range is time-consuming to compute and depth is generally already available. Using depth to calculate fog has the undesirable effect of having the fogginess of peripheral objects change as the viewer's eye moves - in this case, the depth changes and the range remains constant.
//Because no hardware currently supports per-pixel range-based fog, range correction is offered only for vertex fog.
//For more information, see Vertex Fog (Direct3D 9).
		}
		break;
	case D3DRS_STENCILENABLE:
		{
			*pValue = value;
//TRUE to enable stenciling, or FALSE to disable stenciling. The default value is FALSE. For more information, see Stencil Buffer Techniques (Direct3D 9).
		}
		break;
	case D3DRS_STENCILFAIL:
		{
			*pValue = to_DIS.dStencilOp(D3DSTENCILOP(value));
//Stencil operation to perform if the stencil test fails. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP.
		}
		break;
	case D3DRS_STENCILZFAIL:
		{
			*pValue = to_DIS.dStencilOp(D3DSTENCILOP(value));
//Stencil operation to perform if the stencil test passes and the depth test (z-test) fails. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP.
		}
		break;
	case D3DRS_STENCILPASS:
		{
			*pValue = to_DIS.dStencilOp(D3DSTENCILOP(value));
//Stencil operation to perform if both the stencil and the depth (z) tests pass. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP.
		}
		break;
	case D3DRS_STENCILFUNC:
		{
			*pValue = to_DIS.CompareFunc(D3DCMPFUNC(value));
//Comparison function for the stencil test. Values are from the D3DCMPFUNC enumerated type. The default value is D3DCMP_ALWAYS.
//The comparison function is used to compare the reference value to a stencil buffer entry. This comparison applies only to the bits in the reference value and stencil buffer entry that are set in the stencil mask (set by the D3DRS_STENCILMASK render state). If TRUE, the stencil test passes.
		}
		break;
	case D3DRS_STENCILREF:
		{
			*pValue = value;
//An int reference value for the stencil test. The default value is 0.
		}
		break;
	case D3DRS_STENCILMASK:
		{
			*pValue = value;
//Mask applied to the reference value and each stencil buffer entry to determine the significant bits for the stencil test. The default mask is 0xFFFFFFFF.
		}
		break;
	case D3DRS_STENCILWRITEMASK:
		{
			*pValue = value;
//Write mask applied to values written into the stencil buffer. The default mask is 0xFFFFFFFF.
		}
		break;
	case D3DRS_TEXTUREFACTOR:
		{
			*pValue = value;
//Color used for multiple-texture blending with the D3DTA_TFACTOR texture-blending argument or the D3DTOP_BLENDFACTORALPHA texture-blending operation. The associated value is a D3DCOLOR variable. The default value is opaque white (0xFFFFFFFF).
		}
		break;
	case D3DRS_WRAP0:
		{
			*pValue = value;
//Texture-wrapping behavior for multiple sets of texture coordinates. Valid values for this render state can be any combination of the D3DWRAPCOORD_0 (or D3DWRAP_U), D3DWRAPCOORD_1 (or D3DWRAP_V), D3DWRAPCOORD_2 (or D3DWRAP_W), and D3DWRAPCOORD_3 flags. These cause the system to wrap in the direction of the first, second, third, and fourth dimensions, sometimes referred to as the s, t, r, and q directions, for a given texture. The default value for this render state is 0 (wrapping disabled in all directions).
		}
		break;
	case D3DRS_WRAP1: 
		{
			*pValue = value; 
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP2:
		{
//See D3DRS_WRAP0.
			*pValue = value; 
		}
		break;

	case D3DRS_WRAP3:
		{
			*pValue = value; 
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP4:
		{
			*pValue = value; 
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP5:
		{
			*pValue = value; 
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP6:
		{
			*pValue = value; 
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP7:
		{
			*pValue = value; 
//See D3DRS_WRAP0.
		}
		break;

	case D3DRS_CLIPPING:
		{
			*pValue = value;
//TRUE to enable primitive clipping by Direct3D, or FALSE to disable it. The default value is TRUE.
		}
		break;
	case D3DRS_LIGHTING:
		{
			*pValue = value;
//TRUE to enable Direct3D lighting, or FALSE to disable it. The default value is TRUE. Only vertices that include a vertex normal are properly lit; vertices that do not contain a normal employ a dot product of 0 in all lighting calculations.
		}
		break;
	case D3DRS_AMBIENT:
		{
			*pValue = value;
//Ambient light color. This value is of type D3DCOLOR. The default value is 0.
		}
		break;
	case D3DRS_FOGVERTEXMODE:
		{
			*pValue = to_DIS.FogMode( D3DFOGMODE(value) );
//Fog formula to be used for vertex fog. Set to one member of the D3DFOGMODE enumerated type. The default value is D3DFOG_NONE.
		}
		break;
	case D3DRS_COLORVERTEX:
		{
			*pValue = value;
//TRUE to enable per-vertex color or FALSE to disable it. The default value is TRUE. Enabling per-vertex color allows the system to include the color defined for individual vertices in its lighting calculations.
//For more information, see the following render states:
		}
		break;

	case D3DRS_LOCALVIEWER:
		{
			*pValue = value;
//TRUE to enable camera-relative specular highlights, or FALSE to use orthogonal specular highlights. The default value is TRUE. Applications that use orthogonal projection should specify FALSE.
		}
		break;
	case D3DRS_NORMALIZENORMALS:
		{
			*pValue = value;
//TRUE to enable automatic normalization of vertex normals, or FALSE to disable it. The default value is FALSE. Enabling this feature causes the system to normalize the vertex normals for vertices after transforming them to camera space, which can be computationally time-consuming.
		}
		break;
	case D3DRS_DIFFUSEMATERIALSOURCE:
		{
			*pValue = to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(value) );
//Diffuse color source for lighting calculations. Valid values are members of the D3DMATERIALCOLORSOURCE enumerated type. The default value is D3DMCS_COLOR1. The value for this render state is used only if the D3DRS_COLORVERTEX render state is set to TRUE.
		}
		break;
	case D3DRS_SPECULARMATERIALSOURCE:
		{
			*pValue = to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(value) );
//Specular color source for lighting calculations. Valid values are members of the D3DMATERIALCOLORSOURCE enumerated type. The default value is D3DMCS_COLOR2.
		}
		break;
	case D3DRS_AMBIENTMATERIALSOURCE:
		{
			*pValue = to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(value) );
//Ambient color source for lighting calculations. Valid values are members of the D3DMATERIALCOLORSOURCE enumerated type. The default value is D3DMCS_MATERIAL.
		}
		break;
	case D3DRS_EMISSIVEMATERIALSOURCE:
		{
			*pValue = to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(value) );
//Emissive color source for lighting calculations. Valid values are members of the D3DMATERIALCOLORSOURCE enumerated type. The default value is D3DMCS_MATERIAL.
		}
		break;
	case D3DRS_VERTEXBLEND:
		{
			*pValue = to_DIS.dVertexBlendFlags( D3DVERTEXBLENDFLAGS(value) );
//Number of matrices to use to perform geometry blending, if any. Valid values are members of the D3DVERTEXBLENDFLAGS enumerated type. The default value is D3DVBF_DISABLE.
		}
		break;
	case D3DRS_CLIPPLANEENABLE:
		{
			*pValue = value;
//Enables or disables user-defined clipping planes. 
//Valid values are any DWORD in which the status of each bit (set or not set) toggles the activation state 
//of a corresponding user-defined clipping plane. 
//The least significant bit (bit 0) controls the first clipping plane at index 0, and subsequent bits control the activation of clipping planes at higher indexes. 
//If a bit is set, the system applies the appropriate clipping plane during scene rendering. The default value is 0.
//The D3DCLIPPLANEn macros are defined to provide a convenient way to enable clipping planes.
		}
		break;
	case D3DRS_POINTSIZE:
		{
			*pValue = value;
//A float value that specifies the size to use for point size computation in cases where point size is not specified for each vertex. This value is not used when the vertex contains point size. This value is in screen space units if D3DRS_POINTSCALEENABLE is FALSE; otherwise this value is in world space units. The default value is the value a driver returns. If a driver returns 0 or 1, the default value is 64, which allows software point size emulation. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
		}
		break;
//m_pDevice9->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&pointSize));
	case D3DRS_POINTSIZE_MIN:
		{
			*pValue = value;
//A float value that specifies the minimum size of point primitives. Point primitives are clamped to this size during rendering. Setting this to values smaller than 1.0 results in points dropping out when the point does not cover a pixel center and antialiasing is disabled or being rendered with reduced intensity when antialiasing is enabled. The default value is 1.0f. The range for this value is greater than or equal to 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
//m_pDevice9->SetRenderState(D3DRS_POINTSIZE_MIN, *((DWORD*)&pointSizeMin));
		}
		break;
	case D3DRS_POINTSPRITEENABLE:
		{
			*pValue = value;
//bool value. When TRUE, texture coordinates of point primitives are set so that full textures are mapped on each point. When FALSE, the vertex texture coordinates are used for the entire point. The default value is FALSE. You can achieve DirectX 7 style single-pixel points by setting D3DRS_POINTSCALEENABLE to FALSE and D3DRS_POINTSIZE to 1.0, which are the default values.
		}
		break;
	case D3DRS_POINTSCALEENABLE:
		{
			*pValue = value;
//bool value that controls computation of size for point primitives. When TRUE, the point size is interpreted as a camera space value and is scaled by the distance function and the frustum to viewport y-axis scaling to compute the final screen-space point size. When FALSE, the point size is interpreted as screen space and used directly. The default value is FALSE.
		}
		break;
	case D3DRS_POINTSCALE_A:
		{
			*pValue = value;
//A float value that controls for distance-based size attenuation for point primitives. Active only when D3DRS_POINTSCALEENABLE is TRUE. The default value is 1.0f. The range for this value is greater than or equal to 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
//m_pDevice9->SetRenderState(D3DRS_POINTSCALE_A, *((DWORD*)&pointScaleA));
		}
		break;
	case D3DRS_POINTSCALE_B:
		{
			*pValue = value;
//A float value that controls for distance-based size attenuation for point primitives. Active only when D3DRS_POINTSCALEENABLE is TRUE. The default value is 0.0f. The range for this value is greater than or equal to 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
//m_pDevice9->SetRenderState(D3DRS_POINTSCALE_B, *((DWORD*)&pointScaleB));
		}
		break;
	case D3DRS_POINTSCALE_C:
		{
			*pValue = value;
//A float value that controls for distance-based size attenuation for point primitives. Active only when D3DRS_POINTSCALEENABLE is TRUE. The default value is 0.0f. The range for this value is greater than or equal to 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
//m_pDevice9->SetRenderState(D3DRS_POINTSCALE_C, *((DWORD*)&pointScaleC));
		}
		break;
	case D3DRS_MULTISAMPLEANTIALIAS:
		{
			*pValue = value;
//bool value that determines how individual samples are computed when using a multisample render-target buffer. When set to TRUE, the multiple samples are computed so that full-scene antialiasing is performed by sampling at different sample positions for each multiple sample. When set to FALSE, the multiple samples are all written with the same sample value, sampled at the pixel center, which allows non-antialiased rendering to a multisample buffer. This render state has no effect when rendering to a single sample buffer. The default value is TRUE.
		}
		break;
	case D3DRS_MULTISAMPLEMASK:
		{
			*pValue = value;
//Each bit in this mask, starting at the least significant bit (LSB), controls modification of one of the samples in a multisample render target. Thus, for an 8-sample render target, the low byte contains the eight write enables for each of the eight samples. This render state has no effect when rendering to a single sample buffer. The default value is 0xFFFFFFFF.
//This render state enables use of a multisample buffer as an accumulation buffer, doing multipass rendering of geometry where each pass updates a subset of samples.
//If there are n multisamples and k enabled samples, the resulting intensity of the rendered image should be k/n. Each component RGB of every pixel is factored by k/n.
		}
		break;
	case D3DRS_PATCHEDGESTYLE:
		{
			*pValue = to_DIS.PatchEdgeStyle( D3DPATCHEDGESTYLE( value ));
//Sets whether patch edges will use float style tessellation. Possible values are defined by the D3DPATCHEDGESTYLE enumerated type. The default value is D3DPATCHEDGE_DISCRETE.
		}
		break;
	case D3DRS_DEBUGMONITORTOKEN:
		{
			*pValue = to_DIS.DebugMonitorToken( D3DDEBUGMONITORTOKENS(value) );
//Set only for debugging the monitor. Possible values are defined by the D3DDEBUGMONITORTOKENS enumerated type. Note that if D3DRS_DEBUGMONITORTOKEN is set, the call is treated as passing a token to the debug monitor. For example, if - after passing D3DDMT_ENABLE or D3DDMT_DISABLE to D3DRS_DEBUGMONITORTOKEN - other token values are passed in, the state (enabled or disabled) of the debug monitor will still persist.
//This state is only useful for debug builds. The debug monitor defaults to D3DDMT_ENABLE.
		}
		break;
	case D3DRS_POINTSIZE_MAX:
		{
			*pValue = value;
//A float value that specifies the maximum size to which point sprites will be clamped. The value must be less than or equal to the MaxPointSize member of D3DCAPS9 and greater than or equal to D3DRS_POINTSIZE_MIN. The default value is 64.0. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
//m_pDevice9->SetRenderState(D3DRS_PONTSIZE_MAX, *((DWORD*)&pointSizeMax));
		}
		break;
	case D3DRS_INDEXEDVERTEXBLENDENABLE:
		{
			*pValue = value;
//bool value that enables or disables indexed vertex blending. The default value is FALSE. When set to TRUE, indexed vertex blending is enabled. When set to FALSE, indexed vertex blending is disabled. If this render state is enabled, the user must pass matrix indices as a packed DWORDwith every vertex. When the render state is disabled and vertex blending is enabled through the D3DRS_VERTEXBLEND state, it is equivalent to having matrix indices 0, 1, 2, 3 in every vertex.
		}
		break;
	case D3DRS_COLORWRITEENABLE:
		{
			*pValue = value;
//UINT value that enables a per-channel write for the render-target color buffer. A set bit results in the color channel being updated during 3D rendering. A clear bit results in the color channel being unaffected. This functionality is available if the D3DPMISCCAPS_COLORWRITEENABLE capabilities bit is set in the PrimitiveMiscCaps member of the D3DCAPS9 structure for the device. This render state does not affect the clear operation. The default value is 0x0000000F.
//Valid values for this render state can be any combination of the D3DCOLORWRITEENABLE_ALPHA, D3DCOLORWRITEENABLE_BLUE, D3DCOLORWRITEENABLE_GREEN, or D3DCOLORWRITEENABLE_RED flags.
		}
		break;
	//case D3DRS_TWEENF2ACTOR:
	//	{
	//		*pValue = value;
//A float value that controls the tween factor. The default value is 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD values, your application must cast a variable that contains the value, as shown in the following code example.
	//	}
	//	break;
	case D3DRS_BLENDOP:
		{
			*pValue = to_DIS.BlendOp(D3DBLENDOP(value));
//Value used to select the arithmetic operation applied when the alpha blending render state, D3DRS_ALPHABLENDENABLE, is set to TRUE. Valid values are defined by the D3DBLENDOP enumerated type. The default value is D3DBLENDOP_ADD.
//If the D3DPMISCCAPS_BLENDOP device capability is not supported, then D3DBLENDOP_ADD is performed.
		}
		break;
	case D3DRS_POSITIONDEGREE:
		{
			*pValue = to_DIS.DegreeType(D3DDEGREETYPE(value));
//N-patch position interpolation degree. The values can be D3DDEGREE_CUBIC (default) or D3DDEGREE_LINEAR. For more information, see D3DDEGREETYPE.
		}
		break;
	case D3DRS_NORMALDEGREE:
		{
			*pValue = to_DIS.DegreeType(D3DDEGREETYPE(value));
//N-patch normal interpolation degree. The values can be D3DDEGREE_LINEAR (default) or D3DDEGREE_QUADRATIC. For more information, see D3DDEGREETYPE.
		}
		break;
	case D3DRS_SCISSORTESTENABLE:
		{
			*pValue = value;
//TRUE to enable scissor testing and FALSE to disable it. The default value is FALSE.
		}
		break;
	case D3DRS_SLOPESCALEDEPTHBIAS:
		{
			*pValue = value;
//Used to determine how much bias can be applied to co-planar primitives to reduce z-fighting. The default value is 0.
//bias = (max * D3DRS_SLOPESCALEDEPTHBIAS) + D3DRS_DEPTHBIAS.
//where max is the maximum depth slope of the triangle being rendered.
		}
		break;
	case D3DRS_ANTIALIASEDLINEENABLE:
		{
			*pValue = value;
//TRUE to enable line antialiasing, FALSE to disable line antialiasing. The default value is FALSE.
//When rendering to a multisample render target, D3DRS_ANTIALIASEDLINEENABLE is ignored and all lines are rendered aliased. Use ID3DXLine for antialiased line rendering in a multisample render target.
		}
		break;
	case D3DRS_MINTESSELLATIONLEVEL:
		{
			*pValue = value;
//Minimum tessellation level. The default value is 1.0f. See Tessellation (Direct3D 9).
		}
		break;
	case D3DRS_MAXTESSELLATIONLEVEL:
		{
			*pValue = value;
//Maximum tessellation level. The default value is 1.0f. See Tessellation (Direct3D 9).
		}
		break;
	case D3DRS_ADAPTIVETESS_X:
		{
			*pValue = value;
//Amount to adaptively tessellate, in the x direction. Default value is 0.0f. See Adaptive Tessellation.
		}
		break;

	case D3DRS_ADAPTIVETESS_Y:
		{
			*pValue = value;
//Amount to adaptively tessellate, in the y direction. Default value is 0.0f. See Adaptive_Tessellation.
		}
		break;
	case D3DRS_ADAPTIVETESS_Z:
		{
			*pValue = value;
//Amount to adaptively tessellate, in the z direction. Default value is 1.0f. See Adaptive_Tessellation.
		}
		break;
	case D3DRS_ADAPTIVETESS_W:
		{
			*pValue = value;
//Amount to adaptively tessellate, in the w direction. Default value is 0.0f. See Adaptive_Tessellation.
		}
		break;
	case D3DRS_ENABLEADAPTIVETESSELLATION:
		{
			*pValue = value;
//TRUE to enable adaptive tessellation, FALSE to disable it. The default value is FALSE. See Adaptive_Tessellation.
		}
	case D3DRS_TWOSIDEDSTENCILMODE:
		{
			*pValue = value;
//TRUE enables two-sided stenciling, FALSE disables it. The default value is FALSE. The application should set D3DRS_CULLMODE to D3DCULL_NONE to enable two-sided stencil mode. If the triangle winding order is clockwise, the D3DRS_STENCIL* operations will be used. If the winding order is counterclockwise, the D3DRS_CCW_STENCIL* operations will be used.
//To see if two-sided stencil is supported, check the StencilCaps member of D3DCAPS9 for D3DSTENCILCAPS_TWOSIDED. See also D3DSTENCILCAPS.
		}
		break;
	case D3DRS_CCW_STENCILFAIL:
		{
			*pValue = to_DIS.dStencilOp( D3DSTENCILOP(value));
//Stencil operation to perform if CCW stencil test fails. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP.
		}
		break;
	case D3DRS_CCW_STENCILZFAIL:
		{
			*pValue = to_DIS.dStencilOp( D3DSTENCILOP(value));
//Stencil operation to perform if CCW stencil test passes and z-test fails. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP.
		}
		break;
	case D3DRS_CCW_STENCILPASS:
		{
			*pValue = to_DIS.dStencilOp( D3DSTENCILOP(value));
//Stencil operation to perform if both CCW stencil and z-tests pass. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP.
		}
		break;
	case D3DRS_CCW_STENCILFUNC:
		{
			*pValue = to_DIS.dStencilOp( D3DSTENCILOP(value));
//The comparison function. CCW stencil test passes if ((ref & mask) stencil function (stencil & mask)) is TRUE. Values are from the D3DCMPFUNC enumerated type. The default value is D3DCMP_ALWAYS.
		}
		break;
	case D3DRS_COLORWRITEENABLE1:
		{
			*pValue = value;
//Additional ColorWriteEnable values for the devices. See D3DRS_COLORWRITEENABLE. This functionality is available if the D3DPMISCCAPS_INDEPENDENTWRITEMASKS capabilities bit is set in the PrimitiveMiscCaps member of the D3DCAPS9 structure for the device. The default value is 0x0000000f.
		}
		break;
	case D3DRS_COLORWRITEENABLE2:
		{
			*pValue = value;
//Additional ColorWriteEnable values for the devices. See D3DRS_COLORWRITEENABLE. This functionality is available if the D3DPMISCCAPS_INDEPENDENTWRITEMASKS capabilities bit is set in the PrimitiveMiscCaps member of the D3DCAPS9 structure for the device. The default value is 0x0000000f.
		}
		break;
	case D3DRS_COLORWRITEENABLE3:
		{
			*pValue = value;
//Additional ColorWriteEnable values for the devices. See D3DRS_COLORWRITEENABLE. This functionality is available if the D3DPMISCCAPS_INDEPENDENTWRITEMASKS capabilities bit is set in the PrimitiveMiscCaps member of the D3DCAPS9 structure for the device. The default value is 0x0000000f.
		}
		break;
	case D3DRS_BLENDFACTOR:
		{
			*pValue = value;
//D3DCOLOR used for a constant blend-factor during alpha blending. This functionality is available if the D3DPBLENDCAPS_BLENDFACTOR capabilities bit is set in the SrcBlendCaps member of D3DCAPS9 or the DestBlendCaps member of D3DCAPS9. See D3DRENDERSTATETYPE. The default value is 0xffffffff.
		}
		break;
	case D3DRS_SRGBWRITEENABLE:
		{
			*pValue = value;
//Enable render-target writes to be gamma corrected to sRGB. The format must expose D3DUSAGE_SRGBWRITE. The default value is 0.
		}
		break;
	case D3DRS_DEPTHBIAS:
		{
			*pValue = value;
//A floating-point value that is used for comparison of depth values. See Depth Bias (Direct3D 9). The default value is 0.
		}
		break;
	case D3DRS_WRAP8:
		{
			*pValue = value;
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP9:
		{
			*pValue = value;
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP10:
		{
			*pValue = value;
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP11:
		{
			*pValue = value;
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP12:
		{
			*pValue = value;
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP13:
		{
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_WRAP14:
		{
			*pValue = value;
//See D3DRS_WRAP0.
		}
		break;

	case D3DRS_WRAP15:
		{
			*pValue = value;
//See D3DRS_WRAP0.
		}
		break;
	case D3DRS_SEPARATEALPHABLENDENABLE:
		{
			*pValue = value;
//TRUE enables the separate blend mode for the alpha channel. The default value is FALSE.
//When set to FALSE, the render-target blending factors and operations applied to alpha are forced to be the same as those defined for color. This mode is effectively hardwired to FALSE on implementations that don't set the cap D3DPMISCCAPS_SEPARATEALPHABLEND. See D3DPMISCCAPS.
//The type of separate alpha blending is determined by the D3DRS_SRCBLENDALPHA and D3DRS_DESTBLENDALPHA render states.
		}
		break;
	case D3DRS_SRCBLENDALPHA:
		{
			*pValue = to_DIS.BlendType( D3DBLEND(value));
//One member of the D3DBLEND enumerated type. This value is ignored unless D3DRS_SEPARATEALPHABLENDENABLE is TRUE. The default value is D3DBLEND_ONE.
		}
		break;
	case D3DRS_DESTBLENDALPHA:
		{
			*pValue = to_DIS.BlendType( D3DBLEND(value));
//One member of the D3DBLEND enumerated type. This value is ignored unless D3DRS_SEPARATEALPHABLENDENABLE is TRUE. The default value is D3DBLEND_ZERO.
		}
		break;
	case D3DRS_BLENDOPALPHA:
		{
			*pValue = to_DIS.BlendType( D3DBLEND(value));
//Value used to select the arithmetic operation applied to separate alpha blending when the render state, D3DRS_SEPARATEALPHABLENDENABLE, is set to TRUE.
//Valid values are defined by the D3DBLENDOP enumerated type. The default value is D3DBLENDOP_ADD.
//If the D3DPMISCCAPS_BLENDOP device capability is not supported, then D3DBLENDOP_ADD is performed. See D3DPMISCCAPS.
		}
		break;
	
	default: *pValue = value;
	};
#endif
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetRenderTarget( //Retrieves a render-target surface.
	UInt32 RenderTargetIndex,//[in]Index of the render target. See Remarks.
	LPSURFACE2D *ppRenderTarget//[out]Address of a pointer to an IDirect3DSurface9 interface, representing the returned render-target surface for this device.
	)
{
	LPDIRECT3DSURFACE9 pSurf;
	HRESULT hr = pD3DDevice->GetRenderTarget(
								RenderTargetIndex, 
								&pSurf);

	Surface2DRenderTargetForGetFunc.SetGetter(pSurf);
	*ppRenderTarget = Surface2DRenderTargetForGetFunc.GetGetter();
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetRenderTargetData( //Copies the render-target data from device memory to system memory.
	LPSURFACE2D pRenderTarget,//[in] 
	LPSURFACE2D pDestSurface//[in]
	)
{

	if( pRenderTarget == NULL )
	{
		return DIS_FAIL;
	}
	if( pDestSurface == NULL )
	{
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->GetRenderTargetData(
								LPSURFACE2D_D3D9(pRenderTarget)->pd3dSurface, 
								LPSURFACE2D_D3D9(pDestSurface)->pd3dSurface);
	
	return HR_to_DR( hr );
}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetSamplerState( //Gets the sampler state value.
	UInt32 Sampler,// [in] The sampler stage index.
	DIS_SAMPLERSTATETYPE Type,// [in]This parameter can be any member of the D3DSAMPLERSTATETYPE enumerated type.
	UInt32 *pValue//[out]State value to get. The meaning of this value is determined by the Type parameter.
	)	
{
	D3DSAMPLERSTATETYPE d3dType = D3DSAMPLERSTATETYPE(DIS_SampleStateType[ Type ]);
	DWORD value;

	HRESULT hr = pD3DDevice->GetSamplerState(Sampler, d3dType, &value);
	
	switch(d3dType)
	{
	case D3DSAMP_ADDRESSU:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS( value ));
//Texture-address mode for the u coordinate. The default is D3DTADDRESS_WRAP. For more information, see D3DTEXTUREADDRESS.
		}
		break;
	case D3DSAMP_ADDRESSV:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS( value ));
//Texture-address mode for the v coordinate. The default is D3DTADDRESS_WRAP. For more information, see D3DTEXTUREADDRESS.
		}
		break;
	case D3DSAMP_ADDRESSW:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS( value ));
//Texture-address mode for the w coordinate. The default is D3DTADDRESS_WRAP. For more information, see D3DTEXTUREADDRESS.
		}
		break;
	case D3DSAMP_BORDERCOLOR:
		{
			*pValue = value;
//Border color or type D3DCOLOR. The default color is 0x00000000.
		}
		break;
	case D3DSAMP_MAGFILTER:
		{
			*pValue = to_DIS.dTextureFilter( D3DTEXTUREFILTERTYPE( value ));
//Magnification filter of type D3DTEXTUREFILTERTYPE. The default value is D3DTEXF_POINT.
		}
		break;
	case D3DSAMP_MINFILTER:
		{
			*pValue = to_DIS.dTextureFilter( D3DTEXTUREFILTERTYPE( value ));
//Minification filter of type D3DTEXTUREFILTERTYPE. The default value is D3DTEXF_POINT.
		}
		break;
	case D3DSAMP_MIPFILTER:
		{
			*pValue = to_DIS.dTextureFilter( D3DTEXTUREFILTERTYPE( value ));
//Mipmap filter to use during minification. See D3DTEXTUREFILTERTYPE. The default value is D3DTEXF_NONE.
		}
		break;
	case D3DSAMP_MIPMAPLODBIAS:
		{
			*pValue = value;
//Mipmap level-of-detail bias. The default value is zero.
		}
		break;
	case D3DSAMP_MAXMIPLEVEL:
		{
		*pValue = value;
//level-of-detail index of largest map to use. Values range from 0 to (n - 1) where 0 is the largest. The default value is zero.
		}
		break;
	case D3DSAMP_MAXANISOTROPY:
		{
			*pValue = value;
//DWORD maximum anisotropy. Values range from 1 to the value that is specified in the MaxAnisotropy member of the D3DCAPS9 structure. The default value is 1.
		}
		break;	
	case D3DSAMP_SRGBTEXTURE:
		{
			*pValue = value;
//Gamma correction value. The default value is 0, which means gamma is 1.0 and no correction is required. Otherwise, this value means that the sampler should assume gamma of 2.2 on the content and convert it to linear (gamma 1.0) before presenting it to the pixel shader.
		}
		break;	
	case D3DSAMP_ELEMENTINDEX:
		{
			*pValue = value;
//When a multielement texture is assigned to the sampler, this indicates which element index to use. The default value is 0.
		}
		break;
	case D3DSAMP_DMAPOFFSET:
		{
			*pValue = value;
//Vertex offset in the presampled displacement map. This is a constant used by the tessellator, its default value is 0.
		}
		break;

	default: *pValue = value; break;

	};
	return HR_to_DR(hr);
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetScissorRect( //Gets the scissor rectangle.
	DIS_Rect *pRect//[out] Returns a pointer to a RECT structure that defines the rendering area within the render target if scissor test is enabled.
	)
{
	RECT rect;
	HRESULT hr = pD3DDevice->GetScissorRect(&rect);
	
	pRect->x1 = rect.left;
	pRect->y1 = rect.top;
	pRect->x2 = rect.right;
	pRect->y2 = rect.bottom;

	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE bool D3D_DeviceInterface::GetSoftwareVertexProcessing() //Gets the vertex processing (hardware or software) mode.
{
	return pD3DDevice->GetSoftwareVertexProcessing();
}

DIS_RESULT D3D_DeviceInterface::GetStreamSource(//Retrieves a vertex buffer bound to the specified data stream.
    UInt32 StreamNumber,//[in]Specifies the data stream, in the range from 0 to the maximum number of streams minus one.
	LPVERTEXBUFFER *ppStreamData,//[in, out]Address of a pointer to an IDirect3DVertexBuffer9 interface, representing the returned vertex buffer bound to the specified data stream.
    UInt32 *pOffsetInBytes,//[out]Pointer containing the offset from the beginning of the stream to the beginning of the vertex data. The offset is measured in bytes. See Remarks.
    UInt32 *pStride//[out]Pointer to a returned stride of the component, in bytes. See Remarks.
	)
{
	HRESULT hr = pD3DDevice->GetStreamSource(
								StreamNumber, 
								&VertexBufferForGetFunc.pd3dVertexBuffer, 
								pOffsetInBytes, 
								pStride);

	*ppStreamData = &VertexBufferForGetFunc;

	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetStreamSourceFreq( //Gets the stream source frequency divider value.
	UInt32 StreamNumber,//[in] Stream source number.
	UInt32 *pDivider//[out]Returns the frequency divider value.
	)
{

	HRESULT hr = pD3DDevice->GetStreamSourceFreq(StreamNumber, pDivider);
	
	return HR_to_DR( hr );

//	return DIS_OK;
}



//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetSwapChain( //Gets a pointer to a swap chain.
	UInt32  iSwapChain,//[in] The swap chain ordinal value. For more information, see NumberOfAdaptersInGroup in D3DCAPS9.
	LPSWAPCHAIN *ppSwapChain//[in]Pointer to an IDirect3DSwapChain9 interface that will receive a copy of swap chain.
	)
{
	HRESULT hr = pD3DDevice->GetSwapChain(
								iSwapChain, 
								&SwapChainWrapperForGetFunc.pd3dSwapChain);
	
	*ppSwapChain = &SwapChainWrapperForGetFunc;

	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetTexture( //Retrieves a texture assigned to a stage for a device.
        UInt32 Stage,//[in]Stage identifier of the texture to retrieve. Stage identifiers are zero-based.
		LPBASETEXTURE *ppTexture//[out, retval]Address of a pointer to an IDirect3DBaseTexture9 interface, representing the returned texture.
	)
{

	if( Stage >= 8 ) 
	{
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->GetTexture(
								Stage, 
								&BaseTextureForGetFunc[Stage].pBaseTexture);
	
	*ppTexture = &BaseTextureForGetFunc[Stage];
	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetTextureStageState(//Retrieves a state value for an assigned texture.
	UInt32 Stage,//[in] Stage identifier of the texture for which the state is retrieved. Stage identifiers are zero-based. Devices can have up to eight set textures, so the maximum value allowed for Stage is 7.
    DIS_TEXTURESTAGESTATETYPE Type,//[in] Texture state to retrieve. This parameter can be any member of the D3DTEXTURESTAGESTATETYPE enumerated type.
	UInt32 *pValue // [out, retval]Pointer a variable to fill with the retrieved state value. The meaning of the retrieved value is determined by the Type parameter.
	)
{
	D3DTEXTURESTAGESTATETYPE d3dType = D3DTEXTURESTAGESTATETYPE( DIS_TextureStageStateType[ Type ]);
	DWORD value;

	HRESULT hr = pD3DDevice->GetTextureStageState(Stage, d3dType, &value);
	


	switch( d3dType )
	{
	case D3DTSS_COLOROP:
		{
			*pValue = to_DIS.dTextureOp( D3DTEXTUREOP(value) );
//Texture-stage state is a texture color blending operation identified by one member of the D3DTEXTUREOP enumerated type. The default value for the first texture stage (stage 0) is D3DTOP_MODULATE; for all other stages the default is D3DTOP_DISABLE.
		}
		break;
	case D3DTSS_COLORARG1:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS(value) );
//Texture-stage state is the first color argument for the stage, identified by one of the D3DTA. The default argument is D3DTA_TEXTURE.
//Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default value for the register is (0.0, 0.0, 0.0, 0.0).
		}
		break;
	case D3DTSS_COLORARG2:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS(value) );
//Texture-stage state is the second color argument for the stage, identified by D3DTA. The default argument is D3DTA_CURRENT. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default value for the register is (0.0, 0.0, 0.0, 0.0)
		}
		break;
	
	case D3DTSS_ALPHAOP:
		{
			*pValue = to_DIS.dTextureOp( D3DTEXTUREOP(value) );
//Texture-stage state is a texture alpha blending operation identified by one member of the D3DTEXTUREOP enumerated type. The default value for the first texture stage (stage 0) is D3DTOP_SELECTARG1, and for all other stages the default is D3DTOP_DISABLE.
		}
		break;

	case D3DTSS_ALPHAARG1:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS(value) );
//Texture-stage state is the first alpha argument for the stage, identified by by D3DTA. The default argument is D3DTA_TEXTURE. If no texture is set for this stage, the default argument is D3DTA_DIFFUSE. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default value for the register is (0.0, 0.0, 0.0, 0.0).
		}
		break;

	case D3DTSS_ALPHAARG2:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS(value) );
//Texture-stage state is the second alpha argument for the stage, identified by by D3DTA. The default argument is D3DTA_CURRENT. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default value for the register is (0.0, 0.0, 0.0, 0.0).
		}
		break;
	case D3DTSS_BUMPENVMAT00:
		{
			*pValue = value;
//Texture-stage state is a floating-point value for the [0][0] coefficient in a bump-mapping matrix. The default value is 0.0.
		}
		break;

	case D3DTSS_BUMPENVMAT01:
		{
			*pValue = value;
//Texture-stage state is a floating-point value for the [0][1] coefficient in a bump-mapping matrix. The default value is 0.0.
		}
		break;

	case D3DTSS_BUMPENVMAT10:
		{
			*pValue = value;
//Texture-stage state is a floating-point value for the [1][0] coefficient in a bump-mapping matrix. The default value is 0.0.
		}
		break;

	case D3DTSS_BUMPENVMAT11:
		{
			*pValue = value;
//Texture-stage state is a floating-point value for the [1][1] coefficient in a bump-mapping matrix. The default value is 0.0.
		}
		break;
	case D3DTSS_TEXCOORDINDEX:
		{
			*pValue = value;
//Index of the texture coordinate set to use with this texture stage. You can specify up to eight sets of texture coordinates per vertex. If a vertex does not include a set of texture coordinates at the specified index, the system defaults to the u and v coordinates (0,0).
//When rendering using vertex shaders, each stage's texture coordinate index must be set to its default value. The default index for each stage is equal to the stage index. Set this state to the zero-based index of the coordinate set for each vertex that this texture stage uses.
//Additionally, applications can include, as logical OR with the index being set, one of the constants to request that Direct3D automatically generate the input texture coordinates for a texture transformation. For a list of all the constants, see D3DTSS_TCI.
//With the exception of D3DTSS_TCI_PASSTHRU, which resolves to zero, if any of the following values is included with the index being set, the system uses the index strictly to determine texture wrapping mode. These flags are most useful when performing environment mapping.
		}
		break;

	case D3DTSS_BUMPENVLSCALE:
		{
			*pValue = value;
//Floating-point scale value for bump-map luminance. The default value is 0.0.
		}
		break;

	case D3DTSS_BUMPENVLOFFSET:
		{
			*pValue = value;
//Floating-point offset value for bump-map luminance. The default value is 0.0.
		}
		break;

	case D3DTSS_TEXTURETRANSFORMFLAGS:
		{
			*pValue = value;
//Member of the D3DTEXTURETRANSFORMFLAGS enumerated type that controls the transformation of texture coordinates for this texture stage. The default value is D3DTTFF_DISABLE.
		}
		break;

	case D3DTSS_COLORARG0:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS(value) );
//Settings for the third color operand for triadic operations (multiply, add, and linearly interpolate), identified by D3DTA. This setting is supported if the D3DTEXOPCAPS_MULTIPLYADD or D3DTEXOPCAPS_LERP device capabilities are present. The default argument is D3DTA_CURRENT. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default value for the register is (0.0, 0.0, 0.0, 0.0).
		}
		break;

	case D3DTSS_ALPHAARG0:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS(value) );
//Settings for the alpha channel selector operand for triadic operations (multiply, add, and linearly interpolate), identified by D3DTA. This setting is supported if the D3DTEXOPCAPS_MULTIPLYADD or D3DTEXOPCAPS_LERP device capabilities are present. The default argument is D3DTA_CURRENT. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default argument is (0.0, 0.0, 0.0, 0.0).
		}
		break;
	case D3DTSS_RESULTARG:
		{
			*pValue = to_DIS.dTextureAddress( D3DTEXTUREADDRESS(value) );
//Setting to select destination register for the result of this stage, identified by D3DTA. This value can be set to D3DTA_CURRENT (the default value) or to D3DTA_TEMP, which is a single temporary register that can be read into subsequent stages as an input argument. The final color passed to the fog blender and frame buffer is taken from D3DTA_CURRENT, so the last active texture stage state must be set to write to current. This setting is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present.
		}
		break;
	case D3DTSS_CONSTANT:
		{
			*pValue = (value) ;
//Per-stage constant color. To see if a device supports a per-stage constant color, see the D3DPMISCCAPS_PERSTAGECONSTANT constant in D3DPMISCCAPS. D3DTSS_CONSTANT is used by D3DTA_CONSTANT. See D3DTA.
		}
		break;
	
	default: *pValue=value;break;
	}
	
	return HR_to_DR(hr);
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetTransform( //Retrieves a matrix describing a transformation state.
	DIS_TRANSFORMSTATETYPE State,//[in]Device state variable that is being modified. This parameter can be any member of the D3DTRANSFORMSTATETYPE enumerated type, or the D3DTS_WORLDMATRIX macro.
	DIS_MATRIX *pMatrix//[out] Pointer to a D3DMATRIX structure, describing the returned transformation state.
	)
{
	
	D3DMATRIX mat;

	HRESULT hr = pD3DDevice->GetTransform(
								D3DTRANSFORMSTATETYPE( this->DIS_TransformStateType[ State ] ),
								&mat);
	
	Copy_D3DMATRIX_To_DIS_MATRIX( mat, *pMatrix );

	return HR_to_DR( hr );
		
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetVertexDeclaration( //Gets a vertex shader declaration.
	LPVERTEXDECLERATION *ppDecl//[out]
	)
{
	HRESULT hr = pD3DDevice->GetVertexDeclaration(
								&VertexDeclerationWrapperForGetFunc.pd3dVertexDecl);
	
	*ppDecl = &VertexDeclerationWrapperForGetFunc;
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetVertexShader( //Retrieves the currently set vertex shader.
	LPVERTEXSHADER *ppShader //[out, retval]
	)
{
	HRESULT hr = pD3DDevice->GetVertexShader(
			&VertexShaderForGetFunc.pd3dVertexShader);
	
	*ppShader = &VertexShaderForGetFunc;
	return HR_to_DR( hr );


}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetVertexShaderConstantB( //Gets a Boolean vertex shader constant.
    UInt32 StartRegister,//[in]Register number that will contain the first constant value.
	bool *pConstantData,//[in, out]Pointer to an array of constants.
    UInt32 BoolCount//[in]Number of Boolean values in the array of constants.
	)
{

	HRESULT hr = pD3DDevice->GetVertexShaderConstantB(StartRegister, 
												(BOOL*)pConstantData, BoolCount);
	
	return HR_to_DR( hr );

//	return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetVertexShaderConstantF( //Gets a floating-point vertex shader constant.
    UInt32 StartRegister,//[in] Register number that will contain the first constant value.
	float *pConstantData,//[in, out] Pointer to an array of constants.
    UInt32 Vector4fCount//[in] Number of four float vectors in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->GetVertexShaderConstantF(StartRegister, 
												pConstantData, Vector4fCount);
	
	return HR_to_DR( hr );
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetVertexShaderConstantI(//Gets an integer vertex shader constant.
	UInt32 StartRegister,//  [in]Register number that will contain the first constant value.
	int *pConstantData,//[in, out]Pointer to an array of constants.
	UInt32 Vector4iCount//  [in]Number of four integer vectors in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->GetVertexShaderConstantI(StartRegister, 
												pConstantData, Vector4iCount);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::GetViewport(//Retrieves the viewport parameters currently set for the device.
	DIS_VIEWPORT *pViewport //[out] Pointer to a D3DVIEWPORT9 structure, representing the returned viewport parameters.
	)
{

	D3DVIEWPORT9 vp;
	HRESULT hr = pD3DDevice->GetViewport(&vp);
	

	pViewport->Height = vp.Height;
	pViewport->MaxZ = vp.MaxZ;
	pViewport->MinZ = vp.MinZ;
	pViewport->Width = vp.Width;
	pViewport->X = vp.X;
	pViewport->Y = vp.Y;


	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::LightEnable( //Enables or disables a set of lighting parameters within a device.
	UInt32 LightIndex,//[in]Zero-based index of the set of lighting parameters that are the target of this method.
	bool bEnable	//[in]Value that indicates if the set of lighting parameters are being enabled or disabled. Set this parameter to TRUE to enable lighting with the parameters at the specified index, or FALSE to disable it.
	)
{

	HRESULT hr = pD3DDevice->LightEnable(LightIndex, bEnable);
	
	return HR_to_DR( hr );

//	return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::MultiplyTransform( //Multiplies a device's world, view, or projection matrices by a specified matrix.
	DIS_TRANSFORMSTATETYPE State, // [in]Member of the D3DTRANSFORMSTATETYPE enumerated type, or the D3DTS_WORLDMATRIX macro that identifies which device matrix is to be modified. The most common setting, D3DTS_WORLDMATRIX(0), modifies the world matrix, but you can specify that the method modify the view or projection matrices, if needed.
	const DIS_MATRIX *pMatrix // [in]Pointer to a D3DMATRIX structure that modifies the current transformation.
	)
{
	D3DMATRIX mat;

	Copy_DIS_MATRIX_To_D3DMATRIX( *pMatrix, mat );

	HRESULT hr = pD3DDevice->MultiplyTransform(
								D3DTRANSFORMSTATETYPE(DIS_TransformStateType[ State ]), 
								&mat);
	
	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::Present( //Presents the contents of the next buffer in the sequence of back buffers owned by the device.
	const DIS_Rect *pSourceRect,//[in]Pointer to a value that must be NULL unless the swap chain was created with D3DSWAPEFFECT_COPY. pSourceRect is a pointer to a RECT structure containing the source rectangle. If NULL, the entire source surface is presented. If the rectangle exceeds the source surface, the rectangle is clipped to the source surface.
	const DIS_Rect *pDestRect,//[in]Pointer to a value that must be NULL unless the swap chain was created with D3DSWAPEFFECT_COPY. pDestRect is a pointer to a RECT structure containing the destination rectangle, in window client coordinates. If NULL, the entire client area is filled. If the rectangle exceeds the destination client area, the rectangle is clipped to the destination client area.
	DIS_HWND hDestWindowOverride,//[in]Pointer to a destination window whose client area is taken as the target for this presentation. If this value is NULL, the runtime uses the hDeviceWindow member of D3DPRESENT_PARAMETERS for the presentation.
	const DIS_RGNDATA *pDirtyRegion//[in]Value must be NULL unless the swap chain was created with D3DSWAPEFFECT_COPY. For more information about swap chains, see Flipping Surfaces (Direct3D 9) and D3DSWAPEFFECT. If this value is non-NULL, the contained region is expressed in back buffer coordinates. The rectangles within the region are the minimal set of pixels that need to be updated. This method takes these rectangles into account when optimizing the presentation by copying only the pixels within the region, or some suitably expanded set of rectangles. This is an aid to optimization only, and the application should not rely on the region being copied exactly. The implementation can choose to copy the whole source rectangle.
	)
{

	HRESULT hr = pD3DDevice->Present((RECT*) pSourceRect, 
									 (RECT*) pDestRect, 
									 (HWND)  hDestWindowOverride,
									 (RGNDATA*) pDirtyRegion);
	
	return HR_to_DR( hr );

	//return DIS_OK;
}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::ProcessVertices( //Applies the vertex processing defined by the vertex shader to the set of input data streams, generating a single stream of interleaved vertex data to the destination vertex buffer.
	UInt32 SrcStartIndex, //[in] Index of first vertex to load.
	UInt32 DestIndex, // [in] Index of first vertex in the destination vertex buffer into which the results are placed.
	UInt32 VertexCount,//[in] Number of vertices to process.
	LPVERTEXBUFFER *pDestBuffer,//[in] Pointer to an IDirect3DVertexBuffer9 interface, the destination vertex buffer representing the stream of interleaved vertex data.
	LPVERTEXDECLERATION pVertexDecl,//[in] Pointer to an IDirect3DVertexDeclaration9 interface that represents the output vertex data declaration. When vertex shader 3.0 or above is set as the current vertex shader, the output vertex declaration must be present.
	UInt32 Flags//[in] Processing options. Set this parameter to 0 for default processing. Set to D3DPV_DONOTCOPYDATA to prevent the system from copying vertex data not affected by the vertex operation into the destination buffer. The D3DPV_DONOTCOPYDATA value may be combined with one or more D3DLOCK values appropriate for the destination buffer.
	)
{

	if( *pDestBuffer == NULL )
	{
		return DIS_FAIL;
	}

	if( pVertexDecl == NULL )
	{
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->ProcessVertices(
								SrcStartIndex, 
								DestIndex, 
								VertexCount,
								(LPVERTEXBUFFER_D3D9(pDestBuffer)->pd3dVertexBuffer), 
								(LPVERTEXDECLERATION_D3D9(pDestBuffer)->pd3dVertexDecl), 
								Flags);
	
	return HR_to_DR( hr );

}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::Reset( //Resets the type, size, and format of the swap chain.
	DIS_PRESENT_PARAMETERS *pPresentationParameters // [in, out]Pointer to a D3DPRESENT_PARAMETERS structure, describing the new presentation parameters. This value cannot be NULL.
	//	When switching to full-screen mode, Direct3D will try to find a desktop format that matches the back buffer format, so that back buffer and front buffer formats will be identical (to eliminate the need for color conversion).
	//	When this method returns:
	//	BackBufferCount, BackBufferWidth, and BackBufferHeight are set to zero.
	//	BackBufferFormat is set to D3DFMT_UNKNOWN for windowed mode only; a full-screen mode must specify a format.
	)
{
	D3DPRESENT_PARAMETERS d3dpp;

	d3dpp.AutoDepthStencilFormat = D3DFORMAT( DIS_Format[ pPresentationParameters->AutoDepthStencilFormat ]);
	d3dpp.BackBufferCount =			pPresentationParameters->BackBufferCount;
	d3dpp.BackBufferFormat =		D3DFORMAT( DIS_Format[ pPresentationParameters->BackBufferFormat]);
	d3dpp.BackBufferHeight =		pPresentationParameters->BackBufferHeight;
	d3dpp.BackBufferWidth =			pPresentationParameters->BackBufferWidth;
	d3dpp.EnableAutoDepthStencil = pPresentationParameters->EnableAutoDepthStencil;
	d3dpp.Flags =					pPresentationParameters->Flags;
	d3dpp.FullScreen_RefreshRateInHz = pPresentationParameters->FullScreen_RefreshRateInHz;
	d3dpp.hDeviceWindow =			(HWND)pPresentationParameters->hDeviceWindow;
	d3dpp.MultiSampleQuality =		pPresentationParameters->MultiSampleQuality;
	d3dpp.MultiSampleType =			(D3DMULTISAMPLE_TYPE) DIS_MultiSampleType[ pPresentationParameters->MultiSampleType];
	d3dpp.PresentationInterval =	pPresentationParameters->PresentationInterval;
	d3dpp.SwapEffect =				(D3DSWAPEFFECT)DIS_SwapEffect[ pPresentationParameters->SwapEffect ];
	d3dpp.Windowed =				pPresentationParameters->Windowed;


	HRESULT hr = pD3DDevice->Reset( &d3dpp);

	pPresentationParameters->AutoDepthStencilFormat  = to_DIS.dFormat( d3dpp.AutoDepthStencilFormat ); 
	pPresentationParameters->BackBufferCount =			d3dpp.BackBufferCount;
	pPresentationParameters->BackBufferFormat =			to_DIS.dFormat( d3dpp.BackBufferFormat );
	pPresentationParameters->BackBufferHeight =			d3dpp.BackBufferHeight;
	pPresentationParameters->BackBufferWidth =			d3dpp.BackBufferWidth;
	pPresentationParameters->EnableAutoDepthStencil =	d3dpp.EnableAutoDepthStencil;
	pPresentationParameters->Flags =					d3dpp.Flags;
	pPresentationParameters->FullScreen_RefreshRateInHz = d3dpp.FullScreen_RefreshRateInHz;
	pPresentationParameters->hDeviceWindow =			(DIS_HWND)d3dpp.hDeviceWindow;
	pPresentationParameters->MultiSampleQuality =		d3dpp.MultiSampleQuality;
	pPresentationParameters->MultiSampleType =			to_DIS.MultiSampleType( d3dpp.MultiSampleType );
	pPresentationParameters->PresentationInterval =		d3dpp.PresentationInterval;
	pPresentationParameters->SwapEffect  =				to_DIS.dSwapEffect( d3dpp.SwapEffect );
	pPresentationParameters->Windowed =					d3dpp.Windowed;
	
	return HR_to_DR( hr );
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetClipPlane( //Sets the coefficients of a user-defined clipping plane for the device.
	UInt32 Index, // [in] Index of the clipping plane for which the plane equation coefficients are to be set.
	const float *pPlane	//[in]Pointer to an address of a four-element array of values that represent the clipping plane coefficients to be set, in the form of the general plane equation. See Remarks.
	)
{
	HRESULT hr = pD3DDevice->SetClipPlane(Index, pPlane);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetClipStatus( //Sets the clip status.
		const DIS_CLIPSTATUS *pClipStatus//[in]  Pointer to a DIS_CLIPSTATUS structure, describing the clip status settings to be set.
	)
{

	D3DCLIPSTATUS9 cs;

	cs.ClipIntersection = pClipStatus->ClipIntersection;
	cs.ClipUnion = pClipStatus->ClipUnion;
	
	HRESULT hr = pD3DDevice->SetClipStatus(&cs);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT  D3D_DeviceInterface::SetCurrentTexturePalette( //Sets the current texture palette.
	UInt32 PaletteNumber //[in]
	)
{

	HRESULT hr = pD3DDevice->SetCurrentTexturePalette(PaletteNumber);
	
	return HR_to_DR( hr );

	//return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetCursorPosition( //Sets the cursor position and update options.
	UInt32 X,//[in]
	UInt32 Y,//[in]
	UInt32 Flags//[in]Specifies the update options for the cursor. Currently, only one flag is defined. D3DCURSOR_IMMEDIATE_UPDATE
	)
{

	pD3DDevice->SetCursorPosition(X, Y, Flags);
	
	//return HR_to_DR( hr );

	return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetCursorProperties( //Sets properties for the cursor.
	UInt32 XHotSpot,//[in]X-coordinate offset (in pixels) that marks the center of the cursor. The offset is relative to the upper-left corner of the cursor. When the cursor is given a new position, the image is drawn at an offset from this new position determined by subtracting the hot spot coordinates from the position.
	UInt32 YHotSpot,//[in]Y-coordinate offset (in pixels) that marks the center of the cursor. The offset is relative to the upper-left corner of the cursor. When the cursor is given a new position, the image is drawn at an offset from this new position determined by subtracting the hot spot coordinates from the position.
	LPSURFACE2D pCursorBitmap//[in]Pointer to an IDirect3DSurface9 interface. This parameter must point to an 8888 ARGB surface (format D3DFMT_A8R8G8B8). The contents of this surface will be copied and potentially format-converted into an internal buffer from which the cursor is displayed. The dimensions of this surface must be less than the dimensions of the display mode, and must be a power of two in each direction, although not necessarily the same power of two. The alpha channel must be either 0.0 or 1.0.
	)
{
	
	HRESULT hr = pD3DDevice->SetCursorProperties(
								XHotSpot, 
								YHotSpot, 
								LPSURFACE2D_D3D9(pCursorBitmap)->pd3dSurface);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetDepthStencilSurface( //Sets the depth stencil surface.
		LPSURFACE2D pNewZStencil // [in]Address of a pointer to an IDirect3DSurface9 interface representing the depth stencil surface. Setting this to NULL disables the depth stencil operation.
	)
{
	HRESULT hr;
	if( pNewZStencil == NULL )
	{
		hr = pD3DDevice->SetDepthStencilSurface(NULL);
	}
	else
	{
		hr = pD3DDevice->SetDepthStencilSurface(
							LPSURFACE2D_D3D9(pNewZStencil)->pd3dSurface);
	}
	 
	
	return HR_to_DR( hr );
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetDialogBoxMode( //This method allows the use of GDI dialog boxes in full-screen mode applications.
	bool bEnableDialogs	//[in]
	)
{

	HRESULT hr = pD3DDevice->SetDialogBoxMode(bEnableDialogs);
	
	return HR_to_DR( hr );

//	return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetFVF( //Sets the current vertex stream declaration.
	UInt32 fvf // [in]DWORD containing the fixed function vertex type. For more information, see D3DFVF.
	)
{
	HRESULT hr = pD3DDevice->SetFVF(fvf);
	
	return HR_to_DR( hr );
}

	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetGammaRamp( //Sets the gamma correction ramp for the implicit swap chain. This method will affect the entire screen (not just the active window if you are running in windowed mode).
	UInt32  iSwapChain,//[in]  
	UInt32 Flags,//[in]  Indicates whether correction should be applied. Gamma correction results in a more consistent display, but can incur processing overhead and should not be used frequently. Short-duration effects, such as flashing the whole screen red, should not be calibrated, but long-duration gamma changes should be calibrated. One of the following values can be set:
	//D3DSGR_CALIBRATE
	//If a gamma calibrator is installed, the ramp will be modified before being sent to the device to account for the system and monitor response curves. If a calibrator is not installed, the ramp will be passed directly to the device.
	//D3DSGR_NO_CALIBRATION
	//No gamma correction is applied. The supplied gamma table is transferred directly to the device.
	const DIS_GAMMARAMP *pRamp//[in]  
	)
{
	D3DGAMMARAMP ramp;

	for( UInt32 i = 0; i < 256; i++ )
	{
		ramp.red[i] = pRamp->red[i];
		ramp.green[i] = pRamp->green[i];
		ramp.blue[i] = pRamp->blue[i];
	}

	pD3DDevice->SetGammaRamp(
								iSwapChain, 
								Flags, 
								&ramp);
	
	return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetIndices( //Sets index data.
	LPINDEXBUFFER pIndexData // [in]
	)
{

	if( pIndexData == NULL )
	{
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->SetIndices(
								LPINDEXBUFFER_D3D9(pIndexData)->pd3dIndexBuffer);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetLight( //Assigns a set of lighting properties for this device.
	UInt32 Index, // [in] light index
	const DIS_LIGHT *pLight//[in] light
	)
{
	D3DLIGHT9 light;
	light.Ambient.r = pLight->Ambient.r;
	light.Ambient.g = pLight->Ambient.g;
	light.Ambient.b = pLight->Ambient.b;
	light.Ambient.a = pLight->Ambient.a;

	light.Diffuse.r = pLight->Diffuse.r;
	light.Diffuse.g = pLight->Diffuse.g;
	light.Diffuse.b = pLight->Diffuse.b;
	light.Diffuse.a = pLight->Diffuse.a;

	light.Specular.r = pLight->Specular.r;
	light.Specular.g = pLight->Specular.g;
	light.Specular.b = pLight->Specular.b;
	light.Specular.a = pLight->Specular.a;

	light.Position.x = pLight->Position.x;
	light.Position.y = pLight->Position.y;
	light.Position.z = pLight->Position.z;

	light.Direction.x = pLight->Direction.x;
	light.Direction.y = pLight->Direction.y;
	light.Direction.z = pLight->Direction.z;

	light.Attenuation0 = pLight->Attenuation0;
	light.Attenuation1 = pLight->Attenuation1;
	light.Attenuation2 = pLight->Attenuation2;

	light.Falloff = pLight->Falloff;
	light.Phi = pLight->Phi;
	light.Range = pLight->Range;
	light.Theta = pLight->Theta;
	light.Type = (D3DLIGHTTYPE)DIS_LightType[ pLight->Type ];

	HRESULT hr = pD3DDevice->SetLight(Index, &light);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetMaterial( //Sets the material properties for the device.
	const DIS_MATERIAL *pMaterial // [in] pointer to material structure
	)
{
	D3DMATERIAL9 mat;

	mat.Ambient.r = pMaterial->Ambient.r;
	mat.Ambient.g = pMaterial->Ambient.g;
	mat.Ambient.b = pMaterial->Ambient.b;
	mat.Ambient.a = pMaterial->Ambient.a;

	mat.Diffuse.r = pMaterial->Diffuse.r;
	mat.Diffuse.g = pMaterial->Diffuse.g;
	mat.Diffuse.b = pMaterial->Diffuse.b;
	mat.Diffuse.a = pMaterial->Diffuse.a;

	mat.Specular.r = pMaterial->Specular.r;
	mat.Specular.g = pMaterial->Specular.g;
	mat.Specular.b = pMaterial->Specular.b;
	mat.Specular.a = pMaterial->Specular.a;

	mat.Emissive.r = pMaterial->Emissive.r;
	mat.Emissive.g = pMaterial->Emissive.g;
	mat.Emissive.b = pMaterial->Emissive.b;
	mat.Emissive.a = pMaterial->Emissive.a;
	
	mat.Power = pMaterial->Power;

	HRESULT hr = pD3DDevice->SetMaterial(&mat);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetNPatchMode( //Enable or disable N-patches.
	float nSegments // [in]Specifies the number of subdivision segments. If the number of segments is less than 1.0, N-patches are disabled. The default value is 0.0.
	)
{

	HRESULT hr = pD3DDevice->SetNPatchMode(nSegments);
	
	return HR_to_DR( hr );
}



//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetPaletteEntries( //Sets palette entries.
	UInt32 PaletteNumber,//[in]  An ordinal value identifying the particular palette upon which the operation is to be performed.
	const DIS_PALETTEENTRY *pEntries//[in]  Pointer to a PALETTEENTRY structure, representing the palette entries to set. The number of PALETTEENTRY structures pointed to by pEntries is assumed to be 256. See Remarks
	)
{
	PALETTEENTRY pE;

	pE.peRed = pEntries->peRed;
	pE.peGreen = pEntries->peGreen;
	pE.peBlue = pEntries->peBlue;
	pE.peFlags = pEntries->peFlags;
	
	HRESULT hr = pD3DDevice->SetPaletteEntries(PaletteNumber, &pE);
	
	return HR_to_DR( hr );
}
	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetPixelShader( //Sets the current pixel shader to a previously created pixel shader.
	LPPIXELSHADER pShader // [in]  Pixel shader interface.
	)
{

	if( pShader == NULL )
	{
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->SetPixelShader(
								LPPIXELSHADER_D3D9(pShader)->pd3dPixelShader);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetPixelShaderConstantB( //Sets a Boolean shader constant.
	UInt32 StartRegister, // [in]Register number that will contain the first constant value.
	const bool *pConstantData, // [in]Pointer to an array of constants.
	UInt32 BoolCount // [in]  Number of boolean values in the array of constants.
	)
{

	HRESULT hr = pD3DDevice->SetPixelShaderConstantB(StartRegister,
													(const BOOL*)pConstantData,
													BoolCount);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetPixelShaderConstantF( //Sets a floating-point shader constant.
	UInt32 StartRegister, // [in]Register number that will contain the first constant value.
	const float *pConstantData, // [in]Pointer to an array of constants.
	UInt32 Vector4fCount // [in]  Number of 4 float vectors in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->SetPixelShaderConstantF(StartRegister,
													pConstantData,
													Vector4fCount);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetPixelShaderConstantI( //Sets an integer shader constant.
	UInt32 StartRegister, // [in]Register number that will contain the first constant value.
	const int *pConstantData, // [in]Pointer to an array of constants.
	UInt32 Vector4iCount // [in]  Number of 4 integer vectors in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->SetPixelShaderConstantI(StartRegister,
													(const int*)pConstantData,
													Vector4iCount);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetRenderState( //Sets a single device render-state parameter.
	DIS_RENDERSTATETYPE State, //[in]  Device state variable that is being modified. This parameter can be any member of the DIS_RENDERSTATETYPE enumerated type.
	UInt32 Value //[in]  New value for the device render state to be set. The meaning of this parameter is dependent on the value specified for State. For example, if State were D3DRS_SHADEMODE, the second parameter would be one member of the DIS_SHADEMODE enumerated type.
	)
{
	D3DRENDERSTATETYPE d3dState = D3DRENDERSTATETYPE( DIS_RenderStateType[ State ] );
	DWORD newValue = 0;

#ifndef SLOW_MODE
	return m_RenderStateSetter[d3dState]->SetState((UInt32)State, (UInt32)Value);
/*
	or ifdef STUPID_MODE
*/
#else
	switch( State )
	{
	case DISRS_ZENABLE: 
		{
//Depth-buffering state as one member of the D3DZBUFFERTYPE enumerated type. Set this state to D3DZB_TRUE to enable z-buffering, D3DZB_USEW to enable w-buffering, or D3DZB_FALSE to disable depth buffering.
//The default Value for this render state is D3DZB_TRUE if a depth stencil was created along with the swap chain by setting the EnableAutoDepthStencil member of the D3DPRESENT_PARAMETERS structure to TRUE, and D3DZB_FALSE otherwise.
			if( Value == DIS_ZB_TRUE )
			{
				newValue = D3DZB_TRUE;
			}
			else
			{
				newValue = D3DZB_FALSE;
			}
		}
		break;
	case DISRS_FILLMODE:
		{
//One or more members of the D3DFILLMODE enumerated type. The default Value is D3DFILL_SOLID
			newValue = (D3DFILLMODE)DIS_FillMode[ Value ];//to_DIS.FillMode( (D3DFILLMODE)Value );
		}
		break;

	case DISRS_SHADEMODE:
		{
			newValue = (D3DSHADEMODE)DIS_ShadeMode[ Value ];//to_DIS.dShadeMode( (D3DSHADEMODE)Value );
//One or more members of the D3DSHADEMODE enumerated type. The default Value is D3DSHADE_GOURAUD
		}
		break;

	case DISRS_ZWRITEENABLE:
		{
			newValue = Value;
//TRUE to enable the application to write to the depth buffer. The default Value is TRUE. This member enables an application to prevent the system from updating the depth buffer with new depth Values. If FALSE, depth comparisons are still made according to the render state DISRS_ZFUNC, assuming that depth buffering is taking place, but depth Values are not written to the buffer.
		}
		break;
	case DISRS_ALPHATESTENABLE:
		{
			newValue = Value;
//TRUE to enable per pixel alpha testing. If the test passes, the pixel is processed by the frame buffer. Otherwise, all frame-buffer processing is skipped for the pixel.
//The test is done by comparing the incoming alpha Value with the reference alpha Value, using the comparison function provided by the DISRS_ALPHAFUNC render state. The reference alpha Value is determined by the Value set for DISRS_ALPHAREF. For more information, see Alpha Testing State (Direct3D 9).
//The default Value of this parameter is FALSE.
		}
		break;
	case DISRS_LASTPIXEL:
		{
			newValue = Value;
//The default Value is TRUE, which enables drawing of the last pixel in a line. To prevent drawing of the last pixel, set this Value to FALSE. For more information, see Outline and Fill State (Direct3D 9).
		}
		break;

	case DISRS_SRCBLEND:
		{
			newValue = (D3DBLEND )this->DIS_Blend_Func[ Value ];// to_DIS.BlendType( D3DBLEND( Value ) );
//One member of the D3DBLEND enumerated type. The default Value is D3DBLEND_ONE
		}
		break;
	case DISRS_DESTBLEND:
		{
			newValue = (D3DBLEND )this->DIS_Blend_Func[ Value ];
//One member of the D3DBLEND enumerated type. The default Value is D3DBLEND_ZERO.
		}
		break;
	case DISRS_CULLMODE:
		{
			newValue = (D3DCULL )DIS_Cullmode[ Value ];// to_DIS.CullMode( D3DCULL( Value ) );
//Specifies how back-facing triangles are culled, if at all. This can be set to one member of the D3DCULL enumerated type. The default Value is D3DCULL_CCW.
		}
		break;

	case DISRS_ZFUNC:
		{
			newValue = (D3DCMPFUNC )this->DIS_CmpFunc[ Value ];//to_DIS.CompareFunc( D3DCMPFUNC( Value ) );
//One member of the D3DCMPFUNC enumerated type. The default Value is D3DCMP_LESSEQUAL. This member enables an application to accept or reject a pixel, based on its distance from the camera.
//The depth Value of the pixel is compared with the depth-buffer Value. If the depth Value of the pixel passes the comparison function, the pixel is written.
//The depth Value is written to the depth buffer only if the render state is TRUE.
//Software rasterizers and many hardware accelerators work faster if the depth test fails, because there is no need to filter and modulate the texture if the pixel is not going to be rendered.
		}
		break;
	case DISRS_ALPHAREF:
		{
			newValue = Value;
//Value that specifies a reference alpha Value against which pixels are tested when alpha testing is enabled. This is an 8-bit Value placed in the low 8 bits of the DWORD render-state Value. Values can range from 0x00000000 through 0x000000FF. The default Value is 0.
		}
		break;
	case DISRS_ALPHAFUNC:
		{
			newValue = (D3DCMPFUNC )this->DIS_CmpFunc[ Value ];//to_DIS.CompareFunc( D3DCMPFUNC( Value ) );
//One member of the D3DCMPFUNC enumerated type. The default Value is D3DCMP_ALWAYS. This member enables an application to accept or reject a pixel, based on its alpha Value.
		}
		break;

	case DISRS_DITHERENABLE:
		{
			newValue = Value;
//TRUE to enable dithering. The default Value is FALSE.
		}
		break;

	case DISRS_ALPHABLENDENABLE:
		{
			newValue = Value;
//TRUE to enable alpha-blended transparency. The default Value is FALSE.
//The type of alpha blending is determined by the DISRS_SRCBLEND and DISRS_DESTBLEND render states.
		}
		break;
	case DISRS_FOGENABLE:
		{
			newValue = Value;
//TRUE to enable fog blending. The default Value is FALSE. For more information about using fog blending, see Fog.
		}
		break;
	case DISRS_SPECULARENABLE:
		{
			newValue = Value;
//TRUE to enable specular highlights. The default Value is FALSE.
//Specular highlights are calculated as though every vertex in the object being lit is at the object's origin. This gives the expected results as long as the object is modeled around the origin and the distance from the light to the object is relatively large. In other cases, the results as undefined.
//When this member is set to TRUE, the specular color is added to the base color after the texture cascade but before alpha blending.
		}
		break;
	case DISRS_FOGCOLOR:
		{
			newValue = Value;
//Value whose type is D3DCOLOR. The default Value is 0. For more information about fog color, see Fog Color (Direct3D 9).
		}
		break;
	
	case DISRS_FOGTABLEMODE:
		{
			newValue = (D3DFOGMODE )this->DIS_FogMode[ Value ];//to_DIS.FogMode( D3DFOGMODE( Value ));
//The fog formula to be used for pixel fog. Set to one of the members of the D3DFOGMODE enumerated type. The default Value is D3DFOG_NONE. For more information about pixel fog, see Pixel Fog (Direct3D 9).
		}
		break;
	case DISRS_FOGSTART:
		{
			newValue = Value;
//Depth at which pixel or vertex fog effects begin for linear fog mode. The default Value is 0.0f. Depth is specified in world space for vertex fog and either device space [0.0, 1.0] or world space for pixel fog. For pixel fog, these Values are in device space when the system uses z for fog calculations and world-world space when the system is using eye-relative fog (w-fog). For more information, see Fog Parameters (Direct3D 9) and Eye-Relative vs. Z-based Depth.
//Values for this render state are floating-point Values. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
//pDevice9->SetRenderState(DISRS_FOGSTART, 
//                         *((DWORD*) (&fFogStart)));
		}
		break;
	case DISRS_FOGEND:
		{
			newValue = Value;
//Depth at which pixel or vertex fog effects end for linear fog mode. The default Value is 1.0f. Depth is specified in world space for vertex fog and either device space [0.0, 1.0] or world space for pixel fog. For pixel fog, these Values are in device space when the system uses z for fog calculations and in world space when the system is using eye-relative fog (w-fog). For more information, see Fog Parameters (Direct3D 9) and Eye-Relative vs. Z-based Depth.
//Values for this render state are floating-point Values. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
//m_pDevice9->SetRenderState(DISRS_FOGEND, *((DWORD*) (&fFogEnd)));
		}
		break;
	case DISRS_FOGDENSITY:
		{
			newValue = Value;
//Fog density for pixel or vertex fog used in the exponential fog modes (D3DFOG_EXP and D3DFOG_EXP2). Valid density Values range from 0.0 through 1.0. The default Value is 1.0. For more information, see Fog Parameters (Direct3D 9).
//Values for this render state are floating-point Values. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
//    m_pDevice9->SetRenderState(DISRS_FOGDENSITY, *((DWORD*) (&fFogDensity)));
		}
		break;
	case DISRS_RANGEFOGENABLE:
		{
			newValue = Value;
//TRUE to enable range-based vertex fog. The default Value is FALSE, in which case the system uses depth-based fog. In range-based fog, the distance of an object from the viewer is used to compute fog effects, not the depth of the object (that is, the z-coordinate) in the scene. In range-based fog, all fog methods work as usual, except that they use range instead of depth in the computations.
//Range is the correct factor to use for fog computations, but depth is commonly used instead because range is time-consuming to compute and depth is generally already available. Using depth to calculate fog has the undesirable effect of having the fogginess of peripheral objects change as the viewer's eye moves - in this case, the depth changes and the range remains constant.
//Because no hardware currently supports per-pixel range-based fog, range correction is offered only for vertex fog.
//For more information, see Vertex Fog (Direct3D 9).
		}
		break;
	case DISRS_STENCILENABLE:
		{
			newValue = Value;
//TRUE to enable stenciling, or FALSE to disable stenciling. The default Value is FALSE. For more information, see Stencil Buffer Techniques (Direct3D 9).
		}
		break;
	case DISRS_STENCILFAIL:
		{
			newValue = (D3DSTENCILOP )DIS_StencilOp[ Value ];//to_DIS.dStencilOp(D3DSTENCILOP(Value));
//Stencil operation to perform if the stencil test fails. Values are from the D3DSTENCILOP enumerated type. The default Value is D3DSTENCILOP_KEEP.
		}
		break;
	case DISRS_STENCILZFAIL:
		{
			newValue = (D3DSTENCILOP )DIS_StencilOp[ Value ];
//Stencil operation to perform if the stencil test passes and the depth test (z-test) fails. Values are from the D3DSTENCILOP enumerated type. The default Value is D3DSTENCILOP_KEEP.
		}
		break;
	case DISRS_STENCILPASS:
		{
			newValue = (D3DSTENCILOP )DIS_StencilOp[ Value ];
//Stencil operation to perform if both the stencil and the depth (z) tests pass. Values are from the D3DSTENCILOP enumerated type. The default Value is D3DSTENCILOP_KEEP.
		}
		break;
	case DISRS_STENCILFUNC:
		{
			newValue = (D3DCMPFUNC )this->DIS_CmpFunc[ Value ];
//Comparison function for the stencil test. Values are from the D3DCMPFUNC enumerated type. The default Value is D3DCMP_ALWAYS.
//The comparison function is used to compare the reference Value to a stencil buffer entry. This comparison applies only to the bits in the reference Value and stencil buffer entry that are set in the stencil mask (set by the DISRS_STENCILMASK render state). If TRUE, the stencil test passes.
		}
		break;
	case DISRS_STENCILREF:
		{
			newValue = Value;
//An int reference Value for the stencil test. The default Value is 0.
		}
		break;
	case DISRS_STENCILMASK:
		{
			newValue = Value;
//Mask applied to the reference Value and each stencil buffer entry to determine the significant bits for the stencil test. The default mask is 0xFFFFFFFF.
		}
		break;
	case DISRS_STENCILWRITEMASK:
		{
			newValue = Value;
//Write mask applied to Values written into the stencil buffer. The default mask is 0xFFFFFFFF.
		}
		break;
	case DISRS_TEXTUREFACTOR:
		{
			newValue = Value;
//Color used for multiple-texture blending with the D3DTA_TFACTOR texture-blending argument or the D3DTOP_BLENDFACTORALPHA texture-blending operation. The associated Value is a D3DCOLOR variable. The default Value is opaque white (0xFFFFFFFF).
		}
		break;
	case DISRS_WRAP0:
		{
			newValue = Value;
//Texture-wrapping behavior for multiple sets of texture coordinates. Valid Values for this render state can be any combination of the D3DWRAPCOORD_0 (or D3DWRAP_U), D3DWRAPCOORD_1 (or D3DWRAP_V), D3DWRAPCOORD_2 (or D3DWRAP_W), and D3DWRAPCOORD_3 flags. These cause the system to wrap in the direction of the first, second, third, and fourth dimensions, sometimes referred to as the s, t, r, and q directions, for a given texture. The default Value for this render state is 0 (wrapping disabled in all directions).
		}
		break;
	case DISRS_WRAP1: 
		{
			newValue = Value; 
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP2:
		{
//See DISRS_WRAP0.
			newValue = Value; 
		}
		break;

	case DISRS_WRAP3:
		{
			newValue = Value; 
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP4:
		{
			newValue = Value; 
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP5:
		{
			newValue = Value; 
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP6:
		{
			newValue = Value; 
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP7:
		{
			newValue = Value; 
//See DISRS_WRAP0.
		}
		break;

	case DISRS_CLIPPING:
		{
			newValue = Value;
//TRUE to enable primitive clipping by Direct3D, or FALSE to disable it. The default Value is TRUE.
		}
		break;
	case DISRS_LIGHTING:
		{
			newValue = Value;
//TRUE to enable Direct3D lighting, or FALSE to disable it. The default Value is TRUE. Only vertices that include a vertex normal are properly lit; vertices that do not contain a normal employ a dot product of 0 in all lighting calculations.
		}
		break;
	case DISRS_AMBIENT:
		{
			newValue = Value;
//Ambient light color. This Value is of type D3DCOLOR. The default Value is 0.
		}
		break;
	case DISRS_FOGVERTEXMODE:
		{
			newValue = (D3DFOGMODE )DIS_FogMode[ Value ];//to_DIS.FogMode( D3DFOGMODE(Value) );
//Fog formula to be used for vertex fog. Set to one member of the D3DFOGMODE enumerated type. The default Value is D3DFOG_NONE.
		}
		break;
	case DISRS_COLORVERTEX:
		{
			newValue = Value;
//TRUE to enable per-vertex color or FALSE to disable it. The default Value is TRUE. Enabling per-vertex color allows the system to include the color defined for individual vertices in its lighting calculations.
//For more information, see the following render states:
		}
		break;

	case DISRS_LOCALVIEWER:
		{
			newValue = Value;
//TRUE to enable camera-relative specular highlights, or FALSE to use orthogonal specular highlights. The default Value is TRUE. Applications that use orthogonal projection should specify FALSE.
		}
		break;
	case DISRS_NORMALIZENORMALS:
		{
			newValue = Value;
//TRUE to enable automatic normalization of vertex normals, or FALSE to disable it. The default Value is FALSE. Enabling this feature causes the system to normalize the vertex normals for vertices after transforming them to camera space, which can be computationally time-consuming.
		}
		break;
	case DISRS_DIFFUSEMATERIALSOURCE:
		{
			newValue = (D3DMATERIALCOLORSOURCE )this->DIS_MaterialColorSource[ Value ];//to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(Value) );
//Diffuse color source for lighting calculations. Valid Values are members of the D3DMATERIALCOLORSOURCE enumerated type. The default Value is D3DMCS_COLOR1. The Value for this render state is used only if the DISRS_COLORVERTEX render state is set to TRUE.
		}
		break;
	case DISRS_SPECULARMATERIALSOURCE:
		{
			newValue = (D3DMATERIALCOLORSOURCE )this->DIS_MaterialColorSource[ Value ];//to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(Value) );
//Specular color source for lighting calculations. Valid Values are members of the D3DMATERIALCOLORSOURCE enumerated type. The default Value is D3DMCS_COLOR2.
		}
		break;
	case DISRS_AMBIENTMATERIALSOURCE:
		{
			newValue = (D3DMATERIALCOLORSOURCE )this->DIS_MaterialColorSource[ Value ];//to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(Value) );
//Ambient color source for lighting calculations. Valid Values are members of the D3DMATERIALCOLORSOURCE enumerated type. The default Value is D3DMCS_MATERIAL.
		}
		break;
	case DISRS_EMISSIVEMATERIALSOURCE:
		{
			newValue = (D3DMATERIALCOLORSOURCE )this->DIS_MaterialColorSource[ Value ];//to_DIS.MaterialColorSource( D3DMATERIALCOLORSOURCE(Value) );
//Emissive color source for lighting calculations. Valid Values are members of the D3DMATERIALCOLORSOURCE enumerated type. The default Value is D3DMCS_MATERIAL.
		}
		break;
	case DISRS_VERTEXBLEND:
		{
			newValue = (D3DVERTEXBLENDFLAGS )this->DIS_VertexBlendFlags[ Value ];//to_DIS.dVertexBlendFlags( D3DVERTEXBLENDFLAGS(Value) );
//Number of matrices to use to perform geometry blending, if any. Valid Values are members of the D3DVERTEXBLENDFLAGS enumerated type. The default Value is D3DVBF_DISABLE.
		}
		break;
	case DISRS_CLIPPLANEENABLE:
		{
			newValue = Value;
//Enables or disables user-defined clipping planes. 
//Valid Values are any DWORD in which the status of each bit (set or not set) toggles the activation state 
//of a corresponding user-defined clipping plane. 
//The least significant bit (bit 0) controls the first clipping plane at index 0, and subsequent bits control the activation of clipping planes at higher indexes. 
//If a bit is set, the system applies the appropriate clipping plane during scene rendering. The default Value is 0.
//The D3DCLIPPLANEn macros are defined to provide a convenient way to enable clipping planes.
		}
		break;
	case DISRS_POINTSIZE:
		{
			newValue = Value;
//A float Value that specifies the size to use for point size computation in cases where point size is not specified for each vertex. This Value is not used when the vertex contains point size. This Value is in screen space units if DISRS_POINTSCALEENABLE is FALSE; otherwise this Value is in world space units. The default Value is the Value a driver returns. If a driver returns 0 or 1, the default Value is 64, which allows software point size emulation. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
		}
		break;
//m_pDevice9->SetRenderState(DISRS_POINTSIZE, *((DWORD*)&pointSize));
	case DISRS_POINTSIZE_MIN:
		{
			newValue = Value;
//A float Value that specifies the minimum size of point primitives. Point primitives are clamped to this size during rendering. Setting this to Values smaller than 1.0 results in points dropping out when the point does not cover a pixel center and antialiasing is disabled or being rendered with reduced intensity when antialiasing is enabled. The default Value is 1.0f. The range for this Value is greater than or equal to 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
//m_pDevice9->SetRenderState(DISRS_POINTSIZE_MIN, *((DWORD*)&pointSizeMin));
		}
		break;
	case DISRS_POINTSPRITEENABLE:
		{
			newValue = Value;
//bool Value. When TRUE, texture coordinates of point primitives are set so that full textures are mapped on each point. When FALSE, the vertex texture coordinates are used for the entire point. The default Value is FALSE. You can achieve DirectX 7 style single-pixel points by setting DISRS_POINTSCALEENABLE to FALSE and DISRS_POINTSIZE to 1.0, which are the default Values.
		}
		break;
	case DISRS_POINTSCALEENABLE:
		{
			newValue = Value;
//bool Value that controls computation of size for point primitives. When TRUE, the point size is interpreted as a camera space Value and is scaled by the distance function and the frustum to viewport y-axis scaling to compute the final screen-space point size. When FALSE, the point size is interpreted as screen space and used directly. The default Value is FALSE.
		}
		break;
	case DISRS_POINTSCALE_A:
		{
			newValue = Value;
//A float Value that controls for distance-based size attenuation for point primitives. Active only when DISRS_POINTSCALEENABLE is TRUE. The default Value is 1.0f. The range for this Value is greater than or equal to 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
//m_pDevice9->SetRenderState(DISRS_POINTSCALE_A, *((DWORD*)&pointScaleA));
		}
		break;
	case DISRS_POINTSCALE_B:
		{
			newValue = Value;
//A float Value that controls for distance-based size attenuation for point primitives. Active only when DISRS_POINTSCALEENABLE is TRUE. The default Value is 0.0f. The range for this Value is greater than or equal to 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
//m_pDevice9->SetRenderState(DISRS_POINTSCALE_B, *((DWORD*)&pointScaleB));
		}
		break;
	case DISRS_POINTSCALE_C:
		{
			newValue = Value;
//A float Value that controls for distance-based size attenuation for point primitives. Active only when DISRS_POINTSCALEENABLE is TRUE. The default Value is 0.0f. The range for this Value is greater than or equal to 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
//m_pDevice9->SetRenderState(DISRS_POINTSCALE_C, *((DWORD*)&pointScaleC));
		}
		break;
	case DISRS_MULTISAMPLEANTIALIAS:
		{
			newValue = Value;
//bool Value that determines how individual samples are computed when using a multisample render-target buffer. When set to TRUE, the multiple samples are computed so that full-scene antialiasing is performed by sampling at different sample positions for each multiple sample. When set to FALSE, the multiple samples are all written with the same sample Value, sampled at the pixel center, which allows non-antialiased rendering to a multisample buffer. This render state has no effect when rendering to a single sample buffer. The default Value is TRUE.
		}
		break;
	case DISRS_MULTISAMPLEMASK:
		{
			newValue = Value;
//Each bit in this mask, starting at the least significant bit (LSB), controls modification of one of the samples in a multisample render target. Thus, for an 8-sample render target, the low byte contains the eight write enables for each of the eight samples. This render state has no effect when rendering to a single sample buffer. The default Value is 0xFFFFFFFF.
//This render state enables use of a multisample buffer as an accumulation buffer, doing multipass rendering of geometry where each pass updates a subset of samples.
//If there are n multisamples and k enabled samples, the resulting intensity of the rendered image should be k/n. Each component RGB of every pixel is factored by k/n.
		}
		break;
	case DISRS_PATCHEDGESTYLE:
		{
			newValue = (D3DPATCHEDGESTYLE )this->DIS_PatchEdgeStyle[ Value ];//to_DIS.PatchEdgeStyle( D3DPATCHEDGESTYLE( Value ));
//Sets whether patch edges will use float style tessellation. Possible Values are defined by the D3DPATCHEDGESTYLE enumerated type. The default Value is D3DPATCHEDGE_DISCRETE.
		}
		break;
	case DISRS_DEBUGMONITORTOKEN:
		{
			newValue = (D3DDEBUGMONITORTOKENS )this->DIS_DebugMonitor[ Value ];//to_DIS.DebugMonitorToken( D3DDEBUGMONITORTOKENS(Value) );
//Set only for debugging the monitor. Possible Values are defined by the D3DDEBUGMONITORTOKENS enumerated type. Note that if DISRS_DEBUGMONITORTOKEN is set, the call is treated as passing a token to the debug monitor. For example, if - after passing D3DDMT_ENABLE or D3DDMT_DISABLE to DISRS_DEBUGMONITORTOKEN - other token Values are passed in, the state (enabled or disabled) of the debug monitor will still persist.
//This state is only useful for debug builds. The debug monitor defaults to D3DDMT_ENABLE.
		}
		break;
	case DISRS_POINTSIZE_MAX:
		{
			newValue = Value;
//A float Value that specifies the maximum size to which point sprites will be clamped. The Value must be less than or equal to the MaxPointSize member of D3DCAPS9 and greater than or equal to DISRS_POINTSIZE_MIN. The default Value is 64.0. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
//m_pDevice9->SetRenderState(DISRS_PONTSIZE_MAX, *((DWORD*)&pointSizeMax));
		}
		break;
	case DISRS_INDEXEDVERTEXBLENDENABLE:
		{
			newValue = Value;
//bool Value that enables or disables indexed vertex blending. The default Value is FALSE. When set to TRUE, indexed vertex blending is enabled. When set to FALSE, indexed vertex blending is disabled. If this render state is enabled, the user must pass matrix indices as a packed DWORDwith every vertex. When the render state is disabled and vertex blending is enabled through the DISRS_VERTEXBLEND state, it is equivalent to having matrix indices 0, 1, 2, 3 in every vertex.
		}
		break;
	case DISRS_COLORWRITEENABLE:
		{
			newValue = Value;
//UINT Value that enables a per-channel write for the render-target color buffer. A set bit results in the color channel being updated during 3D rendering. A clear bit results in the color channel being unaffected. This functionality is available if the D3DPMISCCAPS_COLORWRITEENABLE capabilities bit is set in the PrimitiveMiscCaps member of the D3DCAPS9 structure for the device. This render state does not affect the clear operation. The default Value is 0x0000000F.
//Valid Values for this render state can be any combination of the D3DCOLORWRITEENABLE_ALPHA, D3DCOLORWRITEENABLE_BLUE, D3DCOLORWRITEENABLE_GREEN, or D3DCOLORWRITEENABLE_RED flags.
		}
		break;
	//case DISRS_TWEENF2ACTOR:
	//	{
	//		newValue = Value;
//A float Value that controls the tween factor. The default Value is 0.0f. Because the IDirect3DDevice9::SetRenderState method accepts DWORD Values, your application must cast a variable that contains the Value, as shown in the following code example.
	//	}
	//	break;
	case DISRS_BLENDOP:
		{
			newValue = (D3DBLENDOP )this->DIS_BlendOp[ Value ];//to_DIS.BlendOp(D3DBLENDOP(Value));
//Value used to select the arithmetic operation applied when the alpha blending render state, DISRS_ALPHABLENDENABLE, is set to TRUE. Valid Values are defined by the D3DBLENDOP enumerated type. The default Value is D3DBLENDOP_ADD.
//If the D3DPMISCCAPS_BLENDOP device capability is not supported, then D3DBLENDOP_ADD is performed.
		}
		break;
	case DISRS_POSITIONDEGREE:
		{
			newValue = (D3DDEGREETYPE )this->DIS_DegreeType[ Value ];//to_DIS.DegreeType(D3DDEGREETYPE(Value));
//N-patch position interpolation degree. The Values can be D3DDEGREE_CUBIC (default) or D3DDEGREE_LINEAR. For more information, see D3DDEGREETYPE.
		}
		break;
	case DISRS_NORMALDEGREE:
		{
			newValue = (D3DDEGREETYPE )this->DIS_DegreeType[ Value ];
//N-patch normal interpolation degree. The Values can be D3DDEGREE_LINEAR (default) or D3DDEGREE_QUADRATIC. For more information, see D3DDEGREETYPE.
		}
		break;
	case DISRS_SCISSORTESTENABLE:
		{
			newValue = Value;
//TRUE to enable scissor testing and FALSE to disable it. The default Value is FALSE.
		}
		break;
	case DISRS_SLOPESCALEDEPTHBIAS:
		{
			newValue = Value;
//Used to determine how much bias can be applied to co-planar primitives to reduce z-fighting. The default Value is 0.
//bias = (max * DISRS_SLOPESCALEDEPTHBIAS) + DISRS_DEPTHBIAS.
//where max is the maximum depth slope of the triangle being rendered.
		}
		break;
	case DISRS_ANTIALIASEDLINEENABLE:
		{
			newValue = Value;
//TRUE to enable line antialiasing, FALSE to disable line antialiasing. The default Value is FALSE.
//When rendering to a multisample render target, DISRS_ANTIALIASEDLINEENABLE is ignored and all lines are rendered aliased. Use ID3DXLine for antialiased line rendering in a multisample render target.
		}
		break;
	case DISRS_MINTESSELLATIONLEVEL:
		{
			newValue = Value;
//Minimum tessellation level. The default Value is 1.0f. See Tessellation (Direct3D 9).
		}
		break;
	case DISRS_MAXTESSELLATIONLEVEL:
		{
			newValue = Value;
//Maximum tessellation level. The default Value is 1.0f. See Tessellation (Direct3D 9).
		}
		break;
	case DISRS_ADAPTIVETESS_X:
		{
			newValue = Value;
//Amount to adaptively tessellate, in the x direction. Default Value is 0.0f. See Adaptive Tessellation.
		}
		break;

	case DISRS_ADAPTIVETESS_Y:
		{
			newValue = Value;
//Amount to adaptively tessellate, in the y direction. Default Value is 0.0f. See Adaptive_Tessellation.
		}
		break;
	case DISRS_ADAPTIVETESS_Z:
		{
			newValue = Value;
//Amount to adaptively tessellate, in the z direction. Default Value is 1.0f. See Adaptive_Tessellation.
		}
		break;
	case DISRS_ADAPTIVETESS_W:
		{
			newValue = Value;
//Amount to adaptively tessellate, in the w direction. Default Value is 0.0f. See Adaptive_Tessellation.
		}
		break;
	case DISRS_ENABLEADAPTIVETESSELLATION:
		{
			newValue = Value;
//TRUE to enable adaptive tessellation, FALSE to disable it. The default Value is FALSE. See Adaptive_Tessellation.
		}
	case DISRS_TWOSIDEDSTENCILMODE:
		{
			newValue = Value;
//TRUE enables two-sided stenciling, FALSE disables it. The default Value is FALSE. The application should set DISRS_CULLMODE to D3DCULL_NONE to enable two-sided stencil mode. If the triangle winding order is clockwise, the DISRS_STENCIL* operations will be used. If the winding order is counterclockwise, the DISRS_CCW_STENCIL* operations will be used.
//To see if two-sided stencil is supported, check the StencilCaps member of D3DCAPS9 for D3DSTENCILCAPS_TWOSIDED. See also D3DSTENCILCAPS.
		}
		break;
	case DISRS_CCW_STENCILFAIL:
		{
			newValue = (D3DSTENCILOP )this->DIS_StencilOp[ Value ];//to_DIS.dStencilOp( D3DSTENCILOP(Value));
//Stencil operation to perform if CCW stencil test fails. Values are from the D3DSTENCILOP enumerated type. The default Value is D3DSTENCILOP_KEEP.
		}
		break;
	case DISRS_CCW_STENCILZFAIL:
		{
			newValue = (D3DSTENCILOP )this->DIS_StencilOp[ Value ];
//Stencil operation to perform if CCW stencil test passes and z-test fails. Values are from the D3DSTENCILOP enumerated type. The default Value is D3DSTENCILOP_KEEP.
		}
		break;
	case DISRS_CCW_STENCILPASS:
		{
			newValue = (D3DSTENCILOP )this->DIS_StencilOp[ Value ];
//Stencil operation to perform if both CCW stencil and z-tests pass. Values are from the D3DSTENCILOP enumerated type. The default Value is D3DSTENCILOP_KEEP.
		}
		break;
	case DISRS_CCW_STENCILFUNC:
		{
			newValue = (D3DSTENCILOP )this->DIS_StencilOp[ Value ];
//The comparison function. CCW stencil test passes if ((ref & mask) stencil function (stencil & mask)) is TRUE. Values are from the D3DCMPFUNC enumerated type. The default Value is D3DCMP_ALWAYS.
		}
		break;
	case DISRS_COLORWRITEENABLE1:
		{
			newValue = Value;
//Additional ColorWriteEnable Values for the devices. See DISRS_COLORWRITEENABLE. This functionality is available if the D3DPMISCCAPS_INDEPENDENTWRITEMASKS capabilities bit is set in the PrimitiveMiscCaps member of the D3DCAPS9 structure for the device. The default Value is 0x0000000f.
		}
		break;
	case DISRS_COLORWRITEENABLE2:
		{
			newValue = Value;
//Additional ColorWriteEnable Values for the devices. See DISRS_COLORWRITEENABLE. This functionality is available if the D3DPMISCCAPS_INDEPENDENTWRITEMASKS capabilities bit is set in the PrimitiveMiscCaps member of the D3DCAPS9 structure for the device. The default Value is 0x0000000f.
		}
		break;
	case DISRS_COLORWRITEENABLE3:
		{
			newValue = Value;
//Additional ColorWriteEnable Values for the devices. See DISRS_COLORWRITEENABLE. This functionality is available if the D3DPMISCCAPS_INDEPENDENTWRITEMASKS capabilities bit is set in the PrimitiveMiscCaps member of the D3DCAPS9 structure for the device. The default Value is 0x0000000f.
		}
		break;
	case DISRS_BLENDFACTOR:
		{
			newValue = Value;
//D3DCOLOR used for a constant blend-factor during alpha blending. This functionality is available if the D3DPBLENDCAPS_BLENDFACTOR capabilities bit is set in the SrcBlendCaps member of D3DCAPS9 or the DestBlendCaps member of D3DCAPS9. See D3DRENDERSTATETYPE. The default Value is 0xffffffff.
		}
		break;
	case DISRS_SRGBWRITEENABLE:
		{
			newValue = Value;
//Enable render-target writes to be gamma corrected to sRGB. The format must expose D3DUSAGE_SRGBWRITE. The default Value is 0.
		}
		break;
	case DISRS_DEPTHBIAS:
		{
			newValue = Value;
//A floating-point Value that is used for comparison of depth Values. See Depth Bias (Direct3D 9). The default Value is 0.
		}
		break;
	case DISRS_WRAP8:
		{
			newValue = Value;
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP9:
		{
			newValue = Value;
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP10:
		{
			newValue = Value;
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP11:
		{
			newValue = Value;
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP12:
		{
			newValue = Value;
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP13:
		{
			newValue = Value;
//See DISRS_WRAP0.
		}
		break;
	case DISRS_WRAP14:
		{
			newValue = Value;
//See DISRS_WRAP0.
		}
		break;

	case DISRS_WRAP15:
		{
			newValue = Value;
//See DISRS_WRAP0.
		}
		break;
	case DISRS_SEPARATEALPHABLENDENABLE:
		{
			newValue = Value;
//TRUE enables the separate blend mode for the alpha channel. The default Value is FALSE.
//When set to FALSE, the render-target blending factors and operations applied to alpha are forced to be the same as those defined for color. This mode is effectively hardwired to FALSE on implementations that don't set the cap D3DPMISCCAPS_SEPARATEALPHABLEND. See D3DPMISCCAPS.
//The type of separate alpha blending is determined by the DISRS_SRCBLENDALPHA and DISRS_DESTBLENDALPHA render states.
		}
		break;
	case DISRS_SRCBLENDALPHA:
		{
			newValue = (D3DBLEND )this->DIS_Blend_Func[ Value ];//to_DIS.BlendType( D3DBLEND(Value));
//One member of the D3DBLEND enumerated type. This Value is ignored unless DISRS_SEPARATEALPHABLENDENABLE is TRUE. The default Value is D3DBLEND_ONE.
		}
		break;
	case DISRS_DESTBLENDALPHA:
		{
			newValue = (D3DBLEND )this->DIS_Blend_Func[ Value ];
//One member of the D3DBLEND enumerated type. This Value is ignored unless DISRS_SEPARATEALPHABLENDENABLE is TRUE. The default Value is D3DBLEND_ZERO.
		}
		break;
	case DISRS_BLENDOPALPHA:
		{
			newValue = (D3DBLEND )this->DIS_Blend_Func[ Value ];
//Value used to select the arithmetic operation applied to separate alpha blending when the render state, DISRS_SEPARATEALPHABLENDENABLE, is set to TRUE.
//Valid Values are defined by the D3DBLENDOP enumerated type. The default Value is D3DBLENDOP_ADD.
//If the D3DPMISCCAPS_BLENDOP device capability is not supported, then D3DBLENDOP_ADD is performed. See D3DPMISCCAPS.
		}
		break;
	
	default: newValue = Value;
	};


	HRESULT hr = pD3DDevice->SetRenderState(d3dState, newValue);
	
	return HR_to_DR( hr );
#endif 
	//SLOW_MODE
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetRenderTarget( //Sets a new color buffer for the device.
	UInt32 RenderTargetIndex,//[in]  Index of the render target. See Remarks.
	LPSURFACE2D pRenderTarget // [in]  Pointer to a new color buffer. If NULL, the color buffer for the corresponding RenderTargetIndex is disabled. Devices always must be associated with a color buffer. The new render-target surface must have at least DIS_USAGE_RENDERTARGET specified.
	)
{
	if( pRenderTarget == NULL )
	{
		HRESULT hr = pD3DDevice->SetRenderTarget(
			RenderTargetIndex,
			0);
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->SetRenderTarget(
								RenderTargetIndex, 
								LPSURFACE2D_D3D9(pRenderTarget)->pd3dSurface);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetSamplerState( //Sets the sampler state value.
	UInt32 Sampler,//[in]  The sampler stage index. For more info about sampler stage, see Sampling Stage Registers in vs_3_0 (DirectX HLSL).
	DIS_SAMPLERSTATETYPE Type,//[in]  This parameter can be any member of the D3DSAMPLERSTATETYPE enumerated type.
	UInt32 Value//[in]  State value to set. The meaning of this value is determined by the Type parameter.
	)
{
	D3DSAMPLERSTATETYPE d3dType = D3DSAMPLERSTATETYPE(DIS_SampleStateType[ Type ]);
	DWORD newValue;
	
	switch(Type)
	{
	case DIS_SAMP_ADDRESSU:
		{
			newValue = (D3DTEXTUREADDRESS )this->DIS_TextureAddress[ Value ];//to_DIS.dTextureAddress( D3DTEXTUREADDRESS( value ));
//Texture-address mode for the u coordinate. The default is D3DTADDRESS_WRAP. For more information, see D3DTEXTUREADDRESS.
		}
		break;
	case DIS_SAMP_ADDRESSV:
		{
			newValue = (D3DTEXTUREADDRESS )this->DIS_TextureAddress[ Value ];//
//Texture-address mode for the v coordinate. The default is D3DTADDRESS_WRAP. For more information, see D3DTEXTUREADDRESS.
		}
		break;
	case DIS_SAMP_ADDRESSW:
		{
			newValue = (D3DTEXTUREADDRESS )this->DIS_TextureAddress[ Value ];
//Texture-address mode for the w coordinate. The default is D3DTADDRESS_WRAP. For more information, see D3DTEXTUREADDRESS.
		}
		break;
	case DIS_SAMP_BORDERCOLOR:
		{
			newValue = Value;
//Border color or type D3DCOLOR. The default color is 0x00000000.
		}
		break;
	case DIS_SAMP_MAGFILTER:
		{
			newValue = (D3DTEXTUREFILTERTYPE )this->DIS_TextureFilterType[ Value ];//to_DIS.dTextureFilter( D3DTEXTUREFILTERTYPE( value ));
//Magnification filter of type D3DTEXTUREFILTERTYPE. The default value is D3DTEXF_POINT.
		}
		break;
	case DIS_SAMP_MINFILTER:
		{
			newValue = (D3DTEXTUREFILTERTYPE )this->DIS_TextureFilterType[ Value ];
//Minification filter of type D3DTEXTUREFILTERTYPE. The default value is D3DTEXF_POINT.
		}
		break;
	case DIS_SAMP_MIPFILTER:
		{
			newValue = (D3DTEXTUREFILTERTYPE )this->DIS_TextureFilterType[ Value ];
//Mipmap filter to use during minification. See D3DTEXTUREFILTERTYPE. The default value is D3DTEXF_NONE.
		}
		break;
	case DIS_SAMP_MIPMAPLODBIAS:
		{
			newValue = Value;
//Mipmap level-of-detail bias. The default value is zero.
		}
		break;
	case DIS_SAMP_MAXMIPLEVEL:
		{
		newValue = Value;
//level-of-detail index of largest map to use. Values range from 0 to (n - 1) where 0 is the largest. The default value is zero.
		}
		break;
	case DIS_SAMP_MAXANISOTROPY:
		{
			newValue = Value;
//DWORD maximum anisotropy. Values range from 1 to the value that is specified in the MaxAnisotropy member of the D3DCAPS9 structure. The default value is 1.
		}
		break;	
	case DIS_SAMP_SRGBTEXTURE:
		{
			newValue = Value;
//Gamma correction value. The default value is 0, which means gamma is 1.0 and no correction is required. Otherwise, this value means that the sampler should assume gamma of 2.2 on the content and convert it to linear (gamma 1.0) before presenting it to the pixel shader.
		}
		break;	
	case DIS_SAMP_ELEMENTINDEX:
		{
			newValue = Value;
//When a multielement texture is assigned to the sampler, this indicates which element index to use. The default value is 0.
		}
		break;
	case DIS_SAMP_DMAPOFFSET:
		{
			newValue = Value;
//Vertex offset in the presampled displacement map. This is a constant used by the tessellator, its default value is 0.
		}
		break;

	default: newValue = Value; break;

	};

	HRESULT hr = pD3DDevice->SetSamplerState(Sampler, d3dType, newValue);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetScissorRect( //Sets the scissor rectangle.
	const DIS_Rect *pRect	// [in]  
	)
{
	RECT rect;

	rect.left = pRect->x1;
	rect.right = pRect->x2;
	rect.top = pRect->y1;
	rect.bottom = pRect->y2;

	HRESULT hr = pD3DDevice->SetScissorRect(&rect);
	
	return HR_to_DR( hr );

}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetSoftwareVertexProcessing( //Use this method to switch between software and hardware vertex processing.
	bool bSoftware
	)
{

	HRESULT hr = pD3DDevice->SetSoftwareVertexProcessing(bSoftware);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetStreamSource( //Binds a vertex buffer to a device data stream. For more information, see Setting the Stream Source (Direct3D 9).
	UInt32 StreamNumber,//[in]  Specifies the data stream, in the range from 0 to the maximum number of streams -1.
	LPVERTEXBUFFER pStreamData,//[in]  Pointer to an LPVERTEXBUFFER interface, representing the vertex buffer to bind to the specified data stream.
	UInt32 OffsetInBytes,//[in]  Offset from the beginning of the stream to the beginning of the vertex data, in bytes. To find out if the device supports stream offsets, see the D3DDEVCAPS2_STREAMOFFSET constant in D3DDEVCAPS2.
	UInt32 Stride//[in]  Stride of the component, in bytes. See Remarks.
	)
{
	if( pStreamData == NULL )
	{
		return DIS_FAIL;
	}

	LPVERTEXBUFFER_D3D9 pvBd3d9 = (LPVERTEXBUFFER_D3D9)pStreamData;

	HRESULT hr = pD3DDevice->SetStreamSource(
								StreamNumber, 
								pvBd3d9->pd3dVertexBuffer,
								OffsetInBytes, 
								Stride);
	
	return HR_to_DR( hr );

//	return DIS_OK;
}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
//There are two constants defined in d3d9types.h that are designed to use with SetStreamSourceFreq: 
//D3DSTREAMSOURCE_INDEXEDDATA and D3DSTREAMSOURCE_INSTANCEDATA. To see how to use the constants, see Efficiently Drawing Multiple Instances of Geometry (Direct3D 9).
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetStreamSourceFreq( //Sets the stream source frequency divider value. This may be used to draw several instances of geometry.
	UInt32 StreamNumber,//[in]  Stream source number.
	UInt32 FrequencyParameter//[in]  This parameter may have two different values. See remarks.
	)
{

	HRESULT hr = pD3DDevice->SetStreamSourceFreq(StreamNumber, FrequencyParameter);
	
	return HR_to_DR( hr );

//	return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
/*
Programmable shaders reference textures using the sampler number. 
The number of samplers available to a programmable shader is dependent on the shader version. 
For vertex shaders, see Sampler (Direct3D 9 asm-vs). 
For pixel shaders see Sampler (Direct3D 9 asm-ps).
The fixed function pipeline on the other hand, references textures by texture stage number. 
The maximum number of samplers is determined from two caps: 
MaxSimultaneousTextures and MaxTextureBlendStages of the D3DCAPS9 structure.
There are two other special cases for stage/sampler numbers.
A special number called D3DDMAPSAMPLER is used for Displacement Mapping (Direct3D 9).
A programmable vertex shader uses a special number defined by a 
D3DVERTEXTEXTURESAMPLER 
when accessing Vertex Textures in vs_3_0 (DirectX HLSL).
*/
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetTexture( //Assigns a texture to a stage for a device.
	UInt32 Sampler,//[in]  Zero based sampler number. Textures are bound to samplers; samplers define sampling state such as the filtering mode and the address wrapping mode. Textures are referenced differently by the programmable and the fixed function pipeline:
	LPBASETEXTURE pTexture // [in]  Pointer to an LPBASETEXTURE interface, representing the texture being set.
	)
{
	if( pTexture == NULL )
	{
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->SetTexture(
								Sampler, 
								LPTEXTURE2D_D3D9(pTexture)->pd3dTexture);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetTextureStageState( //Sets the state value for the currently assigned texture.
	UInt32 Stage, //[in]Stage identifier of the texture for which the state value is set. Stage identifiers are zero-based. Devices can have up to eight set textures, so the maximum value allowed for Stage is 7.
	DIS_TEXTURESTAGESTATETYPE Type, //[in]Texture state to set. This parameter can be any member of the D3DTEXTURESTAGESTATETYPE enumerated type.
	UInt32 Value // [in]State value to set. The meaning of this value is determined by the Type parameter.
	)
{
	D3DTEXTURESTAGESTATETYPE d3dType = (D3DTEXTURESTAGESTATETYPE)DIS_TextureStageStateType[ Type ];
	DWORD newValue;

	switch( Type )
	 {
	case DIS_TSS_COLOROP:
		{
			newValue = this->DIS_TextureOp[ Value ];//to_DIS.dTextureOp( D3DTEXTUREOP(Value) );
//Texture-stage state is a texture color blending operation identified by one member of the D3DTEXTUREOP enumerated type. The default Value for the first texture stage (stage 0) is D3DTOP_MODULATE; for all other stages the default is D3DTOP_DISABLE.
		}
		break;
	case DIS_TSS_COLORARG1:
		{
			newValue = Value;
//			newValue = this->DIS_TextureAddress[ Value ];//to_DIS.dTextureAddress( D3DTEXTUREADDRESS(Value) );
//Texture-stage state is the first color argument for the stage, identified by one of the D3DTA. The default argument is D3DTA_TEXTURE.
//Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default Value for the register is (0.0, 0.0, 0.0, 0.0).
		}
		break;
	case DIS_TSS_COLORARG2:
		{
			newValue = Value;
//			newValue = this->DIS_TextureAddress[ Value ];//to_DIS.dTextureAddress( D3DTEXTUREADDRESS(Value) );
//Texture-stage state is the second color argument for the stage, identified by D3DTA. The default argument is D3DTA_CURRENT. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default Value for the register is (0.0, 0.0, 0.0, 0.0)
		}
		break;
	
	case DIS_TSS_ALPHAOP:
		{
			newValue = this->DIS_TextureOp[ Value ];//to_DIS.dTextureOp( D3DTEXTUREOP(Value) );
//Texture-stage state is a texture alpha blending operation identified by one member of the D3DTEXTUREOP enumerated type. The default Value for the first texture stage (stage 0) is D3DTOP_SELECTARG1, and for all other stages the default is D3DTOP_DISABLE.
		}
		break;

	case DIS_TSS_ALPHAARG1:
		{
			newValue = Value;
			//newValue = this->DIS_TextureAddress[ Value ];
//Texture-stage state is the first alpha argument for the stage, identified by by D3DTA. The default argument is D3DTA_TEXTURE. If no texture is set for this stage, the default argument is D3DTA_DIFFUSE. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default Value for the register is (0.0, 0.0, 0.0, 0.0).
		}
		break;

	case DIS_TSS_ALPHAARG2:
		{
			newValue = Value;
			//newValue = this->DIS_TextureAddress[ Value ];
//Texture-stage state is the second alpha argument for the stage, identified by by D3DTA. The default argument is D3DTA_CURRENT. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default Value for the register is (0.0, 0.0, 0.0, 0.0).
		}
		break;
	case DIS_TSS_BUMPENVMAT00:
		{
			newValue = Value;
//Texture-stage state is a floating-point Value for the [0][0] coefficient in a bump-mapping matrix. The default Value is 0.0.
		}
		break;

	case DIS_TSS_BUMPENVMAT01:
		{
			newValue = Value;
//Texture-stage state is a floating-point Value for the [0][1] coefficient in a bump-mapping matrix. The default Value is 0.0.
		}
		break;

	case DIS_TSS_BUMPENVMAT10:
		{
			newValue = Value;
//Texture-stage state is a floating-point Value for the [1][0] coefficient in a bump-mapping matrix. The default Value is 0.0.
		}
		break;

	case DIS_TSS_BUMPENVMAT11:
		{
			newValue = Value;
//Texture-stage state is a floating-point Value for the [1][1] coefficient in a bump-mapping matrix. The default Value is 0.0.
		}
		break;
	case DIS_TSS_TEXCOORDINDEX:
		{
			newValue = Value;
//Index of the texture coordinate set to use with this texture stage. You can specify up to eight sets of texture coordinates per vertex. If a vertex does not include a set of texture coordinates at the specified index, the system defaults to the u and v coordinates (0,0).
//When rendering using vertex shaders, each stage's texture coordinate index must be set to its default Value. The default index for each stage is equal to the stage index. Set this state to the zero-based index of the coordinate set for each vertex that this texture stage uses.
//Additionally, applications can include, as logical OR with the index being set, one of the constants to request that Direct3D automatically generate the input texture coordinates for a texture transformation. For a list of all the constants, see DIS_TSS_TCI.
//With the exception of DIS_TSS_TCI_PASSTHRU, which resolves to zero, if any of the following Values is included with the index being set, the system uses the index strictly to determine texture wrapping mode. These flags are most useful when performing environment mapping.
		}
		break;

	case DIS_TSS_BUMPENVLSCALE:
		{
			newValue = Value;
//Floating-point scale Value for bump-map luminance. The default Value is 0.0.
		}
		break;

	case DIS_TSS_BUMPENVLOFFSET:
		{
			newValue = Value;
//Floating-point offset Value for bump-map luminance. The default Value is 0.0.
		}
		break;

	case DIS_TSS_TEXTURETRANSFORMFLAGS:
		{
			newValue = Value;
//Member of the D3DTEXTURETRANSFORMFLAGS enumerated type that controls the transformation of texture coordinates for this texture stage. The default Value is D3DTTFF_DISABLE.
		}
		break;

	case DIS_TSS_COLORARG0:
		{
			newValue = Value;
			//newValue = this->DIS_TextureAddress[ Value ];
//Settings for the third color operand for triadic operations (multiply, add, and linearly interpolate), identified by D3DTA. This setting is supported if the D3DTEXOPCAPS_MULTIPLYADD or D3DTEXOPCAPS_LERP device capabilities are present. The default argument is D3DTA_CURRENT. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default Value for the register is (0.0, 0.0, 0.0, 0.0).
		}
		break;

	case DIS_TSS_ALPHAARG0:
		{
			newValue = Value; 
			//newValue = this->DIS_TextureAddress[ Value ];
//Settings for the alpha channel selector operand for triadic operations (multiply, add, and linearly interpolate), identified by D3DTA. This setting is supported if the D3DTEXOPCAPS_MULTIPLYADD or D3DTEXOPCAPS_LERP device capabilities are present. The default argument is D3DTA_CURRENT. Specify D3DTA_TEMP to select a temporary register color for read or write. D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present. The default argument is (0.0, 0.0, 0.0, 0.0).
		}
		break;
	case DIS_TSS_RESULTARG:
		{
			newValue = this->DIS_TextureAddress[ Value ];
//Setting to select destination register for the result of this stage, identified by D3DTA. This Value can be set to D3DTA_CURRENT (the default Value) or to D3DTA_TEMP, which is a single temporary register that can be read into subsequent stages as an input argument. The final color passed to the fog blender and frame buffer is taken from D3DTA_CURRENT, so the last active texture stage state must be set to write to current. This setting is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is present.
		}
		break;
	case DIS_TSS_CONSTANT:
		{
			newValue = (Value) ;
//Per-stage constant color. To see if a device supports a per-stage constant color, see the D3DPMISCCAPS_PERSTAGECONSTANT constant in D3DPMISCCAPS. DIS_TSS_CONSTANT is used by D3DTA_CONSTANT. See D3DTA.
		}
		break;
	
	default: newValue=Value;break;
	}

	HRESULT hr = pD3DDevice->SetTextureStageState(Stage, d3dType, newValue);
	
	return HR_to_DR( hr );
}

	

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetTransform( //Sets a single device transformation-related state.
	DIS_TRANSFORMSTATETYPE State, //[in]  Device-state variable that is being modified. This parameter can be any member of the D3DTRANSFORMSTATETYPE enumerated type, or the D3DTS_WORLDMATRIX macro.
	const DIS_MATRIX *pMatrix // [in]  
	)
{
	D3DMATRIX mat;
	Copy_DIS_MATRIX_To_D3DMATRIX( *pMatrix, mat );

	HRESULT hr = pD3DDevice->SetTransform( 
								D3DTRANSFORMSTATETYPE(this->DIS_TransformStateType[ State ]), 
								&mat);
	
	return HR_to_DR( hr );
}

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetTransformf( //Sets a single device transformation-related state.
	DIS_TRANSFORMSTATETYPE State, //[in]  Device-state variable that is being modified. This parameter can be any member of the D3DTRANSFORMSTATETYPE enumerated type, or the D3DTS_WORLDMATRIX macro.
	const float *pMatrix // [in]  
	)
{
	HRESULT hr = pD3DDevice->SetTransform( 
								D3DTRANSFORMSTATETYPE(this->DIS_TransformStateType[ State ]), 
								( D3DMATRIX* )pMatrix);
	
	return HR_to_DR( hr );
}

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------		
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetVertexDeclaration( //Sets a Vertex Declaration (Direct3D 9).
	LPVERTEXDECLERATION pDecl //[in]Pointer to an LPVERTEXDECLERATION object, which contains the vertex declaration.
	)
{
	if( pDecl == NULL )
	{
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->SetVertexDeclaration(
								LPVERTEXDECLERATION_D3D9(pDecl)->pd3dVertexDecl);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetVertexShader( //Sets the vertex shader.
	LPVERTEXSHADER pShader //[in]Vertex shader interface. For more information, see LPVERTEXSHADER.
	)
{
	if( pShader == NULL )
	{
		return DIS_FAIL;
	}

	HRESULT hr = pD3DDevice->SetVertexShader(
								LPVERTEXSHADER_D3D9(pShader)->pd3dVertexShader);
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetVertexShaderConstantB( //Sets a Boolean vertex shader constant.
	UInt32 StartRegister, // [in]Register number that will contain the first constant value.
	const bool *pConstantData, // [in]Pointer to an array of constants.
	UInt32 BoolCount // [in]Number of boolean values in the array of constants.
	)
{

	HRESULT hr = pD3DDevice->SetVertexShaderConstantB(StartRegister,
													(const BOOL*) pConstantData,
														BoolCount);
	
	return HR_to_DR( hr );


}



//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetVertexShaderConstantF( //Sets a floating-point vertex shader constant.
	UInt32 StartRegister, //[in] Register number that will contain the first constant value.
	const float *pConstantData,//[in] Pointer to an array of constants.
	UInt32 Vector4fCount //[in] Number of four float vectors in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->SetVertexShaderConstantF(StartRegister,
														pConstantData,
														Vector4fCount);
	
	return HR_to_DR( hr );
}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetVertexShaderConstantI( //Sets an integer vertex shader constant.
	UInt32 StartRegister,//[in]  Register number that will contain the first constant value.
	const int *pConstantData,//[in]  Pointer to an array of constants.
	UInt32 Vector4iCount //[in]  Number of four integer vectors in the array of constants.
	)
{
	HRESULT hr = pD3DDevice->SetVertexShaderConstantI(StartRegister,
														pConstantData,
														Vector4iCount);
	
	return HR_to_DR( hr );
}

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::SetViewport( //Sets the viewport parameters for the device.
	const DIS_VIEWPORT *pViewport // [in] Pointer to a DIS_VIEWPORT structure, specifying the viewport parameters to set. 
	)
{
	D3DVIEWPORT9 vp;

	vp.Height = pViewport->Height;
	vp.MaxZ = pViewport->MaxZ;
	vp.MinZ = pViewport->MinZ;
	vp.Width = pViewport->Width;
	vp.X = pViewport->X;
	vp.Y = pViewport->Y;

	HRESULT hr = pD3DDevice->SetViewport(&vp);
	
	return HR_to_DR( hr );

//	return DIS_OK;
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE bool D3D_DeviceInterface::ShowCursor( bool bShow ) //Displays or hides the cursor.
{

	HRESULT hr = pD3DDevice->ShowCursor(bShow);
	
	return HR_to_DR( hr );

//	return pD3DDevice->ShowCursor(bShow);
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::StretchRect( //Copy the contents of the source rectangle to the destination rectangle. The source rectangle can be stretched and filtered by the copy. This function is often used to change the aspect ratio of a video stream.
	LPSURFACE2D *pSourceSurface,//[in]  Pointer to the source surface. See LPSURFACE2D.
	const DIS_Rect *pSourceRect,//[in]  Pointer to the source rectangle. A NULL for this parameter causes the entire source surface to be used.
	LPSURFACE2D *pDestSurface,//[in]  Pointer to the destination surface. See IDirect3DSurface9.
	const DIS_Rect *pDestRect,//[in]  Pointer to the destination rectangle. A NULL for this parameter causes the entire destination surface to be used.
	DIS_TEXTUREFILTERTYPE Filter//[in]  Filter type. Allowable values are D3DTEXF_NONE, D3DTEXF_POINT, or D3DTEXF_LINEAR. For more information, see
	)
{
	if( *pSourceSurface == NULL )
	{
		return DIS_FAIL;
	}

	if( *pDestSurface == NULL )
	{
		return DIS_FAIL;
	}

	D3DTEXTUREFILTERTYPE d3dFilter = (D3DTEXTUREFILTERTYPE)this->DIS_TextureFilterType[ Filter ];

	HRESULT hr;

	if( (pSourceRect == NULL) && !(pDestRect == NULL))
	{
		RECT dest;
		dest.left = pDestRect->x1;
		dest.right = pDestRect->x2;
		dest.top = pDestRect->y1;
		dest.bottom = pDestRect->y2;

		hr = pD3DDevice->StretchRect(
							LPSURFACE2D_D3D9(pSourceSurface)->pd3dSurface, 
							NULL, 
							LPSURFACE2D_D3D9(pDestSurface)->pd3dSurface, 
							&dest, 
							d3dFilter );
	}
	else if( !(pSourceRect == NULL) && (pDestRect == NULL) )
	{
		RECT source;
		source.left = pSourceRect->x1;
		source.right = pSourceRect->x2;
		source.top = pSourceRect->y1;
		source.bottom = pSourceRect->y2;

		hr = pD3DDevice->StretchRect(
							LPSURFACE2D_D3D9(pSourceSurface)->pd3dSurface, 
							&source, 
							LPSURFACE2D_D3D9(pDestSurface)->pd3dSurface, 
							NULL, 
							d3dFilter );
	}
	else if( (pSourceRect == NULL) && (pDestRect == NULL) )
	{
		hr = pD3DDevice->StretchRect(
							LPSURFACE2D_D3D9(pSourceSurface)->pd3dSurface, 
							NULL, 
							LPSURFACE2D_D3D9(pDestSurface)->pd3dSurface, 
							NULL, 
							d3dFilter );
	}
	else
	{
		RECT source;
		source.left = pSourceRect->x1;
		source.right = pSourceRect->x2;
		source.top = pSourceRect->y1;
		source.bottom = pSourceRect->y2;

		RECT dest;
		dest.left = pDestRect->x1;
		dest.right = pDestRect->x2;
		dest.top = pDestRect->y1;
		dest.bottom = pDestRect->y2;

		hr = pD3DDevice->StretchRect(
							LPSURFACE2D_D3D9(pSourceSurface)->pd3dSurface, 
							&source, 
							LPSURFACE2D_D3D9(pDestSurface)->pd3dSurface, 
							&dest, 
							d3dFilter );
	}


	
	return HR_to_DR( hr );

//	return DIS_OK;
}



//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::TestCooperativeLevel() //Reports the current cooperative-level status of the Direct3D device for a windowed or full-screen application.
{
	HRESULT hr = pD3DDevice->TestCooperativeLevel();
	
	return HR_to_DR( hr );
}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::UpdateSurface( //Copies rectangular subsets of pixels from one surface to another.
	LPSURFACE2D pSourceSurface,//[in]  Pointer to an LPSURFACE2D interface, representing the source surface. This parameter must point to a different surface than pDestinationSurface.
	const DIS_Rect *pSourceRect,//[in]  Pointer to a rectangle on the source surface. Specifying NULL for this parameter causes the entire surface to be copied.
	LPSURFACE2D *pDestinationSurface,//[in]  Pointer to an LPSURFACE2D interface, representing the destination surface.
	const DIS_POINT *pDestinationPoint//[in]  Pointer to the upper left corner of the destination rectangle. Specifying NULL for this parameter causes the entire surface to be copied.
	)
{
	if( pSourceSurface == NULL )
	{
		return DIS_FAIL;
	}

	if( pDestinationSurface == NULL )
	{
		return DIS_FAIL;
	}

	HRESULT hr;

	if( (pSourceRect == NULL) || (pDestinationPoint == NULL) )
	{
		hr = pD3DDevice->UpdateSurface(
							LPSURFACE2D_D3D9(pSourceSurface)->pd3dSurface, 
							NULL, 
							LPSURFACE2D_D3D9(pDestinationSurface)->pd3dSurface, 
							NULL );
	}
	else
	{
		RECT source;
		source.left = pSourceRect->x1;
		source.right = pSourceRect->x2;
		source.top = pSourceRect->y1;
		source.bottom = pSourceRect->y2;

		POINT destp;
		destp.x = pDestinationPoint->X;
		destp.y = pDestinationPoint->Y;
		

		hr = pD3DDevice->UpdateSurface(
							LPSURFACE2D_D3D9(pSourceSurface)->pd3dSurface, 
							&source, 
							LPSURFACE2D_D3D9(pDestinationSurface)->pd3dSurface, 
							&destp );
	}

	return HR_to_DR( hr );
}
		

//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::UpdateTexture( //Updates the dirty portions of a texture.
	LPBASETEXTURE pSourceTexture,//[in]Pointer to an IDirect3DBaseTexture9 interface, representing the source texture. The source texture must be in system memory (D3DPOOL_SYSTEMMEM).
	LPBASETEXTURE pDestinationTexture // [in]Pointer to an IDirect3DBaseTexture9 interface, representing the destination texture. The destination texture must be in the D3DPOOL_DEFAULT memory pool.
	)
{
	if( pSourceTexture == NULL )
	{
		return DIS_FAIL;
	}

	if( pDestinationTexture == NULL )
	{
		return DIS_FAIL;
	}



	HRESULT hr = pD3DDevice->UpdateTexture(
								LPTEXTURE2D_D3D9(pSourceTexture)->pd3dTexture,
								LPTEXTURE2D_D3D9(pDestinationTexture)->pd3dTexture);
	
	return HR_to_DR( hr );


}


//-------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------
DIS_INLINE DIS_RESULT D3D_DeviceInterface::ValidateDevice( //Reports the device's ability to render the current texture-blending operations and arguments in a single pass.
	UInt32 *pNumPasses // [out, retval]  Pointer to a DWORD value to fill with the number of rendering passes needed to complete the desired effect through multipass rendering.
	)
{
	HRESULT hr = pD3DDevice->ValidateDevice((DWORD*)pNumPasses);
	
	return HR_to_DR( hr );

}
