#ifndef DIS_RENDER_STATES_H
#define DIS_RENDER_STATES_H

typedef			unsigned short int			UInt16;
typedef			short int					Int16;
typedef			int							Int32;	
typedef			unsigned int				UInt32;	
typedef			unsigned char				Byte;
typedef			__int64					Int64;
typedef			unsigned __int64			UInt64;
typedef			float						Float;
typedef			double						Double;

#ifndef M_CSTR
typedef const char* M_CSTR;
#endif

#ifndef M_CTSTR
#define M_CTSTR M_CSTR
#endif

#define DIS_MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((Int32)(Byte)(ch0) | ((Int32)(Byte)(ch1) << 8) |   \
                ((Int32)(Byte)(ch2) << 16) | ((Int32)(Byte)(ch3) << 24 ))

#define DIS_FCC(ch4) ((((Int32)(ch4) & 0xFF) << 24) |     \
                  (((Int32)(ch4) & 0xFF00) << 8) |    \
                  (((Int32)(ch4) & 0xFF0000) >> 8) |  \
                  (((Int32)(ch4) & 0xFF000000) >> 24))

typedef enum DIS_BACKBUFFER_TYPE { 
  DIS_BACKBUFFER_TYPE_MONO         = 0,
  DIS_BACKBUFFER_TYPE_LEFT         = 1,
  DIS_BACKBUFFER_TYPE_RIGHT        = 2,
  DIS_BACKBUFFER_TYPE_FORCE_DWORD  = 0x7fffffff
} DIS_BACKBUFFER_TYPE;





typedef enum DIS_BASISTYPE { 
  DIS_BASIS_BEZIER       = 0,
  DIS_BASIS_BSPLINE      = 1,
  DIS_BASIS_CATMULL_ROM  = 2,
  DIS_BASIS_FORCE_DWORD  = 0x7fffffff
} DIS_BASISTYPE;




typedef enum DIS_BLEND { 
  DIS_BLEND_NONE			= 0,
  DIS_BLEND_ZERO             = 1,
  DIS_BLEND_ONE              = 2,
  DIS_BLEND_SRCCOLOR         = 3,
  DIS_BLEND_INVSRCCOLOR      = 4,
  DIS_BLEND_SRCALPHA         = 5,
  DIS_BLEND_INVSRCALPHA      = 6,
  DIS_BLEND_DESTALPHA        = 7,
  DIS_BLEND_INVDESTALPHA     = 8,
  DIS_BLEND_DESTCOLOR        = 9,
  DIS_BLEND_INVDESTCOLOR     = 10,
  DIS_BLEND_SRCALPHASAT      = 11,
  DIS_BLEND_BOTHSRCALPHA     = 12,
  DIS_BLEND_BOTHINVSRCALPHA  = 13,
  DIS_BLEND_BLENDFACTOR      = 14,
  DIS_BLEND_INVBLENDFACTOR   = 15,
  DIS_BLEND_SRCCOLOR2        = 16,
  DIS_BLEND_INVSRCCOLOR2     = 17,
  DIS_BLEND_FORCE_DWORD      = 0x7fffffff
} DIS_BLEND;




typedef enum DIS_BLENDOP { 
	DIS_BLEND_ZEROPAD = 0,
  DIS_BLENDOP_ADD          = 1,
  DIS_BLENDOP_SUBTRACT     = 2,
  DIS_BLENDOP_REVSUBTRACT  = 3,
  DIS_BLENDOP_MIN          = 4,
  DIS_BLENDOP_MAX          = 5,
  DIS_BLENDOP_FORCE_DWORD  = 0x7fffffff
} DIS_BLENDOP;



typedef enum DIS_CMPFUNC {
	DIS_CMP_NONE =0,
  DIS_CMP_NEVER         = 1,
  DIS_CMP_LESS          = 2,
  DIS_CMP_EQUAL         = 3,
  DIS_CMP_LESSEQUAL     = 4,
  DIS_CMP_GREATER       = 5,
  DIS_CMP_NOTEQUAL      = 6,
  DIS_CMP_GREATEREQUAL  = 7,
  DIS_CMP_ALWAYS        = 8,
  DIS_CMP_FORCE_DWORD   = 0x7fffffff
} DIS_CMPFUNC;



typedef enum _DIS_COMPOSERECTSOP { 
	DIS_COMPOSE_NONE = 0,
  DIS_COMPOSERECTS_COPY         = 1,
  DIS_COMPOSERECTS_OR           = 2,
  DIS_COMPOSERECTS_AND          = 3,
  DIS_COMPOSERECTS_NEG          = 4,
  DIS_COMPOSERECTS_FORCE_DWORD  = 0x7fffffff
} DIS_COMPOSERECTSOP;



typedef enum DIS_CUBEMAP_FACES { 
  DIS_CUBEMAP_FACE_POSITIVE_X   = 0,
  DIS_CUBEMAP_FACE_NEGATIVE_X   = 1,
  DIS_CUBEMAP_FACE_POSITIVE_Y   = 2,
  DIS_CUBEMAP_FACE_NEGATIVE_Y   = 3,
  DIS_CUBEMAP_FACE_POSITIVE_Z   = 4,
  DIS_CUBEMAP_FACE_NEGATIVE_Z   = 5,
  DIS_CUBEMAP_FACE_FORCE_DWORD  = 0xffffffff
} DIS_CUBEMAP_FACES;




typedef enum DIS_CULL { 
	DIS_CULL_DEFAULT		= 0,
  DIS_CULL_NONE         = 1,
  DIS_CULL_CW           = 2,
  DIS_CULL_CCW          = 3,
  DIS_CULL_FORCE_DWORD  = 0x7fffffff
} DIS_CULL;



typedef enum DIS_DEBUGMONITORTOKENS { 
  DIS_DMT_ENABLE       = 0,
  DIS_DMT_DISABLE      = 1,
  DIS_DMT_FORCE_DWORD  = 0x7fffffff
} DIS_DEBUGMONITORTOKENS;




typedef enum DIS_DECLMETHOD { 
  DIS_DECLMETHOD_DEFAULT           = 0,
  DIS_DECLMETHOD_PARTIALU          = 1,
  DIS_DECLMETHOD_PARTIALV          = 2,
  DIS_DECLMETHOD_CROSSUV           = 3,
  DIS_DECLMETHOD_UV                = 4,
  DIS_DECLMETHOD_LOOKUP            = 5,
  DIS_DECLMETHOD_LOOKUPPRESAMPLED  = 6
} DIS_DECLMETHOD;



typedef enum DIS_DECLTYPE { 
  DIS_DECLTYPE_FLOAT1     = 0,
  DIS_DECLTYPE_FLOAT2     = 1,
  DIS_DECLTYPE_FLOAT3     = 2,
  DIS_DECLTYPE_FLOAT4     = 3,
  DIS_DECLTYPE_DIS_COLOR   = 4,
  DIS_DECLTYPE_UBYTE4     = 5,
  DIS_DECLTYPE_SHORT2     = 6,
  DIS_DECLTYPE_SHORT4     = 7,
  DIS_DECLTYPE_UBYTE4N    = 8,
  DIS_DECLTYPE_SHORT2N    = 9,
  DIS_DECLTYPE_SHORT4N    = 10,
  DIS_DECLTYPE_USHORT2N   = 11,
  DIS_DECLTYPE_USHORT4N   = 12,
  DIS_DECLTYPE_UDEC3      = 13,
  DIS_DECLTYPE_DEC3N      = 14,
  DIS_DECLTYPE_FLOAT16_2  = 15,
  DIS_DECLTYPE_FLOAT16_4  = 16,
  DIS_DECLTYPE_UNUSED     = 17
} DIS_DECLTYPE;

