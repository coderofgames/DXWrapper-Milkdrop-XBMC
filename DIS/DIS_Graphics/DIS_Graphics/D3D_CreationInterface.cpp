#include "D3D_CreationInterface.h"
#include "D3D_Conversion.h"
#include "D3D_Interface.h"

#include <d3d9.h>

DIS_D3DConversion to_DIS_;
D3D_DeviceInterface d3dInterface;
DIS_Device			disDevice;
D3D_CreationInterface *d3dCreationInterface;

LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice

extern HWND hWnd;

D3D_CreationInterface* D3D_Create(int id)
{
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( g_pD3D == NULL )
		return NULL;

	d3dCreationInterface = new D3D_CreationInterface();

	return d3dCreationInterface;
}

void D3D_Shutdown()
{
	if( g_pD3D )
	{
		g_pD3D->Release();
	}

	if( d3dCreationInterface )
	{
		delete d3dCreationInterface;
		d3dCreationInterface = NULL;
	}
}

DIS_RESULT D3D_CreationInterface::CheckDepthStencilMatch(
	UInt32 Adapter, // [in] Ordinal number denoting the display adapter to query. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_DEVTYPE DeviceType, // [in]Member of the D3DDEVTYPE enumerated type, identifying the device type.
	DIS_FORMAT AdapterFormat, // [in]Member of the D3DFORMAT enumerated type, identifying the format of the display mode into which the adapter will be placed.
	DIS_FORMAT RenderTargetFormat, // [in]Member of the D3DFORMAT enumerated type, identifying the format of the render-target surface to be tested.
	DIS_FORMAT DepthStencilFormat // [in]Member of the D3DFORMAT enumerated type, identifying the format of the depth-stencil surface to be tested.
)
{
	HRESULT hr = g_pD3D->CheckDepthStencilMatch(
						Adapter,
						(D3DDEVTYPE)d3dInterface.DIS_DeviceType[ DeviceType ],
						(D3DFORMAT)d3dInterface.DIS_Format[ AdapterFormat ],
						(D3DFORMAT)d3dInterface.DIS_Format[ RenderTargetFormat ],
						(D3DFORMAT)d3dInterface.DIS_Format[ DepthStencilFormat ]);

	return HR_to_DR(hr);
}
	
//Determines whether a depth-stencil format is compatible with a render-target format in a particular display mode.
DIS_RESULT D3D_CreationInterface::CheckDeviceFormat(
	UInt32 Adapter, //[in]Ordinal number denoting the display adapter to query. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns D3DERR_INVALIDCALL when this value equals or exceeds the number of display adapters in the system.
	DIS_DEVTYPE DeviceType,//[in]Member of the D3DDEVTYPE enumerated type, identifying the device type.
	DIS_FORMAT AdapterFormat,//[in]Member of the D3DFORMAT enumerated type, identifying the format of the display mode into which the adapter will be placed.
	UInt32 Usage,//[in]Requested usage options for the surface. Usage options are any combination of D3DUSAGE and D3DUSAGE_QUERY constants (only a subset of the D3DUSAGE constants are valid for CheckDeviceFormat; see the table on the D3DUSAGE page).
	DIS_RESOURCETYPE RType,//[in]Resource type requested for use with the queried format. Member of D3DRESOURCETYPE.
	DIS_FORMAT CheckFormat//[in]Format of the surfaces which may be used, as defined by Usage. Member of D3DFORMAT.
)
{
	HRESULT hr = g_pD3D->CheckDeviceFormat(
							Adapter,
							(D3DDEVTYPE)d3dInterface.DIS_DeviceType[ DeviceType ],
							(D3DFORMAT)d3dInterface.DIS_Format[ AdapterFormat ],
							(D3DFORMAT)d3dInterface.DIS_Usage[ Usage ],
							(D3DRESOURCETYPE)d3dInterface.DIS_ResourceType[ RType ],
							(D3DFORMAT)d3dInterface.DIS_Format[ CheckFormat ]);
	return HR_to_DR(hr);
}
	
