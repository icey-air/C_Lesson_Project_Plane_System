#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include "tourist.h"
#include "windows_Define.h"
struct passenger
{
	char name[20];
	char phone_number[12];
	char identity_card[19];

	struct Plane_information*plane;
	struct passenger*next;
};

struct passenger* Add_Passenger(HWND hwnd,struct tourist* Now_Account);
void Add_Passengers(HWND hwnd,struct tourist* Now_Account);
void List_Passenger(HWND hwnd,struct tourist* Now_Account);
struct passenger* Find_Passenger(HWND hwnd,struct tourist* Now_Account);
void Cancel_Passenger(HWND hwnd,struct tourist* Now_Account);

#endif