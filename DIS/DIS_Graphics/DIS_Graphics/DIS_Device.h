#ifndef DIS_DEVICE_H
#define DIS_DEVICE_H

#include "DIS_RenderStates.h"
#include "DIS_ResourceTypes.h"

//#define DERIVE_DEVICES 0


#define MAX_RENDERTARGETS 20
#define MAX_SAMPLERSTATES 32

class DIS_Device
{
public:

	DIS_Device();
	~DIS_Device();
	/*
	DIS_INLINE DIS_RESULT	SetBlendState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetStencilState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetRasterizerState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetValueState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetFillModeState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetShadeModeState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetFixedState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetFogModeState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetPatchDegreeState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetCompareFuncState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetPatchEdgeState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetMaterialColorSourceState( UInt32 A, UInt32 B );
	DIS_INLINE DIS_RESULT	SetVertexBlendState( UInt32 A, UInt32 B );	

	DIS_INLINE DIS_RESULT	GetBlendState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetStencilState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetRasterizerState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetValueState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetFillModeState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetShadeModeState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetFixedState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetFogModeState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetPatchDegreeState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetCompareFuncState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetPatchEdgeState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetMaterialColorSourceState( UInt32 A, UInt32 *B );
	DIS_INLINE DIS_RESULT	GetVertexBlendState( UInt32 A, UInt32 *B );	
	*/
	// Begins a scene.
	DIS_INLINE DIS_RESULT BeginScene();	

	//Signals Direct3D to begin recording a device-state block.
	DIS_INLINE DIS_RESULT BeginStateBlock();	
	
	//Clears one or more surfaces such as a render target, multiple render targets, a stencil buffer, and a depth buffer.
	DIS_INLINE DIS_RESULT Clear(  UInt32 Count,		// [in] Number of rectangles in the array at pRects. Must be set to 0 if pRects is NULL. May not be 0 if pRects is a valid pointer.
		const DIS_Rect *pRects,				// [in] Pointer to an array of DIS_Rect structures that describe the rectangles to clear. Set a rectangle to the dimensions of the rendering target to clear the entire surface. Each rectangle uses screen coordinates that correspond to points on the render target. Coordinates are clipped to the bounds of the viewport rectangle. To indicate that the entire viewport rectangle is to be cleared, set this parameter to NULL and Count to 0.
		UInt32 Flags,						// [in] Combination of one or more DIS_CLEAR flags that specify the surface(s) that will be cleared.
		DIS_COLOR Color,					// [in] Clear a render target to this ARGB color
		float Z,							// [in] Clear the depth buffer to this new z value which ranges from 0 to 1. See remarks.
		UInt32 Stencil);					// [in] Clear the stencil buffer to this new value which ranges from 0 to 2n-1 (n is the bit depth of the stencil buffer). See remarks.

	//Allows an application to fill a rectangular area of a DIS_POOL_DEFAULT surface with a specified color.
	DIS_INLINE DIS_RESULT ColorFill (   LPSURFACE2D pSurface, //[in] Pointer to the surface to be filled.
		const DIS_Rect *pRect,						//[in] Pointer to the source rectangle. Using NULL means that the entire surface will be filled.
		DIS_COLOR color);							//[in] Color used for filling.

	//Creates a cube texture resource.
	DIS_INLINE DIS_RESULT CreateCubeTexture(  UInt32 EdgeLength,	//[in]Size of the edges of all the top-level faces of the cube texture. The pixel dimensions of subsequent levels of each face will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0 (zero), 1 will be taken instead.
		UInt32 Levels,							//[in]Number of levels in each face of the cube texture. If this is zero, DIS_3D will generate all cube texture sublevels down to 1x1 pixels for each face for hardware that supports mipmapped cube textures. Call IDirect3DBaseTexture9::GetLevelCount to see the number of levels generated.
		UInt32 Usage,							//[in] Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants. It is good practice to match the usage parameter in CreateCubeTexture with the behavior flags in IDirect3D9::CreateDevice. For more information, see Remarks.
		DIS_FORMAT Format,						//[in]Member of the D3DFORMAT enumerated type, describing the format of all levels in all faces of the cube texture.
		DIS_POOL Pool,							//[in]Member of the D3DPOOL enumerated type, describing the memory class into which the cube texture should be placed.
		LPCUBETEXTURE2D *ppCubeTexture,			//[out, retval]  Address of a pointer to an IDirect3DCubeTexture9 interface, representing the created cube texture resource.
        DIS_HANDLE *pSharedHandle	);			//[in]Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources.

	//Creates a depth-stencil resource.
	DIS_INLINE DIS_RESULT CreateDepthStencilSurface(
		UInt32 Width,							//[in]       Width of the depth-stencil surface, in pixels.    
		UInt32 Height,							//[in]        Height of the depth-stencil surface, in pixels.   
		DIS_FORMAT Format,						//[in] Member of the D3DFORMAT enumerated type, describing the format of the depth-stencil surface. This value must be one of the enumerated depth-stencil formats for this device.          
		DIS_MULTISAMPLE_TYPE MultiSample,		//[in] Member of the D3DMULTISAMPLE_TYPE enumerated type, describing the multisampling buffer type. This value must be one of the allowed multisample types. When this surface is passed to IDirect3DDevice9::SetDepthStencilSurface, its multisample type must be the same as that of the render target set by IDirect3DDevice9::SetRenderTarget.          
		UInt32 MultisampleQuality,				//[in]Quality level. The valid range is between zero and one less than the level returned by pQualityLevels used by IDirect3D9::CheckDeviceMultiSampleType. Passing a larger value returns the error D3DERR_INVALIDCALL. The MultisampleQuality values of paired render targets, depth stencil surfaces, and the MultiSample type must all match.           
		bool Discard,							//[in] Set this flag to TRUE to enable z-buffer discarding, and FALSE otherwise.	 If this flag is set, the contents of the depth stencil buffer will be invalid after calling either IDirect3DDevice9::Present or IDirect3DDevice9::SetDepthStencilSurface with a different depth surface. This flag has the same behavior as the constant, D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL, in D3DPRESENTFLAG.          
		LPSURFACE2D *ppSurface,					//[out, retval]  Address of a pointer to an IDirect3DSurface9 interface, representing the created depth-stencil surface resource.
		DIS_HANDLE *pSharedHandle				//[in]  Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources.         
		);
	//Creates an index buffer.
	DIS_INLINE DIS_RESULT CreateIndexBuffer(
            UInt32 Length,						//[in]Size of the index buffer, in bytes.
            UInt32 Usage,						//[in]Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants. It is good practice to match the usage parameter in CreateIndexBuffer with the behavior flags in IDirect3D9::CreateDevice. For more information, see Remarks.
            DIS_FORMAT Format,					//[in] Member of the DIS_FORMAT enumerated type, describing the format of the index buffer. For more information, see Remarks. The valid settings are the following: DIS_FMT_INDEX16, DIS_FMT_INDEX32
            DIS_POOL Pool,						//[in] Member of the DIS_POOL enumerated type, describing a valid memory class into which to place the resource.
			LPINDEXBUFFER *ppIndexBuffer,		//[out, retval]Address of a pointer to an IDirect3DIndexBuffer9 interface, representing the created index buffer resource.
            DIS_HANDLE *pSharedHandle			//[in] Reserved. Set this parameter to NULL. This parameter can be used in DIS_3D 9 for Windows Vista to share resources.    
	);

	DIS_INLINE DIS_RESULT CreateOffscreenPlainSurface(//Create an off-screen surface.
            UInt32 Width,						//[in] Width of the surface.
             UInt32 Height,						//[in]Height of the surface.
             DIS_FORMAT Format,					//[in]Format of the surface. See DIS_FORMAT.
             DIS_POOL Pool,						//[in]Member of the DIS_POOL enumerated type, describing a valid memory class into which to place the resource.
			LPSURFACE2D *ppSurface,				// [out, retval] 
            DIS_HANDLE *pSharedHandle			//[in]Reserved. Set this parameter to NULL. This parameter can be used in DIS_3D 9 for Windows Vista to share resources.
	);

