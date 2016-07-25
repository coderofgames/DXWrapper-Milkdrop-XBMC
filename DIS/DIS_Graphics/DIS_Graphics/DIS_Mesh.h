#ifndef DIS_MESH_H
#define DIS_MESH_H

#include "DIS_RenderStates.h"
#include "DIS_Device.h"
#include "DIS_ResourceTypes.h"


#define DISX_MESH_32BIT 1				//Use 32-bit indices.
#define DISX_MESH_DONOTCLIP 2			//Use the D3DUSAGE_DONOTCLIP usage flag for vertex and index buffers.
#define DISX_MESH_RTPATCHES 4			//Use the D3DUSAGE_RTPATCHES usage flag for vertex and index buffers.
#define DISX_MESH_NPATCHES 8			// Specifying this flag causes the vertex and index buffer of the mesh to be created with D3DUSAGE_NPATCHES flag. This is required if the mesh object is to be rendered using N-Patch enhancement.
#define DISX_MESH_POINTS 16				//Use the D3DUSAGE_POINTS usage flag for vertex and index buffers.
#define DISX_MESH_IB_DYNAMIC 32			//Use the D3DUSAGE_DYNAMIC usage flag for index buffers.
#define DISX_MESH_IB_MANAGED 64			//Use the D3DPOOL_MANAGED memory class for index buffers.
#define DISX_MESH_IB_WRITEONLY 128		//Use the D3DUSAGE_WRITEONLY usage flag for index buffers.
#define DISX_MESH_IB_SYSTEMMEM 256		//Use the D3DPOOL_SYSTEMMEM memory class for index buffers.
#define DISX_MESH_VB_DYNAMIC 512		//Use the D3DUSAGE_DYNAMIC usage flag for vertex buffers.
#define DISX_MESH_VB_MANAGED 1024		//Use the D3DPOOL_MANAGED memory class for vertex buffers.
#define DISX_MESH_VB_SYSTEMMEM 2048		//Use the D3DPOOL_SYSTEMMEM memory class for vertex buffers.
#define DISX_MESH_VB_WRITEONLY 4096		//Use the D3DUSAGE_WRITEONLY usage flag for vertex buffers.

#define DISX_MESH_SYSTEMMEM (DISX_MESH_IB_SYSTEMMEM | DISX_MESH_VB_SYSTEMMEM)
#define DISX_MESH_WRITEONLY (DISX_MESH_IB_WRITEONLY | DISX_MESH_VB_WRITEONLY)
#define DISX_MESH_DYNAMIC (DISX_MESH_IB_DYNAMIC | DISX_MESH_VB_DYNAMIC)
#define DISX_MESH_MANAGED (DISX_MESH_IB_MANAGED | DISX_MESH_VB_MANAGED)


enum DISX_MESHOPT {  
  DISX_MESHOPT_COMPACT            = 0x01000000, 
  DISX_MESHOPT_ATTRSORT           = 0x02000000, 
  DISX_MESHOPT_VERTEXCACHE        = 0x04000000, 
  DISX_MESHOPT_STRIPREORDER       = 0x08000000, 
  DISX_MESHOPT_IGNOREVERTS        = 0x10000000, 
  DISX_MESHOPT_DONOTSPLIT         = 0x20000000, 
  DISX_MESHOPT_DEVICEINDEPENDENT  = 0x40000000 

};


typedef struct DISX_ATTRIBUTERANGE {
  UInt32 AttribId;
  UInt32 FaceStart;
  UInt32 FaceCount;
  UInt32 VertexStart;
  UInt32 VertexCount;
} DISX_ATTRIBUTERANGE, *LPDATTRIBUTERANGE;


class DISX_BaseMesh;
typedef DISX_BaseMesh* LPDISXMESH;


class DISX_BaseMesh
{
public:

//Clones a mesh using a declarator.
	virtual DIS_RESULT CloneMesh(
			UInt32 Options,  //   [in] A combination of one or more D3DXMESH flags specifying creation options for the mesh.
			const DIS_VERTEXELEMENT *pDeclaration,//[in]     An array of D3DVERTEXELEMENT9 elements, which specify the vertex format for the vertices in the output mesh.     
			LPDEVICE pDevice,//  [in]           Pointer to an IDirect3DDevice9 interface, representing the device object associated with the mesh.
			LPDISXMESH *ppCloneMesh // [out, retval]  Address of a pointer to an ID3DXMesh interface, representing the cloned mesh.
	)=0;

//Clones a mesh using a flexible vertex format (FVF) code.
	virtual DIS_RESULT CloneMeshFVF(
			UInt32 Options,//  [in] A combination of one or more D3DXMESH flags specifying creation options for the mesh.
			UInt32 FVF, // [in]      Combination of FVF codes, which specifies the vertex format for the vertices in the output mesh. For the values of the codes, see D3DFVF.     
			LPDEVICE pDevice,//[in]     Pointer to an IDirect3DDevice9 interface representing the device object associated with the mesh.      
			LPDISXMESH *ppCloneMesh//[out, retval]  Address of a pointer to an ID3DXMesh interface, representing the cloned mesh.
	)=0;	
//Converts mesh adjacency information to an array of point representatives.
	virtual DIS_RESULT ConvertAdjacencyToPointReps(
			const UInt32 *pAdjacency, //   [in] Pointer to an array of three DWORDs per face that specify the three neighbors for each face in the mesh. The number of bytes in this array must be at least 3 * ID3DXBaseMesh::GetNumFaces * sizeof(DWORD).
			UInt32 *pPRep // [in, out]  Pointer to an array of one DWORD per vertex of the mesh that will be filled with point representative data.
	)=0;


