//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) Microsoft Corporation.  All Rights Reserved.
//
//  File:       DISX_9math.h
//  Content:    DISX_ math types and functions
//	Special Note: This content is directly copied from D3DX9Math.h
//				  for the sole purpose of keeping the classic 
//					Microsoft look and feel for the API
//////////////////////////////////////////////////////////////////////////////
#ifndef DISX_MATH_H
#define DISX_MATH_H

#include "DIS_RenderStates.h"



#include <math.h>
#include <memory.h>

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4201) // anonymous unions warning



//===========================================================================
//
// General purpose utilities
//
//===========================================================================
#define DISX_PI    ((float)  3.141592654f)
#define DISX_1BYPI ((float)  0.318309886f)

#define DISX_ToRadian( degree ) ((degree) * (DISX__PI / 180.0f))
#define DISX_ToDegree( radian ) ((radian) * (180.0f / DISX__PI))


//===========================================================================
//
// Vectors
//
//===========================================================================


//--------------------------
// 2D Vector
//--------------------------
class DISX_VECTOR2
{
public:
    DISX_VECTOR2() {};
    DISX_VECTOR2( const float * );
    DISX_VECTOR2( float x, float y );

    // casting
    operator float* ();
    operator const float* () const;

    // assignment operators
    DISX_VECTOR2& operator += ( const DISX_VECTOR2& );
    DISX_VECTOR2& operator -= ( const DISX_VECTOR2& );
    DISX_VECTOR2& operator *= ( float );
    DISX_VECTOR2& operator /= ( float );

    // unary operators
    DISX_VECTOR2 operator + () const;
    DISX_VECTOR2 operator - () const;

    // binary operators
    DISX_VECTOR2 operator + ( const DISX_VECTOR2& ) const;
    DISX_VECTOR2 operator - ( const DISX_VECTOR2& ) const;
    DISX_VECTOR2 operator * ( float ) const;
    DISX_VECTOR2 operator / ( float ) const;

    friend DISX_VECTOR2 operator * ( float, const DISX_VECTOR2& );

    bool operator == ( const DISX_VECTOR2& ) const;
    bool operator != ( const DISX_VECTOR2& ) const;


public:

    float x, y;
};



//--------------------------
// 3D Vector
//--------------------------

class DISX_VECTOR3 : public DIS_VECTOR
{
public:
    DISX_VECTOR3() {};
    DISX_VECTOR3( const float * );
    DISX_VECTOR3( const DIS_VECTOR& );
    DISX_VECTOR3( float x, float y, float z );

    // casting
    operator float* ();
    operator const float* () const;

    // assignment operators
    DISX_VECTOR3& operator += ( const DISX_VECTOR3& );
    DISX_VECTOR3& operator -= ( const DISX_VECTOR3& );
    DISX_VECTOR3& operator *= ( float );
    DISX_VECTOR3& operator /= ( float );

    // unary operators
    DISX_VECTOR3 operator + () const;
    DISX_VECTOR3 operator - () const;

    // binary operators
    DISX_VECTOR3 operator + ( const DISX_VECTOR3& ) const;
    DISX_VECTOR3 operator - ( const DISX_VECTOR3& ) const;
    DISX_VECTOR3 operator * ( float ) const;
    DISX_VECTOR3 operator / ( float ) const;

    friend DISX_VECTOR3 operator * ( float, const struct DISX_VECTOR3& );

    bool operator == ( const DISX_VECTOR3& ) const;
    bool operator != ( const DISX_VECTOR3& ) const;

};




//--------------------------
// 4D Vector
//--------------------------
class DISX_VECTOR4
{
public:
    DISX_VECTOR4() {};
    DISX_VECTOR4( const float* );
    DISX_VECTOR4( const DIS_VECTOR& xyz, float w );
    DISX_VECTOR4( float x, float y, float z, float w );

    // casting
    operator float* ();
    operator const float* () const;

    // assignment operators
    DISX_VECTOR4& operator += ( const DISX_VECTOR4& );
    DISX_VECTOR4& operator -= ( const DISX_VECTOR4& );
    DISX_VECTOR4& operator *= ( float );
    DISX_VECTOR4& operator /= ( float );

    // unary operators
    DISX_VECTOR4 operator + () const;
    DISX_VECTOR4 operator - () const;