	DIS_INLINE DIS_RESULT CreatePixelShader(//Creates a pixel shader.
			const UInt32 *pFunction,				//[in] Pointer to the pixel shader function token array, specifying the blending operations. This value cannot be NULL.
			LPPIXELSHADER *ppShader				// [out, retval]Pointer to the returned pixel shader interface. See LPPIXELSHADER.
	);

	DIS_INLINE DIS_RESULT CreateQuery(//Creates a status query.
            DIS_QUERYTYPE Type,					//[in] Identifies the query type. For more information, see DIS_QUERYTYPE.
			LPQUERY *ppQuery					//[out, retval]Returns a pointer to the query interface that manages the query object. See LPQUERY. This parameter can be set to NULL to see if a query is supported. If the query is not supported, the method returns D3DERR_NOTAVAILABLE.
	);

	DIS_INLINE DIS_RESULT CreateRenderTarget(//Creates a render-target surface.
        UInt32 Width,						//[in] Width of the render-target surface, in pixels.
        UInt32 Height,						//[in] Height of the render-target surface, in pixels.
        DIS_FORMAT Format,					//[in]Member of the D3DFORMAT enumerated type, describing the format of the render target.
        DIS_MULTISAMPLE_TYPE MultiSample,	//[in] Member of the D3DMULTISAMPLE_TYPE enumerated type, which describes the multisampling buffer type. This parameter specifies the antialiasing type for this render target. When this surface is passed to IDirect3DDevice9::SetRenderTarget, its multisample type must be the same as that of the depth-stencil set by IDirect3DDevice9::SetDepthStencilSurface.
        UInt32 MultisampleQuality,			//[in]Quality level. The valid range is between zero and one less than the level returned by pQualityLevels used by IDirect3D9::CheckDeviceMultiSampleType. Passing a larger value returns the error, D3DERR_INVALIDCALL. The MultisampleQuality values of paired render targets, depth stencil surfaces, and the multisample type must all match.
        bool Lockable,						//[in]Render targets are not lockable unless the application specifies TRUE for Lockable. Note that lockable render targets reduce performance on some graphics hardware. The readback performance (moving data from video memory to system memory) depends on the type of hardware used (AGP vs. PCI Express) and is usually far lower than upload performance (moving data from system to video memory). If you need read access to render targets, use GetRenderTargetData instead of lockable render targets.
		LPSURFACE2D *ppSurface,				//[out, retval]Address of a pointer to an LPSURFACE2D interface.
        DIS_HANDLE *pSharedHandle			//[in]Reserved. Set this parameter to NULL. This parameter can be used in DIS_3D 9 for Windows Vista to share resources.
	);

	DIS_INLINE DIS_RESULT CreateStateBlock(//Creates a new state block that contains the values for all device states, vertex-related states, or pixel-related states.
		DIS_STATEBLOCKTYPE Type,			//[in] Type of state data that the method should capture. This parameter can be set to a value defined in the D3DSTATEBLOCKTYPE enumerated type.
		LPSTATEBLOCK  *ppSB					//[out, retval]Pointer to a state block interface. See IDirect3DStateBlock9.
	);	
		
	DIS_INLINE DIS_RESULT CreateTexture(//Creates a texture resource.
		UInt32 Width,						//[in]   Width of the top-level of the texture, in pixels. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0, 1 will be taken instead.       
		UInt32 Height,						//[in]  Height of the top-level of the texture, in pixels. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0, 1 will be taken instead.        
		UInt32 Levels,						//[in]  Number of levels in the texture. If this is zero, Direct3D will generate all texture sublevels down to 1 by 1 pixels for hardware that supports mipmapped textures. Call IDirect3DBaseTexture9::GetLevelCount to see the number of levels generated.         
		UInt32 Usage,						//[in]    Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants. It is good practice to match the usage parameter with the behavior flags in IDirect3D9::CreateDevice.      
		DIS_FORMAT Format,						//[in]     Member of the D3DFORMAT enumerated type, describing the format of all levels in the texture.      
		DIS_POOL Pool,						//[in]  Member of the D3DPOOL enumerated type, describing the memory class into which the texture should be placed.        
		LPTEXTURE2D *ppTexture,				//[out, retval] Pointer to an IDirect3DTexture9 interface, representing the created texture resource. 
		DIS_HANDLE *pSharedHandle			//[in]  Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources. 
	);
	DIS_INLINE DIS_RESULT CreateVertexBuffer(	//Creates a vertex buffer.
		UInt32 Length,						//[in] Size of the vertex buffer, in bytes. For FVF vertex buffers, Length must be large enough to contain at least one vertex, but it need not be a multiple of the vertex size. Length is not validated for non-FVF buffers. See Remarks.
		UInt32 Usage,						//[in] Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants. It is good practice to match the usage parameter in CreateVertexBuffer with the behavior flags in IDirect3D9::CreateDevice. For more information, see Remarks.
		UInt32 FVF,							//[in] Combination of D3DFVF, a usage specifier that describes the vertex format of the vertices in this buffer. If this parameter is set to a valid FVF code, the created vertex buffer is an FVF vertex buffer (see Remarks). Otherwise, if this parameter is set to zero, the vertex buffer is a non-FVF vertex buffer.
		DIS_POOL Pool,						//[in]Member of the D3DPOOL enumerated type, describing a valid memory class into which to place the resource. Do not set to D3DPOOL_SCRATCH.
		LPVERTEXBUFFER *ppVertexBuffer,	//[out, retval] Address of a pointer to an IDirect3DVertexBuffer9 interface, representing the created vertex buffer resource.
		DIS_HANDLE *pSharedHandle			//[in]  Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources.
	);

	DIS_INLINE DIS_RESULT CreateVertexDeclaration(//Create a vertex shader declaration from the device and the vertex elements.
        const DIS_VERTEXELEMENT *pVertexElements,//[in] If the method succeeds, the return value is D3D_OK. If the method fails, the return value can be D3DERR_INVALIDCALL
		LPVERTEXDECLERATION *ppDecl //[out, retval]See the Vertex Declaration (Direct3D 9) page for a detailed description of how to map vertex declarations between different versions of DirectX.
	);

	DIS_INLINE DIS_RESULT CreateVertexShader(//Creates a vertex shader.
		const UInt32 *pFunction,//[in] Pointer to an array of tokens that represents the vertex shader, including any embedded debug and symbol table information.
									//Use a function such as D3DXCompileShader to create the array from a HLSL shader.
									//Use a function like D3DXAssembleShader to create the token array from an assembly language shader.
									//Use a function like ID3DXEffectCompiler::CompileShader to create the array from an effect.
		LPVERTEXSHADER *ppShader//[out, retval]Pointer to the returned vertex shader interface (see LPVERTEXSHADER).
	);