	//Converts point representative data to mesh adjacency information.
	virtual DIS_RESULT ConvertPointRepsToAdjacency(
		const UInt32 *pPRep, //   [in]Pointer to an array of one DWORD per vertex of the mesh that contains point representative data. This parameter is optional. Supplying a NULL value will cause this parameter to be interpreted as an "identity" array.
		UInt32 *pAdjacency //  [in, out]Pointer to an array of three DWORDs per face that specify the three neighbors for each face in the mesh. The number of bytes in this array must be at least 3 * ID3DXBaseMesh::GetNumFaces * sizeof(DWORD).
	)=0;

	//Draws a subset of a mesh.
	virtual DIS_RESULT DrawSubset(
		UInt32 AttribId //   [in] 
	)=0;

	//Generate a list of mesh edges, as well as a list of faces that share each edge.
	virtual DIS_RESULT GenerateAdjacency(
		float Epsilon, //  [in]  Specifies that vertices that differ in position by less than epsilon should be treated as coincident.
		UInt32 *pAdjacency //   [in]  Pointer to an array of three DWORDs per face to be filled with the indices of adjacent faces. The number of bytes in this array must be at least 3 * ID3DXBaseMesh::GetNumFaces * sizeof(DWORD).
	)=0;

	//Retrieves either an attribute table for a mesh, or the number of entries stored in an attribute table for a mesh.
	virtual DIS_RESULT GetAttributeTable(
		DISX_ATTRIBUTERANGE *pAttribTable,  //[in, out]  Pointer to an array of D3DXATTRIBUTERANGE structures, representing the entries in the mesh's attribute table. Specify NULL to retrieve the value for pAttribTableSize.
		UInt32 *pAttribTableSize//  [in, out]  Pointer to either the number of entries stored in pAttribTable or a value to be filled in with the number of entries stored in the attribute table for the mesh.
	)=0;
	
	//Retrieves a declaration describing the vertices in the mesh.
	virtual DIS_RESULT GetDeclaration(
		DIS_VERTEXELEMENT *Declaration //   [in, out]  
	)=0;

	//Retrieves the device associated with the mesh.
	//GetDevice	

	//Gets the fixed function vertex value.
	virtual UInt32 GetFVF()=0;

	//Retrieves the data in an index buffer.
	virtual DIS_RESULT GetIndexBuffer(
		LPINDEXBUFFER *ppIB //   [out, retval]  
	)=0;


	//Gets the number of bytes per vertex.
	virtual UInt32 GetNumBytesPerVertex()=0;	

	//Retrieves the number of faces in the mesh.
	virtual UInt32 GetNumFaces()=0;	
	
	//Retrieves the number of vertices in the mesh.
	virtual UInt32 GetNumVertices()=0;

	//Retrieves the mesh options enabled for this mesh at creation time.
	virtual UInt32 GetOptions()=0;	

	//Retrieves the vertex buffer associated with the mesh.
	virtual DIS_RESULT GetVertexBuffer(
		LPVERTEXBUFFER *ppVB // [out, retval]
	)=0;	

	//Locks an index buffer and obtains a pointer to the index buffer memory.
	virtual DIS_RESULT LockIndexBuffer(
		UInt32 Flags, /* [in] 
		Combination of zero or more locking flags that describe the type of lock to perform. For this method, the valid flags are:
		D3DLOCK_DISCARD
		D3DLOCK_NO_DIRTY_UPDATE
		D3DLOCK_NOSYSLOCK
		D3DLOCK_READONLY
		For a description of the flags, see D3DLOCK.*/   
		void **ppData // [out, retval]
	)=0;

