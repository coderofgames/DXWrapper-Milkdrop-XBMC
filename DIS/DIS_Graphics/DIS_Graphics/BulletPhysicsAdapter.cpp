#include "BulletPhysicsAdapter.h"
#include <btBulletDynamicsCommon.h>
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

#include "DynamicCharacterController.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"

#include "DIS_Math.h"
btDiscreteDynamicsWorld* dynamicsWorld;
btCollisionShape* groundShape;
btCollisionShape* colShape;

btCollisionShape* bigKinematicBox;
btDefaultMotionState* myMotionStateBigBox;
btRigidBody* bodyBox;

btPairCachingGhostObject *m_ghostObject;

	btVector3*gVertices;
	int * gIndices;
	btTriangleIndexVertexArray* m_indexVertexArrays;


#ifdef DYNAMICS_CHARACTER
DynamicCharacterController *m_character;
#else
btKinematicCharacterController *m_character;
#endif

	float		m_cameraHeight=4.f;

	float	m_minCameraDistance=3.f;
	float	m_maxCameraDistance=10.f;


bool bulletLoop = false;
int bulletLoopCount = 0;

btVector3 m_cameraUp(0,1,0);


static int gForward = 0;
static int gBackward = 0;
static int gLeft = 0;
static int gRight = 0;
static int gJump = 0;

btDefaultCollisionConfiguration* collisionConfiguration;
btCollisionDispatcher* dispatcher ;
btAxisSweep3* sweepBP ;
btSequentialImpulseConstraintSolver* solver;
btAlignedObjectArray<btCollisionShape*> collisionShapes;



void BUL_CreateWorld()
{

int i;

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache ;//= new btDbvtBroadphase();
	sweepBP = new btAxisSweep3(worldMin,worldMax);
	overlappingPairCache = sweepBP;

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
	dynamicsWorld->setGravity(btVector3(0,-10,0));

	///create a few basic rigid bodies
	groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));
	
	
	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	

	collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-56,0));

	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}


	{
		//create a dynamic rigidbody
		
		colShape = new btBoxShape(btVector3(1,1,1));
		
		//btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(0.001f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);

			startTransform.setOrigin(btVector3(2,10,0));
			startTransform.setRotation(btQuaternion(45,23,40));
			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);

			dynamicsWorld->addRigidBody(body);
	}

	{
		//create a dynamic rigidbody
		
		bigKinematicBox = new btBoxShape(btVector3(1,1,1));
		bigKinematicBox->setLocalScaling(btVector3(10,10,10));
		//btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(bigKinematicBox);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(6.0f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			bigKinematicBox->calculateLocalInertia(mass,localInertia);

			startTransform.setOrigin(btVector3(25,40,0));
			startTransform.setRotation(btQuaternion(0,0,0));
			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			myMotionStateBigBox = new btDefaultMotionState(startTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionStateBigBox,bigKinematicBox,localInertia);
			bodyBox = new btRigidBody(rbInfo);
						
			bodyBox->setCollisionFlags( bodyBox->getCollisionFlags() & ~(btCollisionObject::CF_KINEMATIC_OBJECT));
			bodyBox->activate(true); // or try… body->forceActivationState(ACTIVE_FLAG)
			bodyBox->setActivationState(DISABLE_DEACTIVATION);
			dynamicsWorld->addRigidBody(bodyBox);
	}


	btTransform startTransform;
	startTransform.setIdentity ();
	startTransform.setOrigin (btVector3(0.0, 7.0, -25.0));
	//startTransform.setOrigin (btVector3(10.210098,-1.6433364,16.453260));

	
	m_ghostObject = new btPairCachingGhostObject();
	m_ghostObject->setWorldTransform(startTransform);
	sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	btScalar characterHeight=0.75;
	btScalar characterWidth =0.75;
	btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
	m_ghostObject->setCollisionShape (capsule);
	m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

	btScalar stepHeight = btScalar(0.35);
	m_character = new btKinematicCharacterController (m_ghostObject,capsule,stepHeight);
	

	//m_character = new DynamicCharacterController();
		
	///only collide with static for now (no interaction with dynamic objects)
	dynamicsWorld->addCollisionObject(m_ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

	dynamicsWorld->addAction(m_character);

	m_character->setJumpSpeed(20.0);
}