	DIS_INLINE DIS_RESULT CreateVolumeTexture(	//Creates a volume texture resource.
		UInt32 Width,					//[in] Width of the top-level of the volume texture, in pixels. This value must be a power of two if the D3DPTEXTURECAPS_VOLUMEMAP_POW2 member of D3DCAPS9 is set. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by two results in 0 (zero), 1 will be taken instead. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
		UInt32 Height,					//[in]Height of the top-level of the volume texture, in pixels. This value must be a power of two if the D3DPTEXTURECAPS_VOLUMEMAP_POW2 member of D3DCAPS9 is set. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0 (zero), 1 will be taken instead. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9
		UInt32 Depth,					//[in]Depth of the top-level of the volume texture, in pixels. This value must be a power of two if the D3DPTEXTURECAPS_VOLUMEMAP_POW2 member of D3DCAPS9 is set. The pixel dimensions of subsequent levels will be the truncated value of half of the previous level's pixel dimension (independently). Each dimension clamps at a size of 1 pixel. Thus, if the division by 2 results in 0 (zero), 1 will be taken instead. The maximum dimension that a driver supports (for width, height, and depth) can be found in MaxVolumeExtent in D3DCAPS9.
		UInt32 Levels,					//[in] Number of levels in the texture. If this is zero, Direct3D will generate all texture sublevels down to 1x1 pixels for hardware that supports mipmapped volume textures. Call IDirect3DBaseTexture9::GetLevelCount to see the number of levels generated.
		UInt32 Usage,					//[in]Usage can be 0, which indicates no usage value. If usage is desired, use D3DUSAGE_DYNAMIC or D3DUSAGE_SOFTWAREPROCESSING. For more information, see D3DUSAGE.
		DIS_FORMAT Format,					//[in] Member of the D3DFORMAT enumerated type, describing the format of all levels in the volume texture.
		DIS_POOL Pool,						//[in]Member of the D3DPOOL enumerated type, describing the memory class into which the volume texture should be placed.
		LPVOLUMETEXTURE *ppVolumeTexture,	//[out, retval]Address of a pointer to an IDirect3DVolumeTexture9 interface, representing the created volume texture resource.
		DIS_HANDLE *pSharedHandle			//[in]Reserved. Set this parameter to NULL. This parameter can be used in Direct3D 9 for Windows Vista to share resources.
	);
	
	DIS_INLINE DIS_RESULT DeletePatch( UInt32 Handle);// [in]//Frees a cached high-order patch.
	
	DIS_INLINE DIS_RESULT DrawIndexedPrimitive(//Based on indexing, renders the specified geometric primitive into an array of vertices.
		DIS_PRIMITIVETYPE Type,		//[in] Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render. D3DPT_POINTLIST is not supported with this method. See Remarks.
		UInt32 BaseVertexIndex,		//[in]Offset from the start of the vertex buffer to the first vertex. See Scenario 4.
		UInt32 MinIndex,			//[in] Minimum vertex index for vertices used during this call. This is a zero based index relative to BaseVertexIndex.
		UInt32 NumVertices,			//[in]Number of vertices used during this call. The first vertex is located at index: BaseVertexIndex + MinIndex.
		UInt32 StartIndex,			//[in]Index of the first index to use when accesssing the vertex buffer. Beginning at StartIndex to index vertices from the vertex buffer.
		UInt32 PrimitiveCount			//[in] Number of primitives to render. The number of vertices used is a function of the primitive count and the primitive type. The maximum number of primitives allowed is determined by checking the MaxPrimitiveCount member of the D3DCAPS9 structure.
	);	
		
	DIS_INLINE DIS_RESULT DrawIndexedPrimitiveUP(//Renders the specified geometric primitive with data specified by a user memory pointer.
		DIS_PRIMITIVETYPE PrimitiveType,		//[in] Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render.
		UInt32 MinVertexIndex,					//[in] Minimum vertex index. This is a zero-based index.
		UInt32 NumVertices,						//[in] Number of vertices used during this call. The first vertex is located at index: MinVertexIndex.
		UInt32 PrimitiveCount,					//[in] Number of primitives to render. The maximum number of primitives allowed is determined by checking the MaxPrimitiveCount member of the D3DCAPS9 structure (the number of indices is a function of the primitive count and the primitive type).
		const void *pIndexData,					//[in] User memory pointer to the index data.
		DIS_FORMAT IndexDataFormat,				//[in] Member of the D3DFORMAT enumerated type, describing the format of the index data. The valid settings are either:
		const void *pVertexStreamZeroData,		//[in] User memory pointer to the vertex data. The vertex data must be in stream 0.
		UInt32 VertexStreamZeroStride			//[in] The number of bytes of data for each vertex. This value may not be 0.
	);
		
	DIS_INLINE DIS_RESULT  DrawPrimitive(//Renders a sequence of nonindexed, geometric primitives of the specified type from the current set of data input streams.
		DIS_PRIMITIVETYPE PrimitiveType,//[in]Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render.
		UInt32 StartVertex,//[in]Index of the first vertex to load. Beginning at StartVertex the correct number of vertices will be read out of the vertex buffer.
		UInt32 PrimitiveCount//[in]Number of primitives to render. The maximum number of primitives allowed is determined by checking the MaxPrimitiveCount member of the D3DCAPS9 structure. PrimitiveCount is the number of primitives as determined by the primitive type. If it is a line list, each primitive has two vertices. If it is a triangle list, each primitive has three vertices.
	);
		
	DIS_INLINE DIS_RESULT  DrawPrimitiveUP(//Renders data specified by a user memory pointer as a sequence of geometric primitives of the specified type.
		DIS_PRIMITIVETYPE PrimitiveType,// [in] Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render.
		UInt32 PrimitiveCount, //[in] Number of primitives to render. The maximum number of primitives allowed is determined by checking the MaxPrimitiveCount member of the D3DCAPS9 structure.
		const void *pVertexStreamZeroData,// [in] User memory pointer to the vertex data.
		UInt32 VertexStreamZeroStride// [in] The number of bytes of data for each vertex. This value may not be 0.
	);
	
	DIS_INLINE DIS_RESULT DrawRectPatch(//Draws a rectangular patch using the currently set streams.
		UInt32 Handle,//[in]Handle to the rectangular patch to draw.
		const float *pNumSegs,//[in]Pointer to an array of four floating-point values that identify the number of segments each edge of the rectangle patch should be divided into when tessellated. See D3DRECTPATCH_INFO.
		const DIS_RECTPATCH_INFO *pRectPatchInfo	//[in]Pointer to a D3DRECTPATCH_INFO structure, describing the rectangular patch to draw.
	);

	DIS_INLINE DIS_RESULT DrawTriPatch( //Draws a triangular patch using the currently set streams.
		UInt32 Handle,//[in]Handle to the triangular patch to draw.
		const float *pNumSegs,//[in]Pointer to an array of three floating-point values that identify the number of segments each edge of the triangle patch should be divided into when tessellated. See D3DTRIPATCH_INFO.
		const DIS_TRIPATCH_INFO *pTriPatchInfo	//[in]Pointer to a D3DTRIPATCH_INFO structure, describing the triangular high-order patch to draw.
	);
	DIS_INLINE DIS_RESULT EndScene(); //Ends a scene that was begun by calling IDirect3DDevice9::BeginScene.
	DIS_INLINE DIS_RESULT EndStateBlock(//Signals Direct3D to stop recording a device-state block and retrieve a pointer to the state block interface.
		LPSTATEBLOCK *ppSB//[in, retval] 
	);
	
	DIS_INLINE DIS_RESULT EvictManagedResources(); //Evicts all managed resources, including both Direct3D and driver-managed resources.
	
	DIS_INLINE UInt32  GetAvailableTextureMem();//Returns an estimate of the amount of available texture memory.
	