#define MAXDIS_DECLTYPE      DIS_DECLTYPE_UNUSED
#define DIS_DECL_END() {0xFF,0,DIS_DECLTYPE_UNUSED,0,0,0}
#define MAX_DECL_SIZE  65

typedef enum DIS_DECLUSAGE { 
  DIS_DECLUSAGE_POSITION      = 0,
  DIS_DECLUSAGE_BLENDWEIGHT   = 1,
  DIS_DECLUSAGE_BLENDINDICES  = 2,
  DIS_DECLUSAGE_NORMAL        = 3,
  DIS_DECLUSAGE_PSIZE         = 4,
  DIS_DECLUSAGE_TEXCOORD      = 5,
  DIS_DECLUSAGE_TANGENT       = 6,
  DIS_DECLUSAGE_BINORMAL      = 7,
  DIS_DECLUSAGE_TESSFACTOR    = 8,
  DIS_DECLUSAGE_POSITIONT     = 9,
  DIS_DECLUSAGE_COLOR         = 10,
  DIS_DECLUSAGE_FOG           = 11,
  DIS_DECLUSAGE_DEPTH         = 12,
  DIS_DECLUSAGE_SAMPLE        = 13
} DIS_DECLUSAGE;



typedef enum DIS_DEGREETYPE { 
	DIS_DEGREE_DEFAULT = 0,
  DIS_DEGREE_LINEAR     = 1,
  DIS_DEGREE_QUADRATIC  = 2,
  DIS_DEGREE_CUBIC      = 3,
  DIS_DEGREE_QUINTIC    = 4,
  DIS_DEGREE_FORCE_DWORD  = 0x7fffffff
} DIS_DEGREETYPE;




typedef enum DIS_DEVTYPE { 
	DIS_DEVTYPE_DEFAULT = 0,
  DIS_DEVTYPE_HAL          = 1,
  DIS_DEVTYPE_NULLREF      = 2,
  DIS_DEVTYPE_REF          = 3,
  DIS_DEVTYPE_SW           = 4,
  DIS_DEVTYPE_FORCE_DWORD  = 0xffffffff
} DIS_DEVTYPE;



typedef enum DIS_DISPLAYROTATION {
	DIS_DISPLAY_ROT = 0,
  DIS_DISPLAYROTATION_IDENTITY  = 1,
  DIS_DISPLAYROTATION_90        = 2,
  DIS_DISPLAYROTATION_180       = 3,
  DIS_DISPLAYROTATION_270       = 4
} DIS_DISPLAYROTATION;




typedef enum DIS_FILLMODE {
	DIS_FILL_DEFAULT = 0,
  DIS_FILL_POINT        = 1,
  DIS_FILL_WIREFRAME    = 2,
  DIS_FILL_SOLID        = 3,
  DIS_FILL_FORCE_DWORD  = 0x7fffffff
} DIS_FILLMODE;



typedef enum DIS_FOGMODE { 
  DIS_FOG_NONE         = 0,
  DIS_FOG_EXP          = 1,
  DIS_FOG_EXP2         = 2,
  DIS_FOG_LINEAR       = 3,
  DIS_FOG_FORCE_DWORD  = 0x7fffffff
} DIS_FOGMODE;



typedef enum _DIS_FORMAT {
    DIS_FMT_UNKNOWN              ,//  0,
    DIS_FMT_R8G8B8               ,// 20,
    DIS_FMT_A8R8G8B8             ,// 21,
    DIS_FMT_X8R8G8B8             ,// 22,
    DIS_FMT_R5G6B5               ,// 23,
    DIS_FMT_X1R5G5B5             ,// 24,
    DIS_FMT_A1R5G5B5             ,// 25,
    DIS_FMT_A4R4G4B4             ,// 26,
    DIS_FMT_R3G3B2               ,// 27,
    DIS_FMT_A8                   ,// 28,
    DIS_FMT_A8R3G3B2             ,// 29,
    DIS_FMT_X4R4G4B4             ,// 30,
    DIS_FMT_A2B10G10R10          ,// 31,
    DIS_FMT_A8B8G8R8             ,// 32,
    DIS_FMT_X8B8G8R8             ,// 33,
    DIS_FMT_G16R16               ,// 34,
    DIS_FMT_A2R10G10B10          ,// 35,
    DIS_FMT_A16B16G16R16         ,// 36,

    DIS_FMT_A8P8                 ,// 40,
    DIS_FMT_P8                   ,// 41,

    DIS_FMT_L8                   ,// 50,
    DIS_FMT_A8L8                 ,// 51,
    DIS_FMT_A4L4                 ,// 52,

    DIS_FMT_V8U8                 ,// 60,
    DIS_FMT_L6V5U5               ,// 61,
    DIS_FMT_X8L8V8U8             ,// 62,
    DIS_FMT_Q8W8V8U8             ,// 63,
    DIS_FMT_V16U16               ,// 64,
    DIS_FMT_A2W10V10U10          ,// 67,

    DIS_FMT_UYVY                 ,// MAKEFOURCC('U', 'Y', 'V', 'Y'),
    DIS_FMT_R8G8_B8G8            ,// MAKEFOURCC('R', 'G', 'B', 'G'),
    DIS_FMT_YUY2                 ,// MAKEFOURCC('Y', 'U', 'Y', '2'),
    DIS_FMT_G8R8_G8B8            ,// MAKEFOURCC('G', 'R', 'G', 'B'),
    DIS_FMT_DXT1                 ,// MAKEFOURCC('D', 'X', 'T', '1'),
    DIS_FMT_DXT2                 ,// MAKEFOURCC('D', 'X', 'T', '2'),
    DIS_FMT_DXT3                 ,// MAKEFOURCC('D', 'X', 'T', '3'),
    DIS_FMT_DXT4                 ,// MAKEFOURCC('D', 'X', 'T', '4'),
    DIS_FMT_DXT5                 ,// MAKEFOURCC('D', 'X', 'T', '5'),

    DIS_FMT_D16_LOCKABLE         ,// 70,
    DIS_FMT_D32                  ,// 71,
    DIS_FMT_D15S1                ,// 73,
    DIS_FMT_D24S8                ,// 75,
    DIS_FMT_D24X8                ,// 77,
    DIS_FMT_D24X4S4              ,// 79,
    DIS_FMT_D16                  ,// 80,

    DIS_FMT_D32F_LOCKABLE        ,// 82,
    DIS_FMT_D24FS8               ,// 83,



    DIS_FMT_L16                  ,// 81,

    DIS_FMT_VERTEXDATA           ,//100,
    DIS_FMT_INDEX16              ,//101,
    DIS_FMT_INDEX32              ,//102,

    DIS_FMT_Q16W16V16U16         ,//110,

    DIS_FMT_MULTI2_ARGB8         ,// MAKEFOURCC('M','E','T','1'),

    DIS_FMT_R16F                 ,// 111,
    DIS_FMT_G16R16F              ,// 112,
    DIS_FMT_A16B16G16R16F        ,// 113,

    DIS_FMT_R32F                 ,// 114,
    DIS_FMT_G32R32F              ,// 115,
    DIS_FMT_A32B32G32R32F        ,// 116,

    DIS_FMT_CxV8U8               ,// 117,
//#if !defined(DIS__DISABLE_9EX)
    DIS_FMT_D32_LOCKABLE         ,// 84,
    DIS_FMT_S8_LOCKABLE          ,// 85,

    DIS_FMT_A1                   ,// 118,
    DIS_FMT_A2B10G10R10_XR_BIAS  ,// 119,
    DIS_FMT_BINARYBUFFER         ,// 199,


    DIS_FMT_FORCE_DWORD          =0x7fffffff
} DIS_FORMAT;