    // binary operators
    DISX_VECTOR4 operator + ( const DISX_VECTOR4& ) const;
    DISX_VECTOR4 operator - ( const DISX_VECTOR4& ) const;
    DISX_VECTOR4 operator * ( float ) const;
    DISX_VECTOR4 operator / ( float ) const;

    friend DISX_VECTOR4 operator * ( float, const DISX_VECTOR4& );

    bool operator == ( const DISX_VECTOR4& ) const;
    bool operator != ( const DISX_VECTOR4& ) const;

public:
    float x, y, z, w;
};



//===========================================================================
//
// Matrices
//
//===========================================================================

class DISX_MATRIX : public DIS_MATRIX
{
public:
    DISX_MATRIX() {};
    DISX_MATRIX( const float * );
    DISX_MATRIX( const DISX_MATRIX& );
    DISX_MATRIX( float _11, float _12, float _13, float _14,
                float _21, float _22, float _23, float _24,
                float _31, float _32, float _33, float _34,
                float _41, float _42, float _43, float _44 );


    // access grants
    float& operator () ( UInt32 Row, UInt32 Col );
    float  operator () ( UInt32 Row, UInt32 Col ) const;

    // casting operators
    operator float* ();
    operator const float* () const;

    // assignment operators
    DISX_MATRIX& operator *= ( const DISX_MATRIX& );
    DISX_MATRIX& operator += ( const DISX_MATRIX& );
    DISX_MATRIX& operator -= ( const DISX_MATRIX& );
    DISX_MATRIX& operator *= ( float );
    DISX_MATRIX& operator /= ( float );

    // unary operators
    DISX_MATRIX operator + () const;
    DISX_MATRIX operator - () const;

    // binary operators
    DISX_MATRIX operator * ( const DISX_MATRIX& ) const;
    DISX_MATRIX operator + ( const DISX_MATRIX& ) const;
    DISX_MATRIX operator - ( const DISX_MATRIX& ) const;
    DISX_MATRIX operator * ( float ) const;
    DISX_MATRIX operator / ( float ) const;

    friend DISX_MATRIX operator * ( float, const DISX_MATRIX& );

    bool operator == ( const DISX_MATRIX& ) const;
    bool operator != ( const DISX_MATRIX& ) const;

};





//===========================================================================
//
//    Quaternions
//
//===========================================================================
class DISX_QUATERNION
{

public:
    DISX_QUATERNION() {}
    DISX_QUATERNION( const float * );
    DISX_QUATERNION( float x, float y, float z, float w );

    // casting
    operator float* ();
    operator const float* () const;

    // assignment operators
    DISX_QUATERNION& operator += ( const DISX_QUATERNION& );
    DISX_QUATERNION& operator -= ( const DISX_QUATERNION& );
    DISX_QUATERNION& operator *= ( const DISX_QUATERNION& );
    DISX_QUATERNION& operator *= ( float );
    DISX_QUATERNION& operator /= ( float );

    // unary operators
    DISX_QUATERNION  operator + () const;
    DISX_QUATERNION  operator - () const;

    // binary operators
    DISX_QUATERNION operator + ( const DISX_QUATERNION& ) const;
    DISX_QUATERNION operator - ( const DISX_QUATERNION& ) const;
    DISX_QUATERNION operator * ( const DISX_QUATERNION& ) const;
    DISX_QUATERNION operator * ( float ) const;
    DISX_QUATERNION operator / ( float ) const;

    friend DISX_QUATERNION operator * (float, const DISX_QUATERNION& );

    bool operator == ( const DISX_QUATERNION& ) const;
    bool operator != ( const DISX_QUATERNION& ) const;

    float x, y, z, w;
};


//===========================================================================
//
// Planes
//
//===========================================================================
class DISX_PLANE
{
public:
    DISX_PLANE() {}
    DISX_PLANE( const float* );
    DISX_PLANE( float a, float b, float c, float d );

    // casting
    operator float* ();
    operator const float* () const;

    // assignment operators
    DISX_PLANE& operator *= ( float );
    DISX_PLANE& operator /= ( float );

    // unary operators
    DISX_PLANE operator + () const;
    DISX_PLANE operator - () const;

    // binary operators
    DISX_PLANE operator * ( float ) const;
    DISX_PLANE operator / ( float ) const;

    friend DISX_PLANE operator * ( float, const DISX_PLANE& );

    bool operator == ( const DISX_PLANE& ) const;
    bool operator != ( const DISX_PLANE& ) const;

