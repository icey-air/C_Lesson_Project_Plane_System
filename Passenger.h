#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include "tourist.h"
struct passenger
{
	char name[20];
	char phone_number[12];
	char identity_card[19];

	struct Plane_information*plane;
	struct passenger*next;
};

struct passenger* Add_Passenger(struct tourist*Now_Account);
void Add_Passengers(struct tourist* Now_Account);
void List_Passenger(struct tourist* Now_Account);
struct passenger* Find_Passenger(struct tourist* Now_Account);
void Cancel_Passenger(struct tourist* Now_Account);

#endif