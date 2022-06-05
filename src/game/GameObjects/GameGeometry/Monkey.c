#include "Monkey.h"

OnStart OnMonkeyStart(GameObject* gameObject)
{

	char* objFile = "assets/models/objs/monkey.obj";;

	objModel objData = LoadOBJFile(objFile);


	gameObject->name = "Monkey";

	gameObject->mesh = objToMesh(objData);

	gameObject->transform.position = (Vector3){ 10.0f, 10.0f, 30.0f };
	gameObject->transform.scale = (Vector3){ 5.0f, 5.0f, 5.0f };
	gameObject->rigidBody.isStatic = true;
}


Mesh objToMesh(objModel model)
{
	const RGBA colorBuffer[] = { {1.0f, 0.0f, 0.5f, 1.0f} };
	Mesh mesh = (Mesh){
		.points = model.vertPosition.vec3Items,
		.indices = model.vertexPosIndicies.vec3IntItems,
		.pointSize = model.nVerts,
		.indexCount = (size_t)model.nFaces * 3,
		.colors = colorBuffer,
		.isUniformColor = true
	};

	return mesh;

}
