#include <stdlib.h>
#include <stdio.h>

#include "window/Window.h"
#include "math/Vector.h"
#include "utilities/vectorUtil.h"

int main(int argc, char** argv)
{
	//InitialiseWindow(&argc, argv, "Project Kathisto");

    listVec3 v;
    Vec3_InitialiseList(&v);

    Vec3_AddToList(&v, (Vector3) { 1.4, 3.3, 7.62 });
    Vec3_AddToList(&v, (Vector3) { 343.4, 652.3, 2346.5 });
    Vec3_AddToList(&v, (Vector3) { 534.4, 33.3, 23.5 });
    Vec3_AddToList(&v, (Vector3) { 4235.4, 53.3, 643.5 });
    Vec3_AddToList(&v, (Vector3) { 64532.4, 457.3, 23.5 });
    Vec3_AddToList(&v, (Vector3) { 643.4, 5321.3, 537.5 });
    Vec3_AddToList(&v, (Vector3) { 75.4, 33.3, 23.5 });

    for (unsigned i = 0; i < v.vecTotalElements; i++)
        printf("%0.2f %0.2f %0.2f\n", Vec3_GetFromListIndex(&v, i).x, Vec3_GetFromListIndex(&v, i).y, Vec3_GetFromListIndex(&v, i).z);
    printf("\n");
    printf("%d\n", v.vecTotalElements);

    Vec3_FreeListMemory(&v);

	return 1;
}