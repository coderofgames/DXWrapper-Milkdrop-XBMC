#ifndef DIS_EFFECT_H
#define DIS_EFFECT_H

#include "DIS_RenderStates.h"
#include "DIS_ResourceTypes.h"
#include "DIS_Math.h"

typedef struct DISX_EFFECT_DESC
{
  M_CSTR Creator;
  UInt32   Parameters;
  UInt32   Techniques;
  UInt32   Functions;
}DISX_EFFECT_DESC;


#include "DISX_Shader.h"

typedef struct DISX_PARAMETER_DESC
{
  M_CSTR              Name;
  M_CSTR              Semantic;
  DISX_PARAMETER_CLASS Class;
  DISX_PARAMETER_TYPE  Type;
  UInt32                Rows;
  UInt32                Columns;
  UInt32                Elements;
  UInt32                Annotations;
  UInt32                StructMembers;
  UInt32               Flags;
  UInt32                Bytes;
}DISX_PARAMETER_DESC;

typedef struct DISX_TECHNIQUE_DESC
{
	M_CSTR Name;
	UInt32   Passes;
	UInt32   Annotations;
}DISX_TECHNIQUE_DESC;

typedef struct DISX_PASS_DESC
{
	M_CSTR      Name;
	UInt32        Annotations;
	const UInt32 *pVertexShaderFunction;
	const UInt32 *pPixelShaderFunction;
}DISX_PASS_DESC;


typedef struct DISX_FUNCTION_DESC
{
  M_CSTR Name;
  UInt32   Annotations;
}DISX_FUNCTION_DESC;

#ifndef PURE
#define PURE =0
#endif

class DIS_Effect : public DIS_Resource
{
    // IDISX_BaseEffect
    virtual void Release() PURE;
	
    // Descs
    virtual DIS_RESULT GetDesc(DISX_EFFECT_DESC* pDesc) PURE ;
    virtual DIS_RESULT GetParameterDesc(DIS_HANDLE hParameter, DISX_PARAMETER_DESC* pDesc)PURE ;
    virtual DIS_RESULT GetTechniqueDesc(DIS_HANDLE hTechnique, DISX_TECHNIQUE_DESC* pDesc)PURE ;
    virtual DIS_RESULT GetPassDesc(DIS_HANDLE hPass, DISX_PASS_DESC* pDesc)PURE ;
    virtual DIS_RESULT GetFunctionDesc(DIS_HANDLE hShader, DISX_FUNCTION_DESC* pDesc)PURE ;

    // Handle operations
    virtual DIS_HANDLE GetParameter(  DIS_HANDLE hParameter, UInt32 Index)  PURE ;
    virtual DIS_HANDLE GetParameterByName(  DIS_HANDLE hParameter, M_CSTR pName)  PURE ;
    virtual DIS_HANDLE GetParameterBySemantic(  DIS_HANDLE hParameter, M_CSTR pSemantic)  PURE ;
    virtual DIS_HANDLE GetParameterElement(  DIS_HANDLE hParameter, UInt32 Index)  PURE ;
    virtual DIS_HANDLE GetTechnique(  UInt32 Index)  PURE ;
    virtual DIS_HANDLE GetTechniqueByName(  M_CSTR pName) PURE  ;
    virtual DIS_HANDLE GetPass(  DIS_HANDLE hTechnique, UInt32 Index)  PURE ;
    virtual DIS_HANDLE GetPassByName(  DIS_HANDLE hTechnique, M_CSTR pName) PURE  ;
    virtual DIS_HANDLE GetFunction(  UInt32 Index)  PURE ;
    virtual DIS_HANDLE GetFunctionByName(  M_CSTR pName) PURE  ;
    virtual DIS_HANDLE GetAnnotation(  DIS_HANDLE hObject, UInt32 Index)  PURE ;
    virtual DIS_HANDLE GetAnnotationByName(  DIS_HANDLE hObject, M_CSTR pName) PURE  ;

