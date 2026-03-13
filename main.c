#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "tourist.h"
#include "plane.h"

//gcc -g main.c tourist.c -o main.
struct tourist*Now_Account=NULL;
struct tourist*head=NULL;
Plane_information* Plane_head=NULL;
Plane_information* Now_Plane=NULL;

int main()
{
	Plane_head=Create_Plane_List();
	Print_Plane_List(Plane_head);
	Now_Plane=Find_Plane_Day(Plane_head);

	
	/*free();*/
	return 0;
	
}