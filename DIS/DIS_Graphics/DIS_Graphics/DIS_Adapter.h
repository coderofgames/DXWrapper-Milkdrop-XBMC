/*

This file is unused, so for now it will be the TODO list

1) D3D_Interface.cpp, the create texture call still has
   the default usage flag as D3DUSAGE_DYNAMIC
 
2) Add more formats to the texture load + tidy up the code a bit
	- 2 passes, error checking, then code beautification

3) Find a way to load the D3D texture straight from FreeImage without
   allowing the two libraries to collide, so some kind of object to pass betweem
   them

4) D3D_Interface.cpp 
   All the *Get* routines that take an object pointer to be assigned with the
   currently used object need to be fixed, there are notes "GET FROM RESOURCE MANAGER"

5) Effects - add a wrapper, try to unify with CG or GLSL eventually

6) Animation - the DX9 wrappers for animation, perhaps can be wrapped up into 
			   an animated skinned Mesh object

7) Load other types of Texture 
	a) DDS 2D textures
	b) Volumes (or DDS)
	c) Cubemaps

8) Vertex Buffer and Index Buffer formats
   a) Lock the vertex buffer
   b) Lock the index buffer

9) All the OpenGL needs to be done

10) FVF flags need to be added

11) DECL's need to be done

12) Effect->GetTexture is not implemented for d3d9

13)

*/