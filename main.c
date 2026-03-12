#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "tourist.h"
//gcc -g main.c tourist.c -o main.
struct tourist*Now_Account=NULL;
struct tourist*head=NULL;
int main()
{
	head=Register_Tourist(head);
	 List_Tourist(head);
	 printf("2\n");
	head=Register_Tourist(head);
	 List_Tourist(head);
	 Find_Tourist_PhoneNumber(head,"12345678901");
	 system("pause");
	/*free();*/
	return 0;
	
}