	//Locks a vertex buffer and obtains a pointer to the vertex buffer memory.
	virtual DIS_RESULT LockVertexBuffer(
		UInt32 Flags, /*  [in]  
		Combination of zero or more locking flags that describe the type of lock to perform. For this method, the valid flags are:
		D3DLOCK_DISCARD
		D3DLOCK_NO_DIRTY_UPDATE
		D3DLOCK_NOSYSLOCK
		D3DLOCK_READONLY
		D3DLOCK_NOOVERWRITE         */
		void **ppData //   [out, retval]  
		)=0;	

	//Unlocks an index buffer.
	virtual DIS_RESULT UnlockIndexBuffer()=0;
	
	//Unlocks a vertex buffer.
	virtual DIS_RESULT UnlockVertexBuffer()=0;

	//This method allows the user to change the mesh declaration without changing the data layout of the vertex buffer. The call is valid only if the old and new declaration formats have the same vertex size.
	virtual DIS_RESULT UpdateSemantics(
		DIS_VERTEXELEMENT *Declaration // [in, out]  
	)=0;

};


class DISX_Mesh : public DISX_BaseMesh
{
public:

//Locks the mesh buffer that contains the mesh attribute data, and returns a pointer to it.
	virtual DIS_RESULT LockAttributeBuffer(
		UInt32 Flags, //   [in]   
	/*
		Combination of zero or more locking flags that describe the type of lock to perform. For this method, the valid flags are:
		D3DLOCK_DISCARD
		D3DLOCK_NO_DIRTY_UPDATE
		D3DLOCK_NOSYSLOCK
		D3DLOCK_READONLY
	*/
		UInt32 **ppData //   [out]  //Address of a pointer to a buffer containing a DWORD for each face in the mesh.
	)=0;
	

	
	//Generates a new mesh with reordered faces and vertices to optimize drawing performance.
	virtual DIS_RESULT Optimize(
		UInt32 Flags, // [in]   //Specifies the type of optimization to perform. This parameter can be set to a combination of one or more flags from D3DXMESHOPT and D3DXMESH (except D3DXMESH_32BIT, D3DXMESH_IB_WRITEONLY, and D3DXMESH_WRITEONLY).    
		const UInt32 *pAdjacencyIn, // [in]    Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the source mesh. If the edge has no adjacent faces, the value is 0xffffffff. See Remarks.   
		UInt32 *pAdjacencyOut, // [in, out]  Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the optimized mesh. If the edge has no adjacent faces, the value is 0xffffffff.
		UInt32 *pFaceRemap, // [in, out]  An array of DWORDs, one per face, that identifies the original mesh face that corresponds to each face in the optimized mesh. If the value supplied for this argument is NULL, face remap data is not returned.
		LPBUFFER *ppVertexRemap, //[out]      Address of a pointer to an ID3DXBuffer interface, which contains a DWORD for each vertex that specifies how the new vertices map to the old vertices. This remap is useful if you need to alter external data based on the new vertex mapping.
		LPDISXMESH *ppOptMesh //[out]      Address of a pointer to an ID3DXMesh interface, representing the optimized mesh.
	)=0;


	//Generates a mesh with reordered faces and vertices to optimize drawing performance. This method reorders the existing mesh.
	virtual DIS_RESULT OptimizeInplace(
		UInt32 Flags,//  [in]   Combination of one or more D3DXMESHOPT flags, specifying the type of optimization to perform.
		const UInt32 *pAdjacencyIn, //   [in]   Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the source mesh. If the edge has no adjacent faces, the value is 0xffffffff.
		UInt32 *pAdjacencyOut, //   [out]  Pointer to an array of three DWORDs per face that specifies the three neighbors for each face in the optimized mesh. If the edge has no adjacent faces, the value is 0xffffffff. If the value supplied for this argument is NULL, adjacency data is not returned.
		UInt32 *pFaceRemap, //   [out]  An array of DWORDs, one per face, that identifies the original mesh face that corresponds to each face in the optimized mesh. If the value supplied for this argument is NULL, face remap data is not returned.
		LPBUFFER *ppVertexRemap //   [out]  Address of a pointer to an ID3DXBuffer interface, which contains a DWORD for each vertex that specifies how the new vertices map to the old vertices. This remap is useful if you need to alter external data based on the new vertex mapping. If the value supplied for this argument is NULL, vertex remap data is not returned.
	)=0;
	
	//Sets the attribute table for a mesh and the number of entries stored in the table.
	virtual DIS_RESULT SetAttributeTable(
		const DISX_ATTRIBUTERANGE *pAttribTable, //   [in]  Pointer to an array of D3DXATTRIBUTERANGE structures, representing the entries in the mesh attribute table.
		UInt32 cAttribTableSize //   [in]  Number of attributes in the mesh attribute table.
	)=0;


	//Unlocks an attribute buffer.
	virtual DIS_RESULT UnlockAttributeBuffer()=0;	
};

#endif