void BUL_CreateDynamicObject()
{
}

void SlerpVecsHelper( btVector3 *outPut, btVector3 *p0, btVector3 *p1, float t )
{
	//Slerp(p0, p1:t) = sin[ (1-t) angle] * p0 / (sin[ angle ]) + sin[ t* angle ] * p1/ (sin[angle]);
	btVector3 P0 = *p0;//.normalize();
	P0 = P0.normalize();
	btVector3 P1 = *p1;
	P1 = P1.normalize();

	float dotProd = P0.dot(P1);
	float angle = acos(dotProd);

	float sinAngle = sin(angle);
	t *= angle / 100;

	outPut->setX( sinf( (1-t) * angle ) * P0.x() / sinAngle + sinf( t* angle ) * P1.x()/ sinAngle);
	outPut->setY( sinf( (1-t) * angle ) * P0.y() / sinAngle + sinf( t* angle ) * P1.y()/ sinAngle);
	outPut->setZ( sinf( (1-t) * angle ) * P0.z() / sinAngle + sinf( t* angle ) * P1.z()/ sinAngle);
}

void BUL_UpdateCamera(DISX_MATRIX* matCam)
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity()
	static btVector3 m_cameraOldPosition;
	static bool first_time = true;


	btTransform characterWorldTrans;

	//look at the vehicle
	characterWorldTrans = m_ghostObject->getWorldTransform();
	btVector3 up = characterWorldTrans.getBasis()[1];
	btVector3 backward = -characterWorldTrans.getBasis()[2];
	up.normalize ();
	backward.normalize ();

	if( first_time )
	{
		m_cameraOldPosition + up * 1.3 + backward * 12.0;
		first_time = false;
	}

	btVector3 m_cameraTargetPosition = characterWorldTrans.getOrigin();
	btVector3 m_cameraPosition = m_cameraTargetPosition + up * 1.3 + backward * 12.0;
	//SlerpVecsHelper( &m_cameraPosition, &m_cameraOldPosition, &m_cameraPosition, 0.1);
	m_cameraOldPosition = m_cameraPosition;

	//use the convex sweep test to find a safe position for the camera (not blocked by static geometry)
	btSphereShape cameraSphere(0.2f);
	btTransform cameraFrom,cameraTo;
	cameraFrom.setIdentity();
	cameraFrom.setOrigin(characterWorldTrans.getOrigin());
	cameraTo.setIdentity();
	cameraTo.setOrigin(m_cameraPosition);
	
	btCollisionWorld::ClosestConvexResultCallback cb( characterWorldTrans.getOrigin(), cameraTo.getOrigin() );
	cb.m_collisionFilterMask = btBroadphaseProxy::StaticFilter;
		
	dynamicsWorld->convexSweepTest(&cameraSphere,cameraFrom,cameraTo,cb);
	if (cb.hasHit())
	{

		btScalar minFraction  = cb.m_closestHitFraction;//btMax(btScalar(0.3),cb.m_closestHitFraction);
		m_cameraPosition.setInterpolate3(cameraFrom.getOrigin(),cameraTo.getOrigin(),minFraction);
	}


	DISX_VECTOR3 vpos = DISX_VECTOR3(m_cameraPosition[0],m_cameraPosition[1],m_cameraPosition[2]);
	DISX_VECTOR3 vup = DISX_VECTOR3(m_cameraUp.getX(),m_cameraUp.getY(),m_cameraUp.getZ());
	DISX_VECTOR3 vat = DISX_VECTOR3(m_cameraTargetPosition[0],m_cameraTargetPosition[1], m_cameraTargetPosition[2]) ;
	/*
			m_vEye =	Vec3(finalTransformationMatrix._41,finalTransformationMatrix._42,finalTransformationMatrix._43);
		m_vLook =	Vec3(finalTransformationMatrix._31,finalTransformationMatrix._32,finalTransformationMatrix._33);
		m_vUp =		Vec3(finalTransformationMatrix._21,finalTransformationMatrix._22,finalTransformationMatrix._23);
		m_vRight =	Vec3(finalTransformationMatrix._11,finalTransformationMatrix._12,finalTransformationMatrix._13);
	*/

	DISX_VECTOR3 lookdir = vat-vpos;
	DISX_Vec3Normalize(&lookdir, &lookdir);
	
	//Vec3 right = vup.Cross(lookdir);
	DISX_VECTOR3 right;
	DISX_Vec3Cross( &right, &vup, &lookdir );

	DISX_MATRIX matTransform;
	DISX_MatrixIdentity( &matTransform );
	//matTransform.identity();
	matTransform._41 = vpos.x;   matTransform._42 = vpos.y;   matTransform._43 = vpos.z;
	matTransform._31 = lookdir.x;   matTransform._32 = lookdir.y;   matTransform._33 = lookdir.z;
	matTransform._21 = vup.x;   matTransform._22 = vup.y;   matTransform._23 = vup.z;
	matTransform._11 = right .x;   matTransform._12 = right .y;   matTransform._13 = right .z;

	//InvertFull( *matCam, matTransform );
	DISX_MatrixInverse(matCam, 0, &matTransform );
	//update OpenGL camera settings
  //  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10000.0);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

  /*  gluLookAt(m_cameraPosition[0],m_cameraPosition[1],m_cameraPosition[2],
		      m_cameraTargetPosition[0],m_cameraTargetPosition[1], m_cameraTargetPosition[2],
			  m_cameraUp.getX(),m_cameraUp.getY(),m_cameraUp.getZ());
			  */
}

