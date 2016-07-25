#include "DIS_Math.h"

#include <math.h>
#include <float.h>

#define DEBUG_ME
#ifdef DEBUG_ME
#include <d3dx9math.h>
void CopyD3DXMatrixToDISX(D3DXMATRIX *source, DISX_MATRIX *dest)
{
	dest->_11 = source->_11;  dest->_21 = source->_21;  dest->_31 = source->_31;  dest->_41 = source->_41;
	dest->_12 = source->_12;  dest->_22 = source->_22;  dest->_32 = source->_32;  dest->_42 = source->_42;
	dest->_13 = source->_13;  dest->_23 = source->_23;  dest->_33 = source->_33;  dest->_43 = source->_43;
	dest->_14 = source->_14; dest->_24 = source->_24; dest->_34 = source->_34; dest->_44 = source->_44;
}

void CopyD3DXVector3ToDISX(D3DXVECTOR3 *source, DISX_VECTOR3 *dest)
{
	dest->x = source->x;
	dest->y = source->y;
	dest->z = source->z;
}

void CopyD3DXVector4ToDISX(D3DXVECTOR4 *source, DISX_VECTOR4 *dest)
{
	dest->x = source->x;
	dest->y = source->y;
	dest->z = source->z;
	dest->w = source->w;
}
#endif

//--------------------------
// 2D Vector
//--------------------------

DISX_VECTOR2*  DISX_Vec2Normalize
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV )
{
	float pVLength = DISX_Vec2Length(pV);
	*pOut /= pVLength;

	return pOut;
}

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
DISX_VECTOR2*  DISX_Vec2Hermite
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pT1,
      const DISX_VECTOR2 *pV2, const DISX_VECTOR2 *pT2, float s )
{
	//Q(s) = (2s3 - 3s2 + 1)v1 + (-2s3 + 3s2)v2 + (s3 - 2s2 + s)t1 + (s3 - s2)t2
	float s3 = s*s*s;
	float s2 = s*s;
	*pOut = (2*s3 - 3*s2 + 1)*(*pV1) + (-2*s3 + 3*s2)*(*pV2) + (s3 - 2*s2 + s)*(*pT1) + (s3 - s2)*(*pT2);
	
	return pOut;
}

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
DISX_VECTOR2*  DISX_Vec2CatmullRom
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV0, const DISX_VECTOR2 *pV1,
      const DISX_VECTOR2 *pV2, const DISX_VECTOR2 *pV3, float s )
{
	//Q(s) = [(-s3 + 2s2 - s)p1 + (3s3 - 5s2 + 2)p2 + (-3s3 + 4s2 + s)p3 + (s3 - s2)p4] / 2
	float s3 = s*s*s;
	float s2 = s*s;
	*pOut = 0.5 * ((-s3 + 2*s2 - s)*(*pV0) + (3*s3 - 5*s2 + 2)*(*pV1) + (-3*s3 + 4*s2 + s)*(*pV2) + (s3 - s2)*(*pV3));
	
	return pOut;
}

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
DISX_VECTOR2*  DISX_Vec2BaryCentric
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2,
      const DISX_VECTOR2 *pV3, float f, float g)
{
	*pOut= (*pV1) + f*((*pV2)-(*pV1)) + g*((*pV3)-(*pV1));
	return pOut;
}

// Transform (x, y, 0, 1) by matrix.
DISX_VECTOR4*  DISX_Vec2Transform
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR2 *pV, const DISX_MATRIX *pM )
{
	pOut->x = pV->x * pM->_11 + pV->y * pM->_12 + pM->_14;
	pOut->y = pV->x * pM->_21 + pV->y * pM->_22 + pM->_24;
	pOut->z = pV->x * pM->_31 + pV->y * pM->_32 + pM->_34;
	pOut->w = pV->x * pM->_41 + pV->y * pM->_42 + pM->_44;
	
	return pOut;
}

// Transform (x, y, 0, 1) by matrix, project result back into w=1.
DISX_VECTOR2*  DISX_Vec2TransformCoord
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV, const DISX_MATRIX *pM )
{
	// TODO
	pOut->x = pV->x * pM->_11 + pV->y * pM->_12 + pM->_14;
	pOut->y = pV->x * pM->_21 + pV->y * pM->_22 + pM->_24;
	float w = pV->x * pM->_41 + pV->y * pM->_42 + pM->_44;
	
	float recip = 1/w;
	*pOut *= w;
	
	return pOut;	
}

// Transform (x, y, 0, 0) by matrix.
DISX_VECTOR2*  DISX_Vec2TransformNormal
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV, const DISX_MATRIX *pM )
{
	// TODO
	pOut->x = pV->x * pM->_11 + pV->y * pM->_12 ;
	pOut->y = pV->x * pM->_21 + pV->y * pM->_22 ;
	
	return pOut;	
}
     
// Transform Array (x, y, 0, 1) by matrix.
DISX_VECTOR4*  DISX_Vec2TransformArray
    ( DISX_VECTOR4 *pOut, UInt32 OutStride, const DISX_VECTOR2 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n)
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec2Transform( &pOut[ outputIndex ], &pV[inputIndex], pM ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}

	return pOut;
}

// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
DISX_VECTOR2*  DISX_Vec2TransformCoordArray
    ( DISX_VECTOR2 *pOut, UInt32 OutStride, const DISX_VECTOR2 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n )
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec2TransformCoord( &pOut[ outputIndex ], &pV[inputIndex], pM ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}
	return pOut;
}

// Transform Array (x, y, 0, 0) by matrix.
DISX_VECTOR2*  DISX_Vec2TransformNormalArray
    ( DISX_VECTOR2 *pOut, UInt32 OutStride, const DISX_VECTOR2 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n )
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec2TransformNormal( &pOut[ outputIndex ], &pV[inputIndex], pM ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}
	return pOut;
}
    
//--------------------------
// 3D Vector
//--------------------------

DISX_VECTOR3*  DISX_Vec3Normalize
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV )
{
	float fMagnitude = DISX_Vec3Length(pV);
	
	float fVal = 1 / fMagnitude;
	
	*pOut *= fVal;

	return pOut;
}

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
DISX_VECTOR3*  DISX_Vec3Hermite
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pT1,
      const DISX_VECTOR3 *pV2, const DISX_VECTOR3 *pT2, float s )
{
	//Q(s) = (2s3 - 3s2 + 1)v1 + (-2s3 + 3s2)v2 + (s3 - 2s2 + s)t1 + (s3 - s2)t2
	float s3 = s*s*s;
	float s2 = s*s;
	
	pOut->x = (2*s3 - 3*s2 + 1)*pV1->x + (-2*s3 + 3*s2)*pV2->x + (s3 - 2*s2 + s)*pT1->x + (s3 - s2)*pT2->x;
	pOut->y = (2*s3 - 3*s2 + 1)*pV1->y + (-2*s3 + 3*s2)*pV2->y + (s3 - 2*s2 + s)*pT1->y + (s3 - s2)*pT2->y;
	pOut->z = (2*s3 - 3*s2 + 1)*pV1->z + (-2*s3 + 3*s2)*pV2->z + (s3 - 2*s2 + s)*pT1->z + (s3 - s2)*pT2->z;
	
	return pOut;
}

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
DISX_VECTOR3*  DISX_Vec3CatmullRom
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV0, const DISX_VECTOR3 *pV1,
      const DISX_VECTOR3 *pV2, const DISX_VECTOR3 *pV3, float s )
{
	float s3 = s*s*s;
	float s2 = s*s;

	// From Microsoft Documentation
	//Q(s) = [(-s3 + 2s2 - s)p1 + (3s3 - 5s2 + 2)p2 + (-3s3 + 4s2 + s)p3 + (s3 - s2)p4] / 2
	pOut->x = 0.5*((-s3 + 2*s2 - s)*pV0->x + (3*s3 - 5*s2 + 2)*pV1->x + (-3*s3 + 4*s2 + s)*pV2->x + (s3 - s2)*pV3->x);
	pOut->y = 0.5*((-s3 + 2*s2 - s)*pV0->y + (3*s3 - 5*s2 + 2)*pV1->y + (-3*s3 + 4*s2 + s)*pV2->y + (s3 - s2)*pV3->y);
	pOut->z = 0.5*((-s3 + 2*s2 - s)*pV0->z + (3*s3 - 5*s2 + 2)*pV1->z + (-3*s3 + 4*s2 + s)*pV2->z + (s3 - s2)*pV3->z);
	
	return pOut;
}

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
DISX_VECTOR3*  DISX_Vec3BaryCentric
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2,
      const DISX_VECTOR3 *pV3, float f, float g)
{
	//*pOut = *pV1 + f *( *pV2 - *pV1 ) + g* (*pV3 - *pV1);
	pOut->x = pV1->x + f *(pV2->x - pV1->x) + g* (pV3->x - pV1->x);
	pOut->y = pV1->y + f *(pV2->y - pV1->y) + g* (pV3->y - pV1->y);
	pOut->z = pV1->z + f *(pV2->z - pV1->z) + g* (pV3->z - pV1->z);

	return pOut;
}

// Transform (x, y, z, 1) by matrix.
DISX_VECTOR4*  DISX_Vec3Transform
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR3 *pV, const DISX_MATRIX *pM )
{
	pOut->x = pV->x * pM->_11 + pV->y * pM->_12 + pV->z * pM->_13 + pM->_14;
	pOut->y = pV->x * pM->_21 + pV->y * pM->_22 + pV->z * pM->_23 + pM->_24;
	pOut->z = pV->x * pM->_31 + pV->y * pM->_32 + pV->z * pM->_33 + pM->_34;
	pOut->w = pV->x * pM->_41 + pV->y * pM->_42 + pV->z * pM->_43 + pM->_44;

	return pOut;
}

// Transform (x, y, z, 1) by matrix, project result back into w=1.
DISX_VECTOR3*  DISX_Vec3TransformCoord
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, const DISX_MATRIX *pM )
{
	// todo
	pOut->x = pV->x * pM->_11 + pV->y * pM->_12 + pV->z * pM->_13 + pM->_14;
	pOut->y = pV->x * pM->_21 + pV->y * pM->_22 + pV->z * pM->_23 + pM->_24;
	pOut->z = pV->x * pM->_31 + pV->y * pM->_32 + pV->z * pM->_33 + pM->_34;
	//pOut->w = pV->x * pM->_41 + pV->y * pM->_42 + pV->z * pM->_43 + pM->_44;
	
	float w = pV->x * pM->_41 + pV->y * pM->_42 + pV->z * pM->_43 + pM->_44;
	
	// found this in really old DX7 math 
	float recip = 1/w;
	
	*pOut *= recip;

	return pOut;
}

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
// non-affine matrix, the matrix you pass to this function should be the 
// transpose of the inverse of the matrix you would use to transform a coord.
DISX_VECTOR3*  DISX_Vec3TransformNormal
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, const DISX_MATRIX *pM )
{
	pOut->x = pV->x * pM->_11 + pV->y * pM->_12 + pV->z * pM->_13;
	pOut->y = pV->x * pM->_21 + pV->y * pM->_22 + pV->z * pM->_23;
	pOut->z = pV->x * pM->_31 + pV->y * pM->_32 + pV->z * pM->_33;

	return pOut;
}
    
    
// Transform Array (x, y, z, 1) by matrix. 
DISX_VECTOR4*  DISX_Vec3TransformArray
    ( DISX_VECTOR4 *pOut, UInt32 OutStride, const DISX_VECTOR3 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n )
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec3Transform( &pOut[ outputIndex ], &pV[inputIndex], pM ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}
	return pOut;
}

// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
DISX_VECTOR3*  DISX_Vec3TransformCoordArray
    ( DISX_VECTOR3 *pOut, UInt32 OutStride, const DISX_VECTOR3 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n )
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec3TransformCoord( &pOut[ outputIndex ], &pV[inputIndex], pM ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}
	return pOut;
}

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
// non-affine matrix, the matrix you pass to this function should be the 
// transpose of the inverse of the matrix you would use to transform a coord.
DISX_VECTOR3*  DISX_Vec3TransformNormalArray
    ( DISX_VECTOR3 *pOut, UInt32 OutStride, const DISX_VECTOR3 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n )
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec3TransformNormal( &pOut[ outputIndex ], &pV[inputIndex], pM ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}
	return pOut;
}

// Project vector from object space into screen space
DISX_VECTOR3*  DISX_Vec3Project
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, const DIS_VIEWPORT *pViewport,
      const DISX_MATRIX *pProjection, const DISX_MATRIX *pView, const DISX_MATRIX *pWorld)
{
	// TODO, why is there a viewport here? Near plane? clipping?
	DISX_MATRIX matWorldViewProjection = (*pWorld) * (*pView) * (*pProjection);

	DISX_Vec3TransformCoord( pOut, pV, &matWorldViewProjection );

	return pOut;
}

// Project vector from screen space into object space
DISX_VECTOR3*  DISX_Vec3Unproject
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, const DIS_VIEWPORT *pViewport,
      const DISX_MATRIX *pProjection, const DISX_MATRIX *pView, const DISX_MATRIX *pWorld)
{
	// TODO, why is there a viewport here? Near plane? clipping?
	DISX_MATRIX matWorldViewProjection = (*pWorld) * (*pView) * (*pProjection);
	
	DISX_MATRIX mWorldViewProjInv;
	DISX_MatrixInverse( &mWorldViewProjInv, 0, &matWorldViewProjection );
	
	DISX_Vec3TransformCoord( pOut, pV, &mWorldViewProjInv );

	return pOut;
}
      
// Project vector Array from object space into screen space
DISX_VECTOR3*  DISX_Vec3ProjectArray
    ( DISX_VECTOR3 *pOut, UInt32 OutStride,const DISX_VECTOR3 *pV, UInt32 VStride,const DIS_VIEWPORT  *pViewport,
      const DISX_MATRIX *pProjection, const DISX_MATRIX *pView, const DISX_MATRIX *pWorld, UInt32 n)
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec3Project( &pOut[ outputIndex ], &pV[inputIndex], pViewport, pProjection, pView, pWorld ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}
	return pOut;
}

// Project vector Array from screen space into object space
DISX_VECTOR3*  DISX_Vec3UnprojectArray
    ( DISX_VECTOR3 *pOut, UInt32 OutStride, const DISX_VECTOR3 *pV, UInt32 VStride, const DIS_VIEWPORT *pViewport,
      const DISX_MATRIX *pProjection, const DISX_MATRIX *pView, const DISX_MATRIX *pWorld, UInt32 n)
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec3Unproject( &pOut[ outputIndex ], &pV[inputIndex], pViewport, pProjection, pView, pWorld ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}
	return pOut;
}

//--------------------------
// 4D Vector
//--------------------------


DISX_VECTOR4*  DISX_Vec4Cross
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2,
      const DISX_VECTOR4 *pV3)
{
	//| i      j      k      l    |
	//| v1.x   v1.y   v1.z   v1.w |
	//| v2.x   v2.y   v2.z   v2.w |
	//| v3.x   v3.y   v3.z   v3.w |

	// (+) i * d1 + (-) j * d2 + (+) k * d3 + (-) l * d4;

	// d1 = | pV1->y    pV1->z   pV1->w |
	//      | pV2->y    pV2->z   pV2->w |	
	//      | pV3->y    pV3->z   pV3->w |
	//
	float d11 = (pV2->z * pV3->w - pV2->w * pV3->z);
	float d12 = (pV2->y * pV3->w - pV3->y * pV2->w);
	float d13 = (pV2->y * pV3->z - pV3->y * pV2->z);
	 
	float d1 = pV1->y * d11 - pV1->z * d12 + pV1->w * d13;

	// d2 = | pV1->x    pV1->z   pV1->w |
	//      | pV2->x    pV2->z   pV2->w |	
	//      | pV3->x    pV3->z   pV3->w |
	//
	float d21 = (pV2->z*pV3->w - pV3->z*pV2->w);
	float d22 = (pV2->x*pV3->w - pV3->x*pV2->w);
	float d23 = (pV2->x*pV3->z - pV3->x*pV2->z);
	
	float d2 =  pV1->x * d21 -pV1->z * d22 + pV1->w * d23;

	// d3 = | pV1->x    pV1->y   pV1->w |
	//      | pV2->x    pV2->y   pV2->w |	
	//      | pV3->x    pV3->y   pV3->w |
	//
	float d31 = (pV2->y * pV3->w - pV3->y * pV2->w);
	float d32 = (pV2->x * pV3->w - pV3->x * pV2->w);
	float d33 = (pV2->x * pV3->y - pV3->x * pV2->y);
	float d3 = pV1->x * d31 - pV1->y * d32 + pV1->w * d33;
	
	// d4 = | pV1->x    pV1->y   pV1->z |
	//      | pV2->x    pV2->y   pV2->z |	
	//      | pV3->x    pV3->y   pV3->z |
	//	
	float d41 = (pV2->y * pV3->z - pV3->y * pV2->z);
	float d42 = (pV2->x * pV3->y - pV3->x * pV2->y);
	float d43 = (pV2->x * pV3->y - pV3->x * pV2->y);
	
	float d4 = pV1->x * d41 - pV1->y * d42 + pV1->z * d43;

	pOut->x = d1;
	pOut->y = -d2;
	pOut->z = d3;
	pOut->w = -d4;

	return pOut;
}

DISX_VECTOR4*  DISX_Vec4Normalize
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV )
{
	float fMagnitude = DISX_Vec4Length(pV);
	
	float fVal = 1 / fMagnitude;
	
	*pOut *= fVal;

	return pOut;
}

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
DISX_VECTOR4*  DISX_Vec4Hermite
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pT1,
      const DISX_VECTOR4 *pV2, const DISX_VECTOR4 *pT2, float s )
{
	float s3 = s*s*s;
	float s2 = s*s;
	
	pOut->x = (2*s3 - 3*s2 + 1)*pV1->x + (-2*s3 + 3*s2)*pV2->x + (s3 - 2*s2 + s)*pT1->x + (s3 - s2)*pT2->x;
	pOut->y = (2*s3 - 3*s2 + 1)*pV1->y + (-2*s3 + 3*s2)*pV2->y + (s3 - 2*s2 + s)*pT1->y + (s3 - s2)*pT2->y;
	pOut->z = (2*s3 - 3*s2 + 1)*pV1->z + (-2*s3 + 3*s2)*pV2->z + (s3 - 2*s2 + s)*pT1->z + (s3 - s2)*pT2->z;
	pOut->w = (2*s3 - 3*s2 + 1)*pV1->w + (-2*s3 + 3*s2)*pV2->w + (s3 - 2*s2 + s)*pT1->w + (s3 - s2)*pT2->w;

	return pOut;
}

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
DISX_VECTOR4*  DISX_Vec4CatmullRom
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV0, const DISX_VECTOR4 *pV1,
      const DISX_VECTOR4 *pV2, const DISX_VECTOR4 *pV3, float s )
{
	float s3 = s*s*s;
	float s2 = s*s;

	// From Microsoft Documentation
	//Q(s) = [(-s3 + 2s2 - s)p1 + (3s3 - 5s2 + 2)p2 + (-3s3 + 4s2 + s)p3 + (s3 - s2)p4] / 2
	pOut->x = 0.5*((-s3 + 2*s2 - s)*pV0->x + (3*s3 - 5*s2 + 2)*pV1->x + (-3*s3 + 4*s2 + s)*pV2->x + (s3 - s2)*pV3->x);
	pOut->y = 0.5*((-s3 + 2*s2 - s)*pV0->y + (3*s3 - 5*s2 + 2)*pV1->y + (-3*s3 + 4*s2 + s)*pV2->y + (s3 - s2)*pV3->y);
	pOut->z = 0.5*((-s3 + 2*s2 - s)*pV0->z + (3*s3 - 5*s2 + 2)*pV1->z + (-3*s3 + 4*s2 + s)*pV2->z + (s3 - s2)*pV3->z);
	pOut->w = 0.5*((-s3 + 2*s2 - s)*pV0->w + (3*s3 - 5*s2 + 2)*pV1->w + (-3*s3 + 4*s2 + s)*pV2->w + (s3 - s2)*pV3->w);
	
	return pOut;
}

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
DISX_VECTOR4*  DISX_Vec4BaryCentric
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2,
      const DISX_VECTOR4 *pV3, float f, float g)
{
	//*pOut = *pV1 + f *( *pV2 - *pV1 ) + g* (*pV3 - *pV1);
	pOut->x = pV1->x + f *(pV2->x - pV1->x) + g* (pV3->x - pV1->x);
	pOut->y = pV1->y + f *(pV2->y - pV1->y) + g* (pV3->y - pV1->y);
	pOut->z = pV1->z + f *(pV2->z - pV1->z) + g* (pV3->z - pV1->z);
	pOut->w = pV1->w + f *(pV2->w - pV1->w) + g* (pV3->w - pV1->w);

	return pOut;
}

// Transform vector by matrix.
DISX_VECTOR4*  DISX_Vec4Transform
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV, const DISX_MATRIX *pM )
{
	pOut->x = pV->x * pM->_11 + pV->y * pM->_12 + pV->z * pM->_13 + pV->w * pM->_14;
	pOut->y = pV->x * pM->_21 + pV->y * pM->_22 + pV->z * pM->_23 + pV->w * pM->_24;
	pOut->z = pV->x * pM->_31 + pV->y * pM->_32 + pV->z * pM->_33 + pV->w * pM->_34;
	pOut->w = pV->x * pM->_41 + pV->y * pM->_42 + pV->z * pM->_43 + pV->w * pM->_44;

	return pOut;
}
    
// Transform vector array by matrix.
DISX_VECTOR4*  DISX_Vec4TransformArray
    ( DISX_VECTOR4 *pOut, UInt32 OutStride, const DISX_VECTOR4 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n )
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_Vec4Transform( &pOut[ outputIndex ], &pV[inputIndex], pM ); 
		
		outputIndex += OutStride;
		inputIndex += VStride;
	}
	return pOut;
}


//--------------------------
// 4D Matrix
//--------------------------