    float a, b, c, d;
};


//===========================================================================
//
// Colors
//
//===========================================================================

class DISX_COLOR
{
public:
    DISX_COLOR() {}
    DISX_COLOR( UInt32 argb );
    DISX_COLOR( const float * );
    DISX_COLOR( const DIS_COLORVALUE& );
    DISX_COLOR( float r, float g, float b, float a );

    // casting
    operator UInt32 () const;

    operator float* ();
    operator const float* () const;

    operator DIS_COLORVALUE* ();
    operator const DIS_COLORVALUE* () const;

    operator DIS_COLORVALUE& ();
    operator const DIS_COLORVALUE& () const;

    // assignment operators
    DISX_COLOR& operator += ( const DISX_COLOR& );
    DISX_COLOR& operator -= ( const DISX_COLOR& );
    DISX_COLOR& operator *= ( float );
    DISX_COLOR& operator /= ( float );

    // unary operators
    DISX_COLOR operator + () const;
    DISX_COLOR operator - () const;

    // binary operators
    DISX_COLOR operator + ( const DISX_COLOR& ) const;
    DISX_COLOR operator - ( const DISX_COLOR& ) const;
    DISX_COLOR operator * ( float ) const;
    DISX_COLOR operator / ( float ) const;

    friend DISX_COLOR operator * ( float, const DISX_COLOR& );

    bool operator == ( const DISX_COLOR& ) const;
    bool operator != ( const DISX_COLOR& ) const;

    float r, g, b, a;
};



//===========================================================================
//
// DISX_ math functions:
//
// NOTE:
//  * All these functions can take the same object as in and out parameters.
//
//  * Out parameters are typically also returned as return values, so that
//    the output of one function may be used as a parameter to another.
//
//===========================================================================


//--------------------------
// 2D Vector
//--------------------------

// inline

float DISX_Vec2Length
    ( const DISX_VECTOR2 *pV );

float DISX_Vec2LengthSq
    ( const DISX_VECTOR2 *pV );

float DISX_Vec2Dot
    ( const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 );

// Z component of ((x1,y1,0) cross (x2,y2,0))
float DISX_Vec2CCW
    ( const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 );

DISX_VECTOR2* DISX_Vec2Add
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 );

DISX_VECTOR2* DISX_Vec2Subtract
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 );

// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
DISX_VECTOR2* DISX_Vec2Minimize
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 );

// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
DISX_VECTOR2* DISX_Vec2Maximize
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 );

DISX_VECTOR2* DISX_Vec2Scale
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV, float s );

// Linear interpolation. V1 + s(V2-V1)
DISX_VECTOR2* DISX_Vec2Lerp
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2,
      float s );

// non-inline


DISX_VECTOR2*  DISX_Vec2Normalize
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV );

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
DISX_VECTOR2*  DISX_Vec2Hermite
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pT1,
      const DISX_VECTOR2 *pV2, const DISX_VECTOR2 *pT2, float s );

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
DISX_VECTOR2*  DISX_Vec2CatmullRom
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV0, const DISX_VECTOR2 *pV1,
      const DISX_VECTOR2 *pV2, const DISX_VECTOR2 *pV3, float s );

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
DISX_VECTOR2*  DISX_Vec2BaryCentric
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2,
      const DISX_VECTOR2 *pV3, float f, float g);

// Transform (x, y, 0, 1) by matrix.
DISX_VECTOR4*  DISX_Vec2Transform
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR2 *pV, const DISX_MATRIX *pM );

// Transform (x, y, 0, 1) by matrix, project result back into w=1.
DISX_VECTOR2*  DISX_Vec2TransformCoord
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV, const DISX_MATRIX *pM );

// Transform (x, y, 0, 0) by matrix.
DISX_VECTOR2*  DISX_Vec2TransformNormal
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV, const DISX_MATRIX *pM );
     
// Transform Array (x, y, 0, 1) by matrix.
DISX_VECTOR4*  DISX_Vec2TransformArray
    ( DISX_VECTOR4 *pOut, UInt32 OutStride, const DISX_VECTOR2 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n);

// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
DISX_VECTOR2*  DISX_Vec2TransformCoordArray
    ( DISX_VECTOR2 *pOut, UInt32 OutStride, const DISX_VECTOR2 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n );

