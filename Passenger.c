#include <stdio.h>
#include "Passenger.h"
struct passenger
{
	char name[20];
	char phone_number[12];
	char identity_card[19];

	struct Plane_information*plane;
	struct passenger*next;
};


/*@breif    添加同行乘客 
* @param    窗口句柄 
* @param	当前账户指针
* @return	乘客链表头指针orNULL
*/
struct passenger* Add_Passenger(HWND hwnd,struct tourist* Now_Account)
{
    if (Now_Account == NULL) {
        MessageBox(hwnd, "错误：游客账户为空！", "提示", MB_OK);
        return NULL;
    }

    struct passenger* new_passenger = (struct passenger*)malloc(sizeof(struct passenger));
    if (new_passenger == NULL) {
        MessageBox(hwnd, "内存分配失败！", "提示", MB_OK);
        return NULL;
    }

    MessageBox(hwnd, "请输入乘客姓名：", "提示", MB_OK);
    GetDlgItemText(hwnd, ID_EDIT_PASSENGER_NAME, new_passenger->name, 20);
    MessageBox(hwnd, "请输入乘客电话号码：", "提示", MB_OK);
    GetDlgItemText(hwnd, ID_EDIT_PASSENGER_PHONE, new_passenger->phone_number, 12);
    MessageBox(hwnd, "请输入乘客身份证号：", "提示", MB_OK);
    GetDlgItemText(hwnd, ID_EDIT_PASSENGER_ID, new_passenger->identity_card, 19);
    new_passenger->plane = NULL;
    new_passenger->next = NULL;

    if (Now_Account->Passenger_List == NULL)
    {
        Now_Account->Passenger_List = new_passenger;
    } 
    else
    {
        struct passenger* current = Now_Account->Passenger_List;
        // 检查链表头指针是否有效
        if (current == NULL) {
            MessageBox(hwnd, "错误：Passenger_List指针异常！", "提示", MB_OK);
            return NULL;
        }
        // 遍历到链表尾部
        while (current->next != NULL) 
        {
            current = current->next;
        }
        // 插入新节点前确保next为NULL
        new_passenger->next = NULL;
        current->next = new_passenger;
    }
    return new_passenger;
}
    void Add_Passengers(HWND hwnd,struct tourist* Now_Account)
    {
        char num[10];
        int i;
        MessageBox(hwnd, "请输入要添加的乘客人数：", "提示", MB_OK);
        GetDlgItemText(hwnd, ID_EDIT_PASSENGER_COUNT, num, sizeof(num));
        while (getchar() != '\n');
        for (i = 0; i < atoi(num); i++) 
        {
            MessageBox(hwnd, "\n--- 添加第 %d 位乘客 ---\n", "提示", MB_OK);
            Add_Passenger(hwnd, Now_Account);
        }
    }
/*@breif    列举乘客 
* @param    窗口句柄 
* @param	当前账户指针
* @return   无	
*/
    void List_Passenger(HWND hwnd,struct tourist* Now_Account)
    {
        if (Now_Account == NULL)
        {
            MessageBox(hwnd, "错误：游客账户为空，无法列出乘客！", "提示", MB_OK);
            return;
        }

        struct passenger* p1 = Now_Account->Passenger_List;
        if (p1 == NULL)
        {
            MessageBox(hwnd, "没有乘客信息！", "提示", MB_OK);
            return;
        }

        MessageBox(hwnd, "乘客列表：", "提示", MB_OK);
        while (p1 != NULL)
        {
            MessageBox(hwnd, "-------------------------", "提示", MB_OK);
            MessageBox(hwnd, "姓名: %s\n", "提示", MB_OK);
            p1 = p1->next;
        }
    }

/*@breif    查找乘客
* @param    窗口句柄 
* @param	当前账户指针
* @return   找到的同行乘客指针orNULL
*/
  struct passenger* Find_Passenger(HWND hwnd,struct tourist* Now_Account)
{
    if (Now_Account == NULL)
    {
        MessageBox(hwnd, "错误：游客账户为空，无法查找乘客！", "提示", MB_OK);
        return NULL;
    }

    struct passenger* p1 = Now_Account->Passenger_List;
    char identity_card[19];
    MessageBox(hwnd, "请输入乘客的身份证号：", "提示", MB_OK);
    GetDlgItemText(hwnd, ID_EDIT_PASSENGER_ID, identity_card, 19);
    while (getchar() != '\n');

    while (p1 != NULL)
    {
        if (strcmp(p1->identity_card, identity_card) == 0)
        {
            MessageBox(hwnd, "找到乘客信息！", "提示", MB_OK);
            MessageBox(hwnd, "姓名: %s\n", "提示", MB_OK);
            MessageBox(hwnd, "电话号码: %s\n", "提示", MB_OK);
            MessageBox(hwnd, "身份证号: %s\n", "提示", MB_OK);
            return p1;
        }
        p1 = p1->next;
    }
    MessageBox(hwnd, "未找到身份证号为 %s 的乘客！", "提示", MB_OK);
    return NULL; 
}

/*@breif    删除同行乘客
* @param    窗口句柄 
* @param	当前账户指针
* @return   无
*/
    void Cancel_Passenger(HWND hwnd,struct tourist* Now_Account)
    {
        if (Now_Account == NULL)
        {
            MessageBox(hwnd, "错误：游客账户为空，无法取消乘客！", "提示", MB_OK);
            return;
        }

        struct passenger* p1 = Now_Account->Passenger_List;
        struct passenger* prev = NULL;
        char identity_card[19];
        MessageBox(hwnd, "请输入要取消的乘客身份证号：", "提示", MB_OK);
        GetDlgItemText(hwnd, ID_EDIT_PASSENGER_ID, identity_card, 19);
        while (getchar() != '\n');

        while (p1 != NULL)
        {
            if (strcmp(p1->identity_card, identity_card) == 0)
            {
                if (prev == NULL)
                {
                    Now_Account->Passenger_List = p1->next; 
                }
                else
                {
                    prev->next = p1->next; 
                }
                free(p1); 
                MessageBox(hwnd, "乘客已取消！", "提示", MB_OK);
                return;
            }
            prev = p1;
            p1 = p1->next;
        }
        MessageBox(hwnd, "未找到乘客信息！", "提示", MB_OK);
    }