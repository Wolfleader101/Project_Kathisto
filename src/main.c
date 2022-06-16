#define STB_IMAGE_IMPLEMENTATION //Needed in main.c for the stb_image library to function

#include <stdlib.h>
#include <stdio.h>

#include "window/Window.h"

int main(int argc, char** argv)
{
	InitialiseWindow(&argc, argv, "Project Kathisto");

	return 1;
}