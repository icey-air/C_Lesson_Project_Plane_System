#ifndef __TOURIST_H__
#define __TOURIST_H__
#include "plane.h"
#include "windows_Define.h"
#include "windef.h"
#include "Tourist_File.h"
#define Ticket_LEN	sizeof(struct Ticket)
#define Tourist_LEN sizeof(struct tourist)

struct tourist* Register_Tourist(HWND hwnd,struct tourist*head);
struct tourist* Loging_Account(HWND hwnd,struct tourist*head);
void List_Tourist(struct tourist* head);
struct tourist* Remove_Tourist(struct tourist*head,int id);
int Change_tourist(HWND hwnd,int wmId,struct tourist*Now_Account);
void Change_Information_Comfirm(HWND hwnd,int Change_What,struct tourist* Now_Account);
struct tourist* Find_Tourist_Account(struct tourist* head,char Account[11]);
struct tourist* Find_Tourist_PhoneNumber(struct tourist* head,char Phone_Number[12]);
void Change_Password(struct tourist*Now_Account);
void Change_Phone_Number(struct tourist*Now_Account);
//游客结构体
typedef struct tourist
{  		int id;
	  char name[20];
    char phone_number[12];
	char Account[20];
    char password[21];
	char identity_card[19];
	int Count;
	int Airfare_Cost;//开销

	struct Ticket*Ticket_List;
	struct passenger*Passenger_List;
	struct tourist *next;
}tourist;

struct passenger
{
	char name[20];
	char phone_number[12];
	char identity_card[19];

	struct Plane_information*plane;
	struct passenger*next;
};


typedef struct Ticket
{
	Plane_information*Plane_Ticket;
	struct passenger*Passsenger_List;
	struct Ticket*next;

}Ticket;

#endif