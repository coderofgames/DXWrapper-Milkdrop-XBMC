//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) Microsoft Corporation.  All Rights Reserved.
//
//  File:       DISX_9math.inl
//  Content:    DISX_ math inline functions
//
//////////////////////////////////////////////////////////////////////////////

#ifndef DISX_MATH_INL
#define DISX_MATH_INL

//===========================================================================
//
// Inline Class Methods
//
//===========================================================================


//--------------------------
// 2D Vector
//--------------------------

DISX_INLINE
DISX_VECTOR2::DISX_VECTOR2( const float *pf )
{
#ifdef DISX__DEBUG
    if(!pf)
        return;
#endif

    x = pf[0];
    y = pf[1];
}


DISX_INLINE
DISX_VECTOR2::DISX_VECTOR2( float fx, float fy )
{
    x = fx;
    y = fy;
}


// casting
DISX_INLINE
DISX_VECTOR2::operator float* ()
{
    return (float *) &x;
}

DISX_INLINE
DISX_VECTOR2::operator const float* () const
{
    return (const float *) &x;
}


// assignment operators
DISX_INLINE DISX_VECTOR2&
DISX_VECTOR2::operator += ( const DISX_VECTOR2& v )
{
    x += v.x;
    y += v.y;
    return *this;
}

DISX_INLINE DISX_VECTOR2&
DISX_VECTOR2::operator -= ( const DISX_VECTOR2& v )
{
    x -= v.x;
    y -= v.y;
    return *this;
}

DISX_INLINE DISX_VECTOR2&
DISX_VECTOR2::operator *= ( float f )
{
    x *= f;
    y *= f;
    return *this;
}

DISX_INLINE DISX_VECTOR2&
DISX_VECTOR2::operator /= ( float f )
{
    float fInv = 1.0f / f;
    x *= fInv;
    y *= fInv;
    return *this;
}


// unary operators
DISX_INLINE DISX_VECTOR2
DISX_VECTOR2::operator + () const
{
    return *this;
}

DISX_INLINE DISX_VECTOR2
DISX_VECTOR2::operator - () const
{
    return DISX_VECTOR2(-x, -y);
}


// binary operators
DISX_INLINE DISX_VECTOR2
DISX_VECTOR2::operator + ( const DISX_VECTOR2& v ) const
{
    return DISX_VECTOR2(x + v.x, y + v.y);
}

DISX_INLINE DISX_VECTOR2
DISX_VECTOR2::operator - ( const DISX_VECTOR2& v ) const
{
    return DISX_VECTOR2(x - v.x, y - v.y);
}

DISX_INLINE DISX_VECTOR2
DISX_VECTOR2::operator * ( float f ) const
{
    return DISX_VECTOR2(x * f, y * f);
}

DISX_INLINE DISX_VECTOR2
DISX_VECTOR2::operator / ( float f ) const
{
    float fInv = 1.0f / f;
    return DISX_VECTOR2(x * fInv, y * fInv);
}

DISX_INLINE DISX_VECTOR2
operator * ( float f, const DISX_VECTOR2& v )
{
    return DISX_VECTOR2(f * v.x, f * v.y);
}

DISX_INLINE bool
DISX_VECTOR2::operator == ( const DISX_VECTOR2& v ) const
{
    return x == v.x && y == v.y;
}

DISX_INLINE bool
DISX_VECTOR2::operator != ( const DISX_VECTOR2& v ) const
{
    return x != v.x || y != v.y;
}



//--------------------------
// 3D Vector
//--------------------------
DISX_INLINE
DISX_VECTOR3::DISX_VECTOR3( const float *pf )
{
#ifdef DISX__DEBUG
    if(!pf)
        return;
#endif

    x = pf[0];
    y = pf[1];
    z = pf[2];
}

DISX_INLINE
DISX_VECTOR3::DISX_VECTOR3( const DIS_VECTOR& v )
{
    x = v.x;
    y = v.y;
    z = v.z;
}


DISX_INLINE
DISX_VECTOR3::DISX_VECTOR3( float fx, float fy, float fz )
{
    x = fx;
    y = fy;
    z = fz;
}


// casting
DISX_INLINE
DISX_VECTOR3::operator float* ()
{
    return (float *) &x;
}

DISX_INLINE
DISX_VECTOR3::operator const float* () const
{
    return (const float *) &x;
}


// assignment operators
DISX_INLINE DISX_VECTOR3&
DISX_VECTOR3::operator += ( const DISX_VECTOR3& v )
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

DISX_INLINE DISX_VECTOR3&
DISX_VECTOR3::operator -= ( const DISX_VECTOR3& v )
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

DISX_INLINE DISX_VECTOR3&
DISX_VECTOR3::operator *= ( float f )
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

DISX_INLINE DISX_VECTOR3&
DISX_VECTOR3::operator /= ( float f )
{
    float fInv = 1.0f / f;
    x *= fInv;
    y *= fInv;
    z *= fInv;
    return *this;
}


// unary operators
DISX_INLINE DISX_VECTOR3
DISX_VECTOR3::operator + () const
{
    return *this;
}

DISX_INLINE DISX_VECTOR3
DISX_VECTOR3::operator - () const
{
    return DISX_VECTOR3(-x, -y, -z);
}


// binary operators
DISX_INLINE DISX_VECTOR3
DISX_VECTOR3::operator + ( const DISX_VECTOR3& v ) const
{
    return DISX_VECTOR3(x + v.x, y + v.y, z + v.z);
}

