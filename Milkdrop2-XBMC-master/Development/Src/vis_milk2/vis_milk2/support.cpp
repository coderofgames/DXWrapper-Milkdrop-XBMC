/*
  LICENSE
  -------
Copyright 2005-2013 Nullsoft, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer. 

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution. 

  * Neither the name of Nullsoft nor the names of its contributors may be used to 
    endorse or promote products derived from this software without specific prior written permission. 
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "support.h"
#include "utility.h"
//#include "../Winamp/wa_ipc.h"

bool g_bDebugOutput = false;
bool g_bDumpFileCleared = false;

//---------------------------------------------------
void PrepareFor3DDrawing(
        LPDEVICE pDevice, 
        int viewport_width,
        int viewport_height,
        float fov_in_degrees, 
        float near_clip,
        float far_clip,
        DISX_VECTOR3* pvEye,
		DISX_VECTOR3* pvLookat,
		DISX_VECTOR3* pvUp
    )
{
    // This function sets up DirectX up for 3D rendering.
    // Only call it once per frame, as it is VERY slow.
    // INPUTS:
    //    pDevice           a pointer to the D3D device
    //    viewport_width    the width of the client area of the window
    //    viewport_height   the height of the client area of the window
    //    fov_in_degrees    the field of view, in degrees
    //    near_clip         the distance to the near clip plane; should be > 0!
    //    far_clip          the distance to the far clip plane
    //    eye               the eyepoint coordinates, in world space
    //    lookat            the point toward which the eye is looking, in world space
    //    up                a vector indicating which dir. is up; usually <0,1,0>
    //
    // What this function does NOT do:
    //    1. set the current texture (SetTexture)
    //    2. set up the texture stages for texturing (SetTextureStageState)
    //    3. set the current vertex format (SetVertexShader)
    //    4. set up the world matrix (SetTransform(D3DTS_WORLD, &my_world_matrix))

    
    // set up render state to some nice defaults:
    {
        // some defaults
        pDevice->SetRenderState( DISRS_ZENABLE, TRUE );
        pDevice->SetRenderState( DISRS_ZWRITEENABLE, TRUE );
        pDevice->SetRenderState( DISRS_ZFUNC,     DIS_CMP_LESSEQUAL );
        pDevice->SetRenderState( DISRS_CULLMODE, DIS_CULL_NONE );
        pDevice->SetRenderState( DISRS_CLIPPING, TRUE );
        pDevice->SetRenderState( DISRS_LIGHTING, FALSE );
        pDevice->SetRenderState( DISRS_COLORVERTEX, TRUE );
        pDevice->SetRenderState( DISRS_SHADEMODE, DIS_SHADE_GOURAUD );
        pDevice->SetRenderState( DISRS_FILLMODE,  DIS_FILL_SOLID );
        pDevice->SetRenderState( DISRS_ALPHABLENDENABLE, FALSE );

        // turn fog off
        pDevice->SetRenderState( DISRS_FOGENABLE, FALSE );
        pDevice->SetRenderState( DISRS_RANGEFOGENABLE, FALSE );
    
        // turn on high-quality bilinear interpolations
        pDevice->SetSamplerState(0, DIS_SAMP_MAGFILTER, DIS_TEXF_LINEAR); 
		pDevice->SetSamplerState(1, DIS_SAMP_MAGFILTER, DIS_TEXF_LINEAR);
		pDevice->SetSamplerState(0, DIS_SAMP_MINFILTER, DIS_TEXF_LINEAR);
		pDevice->SetSamplerState(1, DIS_SAMP_MINFILTER, DIS_TEXF_LINEAR);
		pDevice->SetSamplerState(0, DIS_SAMP_MIPFILTER, DIS_TEXF_LINEAR);
		pDevice->SetSamplerState(1, DIS_SAMP_MIPFILTER, DIS_TEXF_LINEAR);
    }    

    // set up view & projection matrices (but not the world matrix!)
    {
        // if the window is not square, instead of distorting the scene,
        // clip it so that the longer dimension of the window has the
        // regular FOV, and the shorter dimension has a reduced FOV.
        float fov_x = fov_in_degrees * 3.1415927f/180.0f;
        float fov_y = fov_in_degrees * 3.1415927f/180.0f;
        float aspect = (float)viewport_height / (float)viewport_width;
        if (aspect < 1)
            fov_y *= aspect;
        else
            fov_x /= aspect;
        
        if (near_clip < 0.1f)
            near_clip = 0.1f;
        if (far_clip < near_clip + 1.0f)
            far_clip = near_clip + 1.0f;

        DISX_MATRIX proj;
        MakeProjectionMatrix(&proj, near_clip, far_clip, fov_x, fov_y);
        pDevice->SetTransform(DIS_TS_PROJECTION, &proj);
        
		DISX_MATRIX view;
        DISX_MatrixLookAtLH(&view, pvEye, pvLookat, pvUp);
        pDevice->SetTransform(DIS_TS_VIEW, &view);

        // Optimization note: "You can minimize the number of required calculations 
        // by concatenating your world and view matrices into a world-view matrix 
        // that you set as the world matrix, and then setting the view matrix 
        // to the identity."
        //D3DXMatrixMultiply(&world, &world, &view);                
        //D3DXMatrixIdentity(&view);
    }
}

void PrepareFor2DDrawing(LPDEVICE pDevice)
{
    // New 2D drawing area will have x,y coords in the range <-1,-1> .. <1,1>
    //         +--------+ Y=-1
    //         |        |
    //         | screen |             Z=0: front of scene
    //         |        |             Z=1: back of scene
    //         +--------+ Y=1
    //       X=-1      X=1
    // NOTE: After calling this, be sure to then call (at least):
    //  1. SetVertexShader()
    //  2. SetTexture(), if you need it
    // before rendering primitives!
    // Also, be sure your sprites have a z coordinate of 0.
    pDevice->SetRenderState( DISRS_ZENABLE, TRUE );
    pDevice->SetRenderState( DISRS_ZWRITEENABLE, TRUE );
    pDevice->SetRenderState( DISRS_ZFUNC,     D3DCMP_LESSEQUAL );
    pDevice->SetRenderState( DISRS_SHADEMODE, D3DSHADE_FLAT );
    pDevice->SetRenderState( DISRS_FILLMODE,  D3DFILL_SOLID );
    pDevice->SetRenderState( DISRS_FOGENABLE, FALSE );
    pDevice->SetRenderState( DISRS_CULLMODE, D3DCULL_NONE );
    pDevice->SetRenderState( DISRS_CLIPPING, TRUE ); 
    pDevice->SetRenderState( DISRS_LIGHTING, FALSE );
    pDevice->SetRenderState( DISRS_ALPHABLENDENABLE, FALSE );
    pDevice->SetRenderState( DISRS_LOCALVIEWER, FALSE );
    
    pDevice->SetTexture(0, NULL);
    pDevice->SetTexture(1, NULL);
    pDevice->SetSamplerState(0, DIS_SAMP_MAGFILTER, D3DTEXF_POINT);//D3DTEXF_LINEAR);
    pDevice->SetSamplerState(1, DIS_SAMP_MAGFILTER, D3DTEXF_POINT);//D3DTEXF_LINEAR);
    pDevice->SetTextureStageState(0, DIS_TSS_TEXTURETRANSFORMFLAGS, DIS_TTFF_DISABLE);
    pDevice->SetTextureStageState(1, DIS_TSS_TEXTURETRANSFORMFLAGS, DIS_TTFF_DISABLE);    
    pDevice->SetTextureStageState(0, DIS_TSS_COLOROP, DIS_TOP_MODULATE );
    pDevice->SetTextureStageState(0, DIS_TSS_COLORARG1, DIS_TA_TEXTURE );
    pDevice->SetTextureStageState(0, DIS_TSS_COLORARG2, DIS_TA_CURRENT );
    pDevice->SetTextureStageState(1, DIS_TSS_COLOROP, DIS_TOP_DISABLE );

    pDevice->SetTextureStageState(0, DIS_TSS_ALPHAOP, DIS_TOP_SELECTARG1 );
    pDevice->SetTextureStageState(0, DIS_TSS_ALPHAARG1, DIS_TA_DIFFUSE );
    pDevice->SetTextureStageState(1, DIS_TSS_ALPHAOP, DIS_TOP_DISABLE );

    pDevice->SetRenderState( DISRS_ALPHABLENDENABLE, FALSE );
    
    // set up for 2D drawing:
    {
        DISX_MATRIX Ortho2D;    
        DISX_MATRIX Identity;
        
        DISX_MatrixOrthoLH(&Ortho2D, 2.0f, -2.0f, 0.f, 1.0f);
		//DISX_MatrixPerspectiveLH(&Ortho2D, 1280.0f, 1024.0f, 0.1f, 100.0f);
        DISX_MatrixIdentity(&Identity);

        pDevice->SetTransform(DIS_TS_PROJECTION, &Ortho2D);
        pDevice->SetTransform(DIS_TS_WORLD, &Identity);
        pDevice->SetTransform(DIS_TS_VIEW, &Identity);
    }
}

//---------------------------------------------------

void MakeWorldMatrix( D3DXMATRIX* pOut, 
                      float xpos, float ypos, float zpos, 
                      float sx,   float sy,   float sz, 
                      float pitch, float yaw, float roll)
{
    /*
     * The m_xPos, m_yPos, m_zPos variables contain the model's
     * location in world coordinates.
     * The m_fPitch, m_fYaw, and m_fRoll variables are floats that 
     * contain the model's orientation in terms of pitch, yaw, and roll
     * angles, in radians.
     */

    D3DXMATRIX MatTemp;
    D3DXMatrixIdentity(pOut);

    // 1. first, rotation
    if (pitch || yaw || roll) 
    {
        D3DXMATRIX MatRot;
        D3DXMatrixIdentity(&MatRot);

        D3DXMatrixRotationX(&MatTemp, pitch);         // Pitch
        D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
        D3DXMatrixRotationY(&MatTemp, yaw);           // Yaw
        D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
        D3DXMatrixRotationZ(&MatTemp, roll);          // Roll
        D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
 
        D3DXMatrixMultiply(pOut, pOut, &MatRot);
    }

    // 2. then, scaling
    D3DXMatrixScaling(&MatTemp, sx, sy, sz);
    D3DXMatrixMultiply(pOut, pOut, &MatTemp);

    // 3. last, translation to final world pos.
    D3DXMatrixTranslation(&MatTemp, xpos, ypos, zpos);
    D3DXMatrixMultiply(pOut, pOut, &MatTemp);
}

