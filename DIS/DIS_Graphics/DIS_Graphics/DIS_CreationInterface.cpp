#include "DIS_CreationInterface.h"
#include "D3D_CreationInterface.h"

extern D3D_CreationInterface *d3dCreationInterface;

DIS_CreationInterface* DIS_Create(int id)
{
	d3dCreationInterface = D3D_Create(id);

	return new DIS_CreationInterface ();
}

void DIS_Shutdown(DIS_CreationInterface *disCreationInterface)
{
	if( disCreationInterface )
	{
		delete disCreationInterface;
		disCreationInterface = NULL;
	}

	D3D_Shutdown();
}

DIS_RESULT DIS_CreationInterface::CheckDepthStencilMatch(
	UInt32 Adapter, // [in] Ordinal number denoting the display adapter to query. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_DEVTYPE DeviceType, // [in]Member of the D3DDEVTYPE enumerated type, identifying the device type.
	DIS_FORMAT AdapterFormat, // [in]Member of the D3DFORMAT enumerated type, identifying the format of the display mode into which the adapter will be placed.
	DIS_FORMAT RenderTargetFormat, // [in]Member of the D3DFORMAT enumerated type, identifying the format of the render-target surface to be tested.
	DIS_FORMAT DepthStencilFormat // [in]Member of the D3DFORMAT enumerated type, identifying the format of the depth-stencil surface to be tested.
)
{
	if( !d3dCreationInterface )
		return DIS_FAIL;
	return d3dCreationInterface->CheckDepthStencilMatch(
							Adapter, 
							DeviceType,
							AdapterFormat,
							RenderTargetFormat,
							DepthStencilFormat);
}
	
//Determines whether a depth-stencil format is compatible with a render-target format in a particular display mode.
DIS_RESULT DIS_CreationInterface::CheckDeviceFormat(
	UInt32 Adapter, //[in]Ordinal number denoting the display adapter to query. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns D3DERR_INVALIDCALL when this value equals or exceeds the number of display adapters in the system.
	DIS_DEVTYPE DeviceType,//[in]Member of the D3DDEVTYPE enumerated type, identifying the device type.
	DIS_FORMAT AdapterFormat,//[in]Member of the D3DFORMAT enumerated type, identifying the format of the display mode into which the adapter will be placed.
	UInt32 Usage,//[in]Requested usage options for the surface. Usage options are any combination of D3DUSAGE and D3DUSAGE_QUERY constants (only a subset of the D3DUSAGE constants are valid for CheckDeviceFormat; see the table on the D3DUSAGE page).
	DIS_RESOURCETYPE RType,//[in]Resource type requested for use with the queried format. Member of D3DRESOURCETYPE.
	DIS_FORMAT CheckFormat//[in]Format of the surfaces which may be used, as defined by Usage. Member of D3DFORMAT.
)
{
	return d3dCreationInterface->CheckDeviceFormat(
							Adapter, 
							DeviceType,
							AdapterFormat,
							Usage,
							RType,
							CheckFormat);
	
}
	
//Determines whether a surface format is available as a specified resource type and can be used as a texture, depth-stencil buffer, or render target, or any combination of the three, on a device representing this adapter.
DIS_RESULT DIS_CreationInterface::CheckDeviceFormatConversion(
	UInt32 Adapter,//[in] Display adapter ordinal number. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns D3DERR_INVALIDCALL when this value equals or exceeds the number of display adapters in the system.
	DIS_DEVTYPE DeviceType,//[in]Device type. Member of the D3DDEVTYPE enumerated type.
	DIS_FORMAT SourceFormat,//[in]Source adapter format. Member of the D3DFORMAT enumerated type.
	DIS_FORMAT TargetFormat//[in]Target adapter format. Member of the D3DFORMAT enumerated type.
)
{
	return d3dCreationInterface->CheckDeviceFormatConversion(
							Adapter, 
							DeviceType,
							SourceFormat,
							TargetFormat);
}

//Tests the device to see if it supports conversion from one display format to another.
DIS_RESULT DIS_CreationInterface::CheckDeviceMultiSampleType(
	UInt32 Adapter, // [in]Ordinal number denoting the display adapter to query. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns FALSE when this value equals or exceeds the number of display adapters in the system. See Remarks.
	DIS_DEVTYPE DeviceType,//[in]Member of the D3DDEVTYPE enumerated type, identifying the device type.
	DIS_FORMAT SurfaceFormat,//[in]Member of the D3DFORMAT enumerated type that specifies the format of the surface to be multisampled. For more information, see Remarks.
	bool Windowed,//[in] bool value. Specify TRUE to inquire about windowed multisampling, and specify FALSE to inquire about full-screen multisampling.
	DIS_MULTISAMPLE_TYPE MultiSampleType,//[in]Member of the D3DMULTISAMPLE_TYPE enumerated type, identifying the multisampling technique to test.
	UInt32 *pQualityLevels//[in]pQualityLevels returns the number of device-specific sampling variations available with the given sample type. For example, if the returned value is 3, then quality levels 0, 1 and 2 can be used when creating resources with the given sample count. The meanings of these quality levels are defined by the device manufacturer and cannot be queried through D3D. For example, for a particular device different quality levels at a fixed sample count might refer to different spatial layouts of the sample locations or different methods of resolving. This can be NULL if it is not necessary to return the quality levels.
)
{
	return d3dCreationInterface->CheckDeviceMultiSampleType(
							Adapter, 
							DeviceType,
							SurfaceFormat,
							Windowed,
							MultiSampleType,
							pQualityLevels);
}
//Determines if a multisampling technique is available on this device.
DIS_RESULT DIS_CreationInterface::CheckDeviceType(
	UInt32 Adapter, // [in]Ordinal number denoting the display adapter to enumerate. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns D3DERR_INVALIDCALL when this value equals or exceeds the number of display adapters in the system.
	DIS_DEVTYPE DeviceType, // [in]Member of the D3DDEVTYPE enumerated type, indicating the device type to check.
	DIS_FORMAT DisplayFormat, // [in]Member of the D3DFORMAT enumerated type, indicating the format of the adapter display mode for which the device type is to be checked. For example, some devices will operate only in 16-bits-per-pixel modes.
	DIS_FORMAT BackBufferFormat, // [in]Back buffer format. For more information about formats, see D3DFORMAT. This value must be one of the render-target formats. You can use GetAdapterDisplayMode to obtain the current format. For windowed applications, the back buffer format does not need to match the display mode format if the hardware supports color conversion. The set of possible back buffer formats is constrained, but the runtime will allow any valid back buffer format to be presented to any desktop format. There is the additional requirement that the device be operable in the desktop mode because devices typically do not operate in 8 bits per pixel modes. Full-screen applications cannot do color conversion. D3DFMT_UNKNOWN is allowed for windowed mode.
	bool Windowed // [in]Value indicating whether the device type will be used in full-screen or windowed mode. If set to TRUE, the query is performed for windowed applications; otherwise, this value should be set FALSE.
)
{
	return d3dCreationInterface->CheckDeviceType(
							Adapter, 
							DeviceType,
							DisplayFormat,
							BackBufferFormat,
							Windowed);
}

