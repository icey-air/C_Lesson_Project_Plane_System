#include "DataFile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//@brief 保存航班数据到文件
//@param head 航班信息链表头指针
//@return 0成功，-1失败
int SavePlaneData(Plane_information* head)
{
    FILE*fp=fopen(PLANE_DATA_FILE,"wb");
    if(fp==NULL)
    {
        return -1;
    }

    Plane_information *p=head;
    int count=0;
    //写入数据数量
    while(p!=NULL)
    {
        count++;
        p=p->next;
    }

    fwrite(&count,sizeof(int),1,fp);

    //写入数据
    Plane_information *p1=head;
    while(p1!=NULL)
    {
         // 保存 ID
    fwrite(p1->id, sizeof(char), 20, fp);
    // 保存整型数据
    fwrite(&p1->whole_seat, sizeof(int), 1, fp);
    fwrite(&p1->rest_seat, sizeof(int), 1, fp);
    fwrite(p1->take_off_time, sizeof(int), 5, fp);
    fwrite(p1->landing_time, sizeof(int), 5, fp);
    fwrite(&p1->prize, sizeof(float), 1, fp);
    fwrite(&p1->num, sizeof(int), 1, fp);
    fwrite(p1->starting_point, sizeof(char), 20, fp);
    fwrite(p1->destination, sizeof(char), 20, fp);
    
    p1=p1->next;
    }

    fclose(fp);
    return 0;
}


//@brief 加载航班数据
//@param head 航班信息链表头指针地址
//@return 0成功，-1失败
int LoadPlaneData(Plane_information **head)
{
    FILE* fp=fopen(PLANE_DATA_FILE,"rb");
    if(fp==NULL)
    {
        *head=NULL;
        return -1;
    }

    int count;
    fread(&count,sizeof(int),1,fp);

    *head=NULL;
    Plane_information*tail=NULL;

    for(int i=0;i<count;i++)
    {
        Plane_information*newplane=(Plane_information*)malloc(sizeof(Plane_information));
        if(newplane==NULL)
        {
            fclose(fp);
            return -1;
        }
        else
        {
            // 读取 ID
fread(newplane->id, sizeof(char), 20, fp);
// 读取整型数据
fread(&newplane->whole_seat, sizeof(int), 1, fp);
fread(&newplane->rest_seat, sizeof(int), 1, fp);
fread(newplane->take_off_time, sizeof(int), 5, fp);
fread(newplane->landing_time, sizeof(int), 5, fp);
fread(&newplane->prize, sizeof(float), 1, fp);
fread(&newplane->num, sizeof(int), 1, fp);
fread(newplane->starting_point, sizeof(char), 20, fp);
fread(newplane->destination, sizeof(char), 20, fp);
            newplane->next=NULL;
            newplane->passenger=NULL;  // 重置指针

            if(*head==NULL)
            {
                *head=newplane;
                tail=newplane;
            }
            else
            {
                tail->next=newplane;
                tail=newplane;
            }
        }
    }
    fclose(fp);
    return 0;
}


static Plane_information* FindPlaneById(Plane_information* head, char* id)
{
    Plane_information* p = head;
    while (p != NULL)
    {
        if (strcmp(p->id, id) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

// 保存所有游客数据（包括订票信息）
int SaveAllTourists(struct tourist* head)
{
    FILE* fp = fopen(TOURIST_DATA_FILE, "wb");
    if (fp == NULL)
    {
        return -1;
    }
    
    struct tourist* p = head;
    int count = 0;
    
    // 统计游客数量
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    
    // 写入数量
    fwrite(&count, sizeof(int), 1, fp);
    
    // 写入每个游客数据
    p = head;
    while (p != NULL)
    {
        // 保存游客基本信息
        fwrite(p, sizeof(struct tourist), 1, fp);
        
        // 保存该游客的订票数量
        int ticketCount = 0;
        struct Ticket* t = p->Ticket_List;
        while (t != NULL)
        {
            ticketCount++;
            t = t->next;
        }
        fwrite(&ticketCount, sizeof(int), 1, fp);
        
        // 保存每张机票的航班号
        t = p->Ticket_List;
        while (t != NULL)
        {
            // 保存航班号（20个字符）
            fwrite(t->Plane_Ticket->id, sizeof(char), 20, fp);
            t = t->next;
        }
        
        p = p->next;
    }
    
    fclose(fp);
    return 0;
}

// 加载所有游客数据
int LoadAllTourists(struct tourist** head, Plane_information* planeHead)
{
    FILE* fp = fopen(TOURIST_DATA_FILE, "rb");
    if (fp == NULL)
    {
        *head = NULL;
        return -1;
    }
    
    int count;
    fread(&count, sizeof(int), 1, fp);
    
    *head = NULL;
    struct tourist* tail = NULL;
    
    for (int i = 0; i < count; i++)
    {
        struct tourist* newTourist = (struct tourist*)malloc(sizeof(struct tourist));
        if (newTourist == NULL)
        {
            fclose(fp);
            return -1;
        }
        
        fread(newTourist, sizeof(struct tourist), 1, fp);
        
        // 重置指针字段（文件中的旧地址无效）
        newTourist->next = NULL;
        newTourist->Ticket_List = NULL;
        
        // 读取订票数量
        int ticketCount;
        fread(&ticketCount, sizeof(int), 1, fp);
        
        // 恢复订票信息
        struct Ticket* ticketTail = NULL;
        for (int j = 0; j < ticketCount; j++)
        {
            char planeId[20];
            fread(planeId, sizeof(char), 20, fp);
            
            // 根据航班号找到对应的航班信息
            Plane_information* foundPlane = FindPlaneById(planeHead, planeId);
            if (foundPlane != NULL)
            {
                struct Ticket* newTicket = (struct Ticket*)malloc(sizeof(struct Ticket));
                if (newTicket != NULL)
                {
                    newTicket->Plane_Ticket = foundPlane;
                    newTicket->Passsenger_List = NULL;
                    newTicket->next = NULL;
                    
                    if (newTourist->Ticket_List == NULL)
                    {
                        newTourist->Ticket_List = newTicket;
                        ticketTail = newTicket;
                    }
                    else
                    {
                        ticketTail->next = newTicket;
                        ticketTail = newTicket;
                    }
                }
            }
        }
        
        if (*head == NULL)
        {
            *head = newTourist;
            tail = newTourist;
        }
        else
        {
            tail->next = newTourist;
            tail = newTourist;
        }
    }
    
    fclose(fp);
    return 0;
}