void BUL_UpdateCamera( Mat44* matCam)
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	btTransform characterWorldTrans;

	//look at the vehicle
	characterWorldTrans = m_ghostObject->getWorldTransform();
	btVector3 up = characterWorldTrans.getBasis()[1];
	btVector3 backward = -characterWorldTrans.getBasis()[2];
	up.normalize ();
	backward.normalize ();

	btVector3 m_cameraTargetPosition = characterWorldTrans.getOrigin();
	btVector3 m_cameraPosition = m_cameraTargetPosition + up * 1.3 + backward * 12.0;
	
	//use the convex sweep test to find a safe position for the camera (not blocked by static geometry)
	btSphereShape cameraSphere(0.2f);
	btTransform cameraFrom,cameraTo;
	cameraFrom.setIdentity();
	cameraFrom.setOrigin(characterWorldTrans.getOrigin());
	cameraTo.setIdentity();
	cameraTo.setOrigin(m_cameraPosition);
	
	btCollisionWorld::ClosestConvexResultCallback cb( characterWorldTrans.getOrigin(), cameraTo.getOrigin() );
	cb.m_collisionFilterMask = btBroadphaseProxy::StaticFilter;
		
	dynamicsWorld->convexSweepTest(&cameraSphere,cameraFrom,cameraTo,cb);
	if (cb.hasHit())
	{

		btScalar minFraction  = cb.m_closestHitFraction;//btMax(btScalar(0.3),cb.m_closestHitFraction);
		m_cameraPosition.setInterpolate3(cameraFrom.getOrigin(),cameraTo.getOrigin(),minFraction);
	}


	Vec3 vpos = Vec3(m_cameraPosition[0],m_cameraPosition[1],m_cameraPosition[2]);
	Vec3 vup = Vec3(m_cameraUp.getX(),m_cameraUp.getY(),m_cameraUp.getZ());
	Vec3 vat = Vec3(m_cameraTargetPosition[0],m_cameraTargetPosition[1], m_cameraTargetPosition[2]) ;
	/*
			m_vEye =	Vec3(finalTransformationMatrix._41,finalTransformationMatrix._42,finalTransformationMatrix._43);
		m_vLook =	Vec3(finalTransformationMatrix._31,finalTransformationMatrix._32,finalTransformationMatrix._33);
		m_vUp =		Vec3(finalTransformationMatrix._21,finalTransformationMatrix._22,finalTransformationMatrix._23);
		m_vRight =	Vec3(finalTransformationMatrix._11,finalTransformationMatrix._12,finalTransformationMatrix._13);
	*/

	Vec3 lookdir = vat-vpos;
	lookdir.Normalize();
	
	Vec3 right = vup.Cross(lookdir);

	Mat44 matTransform;
	matTransform.identity();
	matTransform._41 = vpos.x;   matTransform._42 = vpos.y;   matTransform._43 = vpos.z;
	matTransform._31 = lookdir.x;   matTransform._32 = lookdir.y;   matTransform._33 = lookdir.z;
	matTransform._21 = vup.x;   matTransform._22 = vup.y;   matTransform._23 = vup.z;
	matTransform._11 = right .x;   matTransform._12 = right .y;   matTransform._13 = right .z;

	InvertFull( *matCam, matTransform );
	//update OpenGL camera settings
  //  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10000.0);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

  /*  gluLookAt(m_cameraPosition[0],m_cameraPosition[1],m_cameraPosition[2],
		      m_cameraTargetPosition[0],m_cameraTargetPosition[1], m_cameraTargetPosition[2],
			  m_cameraUp.getX(),m_cameraUp.getY(),m_cameraUp.getZ());
*/
}