typedef enum DIS_LIGHTTYPE { 
	DIS_LIGHT_NONE		= 0,
  DIS_LIGHT_POINT        = 1,
  DIS_LIGHT_SPOT         = 2,
  DIS_LIGHT_DIRECTIONAL  = 3,
  DIS_LIGHT_AREA_POINT		= 4,
  DIS_LIGHT_AREA_SPOT = 5,
  DIS_LIGHT_VOLUME		= 6,
  DIS_LIGHT_FORCE_DWORD  = 0x7fffffff
} DIS_LIGHTTYPE;



typedef enum DIS_MATERIALCOLORSOURCE { 
  DIS_MCS_MATERIAL     = 0,
  DIS_MCS_COLOR1       = 1,
  DIS_MCS_COLOR2       = 2,
  DIS_MCS_FORCE_DWORD  = 0x7fffffff
} DIS_MATERIALCOLORSOURCE;



typedef enum DIS_MULTISAMPLE_TYPE { 
  DIS_MULTISAMPLE_NONE          = 0,
  DIS_MULTISAMPLE_NONMASKABLE   = 1,
  DIS_MULTISAMPLE_2_SAMPLES     = 2,
  DIS_MULTISAMPLE_3_SAMPLES     = 3,
  DIS_MULTISAMPLE_4_SAMPLES     = 4,
  DIS_MULTISAMPLE_5_SAMPLES     = 5,
  DIS_MULTISAMPLE_6_SAMPLES     = 6,
  DIS_MULTISAMPLE_7_SAMPLES     = 7,
  DIS_MULTISAMPLE_8_SAMPLES     = 8,
  DIS_MULTISAMPLE_9_SAMPLES     = 9,
  DIS_MULTISAMPLE_10_SAMPLES    = 10,
  DIS_MULTISAMPLE_11_SAMPLES    = 11,
  DIS_MULTISAMPLE_12_SAMPLES    = 12,
  DIS_MULTISAMPLE_13_SAMPLES    = 13,
  DIS_MULTISAMPLE_14_SAMPLES    = 14,
  DIS_MULTISAMPLE_15_SAMPLES    = 15,
  DIS_MULTISAMPLE_16_SAMPLES    = 16,
  DIS_MULTISAMPLE_FORCE_DWORD   = 0xffffffff
} DIS_MULTISAMPLE_TYPE;



typedef enum DIS_PATCHEDGESTYLE { 
  DIS_PATCHEDGE_DISCRETE     = 0,
  DIS_PATCHEDGE_CONTINUOUS   = 1,
  DIS_PATCHEDGE_FORCE_DWORD  = 0x7fffffff
} DIS_PATCHEDGESTYLE;




typedef enum DIS_POOL { 
  DIS_POOL_DEFAULT      = 0,
  DIS_POOL_MANAGED      = 1,
  DIS_POOL_SYSTEMMEM    = 2,
  DIS_POOL_SCRATCH      = 3,
  DIS_POOL_FORCE_DWORD  = 0x7fffffff
} DIS_POOL;



typedef enum DIS_PRIMITIVETYPE { 
	DIS_PT_DEFAULT = 0,
  DIS_PT_POINTLIST      = 1,
  DIS_PT_LINELIST       = 2,
  DIS_PT_LINESTRIP      = 3,
  DIS_PT_TRIANGLELIST   = 4,
  DIS_PT_TRIANGLESTRIP  = 5,
  DIS_PT_TRIANGLEFAN    = 6,
  DIS_PT_FORCE_DWORD    = 0x7fffffff
} DIS_PRIMITIVETYPE;



typedef enum DIS_QUERYTYPE { 
	DIS_QUERY_DEFAULT = 0,
  DIS_QUERYTYPE_VCACHE             = 1,
  DIS_QUERYTYPE_RESOURCEMANAGER    = 2,
  DIS_QUERYTYPE_VERTEXSTATS        = 3,
  DIS_QUERYTYPE_EVENT              = 4,
  DIS_QUERYTYPE_OCCLUSION          = 5,
  DIS_QUERYTYPE_TIMESTAMP          = 6,
  DIS_QUERYTYPE_TIMESTAMPDISJOINT  = 7,
  DIS_QUERYTYPE_TIMESTAMPFREQ      = 8,
  DIS_QUERYTYPE_PIPELINETIMINGS    = 9,
  DIS_QUERYTYPE_INTERFACETIMINGS   = 10,
  DIS_QUERYTYPE_VERTEXTIMINGS      = 11,
  DIS_QUERYTYPE_PIXELTIMINGS       = 12,
  DIS_QUERYTYPE_BANDWIDTHTIMINGS   = 13,
  DIS_QUERYTYPE_CACHEUTILIZATION   = 14,
  DIS_QUERYTYPE_MEMORYPRESSURE     = 15
} DIS_QUERYTYPE;



//Render States	Default Value
#define RS_ZB_FALSE		FALSE // DIS_ZB_FALSE
#define RS_ZB_TRUE		TRUE