DISX_INLINE DISX_VECTOR3
DISX_VECTOR3::operator - ( const DISX_VECTOR3& v ) const
{
    return DISX_VECTOR3(x - v.x, y - v.y, z - v.z);
}

DISX_INLINE DISX_VECTOR3
DISX_VECTOR3::operator * ( float f ) const
{
    return DISX_VECTOR3(x * f, y * f, z * f);
}

DISX_INLINE DISX_VECTOR3
DISX_VECTOR3::operator / ( float f ) const
{
    float fInv = 1.0f / f;
    return DISX_VECTOR3(x * fInv, y * fInv, z * fInv);
}


DISX_INLINE DISX_VECTOR3
operator * ( float f, const struct DISX_VECTOR3& v )
{
    return DISX_VECTOR3(f * v.x, f * v.y, f * v.z);
}


DISX_INLINE bool
DISX_VECTOR3::operator == ( const DISX_VECTOR3& v ) const
{
    return x == v.x && y == v.y && z == v.z;
}

DISX_INLINE bool
DISX_VECTOR3::operator != ( const DISX_VECTOR3& v ) const
{
    return x != v.x || y != v.y || z != v.z;
}






//--------------------------
// 4D Vector
//--------------------------
DISX_INLINE
DISX_VECTOR4::DISX_VECTOR4( const float *pf )
{
#ifdef DISX__DEBUG
    if(!pf)
        return;
#endif

    x = pf[0];
    y = pf[1];
    z = pf[2];
    w = pf[3];
}



DISX_INLINE
DISX_VECTOR4::DISX_VECTOR4( const DIS_VECTOR& v, float f )
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = f;
}

DISX_INLINE
DISX_VECTOR4::DISX_VECTOR4( float fx, float fy, float fz, float fw )
{
    x = fx;
    y = fy;
    z = fz;
    w = fw;
}


// casting
DISX_INLINE
DISX_VECTOR4::operator float* ()
{
    return (float *) &x;
}

DISX_INLINE
DISX_VECTOR4::operator const float* () const
{
    return (const float *) &x;
}


// assignment operators
DISX_INLINE DISX_VECTOR4&
DISX_VECTOR4::operator += ( const DISX_VECTOR4& v )
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

DISX_INLINE DISX_VECTOR4&
DISX_VECTOR4::operator -= ( const DISX_VECTOR4& v )
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

DISX_INLINE DISX_VECTOR4&
DISX_VECTOR4::operator *= ( float f )
{
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
}

DISX_INLINE DISX_VECTOR4&
DISX_VECTOR4::operator /= ( float f )
{
    float fInv = 1.0f / f;
    x *= fInv;
    y *= fInv;
    z *= fInv;
    w *= fInv;
    return *this;
}


// unary operators
DISX_INLINE DISX_VECTOR4
DISX_VECTOR4::operator + () const
{
    return *this;
}

DISX_INLINE DISX_VECTOR4
DISX_VECTOR4::operator - () const
{
    return DISX_VECTOR4(-x, -y, -z, -w);
}


// binary operators
DISX_INLINE DISX_VECTOR4
DISX_VECTOR4::operator + ( const DISX_VECTOR4& v ) const
{
    return DISX_VECTOR4(x + v.x, y + v.y, z + v.z, w + v.w);
}

DISX_INLINE DISX_VECTOR4
DISX_VECTOR4::operator - ( const DISX_VECTOR4& v ) const
{
    return DISX_VECTOR4(x - v.x, y - v.y, z - v.z, w - v.w);
}

DISX_INLINE DISX_VECTOR4
DISX_VECTOR4::operator * ( float f ) const
{
    return DISX_VECTOR4(x * f, y * f, z * f, w * f);
}

DISX_INLINE DISX_VECTOR4
DISX_VECTOR4::operator / ( float f ) const
{
    float fInv = 1.0f / f;
    return DISX_VECTOR4(x * fInv, y * fInv, z * fInv, w * fInv);
}

DISX_INLINE DISX_VECTOR4
operator * ( float f, const DISX_VECTOR4& v )
{
    return DISX_VECTOR4(f * v.x, f * v.y, f * v.z, f * v.w);
}