//Determines whether a surface format is available as a specified resource type and can be used as a texture, depth-stencil buffer, or render target, or any combination of the three, on a device representing this adapter.
DIS_RESULT D3D_CreationInterface::CheckDeviceFormatConversion(
	UInt32 Adapter,//[in] Display adapter ordinal number. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns D3DERR_INVALIDCALL when this value equals or exceeds the number of display adapters in the system.
	DIS_DEVTYPE DeviceType,//[in]Device type. Member of the D3DDEVTYPE enumerated type.
	DIS_FORMAT SourceFormat,//[in]Source adapter format. Member of the D3DFORMAT enumerated type.
	DIS_FORMAT TargetFormat//[in]Target adapter format. Member of the D3DFORMAT enumerated type.
)
{
	HRESULT hr = g_pD3D->CheckDeviceFormatConversion(
							Adapter,
							(D3DDEVTYPE)d3dInterface.DIS_DeviceType[ DeviceType ],
							(D3DFORMAT)d3dInterface.DIS_Format[ SourceFormat ],
							(D3DFORMAT)d3dInterface.DIS_Format[ TargetFormat ]);
	return HR_to_DR(hr);
}

//Tests the device to see if it supports conversion from one display format to another.
DIS_RESULT D3D_CreationInterface::CheckDeviceMultiSampleType(
	UInt32 Adapter, // [in]Ordinal number denoting the display adapter to query. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns FALSE when this value equals or exceeds the number of display adapters in the system. See Remarks.
	DIS_DEVTYPE DeviceType,//[in]Member of the D3DDEVTYPE enumerated type, identifying the device type.
	DIS_FORMAT SurfaceFormat,//[in]Member of the D3DFORMAT enumerated type that specifies the format of the surface to be multisampled. For more information, see Remarks.
	bool Windowed,//[in] bool value. Specify TRUE to inquire about windowed multisampling, and specify FALSE to inquire about full-screen multisampling.
	DIS_MULTISAMPLE_TYPE MultiSampleType,//[in]Member of the D3DMULTISAMPLE_TYPE enumerated type, identifying the multisampling technique to test.
	UInt32 *pQualityLevels//[in]pQualityLevels returns the number of device-specific sampling variations available with the given sample type. For example, if the returned value is 3, then quality levels 0, 1 and 2 can be used when creating resources with the given sample count. The meanings of these quality levels are defined by the device manufacturer and cannot be queried through D3D. For example, for a particular device different quality levels at a fixed sample count might refer to different spatial layouts of the sample locations or different methods of resolving. This can be NULL if it is not necessary to return the quality levels.
)
{
	HRESULT hr = g_pD3D->CheckDeviceMultiSampleType(
							Adapter,
							(D3DDEVTYPE)d3dInterface.DIS_DeviceType[ DeviceType ],
							(D3DFORMAT)d3dInterface.DIS_Format[ SurfaceFormat ],
							Windowed,
							(D3DMULTISAMPLE_TYPE)d3dInterface.DIS_MultiSampleType[ MultiSampleType ],
							(DWORD*)pQualityLevels);

	return HR_to_DR(hr);
}
//Determines if a multisampling technique is available on this device.
DIS_RESULT D3D_CreationInterface::CheckDeviceType(
	UInt32 Adapter, // [in]Ordinal number denoting the display adapter to enumerate. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns D3DERR_INVALIDCALL when this value equals or exceeds the number of display adapters in the system.
	DIS_DEVTYPE DeviceType, // [in]Member of the D3DDEVTYPE enumerated type, indicating the device type to check.
	DIS_FORMAT DisplayFormat, // [in]Member of the D3DFORMAT enumerated type, indicating the format of the adapter display mode for which the device type is to be checked. For example, some devices will operate only in 16-bits-per-pixel modes.
	DIS_FORMAT BackBufferFormat, // [in]Back buffer format. For more information about formats, see D3DFORMAT. This value must be one of the render-target formats. You can use GetAdapterDisplayMode to obtain the current format. For windowed applications, the back buffer format does not need to match the display mode format if the hardware supports color conversion. The set of possible back buffer formats is constrained, but the runtime will allow any valid back buffer format to be presented to any desktop format. There is the additional requirement that the device be operable in the desktop mode because devices typically do not operate in 8 bits per pixel modes. Full-screen applications cannot do color conversion. D3DFMT_UNKNOWN is allowed for windowed mode.
	bool Windowed // [in]Value indicating whether the device type will be used in full-screen or windowed mode. If set to TRUE, the query is performed for windowed applications; otherwise, this value should be set FALSE.
)
{
	HRESULT hr = g_pD3D->CheckDeviceType(
							Adapter,
							(D3DDEVTYPE)d3dInterface.DIS_DeviceType[ DeviceType ],
							(D3DFORMAT)d3dInterface.DIS_Format[ DisplayFormat ],
							(D3DFORMAT)d3dInterface.DIS_Format[ BackBufferFormat ],
							Windowed);
	return HR_to_DR(hr);
}

