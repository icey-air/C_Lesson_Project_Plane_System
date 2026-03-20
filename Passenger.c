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



struct passenger* Add_Passenger(struct tourist* Now_Account)
{
    if (Now_Account == NULL) {
        printf("错误：游客账户为空！\n");
        return NULL;
    }

    struct passenger* new_passenger = (struct passenger*)malloc(sizeof(struct passenger));
    if (new_passenger == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    printf("请输入乘客姓名：");
    scanf("%19s", new_passenger->name);
    printf("请输入乘客电话号码：");
    scanf("%11s", new_passenger->phone_number);
    printf("请输入乘客身份证号：");
    scanf("%18s", new_passenger->identity_card);
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
            printf("错误：Passenger_List指针异常！\n");
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
    void Add_Passengers(struct tourist* Now_Account)
    {
        int num, i;
        printf("请输入要添加的乘客人数：");
        scanf("%d", &num);
        while (getchar() != '\n');
        for (i = 0; i < num; i++) 
        {
            printf("\n--- 添加第 %d 位乘客 ---\n", i + 1);
            Add_Passenger(Now_Account);
        }
    }

    void List_Passenger(struct tourist* Now_Account)
    {
        if (Now_Account == NULL)
        {
            printf("错误：游客账户为空，无法列出乘客！\n");
            return;
        }

        struct passenger* p1 = Now_Account->Passenger_List;
        if (p1 == NULL)
        {
            printf("没有乘客信息！\n");
            return;
        }

        printf("乘客列表：\n");
        while (p1 != NULL)
        {
            printf("姓名: %s, 电话号码: %s, 身份证号: %s\n", p1->name, p1->phone_number, p1->identity_card);
            p1 = p1->next;
        }
    }


  struct passenger* Find_Passenger(struct tourist* Now_Account)
{
    if (Now_Account == NULL)
    {
        printf("错误：游客账户为空，无法查找乘客！\n");
        return NULL;
    }

    struct passenger* p1 = Now_Account->Passenger_List;
    char identity_card[19];
    printf("请输入乘客的身份证号：\n");
    scanf("%19s", identity_card);
    while (getchar() != '\n');

    while (p1 != NULL)
    {
        if (strcmp(p1->identity_card, identity_card) == 0)
        {
            printf("找到乘客信息！\n");
            printf("姓名: %s, 电话号码: %s, 身份证号: %s\n", p1->name, p1->phone_number, p1->identity_card);
            return p1;
        }
        p1 = p1->next;
    }
    printf("未找到身份证号为 %s 的乘客！\n", identity_card);
    return NULL; 
}

    void Cancel_Passenger(struct tourist* Now_Account)
    {
        if (Now_Account == NULL)
        {
            printf("错误：游客账户为空，无法取消乘客！\n");
            return;
        }

        struct passenger* p1 = Now_Account->Passenger_List;
        struct passenger* prev = NULL;
        char identity_card[19];
        printf("请输入要取消的乘客身份证号：\n");
        scanf("%19s", identity_card);
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
                printf("乘客已取消！\n");
                return;
            }
            prev = p1;
            p1 = p1->next;
        }
        printf("未找到乘客信息！\n");
    }