DISX_INLINE bool
DISX_VECTOR4::operator == ( const DISX_VECTOR4& v ) const
{
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

DISX_INLINE bool
DISX_VECTOR4::operator != ( const DISX_VECTOR4& v ) const
{
    return x != v.x || y != v.y || z != v.z || w != v.w;
}




//--------------------------
// Matrix
//--------------------------
DISX_INLINE
DISX_MATRIX::DISX_MATRIX( const float* pf )
{
#ifdef DISX__DEBUG
    if(!pf)
        return;
#endif

    memcpy(&_11, pf, sizeof(DISX_MATRIX));
}

DISX_INLINE
DISX_MATRIX::DISX_MATRIX( const DISX_MATRIX& mat )
{
    memcpy(&_11, &mat, sizeof(DISX_MATRIX));
}



DISX_INLINE
DISX_MATRIX::DISX_MATRIX( float f11, float f12, float f13, float f14,
                        float f21, float f22, float f23, float f24,
                        float f31, float f32, float f33, float f34,
                        float f41, float f42, float f43, float f44 )
{
    _11 = f11; _12 = f12; _13 = f13; _14 = f14;
    _21 = f21; _22 = f22; _23 = f23; _24 = f24;
    _31 = f31; _32 = f32; _33 = f33; _34 = f34;
    _41 = f41; _42 = f42; _43 = f43; _44 = f44;
}



// access grants
DISX_INLINE float&
DISX_MATRIX::operator () ( UInt32 iRow, UInt32 iCol )
{
    return m[iRow][iCol];
}

DISX_INLINE float
DISX_MATRIX::operator () ( UInt32 iRow, UInt32 iCol ) const
{
    return m[iRow][iCol];
}


// casting operators
DISX_INLINE
DISX_MATRIX::operator float* ()
{
    return (float *) &_11;
}

DISX_INLINE
DISX_MATRIX::operator const float* () const
{
    return (const float *) &_11;
}


// assignment operators
DISX_INLINE DISX_MATRIX&
DISX_MATRIX::operator *= ( const DISX_MATRIX& mat )
{
    DISX_MatrixMultiply(this, this, &mat);
    return *this;
}

DISX_INLINE DISX_MATRIX&
DISX_MATRIX::operator += ( const DISX_MATRIX& mat )
{
    _11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
    _21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
    _31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
    _41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
    return *this;
}

DISX_INLINE DISX_MATRIX&
DISX_MATRIX::operator -= ( const DISX_MATRIX& mat )
{
    _11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
    _21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
    _31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
    _41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
    return *this;
}

DISX_INLINE DISX_MATRIX&
DISX_MATRIX::operator *= ( float f )
{
    _11 *= f; _12 *= f; _13 *= f; _14 *= f;
    _21 *= f; _22 *= f; _23 *= f; _24 *= f;
    _31 *= f; _32 *= f; _33 *= f; _34 *= f;
    _41 *= f; _42 *= f; _43 *= f; _44 *= f;
    return *this;
}

DISX_INLINE DISX_MATRIX&
DISX_MATRIX::operator /= ( float f )
{
    float fInv = 1.0f / f;
    _11 *= fInv; _12 *= fInv; _13 *= fInv; _14 *= fInv;
    _21 *= fInv; _22 *= fInv; _23 *= fInv; _24 *= fInv;
    _31 *= fInv; _32 *= fInv; _33 *= fInv; _34 *= fInv;
    _41 *= fInv; _42 *= fInv; _43 *= fInv; _44 *= fInv;
    return *this;
}


// unary operators
DISX_INLINE DISX_MATRIX
DISX_MATRIX::operator + () const
{
    return *this;
}

DISX_INLINE DISX_MATRIX
DISX_MATRIX::operator - () const
{
    return DISX_MATRIX(-_11, -_12, -_13, -_14,
                      -_21, -_22, -_23, -_24,
                      -_31, -_32, -_33, -_34,
                      -_41, -_42, -_43, -_44);
}


// binary operators
DISX_INLINE DISX_MATRIX
DISX_MATRIX::operator * ( const DISX_MATRIX& mat ) const
{
    DISX_MATRIX matT;
    DISX_MatrixMultiply(&matT, this, &mat);
    return matT;
}

DISX_INLINE DISX_MATRIX
DISX_MATRIX::operator + ( const DISX_MATRIX& mat ) const
{
    return DISX_MATRIX(_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
                      _21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
                      _31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
                      _41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
}

DISX_INLINE DISX_MATRIX
DISX_MATRIX::operator - ( const DISX_MATRIX& mat ) const
{
    return DISX_MATRIX(_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
                      _21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
                      _31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
                      _41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
}

DISX_INLINE DISX_MATRIX
DISX_MATRIX::operator * ( float f ) const
{
    return DISX_MATRIX(_11 * f, _12 * f, _13 * f, _14 * f,
                      _21 * f, _22 * f, _23 * f, _24 * f,
                      _31 * f, _32 * f, _33 * f, _34 * f,
                      _41 * f, _42 * f, _43 * f, _44 * f);
}

DISX_INLINE DISX_MATRIX
DISX_MATRIX::operator / ( float f ) const
{
    float fInv = 1.0f / f;
    return DISX_MATRIX(_11 * fInv, _12 * fInv, _13 * fInv, _14 * fInv,
                      _21 * fInv, _22 * fInv, _23 * fInv, _24 * fInv,
                      _31 * fInv, _32 * fInv, _33 * fInv, _34 * fInv,
                      _41 * fInv, _42 * fInv, _43 * fInv, _44 * fInv);
}


DISX_INLINE DISX_MATRIX
operator * ( float f, const DISX_MATRIX& mat )
{
    return DISX_MATRIX(f * mat._11, f * mat._12, f * mat._13, f * mat._14,
                      f * mat._21, f * mat._22, f * mat._23, f * mat._24,
                      f * mat._31, f * mat._32, f * mat._33, f * mat._34,
                      f * mat._41, f * mat._42, f * mat._43, f * mat._44);
}


DISX_INLINE bool
DISX_MATRIX::operator == ( const DISX_MATRIX& mat ) const
{
    return 0 == memcmp(this, &mat, sizeof(DISX_MATRIX));
}

DISX_INLINE bool
DISX_MATRIX::operator != ( const DISX_MATRIX& mat ) const
{
    return 0 != memcmp(this, &mat, sizeof(DISX_MATRIX));
}






//--------------------------
// Quaternion
//--------------------------

DISX_INLINE
DISX_QUATERNION::DISX_QUATERNION( const float* pf )
{
#ifdef DISX__DEBUG
    if(!pf)
        return;
#endif

    x = pf[0];
    y = pf[1];
    z = pf[2];
    w = pf[3];
}



DISX_INLINE
DISX_QUATERNION::DISX_QUATERNION( float fx, float fy, float fz, float fw )
{
    x = fx;
    y = fy;
    z = fz;
    w = fw;
}


// casting
DISX_INLINE
DISX_QUATERNION::operator float* ()
{
    return (float *) &x;
}

DISX_INLINE
DISX_QUATERNION::operator const float* () const
{
    return (const float *) &x;
}


// assignment operators
DISX_INLINE DISX_QUATERNION&
DISX_QUATERNION::operator += ( const DISX_QUATERNION& q )
{
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;
    return *this;
}

DISX_INLINE DISX_QUATERNION&
DISX_QUATERNION::operator -= ( const DISX_QUATERNION& q )
{
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;
    return *this;
}

DISX_INLINE DISX_QUATERNION&
DISX_QUATERNION::operator *= ( const DISX_QUATERNION& q )
{
    DISX_QuaternionMultiply(this, this, &q);
    return *this;
}

DISX_INLINE DISX_QUATERNION&
DISX_QUATERNION::operator *= ( float f )
{
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
}

DISX_INLINE DISX_QUATERNION&
DISX_QUATERNION::operator /= ( float f )
{
    float fInv = 1.0f / f;
    x *= fInv;
    y *= fInv;
    z *= fInv;
    w *= fInv;
    return *this;
}


// unary operators
DISX_INLINE DISX_QUATERNION
DISX_QUATERNION::operator + () const
{
    return *this;
}

DISX_INLINE DISX_QUATERNION
DISX_QUATERNION::operator - () const
{
    return DISX_QUATERNION(-x, -y, -z, -w);
}


// binary operators
DISX_INLINE DISX_QUATERNION
DISX_QUATERNION::operator + ( const DISX_QUATERNION& q ) const
{
    return DISX_QUATERNION(x + q.x, y + q.y, z + q.z, w + q.w);
}

DISX_INLINE DISX_QUATERNION
DISX_QUATERNION::operator - ( const DISX_QUATERNION& q ) const
{
    return DISX_QUATERNION(x - q.x, y - q.y, z - q.z, w - q.w);
}

DISX_INLINE DISX_QUATERNION
DISX_QUATERNION::operator * ( const DISX_QUATERNION& q ) const
{
    DISX_QUATERNION qT;
    DISX_QuaternionMultiply(&qT, this, &q);
    return qT;
}

DISX_INLINE DISX_QUATERNION
DISX_QUATERNION::operator * ( float f ) const
{
    return DISX_QUATERNION(x * f, y * f, z * f, w * f);
}

DISX_INLINE DISX_QUATERNION
DISX_QUATERNION::operator / ( float f ) const
{
    float fInv = 1.0f / f;
    return DISX_QUATERNION(x * fInv, y * fInv, z * fInv, w * fInv);
}


DISX_INLINE DISX_QUATERNION
operator * (float f, const DISX_QUATERNION& q )
{
    return DISX_QUATERNION(f * q.x, f * q.y, f * q.z, f * q.w);
}


DISX_INLINE bool
DISX_QUATERNION::operator == ( const DISX_QUATERNION& q ) const
{
    return x == q.x && y == q.y && z == q.z && w == q.w;
}

DISX_INLINE bool
DISX_QUATERNION::operator != ( const DISX_QUATERNION& q ) const
{
    return x != q.x || y != q.y || z != q.z || w != q.w;
}



//--------------------------
// Plane
//--------------------------

DISX_INLINE
DISX_PLANE::DISX_PLANE( const float* pf )
{
#ifdef DISX__DEBUG
    if(!pf)
        return;
#endif

    a = pf[0];
    b = pf[1];
    c = pf[2];
    d = pf[3];
}



DISX_INLINE
DISX_PLANE::DISX_PLANE( float fa, float fb, float fc, float fd )
{
    a = fa;
    b = fb;
    c = fc;
    d = fd;
}


// casting
DISX_INLINE
DISX_PLANE::operator float* ()
{
    return (float *) &a;
}

DISX_INLINE
DISX_PLANE::operator const float* () const
{
    return (const float *) &a;
}


// assignment operators
DISX_INLINE DISX_PLANE&
DISX_PLANE::operator *= ( float f )
{
    a *= f;
    b *= f;
    c *= f;
    d *= f;
    return *this;
}

DISX_INLINE DISX_PLANE&
DISX_PLANE::operator /= ( float f )
{
    float fInv = 1.0f / f;
    a *= fInv;
    b *= fInv;
    c *= fInv;
    d *= fInv;
    return *this;
}


// unary operators
DISX_INLINE DISX_PLANE
DISX_PLANE::operator + () const
{
    return *this;
}

DISX_INLINE DISX_PLANE
DISX_PLANE::operator - () const
{
    return DISX_PLANE(-a, -b, -c, -d);
}


// binary operators
DISX_INLINE DISX_PLANE
DISX_PLANE::operator * ( float f ) const
{
    return DISX_PLANE(a * f, b * f, c * f, d * f);
}

DISX_INLINE DISX_PLANE
DISX_PLANE::operator / ( float f ) const
{
    float fInv = 1.0f / f;
    return DISX_PLANE(a * fInv, b * fInv, c * fInv, d * fInv);
}

DISX_INLINE DISX_PLANE
operator * (float f, const DISX_PLANE& p )
{
    return DISX_PLANE(f * p.a, f * p.b, f * p.c, f * p.d);
}

DISX_INLINE bool
DISX_PLANE::operator == ( const DISX_PLANE& p ) const
{
    return a == p.a && b == p.b && c == p.c && d == p.d;
}

DISX_INLINE bool
DISX_PLANE::operator != ( const DISX_PLANE& p ) const
{
    return a != p.a || b != p.b || c != p.c || d != p.d;
}




//--------------------------
// Color
//--------------------------

DISX_INLINE
DISX_COLOR::DISX_COLOR( UInt32 dw )
{
    const float f = 1.0f / 255.0f;
    r = f * (float) (unsigned char) (dw >> 16);
    g = f * (float) (unsigned char) (dw >>  8);
    b = f * (float) (unsigned char) (dw >>  0);
    a = f * (float) (unsigned char) (dw >> 24);
}

DISX_INLINE
DISX_COLOR::DISX_COLOR( const float* pf )
{
#ifdef DISX__DEBUG
    if(!pf)
        return;
#endif

    r = pf[0];
    g = pf[1];
    b = pf[2];
    a = pf[3];
}


DISX_INLINE
DISX_COLOR::DISX_COLOR( const DIS_COLORVALUE& c )
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

DISX_INLINE
DISX_COLOR::DISX_COLOR( float fr, float fg, float fb, float fa )
{
    r = fr;
    g = fg;
    b = fb;
    a = fa;
}


// casting
DISX_INLINE
DISX_COLOR::operator UInt32 () const
{
    UInt32 dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (UInt32) (r * 255.0f + 0.5f);
    UInt32 dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (UInt32) (g * 255.0f + 0.5f);
    UInt32 dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (UInt32) (b * 255.0f + 0.5f);
    UInt32 dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (UInt32) (a * 255.0f + 0.5f);

    return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}


DISX_INLINE
DISX_COLOR::operator float * ()
{
    return (float *) &r;
}

DISX_INLINE
DISX_COLOR::operator const float * () const
{
    return (const float *) &r;
}


DISX_INLINE
DISX_COLOR::operator DIS_COLORVALUE * ()
{
    return (DIS_COLORVALUE *) &r;
}

DISX_INLINE
DISX_COLOR::operator const DIS_COLORVALUE * () const
{
    return (const DIS_COLORVALUE *) &r;
}


DISX_INLINE
DISX_COLOR::operator DIS_COLORVALUE& ()
{
    return *((DIS_COLORVALUE *) &r);
}

DISX_INLINE
DISX_COLOR::operator const DIS_COLORVALUE& () const
{
    return *((const DIS_COLORVALUE *) &r);
}


// assignment operators
DISX_INLINE DISX_COLOR&
DISX_COLOR::operator += ( const DISX_COLOR& c )
{
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}

DISX_INLINE DISX_COLOR&
DISX_COLOR::operator -= ( const DISX_COLOR& c )
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
    return *this;
}

DISX_INLINE DISX_COLOR&
DISX_COLOR::operator *= ( float f )
{
    r *= f;
    g *= f;
    b *= f;
    a *= f;
    return *this;
}

DISX_INLINE DISX_COLOR&
DISX_COLOR::operator /= ( float f )
{
    float fInv = 1.0f / f;
    r *= fInv;
    g *= fInv;
    b *= fInv;
    a *= fInv;
    return *this;
}


// unary operators
DISX_INLINE DISX_COLOR
DISX_COLOR::operator + () const
{
    return *this;
}

DISX_INLINE DISX_COLOR
DISX_COLOR::operator - () const
{
    return DISX_COLOR(-r, -g, -b, -a);
}


// binary operators
DISX_INLINE DISX_COLOR
DISX_COLOR::operator + ( const DISX_COLOR& c ) const
{
    return DISX_COLOR(r + c.r, g + c.g, b + c.b, a + c.a);
}

DISX_INLINE DISX_COLOR
DISX_COLOR::operator - ( const DISX_COLOR& c ) const
{
    return DISX_COLOR(r - c.r, g - c.g, b - c.b, a - c.a);
}

DISX_INLINE DISX_COLOR
DISX_COLOR::operator * ( float f ) const
{
    return DISX_COLOR(r * f, g * f, b * f, a * f);
}

DISX_INLINE DISX_COLOR
DISX_COLOR::operator / ( float f ) const
{
    float fInv = 1.0f / f;
    return DISX_COLOR(r * fInv, g * fInv, b * fInv, a * fInv);
}


DISX_INLINE DISX_COLOR
operator * (float f, const DISX_COLOR& c )
{
    return DISX_COLOR(f * c.r, f * c.g, f * c.b, f * c.a);
}


DISX_INLINE bool
DISX_COLOR::operator == ( const DISX_COLOR& c ) const
{
    return r == c.r && g == c.g && b == c.b && a == c.a;
}

DISX_INLINE bool
DISX_COLOR::operator != ( const DISX_COLOR& c ) const
{
    return r != c.r || g != c.g || b != c.b || a != c.a;
}






//===========================================================================
//
// Inline functions
//
//===========================================================================


//--------------------------
// 2D Vector
//--------------------------

DISX_INLINE float DISX_Vec2Length
    ( const DISX_VECTOR2 *pV )
{
#ifdef DISX__DEBUG
    if(!pV)
        return 0.0f;
#endif

    return sqrtf(pV->x * pV->x + pV->y * pV->y);
}

DISX_INLINE float DISX_Vec2LengthSq
    ( const DISX_VECTOR2 *pV )
{
#ifdef DISX__DEBUG
    if(!pV)
        return 0.0f;
#endif

    return pV->x * pV->x + pV->y * pV->y;
}

DISX_INLINE float DISX_Vec2Dot
    ( const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pV1 || !pV2)
        return 0.0f;
#endif

    return pV1->x * pV2->x + pV1->y * pV2->y;
}

DISX_INLINE float DISX_Vec2CCW
    ( const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pV1 || !pV2)
        return 0.0f;
#endif

    return pV1->x * pV2->y - pV1->y * pV2->x;
}