typedef enum DIS_RENDERSTATETYPE { 
  DISRS_ZENABLE                     ,// 7,
  DISRS_FILLMODE                    ,// 8,
  DISRS_SHADEMODE                   ,// 9,
  DISRS_ZWRITEENABLE                ,// 14,
  DISRS_ALPHATESTENABLE             ,// 15,
  DISRS_LASTPIXEL                   ,// 16,
  DISRS_SRCBLEND                    ,// 19,
  DISRS_DESTBLEND                   ,// 20,
  DISRS_CULLMODE                    ,// 22,
  DISRS_ZFUNC                       ,// 23,
  DISRS_ALPHAREF                    ,// 24,
  DISRS_ALPHAFUNC                   ,// 25,
  DISRS_DITHERENABLE                ,// 26,
  DISRS_ALPHABLENDENABLE            ,// 27,
  DISRS_FOGENABLE                   ,// 28,
  DISRS_SPECULARENABLE              ,// 29,
  DISRS_FOGCOLOR                    ,// 34,
  DISRS_FOGTABLEMODE                ,// 35,
  DISRS_FOGSTART                    ,// 36,
  DISRS_FOGEND                      ,// 37,
  DISRS_FOGDENSITY                  ,// 38,
  DISRS_RANGEFOGENABLE              ,// 48,
  DISRS_STENCILENABLE               ,// 52,
  DISRS_STENCILFAIL                 ,// 53,
  DISRS_STENCILZFAIL                ,// 54,
  DISRS_STENCILPASS                 ,// 55,
  DISRS_STENCILFUNC                 ,// 56,
  DISRS_STENCILREF                  ,// 57,
  DISRS_STENCILMASK                 ,// 58,
  DISRS_STENCILWRITEMASK            ,// 59,
  DISRS_TEXTUREFACTOR               ,// 60,
  DISRS_WRAP0                       ,// 128,
  DISRS_WRAP1                       ,// 129,
  DISRS_WRAP2                       ,// 130,
  DISRS_WRAP3                       ,// 131,
  DISRS_WRAP4                       ,// 132,
  DISRS_WRAP5                       ,// 133,
  DISRS_WRAP6                       ,// 134,
  DISRS_WRAP7                       ,// 135,
  DISRS_CLIPPING                    ,// 136,
  DISRS_LIGHTING                    ,// 137,
  DISRS_AMBIENT                     ,// 139,
  DISRS_FOGVERTEXMODE               ,// 140,
  DISRS_COLORVERTEX                 ,// 141,
  DISRS_LOCALVIEWER                 ,// 142,
  DISRS_NORMALIZENORMALS            ,// 143,
  DISRS_DIFFUSEMATERIALSOURCE       ,// 145,
  DISRS_SPECULARMATERIALSOURCE      ,// 146,
  DISRS_AMBIENTMATERIALSOURCE       ,// 147,
  DISRS_EMISSIVEMATERIALSOURCE      ,// 148,
  DISRS_VERTEXBLEND                 ,// 151,
  DISRS_CLIPPLANEENABLE             ,// 152,
  DISRS_POINTSIZE                   ,// 154,
  DISRS_POINTSIZE_MIN               ,// 155,
  DISRS_POINTSPRITEENABLE           ,// 156,
  DISRS_POINTSCALEENABLE            ,// 157,
  DISRS_POINTSCALE_A                ,// 158,
  DISRS_POINTSCALE_B                ,// 159,
  DISRS_POINTSCALE_C                ,// 160,
  DISRS_MULTISAMPLEANTIALIAS        ,// 161,
  DISRS_MULTISAMPLEMASK             ,// 162,
  DISRS_PATCHEDGESTYLE              ,// 163,
  DISRS_DEBUGMONITORTOKEN           ,// 165,
  DISRS_POINTSIZE_MAX               ,// 166,
  DISRS_INDEXEDVERTEXBLENDENABLE    ,// 167,
  DISRS_COLORWRITEENABLE            ,// 168,
  DISRS_TWEENFACTOR                 ,// 170,
  DISRS_BLENDOP                     ,// 171,
  DISRS_POSITIONDEGREE              ,// 172,
  DISRS_NORMALDEGREE                ,// 173,
  DISRS_SCISSORTESTENABLE           ,// 174,
  DISRS_SLOPESCALEDEPTHBIAS         ,// 175,
  DISRS_ANTIALIASEDLINEENABLE       ,// 176,
  DISRS_MINTESSELLATIONLEVEL        ,// 178,
  DISRS_MAXTESSELLATIONLEVEL        ,// 179,
  DISRS_ADAPTIVETESS_X              ,// 180,
  DISRS_ADAPTIVETESS_Y              ,// 181,
  DISRS_ADAPTIVETESS_Z              ,// 182,
  DISRS_ADAPTIVETESS_W              ,// 183,
  DISRS_ENABLEADAPTIVETESSELLATION  ,// 184,
  DISRS_TWOSIDEDSTENCILMODE         ,// 185,
  DISRS_CCW_STENCILFAIL             ,// 186,
  DISRS_CCW_STENCILZFAIL            ,// 187,
  DISRS_CCW_STENCILPASS             ,// 188,
  DISRS_CCW_STENCILFUNC             ,// 189,
  DISRS_COLORWRITEENABLE1           ,// 190,
  DISRS_COLORWRITEENABLE2           ,// 191,
  DISRS_COLORWRITEENABLE3           ,// 192,
  DISRS_BLENDFACTOR                 ,// 193,
  DISRS_SRGBWRITEENABLE             ,// 194,
  DISRS_DEPTHBIAS                   ,// 195,
  DISRS_WRAP8                       ,// 198,
  DISRS_WRAP9                       ,// 199,
  DISRS_WRAP10                      ,// 200,
  DISRS_WRAP11                      ,// 201,
  DISRS_WRAP12                      ,// 202,
  DISRS_WRAP13                      ,// 203,
  DISRS_WRAP14                      ,// 204,
  DISRS_WRAP15                      ,// 205,
  DISRS_SEPARATEALPHABLENDENABLE    ,// 206,
  DISRS_SRCBLENDALPHA               ,// 207,
  DISRS_DESTBLENDALPHA              ,// 208,
  DISRS_BLENDOPALPHA                ,// 209,
  DIS_FORCE_DWORD                 = 0x7fffffff
}DIS_RENDERSTATETYPE;


typedef enum DIS_RESOURCETYPE { 
  DIS_RTYPE_SURFACE        = 0,
  DIS_RTYPE_VOLUME         = 1,
  DIS_RTYPE_TEXTURE        = 2,
  DIS_RTYPE_VOLUMETEXTURE  = 3,
  DIS_RTYPE_CUBETEXTURE    = 4,
  DIS_RTYPE_VERTEXBUFFER   = 5,
  DIS_RTYPE_INDEXBUFFER    = 6,
  DIS_RTYPE_FORCE_DWORD    = 0x7fffffff
} DIS_RESOURCETYPE;

/* Lock flags */

#define DIS_LOCK_READONLY           0x00000010L
#define DIS_LOCK_DISCARD            0x00002000L
#define DIS_LOCK_NOOVERWRITE        0x00001000L
#define DIS_LOCK_NOSYSLOCK          0x00000800L
#define DIS_LOCK_DONOTWAIT          0x00004000L                  

#define DIS_LOCK_NO_DIRTY_UPDATE     0x00008000L

/* Vertex Buffer Description */
typedef struct DIS_VERTEXBUFFER_DESC
{
    DIS_FORMAT           Format;
    DIS_RESOURCETYPE     Type;
    UInt32               Usage;
    DIS_POOL             Pool;
    UInt32                Size;

    UInt32               FVF;

} DIS_VERTEXBUFFER_DESC;

/* Index Buffer Description */
typedef struct DIS_INDEXBUFFER_DESC
{
    DIS_FORMAT           Format;
    DIS_RESOURCETYPE     Type;
    UInt32               Usage;
    DIS_POOL             Pool;
    UInt32                Size;
} DIS_INDEXBUFFER_DESC;


/* Surface Description */
typedef struct DIS_SURFACE_DESC
{
    DIS_FORMAT           Format;
    DIS_RESOURCETYPE     Type;
    UInt32               Usage;
    DIS_POOL             Pool;

    DIS_MULTISAMPLE_TYPE MultiSampleType;
    UInt32               MultiSampleQuality;
    UInt32                Width;
    UInt32                Height;
} DIS_SURFACE_DESC, DIS_TEXTURE2D_DESC;

typedef struct DIS_VOLUME_DESC
{
    DIS_FORMAT           Format;
    DIS_RESOURCETYPE     Type;
    UInt32               Usage;
    DIS_POOL             Pool;

    UInt32                Width;
    UInt32                Height;
    UInt32                Depth;
} DIS_VOLUME_DESC;

typedef struct DIS_LOCKED_BOX
{
    Int32                 RowPitch;
    Int32                 SlicePitch;
    void*               pBits;
} DIS_LOCKED_BOX;

/* Structures for LockRange */
typedef struct DIS_RANGE
{
    UInt32                Offset;
    UInt32                Size;
} DIS_RANGE;




typedef enum DIS_SAMPLER_TEXTURE_TYPE { 
  DIS_STT_UNKNOWN,
  DIS_STT_2D,
  DIS_STT_CUBE,
  DIS_STT_VOLUME,
  DIS_STT_FORCE_DWORD = 0x7fffffff
} DIS_SAMPLER_TEXTURE_TYPE;





