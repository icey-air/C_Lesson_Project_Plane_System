#ifndef __TOURIST_H__
#define __TOURIST_H__



struct tourist* Register_Tourist(struct tourist*head);
void List_Tourist(struct tourist* head);
struct tourist* Remove_Tourist(struct tourist*head,int id);
void Change_tourist(struct tourist*Now_Account);
struct tourist* Find_Tourist_Account(struct tourist* head,char Account[11]);
struct tourist* Find_Tourist_PhoneNumber(struct tourist* head,char Phone_Number[12]);


//游客结构体
struct tourist
{  		int id;
	  char name[20];
    char phone_number[12];
	char Account[11];
    char password[21];
	int Count;
	int Airfare_Cost;//开销
	//plane
	struct tourist *passenger;//一个人买多张票
	struct tourist *next;
};


typedef struct 
{
char id[20];//飞机编号
int whole_seat;//总座位
int rest_seat;
int take_off_time[5];//起飞时间
int landing_time[5];//着陆时间
int if_reserve;//预定为1，未预定为0
float prize;//价格
int num;//索引序号


struct Plane_information*next;
}Plane_information;

#endif