DISX_INLINE DISX_VECTOR2* DISX_Vec2Add
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    return pOut;
}

DISX_INLINE DISX_VECTOR2* DISX_Vec2Subtract
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    return pOut;
}

DISX_INLINE DISX_VECTOR2* DISX_Vec2Minimize
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x < pV2->x ? pV1->x : pV2->x;
    pOut->y = pV1->y < pV2->y ? pV1->y : pV2->y;
    return pOut;
}

DISX_INLINE DISX_VECTOR2* DISX_Vec2Maximize
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x > pV2->x ? pV1->x : pV2->x;
    pOut->y = pV1->y > pV2->y ? pV1->y : pV2->y;
    return pOut;
}

DISX_INLINE DISX_VECTOR2* DISX_Vec2Scale
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV, float s )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV)
        return NULL;
#endif

    pOut->x = pV->x * s;
    pOut->y = pV->y * s;
    return pOut;
}

DISX_INLINE DISX_VECTOR2* DISX_Vec2Lerp
    ( DISX_VECTOR2 *pOut, const DISX_VECTOR2 *pV1, const DISX_VECTOR2 *pV2,
      float s )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + s * (pV2->x - pV1->x);
    pOut->y = pV1->y + s * (pV2->y - pV1->y);
    return pOut;
}


