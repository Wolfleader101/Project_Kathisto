#include <stdlib.h>
#include <stdio.h>

#include "window/Window.h"
#include "utilities/vectorUtil.h"

int main(int argc, char** argv)
{
	//InitialiseWindow(&argc, argv, "Project Kathisto");

    vector v;
    Initialise_Vector(&v);

    Add_To_Vector(&v, "Bonjour");
    Add_To_Vector(&v, "tout");
    Add_To_Vector(&v, "le");
    Add_To_Vector(&v, "monde");

    for (unsigned i = 0; i < Number_Of_Elements(&v); i++)
        printf("%s ", (char*)Get_From_Vector_Index(&v, i));
    printf("\n");

    Delete_Vector_Element(&v, 3);
    Delete_Vector_Element(&v, 2);
    Delete_Vector_Element(&v, 1);

    Set_At_Vector_Index(&v, 0, "Hello");
    Add_To_Vector(&v, "World");

    for (unsigned i = 0; i < Number_Of_Elements(&v); i++)
        printf("%s ", (char*)Get_From_Vector_Index(&v, i));
    printf("\n");

    Free_Vector_Memory(&v);

	return 1;
}