// Transform Array (x, y, 0, 0) by matrix.
DISX_VECTOR2*  DISX_Vec2TransformNormalArray
    ( DISX_VECTOR2 *pOut, UInt32 OutStride, const DISX_VECTOR2 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n );
    
    

//--------------------------
// 3D Vector
//--------------------------

// inline

float DISX_Vec3Length
    ( const DISX_VECTOR3 *pV );

float DISX_Vec3LengthSq
    ( const DISX_VECTOR3 *pV );

float DISX_Vec3Dot
    ( const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 );

DISX_VECTOR3* DISX_Vec3Cross
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 );

DISX_VECTOR3* DISX_Vec3Add
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 );

DISX_VECTOR3* DISX_Vec3Subtract
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 );

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
DISX_VECTOR3* DISX_Vec3Minimize
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 );

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
DISX_VECTOR3* DISX_Vec3Maximize
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 );

DISX_VECTOR3* DISX_Vec3Scale
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, float s);

// Linear interpolation. V1 + s(V2-V1)
DISX_VECTOR3* DISX_Vec3Lerp
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2,
      float s );

// non-inline

DISX_VECTOR3*  DISX_Vec3Normalize
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV );

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
DISX_VECTOR3*  DISX_Vec3Hermite
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pT1,
      const DISX_VECTOR3 *pV2, const DISX_VECTOR3 *pT2, float s );

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
DISX_VECTOR3*  DISX_Vec3CatmullRom
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV0, const DISX_VECTOR3 *pV1,
      const DISX_VECTOR3 *pV2, const DISX_VECTOR3 *pV3, float s );

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
DISX_VECTOR3*  DISX_Vec3BaryCentric
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2,
      const DISX_VECTOR3 *pV3, float f, float g);

// Transform (x, y, z, 1) by matrix.
DISX_VECTOR4*  DISX_Vec3Transform
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR3 *pV, const DISX_MATRIX *pM );

// Transform (x, y, z, 1) by matrix, project result back into w=1.
DISX_VECTOR3*  DISX_Vec3TransformCoord
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, const DISX_MATRIX *pM );

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
// non-affine matrix, the matrix you pass to this function should be the 
// transpose of the inverse of the matrix you would use to transform a coord.
DISX_VECTOR3*  DISX_Vec3TransformNormal
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, const DISX_MATRIX *pM );
    
    
// Transform Array (x, y, z, 1) by matrix. 
DISX_VECTOR4*  DISX_Vec3TransformArray
    ( DISX_VECTOR4 *pOut, UInt32 OutStride, const DISX_VECTOR3 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n );

// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
DISX_VECTOR3*  DISX_Vec3TransformCoordArray
    ( DISX_VECTOR3 *pOut, UInt32 OutStride, const DISX_VECTOR3 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n );

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
// non-affine matrix, the matrix you pass to this function should be the 
// transpose of the inverse of the matrix you would use to transform a coord.
DISX_VECTOR3*  DISX_Vec3TransformNormalArray
    ( DISX_VECTOR3 *pOut, UInt32 OutStride, const DISX_VECTOR3 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n );

// Project vector from object space into screen space
DISX_VECTOR3*  DISX_Vec3Project
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, const DIS_VIEWPORT *pViewport,
      const DISX_MATRIX *pProjection, const DISX_MATRIX *pView, const DISX_MATRIX *pWorld);

// Project vector from screen space into object space
DISX_VECTOR3*  DISX_Vec3Unproject
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, const DIS_VIEWPORT *pViewport,
      const DISX_MATRIX *pProjection, const DISX_MATRIX *pView, const DISX_MATRIX *pWorld);
      
// Project vector Array from object space into screen space
DISX_VECTOR3*  DISX_Vec3ProjectArray
    ( DISX_VECTOR3 *pOut, UInt32 OutStride,const DISX_VECTOR3 *pV, UInt32 VStride,const DIS_VIEWPORT *pViewport,
      const DISX_MATRIX *pProjection, const DISX_MATRIX *pView, const DISX_MATRIX *pWorld, UInt32 n);

// Project vector Array from screen space into object space
DISX_VECTOR3*  DISX_Vec3UnprojectArray
    ( DISX_VECTOR3 *pOut, UInt32 OutStride, const DISX_VECTOR3 *pV, UInt32 VStride, const DIS_VIEWPORT *pViewport,
      const DISX_MATRIX *pProjection, const DISX_MATRIX *pView, const DISX_MATRIX *pWorld, UInt32 n);