void MakeProjectionMatrix( DISX_MATRIX* pOut,
                           const float near_plane, // Distance to near clipping plane
                           const float far_plane,  // Distance to far clipping plane
                           const float fov_horiz,  // Horizontal field of view angle, in radians
                           const float fov_vert)   // Vertical field of view angle, in radians
{
    float w = (float)1/tanf(fov_horiz*0.5f);  // 1/tan(x) == cot(x)
    float h = (float)1/tanf(fov_vert*0.5f);   // 1/tan(x) == cot(x)
    float Q = far_plane/(far_plane - near_plane);
 
	ZeroMemory(pOut, sizeof(DISX_MATRIX));
    pOut->_11 = w;
    pOut->_22 = h;
    pOut->_33 = Q;
    pOut->_43 = -Q*near_plane;
    pOut->_34 = 1;
}

int GetDX9TexFormatBitsPerPixel(DIS_FORMAT fmt)
{
    switch(fmt)
    {
    case DIS_FMT_DXT1:   // 64 bits for each 4x4 pixels = 4 bits per pixel.  No Alpha channel.
      return 4; // bytes per pixel
  
    case DIS_FMT_DXT2:   // 128 bits for each 4x4 pixels = 8 bits per pixel.  RGB+A.
    case DIS_FMT_DXT3:   // 128 bits for each 4x4 pixels = 8 bits per pixel.  RGB+A.
    case DIS_FMT_DXT4:   // 128 bits for each 4x4 pixels = 8 bits per pixel.  RGB+A.
    case DIS_FMT_DXT5:   // 128 bits for each 4x4 pixels = 8 bits per pixel.  RGB+A.
    case DIS_FMT_R3G3B2: // 8-bit RGB texture format using 3 bits for red, 3 bits for green, and 2 bits for blue. 
    case DIS_FMT_A8:   // 8-bit alpha only. 
    case DIS_FMT_A8P8: // 8-bit color indexed with 8 bits of alpha. 
    case DIS_FMT_P8:   // 8-bit color indexed. 
    case DIS_FMT_L8:   // 8-bit luminance only. 
    case DIS_FMT_A4L4: // 8-bit using 4 bits each for alpha and luminance. 
      return 8;

    case DIS_FMT_R5G6B5:   // 16-bit RGB pixel format with 5 bits for red, 6 bits for green, and 5 bits for blue. 
	case DIS_FMT_X1R5G5B5: // 16-bit pixel format where 5 bits are reserved for each color. 
	case DIS_FMT_A1R5G5B5: // 16-bit pixel format where 5 bits are reserved for each color and 1 bit is reserved for alpha. 
    case DIS_FMT_A4R4G4B4: // 16-bit ARGB pixel format with 4 bits for each channel. 
    case DIS_FMT_R16F:
    case DIS_FMT_A8R3G3B2: // 16-bit ARGB texture format using 8 bits for alpha, 3 bits each for red and green, and 2 bits for blue. 
    case DIS_FMT_X4R4G4B4: // 16-bit RGB pixel format using 4 bits for each color. 
    case DIS_FMT_L16:      // 16-bit luminance only. 
    case DIS_FMT_A8L8:     // 16-bit using 8 bits each for alpha and luminance. 
    case DIS_FMT_CxV8U8:
    case DIS_FMT_V8U8:
    case DIS_FMT_L6V5U5:
      return 16;

    case DIS_FMT_G16R16F: 
    case DIS_FMT_R32F:          // 32-bit float format using 32 bits for the red channel. 
    case DIS_FMT_A8R8G8B8:      // 32-bit ARGB pixel format with alpha, using 8 bits per channel. 
    case DIS_FMT_X8R8G8B8:      // 32-bit RGB pixel format, where 8 bits are reserved for each color. 
    case DIS_FMT_A8B8G8R8:      // 32-bit ARGB pixel format with alpha, using 8 bits per channel. 
    case DIS_FMT_X8B8G8R8:      // 32-bit RGB pixel format, where 8 bits are reserved for each color. 
    case DIS_FMT_G16R16:        // 32-bit pixel format using 16 bits each for green and red. 
    case DIS_FMT_A2R10G10B10:   // 32-bit pixel format using 10 bits each for red, green, and blue, and 2 bits for alpha. 
    case DIS_FMT_A2B10G10R10:   // 32-bit pixel format using 10 bits for each color and 2 bits for alpha. 
    case DIS_FMT_R8G8B8:        // 24-bit RGB pixel format with 8 bits per channel. 
    case DIS_FMT_X8L8V8U8:
    case DIS_FMT_Q8W8V8U8:
    case DIS_FMT_V16U16:
      return 32;
  
    case DIS_FMT_A16B16G16R16F: 
    case DIS_FMT_A16B16G16R16:  // 64-bit pixel format using 16 bits for each component. 
    case DIS_FMT_G32R32F:       // 64-bit float format using 32 bits for the red channel and 32 bits for the green channel. 
      return 64;

    case DIS_FMT_A32B32G32R32F: 
      return 128;
    }
    
    return 32;
}