typedef enum DIS_SAMPLERSTATETYPE {
	DIS_SAMP_DEFAULT = 0,
  DIS_SAMP_ADDRESSU       = 1,
  DIS_SAMP_ADDRESSV       = 2,
  DIS_SAMP_ADDRESSW       = 3,
  DIS_SAMP_BORDERCOLOR    = 4,
  DIS_SAMP_MAGFILTER      = 5,
  DIS_SAMP_MINFILTER      = 6,
  DIS_SAMP_MIPFILTER      = 7,
  DIS_SAMP_MIPMAPLODBIAS  = 8,
  DIS_SAMP_MAXMIPLEVEL    = 9,
  DIS_SAMP_MAXANISOTROPY  = 10,
  DIS_SAMP_SRGBTEXTURE    = 11,
  DIS_SAMP_ELEMENTINDEX   = 12,
  DIS_SAMP_DMAPOFFSET     = 13,
  DIS_SAMP_FORCE_DWORD    = 0x7fffffff
} DIS_SAMPLERSTATETYPE;



typedef enum DIS_SCANLINEORDERING { 
	DIS_SCANLINEORDERING_DEFAULT = 0,
  DIS_SCANLINEORDERING_PROGRESSIVE  = 1,
  DIS_SCANLINEORDERING_INTERLACED   = 2
} DIS_SCANLINEORDERING;




typedef enum DIS_SHADEMODE { 
	DIS_SHADE_DEFAULT = 0,
  DIS_SHADE_FLAT         = 1,
  DIS_SHADE_GOURAUD      = 2,
  DIS_SHADE_PHONG        = 3,
  DIS_SHADE_COOK_TORRENCE = 4,
  DIS_SHADE_FORCE_DWORD  = 0x7fffffff
} DIS_SHADEMODE;



typedef enum _DIS_STATEBLOCKTYPE {
	DIS_SBT_NULL = 0,
  DIS_SBT_ALL          = 1,
  DIS_SBT_PIXELSTATE   = 2,
  DIS_SBT_VERTEXSTATE  = 3,
  DIS_SBT_FORCE_DWORD  = 0x7fffffff
} DIS_STATEBLOCKTYPE;




typedef enum DIS_STENCILOP {
	DIS_STENCILOP_NULL = 0,
  DIS_STENCILOP_KEEP         = 1,
  DIS_STENCILOP_ZERO         = 2,
  DIS_STENCILOP_REPLACE      = 3,
  DIS_STENCILOP_INCRSAT      = 4,
  DIS_STENCILOP_DECRSAT      = 5,
  DIS_STENCILOP_INVERT       = 6,
  DIS_STENCILOP_INCR         = 7,
  DIS_STENCILOP_DECR         = 8,
  DIS_STENCILOP_FORCE_DWORD  = 0x7fffffff
} DIS_STENCILOP;



typedef enum DIS_SWAPEFFECT 
{ 
	DIS_SWAPEFFECT_DEFAULT = 0,
  DIS_SWAPEFFECT_DISCARD      = 1,
  DIS_SWAPEFFECT_FLIP         = 2,
  DIS_SWAPEFFECT_COPY         = 3,
  DIS_SWAPEFFECT_OVERLAY      = 4,
  DIS_SWAPEFFECT_FLIPEX       = 5,
  DIS_SWAPEFFECT_FORCE_DWORD  = 0xFFFFFFFF
} DIS_SWAPEFFECT;



typedef enum DIS_TEXTUREADDRESS {
	DIS_TADDRESS_DEFAULT = 0,
  DIS_TADDRESS_WRAP         = 1,
  DIS_TADDRESS_MIRROR       = 2,
  DIS_TADDRESS_CLAMP        = 3,
  DIS_TADDRESS_BORDER       = 4,
  DIS_TADDRESS_MIRRORONCE   = 5,
  DIS_TADDRESS_FORCE_DWORD  = 0x7fffffff
} DIS_TEXTUREADDRESS;




typedef enum DIS_TEXTUREFILTERTYPE { 
  DIS_TEXF_NONE             = 0,
  DIS_TEXF_POINT            = 1,
  DIS_TEXF_LINEAR           = 2,
  DIS_TEXF_ANISOTROPIC      = 3,
  DIS_TEXF_PYRAMIDALQUAD    = 4,
  DIS_TEXF_GAUSSIANQUAD     = 5,
  DIS_TEXF_CONVOLUTIONMONO  = 6,
  DIS_TEXF_FORCE_DWORD      = 0x7fffffff
} DIS_TEXTUREFILTERTYPE;

#define DIS_TA_SELECTMASK        0x0000000f  // mask for arg selector
#define DIS_TA_DIFFUSE           0x00000000  // select diffuse color (read only)
#define DIS_TA_CURRENT           0x00000001  // select stage destination register (read/write)
#define DIS_TA_TEXTURE           0x00000002  // select texture color (read only)
#define DIS_TA_TFACTOR           0x00000003  // select D3DRS_TEXTUREFACTOR (read only)
#define DIS_TA_SPECULAR          0x00000004  // select specular color (read only)
#define DIS_TA_TEMP              0x00000005  // select temporary register color (read/write)
#define DIS_TA_CONSTANT          0x00000006  // select texture stage constant
#define DIS_TA_COMPLEMENT        0x00000010  // take 1.0 - x (read modifier)
#define DIS_TA_ALPHAREPLICATE    0x00000020  // replicate alpha to color components (read modifier)

typedef enum DIS_TEXTUREOP { 
	DIS_TOP_NULL = 0,
  DIS_TOP_DISABLE                    = 1,
  DIS_TOP_SELECTARG1                 = 2,
  DIS_TOP_SELECTARG2                 = 3,
  DIS_TOP_MODULATE                   = 4,
  DIS_TOP_MODULATE2X                 = 5,
  DIS_TOP_MODULATE4X                 = 6,
  DIS_TOP_ADD                        = 7,
  DIS_TOP_ADDSIGNED                  = 8,
  DIS_TOP_ADDSIGNED2X                = 9,
  DIS_TOP_SUBTRACT                   = 10,
  DIS_TOP_ADDSMOOTH                  = 11,
  DIS_TOP_BLENDDIFFUSEALPHA          = 12,
  DIS_TOP_BLENDTEXTUREALPHA          = 13,
  DIS_TOP_BLENDFACTORALPHA           = 14,
  DIS_TOP_BLENDTEXTUREALPHAPM        = 15,
  DIS_TOP_BLENDCURRENTALPHA          = 16,
  DIS_TOP_PREMODULATE                = 17,
  DIS_TOP_MODULATEALPHA_ADDCOLOR     = 18,
  DIS_TOP_MODULATECOLOR_ADDALPHA     = 19,
  DIS_TOP_MODULATEINVALPHA_ADDCOLOR  = 20,
  DIS_TOP_MODULATEINVCOLOR_ADDALPHA  = 21,
  DIS_TOP_BUMPENVMAP                 = 22,
  DIS_TOP_BUMPENVMAPLUMINANCE        = 23,
  DIS_TOP_DOTPRODUCT3                = 24,
  DIS_TOP_MULTIPLYADD                = 25,
  DIS_TOP_LERP                       = 26,
  DIS_TOP_FORCE_DWORD                = 0x7fffffff
} DIS_TEXTUREOP;