	DIS_INLINE DIS_RESULT GetBackBuffer( //Retrieves a back buffer from the device's swap chain.
			UInt32  iSwapChain,				//[in]An unsigned integer specifying the swap chain.
            UInt32 BackBuffer,				//[in]Index of the back buffer object to return. Back buffers are numbered from 0 to the total number of back buffers minus one. A value of 0 returns the first back buffer, not the front buffer. The front buffer is not accessible through this method. Use IDirect3DDevice9::GetFrontBufferData to retrieve a copy of the front buffer.
            DIS_BACKBUFFER_TYPE Type,		//[in]Stereo view is not supported in Direct3D 9, so the only valid value for this parameter is D3DBACKBUFFER_TYPE_MONO.
			LPSURFACE2D *ppBackBuffer		// [out, retval]Address of a pointer to an IDirect3DSurface9 interface, representing the returned back buffer surface.
	);
	DIS_INLINE DIS_RESULT GetClipPlane( //Retrieves the coefficients of a user-defined clipping plane for the device.
			UInt32 Index,			//[in] Index of the clipping plane for which the plane equation coefficients are retrieved.
			float *pPlane			//[out]Pointer to a four-element array of values that represent the coefficients of the clipping plane in the form of the general plane equation. See Remarks.
	);
	
	DIS_INLINE DIS_RESULT GetClipStatus(LPCLIPSTATUS pClipStatus); //Retrieves the clip status.
	
	DIS_INLINE DIS_RESULT GetCreationParameters( //Retrieves the creation parameters of the device.
		DIS_DEVICE_CREATION_PARAMETERS* pParemeters // note: get the HWND done
	);

	DIS_INLINE DIS_RESULT GetCurrentTexturePalette(UInt32 *pPaletteNumber); //Retrieves the current texture palette.
	
	DIS_INLINE DIS_RESULT GetDepthStencilSurface( //Gets the depth-stencil surface owned by the Direct3DDevice object.
	 LPSURFACE2D *ppZStencilSurface//[out, retval]  Address of a pointer to an IDirect3DSurface9 interface, representing the returned depth-stencil surface.
	 );
		
	DIS_INLINE DIS_RESULT GetDeviceCaps( //Retrieves the capabilities of the rendering device.
		DIS_CAPS *pCaps//[out]Pointer to a D3DCAPS9 structure, describing the returned device.
	);
		
	//bool GetDirect3D(); //Returns an interface to the instance of the Direct3D object that created the device.
	
	DIS_INLINE DIS_RESULT GetDisplayMode(//Retrieves the display mode's spatial resolution, color resolution, and refresh frequency.
	    UInt32  iSwapChain,				//[in]An unsigned integer specifying the swap chain.
		DIS_DISPLAYMODE *pMode			//[out]  Pointer to a D3DDISPLAYMODE structure containing data about the display mode of the adapter. As opposed to the display mode of the device, which may not be active if the device does not own full-screen mode.
	);

	DIS_INLINE DIS_RESULT GetFrontBufferData( //Generates a copy of the device's front buffer and places that copy in a system memory buffer provided by the application.
		UInt32  iSwapChain,				//[in] An unsigned integer specifying the swap chain.
		LPSURFACE2D pDestSurface		//	[in] Pointer to an IDirect3DSurface9 interface that will receive a copy of the contents of the front buffer. The data is returned in successive rows with no intervening space, starting from the vertically highest row on the device's output to the lowest.
	//For windowed mode, the size of the destination surface should be the size of the desktop. For full-screen mode, the size of the destination surface should be the screen size.
	);

	DIS_INLINE DIS_RESULT GetFVF(UInt32 *pFVF); //Gets the fixed vertex function declaration.
	
	DIS_INLINE DIS_RESULT GetGammaRamp( //Retrieves the gamma correction ramp for the swap chain.
        UInt32  iSwapChain, //[in]An unsigned integer specifying the swap chain.
		DIS_GAMMARAMP *pRamp//	[in, out]Pointer to an application-supplied D3DGAMMARAMP structure to fill with the gamma correction ramp.
	);
	DIS_INLINE DIS_RESULT GetIndices(  //Retrieves index data.
		LPINDEXBUFFER *ppIndexData//[out]Address of a pointer to an IDirect3DIndexBuffer9 interface, representing the returned index data.
		//UInt32 *pBaseVertexIndex//[out]Pointer to a UINT value, holding the returned base value for vertex indices. This value is added to all indices prior to referencing vertex data, defining a starting position in the vertex streams.
	);
	DIS_INLINE DIS_RESULT GetLight( //Retrieves a set of lighting properties that this device uses.
		UInt32 Index, //[in]Zero-based index of the lighting property set to retrieve. This method will fail if a lighting property has not been set for this index by calling the IDirect3DDevice9::SetLight method.
		DIS_LIGHT  *pLight//[in]Pointer to a D3DLIGHT9 structure that is filled with the retrieved lighting-parameter set.
	);

	DIS_INLINE DIS_RESULT GetLightEnable( //Retrieves the activity status - enabled or disabled - for a set of lighting parameters within a device.
		UInt32 Index,//[in] Zero-based index of the set of lighting parameters that are the target of this method.
		bool *pEnable	//[out, retval]Pointer to a variable to fill with the status of the specified lighting parameters. After the call, a nonzero value at this address indicates that the specified lighting parameters are enabled; a value of 0 indicates that they are disabled.
	);
	
	DIS_INLINE DIS_RESULT GetMaterial( //Retrieves the current material properties for the device.
		DIS_MATERIAL  *pMaterial // Pointer to a D3DMATERIAL9 structure to fill with the currently set material properties.
	);
	
	DIS_INLINE float GetNPatchMode(); //Gets the N-patch mode segments.
	
	DIS_INLINE UInt32 GetNumberOfSwapChains(); //Gets the number of implicit swap chains.
	
	DIS_INLINE DIS_RESULT GetPaletteEntries( //Retrieves palette entries.
       UInt32 PaletteNumber,//[in]An ordinal value identifying the particular palette to retrieve.
		DIS_PALETTEENTRY *pEntries//[in, out]Pointer to a PALETTEENTRY structure, representing the returned palette entries.
	);

	DIS_INLINE DIS_RESULT GetPixelShader( //Retrieves the currently set pixel shader.
	  LPPIXELSHADER *ppShader //[out, retval]If the method succeeds, the return value is D3D_OK. If the method fails, the return value can be D3DERR_INVALIDCALL.
		);
	DIS_INLINE DIS_RESULT GetPixelShaderConstantB( //Gets a Boolean shader constant.
        UInt32 StartRegister,//[in] Register number that will contain the first constant value.
		bool *pConstantData,//[in, out]Pointer to an array of constants.
        UInt32 BoolCount//[in] Number of Boolean values in the array of constants.
	);
	DIS_INLINE DIS_RESULT GetPixelShaderConstantF( //Gets a floating-point shader constant.
        UInt32 StartRegister,//[in]Register number that will contain the first constant value.
		float *pConstantData,//[in, out]Pointer to an array of constants.
		UInt32 Vector4fCount//[in]Number of four float vectors in the array of constants.
	);
	DIS_INLINE DIS_RESULT GetPixelShaderConstantI( //Gets an integer shader constant.
        UInt32 StartRegister,//[in] Register number that will contain the first constant value.
		int *pConstantData,//[in, out]Pointer to an array of constants.
         UInt32 Vector4iCount//[in]Number of four integer vectors in the array of constants.
	);
	DIS_INLINE DIS_RESULT GetRasterStatus( //Returns information describing the raster of the monitor on which the swap chain is presented.
		UInt32  iSwapChain,//[in]An unsigned integer specifying the swap chain.
		DIS_RASTER_STATUS *pRasterStatus // [out]Pointer to a D3DRASTER_STATUS structure filled with information about the position or other status of the raster on the monitor driven by this adapter.
	);	
		
	DIS_INLINE DIS_RESULT GetRenderState( //Retrieves a render-state value for a device.
        DIS_RENDERSTATETYPE State,//[in]Device state variable that is being queried. This parameter can be any member of the D3DRENDERSTATETYPE enumerated type.
		UInt32 *pValue//[out, retval] Pointer to a variable that receives the value of the queried render state variable when the method returns.
	);