float  DISX_MatrixDeterminant
    ( const DISX_MATRIX *pM )
{
	float d1 = 	(*pM)._11 * ( (*pM)(1,1) * ((*pM)(2,2) * (*pM)(3,3) - (*pM)(3,2) * (*pM)(2,3)) -
							  (*pM)(1,2) * ((*pM)(2,1) * (*pM)(3,3) - (*pM)(3,1) * (*pM)(2,3)) +
                              (*pM)(1,3) * ((*pM)(2,1) * (*pM)(3,2) - (*pM)(3,1) * (*pM)(2,2)));

	float d2 = 	(*pM)._12 * ( (*pM)(1,0) * ((*pM)(2,2) * (*pM)(3,3) - (*pM)(3,2) * (*pM)(2,3)) -
							  (*pM)(1,2) * ((*pM)(2,0) * (*pM)(3,3) - (*pM)(3,0) * (*pM)(2,3)) +
							  (*pM)(1,3) * ((*pM)(2,0) * (*pM)(3,2) - (*pM)(3,0) * (*pM)(2,2)));

	float d3 = 	(*pM)._13 * ( (*pM)(1,0) * ((*pM)(2,1) * (*pM)(3,3) - (*pM)(3,1) * (*pM)(2,3)) -
							  (*pM)(1,1) * ((*pM)(2,0) * (*pM)(3,3) - (*pM)(3,0) * (*pM)(2,3)) +
							  (*pM)(1,3) * ((*pM)(2,0) * (*pM)(3,1) - (*pM)(3,0) * (*pM)(2,1)));

	float d4 = 	(*pM)._14 * ( (*pM)(1,0) * ((*pM)(2,1) * (*pM)(3,2) - (*pM)(3,1) * (*pM)(2,2)) -
							  (*pM)(1,1) * ((*pM)(2,0) * (*pM)(3,2) - (*pM)(3,0) * (*pM)(2,2)) +
							  (*pM)(1,2) * ((*pM)(2,0) * (*pM)(3,1) - (*pM)(3,0) * (*pM)(2,1)));

	return d1 - d2 + d3 - d4;
}

DIS_RESULT  DISX_MatrixDecompose
    ( DISX_VECTOR3 *pOutScale, DISX_QUATERNION *pOutRotation, 
	  DISX_VECTOR3 *pOutTranslation, const DISX_MATRIX *pM )
{
	// TODO: Can't find exactly how the scale is packed in to the rotation + translation matrix
	// (c+(1-c)x^2)		((1-c)xy - sz)    (1-c)xz + sy   scaleX
	//  (1-c)xy + sz    (c+(1-c)y^2)	  (1-c)yx - sx   scaleY
	//  (1-c)xz-sy       (1-c)yz+sx       c+(1-c)z^2     scaleZ
	//   PX				PY				  PZ

	pOutScale->x = pM->_14;
	pOutScale->y = pM->_24;
	pOutScale->z = pM->_34;

	pOutTranslation->x = pM->_41;
	pOutTranslation->y = pM->_42;
	pOutTranslation->z = pM->_43;

	DISX_QuaternionRotationMatrix(pOutRotation, pM);

	return DIS_FAIL;
}

DISX_MATRIX*  DISX_MatrixTranspose
    ( DISX_MATRIX *pOut, const DISX_MATRIX *pM )
{
	pOut->_11 = pM->_11;  pOut->_12 = pM->_21;  pOut->_13 = pM->_31;  pOut->_14 = pM->_41;
	pOut->_21 = pM->_12;  pOut->_22 = pM->_22;  pOut->_23 = pM->_32;  pOut->_24 = pM->_42;
	pOut->_31 = pM->_13;  pOut->_32 = pM->_23;  pOut->_33 = pM->_33;  pOut->_34 = pM->_43;
	pOut->_41 = pM->_14;  pOut->_42 = pM->_24;  pOut->_43 = pM->_34;  pOut->_44 = pM->_44;

	return pOut;
}

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
DISX_MATRIX*  DISX_MatrixMultiply
    ( DISX_MATRIX *pOut, const DISX_MATRIX *pM1, const DISX_MATRIX *pM2 )
{
	pOut->_11 = pM1->_11 * pM2->_11 + pM1->_12 * pM2->_21 + pM1->_13 * pM2->_31 + pM1->_14 * pM2->_41;
	pOut->_12 = pM1->_11 * pM2->_12 + pM1->_12 * pM2->_22 + pM1->_13 * pM2->_32 + pM1->_14 * pM2->_42;
	pOut->_13 = pM1->_11 * pM2->_13 + pM1->_12 * pM2->_23 + pM1->_13 * pM2->_33 + pM1->_14 * pM2->_43;
	pOut->_14 = pM1->_11 * pM2->_14 + pM1->_12 * pM2->_24 + pM1->_13 * pM2->_34 + pM1->_14 * pM2->_44;

	pOut->_21 = pM1->_21 * pM2->_11 + pM1->_22 * pM2->_21 + pM1->_23 * pM2->_31 + pM1->_24 * pM2->_41;
	pOut->_22 = pM1->_21 * pM2->_12 + pM1->_22 * pM2->_22 + pM1->_23 * pM2->_32 + pM1->_24 * pM2->_42;
	pOut->_23 = pM1->_21 * pM2->_13 + pM1->_22 * pM2->_23 + pM1->_23 * pM2->_33 + pM1->_24 * pM2->_43;
	pOut->_24 = pM1->_21 * pM2->_14 + pM1->_22 * pM2->_24 + pM1->_23 * pM2->_34 + pM1->_24 * pM2->_44;

	pOut->_31 = pM1->_31 * pM2->_11 + pM1->_32 * pM2->_21 + pM1->_33 * pM2->_31 + pM1->_34 * pM2->_41;
	pOut->_32 = pM1->_31 * pM2->_12 + pM1->_32 * pM2->_22 + pM1->_33 * pM2->_32 + pM1->_34 * pM2->_42;
	pOut->_33 = pM1->_31 * pM2->_13 + pM1->_32 * pM2->_23 + pM1->_33 * pM2->_33 + pM1->_34 * pM2->_43;
	pOut->_34 = pM1->_31 * pM2->_14 + pM1->_32 * pM2->_24 + pM1->_33 * pM2->_34 + pM1->_34 * pM2->_44;

	pOut->_41 = pM1->_41 * pM2->_11 + pM1->_42 * pM2->_21 + pM1->_43 * pM2->_31 + pM1->_44 * pM2->_41;
	pOut->_42 = pM1->_41 * pM2->_12 + pM1->_42 * pM2->_22 + pM1->_43 * pM2->_32 + pM1->_44 * pM2->_42;
	pOut->_43 = pM1->_41 * pM2->_13 + pM1->_42 * pM2->_23 + pM1->_43 * pM2->_33 + pM1->_44 * pM2->_43;
	pOut->_44 = pM1->_41 * pM2->_14 + pM1->_42 * pM2->_24 + pM1->_43 * pM2->_34 + pM1->_44 * pM2->_44;
	
	return pOut;
}

// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
DISX_MATRIX*  DISX_MatrixMultiplyTranspose
    ( DISX_MATRIX *pOut, const DISX_MATRIX *pM1, const DISX_MATRIX *pM2 )
{
	DISX_MATRIX temp;
	
	DISX_MatrixMultiply(&temp, pM1, pM2);
	DISX_MatrixTranspose(pOut, &temp);
	
	return pOut;
}


//-----------------------------------------------------------------------------
// Helper function for inverting the matrix
//-----------------------------------------------------------------------------
float Minor( const DISX_MATRIX* pM, const int r0, const int r1, const int r2, 
	                             const int c0, const int c1, const int c2)
{
   return (*pM)(r0,c0) * ((*pM)(r1,c1) * (*pM)(r2,c2) - (*pM)(r2,c1) * (*pM)(r1,c2)) -
          (*pM)(r0,c1) * ((*pM)(r1,c0) * (*pM)(r2,c2) - (*pM)(r2,c0) * (*pM)(r1,c2)) +
          (*pM)(r0,c2) * ((*pM)(r1,c0) * (*pM)(r2,c1) - (*pM)(r2,c0) * (*pM)(r1,c1));
}

// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.
DISX_MATRIX*  DISX_MatrixInverse
    ( DISX_MATRIX *pOut, float *pDeterminant, const DISX_MATRIX *pM )
{

	float det = DISX_MatrixDeterminant(pM);

	if( pDeterminant != NULL )
	{
		*pDeterminant = det;
	}

	float det_recip = 1 / det;

	// Compute adjoint while mulitplying by the reciprocal 
	// of the determinant - TODO:- as above
	pOut->_11 = Minor( pM, 1, 2, 3, 1, 2, 3 ) * det_recip;
    pOut->_12 =-Minor( pM, 0, 2, 3, 1, 2, 3 ) * det_recip;
    pOut->_13 = Minor( pM, 0, 1, 3, 1, 2, 3 ) * det_recip;
    pOut->_14 =-Minor( pM, 0, 1, 2, 1, 2, 3 ) * det_recip;

    pOut->_21 =-Minor( pM, 1, 2, 3, 0, 2, 3 ) * det_recip;
    pOut->_22 = Minor( pM, 0, 2, 3, 0, 2, 3 ) * det_recip;
    pOut->_23 =-Minor( pM, 0, 1, 3, 0, 2, 3 ) * det_recip;
    pOut->_24 = Minor( pM, 0, 1, 2, 0, 2, 3 ) * det_recip;

    pOut->_31 = Minor( pM, 1, 2, 3, 0, 1, 3 ) * det_recip;
    pOut->_32 =-Minor( pM, 0, 2, 3, 0, 1, 3 ) * det_recip;
    pOut->_33 = Minor( pM, 0, 1, 3, 0, 1, 3 ) * det_recip;
    pOut->_34 =-Minor( pM, 0, 1, 2, 0, 1, 3 ) * det_recip;

    pOut->_41 =-Minor( pM, 1, 2, 3, 0, 1, 2 ) * det_recip;
    pOut->_42 = Minor( pM, 0, 2, 3, 0, 1, 2 ) * det_recip;
    pOut->_43 =-Minor( pM, 0, 1, 3, 0, 1, 2 ) * det_recip;
    pOut->_44 = Minor( pM, 0, 1, 2, 0, 1, 2 ) * det_recip;

	return pOut;
}

// Build a matrix which scales by (sx, sy, sz)
DISX_MATRIX*  DISX_MatrixScaling
    ( DISX_MATRIX *pOut, float sx, float sy, float sz )
{
	DISX_MatrixIdentity(pOut);

	pOut->_11 = sx;
	pOut->_22 = sy;
	pOut->_33 = sz;

	return pOut;
}

// Build a matrix which translates by (x, y, z)
DISX_MATRIX*  DISX_MatrixTranslation
    ( DISX_MATRIX *pOut, float x, float y, float z )
{
	DISX_MatrixIdentity(pOut);

	pOut->_41 = x;
	pOut->_42 = y;
	pOut->_43 = z;

	return pOut;
}

// Build a matrix which rotates around the X axis
DISX_MATRIX*  DISX_MatrixRotationX
    ( DISX_MATRIX *pOut, float Angle )
{
	float sinA, cosA;

	sinA = (float)sin(Angle);
	cosA = (float)cos(Angle);

	(*pOut)(0,0) =  1.0F; (*pOut)(1,0) =  0.0F; (*pOut)(2,0) =  0.0F;
	(*pOut)(0,1) =  0.0F; (*pOut)(1,1) =  cosA; (*pOut)(2,1) = -sinA;
	(*pOut)(0,2) =  0.0F; (*pOut)(1,2) =  sinA; (*pOut)(2,2) =  cosA;

	(*pOut)(0,3) = 0.0F; 
	(*pOut)(1,3) = 0.0F; 
	(*pOut)(2,3) = 0.0F;
	(*pOut)(3,0) = 0.0F;
	(*pOut)(3,1) = 0.0F;
	(*pOut)(3,2) = 0.0F;
	(*pOut)(3,3) = 1.0F;

	return pOut;
}

