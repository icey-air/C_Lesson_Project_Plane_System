#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "tourist.h"
//gcc -g main.c tourist.c -o main.exe
struct tourist*Now_Account=NULL;
struct tourist*head=NULL;
int main()
{
	head=Register_Tourist(head);
	 List_Tourist(head);
	 printf("2\n");
	Register_Tourist(head);
	 List_Tourist(head);
	/*free();*/
	return 0;
	system("pause");
}