	DIS_INLINE DIS_RESULT GetRenderTarget( //Retrieves a render-target surface.
		UInt32 RenderTargetIndex,//[in]Index of the render target. See Remarks.
		LPSURFACE2D *ppRenderTarget//[out]Address of a pointer to an IDirect3DSurface9 interface, representing the returned render-target surface for this device.
	);

	DIS_INLINE DIS_RESULT GetRenderTargetData( //Copies the render-target data from device memory to system memory.
		LPSURFACE2D pRenderTarget,//[in] 
		LPSURFACE2D pDestSurface//[in]
	);	
		
	DIS_INLINE DIS_RESULT GetSamplerState( //Gets the sampler state value.
		UInt32 Sampler,// [in] The sampler stage index.
		DIS_SAMPLERSTATETYPE Type,// [in]This parameter can be any member of the D3DSAMPLERSTATETYPE enumerated type.
		UInt32 *pValue//[out]State value to get. The meaning of this value is determined by the Type parameter.
	);
	DIS_INLINE DIS_RESULT GetScissorRect( //Gets the scissor rectangle.
		DIS_Rect *pRect//[out] Returns a pointer to a RECT structure that defines the rendering area within the render target if scissor test is enabled.
	);
	DIS_INLINE bool GetSoftwareVertexProcessing(); //Gets the vertex processing (hardware or software) mode.
	
	DIS_INLINE DIS_RESULT GetStreamSource(//Retrieves a vertex buffer bound to the specified data stream.
        UInt32 StreamNumber,//[in]Specifies the data stream, in the range from 0 to the maximum number of streams minus one.
		LPVERTEXBUFFER *ppStreamData,//[in, out]Address of a pointer to an IDirect3DVertexBuffer9 interface, representing the returned vertex buffer bound to the specified data stream.
        UInt32 *pOffsetInBytes,//[out]Pointer containing the offset from the beginning of the stream to the beginning of the vertex data. The offset is measured in bytes. See Remarks.
        UInt32 *pStride//[out]Pointer to a returned stride of the component, in bytes. See Remarks.
	);

	DIS_INLINE DIS_RESULT GetStreamSourceFreq( //Gets the stream source frequency divider value.
		UInt32 StreamNumber,//[in] Stream source number.
		UInt32 *pDivider//[out]Returns the frequency divider value.
	);

	DIS_INLINE DIS_RESULT GetSwapChain( //Gets a pointer to a swap chain.
		UInt32  iSwapChain,//[in] The swap chain ordinal value. For more information, see NumberOfAdaptersInGroup in D3DCAPS9.
		LPSWAPCHAIN *ppSwapChain//[in]Pointer to an IDirect3DSwapChain9 interface that will receive a copy of swap chain.
	);

	DIS_INLINE DIS_RESULT GetTexture( //Retrieves a texture assigned to a stage for a device.
            UInt32 Stage,//[in]Stage identifier of the texture to retrieve. Stage identifiers are zero-based.
			LPBASETEXTURE *ppTexture//[out, retval]Address of a pointer to an IDirect3DBaseTexture9 interface, representing the returned texture.
	);

	DIS_INLINE DIS_RESULT GetTextureStageState(//Retrieves a state value for an assigned texture.
		UInt32 Stage,//[in] Stage identifier of the texture for which the state is retrieved. Stage identifiers are zero-based. Devices can have up to eight set textures, so the maximum value allowed for Stage is 7.
        DIS_TEXTURESTAGESTATETYPE Type,//[in] Texture state to retrieve. This parameter can be any member of the D3DTEXTURESTAGESTATETYPE enumerated type.
		UInt32 *pValue // [out, retval]Pointer a variable to fill with the retrieved state value. The meaning of the retrieved value is determined by the Type parameter.
	);

	DIS_INLINE DIS_RESULT GetTransform( //Retrieves a matrix describing a transformation state.
		DIS_TRANSFORMSTATETYPE State,//[in]Device state variable that is being modified. This parameter can be any member of the D3DTRANSFORMSTATETYPE enumerated type, or the D3DTS_WORLDMATRIX macro.
		DIS_MATRIX *pMatrix//[out] Pointer to a D3DMATRIX structure, describing the returned transformation state.
	);

	DIS_INLINE DIS_RESULT GetVertexDeclaration( //Gets a vertex shader declaration.
		LPVERTEXDECLERATION *ppDecl//[out]
	);

	DIS_INLINE DIS_RESULT GetVertexShader( //Retrieves the currently set vertex shader.
		LPVERTEXSHADER *ppShader //[out, retval]
	);

	DIS_INLINE DIS_RESULT GetVertexShaderConstantB( //Gets a Boolean vertex shader constant.
        UInt32 StartRegister,//[in]Register number that will contain the first constant value.
		bool *pConstantData,//[in, out]Pointer to an array of constants.
        UInt32 BoolCount//[in]Number of Boolean values in the array of constants.
	);

	DIS_INLINE DIS_RESULT GetVertexShaderConstantF( //Gets a floating-point vertex shader constant.
        UInt32 StartRegister,//[in] Register number that will contain the first constant value.
		float *pConstantData,//[in, out] Pointer to an array of constants.
        UInt32 Vector4fCount//[in] Number of four float vectors in the array of constants.
	);
	
	DIS_INLINE DIS_RESULT GetVertexShaderConstantI(//Gets an integer vertex shader constant.
		UInt32 StartRegister,//  [in]Register number that will contain the first constant value.
		int *pConstantData,//[in, out]Pointer to an array of constants.
		UInt32 Vector4iCount//  [in]Number of four integer vectors in the array of constants.
	);	

	DIS_INLINE DIS_RESULT GetViewport(//Retrieves the viewport parameters currently set for the device.
		DIS_VIEWPORT *pViewport //[out] Pointer to a D3DVIEWPORT9 structure, representing the returned viewport parameters.
	);

	DIS_INLINE DIS_RESULT LightEnable( //Enables or disables a set of lighting parameters within a device.
		UInt32 LightIndex,//[in]Zero-based index of the set of lighting parameters that are the target of this method.
		bool bEnable	//[in]Value that indicates if the set of lighting parameters are being enabled or disabled. Set this parameter to TRUE to enable lighting with the parameters at the specified index, or FALSE to disable it.
	);

	DIS_INLINE DIS_RESULT MultiplyTransform( //Multiplies a device's world, view, or projection matrices by a specified matrix.
		DIS_TRANSFORMSTATETYPE State, // [in]Member of the D3DTRANSFORMSTATETYPE enumerated type, or the D3DTS_WORLDMATRIX macro that identifies which device matrix is to be modified. The most common setting, D3DTS_WORLDMATRIX(0), modifies the world matrix, but you can specify that the method modify the view or projection matrices, if needed.
		const DIS_MATRIX *pMatrix // [in]Pointer to a D3DMATRIX structure that modifies the current transformation.
	);	

	DIS_INLINE DIS_RESULT Present( //Presents the contents of the next buffer in the sequence of back buffers owned by the device.
		const DIS_Rect *pSourceRect,//[in]Pointer to a value that must be NULL unless the swap chain was created with D3DSWAPEFFECT_COPY. pSourceRect is a pointer to a RECT structure containing the source rectangle. If NULL, the entire source surface is presented. If the rectangle exceeds the source surface, the rectangle is clipped to the source surface.
		const DIS_Rect *pDestRect,//[in]Pointer to a value that must be NULL unless the swap chain was created with D3DSWAPEFFECT_COPY. pDestRect is a pointer to a RECT structure containing the destination rectangle, in window client coordinates. If NULL, the entire client area is filled. If the rectangle exceeds the destination client area, the rectangle is clipped to the destination client area.
		DIS_HWND hDestWindowOverride,//[in]Pointer to a destination window whose client area is taken as the target for this presentation. If this value is NULL, the runtime uses the hDeviceWindow member of D3DPRESENT_PARAMETERS for the presentation.
		const DIS_RGNDATA *pDirtyRegion//[in]Value must be NULL unless the swap chain was created with D3DSWAPEFFECT_COPY. For more information about swap chains, see Flipping Surfaces (Direct3D 9) and D3DSWAPEFFECT. If this value is non-NULL, the contained region is expressed in back buffer coordinates. The rectangles within the region are the minimal set of pixels that need to be updated. This method takes these rectangles into account when optimizing the presentation by copying only the pixels within the region, or some suitably expanded set of rectangles. This is an aid to optimization only, and the application should not rely on the region being copied exactly. The implementation can choose to copy the whole source rectangle.
	);	
		
