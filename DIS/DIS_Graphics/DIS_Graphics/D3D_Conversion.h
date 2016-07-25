#ifndef D3D_CONVERSIONS_H
#define D3D_CONVERSIONS_H

#include "DIS_RenderStates.h"
#include <d3d9.h>

DIS_RESULT HR_to_DR( HRESULT r );

void Copy_D3DMATRIX_To_DIS_MATRIX( const D3DMATRIX &in, DIS_MATRIX &out );
void Copy_DIS_MATRIX_To_D3DMATRIX( const DIS_MATRIX &in,  D3DMATRIX &out );

LPDIRECT3DDEVICE9* GetDeviceD3D();

class DIS_D3DConversion
{
public:
	DIS_D3DConversion();
	~DIS_D3DConversion();

	DIS_BACKBUFFER_TYPE			D3DtoDIS_BackBuffer[3];
	DIS_BASISTYPE				D3DtoDIS_BasisType[3];
	DIS_BLEND					D3DtoDIS_BlendType[18];
	DIS_BLENDOP					D3DtoDIS_BlendOp[6];
	DIS_CMPFUNC					D3DtoDIS_CmpFunc[9];
	DIS_COMPOSERECTSOP			D3DtoDIS_ComposerOp[5];
	DIS_CUBEMAP_FACES			D3DtoDIS_CubemapFaces[6];
	DIS_CULL					D3DtoDIS_CullMode[4];
	DIS_DEBUGMONITORTOKENS		D3DtoDIS_DebugMonitorTokens[2];
	DIS_DECLMETHOD				D3DtoDIS_DeclMethod[7];
	DIS_DECLTYPE				D3DtoDIS_DeclType[18];
	DIS_DECLUSAGE				D3DtoDIS_DeclUsage[14];
	DIS_DEGREETYPE				D3DtoDIS_DegreeType[6];
	DIS_DEVTYPE					D3DtoDIS_DevType[5];
	DIS_DISPLAYROTATION			D3DtoDIS_DisplayRotation[5];
	DIS_FILLMODE				D3DtoDIS_FillMode[4];
	DIS_FOGMODE					D3DtoDIS_FogMode[4];
	DIS_FORMAT					D3DtoDIS_Format[200];
	DIS_LIGHTTYPE				D3DtoDIS_LightType[4];
	DIS_MATERIALCOLORSOURCE		D3DtoDIS_MaterialColorSource[3];	
	DIS_MULTISAMPLE_TYPE		D3DtoDIS_MultiSampleType[17];
	DIS_PATCHEDGESTYLE			D3DtoDIS_PatchEdgeStyle[2];
	DIS_POOL					D3DtoDIS_Pool[4];
	DIS_PRIMITIVETYPE			D3DtoDIS_PrimitiveType[7];
	DIS_QUERYTYPE				D3DtoDIS_QueryType[20];
	DIS_RENDERSTATETYPE			D3DtoDIS_RenderstateType[210];
	DIS_RESOURCETYPE			D3DtoDIS_ResourceType[8];
	DIS_SAMPLER_TEXTURE_TYPE	D3DtoDIS_SamplerTextureType[4];
	DIS_SAMPLERSTATETYPE		D3DtoDIS_SamplerStateType[14];
	DIS_SCANLINEORDERING		D3DtoDIS_ScanlineOrdering[3];
	DIS_SHADEMODE				D3DtoDIS_ShadeMode[4];
	DIS_STATEBLOCKTYPE			D3DtoDIS_StateBlockType[4];
	DIS_STENCILOP				D3DtoDIS_StencilOp[9];
	DIS_SWAPEFFECT				D3DtoDIS_SwapEffect[6];
	DIS_TEXTUREADDRESS			D3DtoDIS_TextureAddress[6];
	DIS_TEXTUREFILTERTYPE		D3DtoDIS_TextureFilterType[9];
	DIS_TEXTUREOP				D3DtoDIS_TextureOp[27];
	DIS_TEXTURESTAGESTATETYPE	D3DtoDIS_TextureStageStateType[33];
	DIS_TEXTURETRANSFORMFLAGS	D3DtoDIS_TextureTransformFlags[257];
	DIS_TRANSFORMSTATETYPE		D3DtoDIS_TransformStateType[24];
	DIS_VERTEXBLENDFLAGS		D3DtoDIS_VertexBlendFlags[257];
	DIS_ZBUFFERTYPE				D3DtoDIS_ZBufferType[3];
#ifdef INLINE_CONVERSION
#define INL inline
#else
#define INL
#endif
	INL DIS_BACKBUFFER_TYPE			BackBufferType( D3DBACKBUFFER_TYPE  t );
	INL DIS_BASISTYPE				BasisType( D3DBASISTYPE t );
	INL DIS_BLEND					BlendType( D3DBLEND t );
	INL DIS_BLENDOP					BlendOp( D3DBLENDOP t );
	INL DIS_CMPFUNC					CompareFunc( D3DCMPFUNC t );
	INL DIS_COMPOSERECTSOP			ComposerOp( D3DCOMPOSERECTSOP t );
	INL DIS_CUBEMAP_FACES			CubemapFace( D3DCUBEMAP_FACES t );
	INL DIS_CULL					CullMode( D3DCULL t );
	INL DIS_DEBUGMONITORTOKENS		DebugMonitorToken( D3DDEBUGMONITORTOKENS t );
	INL DIS_DECLMETHOD				DeclMethod( D3DDECLMETHOD t );
	INL DIS_DECLTYPE				DeclType( D3DDECLTYPE t );
	INL DIS_DECLUSAGE				DeclUsage( D3DDECLUSAGE t );
	INL DIS_DEGREETYPE				DegreeType( D3DDEGREETYPE  t );
	INL DIS_DEVTYPE					DeviceType( D3DDEVTYPE t );
	INL DIS_DISPLAYROTATION			DisplayRotation( D3DDISPLAYROTATION t );
	INL UInt32				FillMode( D3DFILLMODE t );
	INL DIS_FOGMODE					FogMode( D3DFOGMODE t );
	INL DIS_FORMAT					dFormat( D3DFORMAT t );
	INL DIS_LIGHTTYPE				LightType( D3DLIGHTTYPE t );
	INL DIS_MATERIALCOLORSOURCE		MaterialColorSource( D3DMATERIALCOLORSOURCE t );
	INL DIS_MULTISAMPLE_TYPE		MultiSampleType( D3DMULTISAMPLE_TYPE t );
	INL DIS_PATCHEDGESTYLE			PatchEdgeStyle( D3DPATCHEDGESTYLE t );
	INL DIS_POOL					dPool( D3DPOOL t );
	INL DIS_PRIMITIVETYPE			dPrimitiveType( D3DPRIMITIVETYPE t );
	INL DIS_QUERYTYPE				dQueryType( D3DQUERYTYPE t );
	INL DIS_RENDERSTATETYPE			RenderState( D3DRENDERSTATETYPE t );
	INL DIS_RESOURCETYPE			ResourceType( D3DRESOURCETYPE t );
	INL DIS_SAMPLER_TEXTURE_TYPE	SampleTextureType( D3DSAMPLER_TEXTURE_TYPE t );
	INL DIS_SAMPLERSTATETYPE		SampleStateType( D3DSAMPLERSTATETYPE t );
	INL DIS_SCANLINEORDERING		ScanlineOrdering( D3DSCANLINEORDERING t );
	INL UInt32				dShadeMode( D3DSHADEMODE t );
	INL DIS_STATEBLOCKTYPE			dStateBlockType( D3DSTATEBLOCKTYPE t );
	INL DIS_STENCILOP				dStencilOp( D3DSTENCILOP t );
	INL DIS_SWAPEFFECT				dSwapEffect( D3DSWAPEFFECT t );
	INL DIS_TEXTUREADDRESS			dTextureAddress( D3DTEXTUREADDRESS t );
	INL DIS_TEXTUREFILTERTYPE		dTextureFilter( D3DTEXTUREFILTERTYPE t );
	INL DIS_TEXTUREOP				dTextureOp( D3DTEXTUREOP t );
	INL DIS_TEXTURESTAGESTATETYPE	dTextureStageState( D3DTEXTURESTAGESTATETYPE t );
	INL DIS_TEXTURETRANSFORMFLAGS	dTextureTransformFlag( D3DTEXTURETRANSFORMFLAGS t );
	INL DIS_TRANSFORMSTATETYPE		dTransformState( D3DTRANSFORMSTATETYPE t );
	INL DIS_VERTEXBLENDFLAGS		dVertexBlendFlags( D3DVERTEXBLENDFLAGS t );
	INL DIS_ZBUFFERTYPE				dZBufferType( D3DZBUFFERTYPE t );
	DIS_USAGE dUsage( int t );
#undef INL 
};

#endif