// Build a matrix which rotates around the Y axis
DISX_MATRIX*  DISX_MatrixRotationY
    ( DISX_MATRIX *pOut, float Angle )
{
	float sinA, cosA;

	sinA = (float)sin(Angle);
	cosA = (float)cos(Angle);

    (*pOut)(0,0) =  cosA; (*pOut)(1,0) =  0.0F; (*pOut)(2,0) =  sinA;
    (*pOut)(0,1) =  0.0F; (*pOut)(1,1) =  1.0F; (*pOut)(2,1) =  0.0F;
    (*pOut)(0,2) = -sinA; (*pOut)(1,2) =  0.0F; (*pOut)(2,2) =  cosA;

	(*pOut)(0,3) = 0.0F; 
	(*pOut)(1,3) = 0.0F; 
	(*pOut)(2,3) = 0.0F;
	(*pOut)(3,0) = 0.0F;
	(*pOut)(3,1) = 0.0F;
	(*pOut)(3,2) = 0.0F;
	(*pOut)(3,3) = 1.0F;

	return pOut;
}

// Build a matrix which rotates around the Z axis
DISX_MATRIX*  DISX_MatrixRotationZ
    ( DISX_MATRIX *pOut, float Angle )
{
	float sinA, cosA;

	sinA = (float)sin(Angle);
	cosA = (float)cos(Angle);

    (*pOut)(0,0) =  cosA; (*pOut)(1,0) = -sinA; (*pOut)(2,0) =  0.0F;
    (*pOut)(0,1) =  sinA; (*pOut)(1,1) =  cosA; (*pOut)(2,1) =  0.0F;
    (*pOut)(0,2) =  0.0F; (*pOut)(1,2) =  0.0F; (*pOut)(2,2) =  1.0F;

	(*pOut)(0,3) = 0.0F; 
	(*pOut)(1,3) = 0.0F; 
	(*pOut)(2,3) = 0.0F;
	(*pOut)(3,0) = 0.0F;
	(*pOut)(3,1) = 0.0F;
	(*pOut)(3,2) = 0.0F;
	(*pOut)(3,3) = 1.0F;

	return pOut;
}

// Build a matrix which rotates around an arbitrary axis
DISX_MATRIX*  DISX_MatrixRotationAxis
    ( DISX_MATRIX *pOut, const DISX_VECTOR3 *pV, float Angle )
{
	float sinA, cosA;
	float invCosA;
	float x, y, z;
	float xSq, ySq, zSq;

	DISX_VECTOR3 axis;
		
	DISX_Vec3Normalize(&axis, pV);
	
	sinA = (float)sin(Angle);
	cosA = (float)cos(Angle);
	invCosA = 1.0F - cosA;

	x = axis.x;
	y = axis.y;
	z = axis.z;

	xSq = x * x;
	ySq = y * y;
	zSq = z * z;

	(*pOut)._11 = (invCosA * xSq) + (cosA);
	(*pOut)._21 = (invCosA * x * y) - (sinA * z );
	(*pOut)._31 = (invCosA * x * z) + (sinA * y );
	(*pOut)._41 = 0.0F;

	(*pOut)._12 = (invCosA * x * y) + (sinA * z);
	(*pOut)._22 = (invCosA * ySq) + (cosA);
	(*pOut)._32 = (invCosA * y * z) - (sinA * x);
	(*pOut)._42 = 0.0F;

	(*pOut)._13 = (invCosA * x * z) - (sinA * y);
	(*pOut)._23 = (invCosA * y * z) + (sinA * x);
	(*pOut)._33 = (invCosA * zSq) + (cosA);
	(*pOut)._43 = 0.0F;

	(*pOut)._14 = 0.0F;
	(*pOut)._24 = 0.0F;
	(*pOut)._34 = 0.0F;
	(*pOut)._44 = 1.0F;

	return pOut;
}

// Build a matrix from a quaternion
DISX_MATRIX*  DISX_MatrixRotationQuaternion
    ( DISX_MATRIX *pOut, const DISX_QUATERNION *pQ)
{
    float xx = pQ->x*pQ->x,   xy = pQ->x*pQ->y,   xz = pQ->x*pQ->z,   xw = pQ->x*pQ->w;
    float yy = pQ->y*pQ->y,   yz = pQ->y*pQ->z,   yw = pQ->y*pQ->w;
    float zz = pQ->z*pQ->z,   zw = pQ->z*pQ->w;
    float ww = pQ->w*pQ->w;

    pOut->_11 = xx-yy-zz+ww;
    pOut->_12 = 2.0f*(xy-zw);
    pOut->_13 = 2.0f*(xz+yw);

    pOut->_21 = 2.0f*(xy+zw);
    pOut->_22 = -xx+yy-zz+ww;
    pOut->_23 = 2.0f*(yz-xw);

    pOut->_31 = 2.0f*(xz-yw);
    pOut->_32 = 2.0f*(yz+xw);
    pOut->_33 = -xx-yy+zz+ww;

    pOut->_14 = pOut->_41 = 0.0f;
    pOut->_24 = pOut->_42 = 0.0f;
    pOut->_34 = pOut->_43 = 0.0f;
    pOut->_44 = xx+yy+zz+ww;
	
	return pOut;
}

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
DISX_MATRIX*  DISX_MatrixRotationYawPitchRoll
    ( DISX_MATRIX *pOut, float Yaw, float Pitch, float Roll )

{
	DISX_MATRIX YawMatrix, PitchMatrix, RollMatrix;
	
	DISX_MatrixRotationY( &YawMatrix, Yaw );
	DISX_MatrixRotationX( &PitchMatrix, Pitch);
	DISX_MatrixRotationZ( &RollMatrix, Roll );

	// Microsoft Documentation
	*pOut =  RollMatrix * PitchMatrix * YawMatrix;

	return pOut;
}

// Build transformation matrix.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
DISX_MATRIX*  DISX_MatrixTransformation
    ( DISX_MATRIX *pOut, const DISX_VECTOR3 *pScalingCenter,
      const DISX_QUATERNION *pScalingRotation, const DISX_VECTOR3 *pScaling,
      const DISX_VECTOR3 *pRotationCenter, const DISX_QUATERNION *pRotation,
      const DISX_VECTOR3 *pTranslation)
{
	// TODO
/*
Mout = (Msc)-1 * (Msr)-1* Ms * Msr * Msc * (Mrc)-1* Mr * Mrc * Mt
where:
Mout = output matrix (pOut)
Msc = scaling center matrix (pScalingCenter)
Msr = scaling rotation matrix (pScalingRotation)
Ms = scaling matrix (pScaling)
Mrc = center of rotation matrix (pRotationCenter)
Mr = rotation matrix (pRotation)
Mt = translation matrix (pTranslation)
*/
	// I am not really sure if this is a scaling matrix, pScalingCenter would
	// appear to be a vector location. I have similar problems with some
	// of the other variables.
	DISX_MATRIX Msc;
	DISX_MatrixTranslation(&Msc, pScalingCenter->x, pScalingCenter->y, pScalingCenter->z);
	DISX_MATRIX MscInv;
	DISX_MatrixInverse(&MscInv, 0, &Msc);

	DISX_MATRIX Msr;
	DISX_MatrixRotationQuaternion(&Msr, pScalingRotation);
	DISX_MATRIX MsrInv;
	DISX_MatrixInverse(&MsrInv, 0, &Msr);

	DISX_MATRIX Ms;
	DISX_MatrixScaling(&Ms, pScaling->x, pScaling->y, pScaling->z);

	DISX_MATRIX Mrc;
	DISX_MatrixTranslation(&Mrc, pRotationCenter->x, pRotationCenter->y, pRotationCenter->z);
	DISX_MATRIX MrcInv;
	DISX_MatrixInverse( &MrcInv, 0, &Mrc);

	DISX_MATRIX Mr;
	DISX_MatrixRotationQuaternion( &Mr, pRotation );

	DISX_MATRIX Mt;
	DISX_MatrixTranslation(&Mt, pTranslation->x, pTranslation->y, pTranslation->z); 

	// Microsoft Documentation
	// Mout = (Msc)-1 * (Msr)-1* Ms * Msr * Msc * (Mrc)-1* Mr * Mrc * Mt
	*pOut = MscInv * MsrInv * Ms * Msr * Msc * MrcInv* Mr * Mrc * Mt;
	return pOut;
}

// Build 2D transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
DISX_MATRIX*  DISX_MatrixTransformation2D
    ( DISX_MATRIX *pOut, const DISX_VECTOR2* pScalingCenter, 
      float ScalingRotation, const DISX_VECTOR2* pScaling, 
      const DISX_VECTOR2* pRotationCenter, float Rotation, 
      const DISX_VECTOR2* pTranslation)
{
	DISX_MATRIX Msc;
	DISX_MatrixScaling(&Msc, pScalingCenter->x, pScalingCenter->y, 0.0f);
	DISX_MATRIX MscInv;
	DISX_MatrixInverse(&MscInv, 0, &Msc);

	DISX_MATRIX Msr;
	DISX_MatrixRotationZ(&Msr, ScalingRotation);
	DISX_MATRIX MsrInv;
	DISX_MatrixInverse(&MsrInv, 0, &Msr);

	DISX_MATRIX Ms;
	DISX_MatrixScaling(&Ms, pScaling->x, pScaling->y, 0.0f);

	DISX_MATRIX Mrc;
	DISX_MatrixTranslation(&Mrc, pRotationCenter->x, pRotationCenter->y, 0.0f);
	DISX_MATRIX MrcInv;
	DISX_MatrixInverse( &MrcInv, 0, &Mrc);

	DISX_MATRIX Mr;
	DISX_MatrixRotationZ(&Mr, Rotation );

	DISX_MATRIX Mt;
	DISX_MatrixTranslation(&Mt, pTranslation->x, pTranslation->y, 0.0f); 

	// Microsoft Documentation
	// Mout = (Msc)-1 * (Msr)-1* Ms * Msr * Msc * (Mrc)-1* Mr * Mrc * Mt
	*pOut = MscInv * MsrInv * Ms * Msr * Msc * MrcInv* Mr * Mrc * Mt;
	return pOut;
	
}

