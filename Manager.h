#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "windows_Define.h"
#include "plane.h"

#define MANAGER_ACCOUNT "Manager"
#define MANAGER_PASSWORD "1234"

extern Plane_information* g_head;  // 航班信息链表头指针

void Manager_Login(HWND hwnd);
Plane_information* Manager_Delete_Plane(HWND hwnd,Plane_information*head);



#endif
