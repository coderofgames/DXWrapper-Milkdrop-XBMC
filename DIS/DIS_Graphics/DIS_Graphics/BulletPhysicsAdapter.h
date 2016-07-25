

#ifndef BULLET_PHYSICS_ADAPTER_H
#define BULLET_PHYSICS_ADAPTER_H

#include "3DMath.h"
#include "Geometry.h"

class DISX_MATRIX;

void BUL_CreateWorld();
void BUL_CreateDynamicObject();



void BUL_Tick(float inc, int maxSteps);
void BUL_UpdateCamera(Mat44* matCam);
void BUL_UpdateCamera(DISX_MATRIX* matCam);
void BUL_TickCharacter(float dt);

void BUL_RotateCameraLeft(bool flag);
void BUL_RotateCameraRight(bool flag);
void BUL_MoveCharacterForwards(bool flag);
void BUL_MoveCharacterBackwards(bool flag);
void BUL_MakeCharacterJump(bool flag);

int BUL_GetNumObjects();
void BUL_StartLoop();
void BUL_GetCurrentObjectMatrix(Mat44* mat);
void BUL_GetCurrentObjectMatrix(DISX_MATRIX* mat);
void BUL_Increment();
void BUL_EndLoop();

void BUL_Shutdown();

void BUL_CreateTriMesh(D3DXVECTOR3 *verts, int totalVerts, Triangle *triangles, int totalTriangles );

#endif