// Build affine transformation matrix.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
DISX_MATRIX*  DISX_MatrixAffineTransformation
    ( DISX_MATRIX *pOut, float Scaling, const DISX_VECTOR3 *pRotationCenter,
      const DISX_QUATERNION *pRotation, const DISX_VECTOR3 *pTranslation)
{
	/* Microsoft Documentation
Mout = Ms * (Mrc)-1 * Mr * Mrc * Mt
where:
Mout = output matrix (pOut)
Ms = scaling matrix (Scaling)
Mrc = center of rotation matrix (pRotationCenter)
Mr = rotation matrix (pRotation)
Mt = translation matrix (pTranslation)
	*/

	DISX_MATRIX Ms;
	DISX_MatrixScaling(&Ms, Scaling, Scaling, Scaling);
	
	DISX_MATRIX Mrc;
	DISX_MatrixTranslation( &Mrc, pRotationCenter->x, pRotationCenter->y, pRotationCenter->z);
	
	DISX_MATRIX MrcInv;
	DISX_MatrixInverse(&MrcInv, 0, &Mrc);
	
	DISX_MATRIX Mr;
	DISX_MatrixRotationQuaternion( &Mr, pRotation );
	
	DISX_MATRIX Mt;
	DISX_MatrixTranslation( &Mt, pTranslation->x, pTranslation->y, pTranslation->z );

	
	*pOut = Ms * MrcInv * Mr * Mrc * Mt;

	return pOut;
}

// Build 2D affine transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
DISX_MATRIX*  DISX_MatrixAffineTransformation2D
    ( DISX_MATRIX *pOut, float Scaling, const DISX_VECTOR2* pRotationCenter, 
      float Rotation, const DISX_VECTOR2* pTranslation)
{
	// TODO : Needs to be tested
	DISX_MATRIX Ms;
	DISX_MatrixScaling(&Ms, Scaling, Scaling, Scaling);
	
	DISX_MATRIX Mrc;
	DISX_MatrixTranslation( &Mrc, pRotationCenter->x, pRotationCenter->y, 0.0f);
	
	DISX_MATRIX MrcInv;
	DISX_MatrixInverse(&MrcInv, 0, &Mrc);
	
	DISX_MATRIX Mr;
	DISX_MatrixRotationZ( &Mr, Rotation );
	
	DISX_MATRIX Mt;
	DISX_MatrixTranslation( &Mt, pTranslation->x, pTranslation->y, 0.0f );

	
	*pOut = Ms * MrcInv * Mr * Mrc * Mt;
	
	return pOut;
}



// Build a lookat matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixLookAtRH
    ( DISX_MATRIX *pOut, const DISX_VECTOR3 *pEye, const DISX_VECTOR3 *pAt,
      const DISX_VECTOR3 *pUp )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;
	D3DXVECTOR3 eye(pEye->x, pEye->y, pEye->z);
	D3DXVECTOR3 at(pAt->x, pAt->y, pAt->z);
	D3DXVECTOR3 up(pUp->x, pUp->y, pUp->z);
	D3DXMatrixLookAtRH(&mat, &eye, &at, &up);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
	DISX_VECTOR3 F = *pAt - *pEye;
	DISX_Vec3Normalize( &F, &F );

	DISX_VECTOR3 upNorm;
	DISX_Vec3Normalize( &upNorm, pUp );

	DISX_VECTOR3 s;
	DISX_Vec3Cross(&s, &F, &upNorm );
	
	DISX_VECTOR3 u;
	DISX_Vec3Cross(&u, &s, &F );

	pOut->_11 = s.x;  pOut->_21 = s.y;  pOut->_31 = s.z;  pOut->_41 = 0.0F;
	pOut->_12 = u.x;  pOut->_22 = u.y;  pOut->_32 = u.z;  pOut->_42 = 0.0F;
	pOut->_13 =-F.x;  pOut->_23 =-F.y;  pOut->_33 =-F.z;  pOut->_43 = 0.0F;
	pOut->_14 = 0.0F; pOut->_24 = 0.0F; pOut->_34 = 0.0F; pOut->_44 = 1.0F;
#endif
	return pOut;
}

// Build a lookat matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixLookAtLH
    ( DISX_MATRIX *pOut, const DISX_VECTOR3 *pEye, const DISX_VECTOR3 *pAt,
      const DISX_VECTOR3 *pUp )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;
	D3DXVECTOR3 eye(pEye->x, pEye->y, pEye->z);
	D3DXVECTOR3 at(pAt->x, pAt->y, pAt->z);
	D3DXVECTOR3 up(pUp->x, pUp->y, pUp->z);
	D3DXMatrixLookAtLH(&mat, &eye, &at, &up);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
	DISX_VECTOR3 F = *pAt - *pEye;
	DISX_Vec3Normalize( &F, &F );

	DISX_VECTOR3 upNorm;
	DISX_Vec3Normalize( &upNorm, pUp );

	DISX_VECTOR3 s;
	DISX_Vec3Cross(&s, &upNorm, &F );
	
	DISX_VECTOR3 u = upNorm;
	DISX_Vec3Cross(&u, &F, &s);

/*	pOut->_11 = s.x;  pOut->_21 = s.y;  pOut->_31 = s.z;  pOut->_41 = 0.0F;
	pOut->_12 = u.x;  pOut->_22 = u.y;  pOut->_32 = u.z;  pOut->_42 = 0.0F;
	pOut->_13 =-F.x;  pOut->_23 =-F.y;  pOut->_33 =-F.z;  pOut->_43 = 0.0F;
	pOut->_14 = 0.0F; pOut->_24 = 0.0F; pOut->_34 = 0.0F; pOut->_44 = 1.0F;*/

	pOut->_11 = s.x;  pOut->_21 = s.y;  pOut->_31 = s.z;  pOut->_41 = 0.0F;
	pOut->_12 = u.x;  pOut->_22 = u.y;  pOut->_32 = u.z;  pOut->_42 = 0.0F;
	pOut->_13 =-F.x;  pOut->_23 =-F.y;  pOut->_33 =-F.z;  pOut->_43 = 0.0F;
	pOut->_14 = 0.0F; pOut->_24 = 0.0F; pOut->_34 = 0.0F; pOut->_44 = 1.0F;
#endif
	return pOut;
}

