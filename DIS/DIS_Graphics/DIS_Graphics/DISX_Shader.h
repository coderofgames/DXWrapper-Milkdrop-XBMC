#ifndef DISX_SHADER_H
#define DISX_SHADER_H
//#include <d3dx9shader.h>
//LPD3DXCONSTANTTABLE ct;

#define DISX_SHADER_DEBUG                          (1 << 0)
#define DISX_SHADER_SKIPVALIDATION                 (1 << 1)
#define DISX_SHADER_SKIPOPTIMIZATION               (1 << 2)
#define DISX_SHADER_PACKMATRIX_ROWMAJOR            (1 << 3)
#define DISX_SHADER_PACKMATRIX_COLUMNMAJOR         (1 << 4)
#define DISX_SHADER_PARTIALPRECISION               (1 << 5)
#define DISX_SHADER_FORCE_VS_SOFTWARE_NOOPT        (1 << 6)
#define DISX_SHADER_FORCE_PS_SOFTWARE_NOOPT        (1 << 7)
#define DISX_SHADER_NO_PRESHADER                   (1 << 8)
#define DISX_SHADER_AVOID_FLOW_CONTROL             (1 << 9)
#define DISX_SHADER_PREFER_FLOW_CONTROL            (1 << 10)
#define DISX_SHADER_ENABLE_BACKWARDS_COMPATIBILITY (1 << 12) 
#define DISX_SHADER_IEEE_STRICTNESS                (1 << 13)
#define DISX_SHADER_USE_LEGACY_DISX_31_DLL        (1 << 16)


// optimization level flags
#define DISX_SHADER_OPTIMIZATION_LEVEL0            (1 << 14)
#define DISX_SHADER_OPTIMIZATION_LEVEL1            0
#define DISX_SHADER_OPTIMIZATION_LEVEL2            ((1 << 14) | (1 << 15))
#define DISX_SHADER_OPTIMIZATION_LEVEL3            (1 << 15)


//----------------------------------------------------------------------------
// DISX_CONSTTABLE flags:
// -------------------

#define DISX_CONSTTABLE_LARGEADDRESSAWARE          (1 << 17)


#ifndef DISX_FX_LARGEADDRESS_HANDLE
#include <Windows.h>
typedef LPCSTR DISX_HANDLE;
#else
typedef UINT_PTR D3DXHANDLE;
#endif

typedef DISX_HANDLE *LPDISX_HANDLE;

//----------------------------------------------------------------------------
// DISX_MACRO:
// ----------
// Preprocessor macro definition.  The application pass in a NULL-terminated
// array of this structure to various D3DX APIs.  This enables the application
// to #define tokens at runtime, before the file is parsed.
//----------------------------------------------------------------------------

typedef struct _DISX_MACRO
{
	LPCSTR Name;
	LPCSTR Definition;

} DISX_MACRO, *LPDISX_MACRO;



//----------------------------------------------------------------------------
// DISX_SEMANTIC:
//----------------------------------------------------------------------------

typedef struct _DISX_SEMANTIC
{
	UINT Usage;
	UINT UsageIndex;

} DISX_SEMANTIC, *LPDISX_SEMANTIC;


//----------------------------------------------------------------------------
// DISX_REGISTER_SET:
//----------------------------------------------------------------------------

typedef enum _DISX_REGISTER_SET
{
	DISX_RS_BOOL,
	DISX_RS_INT4,
	DISX_RS_FLOAT4,
	DISX_RS_SAMPLER,

	// force 32-bit size enum
	DISX_RS_FORCE_DWORD = 0x7fffffff

} DISX_REGISTER_SET, *LPDISX_REGISTER_SET;


//----------------------------------------------------------------------------
// DISX_PARAMETER_CLASS:
//----------------------------------------------------------------------------