typedef enum DIS_TEXTURESTAGESTATETYPE { 
	DIS_TSS_DEFAULT = 0,
  DIS_TSS_COLOROP                ,// 1,
  DIS_TSS_COLORARG1              ,// 2,
  DIS_TSS_COLORARG2              ,// 3,
  DIS_TSS_ALPHAOP                ,// 4,
  DIS_TSS_ALPHAARG1              ,// 5,
  DIS_TSS_ALPHAARG2              ,// 6,
  DIS_TSS_BUMPENVMAT00           ,// 7,
  DIS_TSS_BUMPENVMAT01           ,// 8,
  DIS_TSS_BUMPENVMAT10           ,// 9,
  DIS_TSS_BUMPENVMAT11           ,// 10,
  DIS_TSS_TEXCOORDINDEX          ,// 11,
  DIS_TSS_BUMPENVLSCALE          ,// 22,
  DIS_TSS_BUMPENVLOFFSET         ,// 23,
  DIS_TSS_TEXTURETRANSFORMFLAGS  ,// 24,
  DIS_TSS_COLORARG0              ,// 26,
  DIS_TSS_ALPHAARG0              ,// 27,
  DIS_TSS_RESULTARG              ,// 28,
  DIS_TSS_CONSTANT               ,// 32,
  DIS_TSS_FORCE_DWORD            = 0x7fffffff
} DIS_TEXTURESTAGESTATETYPE;



typedef enum DIS_TEXTURETRANSFORMFLAGS { 
  DIS_TTFF_DISABLE      = 0,
  DIS_TTFF_COUNT1       = 1,
  DIS_TTFF_COUNT2       = 2,
  DIS_TTFF_COUNT3       = 3,
  DIS_TTFF_COUNT4       = 4,
  DIS_TTFF_PROJECTED    = 5,
  DIS_TTFF_FORCE_DWORD  = 0x7fffffff
} DIS_TEXTURETRANSFORMFLAGS;



typedef enum DIS_TRANSFORMSTATETYPE { 
  DIS_TS_NULL,
  DIS_TS_WORLD,
  DIS_TS_VIEW         ,// 2,
  DIS_TS_PROJECTION   ,// 3,
  DIS_TS_TEXTURE0     ,// 16,
  DIS_TS_TEXTURE1     ,// 17,
  DIS_TS_TEXTURE2     ,// 18,
  DIS_TS_TEXTURE3     ,// 19,
  DIS_TS_TEXTURE4     ,// 20,
  DIS_TS_TEXTURE5     ,// 21,
  DIS_TS_TEXTURE6     ,// 22,
  DIS_TS_TEXTURE7     ,// 23,
  DIS_TS_FORCE_DWORD  = 0x7fffffff
} DIS_TRANSFORMSTATETYPE;




typedef enum DIS_VERTEXBLENDFLAGS { 
  DIS_VBF_DISABLE   = 0,
  DIS_VBF_1WEIGHTS  = 1,
  DIS_VBF_2WEIGHTS  = 2,
  DIS_VBF_3WEIGHTS  = 3,
  DIS_VBF_TWEENING  = 4,
  DIS_VBF_0WEIGHTS  = 5
} DIS_VERTEXBLENDFLAGS;



typedef enum DIS_ZBUFFERTYPE { 
  DIS_ZB_FALSE        = 0,
  DIS_ZB_TRUE         = 1,
  DIS_ZB_USEW         = 2,
  DIS_ZB_FORCE_DWORD  = 0x7fffffff
} DIS_ZBUFFERTYPE;


enum DIS_RESULT
{
	DIS_OK,
	DIS_FAIL,
	DIS_ERR_NOTAVAILABLE,
	DIS_UNSUPPORTED,
	DIS_MEDIANOTFOUND,
	DIS_DEVICEFAILED,
	DIS_ERR_INVALIDCALL, 
	DIS_ERR_OUTOFVIDEOMEMORY, 
	DIS_E_OUTOFMEMORY
};



typedef UInt32 DIS_COLOR;

typedef struct DIS_Rect
{
	UInt32 x1,y1,x2,y2;

} DIS_Rect;


typedef struct DIS_BOX {
  UInt32 Left;
  UInt32 Top;
  UInt32 Right;
  UInt32 Bottom;
  UInt32 Front;
  UInt32 Back;
} DIS_BOX, *LPDIS_BOX;

typedef struct DIS_LOCKED_RECT {
  Int32  Pitch;
  void *pBits;
} DIS_LOCKED_RECT, *LPLOCKED_RECT;


typedef struct DIS_VERTEXELEMENT {
  UInt16 Stream;
  UInt16 Offset;
  Byte Type;
  Byte Method;
  Byte Usage;
  Byte UsageIndex;
} DIS_VERTEXELEMENT, *LPVERTEXELEMENT;


typedef struct DIS_RECTPATCH_INFO {
  UInt32          StartVertexOffsetWidth;
  UInt32		  StartVertexOffsetHeight;
  UInt32          Width;
  UInt32          Height;
  UInt32          Stride;
  DIS_BASISTYPE  Basis;
  DIS_DEGREETYPE Degree;
} DIS_RECTPATCH_INFO , *LPRECTPATCH_INFO;

typedef struct DIS_TRIPATCH_INFO {
  UInt32          StartVertexOffset;
  UInt32          NumVertices;
  DIS_BASISTYPE  Basis;
  DIS_DEGREETYPE Degree;
} DIS_TRIPATCH_INFO, *LPTRIPATCH_INFO;

typedef struct DIS_CLIPSTATUS {
  UInt32 ClipUnion;
  UInt32 ClipIntersection;
} DIS_CLIPSTATUS, *LPCLIPSTATUS;

typedef void* DIS_HWND;

typedef struct DIS_DEVICE_CREATION_PARAMETERS {
  UInt32       AdapterOrdinal;
  DIS_DEVTYPE DeviceType;
  DIS_HWND       hFocusWindow;
  UInt32      BehaviorFlags;
} DIS_DEVICE_CREATION_PARAMETERS , *LPDEVICE_CREATION_PARAMETERS;

typedef struct DIS_VSHADERCAPS2_0 {
  UInt32 Caps;
  UInt32   DynamicFlowControlDepth;
  UInt32   NumTemps;
  UInt32   StaticFlowControlDepth;
} DIS_VSHADERCAPS2_0 , *LPVSHADERCAPS2_0;

typedef struct DIS_PSHADERCAPS2_0 {
  UInt32 Caps;
  UInt32   DynamicFlowControlDepth;
  UInt32   NumTemps;
  UInt32   StaticFlowControlDepth;
  UInt32   NumInstructionSlots;
} DIS_PSHADERCAPS2_0 , *LPPSHADERCAPS2_0;

