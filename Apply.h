#ifndef __APPLY_H
#define __APPLY_H

#include "plane.h"

void Book_Ticket(HWND hwnd,struct tourist*Now_Account,struct Plane_information*head);
void Cancel_Ticket_Reservation(struct tourist*Now_Account);
void List_Ticket_Reservation(struct tourist*Now_Account);

#endif 