//Verifies whether a hardware accelerated device type can be used on this adapter.
DIS_RESULT D3D_CreationInterface::CreateDevice(
    UInt32 Adapter, // [in]Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_DEVTYPE DeviceType, // [in] Member of the D3DDEVTYPE enumerated type that denotes the desired device type. If the desired device type is not available, the method will fail.          
	DIS_HWND hFocusWindow,//[in] The focus window alerts Direct3D when an application switches from foreground mode to background mode. See Remarks.
							// For full-screen mode, the window specified must be a top-level window.
							// For windowed mode, this parameter may be NULL only if the hDeviceWindow member of pPresentationParameters is set to a valid, non-NULL value.          
    UInt32 BehaviorFlags,//[in]Combination of one or more options that control device creation. For more information, see D3DCREATE.
	DIS_PRESENT_PARAMETERS *pPresentationParameters, // [in, out]    Pointer to a D3DPRESENT_PARAMETERS structure, describing the presentation parameters for the device to be created. If BehaviorFlags specifies D3DCREATE_ADAPTERGROUP_DEVICE, pPresentationParameters is an array. Regardless of the number of heads that exist, only one depth/stencil surface is automatically created.
					/*For Windows 2000 and Windows XP, the full-screen device display refresh rate is set in the following order:
					User-specified nonzero ForcedRefreshRate registry key, if supported by the device.
					Application-specified nonzero refresh rate value in the presentation parameter.
					Refresh rate of the latest desktop mode, if supported by the device.
					75 hertz if supported by the device.
					60 hertz if supported by the device.
					Device default.
					An unsupported refresh rate will default to the closest supported refresh rate below it. For example, if the application specifies 63 hertz, 60 hertz will be used. There are no supported refresh rates below 57 hertz.
					pPresentationParameters is both an input and an output parameter. Calling this method may change several members including:
					If BackBufferCount, BackBufferWidth, and BackBufferHeight are 0 before the method is called, they will be changed when the method returns.
					If BackBufferFormat equals D3DFMT_UNKNOWN before the method is called, it will be changed when the method returns.  */
	LPDEVICE *ppReturnedDeviceInterface // [out, retval]  Address of a pointer to the returned IDirect3DDevice9 interface, which represents the created device.
)
{
	D3DPRESENT_PARAMETERS PP;
	PP.AutoDepthStencilFormat = (D3DFORMAT)d3dInterface.DIS_Format[ pPresentationParameters->AutoDepthStencilFormat ];
	PP.BackBufferCount = pPresentationParameters->BackBufferCount;
	PP.BackBufferFormat =  (D3DFORMAT)d3dInterface.DIS_Format[pPresentationParameters->BackBufferFormat];
	PP.BackBufferHeight = pPresentationParameters->BackBufferHeight;
	PP.BackBufferWidth = pPresentationParameters->BackBufferWidth;
	PP.EnableAutoDepthStencil = pPresentationParameters->EnableAutoDepthStencil;
	PP.Flags = pPresentationParameters->Flags;
	PP.FullScreen_RefreshRateInHz = pPresentationParameters->FullScreen_RefreshRateInHz;
	PP.hDeviceWindow = (HWND)pPresentationParameters->hDeviceWindow;
	PP.MultiSampleQuality = pPresentationParameters->MultiSampleQuality;
	PP.MultiSampleType = (D3DMULTISAMPLE_TYPE)d3dInterface.DIS_MultiSampleType[ pPresentationParameters->MultiSampleType ];
	PP.PresentationInterval = pPresentationParameters->PresentationInterval;
	PP.SwapEffect = (D3DSWAPEFFECT)d3dInterface.DIS_SwapEffect[ pPresentationParameters->SwapEffect ];
	PP.Windowed = pPresentationParameters->Windowed;
	
//D3DPRESENT_PARAMETERS d3dpp;
 //   ZeroMemory( &d3dpp, sizeof( d3dpp ) );
//    d3dpp.Windowed = TRUE;
//	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
  //  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	/*d3dpp.Flags = 0;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
	d3dpp.Windowed = TRUE;
	//PresentParameters.PresentationInterval		=	DISPRESENT_INTERVAL_ONE;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;*/
   // d3dpp.EnableAutoDepthStencil = TRUE;
  //  d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	//d3dpp.MultiSampleQuality = 1;
	HRESULT hr = g_pD3D->CreateDevice(
						/*	Adapter,
							(D3DDEVTYPE)d3dInterface.DIS_DeviceType[ DeviceType ],
							(HWND)hFocusWindow,
							BehaviorFlags,
							&PP,
							GetDeviceD3D());*/
					D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
									  &PP,
							GetDeviceD3D());

	*ppReturnedDeviceInterface = &disDevice;

	return HR_to_DR(hr);
}