// Build a perspective projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveRH
    ( DISX_MATRIX *pOut, float w, float h, float zn, float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixPerspectiveRH(&mat, w,h,zn,zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
	/*
		2*zn/w  0       0              0
		0       2*zn/h  0              0
		0       0       zf/(zn-zf)    -1
		0       0       zn*zf/(zn-zf)  0
	*/
	float _11 = 2*zn  / w;
	float _22 = 2*zn  / h;
	float _33 =    zf / (zn-zf);
	float _34 = zn*zf / (zn-zf);
	
	DISX_MatrixIdentity(pOut);

	pOut->_11 = _11;
	pOut->_22 = _22;
	pOut->_33 = _33;
	pOut->_43 = _34;
	pOut->_34 = -1.0f;
	pOut->_44 = 0.0f;
	
#endif	
	return pOut;

}

// Build a perspective projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveLH
    ( DISX_MATRIX *pOut, float w, float h, float zn, float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixPerspectiveLH(&mat, w, h, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
	/*
	2*zn/w  0       0              0
	0       2*zn/h  0              0
	0       0       zf/(zf-zn)     1
	0       0       zn*zf/(zn-zf)  0
	*/

	DISX_MatrixIdentity(pOut);

	pOut->_11 = 2*zn  / w;
	pOut->_22 = 2*zn  / h;
	pOut->_33 = zf / (zf-zn);
	pOut->_43 = zn*zf / (zn-zf);
	pOut->_34 = 1.0f;
	pOut->_44 = 0.0f;
#endif
	return pOut;
}

// Build a perspective projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveFovRH
    ( DISX_MATRIX *pOut, float fovy, float Aspect, float zn, float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixPerspectiveFovRH(&mat, fovy, Aspect, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
	/*
	xScale     0          0              0
	0        yScale       0              0
	0        0        zf/(zn-zf)        -1
	0        0        zn*zf/(zn-zf)      0
	where:
	yScale = cot(fovY/2)
    
	xScale = yScale / aspect ratio
*/
	DISX_MatrixIdentity(pOut);

	float angle = fovy/2;
	float cot = (float) (cosf(angle) / sinf(angle));
	float yScale = cot;
	float xScale = yScale / Aspect;
	pOut->_11 = xScale;
	pOut->_22= yScale;
	pOut->_33 = zf / (zn-zf);
	pOut->_43 = zn*zf / (zn-zf);
	pOut->_34 = -1.0f;
#endif
	return pOut;
}

// Build a perspective projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveFovLH
    ( DISX_MATRIX *pOut, float fovy, float Aspect, float zn, float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixPerspectiveFovLH(&mat, fovy, Aspect, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
/*
xScale     0          0               0
0        yScale       0               0
0          0       zf/(zf-zn)         1
0          0       -zn*zf/(zf-zn)     0
where:
yScale = cot(fovY/2)

xScale = yScale / aspect ratio

*/
	DISX_MatrixIdentity(pOut);

	float angle = fovy/2;
	float cot = (float) (cosf(angle) / sinf(angle));
	float yScale = cot;
	float xScale = yScale / Aspect;
	pOut->_11 = xScale;
	
	pOut->_22 = yScale;
	pOut->_33 = zf / (zf-zn);
	pOut->_43 = -zn*zf / (zf-zn);
	pOut->_34 = 1.0f;
	pOut->_44 = 0.0f;
#endif
	return pOut;
}

// Build a perspective projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveOffCenterRH
    ( DISX_MATRIX *pOut, float l, float r, float b, float t, float zn,
      float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixPerspectiveOffCenterRH(&mat, l,r,b,t, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
/*
2*zn/(r-l)   0            0                0
0            2*zn/(t-b)   0                0
(l+r)/(r-l)  (t+b)/(t-b)  zf/(zn-zf)      -1
0            0            zn*zf/(zn-zf)    0
*/

	DISX_MatrixIdentity(pOut);

	pOut->_11 = 2 * zn / (r-1);
	pOut->_13 = (1+r)/(r-1);
	pOut->_22 = 2 * zn / (t-b);
	pOut->_23 = (t+b) / (t-b);
	pOut->_33 = zf / (zn-zf);
	pOut->_43 = (zn*zf) / (zn-zf);
	pOut->_34 = -1.0f;
	pOut->_44 = 0.0f;
#endif
	return pOut;
}

// Build a perspective projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveOffCenterLH
    ( DISX_MATRIX *pOut, float l, float r, float b, float t, float zn,
      float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixPerspectiveOffCenterLH(&mat, l, r, b, t, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
/*
2*zn/(r-l)   0            0              0
0            2*zn/(t-b)   0              0
(l+r)/(l-r)  (t+b)/(b-t)  zf/(zf-zn)     1
0            0            zn*zf/(zn-zf)  0
*/
	DISX_MatrixIdentity(pOut);

	pOut->_11 = 2 * zn / (r-1);
	pOut->_31 = (1+r)/(1-r);
	pOut->_22 = 2 * zn / (t-b);
	pOut->_32 = (t+b) / (b-t);
	pOut->_33 = zf / (zf-zn);
	pOut->_43 = (zn*zf) / (zn-zf);
	pOut->_34 = 1.0f;
	pOut->_44 = 0.0f;
#endif	
	return pOut;
}

// Build an ortho projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixOrthoRH
    ( DISX_MATRIX *pOut, float w, float h, float zn, float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixOrthoRH(&mat, w,h, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
/*
2/w  0    0           0
0    2/h  0           0
0    0    1/(zn-zf)   0
0    0    zn/(zn-zf)  1
*/
	DISX_MatrixIdentity(pOut);

	pOut->_11 = 2/w;
	pOut->_22 = 2/h;
	pOut->_33 = 1/(zn-zf);
	pOut->_43 = zn/(zn-zf);
	pOut->_44 = 1.0f;
#endif
	return pOut;
}

// Build an ortho projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixOrthoLH
    ( DISX_MATRIX *pOut, float w, float h, float zn, float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixOrthoLH(&mat, w, h, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
/*
2/w  0    0           0
0    2/h  0           0
0    0    1/(zf-zn)   0
0    0   -zn/(zf-zn)  1
*/
	DISX_MatrixIdentity(pOut);

	pOut->_11 = 2/w;
	pOut->_22 = 2/h;
	pOut->_33 = 1/(zf-zn);
	pOut->_43 = -zn/(zf-zn);
	pOut->_44 = 1.0f;
#endif
	return pOut;
}

// Build an ortho projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixOrthoOffCenterRH
    ( DISX_MATRIX *pOut, float l, float r, float b, float t, float zn,
      float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixOrthoOffCenterRH(&mat, l,r,b,t, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
/*
2*zn/(r-l)   0            0                0
0            2*zn/(t-b)   0                0
(l+r)/(r-l)  (t+b)/(t-b)  zf/(zn-zf)      -1
0            0            zn*zf/(zn-zf)    0
*/
	DISX_MatrixIdentity(pOut);
	
	pOut->_11 = 2*zn/(r-l);
	pOut->_31 = (l+r)/(r-1);
	pOut->_22 = 2*zn/(t-b);
	pOut->_32 = (t+b)/(t-b);
	pOut->_33 = zf/(zn-zf);
	pOut->_43 = zn*zf/(zn-zf);
	pOut->_34 = -1.0f;
#endif
	return pOut;
}

// Build an ortho projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixOrthoOffCenterLH
    ( DISX_MATRIX *pOut, float l, float r, float b, float t, float zn,
      float zf )
{
#ifdef DEBUG_ME
	D3DXMATRIX mat;

	D3DXMatrixOrthoOffCenterLH(&mat, l, r, b, t, zn, zf);
	CopyD3DXMatrixToDISX(&mat, pOut);
#else
/*
2*zn/(r-l)   0            0              0
0            2*zn/(t-b)   0              0
(l+r)/(l-r)  (t+b)/(b-t)  zf/(zf-zn)     1
0            0            zn*zf/(zn-zf)  0
*/
	DISX_MatrixIdentity(pOut);
	
	pOut->_11 = 2*zn/(r-l);
	pOut->_31 = (l+r)/(l-r);
	pOut->_22 = 2*zn/(t-b);
	pOut->_32 = (t+b)/(b-t);
	pOut->_33 = zf/(zf-zn);
	pOut->_43 = zn*zf/(zn-zf);
	pOut->_34 = 1.0f;
#endif
	return pOut;
}

// Build a matrix which flattens geometry into a plane, as if casting
// a shadow from a light.
DISX_MATRIX*  DISX_MatrixShadow
    ( DISX_MATRIX *pOut, const DISX_VECTOR4 *pLight,
      const DISX_PLANE *pPlane )
{
/*
P = normalize(Plane);
L = Light;
d = -dot(P, L)
    
P.a * L.x + d  P.a * L.y      P.a * L.z      P.a * L.w  
P.b * L.x      P.b * L.y + d  P.b * L.z      P.b * L.w  
P.c * L.x      P.c * L.y      P.c * L.z + d  P.c * L.w  
P.d * L.x      P.d * L.y      P.d * L.z      P.d * L.w + d
*/
	DISX_PLANE P;
	DISX_PlaneNormalize(&P, pPlane);

	
	float d = DISX_PlaneDot( &P, pLight );

	pOut->_11 = P.a * pLight->x + d;  
	pOut->_12 = P.a * pLight->y;      
	pOut->_13 = P.a * pLight->z;      
	pOut->_14 = P.a * pLight->w;  

	pOut->_21 = P.b * pLight->x;      
	pOut->_22 = P.b * pLight->y + d;  
	pOut->_23 = P.b * pLight->z;      
	pOut->_24 = P.b * pLight->w;

	pOut->_31 = P.c * pLight->x;      
	pOut->_32 = P.c * pLight->y;      
	pOut->_33 = P.c * pLight->z + d;  
	pOut->_34 = P.c * pLight->w;

	pOut->_41 = P.d * pLight->x;      
	pOut->_42 = P.d * pLight->y;      
	pOut->_34 = P.d * pLight->z;      
	pOut->_44 = P.d * pLight->w + d;

	return pOut;
}

// Build a matrix which reflects the coordinate system about a plane
DISX_MATRIX*  DISX_MatrixReflect
    ( DISX_MATRIX *pOut, const DISX_PLANE *pPlane )
{
/*
P = normalize(Plane);
    
-2 * P.a * P.a + 1  -2 * P.b * P.a      -2 * P.c * P.a        0
-2 * P.a * P.b      -2 * P.b * P.b + 1  -2 * P.c * P.b        0
-2 * P.a * P.c      -2 * P.b * P.c      -2 * P.c * P.c + 1    0
-2 * P.a * P.d      -2 * P.b * P.d      -2 * P.c * P.d        1
*/
	DISX_PLANE P;
	DISX_PlaneNormalize(&P, pPlane);

	pOut->_11 = -2 * P.a * P.a + 1;
	pOut->_12 = -2 * P.b * P.a;
	pOut->_13 = -2 * P.c * P.a;
	pOut->_14 = 0.0f;

	pOut->_21 = -2 * P.a * P.b;
	pOut->_22 = -2 * P.b * P.b + 1;
	pOut->_23 = -2 * P.c * P.b;
	pOut->_24 = 0.0f;

	pOut->_31 = -2 * P.a * P.c;
	pOut->_32 = -2 * P.b * P.c;
	pOut->_33 = -2 * P.c * P.c + 1;
	pOut->_34 = 0.0f;

	pOut->_41 = -2 * P.a * P.d;
	pOut->_42 = -2 * P.b * P.d;
	pOut->_43 = -2 * P.c * P.d;
	pOut->_44 = 1.0f;

	return pOut;
}





//--------------------------
// Quaternion
//--------------------------

// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
void  DISX_QuaternionToAxisAngle
    ( const DISX_QUATERNION *pQ, DISX_VECTOR3 *pAxis, float *pAngle )
{
/*
	Note: This code was taken from http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q60
    quaternion_normalise( |X,Y,Z,W| );
    cos_a = W;
    angle = acos( cos_a ) * 2;
    sin_a = sqrt( 1.0 - cos_a * cos_a );
    if ( fabs( sin_a ) < 0.0005 ) sin_a = 1;
    axis -> x = X / sin_a;
    axis -> y = Y / sin_a;
    axis -> z = Z / sin_a;
*/
	DISX_QUATERNION qNorm;
	DISX_QuaternionNormalize(&qNorm, pQ);

	float cosAngle = qNorm.w;

	*pAngle = acos( cosAngle ) * 2;

	float sinAngle = sqrt( 1.0f - cosAngle*cosAngle );

	if( fabs( sinAngle ) < 0.0005f ) sinAngle = 1.0f;

	pAxis->x = qNorm.x / sinAngle;
	pAxis->y = qNorm.y / sinAngle;
	pAxis->z = qNorm.z / sinAngle;

}

// Build a quaternion from a rotation matrix.
DISX_QUATERNION*  DISX_QuaternionRotationMatrix
    ( DISX_QUATERNION *pOut, const DISX_MATRIX *pM)
{
#define fmax( a, b) (a>b?a:b)
    float diag1 = + pM->_11 - pM->_22 - pM->_33 + pM->_44;
    float diag2 = - pM->_11 + pM->_22 - pM->_33 + pM->_44;
    float diag3 = - pM->_11 - pM->_22 + pM->_33 + pM->_44;
    float diag4 = + pM->_11 + pM->_22 + pM->_33 + pM->_44;
    
    float maxVal = fmax( diag1, fmax( diag2, fmax( diag3, diag4 ) ) );
    float d   = 1 / ( 2.0f * (float)sqrtf( maxVal ) );

    if( diag1 == maxVal )
    {
        pOut->x = maxVal * d;
        pOut->y = ( pM->_21 + pM->_12 ) * d;
        pOut->z = ( pM->_13 + pM->_31 ) * d;
        pOut->w = ( pM->_32 - pM->_23 ) * d;
    }
    else if ( diag2 == maxVal )
    {
        pOut->x = ( pM->_21 + pM->_12 ) * d;
        pOut->y = maxVal * d;
        pOut->z = ( pM->_32 + pM->_23 ) * d;
        pOut->w = ( pM->_13 - pM->_31 ) * d;
    }
    else if( diag3 == maxVal )
    {
        pOut->x = ( pM->_13 + pM->_31 ) * d;
        pOut->y = ( pM->_32 + pM->_23 ) * d;
        pOut->z = maxVal * d;
        pOut->w = ( pM->_21 - pM->_12 ) * d;
    }
    else if( diag4 == maxVal )
    {
        pOut->x = ( pM->_32 - pM->_23 ) * d;
        pOut->y = ( pM->_13 - pM->_31 ) * d;
        pOut->z = ( pM->_21 - pM->_12 ) * d;
        pOut->w = maxVal * d;
    }

    if( pOut->w < 0.0f )
    {
        pOut->x = -pOut->x;   
		pOut->y = -pOut->y;   
		pOut->z = -pOut->z;   
		pOut->w = -pOut->w;
    }
#undef fmax

	return pOut;
}

// Rotation about arbitrary axis.
DISX_QUATERNION*  DISX_QuaternionRotationAxis
    ( DISX_QUATERNION *pOut, const DISX_VECTOR3 *pV, float Angle )
{
/*
	TODO:
*/
	DISX_VECTOR3 Axis;
    DISX_Vec3Normalize(&Axis, pV);

    float sinAngle = sin( Angle / 2 );
    float cosAngle = cos( Angle / 2 );

	DISX_QUATERNION rotQuat;
    rotQuat.x    = Axis.x * sinAngle;
    rotQuat.y    = Axis.y * sinAngle;
    rotQuat.z    = Axis.z * sinAngle;
    rotQuat.w    = cosAngle;

	*pOut = rotQuat * (*pOut);
	//DISX_QuaternionMultiply( pOut, &rotQuat, pOut );
	
	return pOut;
}

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
DISX_QUATERNION*  DISX_QuaternionRotationYawPitchRoll
    ( DISX_QUATERNION *pOut, float Yaw, float Pitch, float Roll )
{
	DISX_MATRIX matRot;
	DISX_MatrixRotationYawPitchRoll( &matRot, Yaw, Pitch, Roll );

	DISX_QuaternionRotationMatrix( pOut, &matRot );

	return pOut;
}

// Quaternion multiplication.  The result represents the rotation Q2
// followed by the rotation Q1.  (Out = Q2 * Q1)
DISX_QUATERNION*  DISX_QuaternionMultiply
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ1,
      const DISX_QUATERNION *pQ2 )
{
    float Dx =   pQ1->x*pQ2->w + pQ1->y*pQ2->z - pQ1->z*pQ2->y + pQ1->w*pQ2->x;
    float Dy = - pQ1->x*pQ2->z + pQ1->y*pQ2->w + pQ1->z*pQ2->x + pQ1->w*pQ2->y;
    float Dz =   pQ1->x*pQ2->y - pQ1->y*pQ2->x + pQ1->z*pQ2->w + pQ1->w*pQ2->z;
    float Dw = - pQ1->x*pQ2->x - pQ1->y*pQ2->y - pQ1->z*pQ2->z + pQ1->w*pQ2->w;

    pOut->x = Dx; pOut->y = Dy; pOut->z = Dz; pOut->w = Dw;

	return pOut;

}

DISX_QUATERNION*  DISX_QuaternionNormalize
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ )
{
	float magnitude = sqrt(pQ->x*pQ->x + pQ->y*pQ->y + pQ->z*pQ->z +pQ->w*pQ->w);
	float recip = 1/ magnitude;
	
	pOut->x = pQ->x * recip;
	pOut->y = pQ->y * recip;
	pOut->z = pQ->z * recip;
	pOut->w = pQ->w * recip;

	return pOut;
}

// Conjugate and re-norm
DISX_QUATERNION*  DISX_QuaternionInverse
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ )
{	
    pOut->w =  pQ->w;
    pOut->x = -pQ->x;
    pOut->y = -pQ->y;
    pOut->z = -pQ->z;

	DISX_QuaternionNormalize(pOut, pOut);

	return pOut;
}

// Expects unit quaternions.
// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
DISX_QUATERNION*  DISX_QuaternionLn
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ )
{
	// TODO
	return pOut;
}

// Expects pure quaternions. (w == 0)  w is ignored in calculation.
// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
DISX_QUATERNION*  DISX_QuaternionExp
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ )
{
	// TODO
	return pOut;
}
      
// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
// Expects unit quaternions.
DISX_QUATERNION*  DISX_QuaternionSlerp
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ1,
      const DISX_QUATERNION *pQ2, float t )
{
	float fScale1;
    float fScale2;

    // Compute dot product, aka cos(theta):
    float fCosTheta = pQ1->x*pQ2->x + pQ1->y*pQ2->y + pQ1->z*pQ2->z + pQ1->w*pQ2->w;

	DISX_QUATERNION A = *pQ1;
	DISX_QUATERNION B = *pQ2;

    if( fCosTheta < 0.0f )
    {
        // Flip quaternion
        A.x = -A.x; A.y = -A.y; A.z = -A.z; A.w = -A.w;
        fCosTheta = -fCosTheta;
    }

    if( fCosTheta + 1.0f > 0.05f )
    {
		// lerp if number is small to avoid floating point errors
		if( 1.0f - fCosTheta < 0.05f )
        {
            fScale1 = 1.0f - t;
            fScale2 = t;
        }
        else 
        {
            float fTheta    = (float)acos( fCosTheta );
            float fSinTheta = (float)sin( fTheta );
            
            fScale1 = (float)sin( fTheta * (1.0f-t) ) / fSinTheta;
            fScale2 = (float)sin( fTheta * t ) / fSinTheta;
        }
    }
    else
    {
        B.x = -A.y;
        B.y =  A.x;
        B.z = -A.w;
        B.w =  A.z;
        fScale1 = (float)sin( DISX_PI * (0.5f - t) );
        fScale2 = (float)sin( DISX_PI * t );
    }

    pOut->x = fScale1 * A.x + fScale2 * B.x;
    pOut->y = fScale1 * A.y + fScale2 * B.y;
    pOut->z = fScale1 * A.z + fScale2 * B.z;
    pOut->w = fScale1 * A.w + fScale2 * B.w;

	return pOut;
}

// Spherical quadrangle interpolation.
// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
DISX_QUATERNION*  DISX_QuaternionSquad
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ1,
      const DISX_QUATERNION *pA, const DISX_QUATERNION *pB,
      const DISX_QUATERNION *pC, float t )
{
	// TODO
	return pOut;
}

// Setup control points for spherical quadrangle interpolation
// from Q1 to Q2.  The control points are chosen in such a way 
// to ensure the continuity of tangents with adjacent segments.
void  DISX_QuaternionSquadSetup
    ( DISX_QUATERNION *pAOut, DISX_QUATERNION *pBOut, DISX_QUATERNION *pCOut,
      const DISX_QUATERNION *pQ0, const DISX_QUATERNION *pQ1, 
      const DISX_QUATERNION *pQ2, const DISX_QUATERNION *pQ3 )
{
	// TODO
}

// Barycentric interpolation.
// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
DISX_QUATERNION*  DISX_QuaternionBaryCentric
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ1,
      const DISX_QUATERNION *pQ2, const DISX_QUATERNION *pQ3,
      float f, float g )
{
	// todo
	return pOut;
}

//--------------------------
// Plane
//--------------------------


// Normalize plane (so that |a,b,c| == 1)
DISX_PLANE*  DISX_PlaneNormalize
    ( DISX_PLANE *pOut, const DISX_PLANE *pP)
{
	DISX_VECTOR3 temp( pP->a, pP->b, pP->c );
	DISX_Vec3Normalize( &temp, &temp );

	pOut->a = temp.x;
	pOut->b = temp.y;
	pOut->c = temp.z;
	pOut->d = pP->d;
	
	return pOut;

}

// Find the intersection between a plane and a line.  If the line is
// parallel to the plane, NULL is returned.
DISX_VECTOR3*  DISX_PlaneIntersectLine
    ( DISX_VECTOR3 *pOut, const DISX_PLANE *pP, const DISX_VECTOR3 *pV1,
      const DISX_VECTOR3 *pV2)
{
	DISX_VECTOR3 rayDir = *pV2 - *pV1;
	
	float Length = DISX_Vec3Length( &rayDir );
	
	float Recip = 1/Length;
	
	rayDir *= Recip; // this normalizes
	//DISX_Vec3Normalize( &rayDir, &rayDir );

	float dot = pP->a * rayDir.x +
				pP->b * rayDir.y +
				pP->c * rayDir.z;

	if(dot == 0.0f)     // change to <= and use Eps
		return NULL;	//error line parallel to plane

	// compute the signed distance between origin and plane
	float sDist =  pP->a * pV1->x +
				   pP->b * pV1->y +
				   pP->c * pV1->z + pP->d;

	if( fabs(sDist) < Length ) // also returning NULL for the case where the line 
		return NULL;	// does not reach

	*pOut =  *pV1 - rayDir * ( sDist / dot );
	
	return pOut;
}

// construct a plane from a point and a normal
DISX_PLANE*  DISX_PlaneFromPointNormal
    ( DISX_PLANE *pOut, const DISX_VECTOR3 *pPoint, const DISX_VECTOR3 *pNormal)
{
	pOut->a = pNormal->x; 
	pOut->b = pNormal->y;
	pOut->c = pNormal->z;
	pOut->d = -(pOut->a*pPoint->x + pOut->b*pPoint->y + pOut->c*pPoint->z);   // temporary d value
	return pOut;
}

// construct a plane from 3 points
DISX_PLANE*  DISX_PlaneFromPoints
    ( DISX_PLANE *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2,
      const DISX_VECTOR3 *pV3)
{
	DISX_VECTOR3 n1 = *pV2 - *pV1;
	DISX_VECTOR3 n2 = *pV3 - *pV1;

	DISX_VECTOR3 n3;
	DISX_Vec3Cross(&n3, &n2, &n1 );
	
	DISX_Vec3Normalize(&n3, &n3);

	pOut->a = n3.x;
	pOut->b = n3.y;
	pOut->c = n3.z;
	pOut->d = -( pV1->x*pOut->a + pV1->y*pOut->b + pV1->z*pOut->c ); // temporary d value, unless used by polyplane

	return pOut;
}

// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
DISX_PLANE*  DISX_PlaneTransform
    ( DISX_PLANE *pOut, const DISX_PLANE *pP, const DISX_MATRIX *pM )
{
	// TODO
	DISX_PLANE P2;
	DISX_PlaneNormalize(&P2, pP);

	pOut->a = P2.a * pM->_11 + P2.b * pM->_12 + P2.c * pM->_13 + P2.d * pM->_14;
	pOut->b = P2.a * pM->_21 + P2.b * pM->_22 + P2.c * pM->_23 + P2.d * pM->_24;
	pOut->c = P2.a * pM->_31 + P2.b * pM->_32 + P2.c * pM->_33 + P2.d * pM->_34;
	pOut->d = P2.a * pM->_41 + P2.b * pM->_42 + P2.c * pM->_43 + P2.d * pM->_44;

	return pOut;
}
    
// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
DISX_PLANE*  DISX_PlaneTransformArray
    ( DISX_PLANE *pOut, UInt32 OutStride, const DISX_PLANE *pP, UInt32 PStride, const DISX_MATRIX *pM, UInt32 n )
{
	UInt32 inputIndex = 0;
	UInt32 outputIndex = 0;

	for( UInt32 i = 0; i < n; i++ )
	{
		DISX_PlaneTransform( &pOut[outputIndex], &pP[inputIndex], pM );
		
		outputIndex += OutStride;
		inputIndex += PStride;
	}

	return pOut;
}


//--------------------------
// Color
//--------------------------


// Interpolate r,g,b between desaturated color and color.
// DesaturatedColor + s(Color - DesaturatedColor)
DISX_COLOR*  DISX_ColorAdjustSaturation
    (DISX_COLOR *pOut, const DISX_COLOR *pC, float s)
{
	
	float grey = 0.2125*pC->r + 0.7154*pC->g + 0.0721*pC->b;
	
	pOut->r = grey + s * (pC->r - grey);
	pOut->g = grey + s * (pC->g - grey);
	pOut->b = grey + s * (pC->b - grey);
	pOut->a = pC->a;
	// TODO
	return pOut;
}

// Interpolate r,g,b between 50% grey and color.  Grey + s(Color - Grey)
DISX_COLOR*  DISX_ColorAdjustContrast
    (DISX_COLOR *pOut, const DISX_COLOR *pC, float c)
{
	float grey = 0.5f;
	//pOut->r = 0.5f + c * (pC->r - 0.5f);

	pOut->r = grey + c * (pC->r - grey);
	pOut->g = grey + c * (pC->g - grey);
	pOut->b = grey + c * (pC->b - grey);
	
	pOut->a = pC->a;
	
	return pOut;
}



//--------------------------
// Misc
//--------------------------

// Calculate Fresnel term given the cosine of theta (likely obtained by
// taking the dot of two normals), and the refraction index of the material.
float  DISX_FresnelTerm
    (float CosTheta, float RefractionIndex)
{
	/* Microsoft Documentation
	--------------------------
	Let r   = sina(A) / sin(B)      (the relative refractive index)
	Let c   = cos(A)
	Let g   = (r2 + c2 - 1)1/2

	F = 0.5 * (g + c)2 / (g - c)2 * ([c(g + c) - 1]2 / [c(g - c) + 1]2 + 1)
	---------------------------

	Using Snell's law to compute the angle of refraction
	Sin(A)  =  Vel1   =  N2
	------     ----      ---
	Sin(B)		Vel2     N1

	for the case of air into water, we have

	N2 = water
	N1 = air

	water = 1.333
	air = 1

	or 1.333 = 1.333 = Sin(A)		so Sin(B) = Sin(A)/1.333
		---				----
		1				Sin(B)

	so Sin(B) = N1 Sin(A)
	            --
				N2

	taking N2 as the value used, to refract Air into Water or some other material
	Sin(B) =  Sin(A) / N2

	an alternative implementation would have N2 == 1

	so, if
	sinA = sin(acos(CosTheta))
	sinB = sinA / RefractionIndex
	then
	r = sinA / sinB 
	  = sinA / (sinA/RefractionIndex)
	  = RefractionIndex* (sinA/sinA)
	  = RefractionIndex
	c = CosTheta
	g = (r2? + c2? - 1)1/2 
	  := (r+c-1)/2 

	then the term given is ...
	F = 0.5 * (g + c)*2 / (g - c)*2 * ( (c(g + c) - 1)*2 / (c(g - c) + 1)*2 + 1)
	*/

	//float sinA = sin(acos(CosTheta));
	//float sinB = sinA /  RefractionIndex;
	
	float r = RefractionIndex; // or 1/ RefractionIndex
	float c = CosTheta;
	float g = (r + c-1)*0.5;

	return 0.5 * (g + c)*2 / (g - c)*2 * ( (c*(g + c) - 1)*2 / (c*(g - c) + 1)*2 + 1);

}


//===========================================================================
//
//  Spherical Harmonic Runtime Routines
//
// NOTE:
//  * Most of these functions can take the same object as in and out parameters.
//    The exceptions are the rotation functions.  
//
//  * Out parameters are typically also returned as return values, so that
//    the output of one function may be used as a parameter to another.
//
//============================================================================
//============================================================================
//
//  DISX_SHEvalDirection:
//  --------------------
//  Evaluates the Spherical Harmonic basis functions
//
//  Parameters:
//   pOut
//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
//      This is the pointer that is returned.
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pDir
//      Direction to evaluate in - assumed to be normalized
//
//============================================================================

float*  DISX_SHEvalDirection
    (  float *pOut, UInt32 Order, const DISX_VECTOR3 *pDir )
{
	return pOut;
}
    
//============================================================================
//
//  DISX_SHRotate:
//  --------------------
//  Rotates SH vector by a rotation matrix
//
//  Parameters:
//   pOut
//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
//      This is the pointer that is returned (should not alias with pIn.)
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pMatrix
//      Matrix used for rotation - rotation sub matrix should be orthogonal
//      and have a unit determinant.
//   pIn
//      Input SH coeffs (rotated), incorect results if this is also output.
//
//============================================================================

float*  DISX_SHRotate
    ( float *pOut, UInt32 Order, const DISX_MATRIX *pMatrix, const float *pIn )
{
	return pOut;
}
    
//============================================================================
//
//  DISX_SHRotateZ:
//  --------------------
//  Rotates the SH vector in the Z axis by an angle
//
//  Parameters:
//   pOut
//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
//      This is the pointer that is returned (should not alias with pIn.)
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   Angle
//      Angle in radians to rotate around the Z axis.
//   pIn
//      Input SH coeffs (rotated), incorect results if this is also output.
//
//============================================================================


float*  DISX_SHRotateZ
    ( float *pOut, UInt32 Order, float Angle, const float *pIn )
{
	return pOut;
}
    
//============================================================================
//
//  DISX_SHAdd:
//  --------------------
//  Adds two SH vectors, pOut[i] = pA[i] + pB[i];
//
//  Parameters:
//   pOut
//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
//      This is the pointer that is returned.
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pA
//      Input SH coeffs.
//   pB
//      Input SH coeffs (second vector.)
//
//============================================================================

float*  DISX_SHAdd
    ( float *pOut, UInt32 Order, const float *pA, const float *pB )
{
	return pOut;
}

//============================================================================
//
//  DISX_SHScale:
//  --------------------
//  Adds two SH vectors, pOut[i] = pA[i]*Scale;
//
//  Parameters:
//   pOut
//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
//      This is the pointer that is returned.
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pIn
//      Input SH coeffs.
//   Scale
//      Scale factor.
//
//============================================================================

float*  DISX_SHScale
    ( float *pOut, UInt32 Order, const float *pIn, const float Scale )
{
	return pOut;
}
    
//============================================================================
//
//  DISX_SHDot:
//  --------------------
//  Computes the dot product of two SH vectors
//
//  Parameters:
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pA
//      Input SH coeffs.
//   pB
//      Second set of input SH coeffs.
//
//============================================================================

float  DISX_SHDot
    ( UInt32 Order, const float *pA, const float *pB )
{
	return 0.0f;
}

//============================================================================
//
//  DISX_SHMultiply[O]:
//  --------------------
//  Computes the product of two functions represented using SH (f and g), where:
//  pOut[i] = int(y_i(s) * f(s) * g(s)), where y_i(s) is the ith SH basis
//  function, f(s) and g(s) are SH functions (sum_i(y_i(s)*c_i)).  The order O
//  determines the lengths of the arrays, where there should always be O^2 
//  coefficients.  In general the product of two SH functions of order O generates
//  and SH function of order 2*O - 1, but we truncate the result.  This means
//  that the product commutes (f*g == g*f) but doesn't associate 
//  (f*(g*h) != (f*g)*h.
//
//  Parameters:
//   pOut
//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
//      This is the pointer that is returned.
//   pF
//      Input SH coeffs for first function.
//   pG
//      Second set of input SH coeffs.
//
//============================================================================

float*  DISX_SHMultiply2( float *pOut, const float *pF, const float *pG)
{
		return pOut;
}
float*  DISX_SHMultiply3( float *pOut, const float *pF, const float *pG)
{
	return pOut;
}
float*  DISX_SHMultiply4( float *pOut, const float *pF, const float *pG)
{
	return pOut;
}
float*  DISX_SHMultiply5( float *pOut, const float *pF, const float *pG)
{
	return pOut;
}
float*  DISX_SHMultiply6( float *pOut, const float *pF, const float *pG)
{
	return pOut;
}


//============================================================================
//
//  Basic Spherical Harmonic lighting routines
//
//============================================================================

//============================================================================
//
//  DISX_SHEvalDirectionalLight:
//  --------------------
//  Evaluates a directional light and returns spectral SH data.  The output 
//  vector is computed so that if the intensity of R/G/B is unit the resulting
//  exit radiance of a point directly under the light on a diffuse object with
//  an albedo of 1 would be 1.0.  This will compute 3 spectral samples, pROut
//  has to be specified, while pGout and pBout are optional.
//
//  Parameters:
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pDir
//      Direction light is coming from (assumed to be normalized.)
//   RIntensity
//      Red intensity of light.
//   GIntensity
//      Green intensity of light.
//   BIntensity
//      Blue intensity of light.
//   pROut
//      Output SH vector for Red.
//   pGOut
//      Output SH vector for Green (optional.)
//   pBOut
//      Output SH vector for Blue (optional.)        
//
//============================================================================

DIS_RESULT  DISX_SHEvalDirectionalLight
    ( UInt32 Order, const DISX_VECTOR3 *pDir, 
      float RIntensity, float GIntensity, float BIntensity,
      float *pROut, float *pGOut, float *pBOut )
{
	return DIS_OK;
}

//============================================================================
//
//  DISX_SHEvalSphericalLight:
//  --------------------
//  Evaluates a spherical light and returns spectral SH data.  There is no 
//  normalization of the intensity of the light like there is for directional
//  lights, care has to be taken when specifiying the intensities.  This will 
//  compute 3 spectral samples, pROut has to be specified, while pGout and 
//  pBout are optional.
//
//  Parameters:
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pPos
//      Position of light - reciever is assumed to be at the origin.
//   Radius
//      Radius of the spherical light source.
//   RIntensity
//      Red intensity of light.
//   GIntensity
//      Green intensity of light.
//   BIntensity
//      Blue intensity of light.
//   pROut
//      Output SH vector for Red.
//   pGOut
//      Output SH vector for Green (optional.)
//   pBOut
//      Output SH vector for Blue (optional.)        
//
//============================================================================

DIS_RESULT  DISX_SHEvalSphericalLight
    ( UInt32 Order, const DISX_VECTOR3 *pPos, float Radius,
      float RIntensity, float GIntensity, float BIntensity,
      float *pROut, float *pGOut, float *pBOut )
{
	return DIS_OK;
}

//============================================================================
//
//  DISX_SHEvalConeLight:
//  --------------------
//  Evaluates a light that is a cone of constant intensity and returns spectral
//  SH data.  The output vector is computed so that if the intensity of R/G/B is
//  unit the resulting exit radiance of a point directly under the light oriented
//  in the cone direction on a diffuse object with an albedo of 1 would be 1.0.
//  This will compute 3 spectral samples, pROut has to be specified, while pGout
//  and pBout are optional.
//
//  Parameters:
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pDir
//      Direction light is coming from (assumed to be normalized.)
//   Radius
//      Radius of cone in radians.
//   RIntensity
//      Red intensity of light.
//   GIntensity
//      Green intensity of light.
//   BIntensity
//      Blue intensity of light.
//   pROut
//      Output SH vector for Red.
//   pGOut
//      Output SH vector for Green (optional.)
//   pBOut
//      Output SH vector for Blue (optional.)        
//
//============================================================================

DIS_RESULT  DISX_SHEvalConeLight
    ( UInt32 Order, const DISX_VECTOR3 *pDir, float Radius,
      float RIntensity, float GIntensity, float BIntensity,
      float *pROut, float *pGOut, float *pBOut )
{
	return DIS_OK;
}
      
//============================================================================
//
//  DISX_SHEvalHemisphereLight:
//  --------------------
//  Evaluates a light that is a linear interpolant between two colors over the
//  sphere.  The interpolant is linear along the axis of the two points, not
//  over the surface of the sphere (ie: if the axis was (0,0,1) it is linear in
//  Z, not in the azimuthal angle.)  The resulting spherical lighting function
//  is normalized so that a point on a perfectly diffuse surface with no
//  shadowing and a normal pointed in the direction pDir would result in exit
//  radiance with a value of 1 if the top color was white and the bottom color
//  was black.  This is a very simple model where Top represents the intensity 
//  of the "sky" and Bottom represents the intensity of the "ground".
//
//  Parameters:
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pDir
//      Axis of the hemisphere.
//   Top
//      Color of the upper hemisphere.
//   Bottom
//      Color of the lower hemisphere.
//   pROut
//      Output SH vector for Red.
//   pGOut
//      Output SH vector for Green
//   pBOut
//      Output SH vector for Blue        
//
//============================================================================

DIS_RESULT  DISX_SHEvalHemisphereLight
    ( UInt32 Order, const DISX_VECTOR3 *pDir, DISX_COLOR Top, DISX_COLOR Bottom,
      float *pROut, float *pGOut, float *pBOut )
{
	return DIS_OK;
}

//============================================================================
//
//  Basic Spherical Harmonic projection routines
//
//============================================================================

//============================================================================
//
//  DISX_SHProjectCubeMap:
//  --------------------
//  Projects a function represented on a cube map into spherical harmonics.
//
//  Parameters:
//   Order
//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
//   pCubeMap
//      CubeMap that is going to be projected into spherical harmonics
//   pROut
//      Output SH vector for Red.
//   pGOut
//      Output SH vector for Green
//   pBOut
//      Output SH vector for Blue        
//
//============================================================================

/*
DIS_RESULT  DISX_SHProjectCubeMap
    ( UInt32 uOrder, LPDIRECT3DCUBETEXTURE9 pCubeMap,
      float *pROut, float *pGOut, float *pBOut );
*/