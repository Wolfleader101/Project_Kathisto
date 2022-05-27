#include <stdlib.h>
#include <stdio.h>

#include "window/Window.h"
#include "math/Vector.h"
#include "utilities/vectorUtil.h"

int main(int argc, char** argv)
{
	//InitialiseWindow(&argc, argv, "Project Kathisto");

    list v;
    InitialiseVector(&v);

    Vector3 *test = malloc(sizeof(Vector3) + 1);

    test->x = 27.0;
    test->y = 12.0;
    test->z = 76.0;

    AddToVector(&v, test);

    for (unsigned i = 0; i < v.vecTotalElements; i++)
        printf("%f ", (Vector3*)GetFromVectorIndex(&v, i));
    printf("\n");

    FreeVectorMemory(&v);

	return 1;
}