//--------------------------
// 4D Vector
//--------------------------

// inline

float DISX_Vec4Length
    ( const DISX_VECTOR4 *pV );

float DISX_Vec4LengthSq
    ( const DISX_VECTOR4 *pV );

float DISX_Vec4Dot
    ( const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2 );

DISX_VECTOR4* DISX_Vec4Add
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2);

DISX_VECTOR4* DISX_Vec4Subtract
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
DISX_VECTOR4* DISX_Vec4Minimize
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2);

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
DISX_VECTOR4* DISX_Vec4Maximize
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2);

DISX_VECTOR4* DISX_Vec4Scale
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV, float s);

// Linear interpolation. V1 + s(V2-V1)
DISX_VECTOR4* DISX_Vec4Lerp
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2,
      float s );

// non-inline

// Cross-product in 4 dimensions.
DISX_VECTOR4*  DISX_Vec4Cross
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2,
      const DISX_VECTOR4 *pV3);

DISX_VECTOR4*  DISX_Vec4Normalize
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV );

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
DISX_VECTOR4*  DISX_Vec4Hermite
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pT1,
      const DISX_VECTOR4 *pV2, const DISX_VECTOR4 *pT2, float s );

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
DISX_VECTOR4*  DISX_Vec4CatmullRom
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV0, const DISX_VECTOR4 *pV1,
      const DISX_VECTOR4 *pV2, const DISX_VECTOR4 *pV3, float s );

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
DISX_VECTOR4*  DISX_Vec4BaryCentric
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2,
      const DISX_VECTOR4 *pV3, float f, float g);

// Transform vector by matrix.
DISX_VECTOR4*  DISX_Vec4Transform
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV, const DISX_MATRIX *pM );
    
// Transform vector array by matrix.
DISX_VECTOR4*  DISX_Vec4TransformArray
    ( DISX_VECTOR4 *pOut, UInt32 OutStride, const DISX_VECTOR4 *pV, UInt32 VStride, const DISX_MATRIX *pM, UInt32 n );




//--------------------------
// 4D Matrix
//--------------------------

// inline

DISX_MATRIX* DISX_MatrixIdentity
    ( DISX_MATRIX *pOut );

bool DISX_MatrixIsIdentity
    ( const DISX_MATRIX *pM );


// non-inline


float  DISX_MatrixDeterminant
    ( const DISX_MATRIX *pM );

DIS_RESULT  DISX_MatrixDecompose
    ( DISX_VECTOR3 *pOutScale, DISX_QUATERNION *pOutRotation, 
	  DISX_VECTOR3 *pOutTranslation, const DISX_MATRIX *pM );

DISX_MATRIX*  DISX_MatrixTranspose
    ( DISX_MATRIX *pOut, const DISX_MATRIX *pM );

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
DISX_MATRIX*  DISX_MatrixMultiply
    ( DISX_MATRIX *pOut, const DISX_MATRIX *pM1, const DISX_MATRIX *pM2 );

// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
DISX_MATRIX*  DISX_MatrixMultiplyTranspose
    ( DISX_MATRIX *pOut, const DISX_MATRIX *pM1, const DISX_MATRIX *pM2 );

// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.
DISX_MATRIX*  DISX_MatrixInverse
    ( DISX_MATRIX *pOut, float *pDeterminant, const DISX_MATRIX *pM );

// Build a matrix which scales by (sx, sy, sz)
DISX_MATRIX*  DISX_MatrixScaling
    ( DISX_MATRIX *pOut, float sx, float sy, float sz );

// Build a matrix which translates by (x, y, z)
DISX_MATRIX*  DISX_MatrixTranslation
    ( DISX_MATRIX *pOut, float x, float y, float z );

// Build a matrix which rotates around the X axis
DISX_MATRIX*  DISX_MatrixRotationX
    ( DISX_MATRIX *pOut, float Angle );

// Build a matrix which rotates around the Y axis
DISX_MATRIX*  DISX_MatrixRotationY
    ( DISX_MATRIX *pOut, float Angle );

// Build a matrix which rotates around the Z axis
DISX_MATRIX*  DISX_MatrixRotationZ
    ( DISX_MATRIX *pOut, float Angle );

// Build a matrix which rotates around an arbitrary axis
DISX_MATRIX*  DISX_MatrixRotationAxis
    ( DISX_MATRIX *pOut, const DISX_VECTOR3 *pV, float Angle );