int BUL_GetNumObjects()
{
	if( dynamicsWorld )
	{
		return dynamicsWorld->getNumCollisionObjects();
	}
	
	return 0;
}

void BUL_Tick(float inc, int maxSteps)
{
	if( dynamicsWorld )
	{
		BUL_TickCharacter(inc);
		dynamicsWorld->stepSimulation(inc,maxSteps);
	}
}

void BUL_TickCharacter(float dt)
{
	/*btTransform xformBox;
	myMotionStateBigBox->getWorldTransform(xformBox);
	btVector3 pos = xformBox.getOrigin();
	pos.setX( 50*sinf(dt));
	xformBox.setOrigin(pos);
	myMotionStateBigBox->setWorldTransform(xformBox);
	*/


//	bodyBox->translate(btVector3(-2*sinf(dt), 0.0f, 0.0f));
	//bigKinematicBox->Set
	///set walkDirection for our character
	btTransform xform;
	xform = m_ghostObject->getWorldTransform ();

	btVector3 forwardDir = xform.getBasis()[2];
//	printf("forwardDir=%f,%f,%f\n",forwardDir[0],forwardDir[1],forwardDir[2]);
	btVector3 upDir = xform.getBasis()[1];
	btVector3 strafeDir = xform.getBasis()[0];
	forwardDir.normalize ();
	upDir.normalize ();
	strafeDir.normalize ();

	btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
	btScalar walkVelocity = btScalar(2.1) * 4.0; // 4 km/h -> 1.1 m/s
	btScalar walkSpeed = walkVelocity * dt;

	//rotate view
	if (gLeft)
	{
		btMatrix3x3 orn = m_ghostObject->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),2*dt));
		m_ghostObject->getWorldTransform ().setBasis(orn);
	}

	if (gRight)
	{
		btMatrix3x3 orn = m_ghostObject->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-2*dt));
		m_ghostObject->getWorldTransform ().setBasis(orn);
	}

	if (gForward)
		walkDirection += forwardDir;

	if (gBackward)
		walkDirection -= forwardDir;	
	btScalar magnitude=0.0f;
	if( gJump )
	{
		magnitude = (btScalar(1.0)) * btScalar(8.0);
		//m_ghostObject->getCollisionShape()->applyCentralImpulse (upDir * magnitude);
		m_character->jump();
		
	}


	m_character->setWalkDirection(walkDirection*walkSpeed/*+magnitude*btVector3(0.0,0.25,0.0)*/);
	


}