//Creates a device to represent the display adapter.
DIS_RESULT D3D_CreationInterface::EnumAdapterModes(
	UInt32 Adapter, // [in]Ordinal number denoting the display adapter to enumerate. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns D3DERR_INVALIDCALL when this value equals or exceeds the number of display adapters in the system.
	DIS_FORMAT Format, // [in]Allowable pixel formats. See Remarks.
	UInt32 Mode, // [in]Represents the display-mode index which is an unsigned integer between zero and the value returned by GetAdapterModeCount minus one.
	DIS_DISPLAYMODE *pMode // [out]A pointer to the available display mode of type D3DDISPLAYMODE. See Remarks.
)
{
	D3DDISPLAYMODE displayMode;
	HRESULT hr = g_pD3D->EnumAdapterModes(
							Adapter,
							(D3DFORMAT)d3dInterface.DIS_Format[ Format ],
							Mode,
							&displayMode);

	pMode->Format = to_DIS_.dFormat( displayMode.Format );
	pMode->Width = displayMode.Width;
	pMode->Height = displayMode.Height;
	pMode->RefreshRate = displayMode.RefreshRate;

	return HR_to_DR(hr);
}

//Queries the device to determine whether the specified adapter supports the requested format and display mode. This method could be used in a loop to enumerate all the available adapter modes.
UInt32 D3D_CreationInterface::GetAdapterCount()
{
	return g_pD3D->GetAdapterCount();
}

//Returns the number of adapters on the system.
DIS_RESULT D3D_CreationInterface::GetAdapterDisplayMode(
    UInt32 Adapter,//[in]Ordinal number that denotes the display adapter to query. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_DISPLAYMODE *pMode//[in, out] Pointer to a D3DDISPLAYMODE structure, to be filled with information describing the current adapter's mode.
)
{
	D3DDISPLAYMODE displayMode;
	HRESULT hr = g_pD3D->GetAdapterDisplayMode(
							Adapter,
							&displayMode);

	pMode->Format = to_DIS_.dFormat( displayMode.Format );
	pMode->Width = displayMode.Width;
	pMode->Height = displayMode.Height;
	pMode->RefreshRate = displayMode.RefreshRate;
	
	return HR_to_DR(hr);
}

//Retrieves the current display mode of the adapter.
DIS_RESULT D3D_CreationInterface::GetAdapterIdentifier(
	UInt32 Adapter, // [in]Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter. The minimum value for this parameter is 0, and the maximum value for this parameter is one less than the value returned by GetAdapterCount.
	UInt32 Flags, // [in]0
	DIS_ADAPTER_IDENTIFIER *pIdentifier // [out]Pointer to a D3DADAPTER_IDENTIFIER9 structure to be filled with information describing this adapter. If Adapter is greater than or equal to the number of adapters in the system, this structure will be zeroed.
)
{
	D3DADAPTER_IDENTIFIER9 d3dAdapterIdentifier;
	HRESULT hr = g_pD3D->GetAdapterIdentifier(
							Adapter,
							Flags,
							&d3dAdapterIdentifier);

	strcpy_s( pIdentifier->Description, d3dAdapterIdentifier.Description);
	pIdentifier->DeviceId = d3dAdapterIdentifier.DeviceId;
	strcpy_s(pIdentifier->DeviceName, d3dAdapterIdentifier.DeviceName);
	strcpy_s(pIdentifier->Driver, d3dAdapterIdentifier.Driver);
	//pIdentifier->DriverVersion = (Int64)d3dAdapterIdentifier.DriverVersion;
	pIdentifier->Revision = d3dAdapterIdentifier.Revision;
	pIdentifier->SubSysId = d3dAdapterIdentifier.SubSysId;
	pIdentifier->VendorId = d3dAdapterIdentifier.VendorId;
	pIdentifier->WHQLLevel = d3dAdapterIdentifier.WHQLLevel;

	return HR_to_DR(hr);
}

//Describes the physical display adapters present in the system when the IDirect3D9 interface was instantiated.
UInt32 D3D_CreationInterface::GetAdapterModeCount(
	UInt32 Adapter,//[in] Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_FORMAT Format//[in] Identifies the format of the surface type using D3DFORMAT. Use EnumAdapterModes to see the valid formats.
)
{
	return g_pD3D->GetAdapterModeCount(
					Adapter,
					(D3DFORMAT)d3dInterface.DIS_Format[ Format ]);

}