// Build a matrix from a quaternion
DISX_MATRIX*  DISX_MatrixRotationQuaternion
    ( DISX_MATRIX *pOut, const DISX_QUATERNION *pQ);

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
DISX_MATRIX*  DISX_MatrixRotationYawPitchRoll
    ( DISX_MATRIX *pOut, float Yaw, float Pitch, float Roll );

// Build transformation matrix.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
DISX_MATRIX*  DISX_MatrixTransformation
    ( DISX_MATRIX *pOut, const DISX_VECTOR3 *pScalingCenter,
      const DISX_QUATERNION *pScalingRotation, const DISX_VECTOR3 *pScaling,
      const DISX_VECTOR3 *pRotationCenter, const DISX_QUATERNION *pRotation,
      const DISX_VECTOR3 *pTranslation);

// Build 2D transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
DISX_MATRIX*  DISX_MatrixTransformation2D
    ( DISX_MATRIX *pOut, const DISX_VECTOR2* pScalingCenter, 
      float ScalingRotation, const DISX_VECTOR2* pScaling, 
      const DISX_VECTOR2* pRotationCenter, float Rotation, 
      const DISX_VECTOR2* pTranslation);

// Build affine transformation matrix.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
DISX_MATRIX*  DISX_MatrixAffineTransformation
    ( DISX_MATRIX *pOut, float Scaling, const DISX_VECTOR3 *pRotationCenter,
      const DISX_QUATERNION *pRotation, const DISX_VECTOR3 *pTranslation);

// Build 2D affine transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
DISX_MATRIX*  DISX_MatrixAffineTransformation2D
    ( DISX_MATRIX *pOut, float Scaling, const DISX_VECTOR2* pRotationCenter, 
      float Rotation, const DISX_VECTOR2* pTranslation);

// Build a lookat matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixLookAtRH
    ( DISX_MATRIX *pOut, const DISX_VECTOR3 *pEye, const DISX_VECTOR3 *pAt,
      const DISX_VECTOR3 *pUp );

// Build a lookat matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixLookAtLH
    ( DISX_MATRIX *pOut, const DISX_VECTOR3 *pEye, const DISX_VECTOR3 *pAt,
      const DISX_VECTOR3 *pUp );

// Build a perspective projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveRH
    ( DISX_MATRIX *pOut, float w, float h, float zn, float zf );

// Build a perspective projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveLH
    ( DISX_MATRIX *pOut, float w, float h, float zn, float zf );

// Build a perspective projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveFovRH
    ( DISX_MATRIX *pOut, float fovy, float Aspect, float zn, float zf );

// Build a perspective projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveFovLH
    ( DISX_MATRIX *pOut, float fovy, float Aspect, float zn, float zf );

// Build a perspective projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveOffCenterRH
    ( DISX_MATRIX *pOut, float l, float r, float b, float t, float zn,
      float zf );

// Build a perspective projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixPerspectiveOffCenterLH
    ( DISX_MATRIX *pOut, float l, float r, float b, float t, float zn,
      float zf );

// Build an ortho projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixOrthoRH
    ( DISX_MATRIX *pOut, float w, float h, float zn, float zf );

// Build an ortho projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixOrthoLH
    ( DISX_MATRIX *pOut, float w, float h, float zn, float zf );

// Build an ortho projection matrix. (right-handed)
DISX_MATRIX*  DISX_MatrixOrthoOffCenterRH
    ( DISX_MATRIX *pOut, float l, float r, float b, float t, float zn,
      float zf );

// Build an ortho projection matrix. (left-handed)
DISX_MATRIX*  DISX_MatrixOrthoOffCenterLH
    ( DISX_MATRIX *pOut, float l, float r, float b, float t, float zn,
      float zf );

// Build a matrix which flattens geometry into a plane, as if casting
// a shadow from a light.
DISX_MATRIX*  DISX_MatrixShadow
    ( DISX_MATRIX *pOut, const DISX_VECTOR4 *pLight,
      const DISX_PLANE *pPlane );

// Build a matrix which reflects the coordinate system about a plane
DISX_MATRIX*  DISX_MatrixReflect
    ( DISX_MATRIX *pOut, const DISX_PLANE *pPlane );




//--------------------------
// Quaternion
//--------------------------

// inline