void BUL_RotateCameraLeft(bool flag)
{
	gLeft = flag;
}
void BUL_RotateCameraRight(bool flag)
{
	gRight = flag;
}
void BUL_MoveCharacterForwards(bool flag)
{
	gForward = flag;
}
void BUL_MoveCharacterBackwards(bool flag)
{
	gBackward = flag;
}
void BUL_MakeCharacterJump(bool flag)
{
	gJump = flag;
}


void BUL_StartLoop()
{
	bulletLoop = true;
	bulletLoopCount = 0;
}

void BUL_GetCurrentObjectMatrix(DISX_MATRIX* mat)
{
	if( bulletLoop == false )
		return;

	btScalar	m[16];
	btMatrix3x3	rot;rot.setIdentity();
	//const int	numObjects=dynamicsWorld->getNumCollisionObjects();
	//btVector3 wireColor(1,0,0);

	btCollisionObject*	colObj=dynamicsWorld->getCollisionObjectArray()[bulletLoopCount];
	btRigidBody*		body=btRigidBody::upcast(colObj);
	if(body&&body->getMotionState())
	{
		btDefaultMotionState* myMotionState = (btDefaultMotionState*)body->getMotionState();
		myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);
		rot=myMotionState->m_graphicsWorldTrans.getBasis();
	}
	else
	{
		colObj->getWorldTransform().getOpenGLMatrix(m);
		rot=colObj->getWorldTransform().getBasis();
	}
	btVector3 wireColor(1.f,1.0f,0.5f); //wants deactivation
	if(bulletLoopCount & 1) wireColor=btVector3(0.f,0.0f,1.f);
	///color differently for active, sleeping, wantsdeactivation states
	if (colObj->getActivationState() == 1) //active
	{
		if (bulletLoopCount & 1)
		{
			wireColor += btVector3 (1.f,0.f,0.f);
		}
		else
		{			
			wireColor += btVector3 (.5f,0.f,0.f);
		}
	}
	if(colObj->getActivationState()==2) //ISLAND_SLEEPING
	{
		if(bulletLoopCount &1)
		{
			wireColor += btVector3 (0.f,1.f, 0.f);
		}
		else
		{
			wireColor += btVector3 (0.f,0.5f,0.f);
		}
	}
	btVector3 vscale(1.0f,1.0f,1.0f);
	if( body && body->getCollisionShape() )
		vscale = body->getCollisionShape()->getLocalScaling();
	
	btVector3 aabbMin,aabbMax;
	dynamicsWorld->getBroadphase()->getBroadphaseAabb(aabbMin,aabbMax);
		
	aabbMin-=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
	aabbMax+=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
//		printf("aabbMin=(%f,%f,%f)\n",aabbMin.getX(),aabbMin.getY(),aabbMin.getZ());
//		printf("aabbMax=(%f,%f,%f)\n",aabbMax.getX(),aabbMax.getY(),aabbMax.getZ());
//		m_dynamicsWorld->getDebugDrawer()->drawAabb(aabbMin,aabbMax,btVector3(1,1,1));

	//*mat = *(Mat44*)&m;
	//D3DXMatrixTranspose(&mat, &mat); 
	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			mat->m[i][j] = m[i*4 + j];
		}
	}
	mat->_11 = rot[0].x();
	mat->_21 = rot[0].y();
	mat->_31 = rot[0].z();

	mat->_12 = rot[1].x();
	mat->_22 = rot[1].y();
	mat->_32 = rot[1].z();

	mat->_13 = rot[2].x();
	mat->_23 = rot[2].y();
	mat->_33 = rot[2].z();

	DISX_MATRIX scale;
	DISX_MatrixScaling(&scale, vscale.getX(), vscale.getY(), vscale.getZ());

	*mat = scale * (*mat);
}