    // Get/Set Parameters
    virtual DIS_RESULT SetValue(  DIS_HANDLE hParameter, const void* pData, UInt32 Bytes)  PURE ;
    virtual DIS_RESULT GetValue(  DIS_HANDLE hParameter, void* pData, UInt32 Bytes)  PURE ;
    virtual DIS_RESULT SetBool(  DIS_HANDLE hParameter, bool b)  PURE ;
    virtual DIS_RESULT GetBool(  DIS_HANDLE hParameter, bool* pb)  PURE ;
    virtual DIS_RESULT SetBoolArray(  DIS_HANDLE hParameter, const bool* pb, UInt32 Count) PURE  ;
    virtual DIS_RESULT GetBoolArray(  DIS_HANDLE hParameter, bool* pb, UInt32 Count)  PURE ;
    virtual DIS_RESULT SetInt(  DIS_HANDLE hParameter, Int32 n)  PURE ;
    virtual DIS_RESULT GetInt(  DIS_HANDLE hParameter, Int32* pn)  PURE ;
    virtual DIS_RESULT SetIntArray(  DIS_HANDLE hParameter, const Int32* pn, UInt32 Count) PURE  ;
    virtual DIS_RESULT GetIntArray(  DIS_HANDLE hParameter, Int32* pn, UInt32 Count)  PURE ;
    virtual DIS_RESULT SetFloat(  DIS_HANDLE hParameter, float f)  PURE ;
    virtual DIS_RESULT GetFloat(  DIS_HANDLE hParameter, float* pf)  PURE ;
    virtual DIS_RESULT SetFloatArray(  DIS_HANDLE hParameter, const float* pf, UInt32 Count)  PURE ;
    virtual DIS_RESULT GetFloatArray(  DIS_HANDLE hParameter, float* pf, UInt32 Count)  PURE ;
    virtual DIS_RESULT SetVector(  DIS_HANDLE hParameter, const DISX_VECTOR4* pVector)  PURE ;
    virtual DIS_RESULT GetVector(  DIS_HANDLE hParameter, DISX_VECTOR4* pVector)  PURE ;
    virtual DIS_RESULT SetVectorArray(  DIS_HANDLE hParameter, const DISX_VECTOR4* pVector, UInt32 Count)  PURE ;
    virtual DIS_RESULT GetVectorArray(  DIS_HANDLE hParameter, DISX_VECTOR4* pVector, UInt32 Count)  PURE ;
    virtual DIS_RESULT SetMatrix(  DIS_HANDLE hParameter, const DISX_MATRIX* pMatrix)  PURE ;
    virtual DIS_RESULT GetMatrix(  DIS_HANDLE hParameter, DISX_MATRIX* pMatrix)  PURE ;
    virtual DIS_RESULT SetMatrixArray(  DIS_HANDLE hParameter, const DISX_MATRIX* pMatrix, UInt32 Count) PURE  ;
    virtual DIS_RESULT GetMatrixArray(  DIS_HANDLE hParameter, DISX_MATRIX* pMatrix, UInt32 Count)  PURE ;
    virtual DIS_RESULT SetMatrixPointerArray(  DIS_HANDLE hParameter, const DISX_MATRIX** ppMatrix, UInt32 Count)  PURE ;
    virtual DIS_RESULT GetMatrixPointerArray(  DIS_HANDLE hParameter, DISX_MATRIX** ppMatrix, UInt32 Count)  PURE ;
    virtual DIS_RESULT SetMatrixTranspose(  DIS_HANDLE hParameter, const DISX_MATRIX* pMatrix)  PURE ;
    virtual DIS_RESULT GetMatrixTranspose(  DIS_HANDLE hParameter, DISX_MATRIX* pMatrix)  PURE ;
    virtual DIS_RESULT SetMatrixTransposeArray(  DIS_HANDLE hParameter, const DISX_MATRIX* pMatrix, UInt32 Count)  PURE ;
    virtual DIS_RESULT GetMatrixTransposeArray(  DIS_HANDLE hParameter, DISX_MATRIX* pMatrix, UInt32 Count)  PURE ;
    virtual DIS_RESULT SetMatrixTransposePointerArray(  DIS_HANDLE hParameter, const DISX_MATRIX** ppMatrix, UInt32 Count)  PURE ;
    virtual DIS_RESULT GetMatrixTransposePointerArray(  DIS_HANDLE hParameter, DISX_MATRIX** ppMatrix, UInt32 Count)  PURE ;
    virtual DIS_RESULT SetString(  DIS_HANDLE hParameter, M_CSTR pString)  PURE ;
    virtual DIS_RESULT GetString(  DIS_HANDLE hParameter, M_CSTR* ppString)  PURE ;
    virtual DIS_RESULT SetTexture(  DIS_HANDLE hParameter, LPBASETEXTURE pTexture)  PURE ;
    virtual DIS_RESULT GetTexture(  DIS_HANDLE hParameter, LPBASETEXTURE *ppTexture)  PURE ;
    virtual DIS_RESULT GetPixelShader(  DIS_HANDLE hParameter, LPPIXELSHADER *ppPShader)  PURE ;
    virtual DIS_RESULT GetVertexShader(  DIS_HANDLE hParameter, LPVERTEXSHADER *ppVShader)  PURE ;