//--------------------------
// 3D Vector
//--------------------------

DISX_INLINE float DISX_Vec3Length
    ( const DISX_VECTOR3 *pV )
{
#ifdef DISX__DEBUG
    if(!pV)
        return 0.0f;
#endif


    return sqrtf(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);

}

DISX_INLINE float DISX_Vec3LengthSq
    ( const DISX_VECTOR3 *pV )
{
#ifdef DISX__DEBUG
    if(!pV)
        return 0.0f;
#endif

    return pV->x * pV->x + pV->y * pV->y + pV->z * pV->z;
}

DISX_INLINE float DISX_Vec3Dot
    ( const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pV1 || !pV2)
        return 0.0f;
#endif

    return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;
}

DISX_INLINE DISX_VECTOR3* DISX_Vec3Cross
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 )
{
    DISX_VECTOR3 v;

#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    v.x = pV1->y * pV2->z - pV1->z * pV2->y;
    v.y = pV1->z * pV2->x - pV1->x * pV2->z;
    v.z = pV1->x * pV2->y - pV1->y * pV2->x;

    *pOut = v;
    return pOut;
}

DISX_INLINE DISX_VECTOR3* DISX_Vec3Add
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    pOut->z = pV1->z + pV2->z;
    return pOut;
}

DISX_INLINE DISX_VECTOR3* DISX_Vec3Subtract
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    pOut->z = pV1->z - pV2->z;
    return pOut;
}