typedef enum _DISX_PARAMETER_CLASS
{
	DISX_PC_SCALAR,
	DISX_PC_VECTOR,
	DISX_PC_MATRIX_ROWS,
	DISX_PC_MATRIX_COLUMNS,
	DISX_PC_OBJECT,
	DISX_PC_STRUCT,

	// force 32-bit size enum
	DISX_PC_FORCE_DWORD = 0x7fffffff

} DISX_PARAMETER_CLASS, *LPDISX_PARAMETER_CLASS;


//----------------------------------------------------------------------------
// DISX_PARAMETER_TYPE:
//----------------------------------------------------------------------------

typedef enum _DISX_PARAMETER_TYPE
{
	DISX_PT_VOID,
	DISX_PT_BOOL,
	DISX_PT_INT,
	DISX_PT_FLOAT,
	DISX_PT_STRING,
	DISX_PT_TEXTURE,
	DISX_PT_TEXTURE1D,
	DISX_PT_TEXTURE2D,
	DISX_PT_TEXTURE3D,
	DISX_PT_TEXTURECUBE,
	DISX_PT_SAMPLER,
	DISX_PT_SAMPLER1D,
	DISX_PT_SAMPLER2D,
	DISX_PT_SAMPLER3D,
	DISX_PT_SAMPLERCUBE,
	DISX_PT_PIXELSHADER,
	DISX_PT_VERTEXSHADER,
	DISX_PT_PIXELFRAGMENT,
	DISX_PT_VERTEXFRAGMENT,
	DISX_PT_UNSUPPORTED,

	// force 32-bit size enum
	DISX_PT_FORCE_DWORD = 0x7fffffff

} DISX_PARAMETER_TYPE, *LPDISX_PARAMETER_TYPE;


//----------------------------------------------------------------------------
// DISX_CONSTANTTABLE_DESC:
//----------------------------------------------------------------------------

typedef struct _DISX_CONSTANTTABLE_DESC
{
	LPCSTR Creator;                     // Creator string
	DWORD Version;                      // Shader version
	UINT Constants;                     // Number of constants

} DISX_CONSTANTTABLE_DESC, *LPDISX_CONSTANTTABLE_DESC;


//----------------------------------------------------------------------------
// DISX_CONSTANT_DESC:
//----------------------------------------------------------------------------

typedef struct _DISX_CONSTANT_DESC
{
	LPCSTR Name;                        // Constant name

	DISX_REGISTER_SET RegisterSet;       // Register set
	UINT RegisterIndex;                 // Register index
	UINT RegisterCount;                 // Number of registers occupied

	DISX_PARAMETER_CLASS Class;          // Class
	DISX_PARAMETER_TYPE Type;            // Component type

	UINT Rows;                          // Number of rows
	UINT Columns;                       // Number of columns
	UINT Elements;                      // Number of array elements
	UINT StructMembers;                 // Number of structure member sub-parameters

	UINT Bytes;                         // Data size, in bytes
	LPCVOID DefaultValue;               // Pointer to default value

} DISX_CONSTANT_DESC, *LPDISX_CONSTANT_DESC;


#include "DIS_ResourceTypes.h"
#include "DIS_Device.h"
#include "DIS_Math.h"

class DISX_ConstantTable : public DIS_Resource
{
public:
	// Buffer
	virtual LPVOID GetBufferPointer(void) = 0;
	virtual DWORD GetBufferSize(void) = 0;

	// Descs
	virtual DIS_RESULT GetDesc(DISX_CONSTANTTABLE_DESC *pDesc) = 0;
	virtual DIS_RESULT GetConstantDesc(DISX_HANDLE hConstant, DISX_CONSTANT_DESC *pConstantDesc, UINT *pCount) = 0;
	virtual UINT GetSamplerIndex(DISX_HANDLE hConstant) = 0;

	// Handle operations
	virtual DISX_HANDLE GetConstant(DISX_HANDLE hConstant, UINT Index) = 0;
	virtual DISX_HANDLE GetConstantByName(DISX_HANDLE hConstant, LPCSTR pName) = 0;
	virtual DISX_HANDLE GetConstantElement(DISX_HANDLE hConstant, UINT Index) = 0;

