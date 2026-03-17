#ifndef __TICKET_H
#define __TICKET_H

#include "plane.h"

void Book_Ticket(HWND hwnd,struct tourist*Now_Account,struct Plane_information*head);
void Cancel_Ticket_Reservation(HWND hwnd,struct tourist*Now_Account);
void List_Ticket_Reservation(HWND hwnd,struct tourist*Now_Account);
void Add_Ticket(HWND hwnd,struct tourist*Now_Account,Plane_information*Book_Plane);
struct Ticket* Find_Ticket(struct tourist*Now_Account,Plane_information*Book_Plane);
#endif 