void BUL_GetCurrentObjectMatrix(Mat44* mat)
{
	if( bulletLoop == false )
		return;

	btScalar	m[16];
	btMatrix3x3	rot;rot.setIdentity();
	//const int	numObjects=dynamicsWorld->getNumCollisionObjects();
	//btVector3 wireColor(1,0,0);

	btCollisionObject*	colObj=dynamicsWorld->getCollisionObjectArray()[bulletLoopCount];
	btRigidBody*		body=btRigidBody::upcast(colObj);
	if(body&&body->getMotionState())
	{
		btDefaultMotionState* myMotionState = (btDefaultMotionState*)body->getMotionState();
		myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);
		rot=myMotionState->m_graphicsWorldTrans.getBasis();
	}
	else
	{
		colObj->getWorldTransform().getOpenGLMatrix(m);
		rot=colObj->getWorldTransform().getBasis();
	}
	btVector3 wireColor(1.f,1.0f,0.5f); //wants deactivation
	if(bulletLoopCount & 1) wireColor=btVector3(0.f,0.0f,1.f);
	///color differently for active, sleeping, wantsdeactivation states
	if (colObj->getActivationState() == 1) //active
	{
		if (bulletLoopCount & 1)
		{
			wireColor += btVector3 (1.f,0.f,0.f);
		}
		else
		{			
			wireColor += btVector3 (.5f,0.f,0.f);
		}
	}
	if(colObj->getActivationState()==2) //ISLAND_SLEEPING
	{
		if(bulletLoopCount &1)
		{
			wireColor += btVector3 (0.f,1.f, 0.f);
		}
		else
		{
			wireColor += btVector3 (0.f,0.5f,0.f);
		}
	}
	btVector3 vscale(1.0f,1.0f,1.0f);
	if( body && body->getCollisionShape() )
		vscale = body->getCollisionShape()->getLocalScaling();
	
	btVector3 aabbMin,aabbMax;
	dynamicsWorld->getBroadphase()->getBroadphaseAabb(aabbMin,aabbMax);
		
	aabbMin-=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
	aabbMax+=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
//		printf("aabbMin=(%f,%f,%f)\n",aabbMin.getX(),aabbMin.getY(),aabbMin.getZ());
//		printf("aabbMax=(%f,%f,%f)\n",aabbMax.getX(),aabbMax.getY(),aabbMax.getZ());
//		m_dynamicsWorld->getDebugDrawer()->drawAabb(aabbMin,aabbMax,btVector3(1,1,1));

	//*mat = *(Mat44*)&m;
	//D3DXMatrixTranspose(&mat, &mat); 
	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			mat->m[i][j] = m[i*4 + j];
		}
	}
	mat->_11 = rot[0].x();
	mat->_12 = rot[0].y();
	mat->_13 = rot[0].z();

	mat->_21 = rot[1].x();
	mat->_22 = rot[1].y();
	mat->_23 = rot[1].z();

	mat->_31 = rot[2].x();
	mat->_32 = rot[2].y();
	mat->_33 = rot[2].z();

	Mat44 scale;
	ScaleMatrix44(scale, vscale.getX(), vscale.getY(), vscale.getZ());

	*mat = scale * *mat;
}

void BUL_Increment()
{
	bulletLoopCount++;
}

void BUL_EndLoop()
{
	bulletLoop = false;
	bulletLoopCount = 0;
}




void BUL_Shutdown()
{

	if( m_indexVertexArrays )
		delete m_indexVertexArrays;

	for (int i=dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int j=0;j<collisionShapes.size();j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		delete shape;
	}

	if( sweepBP )
		delete sweepBP;



	delete dynamicsWorld;

	if( dispatcher )
		delete dispatcher;

	if( collisionConfiguration )
		delete collisionConfiguration;

	if( solver )
		delete solver;


	if( gVertices )
	{
		delete [] gVertices;
		gVertices = NULL;
	}
	if( gIndices )
	{
		delete [] gIndices;
		gIndices = NULL;
	}
}