	// Set Constants
	virtual DIS_RESULT SetDefaults(LPDEVICE pDevice) = 0;
	virtual DIS_RESULT SetValue( LPDEVICE pDevice, DISX_HANDLE hConstant, LPCVOID pData, UINT Bytes) = 0;
	virtual DIS_RESULT SetBool( LPDEVICE pDevice, DISX_HANDLE hConstant, BOOL b) = 0;
	virtual DIS_RESULT SetBoolArray( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST BOOL* pb, UINT Count) = 0;
	virtual DIS_RESULT SetInt( LPDEVICE pDevice, DISX_HANDLE hConstant, INT n) = 0;
	virtual DIS_RESULT SetIntArray( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST INT* pn, UINT Count) = 0;
	virtual DIS_RESULT SetFloat( LPDEVICE pDevice, DISX_HANDLE hConstant, FLOAT f) = 0;
	virtual DIS_RESULT SetFloatArray( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST FLOAT* pf, UINT Count) = 0;
	virtual DIS_RESULT SetVector( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_VECTOR4* pVector) = 0;
	virtual DIS_RESULT SetVectorArray( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_VECTOR4* pVector, UINT Count) = 0;
	virtual DIS_RESULT SetMatrix( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix) = 0;
	virtual DIS_RESULT SetMatrixArray( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix, UINT Count) = 0;
	virtual DIS_RESULT SetMatrixPointerArray( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX** ppMatrix, UINT Count) = 0;
	virtual DIS_RESULT SetMatrixTranspose( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix) = 0;
	virtual DIS_RESULT SetMatrixTransposeArray( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix, UINT Count) = 0;
	virtual DIS_RESULT SetMatrixTransposePointerArray( LPDEVICE pDevice, DISX_HANDLE hConstant, CONST DISX_MATRIX** ppMatrix, UINT Count) = 0;

};
typedef DISX_ConstantTable *LPDISX_CONSTANTTABLE;


class DISX_TextureShader : public DIS_Resource
{
public:

	// IUnknown


	// Gets
	virtual DIS_RESULT GetFunction(LPBUFFER *ppFunction) = 0;
	virtual DIS_RESULT GetConstantBuffer(LPBUFFER *ppConstantBuffer) = 0;

	// Descs
	virtual DIS_RESULT GetDesc( DISX_CONSTANTTABLE_DESC *pDesc) =0;
	virtual DIS_RESULT GetConstantDesc(DISX_HANDLE hConstant, DISX_CONSTANT_DESC *pConstantDesc, UINT *pCount) = 0;

	// Handle operations
	virtual DISX_HANDLE GetConstant(DISX_HANDLE hConstant, UINT Index) = 0;
	virtual DISX_HANDLE GetConstantByName(DISX_HANDLE hConstant, LPCSTR pName) = 0;
	virtual DISX_HANDLE GetConstantElement(DISX_HANDLE hConstant, UINT Index) = 0;

