#ifndef __TOURIST_H__
#define __TOURIST_H__



struct tourist* Register_Tourist(struct tourist*head);
void List_Tourist(struct tourist* head);
struct tourist* Remove_Tourist(struct tourist*head,int id);
void Change_tourist(struct tourist*Now_Account);
struct tourist* Find_Tourist_Account(struct tourist* head,char Account[11]);



//游客结构体
struct tourist
{  		int id;
	  char name[20];
    char phone_number[12];
	char Account[11];
    char password[21];
	//plane
	struct tourist *passenger;//一个人买多张票
	struct tourist *next;
};


#endif