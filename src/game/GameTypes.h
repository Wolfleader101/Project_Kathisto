#pragma once

#include "GameIncludes.h"

/**
 * @struct Time
 * @brief time data which contains current time, previous time and delta time, used for calculations
 */
typedef struct Time
{
	/**
	 * @brief the current time
	 */
	float currTime;

	/**
	 * @brief the previous time
	 */
	float prevTime;

	/**
	 * @brief the delta time
	 */
	float deltaTime;
} Time;

/**
 * @struct Transform
 * @brief the transform component for a gameobject
 */
typedef struct Transform
{
	/**
	 * @brief the world postion of the gameobject
	 */
	Vector3 position;

	/**
	 * @brief  the rotation of the gameobject
	 */
	Vector3 rotation;

	/**
	 * @brief the scale of the gameobject
	 */
	Vector3 scale;

} Transform;

typedef struct GLColour
{
	/**
	 * @brief Red Value
	 */
	GLfloat r;
	/**
	 * @brief Green Value
	 */
	GLfloat g;
	/**
	 * @brief Blue Value
	 */
	GLfloat b;
	/**
	 * @brief Alpha Value
	 */
	GLfloat a;
} GLColour;

/**
 * @struct Mesh
 * @brief the mesh component used for drawing a gameobject
 */
typedef struct Mesh
{
	/**
	 * @brief the vertex points for the mesh
	 */
	Vector3 *points;

	/**
	 * @brief the number of the vertex points
	 */
	size_t vertexAmount;

	/**
	 * @brief the uvs for the mesh
	 */
	Vector2* uvs;

	/**
	 * @brief the number of the vertex uvs
	 */
	size_t uvAmount;

	/**
	 * @brief the vertex normals for the mesh
	 */
	Vector3* normals;

	/**
	 * @brief the number of the vertex normals
	 */
	size_t normalAmount;

	/**
	 * @brief the vertex indices buffer for the mesh
	 */
	Vector3Int *vertexIndices;

	/**
	 * @brief the vertex uv indices buffer for the mesh
	 */
	Vector3Int* uvIndices;

	/**
	 * @brief the vertex normal indices buffer for the mesh
	 */
	Vector3Int* normalIndices;

	/**
	 * @brief the number of indices
	 */
	size_t indexCount;

	/**
	 * @brief color buffer for the mesh
	 */
	RGBA *colors;

	/**
	 * @brief if its a uniform (single) color
	 */
	bool isUniformColor;

	/**
	 * @brief If the mesh has a material
	 */
	bool hasMaterial;

	/**
	 * @brief The diffuse values of the mesh
	 */

	GLColour meshDiffuse;
	/**
	 * @brief The ambient values of the mesh
	 */

	GLColour meshAmbient;
	/**
	 * @brief The specular values of the mesh
	 */

	GLColour meshSpecular;
	/**
	 * @brief The shininess values of the mesh
	 */
	GLColour meshShininess;

	/**
	 * @brief debug mesh to draw with lines
	 */
	bool debug;

	/**
	 * @brief dont draw a mesh
	 */
	bool disableMesh;
} Mesh;

/**
 * @struct BoudingBox
 * @brief the bounding box body for collision detection
 */
typedef struct BoudingBox
{
	/**
	 * @brief the min positions of a bounding box
	 */
	Vector3 minPos;

	/**
	 * @brief the max positions of a bounding box
	 */
	Vector3 maxPos;

	/**
	 * @brief the gameobject id of the bounding box
	 */
	size_t gameObjectId;
} BoudingBox;

/**
 * @struct SphereBody
 * @brief a sphere body for collision detection
 */
typedef struct SphereBody
{
	/**
	 * @brief if the body is a sphere, as every rigidbody contains this
	 */
	bool isSphere;

	/**
	 * @brief radius of the sphere
	 */
	float radius;

} SphereBody;

/**
 * @struct RigidBody
 * @brief a rigidbody components which is used for physics interactions in the game
 */
typedef struct RigidBody
{
	/**
	 * @brief if the rigidbody is static
	 */
	bool isStatic;

	/**
	 * @brief if the rigidbody is a floor
	 */
	bool isFloor;

	/**
	 * @brief if the rigidbody is currently on the ground
	 */
	bool onGround;

	/**
	 * @brief if the rigid body should use gravity
	 */
	bool useGravity;

	/**
	 * @brief if the rigidbody is a trigger
	 *
	 */
	bool isTrigger;

	/**
	 * @brief if the rigidbody will repel from colliding objects 
	 * 
	 */
	bool isPassive;

	/**
	 * @brief mass of the rigidbody (defaults 50)
	 */
	float mass;

	/**
	 * @brief the velocity of the rigidbody
	 */
	Vector3 velocity;

	/**
	 * @brief the bounding sphere body, if a sphere collider
	 */
	SphereBody sphereBody;

	/**
	 * @brief the bounding box body if its a box collider
	 */
	BoudingBox boundingBox;

	/**
	 * @brief if you want to enable bounding box debug drawing
	 */
	bool debug;
} RigidBody;

typedef struct GameObject GameObject;

typedef void (*OnStart)(GameObject *);
typedef void (*OnUpdate)(Time, GameObject *);
typedef void (*OnLateUpdate)(Time, GameObject *);
typedef void (*OnFixedUpdate)(Time, GameObject *);
typedef void (*OnCollision)(Time, GameObject *, GameObject *);

/**
 * @struct GameObject
 * @brief a basic gameobject component which contains components for drawing the gameobject, physics, and callbacks
 */
struct GameObject
{
	/**
	 * @brief id of the gameobject
	 */
	size_t id;

	/**
	 * @brief name of the gameobject
	 */
	char *name;

	/**
	 * @brief transform component of the gameobject
	 */
	Transform transform;

	/**
	 * @brief mesh component of the gameobject
	 */
	Mesh mesh;

	/**
	 * @brief rigidbody component of the gameobject
	 */
	RigidBody rigidBody;

	/**
	 * @brief debug bool for if you want to enable gizmos
	 */
	bool debug;

	/**
	 * @brief on start callback, called at the start of the gameobjects life cycle, this should never be NULL and is required
	 */
	OnStart OnStart;

	/**
	 * @brief on update callback, this is called every tick
	 */
	OnUpdate OnUpdate;

	/**
	 * @brief on late update callback, this is called at the end of every tick
	 */
	OnLateUpdate OnLateUpdate;

	/**
	 * @brief on fixed update, this is called on a fixed update for physics
	 */
	OnFixedUpdate OnFixedUpdate;
	OnCollision OnCollision;
};

/**
 * @struct GameObjectManager
 * @brief GameObjectManager struct which contains an array of gameobject pointers, and bounding boxes
 */
typedef struct GameObjectManager
{
	/**
	 * @brief list of gameobject pointers
	 */
	GameObject **gameObjects;

	/**
	 * @brief list of bounding box pointers
	 */
	BoudingBox **boundingBoxes;

	/**
	 * @brief total capacity of manager
	 */
	size_t count;

	/**
	 * @brief the length of the manager
	 */
	size_t lastIndex;

	/**
	 * @brief the freespace of the manager
	 */
	size_t freeSpace;
} GameObjectManager;

/**
 * @brief enum containing a list of collision directions
 */
typedef enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FORWARD,
	BACK,
} CollisionDir;

/**
 * @struct CollisionData
 * @brief object containing collision data
 */
typedef struct CollisionData
{
	/**
	 * @brief the colliding game object
	 */
	GameObject *collidingGameObject;

	/**
	 * @brief the colliding faces
	 */
	Vector3 collidingFace;
	// CollisionDir collidingFace;
} CollisionData;