//Returns the number of display modes available on this adapter.
DIS_HMONITOR D3D_CreationInterface::GetAdapterMonitor(
UInt32 Adapter//[in]Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter.
)
{

	return (DIS_HMONITOR)g_pD3D->GetAdapterMonitor(Adapter);
}
	
//Returns the handle of the monitor associated with the Direct3D object.
DIS_RESULT D3D_CreationInterface::GetDeviceCaps(
	UInt32 Adapter,//[in]Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_DEVTYPE DeviceType,//[in]Member of the D3DDEVTYPE enumerated type. Denotes the device type.
	DIS_CAPS *pCaps// [out]
)
{
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));
	HRESULT hr = g_pD3D->GetDeviceCaps(
							Adapter,
							(D3DDEVTYPE)d3dInterface.DIS_DeviceType[ DeviceType ],
							&caps);

	
	pCaps->AdapterOrdinal = caps.AdapterOrdinal;
	pCaps->AdapterOrdinalInGroup = caps.AdapterOrdinalInGroup;
	pCaps->AlphaCmpCaps = caps.AlphaCmpCaps;
	pCaps->Caps = caps.Caps;
	pCaps->Caps2 = caps.Caps2;
	pCaps->Caps3 = caps.Caps3;
	pCaps->CubeTextureFilterCaps = caps.CubeTextureFilterCaps;
	pCaps->CursorCaps = caps.CursorCaps;
	pCaps->DeclTypes =caps.DeclTypes;
	pCaps->DestBlendCaps = caps.DestBlendCaps;
	pCaps->DevCaps = caps.DevCaps;
	pCaps->DevCaps2 = caps.DevCaps2;
//	pCaps->DeviceType = caps.DeviceType;
	pCaps->ExtentsAdjust = caps.ExtentsAdjust;
	pCaps->FVFCaps = caps.FVFCaps;
	pCaps->GuardBandBottom = caps.GuardBandBottom;
	pCaps->GuardBandLeft = caps.GuardBandLeft;
	pCaps->GuardBandRight = caps.GuardBandRight;
	pCaps->GuardBandTop = caps.GuardBandTop;
	pCaps->LineCaps = caps.LineCaps;
	pCaps->MasterAdapterOrdinal = caps.MasterAdapterOrdinal;
	pCaps->MaxActiveLights = caps.MaxActiveLights;
	pCaps->MaxAnisotropy = caps.MaxAnisotropy;
	//caps.MaxNpatchTessellationLevel;
	pCaps->MaxPixelShader30InstructionSlots = caps.MaxPixelShader30InstructionSlots;
	pCaps->MaxPointSize = caps.MaxPointSize;
	pCaps->MaxPrimitiveCount = caps.MaxPrimitiveCount;
	pCaps->MaxPShaderInstructionsExecuted = caps.MaxPixelShader30InstructionSlots;
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
	pCaps->MaxVertexBlendMatrixIndex = caps.MaxVertexBlendMatrixIndex;
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
	{
		pCaps->PS20Caps.Caps = caps.PS20Caps.Caps;
		pCaps->PS20Caps.DynamicFlowControlDepth = caps.PS20Caps.DynamicFlowControlDepth;
		pCaps->PS20Caps.NumInstructionSlots = caps.PS20Caps.NumInstructionSlots;
		pCaps->PS20Caps.NumTemps = caps.PS20Caps.NumTemps;
		pCaps->PS20Caps.StaticFlowControlDepth = caps.PS20Caps.StaticFlowControlDepth;
	}

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
	{
		pCaps->VS20Caps.Caps= caps.VS20Caps.Caps;
		pCaps->VS20Caps.DynamicFlowControlDepth= caps.VS20Caps.DynamicFlowControlDepth;
		pCaps->VS20Caps.NumTemps= caps.VS20Caps.NumTemps;

		pCaps->VS20Caps.StaticFlowControlDepth = caps.VS20Caps.StaticFlowControlDepth;
	}

	pCaps->ZCmpCaps = caps.ZCmpCaps;
	
	return HR_to_DR(hr);
}

//Retrieves device-specific information about a device.
DIS_RESULT D3D_CreationInterface::RegisterSoftwareDevice(
	void *pInitializeFunction//[in]
)
{
	HRESULT hr = g_pD3D->RegisterSoftwareDevice(pInitializeFunction);
	return HR_to_DR(hr);
}