typedef struct DIS_CAPS {
  DIS_DEVTYPE        DeviceType;
  UInt32              AdapterOrdinal;
  UInt32             Caps;
  UInt32             Caps2;
  UInt32             Caps3;
  UInt32             PresentationIntervals;
  UInt32             CursorCaps;
  UInt32             DevCaps;
  UInt32             PrimitiveMiscCaps;
  UInt32             RasterCaps;
  UInt32             ZCmpCaps;
  UInt32             SrcBlendCaps;
  UInt32             DestBlendCaps;
  UInt32             AlphaCmpCaps;
  UInt32             ShadeCaps;
  UInt32             TextureCaps;
  UInt32             TextureFilterCaps;
  UInt32             CubeTextureFilterCaps;
  UInt32             VolumeTextureFilterCaps;
  UInt32             TextureAddressCaps;
  UInt32             VolumeTextureAddressCaps;
  UInt32             LineCaps;
  UInt32             MaxTextureWidth;
  UInt32             MaxTextureHeight;
  UInt32             MaxVolumeExtent;
  UInt32             MaxTextureRepeat;
  UInt32             MaxTextureAspectRatio;
  UInt32             MaxAnisotropy;
  float             MaxVertexW;
  float             GuardBandLeft;
  float             GuardBandTop;
  float             GuardBandRight;
  float             GuardBandBottom;
  float             ExtentsAdjust;
  UInt32             StencilCaps;
  UInt32             FVFCaps;
  UInt32             TextureOpCaps;
  UInt32             MaxTextureBlendStages;
  UInt32             MaxSimultaneousTextures;
  UInt32             VertexProcessingCaps;
  UInt32             MaxActiveLights;
  UInt32             MaxUserClipPlanes;
  UInt32             MaxVertexBlendMatrices;
  UInt32             MaxVertexBlendMatrixIndex;
  float             MaxPointSize;
  UInt32             MaxPrimitiveCount;
  UInt32             MaxVertexIndex;
  UInt32             MaxStreams;
  UInt32             MaxStreamStride;
  UInt32             VertexShaderVersion;
  UInt32             MaxVertexShaderConst;
  UInt32             PixelShaderVersion;
  float             PixelShader1xMaxValue;
  UInt32             DevCaps2;
  UInt32              MasterAdapterOrdinal;
  UInt32              AdapterOrdinalInGroup;
  UInt32              NumberOfAdaptersInGroup;
  UInt32             DeclTypes;
  UInt32             NumSimultaneousRTs;
  UInt32             StretchRectFilterCaps;
  DIS_VSHADERCAPS2_0 VS20Caps;
  DIS_PSHADERCAPS2_0 PS20Caps;
  UInt32             VertexTextureFilterCaps;
  UInt32             MaxVShaderInstructionsExecuted;
  UInt32             MaxPShaderInstructionsExecuted;
  UInt32             MaxVertexShader30InstructionSlots;
  UInt32             MaxPixelShader30InstructionSlots;
  UInt32             Reserved2;
  UInt32             Reserved3;
} DIS_CAPS, *LPCAPS;


typedef struct DIS_DISPLAYMODE {
  UInt32      Width;
  UInt32      Height;
  UInt32      RefreshRate;
  DIS_FORMAT Format;
} DIS_DISPLAYMODE, *LPDISPLAYMODE;

typedef struct DIS_GAMMARAMP {
  UInt16 red[256];
  UInt16 green[256];
  UInt16 blue[256];
} DIS_GAMMARAMP, *LPGAMMARAMP;

typedef struct DIS_COLORVALUE {
  float r;
  float g;
  float b;
  float a;
} DIS_COLORVALUE;

typedef struct DIS_VECTOR
{
	float x;
	float y;
	float z;
} DIS_VECTOR;

typedef struct DIS_MATRIX {
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        };
        float m[4][4];
    };
} DIS_MATRIX;

typedef struct DIS_LIGHT {
  DIS_LIGHTTYPE  Type;
  DIS_COLORVALUE Diffuse;
  DIS_COLORVALUE Specular;
  DIS_COLORVALUE Ambient;
  DIS_VECTOR     Position;
  DIS_VECTOR     Direction;
  float         Range;
  float         Falloff;
  float         Attenuation0;
  float         Attenuation1;
  float         Attenuation2;
  float         Theta;
  float         Phi;
} DIS_LIGHT , *LPLIGHT;

typedef struct DIS_MATERIAL {
  DIS_COLORVALUE Diffuse;
  DIS_COLORVALUE Ambient;
  DIS_COLORVALUE Specular;
  DIS_COLORVALUE Emissive;
  float         Power;
} DIS_MATERIAL, *LPMATERIAL;

typedef struct DIS_PALETTEENTRY {
  Byte peRed;
  Byte peGreen;
  Byte peBlue;
  Byte peFlags;
} DIS_PALETTEENTRY, *LPPALETTEENTRY_DIS;


typedef struct DIS_RASTER_STATUS {
  bool InVBlank;
  UInt32 ScanLine;
} DIS_RASTER_STATUS , *LPRASTER_STATUS;


typedef struct DIS_VIEWPORT {
  UInt32 X;
  UInt32 Y;
  UInt32 Width;
  UInt32 Height;
  float MinZ;
  float MaxZ;
} DIS_VIEWPORT, *LPVIEWPORT;

typedef struct DIS_RGNDATAHEADER {
  UInt32 dwSize;
  UInt32 iType;
  UInt32 nCount;
  UInt32 nRgnSize;
  DIS_Rect  rcBound;
} DIS_RGNDATAHEADER , *PDIS_RGNDATAHEADER;

typedef struct DIS_RGNDATA {
  DIS_RGNDATAHEADER rdh;
  char          Buffer[1];
} DIS_RGNDATA , *PDIS_RGNDATA;


typedef struct DIS_PRESENT_PARAMETERS {
  UInt32                BackBufferWidth;
  UInt32                BackBufferHeight;
  DIS_FORMAT           BackBufferFormat;
  UInt32                BackBufferCount;
  DIS_MULTISAMPLE_TYPE MultiSampleType;
  UInt32               MultiSampleQuality;
  DIS_SWAPEFFECT       SwapEffect;
  DIS_HWND                hDeviceWindow;
  bool                Windowed;
  bool                EnableAutoDepthStencil;
  DIS_FORMAT           AutoDepthStencilFormat;
  UInt32               Flags;
  UInt32                FullScreen_RefreshRateInHz;
  UInt32                PresentationInterval;
} DIS_PRESENT_PARAMETERS , *LPPRESENT_PARAMETERS;

typedef struct DIS_POINT
{
	float X;
	float Y;
}DIS_POINT, *LPDIS_POINT;


typedef int DISFONT;
typedef DISFONT* LPFONT;



#include "DIS_Surface.h"

#ifdef DIS_INLINE_BUILD
#define DIS_INLINE inline 
#else
#define DIS_INLINE
#endif



typedef void* DIS_HANDLE;


#define DIS_TSS_TCI_PASSTHRU	0x00000000L	//Use the specified texture coordinates contained within the vertex format. This value resolves to zero.
#define DIS_TSS_TCI_CAMERASPACENORMAL	0x00010000L	//Use the vertex normal, transformed to camera space, as the input texture coordinates for this stage's texture transformation.
#define DIS_TSS_TCI_CAMERASPACEPOSITION	0x00020000L	//Use the vertex position, transformed to camera space, as the input texture coordinates for this stage's texture transformation.
#define DIS_TSS_TCI_CAMERASPACEREFLECTIONVECTOR	0x00030000L	//Use the reflection vector, transformed to camera space, as the input texture coordinate for this stage's texture transformation. The reflection vector is computed from the input vertex position and normal vector.
#define DIS_TSS_TCI_SPHEREMAP	0x00040000L	//Use the specified texture coordinates for sphere mapping.