DISX_INLINE DISX_VECTOR3* DISX_Vec3Minimize
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x < pV2->x ? pV1->x : pV2->x;
    pOut->y = pV1->y < pV2->y ? pV1->y : pV2->y;
    pOut->z = pV1->z < pV2->z ? pV1->z : pV2->z;
    return pOut;
}

DISX_INLINE DISX_VECTOR3* DISX_Vec3Maximize
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x > pV2->x ? pV1->x : pV2->x;
    pOut->y = pV1->y > pV2->y ? pV1->y : pV2->y;
    pOut->z = pV1->z > pV2->z ? pV1->z : pV2->z;
    return pOut;
}

DISX_INLINE DISX_VECTOR3* DISX_Vec3Scale
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV, float s)
{
#ifdef DISX__DEBUG
    if(!pOut || !pV)
        return NULL;
#endif

    pOut->x = pV->x * s;
    pOut->y = pV->y * s;
    pOut->z = pV->z * s;
    return pOut;
}

DISX_INLINE DISX_VECTOR3* DISX_Vec3Lerp
    ( DISX_VECTOR3 *pOut, const DISX_VECTOR3 *pV1, const DISX_VECTOR3 *pV2,
      float s )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + s * (pV2->x - pV1->x);
    pOut->y = pV1->y + s * (pV2->y - pV1->y);
    pOut->z = pV1->z + s * (pV2->z - pV1->z);
    return pOut;
}


//--------------------------
// 4D Vector
//--------------------------

DISX_INLINE float DISX_Vec4Length
    ( const DISX_VECTOR4 *pV )
{
#ifdef DISX__DEBUG
    if(!pV)
        return 0.0f;
#endif


    return sqrtf(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z + pV->w * pV->w);

}

DISX_INLINE float DISX_Vec4LengthSq
    ( const DISX_VECTOR4 *pV )
{
#ifdef DISX__DEBUG
    if(!pV)
        return 0.0f;
#endif

    return pV->x * pV->x + pV->y * pV->y + pV->z * pV->z + pV->w * pV->w;
}

DISX_INLINE float DISX_Vec4Dot
    ( const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2 )
{
#ifdef DISX__DEBUG
    if(!pV1 || !pV2)
        return 0.0f;
#endif

    return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z + pV1->w * pV2->w;
}