	DIS_INLINE DIS_RESULT ProcessVertices( //Applies the vertex processing defined by the vertex shader to the set of input data streams, generating a single stream of interleaved vertex data to the destination vertex buffer.
		UInt32 SrcStartIndex, //[in] Index of first vertex to load.
		UInt32 DestIndex, // [in] Index of first vertex in the destination vertex buffer into which the results are placed.
		UInt32 VertexCount,//[in] Number of vertices to process.
		LPVERTEXBUFFER *pDestBuffer,//[in] Pointer to an IDirect3DVertexBuffer9 interface, the destination vertex buffer representing the stream of interleaved vertex data.
		LPVERTEXDECLERATION pVertexDecl,//[in] Pointer to an IDirect3DVertexDeclaration9 interface that represents the output vertex data declaration. When vertex shader 3.0 or above is set as the current vertex shader, the output vertex declaration must be present.
		UInt32 Flags//[in] Processing options. Set this parameter to 0 for default processing. Set to D3DPV_DONOTCOPYDATA to prevent the system from copying vertex data not affected by the vertex operation into the destination buffer. The D3DPV_DONOTCOPYDATA value may be combined with one or more D3DLOCK values appropriate for the destination buffer.
	);	
		
	DIS_INLINE DIS_RESULT Reset( //Resets the type, size, and format of the swap chain.
		DIS_PRESENT_PARAMETERS *pPresentationParameters // [in, out]Pointer to a D3DPRESENT_PARAMETERS structure, describing the new presentation parameters. This value cannot be NULL.
		//	When switching to full-screen mode, Direct3D will try to find a desktop format that matches the back buffer format, so that back buffer and front buffer formats will be identical (to eliminate the need for color conversion).
		//	When this method returns:
		//	BackBufferCount, BackBufferWidth, and BackBufferHeight are set to zero.
		//	BackBufferFormat is set to D3DFMT_UNKNOWN for windowed mode only; a full-screen mode must specify a format.
	);
	
	DIS_INLINE DIS_RESULT SetClipPlane( //Sets the coefficients of a user-defined clipping plane for the device.
		UInt32 Index, // [in] Index of the clipping plane for which the plane equation coefficients are to be set.
		const float *pPlane	//[in]Pointer to an address of a four-element array of values that represent the clipping plane coefficients to be set, in the form of the general plane equation. See Remarks.
	);

	DIS_INLINE DIS_RESULT SetClipStatus( //Sets the clip status.
		 const DIS_CLIPSTATUS *pClipStatus//[in]  Pointer to a DIS_CLIPSTATUS structure, describing the clip status settings to be set.
	);
	DIS_INLINE DIS_RESULT  SetCurrentTexturePalette( //Sets the current texture palette.
		UInt32 PaletteNumber //[in]
	);

	DIS_INLINE DIS_RESULT SetCursorPosition( //Sets the cursor position and update options.
		UInt32 X,//[in]
		UInt32 Y,//[in]
		UInt32 Flags//[in]Specifies the update options for the cursor. Currently, only one flag is defined. D3DCURSOR_IMMEDIATE_UPDATE
	);

	DIS_INLINE DIS_RESULT SetCursorProperties( //Sets properties for the cursor.
		UInt32 XHotSpot,//[in]X-coordinate offset (in pixels) that marks the center of the cursor. The offset is relative to the upper-left corner of the cursor. When the cursor is given a new position, the image is drawn at an offset from this new position determined by subtracting the hot spot coordinates from the position.
		UInt32 YHotSpot,//[in]Y-coordinate offset (in pixels) that marks the center of the cursor. The offset is relative to the upper-left corner of the cursor. When the cursor is given a new position, the image is drawn at an offset from this new position determined by subtracting the hot spot coordinates from the position.
		LPSURFACE2D pCursorBitmap//[in]Pointer to an IDirect3DSurface9 interface. This parameter must point to an 8888 ARGB surface (format D3DFMT_A8R8G8B8). The contents of this surface will be copied and potentially format-converted into an internal buffer from which the cursor is displayed. The dimensions of this surface must be less than the dimensions of the display mode, and must be a power of two in each direction, although not necessarily the same power of two. The alpha channel must be either 0.0 or 1.0.
	);

	DIS_INLINE DIS_RESULT SetDepthStencilSurface( //Sets the depth stencil surface.
		  LPSURFACE2D pNewZStencil // [in]Address of a pointer to an IDirect3DSurface9 interface representing the depth stencil surface. Setting this to NULL disables the depth stencil operation.
	);
	
	DIS_INLINE DIS_RESULT SetDialogBoxMode( //This method allows the use of GDI dialog boxes in full-screen mode applications.
		bool bEnableDialogs	//[in]
	);

	DIS_INLINE DIS_RESULT SetFVF( //Sets the current vertex stream declaration.
		UInt32 fvf // [in]DWORD containing the fixed function vertex type. For more information, see D3DFVF.
	);

	
	DIS_INLINE DIS_RESULT SetGammaRamp( //Sets the gamma correction ramp for the implicit swap chain. This method will affect the entire screen (not just the active window if you are running in windowed mode).
		UInt32  iSwapChain,//[in]  
		UInt32 Flags,//[in]  Indicates whether correction should be applied. Gamma correction results in a more consistent display, but can incur processing overhead and should not be used frequently. Short-duration effects, such as flashing the whole screen red, should not be calibrated, but long-duration gamma changes should be calibrated. One of the following values can be set:
		//D3DSGR_CALIBRATE
		//If a gamma calibrator is installed, the ramp will be modified before being sent to the device to account for the system and monitor response curves. If a calibrator is not installed, the ramp will be passed directly to the device.
		//D3DSGR_NO_CALIBRATION
		//No gamma correction is applied. The supplied gamma table is transferred directly to the device.
		const DIS_GAMMARAMP *pRamp//[in]  
	);

	DIS_INLINE DIS_RESULT SetIndices( //Sets index data.
		LPINDEXBUFFER pIndexData // [in]
	);

	DIS_INLINE DIS_RESULT SetLight( //Assigns a set of lighting properties for this device.
		UInt32 Index, // [in] light index
		const DIS_LIGHT *pLight//[in] light
	);

	DIS_INLINE DIS_RESULT SetMaterial( //Sets the material properties for the device.
		const DIS_MATERIAL *pMaterial // [in] pointer to material structure
	);

	DIS_INLINE DIS_INLINE DIS_RESULT SetNPatchMode( //Enable or disable N-patches.
		float nSegments // [in]Specifies the number of subdivision segments. If the number of segments is less than 1.0, N-patches are disabled. The default value is 0.0.
	);


	DIS_INLINE DIS_RESULT SetPaletteEntries( //Sets palette entries.
		UInt32 PaletteNumber,//[in]  An ordinal value identifying the particular palette upon which the operation is to be performed.
		const DIS_PALETTEENTRY *pEntries//[in]  Pointer to a PALETTEENTRY structure, representing the palette entries to set. The number of PALETTEENTRY structures pointed to by pEntries is assumed to be 256. See Remarks
	);
	