enum DIS_USAGE
{
DIS_USAGE_NONE = 0,
DIS_USAGE_AUTOGENMIPMAP = 1,//The resource will automatically generate mipmaps. See Automatic Generation of Mipmaps (Direct3D 9). Automatic generation of mipmaps is not supported for volume textures and depth stencil surfaces/textures. This usage is not valid for a resource in system memory (DIS_POOL_SYSTEMMEM).
DIS_USAGE_DEPTHSTENCIL = 2, //The resource will be a depth stencil buffer. DIS_USAGE_DEPTHSTENCIL can only be used with DIS_POOL_DEFAULT.
DIS_USAGE_DMAP = 4,		//The resource will be a displacement map.
DIS_USAGE_DONOTCLIP =8,//Set to indicate that the vertex buffer content will never require clipping. When rendering with buffers that have this flag set, the DIS_RS_CLIPPING render state must be set to false.
DIS_USAGE_DYNAMIC = 16, //Set to indicate that the vertex buffer requires dynamic memory use. This is useful for drivers because it enables them to decide where to place the buffer. In general, static vertex buffers are placed in video memory and dynamic vertex buffers are placed in AGP memory. Note that there is no separate static use. If you do not specify DIS_USAGE_DYNAMIC, the vertex buffer is made static. DIS_USAGE_DYNAMIC is strictly enforced through the DIS_LOCK_DISCARD and DIS_LOCK_NOOVERWRITE locking flags. As a result, DIS_LOCK_DISCARD and DIS_LOCK_NOOVERWRITE are valid only on vertex buffers created with DIS_USAGE_DYNAMIC. They are not valid flags on static vertex buffers. For more information, see Managing Resources (Direct3D 9).
//For more information about using dynamic vertex buffers, see Performance Optimizations (Direct3D 9).
//DIS_USAGE_DYNAMIC and DIS_POOL_MANAGED are incompatible and should not be used together. See DIS_POOL.
//Textures can specify DIS_USAGE_DYNAMIC. However, managed textures cannot use DIS_USAGE_DYNAMIC. For more information about dynamic textures, see Using Dynamic Textures.
DIS_USAGE_NONSECURE = 32,
//Allow a shared surface created by a secure application to be opened by a non-secure application that has the shared handle.
//Differences between Direct3D 9 and Direct3D 9Ex:  This flag is available in Direct3D 9Ex only.
DIS_USAGE_NPATCHES =64,//Set to indicate that the vertex buffer is to be used for drawing N-patches.
DIS_USAGE_POINTS =128, //Set to indicate that the vertex or index buffer will be used for drawing point sprites. The buffer will be loaded in system memory if software vertex processing is needed to emulate point sprites.
DIS_USAGE_RENDERTARGET =256,//The resource will be a render target. DIS_USAGE_RENDERTARGET can only be used with DIS_POOL_DEFAULT.
DIS_USAGE_RTPATCHES = 512, //Set to indicate that the vertex buffer is to be used for drawing high-order primitives.
DIS_USAGE_SOFTWAREPROCESSING = 1024, //If this flag is used, vertex processing is done in software. If this flag is not used, vertex processing is done in hardware.
//The DIS_USAGE_SOFTWAREPROCESSING flag can be set when mixed-mode or software vertex processing (DIS_CREATE_MIXED_VERTEXPROCESSING / DIS_CREATE_SOFTWARE_VERTEXPROCESSING) is enabled for that device. DIS_USAGE_SOFTWAREPROCESSING must be set for buffers to be used with software vertex processing in mixed mode, but it should not be set for the best possible performance when using hardware index processing in mixed mode (DIS_CREATE_HARDWARE_VERTEXPROCESSING). However, setting DIS_USAGE_SOFTWAREPROCESSING is the only option when a single buffer is used with both hardware and software vertex processing. DIS_USAGE_SOFTWAREPROCESSING is allowed for mixed and software devices.
//DIS_USAGE_SOFTWAREPROCESSING is used with CheckDeviceFormat to find out if a particular texture format can be used as a vertex texture during software vertex processing. If it can, the texture must be created in DIS_POOL_SCRATCH.
DIS_USAGE_TEXTAPI = 2048, //This usage flag must be specified for vertex buffers and source surfaces, used in calls to ComposeRects. T extures created with this usage flag cannot be used for texture filtering. Vertex buffers, created with this usage flag, cannot be used as input stream sources.
//Differences between Direct3D 9 and Direct3D 9Ex:  This flag is available in Direct3D 9Ex only.
DIS_USAGE_WRITEONLY =4096,//Informs the system that the application writes only to the vertex buffer. Using this flag enables the driver to choose the best memory location for efficient write operations and rendering. Attempts to read from a vertex buffer that is created with this capability will fail. Buffers created with DIS_POOL_DEFAULT that do not specify DIS_USAGE_WRITEONLY may suffer a severe performance penalty. DIS_USAGE_WRITEONLY only affects the performance of DIS_POOL_DEFAULT buffers.
DIS_USAGE_RESTRICTED_CONTENT =8192,//Setting this flag indicates that the resource might contain protected content.
//Differences between Direct3D 9 and Direct3D 9Ex:  This flag is available in Direct3D 9Ex only.
DIS_USAGE_RESTRICT_SHARED_RESOURCE =16384, //Setting this flag indicates that access to the shared resource should be restricted.
//Differences between Direct3D 9 and Direct3D 9Ex:  This flag is available in Direct3D 9Ex only.
DIS_USAGE_RESTRICT_SHARED_RESOURCE_DRIVER=32768,
};


//-------------------------------------------------------------------

// Flexible vertex format bits
//
#define DIS_FVF_RESERVED0        0x001
#define DIS_FVF_POSITION_MASK    0x400E
#define DIS_FVF_XYZ              0x002
#define DIS_FVF_XYZRHW           0x004
#define DIS_FVF_XYZB1            0x006
#define DIS_FVF_XYZB2            0x008
#define DIS_FVF_XYZB3            0x00a
#define DIS_FVF_XYZB4            0x00c
#define DIS_FVF_XYZB5            0x00e
#define DIS_FVF_XYZW             0x4002

#define DIS_FVF_NORMAL           0x010
#define DIS_FVF_PSIZE            0x020
#define DIS_FVF_DIFFUSE          0x040
#define DIS_FVF_SPECULAR         0x080

#define DIS_FVF_TEXCOUNT_MASK    0xf00
#define DIS_FVF_TEXCOUNT_SHIFT   8
#define DIS_FVF_TEX0             0x000
#define DIS_FVF_TEX1             0x100
#define DIS_FVF_TEX2             0x200
#define DIS_FVF_TEX3             0x300
#define DIS_FVF_TEX4             0x400
#define DIS_FVF_TEX5             0x500
#define DIS_FVF_TEX6             0x600
#define DIS_FVF_TEX7             0x700
#define DIS_FVF_TEX8             0x800

#define DIS_FVF_LASTBETA_UBYTE4   0x1000
#define DIS_FVF_LASTBETA_D3DCOLOR 0x8000

#define DIS_FVF_RESERVED2         0x6000  // 2 reserved bits

#define DIS_FVF_TEXCOORDSIZEN(CoordIndex) 
#define DIS_FVF_TEXCOORDSIZE1(CoordIndex) (DIS_FVF_TEXTUREFORMAT1 << (CoordIndex*2 + 16)) 
#define DIS_FVF_TEXCOORDSIZE2(CoordIndex) (DIS_FVF_TEXTUREFORMAT2) 
#define DIS_FVF_TEXCOORDSIZE3(CoordIndex) (DIS_FVF_TEXTUREFORMAT3 << (CoordIndex*2 + 16)) 
#define DIS_FVF_TEXCOORDSIZE4(CoordIndex) (DIS_FVF_TEXTUREFORMAT4 << (CoordIndex*2 + 16))

#endif