DISX_INLINE DISX_VECTOR4* DISX_Vec4Add
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2)
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    pOut->z = pV1->z + pV2->z;
    pOut->w = pV1->w + pV2->w;
    return pOut;
}

DISX_INLINE DISX_VECTOR4* DISX_Vec4Subtract
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2)
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    pOut->z = pV1->z - pV2->z;
    pOut->w = pV1->w - pV2->w;
    return pOut;
}

DISX_INLINE DISX_VECTOR4* DISX_Vec4Minimize
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2)
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x < pV2->x ? pV1->x : pV2->x;
    pOut->y = pV1->y < pV2->y ? pV1->y : pV2->y;
    pOut->z = pV1->z < pV2->z ? pV1->z : pV2->z;
    pOut->w = pV1->w < pV2->w ? pV1->w : pV2->w;
    return pOut;
}

DISX_INLINE DISX_VECTOR4* DISX_Vec4Maximize
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2)
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x > pV2->x ? pV1->x : pV2->x;
    pOut->y = pV1->y > pV2->y ? pV1->y : pV2->y;
    pOut->z = pV1->z > pV2->z ? pV1->z : pV2->z;
    pOut->w = pV1->w > pV2->w ? pV1->w : pV2->w;
    return pOut;
}

DISX_INLINE DISX_VECTOR4* DISX_Vec4Scale
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV, float s)
{
#ifdef DISX__DEBUG
    if(!pOut || !pV)
        return NULL;
#endif

    pOut->x = pV->x * s;
    pOut->y = pV->y * s;
    pOut->z = pV->z * s;
    pOut->w = pV->w * s;
    return pOut;
}

DISX_INLINE DISX_VECTOR4* DISX_Vec4Lerp
    ( DISX_VECTOR4 *pOut, const DISX_VECTOR4 *pV1, const DISX_VECTOR4 *pV2,
      float s )
{
#ifdef DISX__DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + s * (pV2->x - pV1->x);
    pOut->y = pV1->y + s * (pV2->y - pV1->y);
    pOut->z = pV1->z + s * (pV2->z - pV1->z);
    pOut->w = pV1->w + s * (pV2->w - pV1->w);
    return pOut;
}


//--------------------------
// 4D Matrix
//--------------------------

DISX_INLINE DISX_MATRIX* DISX_MatrixIdentity
    ( DISX_MATRIX *pOut )
{
#ifdef DISX__DEBUG
    if(!pOut)
        return NULL;
#endif

    pOut->m[0][1] = pOut->m[0][2] = pOut->m[0][3] =
    pOut->m[1][0] = pOut->m[1][2] = pOut->m[1][3] =
    pOut->m[2][0] = pOut->m[2][1] = pOut->m[2][3] =
    pOut->m[3][0] = pOut->m[3][1] = pOut->m[3][2] = 0.0f;

    pOut->m[0][0] = pOut->m[1][1] = pOut->m[2][2] = pOut->m[3][3] = 1.0f;
    return pOut;
}


DISX_INLINE bool DISX_MatrixIsIdentity
    ( const DISX_MATRIX *pM )
{
#ifdef DISX__DEBUG
    if(!pM)
        return FALSE;
#endif

    return pM->m[0][0] == 1.0f && pM->m[0][1] == 0.0f && pM->m[0][2] == 0.0f && pM->m[0][3] == 0.0f &&
           pM->m[1][0] == 0.0f && pM->m[1][1] == 1.0f && pM->m[1][2] == 0.0f && pM->m[1][3] == 0.0f &&
           pM->m[2][0] == 0.0f && pM->m[2][1] == 0.0f && pM->m[2][2] == 1.0f && pM->m[2][3] == 0.0f &&
           pM->m[3][0] == 0.0f && pM->m[3][1] == 0.0f && pM->m[3][2] == 0.0f && pM->m[3][3] == 1.0f;
}


//--------------------------
// Quaternion
//--------------------------

DISX_INLINE float DISX_QuaternionLength
    ( const DISX_QUATERNION *pQ )
{
#ifdef DISX__DEBUG
    if(!pQ)
        return 0.0f;
#endif

    return sqrtf(pQ->x * pQ->x + pQ->y * pQ->y + pQ->z * pQ->z + pQ->w * pQ->w);

}

DISX_INLINE float DISX_QuaternionLengthSq
    ( const DISX_QUATERNION *pQ )
{
#ifdef DISX__DEBUG
    if(!pQ)
        return 0.0f;
#endif

    return pQ->x * pQ->x + pQ->y * pQ->y + pQ->z * pQ->z + pQ->w * pQ->w;
}

DISX_INLINE float DISX_QuaternionDot
    ( const DISX_QUATERNION *pQ1, const DISX_QUATERNION *pQ2 )
{
#ifdef DISX__DEBUG
    if(!pQ1 || !pQ2)
        return 0.0f;
#endif

    return pQ1->x * pQ2->x + pQ1->y * pQ2->y + pQ1->z * pQ2->z + pQ1->w * pQ2->w;
}


DISX_INLINE DISX_QUATERNION* DISX_QuaternionIdentity
    ( DISX_QUATERNION *pOut )
{
#ifdef DISX__DEBUG
    if(!pOut)
        return NULL;
#endif

    pOut->x = pOut->y = pOut->z = 0.0f;
    pOut->w = 1.0f;
    return pOut;
}

