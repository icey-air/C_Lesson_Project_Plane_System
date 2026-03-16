#ifndef __PLANE_H__
#define __PLANE_H__

#include "windows_Define.h"


typedef struct Plane_information
{
char id[20];//飞机编号
int whole_seat;//总座位
int Seat_Category[3];//座位类别
int rest_seat;//剩余座位
int take_off_time[5];//起飞时间
int landing_time[5];//着陆时间
float prize;//价格
int num;//索引序号

struct tourist  *passenger;//乘客
struct Plane_information*next;
}Plane_information;



Plane_information *Create_Plane_List(void);
void Print_Plane_List(Plane_information *head);
Plane_information* Delete_Plane(HWND hwnd,Plane_information*head);
void update_Plane(Plane_information*head);
Plane_information* Add_Plane(Plane_information *head);
struct Plane_information* Find_Plane_Day(Plane_information*head);

struct Plane_information* Find_Plane_ID(HWND hwnd,Plane_information*head);

extern Plane_information* g_head;  // 航班信息链表头指针
#include "tourist.h"
#endif