	DIS_INLINE DIS_RESULT SetPixelShader( //Sets the current pixel shader to a previously created pixel shader.
		LPPIXELSHADER pShader // [in]  Pixel shader interface.
	);

	DIS_INLINE DIS_RESULT SetPixelShaderConstantB( //Sets a Boolean shader constant.
		UInt32 StartRegister, // [in]Register number that will contain the first constant value.
		const bool *pConstantData, // [in]Pointer to an array of constants.
		UInt32 BoolCount // [in]  Number of boolean values in the array of constants.
	);

	DIS_INLINE DIS_RESULT SetPixelShaderConstantF( //Sets a floating-point shader constant.
		UInt32 StartRegister, // [in]Register number that will contain the first constant value.
		const float *pConstantData, // [in]Pointer to an array of constants.
		UInt32 Vector4fCount // [in]  Number of 4 float vectors in the array of constants.
	);

	DIS_INLINE DIS_RESULT SetPixelShaderConstantI( //Sets an integer shader constant.
		UInt32 StartRegister, // [in]Register number that will contain the first constant value.
		const int *pConstantData, // [in]Pointer to an array of constants.
		UInt32 Vector4iCount // [in]  Number of 4 integer vectors in the array of constants.
	);

	DIS_INLINE DIS_RESULT SetRenderState( //Sets a single device render-state parameter.
		DIS_RENDERSTATETYPE State, //[in]  Device state variable that is being modified. This parameter can be any member of the DIS_RENDERSTATETYPE enumerated type.
		UInt32 Value //[in]  New value for the device render state to be set. The meaning of this parameter is dependent on the value specified for State. For example, if State were D3DRS_SHADEMODE, the second parameter would be one member of the DIS_SHADEMODE enumerated type.
	);

	DIS_INLINE DIS_RESULT SetRenderTarget( //Sets a new color buffer for the device.
		UInt32 RenderTargetIndex,//[in]  Index of the render target. See Remarks.
		LPSURFACE2D pRenderTarget // [in]  Pointer to a new color buffer. If NULL, the color buffer for the corresponding RenderTargetIndex is disabled. Devices always must be associated with a color buffer. The new render-target surface must have at least DIS_USAGE_RENDERTARGET specified.
	);

	DIS_RESULT SetSamplerState( //Sets the sampler state value.
		UInt32 Sampler,//[in]  The sampler stage index. For more info about sampler stage, see Sampling Stage Registers in vs_3_0 (DirectX HLSL).
		DIS_SAMPLERSTATETYPE Type,//[in]  This parameter can be any member of the D3DSAMPLERSTATETYPE enumerated type.
		UInt32 Value//[in]  State value to set. The meaning of this value is determined by the Type parameter.
	);

	DIS_INLINE DIS_RESULT SetScissorRect( //Sets the scissor rectangle.
		const DIS_Rect *pRect	// [in]  
	);

	DIS_INLINE DIS_RESULT SetSoftwareVertexProcessing( //Use this method to switch between software and hardware vertex processing.
		bool bSoftware
	);

	DIS_INLINE DIS_RESULT SetStreamSource( //Binds a vertex buffer to a device data stream. For more information, see Setting the Stream Source (Direct3D 9).
		UInt32 StreamNumber,//[in]  Specifies the data stream, in the range from 0 to the maximum number of streams -1.
		LPVERTEXBUFFER pStreamData,//[in]  Pointer to an LPVERTEXBUFFER interface, representing the vertex buffer to bind to the specified data stream.
		UInt32 OffsetInBytes,//[in]  Offset from the beginning of the stream to the beginning of the vertex data, in bytes. To find out if the device supports stream offsets, see the D3DDEVCAPS2_STREAMOFFSET constant in D3DDEVCAPS2.
		UInt32 Stride//[in]  Stride of the component, in bytes. See Remarks.
	);
		
	//There are two constants defined in d3d9types.h that are designed to use with SetStreamSourceFreq: 
	//D3DSTREAMSOURCE_INDEXEDDATA and D3DSTREAMSOURCE_INSTANCEDATA. To see how to use the constants, see Efficiently Drawing Multiple Instances of Geometry (Direct3D 9).
	DIS_INLINE DIS_RESULT SetStreamSourceFreq( //Sets the stream source frequency divider value. This may be used to draw several instances of geometry.
		UInt32 StreamNumber,//[in]  Stream source number.
		UInt32 FrequencyParameter//[in]  This parameter may have two different values. See remarks.
	);

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
	DIS_INLINE DIS_RESULT SetTexture( //Assigns a texture to a stage for a device.
		UInt32 Sampler,//[in]  Zero based sampler number. Textures are bound to samplers; samplers define sampling state such as the filtering mode and the address wrapping mode. Textures are referenced differently by the programmable and the fixed function pipeline:
		LPBASETEXTURE pTexture // [in]  Pointer to an LPBASETEXTURE interface, representing the texture being set.
	);

	DIS_INLINE DIS_RESULT SetTextureStageState( //Sets the state value for the currently assigned texture.
		UInt32 Stage, //[in]Stage identifier of the texture for which the state value is set. Stage identifiers are zero-based. Devices can have up to eight set textures, so the maximum value allowed for Stage is 7.
		DIS_TEXTURESTAGESTATETYPE Type, //[in]Texture state to set. This parameter can be any member of the D3DTEXTURESTAGESTATETYPE enumerated type.
		UInt32 Value // [in]State value to set. The meaning of this value is determined by the Type parameter.
	);	

	
	DIS_INLINE DIS_RESULT SetTransform( //Sets a single device transformation-related state.
		DIS_TRANSFORMSTATETYPE State, //[in]  Device-state variable that is being modified. This parameter can be any member of the D3DTRANSFORMSTATETYPE enumerated type, or the D3DTS_WORLDMATRIX macro.
		const DIS_MATRIX *pMatrix // [in]  
	);

	DIS_INLINE DIS_RESULT SetTransformf( //Sets a single device transformation-related state.
		DIS_TRANSFORMSTATETYPE State, //[in]  Device-state variable that is being modified. This parameter can be any member of the D3DTRANSFORMSTATETYPE enumerated type, or the D3DTS_WORLDMATRIX macro.
		const float *pMatrix // [in]  
	);
		
	DIS_INLINE DIS_RESULT SetVertexDeclaration( //Sets a Vertex Declaration (Direct3D 9).
		LPVERTEXDECLERATION pDecl //[in]Pointer to an LPVERTEXDECLERATION object, which contains the vertex declaration.
	);

	DIS_INLINE DIS_RESULT SetVertexShader( //Sets the vertex shader.
		LPVERTEXSHADER pShader //[in]Vertex shader interface. For more information, see LPVERTEXSHADER.
	);

	DIS_INLINE DIS_RESULT SetVertexShaderConstantB( //Sets a Boolean vertex shader constant.
		UInt32 StartRegister, // [in]Register number that will contain the first constant value.
		const bool *pConstantData, // [in]Pointer to an array of constants.
		UInt32 BoolCount // [in]Number of boolean values in the array of constants.
	);


	DIS_INLINE DIS_RESULT SetVertexShaderConstantF( //Sets a floating-point vertex shader constant.
		UInt32 StartRegister, //[in] Register number that will contain the first constant value.
		const float *pConstantData,//[in] Pointer to an array of constants.
		UInt32 Vector4fCount //[in] Number of four float vectors in the array of constants.
	);	
		
	DIS_INLINE DIS_RESULT SetVertexShaderConstantI( //Sets an integer vertex shader constant.
		UInt32 StartRegister,//[in]  Register number that will contain the first constant value.
		const int *pConstantData,//[in]  Pointer to an array of constants.
		UInt32 Vector4iCount //[in]  Number of four integer vectors in the array of constants.
	);