float DISX_QuaternionLength
    ( const DISX_QUATERNION *pQ );

// Length squared, or "norm"
float DISX_QuaternionLengthSq
    ( const DISX_QUATERNION *pQ );

float DISX_QuaternionDot
    ( const DISX_QUATERNION *pQ1, const DISX_QUATERNION *pQ2 );

// (0, 0, 0, 1)
DISX_QUATERNION* DISX_QuaternionIdentity
    ( DISX_QUATERNION *pOut );

bool DISX_QuaternionIsIdentity
    ( const DISX_QUATERNION *pQ );

// (-x, -y, -z, w)
DISX_QUATERNION* DISX_QuaternionConjugate
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ );


// non-inline


// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
void  DISX_QuaternionToAxisAngle
    ( const DISX_QUATERNION *pQ, DISX_VECTOR3 *pAxis, float *pAngle );

// Build a quaternion from a rotation matrix.
DISX_QUATERNION*  DISX_QuaternionRotationMatrix
    ( DISX_QUATERNION *pOut, const DISX_MATRIX *pM);

// Rotation about arbitrary axis.
DISX_QUATERNION*  DISX_QuaternionRotationAxis
    ( DISX_QUATERNION *pOut, const DISX_VECTOR3 *pV, float Angle );

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
DISX_QUATERNION*  DISX_QuaternionRotationYawPitchRoll
    ( DISX_QUATERNION *pOut, float Yaw, float Pitch, float Roll );

// Quaternion multiplication.  The result represents the rotation Q2
// followed by the rotation Q1.  (Out = Q2 * Q1)
DISX_QUATERNION*  DISX_QuaternionMultiply
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ1,
      const DISX_QUATERNION *pQ2 );

DISX_QUATERNION*  DISX_QuaternionNormalize
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ );

// Conjugate and re-norm
DISX_QUATERNION*  DISX_QuaternionInverse
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ );

// Expects unit quaternions.
// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
DISX_QUATERNION*  DISX_QuaternionLn
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ );

// Expects pure quaternions. (w == 0)  w is ignored in calculation.
// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
DISX_QUATERNION*  DISX_QuaternionExp
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ );
      
// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
// Expects unit quaternions.
DISX_QUATERNION*  DISX_QuaternionSlerp
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ1,
      const DISX_QUATERNION *pQ2, float t );

// Spherical quadrangle interpolation.
// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
DISX_QUATERNION*  DISX_QuaternionSquad
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ1,
      const DISX_QUATERNION *pA, const DISX_QUATERNION *pB,
      const DISX_QUATERNION *pC, float t );

// Setup control points for spherical quadrangle interpolation
// from Q1 to Q2.  The control points are chosen in such a way 
// to ensure the continuity of tangents with adjacent segments.
void  DISX_QuaternionSquadSetup
    ( DISX_QUATERNION *pAOut, DISX_QUATERNION *pBOut, DISX_QUATERNION *pCOut,
      const DISX_QUATERNION *pQ0, const DISX_QUATERNION *pQ1, 
      const DISX_QUATERNION *pQ2, const DISX_QUATERNION *pQ3 );

// Barycentric interpolation.
// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
DISX_QUATERNION*  DISX_QuaternionBaryCentric
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ1,
      const DISX_QUATERNION *pQ2, const DISX_QUATERNION *pQ3,
      float f, float g );




//--------------------------
// Plane
//--------------------------

// inline

// ax + by + cz + dw
float DISX_PlaneDot
    ( const DISX_PLANE *pP, const DISX_VECTOR4 *pV);

// ax + by + cz + d
float DISX_PlaneDotCoord
    ( const DISX_PLANE *pP, const DISX_VECTOR3 *pV);

// ax + by + cz
float DISX_PlaneDotNormal
    ( const DISX_PLANE *pP, const DISX_VECTOR3 *pV);

DISX_PLANE* DISX_PlaneScale
    (DISX_PLANE *pOut, const DISX_PLANE *pP, float s);

// non-inline

// Normalize plane (so that |a,b,c| == 1)
DISX_PLANE*  DISX_PlaneNormalize
    ( DISX_PLANE *pOut, const DISX_PLANE *pP);

// Find the intersection between a plane and a line.  If the line is
// parallel to the plane, NULL is returned.
DISX_VECTOR3*  DISX_PlaneIntersectLine
    ( DISX_VECTOR3 *pOut, const DISX_PLANE *pP, const DISX_VECTOR3 *pV1,
      const DISX_VECTOR3 *pV2);