DISX_INLINE bool DISX_QuaternionIsIdentity
    ( const DISX_QUATERNION *pQ )
{
#ifdef DISX__DEBUG
    if(!pQ)
        return FALSE;
#endif

    return pQ->x == 0.0f && pQ->y == 0.0f && pQ->z == 0.0f && pQ->w == 1.0f;
}


DISX_INLINE DISX_QUATERNION* DISX_QuaternionConjugate
    ( DISX_QUATERNION *pOut, const DISX_QUATERNION *pQ )
{
#ifdef DISX__DEBUG
    if(!pOut || !pQ)
        return NULL;
#endif

    pOut->x = -pQ->x;
    pOut->y = -pQ->y;
    pOut->z = -pQ->z;
    pOut->w =  pQ->w;
    return pOut;
}


//--------------------------
// Plane
//--------------------------

DISX_INLINE float DISX_PlaneDot
    ( const DISX_PLANE *pP, const DISX_VECTOR4 *pV)
{
#ifdef DISX__DEBUG
    if(!pP || !pV)
        return 0.0f;
#endif

    return pP->a * pV->x + pP->b * pV->y + pP->c * pV->z + pP->d * pV->w;
}

DISX_INLINE float DISX_PlaneDotCoord
    ( const DISX_PLANE *pP, const DISX_VECTOR3 *pV)
{
#ifdef DISX__DEBUG
    if(!pP || !pV)
        return 0.0f;
#endif

    return pP->a * pV->x + pP->b * pV->y + pP->c * pV->z + pP->d;
}

DISX_INLINE float DISX_PlaneDotNormal
    ( const DISX_PLANE *pP, const DISX_VECTOR3 *pV)
{
#ifdef DISX__DEBUG
    if(!pP || !pV)
        return 0.0f;
#endif

    return pP->a * pV->x + pP->b * pV->y + pP->c * pV->z;
}

DISX_INLINE DISX_PLANE* DISX_PlaneScale
    (DISX_PLANE *pOut, const DISX_PLANE *pP, float s)
{
#ifdef DISX__DEBUG
    if(!pOut || !pP)
        return NULL;
#endif

    pOut->a = pP->a * s;
    pOut->b = pP->b * s;
    pOut->c = pP->c * s;
    pOut->d = pP->d * s;
    return pOut;
}


//--------------------------
// Color
//--------------------------

DISX_INLINE DISX_COLOR* DISX_ColorNegative
    (DISX_COLOR *pOut, const DISX_COLOR *pC)
{
#ifdef DISX__DEBUG
    if(!pOut || !pC)
        return NULL;
#endif

    pOut->r = 1.0f - pC->r;
    pOut->g = 1.0f - pC->g;
    pOut->b = 1.0f - pC->b;
    pOut->a = pC->a;
    return pOut;
}

DISX_INLINE DISX_COLOR* DISX_ColorAdd
    (DISX_COLOR *pOut, const DISX_COLOR *pC1, const DISX_COLOR *pC2)
{
#ifdef DISX__DEBUG
    if(!pOut || !pC1 || !pC2)
        return NULL;
#endif

    pOut->r = pC1->r + pC2->r;
    pOut->g = pC1->g + pC2->g;
    pOut->b = pC1->b + pC2->b;
    pOut->a = pC1->a + pC2->a;
    return pOut;
}

DISX_INLINE DISX_COLOR* DISX_ColorSubtract
    (DISX_COLOR *pOut, const DISX_COLOR *pC1, const DISX_COLOR *pC2)
{
#ifdef DISX__DEBUG
    if(!pOut || !pC1 || !pC2)
        return NULL;
#endif

    pOut->r = pC1->r - pC2->r;
    pOut->g = pC1->g - pC2->g;
    pOut->b = pC1->b - pC2->b;
    pOut->a = pC1->a - pC2->a;
    return pOut;
}

DISX_INLINE DISX_COLOR* DISX_ColorScale
    (DISX_COLOR *pOut, const DISX_COLOR *pC, float s)
{
#ifdef DISX__DEBUG
    if(!pOut || !pC)
        return NULL;
#endif

    pOut->r = pC->r * s;
    pOut->g = pC->g * s;
    pOut->b = pC->b * s;
    pOut->a = pC->a * s;
    return pOut;
}

DISX_INLINE DISX_COLOR* DISX_ColorModulate
    (DISX_COLOR *pOut, const DISX_COLOR *pC1, const DISX_COLOR *pC2)
{
#ifdef DISX__DEBUG
    if(!pOut || !pC1 || !pC2)
        return NULL;
#endif

    pOut->r = pC1->r * pC2->r;
    pOut->g = pC1->g * pC2->g;
    pOut->b = pC1->b * pC2->b;
    pOut->a = pC1->a * pC2->a;
    return pOut;
}

DISX_INLINE DISX_COLOR* DISX_ColorLerp
    (DISX_COLOR *pOut, const DISX_COLOR *pC1, const DISX_COLOR *pC2, float s)
{
#ifdef DISX__DEBUG
    if(!pOut || !pC1 || !pC2)
        return NULL;
#endif

    pOut->r = pC1->r + s * (pC2->r - pC1->r);
    pOut->g = pC1->g + s * (pC2->g - pC1->g);
    pOut->b = pC1->b + s * (pC2->b - pC1->b);
    pOut->a = pC1->a + s * (pC2->a - pC1->a);
    return pOut;
}


#endif // DISX_MATH_INL