	DIS_INLINE DIS_RESULT SetViewport( //Sets the viewport parameters for the device.
		const DIS_VIEWPORT *pViewport // [in] Pointer to a DIS_VIEWPORT structure, specifying the viewport parameters to set. 
	);

	DIS_INLINE bool ShowCursor( bool bShow ); //Displays or hides the cursor.
	
	DIS_INLINE DIS_RESULT StretchRect( //Copy the contents of the source rectangle to the destination rectangle. The source rectangle can be stretched and filtered by the copy. This function is often used to change the aspect ratio of a video stream.
		LPSURFACE2D *pSourceSurface,//[in]  Pointer to the source surface. See LPSURFACE2D.
		const DIS_Rect *pSourceRect,//[in]  Pointer to the source rectangle. A NULL for this parameter causes the entire source surface to be used.
		LPSURFACE2D *pDestSurface,//[in]  Pointer to the destination surface. See IDirect3DSurface9.
		const DIS_Rect *pDestRect,//[in]  Pointer to the destination rectangle. A NULL for this parameter causes the entire destination surface to be used.
		DIS_TEXTUREFILTERTYPE Filter//[in]  Filter type. Allowable values are D3DTEXF_NONE, D3DTEXF_POINT, or D3DTEXF_LINEAR. For more information, see
	);

	DIS_INLINE DIS_RESULT TestCooperativeLevel(); //Reports the current cooperative-level status of the Direct3D device for a windowed or full-screen application.
	
	DIS_INLINE DIS_RESULT UpdateSurface( //Copies rectangular subsets of pixels from one surface to another.
		LPSURFACE2D pSourceSurface,//[in]  Pointer to an LPSURFACE2D interface, representing the source surface. This parameter must point to a different surface than pDestinationSurface.
		const DIS_Rect *pSourceRect,//[in]  Pointer to a rectangle on the source surface. Specifying NULL for this parameter causes the entire surface to be copied.
		LPSURFACE2D *pDestinationSurface,//[in]  Pointer to an LPSURFACE2D interface, representing the destination surface.
		const DIS_POINT *pDestinationPoint//[in]  Pointer to the upper left corner of the destination rectangle. Specifying NULL for this parameter causes the entire surface to be copied.
	);	
		
	DIS_INLINE DIS_RESULT UpdateTexture( //Updates the dirty portions of a texture.
		LPBASETEXTURE pSourceTexture,//[in]Pointer to an IDirect3DBaseTexture9 interface, representing the source texture. The source texture must be in system memory (D3DPOOL_SYSTEMMEM).
		LPBASETEXTURE pDestinationTexture // [in]Pointer to an IDirect3DBaseTexture9 interface, representing the destination texture. The destination texture must be in the D3DPOOL_DEFAULT memory pool.
	);

	DIS_INLINE DIS_RESULT ValidateDevice( //Reports the device's ability to render the current texture-blending operations and arguments in a single pass.
		UInt32 *pNumPasses // [out, retval]  Pointer to a DWORD value to fill with the number of rendering passes needed to complete the desired effect through multipass rendering.
	);

	/*Int32 DIS_Backbuffer_type[3];
	Int32 DIS_Subdiv_type[3];
	Int32 DIS_Blend_Func[18];
	Int32 DIS_BlendOp[6];
	Int32 DIS_CmpFunc[9];
	Int32 DIS_ComposerOp[5];
	Int32 DIS_CubemapFace[6];
	Int32 DIS_Cullmode[4];
	Int32 DIS_DebugMonitor[2];
	Int32 DIS_DeclMethod[7];
	Int32 DIS_DeclType[18];
	Int32 DIS_DeclUsage[14];
	Int32 DIS_DegreeType[5];
	Int32 DIS_DeviceType[5];
	Int32 DIS_DisplayRot[5];
	Int32 DIS_FillMode[4];
	Int32 DIS_FogMode[4];
	Int32 DIS_TexFormat[200];
	Int32 DIS_LightType[6];
	Int32 DIS_MaterialColorSource[3];
	Int32 DIS_MultiSampleType[17];
	Int32 DIS_PatchEdgeStyle[2];
	Int32 DIS_Pool[4];
	Int32 DIS_PrimitiveType[7];
	Int32 DIS_QueryType[16];
	Int32 DIS_RenderStateType[240];
	Int32 DIS_ResourceType[7];
	Int32 DIS_SamplerTextureType[4];
	Int32 DIS_SampleStateType[14];
	Int32 DIS_ScanlineOrdering[3];
	Int32 DIS_ShadeMode[5];
	Int32 DIS_StateBlockType[4];
	Int32 DIS_StencilOp[9];
	Int32 DIS_SwapEffect[6];
	Int32 DIS_TextureAddress[6];
	Int32 DIS_TextureFilterType[7];
	Int32 DIS_TextureOp[27];
	Int32 DIS_TextureStageStateType[40];
	Int32 DIS_TextureTransformFlags[6];
	Int32 DIS_TransformStateType[20];
	Int32 DIS_VertexBlendFlags[6];
	Int32 DIS_ZBufferType[3];
	*/

	UInt32 BackBufferType;
	UInt32 BasicSubdivType;
	UInt32 BlendMode;
	UInt32 BlendOp;
	UInt32 CompareFunc;
	UInt32 ComposeRectsOp;
	UInt32 CubeMapFace;
	UInt32 CullMode;
	UInt32 DebugMonitor;
	UInt32 DeclMethod;
	UInt32 SubdivDegreeType;
	UInt32 DeviceType;
	UInt32 CompositorDisplayRotation;
	UInt32 FillMode;
	UInt32 FogMode;
	UInt32 MultiSampleType;
	UInt32 PatchEdgeStyle;

	union RenderStateVars
	{
		float val;
		UInt32 state;
	};

	RenderStateVars RenderStates[240];
	
	UInt32 SampleTextureType;
	UInt32 ScanlineOrdering;
	UInt32 ShadeMode;
	UInt32 SwapEffect;


	LPSURFACE2D m_RenderTargets[MAX_RENDERTARGETS];

	struct TextureStage
	{
		UInt32 value;
	};

	struct TextureStageType
	{
		TextureStage textures[32];
	};

#define MAX_TEXTURESTAGES 32

	TextureStageType m_TextureStages[MAX_TEXTURESTAGES];

	LPBASETEXTURE textureStages[MAX_TEXTURESTAGES];

#define MAX_VERTEXSTREAMS 100

	LPVERTEXBUFFER m_activeVertexBuffer;

	struct VertexStream
	{
		LPVERTEXBUFFER pVBuffer;
		UInt32 offsetInBytes;
		UInt32 stride;
		UInt32 freq;
	};

	VertexStream m_vertexStreams[MAX_VERTEXSTREAMS];

	LPINDEXBUFFER m_activeIndexBuffer;

	LPSURFACE2D m_activeBackBuffer;
	LPSURFACE2D m_activeDepthStencilBuffer;

	UInt32 m_activeFVF;

	//DIS_GAMMARAMP m_activeGammaRamp;

	LPPIXELSHADER m_activePixelShader;
	LPVERTEXSHADER m_activeVertexShader;

	LPVERTEXDECLERATION m_activeVertexDecleration;

	struct SamplerState
	{
		UInt32 value;
	};

	struct SamplerStateType
	{
		SamplerState samplerStateType[14];
	};

	SamplerStateType m_samplerStates[MAX_SAMPLERSTATES];

	




	bool m_SoftwareVertexProcessing;

	UInt32 m_PaletteNumber;

	enum GET_STATE_MODE
	{
		GSM_LOWLEVEL,
		GSM_HIGHLEVEL,
	};

	GET_STATE_MODE m_GetStateMode;



};

typedef DIS_Device *LPDEVICE;

#endif