	//Set Range of an Array to pass to device
	//Usefull for sending only a subrange of an array down to the device
	virtual DIS_RESULT SetArrayRange(  DIS_HANDLE hParameter, UInt32 uStart, UInt32 uEnd)  PURE ; 
	// IDISX_BaseEffect
    
    
    // Pool
    //DIS_RESULT GetPool(  LPDISX_EFFECTPOOL* ppPool)  ;

    // Selecting and setting a technique
    virtual DIS_RESULT SetTechnique(  DIS_HANDLE hTechnique) PURE ;
    virtual DIS_HANDLE GetCurrentTechnique()  PURE ;
    virtual DIS_RESULT ValidateTechnique(  DIS_HANDLE hTechnique)  PURE ;
    virtual DIS_RESULT FindNextValidTechnique(  DIS_HANDLE hTechnique, DIS_HANDLE *pTechnique)  PURE ;
    virtual bool IsParameterUsed(  DIS_HANDLE hParameter, DIS_HANDLE hTechnique)  PURE ;

    // Using current technique
    // Begin           starts active technique
    // BeginPass       begins a pass
    // CommitChanges   updates changes to any set calls in the pass. This should be called before
    //                 any DrawPrimitive call to d3d
    // EndPass         ends a pass
    // End             ends active technique
    virtual DIS_RESULT Begin(  UInt32 *pPasses, UInt32 Flags)  PURE ;
    virtual DIS_RESULT BeginPass(  UInt32 Pass)  PURE ;
    virtual DIS_RESULT CommitChanges()  PURE ;
    virtual DIS_RESULT EndPass()  PURE ;
    virtual DIS_RESULT End()  PURE ;

    // Managing D3D Device
    //STDMETHOD(GetDevice)(  LPDIRECT3DDEVICE9* ppDevice)  ;
    //STDMETHOD(OnLostDevice)(THIS)  ;
    //STDMETHOD(OnResetDevice)(THIS)  ;

    // Logging device calls
    //DIS_RESULT SetStateManager(  LPDISX_EFFECTSTATEMANAGER pManager)  ;
    //DIS_RESULT GetStateManager(  LPDISX_EFFECTSTATEMANAGER *ppManager)  ;

    // Parameter blocks
    virtual DIS_RESULT BeginParameterBlock()  PURE ;
    virtual DIS_HANDLE EndParameterBlock()  PURE ;
    virtual DIS_RESULT ApplyParameterBlock(  DIS_HANDLE hParameterBlock)  PURE ;
    virtual DIS_RESULT DeleteParameterBlock(  DIS_HANDLE hParameterBlock)  PURE ;

    // Cloning
    //STDMETHOD(CloneEffect)(  LPDIRECT3DDEVICE9 pDevice, LPDISX_EFFECT* ppEffect)  ;
    
    // Fast path for setting variables directly in IDISX_Effect
    virtual DIS_RESULT SetRawValue(  DIS_HANDLE hParameter, const void* pData, UInt32 ByteOffset, UInt32 Bytes)  PURE ;
};


#endif