	// Set Constants
	virtual DIS_RESULT SetDefaults()=0;
	virtual DIS_RESULT SetValue( DISX_HANDLE hConstant, LPCVOID pData, UINT Bytes) =0;
	virtual DIS_RESULT SetBool( DISX_HANDLE hConstant, BOOL b) =0;
	virtual DIS_RESULT SetBoolArray( DISX_HANDLE hConstant, CONST BOOL* pb, UINT Count) =0;
	virtual DIS_RESULT SetInt( DISX_HANDLE hConstant, INT n) =0;
	virtual DIS_RESULT SetIntArray( DISX_HANDLE hConstant, CONST INT* pn, UINT Count) =0;
	virtual DIS_RESULT SetFloat( DISX_HANDLE hConstant, FLOAT f) =0;
	virtual DIS_RESULT SetFloatArray( DISX_HANDLE hConstant, CONST FLOAT* pf, UINT Count) =0;
	virtual DIS_RESULT SetVector( DISX_HANDLE hConstant, CONST DISX_VECTOR4* pVector) =0;
	virtual DIS_RESULT SetVectorArray( DISX_HANDLE hConstant, CONST DISX_VECTOR4* pVector, UINT Count) =0;
	virtual DIS_RESULT SetMatrix( DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix) =0;
	virtual DIS_RESULT SetMatrixArray( DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix, UINT Count) =0;
	virtual DIS_RESULT SetMatrixPointerArray( DISX_HANDLE hConstant, CONST DISX_MATRIX** ppMatrix, UINT Count) =0;
	virtual DIS_RESULT SetMatrixTranspose( DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix) =0;
	virtual DIS_RESULT SetMatrixTransposeArray( DISX_HANDLE hConstant, CONST DISX_MATRIX* pMatrix, UINT Count) =0;
	virtual DIS_RESULT SetMatrixTransposePointerArray( DISX_HANDLE hConstant, CONST DISX_MATRIX** ppMatrix, UINT Count) =0;
};
typedef DISX_TextureShader *LPDISX_TEXTURESHADER;

//----------------------------------------------------------------------------
// DISX_INCLUDE_TYPE:
//----------------------------------------------------------------------------

typedef enum _DISX_INCLUDE_TYPE
{
	DISX_INC_LOCAL,
	DISX_INC_SYSTEM,

	// force 32-bit size enum
	DISX_INC_FORCE_DWORD = 0x7fffffff

} DISX_INCLUDE_TYPE, *LPDISX_INCLUDE_TYPE;



class DISX_Include 
{
public:

	virtual HRESULT Open( DISX_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)=0;
	virtual HRESULT Close(LPCVOID pData) = 0;
};

typedef DISX_Include *LPDISX_INCLUDE;


//----------------------------------------------------------------------------
// DISX_AssembleShader:
// -------------------
// Assembles a shader.
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
//  Flags
//      See DISX_SHADER_xxx flags
//  ppShader
//      Returns a buffer containing the created shader.  This buffer contains
//      the assembled shader code, as well as any embedded debug info.
//  ppErrorMsgs
//      Returns a buffer containing a listing of errors and warnings that were
//      encountered during assembly.  If you are running in a debugger,
//      these are the same messages you will see in your debug output.
//----------------------------------------------------------------------------


DIS_RESULT  
DISX_AssembleShaderFromFileA(
LPCSTR                          pSrcFile,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs);

DIS_RESULT  
DISX_AssembleShaderFromFileW(
LPCWSTR                         pSrcFile,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs);

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
LPBUFFER*                   ppErrorMsgs);

DIS_RESULT  
DISX_AssembleShaderFromResourceW(
HMODULE                         hSrcModule,
LPCWSTR                         pSrcResource,
CONST DISX_MACRO*                pDefines,
LPDISX_INCLUDE                   pInclude,
DWORD                           Flags,
LPBUFFER*                   ppShader,
LPBUFFER*                   ppErrorMsgs);

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
LPBUFFER*                   ppErrorMsgs);



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
LPDISX_CONSTANTTABLE*            ppConstantTable);

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
LPDISX_CONSTANTTABLE*            ppConstantTable);

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
LPDISX_CONSTANTTABLE*            ppConstantTable);

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
LPDISX_CONSTANTTABLE*            ppConstantTable);

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
LPDISX_CONSTANTTABLE*            ppConstantTable);


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
LPBUFFER*                   ppDisassembly);


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
LPDEVICE               pDevice);

LPCSTR  
DISX_GetVertexShaderProfile(
LPDEVICE pDevice);


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
UINT*                           pSizeInBytes);


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
CONST DWORD*                    pFunction);


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
CONST DWORD*                    pFunction);

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
UINT*                           pCount);