btRigidBody* localCreateRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape)
{
	btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic)
		shape->calculateLocalInertia(mass,localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

#define USE_MOTIONSTATE 1
#ifdef USE_MOTIONSTATE
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass,myMotionState,shape,localInertia);

	btRigidBody* body = new btRigidBody(cInfo);
	body->setContactProcessingThreshold(BT_LARGE_FLOAT);

#else
	btRigidBody* body = new btRigidBody(mass,0,shape,localInertia);	
	body->setWorldTransform(startTransform);
#endif//

	dynamicsWorld->addRigidBody(body);

	return body;
}

void BUL_CreateTriMesh(D3DXVECTOR3 *verts, int totalVerts, Triangle *triangles, int totalTriangles )
{
	


	#define TRISIZE 10.f


#define USE_TRIMESH_SHAPE 1


	int vertStride = sizeof(btVector3);
	int indexStride = 3*sizeof(int);

	

	 gVertices = new btVector3[totalVerts];
	gIndices = new int[totalTriangles*3];

	for( int j = 0; j < totalVerts; j++ )
	{
		gVertices[j].setX( verts[j].x );
		gVertices[j].setY( verts[j].y );
		gVertices[j].setZ( verts[j].z );
	}

	for( int  j = 0; j < totalTriangles; j++ )
	{
		gIndices[j*3+0] = triangles[j].v[0];
		gIndices[j*3+1] = triangles[j].v[1];
		gIndices[j*3+2] = triangles[j].v[2];
	}

	int i;


	

	m_indexVertexArrays = new btTriangleIndexVertexArray(totalTriangles,
		gIndices,
		indexStride,
		totalVerts,(btScalar*) &gVertices[0].x(),vertStride);

	bool useQuantizedAabbCompression = true;

//comment out the next line to read the BVH from disk (first run the demo once to create the BVH)




	btVector3 aabbMin(-1000,-1000,-1000),aabbMax(1000,1000,1000);
	
	btBvhTriangleMeshShape* trimeshShape= new btBvhTriangleMeshShape(m_indexVertexArrays,useQuantizedAabbCompression,aabbMin,aabbMax);
	collisionShapes.push_back(trimeshShape);

	int maxSerializeBufferSize = 1024*1024*5;
	btDefaultSerializer*	serializer = new btDefaultSerializer(maxSerializeBufferSize);
	//serializer->setSerializationFlags(BT_SERIALIZE_NO_BVH);//	or BT_SERIALIZE_NO_TRIANGLEINFOMAP
	serializer->startSerialization();
	//registering a name is optional, it allows you to retrieve the shape by name
	//serializer->registerNameForPointer(trimeshShape,"mymesh");

	trimeshShape->serializeSingleBvh(serializer);

	serializer->finishSerialization();
	FILE* f2 = fopen("myShape.bullet","wb");
	fwrite(serializer->getBufferPointer(),serializer->getCurrentBufferSize(),1,f2);
	fclose(f2);


	btTransform startTransform;
	startTransform.setIdentity();
	btCollisionShape* groundShape = trimeshShape;
btRigidBody* body = localCreateRigidBody(0.f, startTransform,groundShape );
body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);//STATIC_OBJECT);
	/*


#ifdef USE_PARALLEL_DISPATCHER

#define USE_WIN32_THREADING
#ifdef USE_WIN32_THREADING

	int maxNumOutstandingTasks = 4;//number of maximum outstanding tasks
	Win32ThreadSupport* threadSupport = new Win32ThreadSupport(Win32ThreadSupport::Win32ThreadConstructionInfo(
								"collision",
								processCollisionTask,
								createCollisionLocalStoreMemory,
								maxNumOutstandingTasks));
#endif

	m_dispatcher = new	SpuGatheringCollisionDispatcher(threadSupport,maxNumOutstandingTasks,m_collisionConfiguration);
#else
	m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);
#endif//USE_PARALLEL_DISPATCHER


	*/






	
	
}