// construct a plane from a point and a normal
DISX_PLANE*  DISX_PlaneFromPointNormal
    ( DISX_PLANE *pOut, const DISX_VECTOR3 *pPoint, const DISX_VECTOR3 *pNormal);

// construct a plane from 3 points
DISX_PLANE*  DISX_PlaneFromPoints
    ( DISX_PLANE *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2,
      const DISX_VECTOR3 *pV3);

// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
DISX_PLANE*  DISX_PlaneTransform
    ( DISX_PLANE *pOut, const DISX_PLANE *pP, const DISX_MATRIX *pM );
    
// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
DISX_PLANE*  DISX_PlaneTransformArray
    ( DISX_PLANE *pOut, UInt32 OutStride, const DISX_PLANE *pP, UInt32 PStride, const DISX_MATRIX *pM, UInt32 n );




//--------------------------
// Color
//--------------------------

// inline

// (1-r, 1-g, 1-b, a)
DISX_COLOR* DISX_ColorNegative
    (DISX_COLOR *pOut, const DISX_COLOR *pC);

DISX_COLOR* DISX_ColorAdd
    (DISX_COLOR *pOut, const DISX_COLOR *pC1, const DISX_COLOR *pC2);

DISX_COLOR* DISX_ColorSubtract
    (DISX_COLOR *pOut, const DISX_COLOR *pC1, const DISX_COLOR *pC2);

DISX_COLOR* DISX_ColorScale
    (DISX_COLOR *pOut, const DISX_COLOR *pC, float s);

// (r1*r2, g1*g2, b1*b2, a1*a2)
DISX_COLOR* DISX_ColorModulate
    (DISX_COLOR *pOut, const DISX_COLOR *pC1, const DISX_COLOR *pC2);

// Linear interpolation of r,g,b, and a. C1 + s(C2-C1)
DISX_COLOR* DISX_ColorLerp
    (DISX_COLOR *pOut, const DISX_COLOR *pC1, const DISX_COLOR *pC2, float s);

// non-inline


// Interpolate r,g,b between desaturated color and color.
// DesaturatedColor + s(Color - DesaturatedColor)
DISX_COLOR*  DISX_ColorAdjustSaturation
    (DISX_COLOR *pOut, const DISX_COLOR *pC, float s);

// Interpolate r,g,b between 50% grey and color.  Grey + s(Color - Grey)
DISX_COLOR*  DISX_ColorAdjustContrast
    (DISX_COLOR *pOut, const DISX_COLOR *pC, float c);






//--------------------------
// Misc
//--------------------------



// Calculate Fresnel term given the cosine of theta (likely obtained by
// taking the dot of two normals), and the refraction index of the material.
float  DISX_FresnelTerm
    (float CosTheta, float RefractionIndex);     






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


// non-inline


//============================================================================
//
//  Basic Spherical Harmonic math routines
//
//============================================================================

#define DISX_SH_MINORDER 2
#define DISX_SH_MAXORDER 6

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
    (  float *pOut, UInt32 Order, const DISX_VECTOR3 *pDir );
    
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
    ( float *pOut, UInt32 Order, const DISX_MATRIX *pMatrix, const float *pIn );
    
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
    ( float *pOut, UInt32 Order, float Angle, const float *pIn );
    
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
    ( float *pOut, UInt32 Order, const float *pA, const float *pB );

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
    ( float *pOut, UInt32 Order, const float *pIn, const float Scale );
    
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
    ( UInt32 Order, const float *pA, const float *pB );

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

float*  DISX_SHMultiply2( float *pOut, const float *pF, const float *pG);
float*  DISX_SHMultiply3( float *pOut, const float *pF, const float *pG);
float*  DISX_SHMultiply4( float *pOut, const float *pF, const float *pG);
float*  DISX_SHMultiply5( float *pOut, const float *pF, const float *pG);
float*  DISX_SHMultiply6( float *pOut, const float *pF, const float *pG);


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
      float *pROut, float *pGOut, float *pBOut );

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
      float *pROut, float *pGOut, float *pBOut );

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
      float *pROut, float *pGOut, float *pBOut );
      
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
      float *pROut, float *pGOut, float *pBOut );

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

#define DISX_INLINE inline
#include "DIS_math.inl"



#endif // DISX_9MATH_H