DIS_RESULT  
DISX_GetShaderOutputSemantics(
CONST DWORD*                    pFunction,
DISX_SEMANTIC*                   pSemantics,
UINT*                           pCount);


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
UINT*                           pCount);


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
LPDISX_CONSTANTTABLE*            ppConstantTable);

DIS_RESULT  
DISX_GetShaderConstantTableEx(
CONST DWORD*                    pFunction,
DWORD                           Flags,
LPDISX_CONSTANTTABLE*            ppConstantTable);



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
LPDISX_TEXTURESHADER*            ppTextureShader);


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
LPBUFFER*                ppErrorMsgs);

DIS_RESULT  
DISX_PreprocessShaderFromFileW(
LPCWSTR                      pSrcFile,
CONST DISX_MACRO*             pDefines,
LPDISX_INCLUDE                pInclude,
LPBUFFER*                ppShaderText,
LPBUFFER*                ppErrorMsgs);

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
LPBUFFER*                ppErrorMsgs);

DIS_RESULT  
DISX_PreprocessShaderFromResourceW(
HMODULE                      hSrcModule,
LPCWSTR                      pSrcResource,
CONST DISX_MACRO*             pDefines,
LPDISX_INCLUDE                pInclude,
LPBUFFER*                ppShaderText,
LPBUFFER*                ppErrorMsgs);

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
LPBUFFER*                ppErrorMsgs);


//////////////////////////////////////////////////////////////////////////////
// Shader comment block layouts //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3DXSHADER_CONSTANTTABLE:
// -------------------------
// Shader constant information; included as an CTAB comment block inside
// shaders.  All offsets are BYTE offsets from start of CONSTANTTABLE struct.
// Entries in the table are sorted by Name in ascending order.
//----------------------------------------------------------------------------

typedef struct _DISX_SHADER_CONSTANTTABLE
{
	DWORD Size;             // sizeof(DISX_SHADER_CONSTANTTABLE)
	DWORD Creator;          // LPCSTR offset
	DWORD Version;          // shader version
	DWORD Constants;        // number of constants
	DWORD ConstantInfo;     // DISX_SHADER_CONSTANTINFO[Constants] offset
	DWORD Flags;            // flags shader was compiled with
	DWORD Target;           // LPCSTR offset 

} DISX_SHADER_CONSTANTTABLE, *LPDISX_SHADER_CONSTANTTABLE;


typedef struct _DISX_SHADER_CONSTANTINFO
{
	DWORD Name;             // LPCSTR offset
	WORD  RegisterSet;      // DISX_REGISTER_SET
	WORD  RegisterIndex;    // register number
	WORD  RegisterCount;    // number of registers
	WORD  Reserved;         // reserved
	DWORD TypeInfo;         // DISX_SHADER_TYPEINFO offset
	DWORD DefaultValue;     // offset of default value

} DISX_SHADER_CONSTANTINFO, *LPDISX_SHADER_CONSTANTINFO;


typedef struct _DISX_SHADER_TYPEINFO
{
	WORD  Class;            // DISX_PARAMETER_CLASS
	WORD  Type;             // DISX_PARAMETER_TYPE
	WORD  Rows;             // number of rows (matrices)
	WORD  Columns;          // number of columns (vectors and matrices)
	WORD  Elements;         // array dimension
	WORD  StructMembers;    // number of struct members
	DWORD StructMemberInfo; // DISX_SHADER_STRUCTMEMBERINFO[Members] offset

} DISX_SHADER_TYPEINFO, *LPDISX_SHADER_TYPEINFO;


typedef struct _DISX_SHADER_STRUCTMEMBERINFO
{
	DWORD Name;             // LPCSTR offset
	DWORD TypeInfo;         // DISX_SHADER_TYPEINFO offset

} DISX_SHADER_STRUCTMEMBERINFO, *LPDISX_SHADER_STRUCTMEMBERINFO;

#endif