//Verifies whether a hardware accelerated device type can be used on this adapter.
DIS_RESULT DIS_CreationInterface::CreateDevice(
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
	return d3dCreationInterface->CreateDevice(
							Adapter, 
							DeviceType,
							hFocusWindow,
							BehaviorFlags,
							pPresentationParameters,
							ppReturnedDeviceInterface);
}

//Creates a device to represent the display adapter.
DIS_RESULT DIS_CreationInterface::EnumAdapterModes(
	UInt32 Adapter, // [in]Ordinal number denoting the display adapter to enumerate. D3DADAPTER_DEFAULT is always the primary display adapter. This method returns D3DERR_INVALIDCALL when this value equals or exceeds the number of display adapters in the system.
	DIS_FORMAT Format, // [in]Allowable pixel formats. See Remarks.
	UInt32 Mode, // [in]Represents the display-mode index which is an unsigned integer between zero and the value returned by GetAdapterModeCount minus one.
	DIS_DISPLAYMODE *pMode // [out]A pointer to the available display mode of type D3DDISPLAYMODE. See Remarks.
)
{
	return d3dCreationInterface->EnumAdapterModes(
							Adapter, 
							Format,
							Mode,
							pMode);
}

//Queries the device to determine whether the specified adapter supports the requested format and display mode. This method could be used in a loop to enumerate all the available adapter modes.
UInt32 DIS_CreationInterface::GetAdapterCount()
{
	return d3dCreationInterface->GetAdapterCount();
							//Adapter, 
							//Format,
							//Mode,
							//pMode);
}

//Returns the number of adapters on the system.
DIS_RESULT DIS_CreationInterface::GetAdapterDisplayMode(
    UInt32 Adapter,//[in]Ordinal number that denotes the display adapter to query. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_DISPLAYMODE *pMode//[in, out] Pointer to a D3DDISPLAYMODE structure, to be filled with information describing the current adapter's mode.
)
{
	return d3dCreationInterface->GetAdapterDisplayMode(
							Adapter, 
							pMode);
}

//Retrieves the current display mode of the adapter.
DIS_RESULT DIS_CreationInterface::GetAdapterIdentifier(
	UInt32 Adapter, // [in]Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter. The minimum value for this parameter is 0, and the maximum value for this parameter is one less than the value returned by GetAdapterCount.
	UInt32 Flags, // [in]0
	DIS_ADAPTER_IDENTIFIER *pIdentifier // [out]Pointer to a D3DADAPTER_IDENTIFIER9 structure to be filled with information describing this adapter. If Adapter is greater than or equal to the number of adapters in the system, this structure will be zeroed.
)
{
	return d3dCreationInterface->GetAdapterIdentifier(
							Adapter, 
							Flags,
							pIdentifier );
}

//Describes the physical display adapters present in the system when the IDirect3D9 interface was instantiated.
UInt32 DIS_CreationInterface::GetAdapterModeCount(
	UInt32 Adapter,//[in] Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_FORMAT Format//[in] Identifies the format of the surface type using D3DFORMAT. Use EnumAdapterModes to see the valid formats.
)
{
	return d3dCreationInterface->GetAdapterModeCount(
							Adapter, 
							Format );
}

//Returns the number of display modes available on this adapter.
DIS_HMONITOR DIS_CreationInterface::GetAdapterMonitor(
UInt32 Adapter//[in]Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter.
)
{
	return d3dCreationInterface->GetAdapterMonitor(
							Adapter );
}
	
//Returns the handle of the monitor associated with the Direct3D object.
DIS_RESULT DIS_CreationInterface::GetDeviceCaps(
	UInt32 Adapter,//[in]Ordinal number that denotes the display adapter. D3DADAPTER_DEFAULT is always the primary display adapter.
	DIS_DEVTYPE DeviceType,//[in]Member of the D3DDEVTYPE enumerated type. Denotes the device type.
	DIS_CAPS *pCaps// [out]
)
{
	return d3dCreationInterface->GetDeviceCaps(
							Adapter,
							DeviceType,
							pCaps);
}

//Retrieves device-specific information about a device.
DIS_RESULT DIS_CreationInterface::RegisterSoftwareDevice(
	void *pInitializeFunction//[in]
)
{
	return d3dCreationInterface->RegisterSoftwareDevice(
							pInitializeFunction);
}