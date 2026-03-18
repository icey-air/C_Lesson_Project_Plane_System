#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include "plane.h"



/*@breif	打印航班信息
* @param	航班信息结构体头指针
* @return	无
*/
void Print_Plane_List(Plane_information *head)
{
    Plane_information *p;
    p=head;
    if(p==NULL)
    {
        printf("航班列表为空，无法打印\n");
        return;
    }
    

    while(p->next!=NULL)
    {
    printf("%s\n",p->id);
    printf("%d %d %d\n",p->whole_seat,p->rest_seat,p->prize);
    printf("year:%d month:%d date:%d hour:%d minute:%d\n",p->take_off_time[0],p->take_off_time[1],p->take_off_time[2],p->take_off_time[3],p->take_off_time[4]);
    printf("year:%d month:%d date:%d hour:%d minute:%d\n",p->landing_time[0],p->landing_time[1],p->landing_time[2],p->landing_time[3],p->landing_time[4]);
    p=p->next;
    }

    printf("%s\n",p->id);
    printf("%d %d %d\n",p->whole_seat,p->rest_seat,p->prize);
    printf("year:%d month:%d date:%d hour:%d minute:%d\n",p->take_off_time[0],p->take_off_time[1],p->take_off_time[2],p->take_off_time[3],p->take_off_time[4]);
    printf("year:%d month:%d date:%d hour:%d minute:%d\n",p->landing_time[0],p->landing_time[1],p->landing_time[2],p->landing_time[3],p->landing_time[4]);
   
}



/*@breif	创造航班信息链表
* @param	无
* @return	航班信息结构体头指针
*/
Plane_information* Create_Plane_List(void)
{
    Plane_information* head,*p1,*p2;
    int n=0;
    int key1;
    int key2;
    int checkstatus;//询问是否要继续录入信息
    head=NULL;
    p1=p2=(Plane_information*)malloc(sizeof(Plane_information));
    printf("请输入：航班号 总座位 剩余座位 票价\n");
    scanf("%s %d %d %d", p1->id, &p1->whole_seat, &p1->rest_seat, &p1->prize);

    printf("请输入起飞时间(年 月 日 时 分):\n");
    scanf("%d %d %d %d %d", &p1->take_off_time[0], &p1->take_off_time[1], 
      &p1->take_off_time[2], &p1->take_off_time[3], &p1->take_off_time[4]);

    printf("请输入着陆时间(年 月 日 时 分):\n");
    scanf("%d %d %d %d %d", &p1->landing_time[0], &p1->landing_time[1], 
    &p1->landing_time[2], &p1->landing_time[3], &p1->landing_time[4]);
    head=p1;

    printf("是否要继续录入航班信息(y/n)\n");
    while(checkstatus==YES)
    {
        
        p2=(Plane_information*)malloc(sizeof(Plane_information));
        p1->next=p2;
        p1=p2;

        printf("请输入：航班号 总座位 剩余座位 票价\n");
        scanf("%s %d %d %d", p2->id, &p2->whole_seat, &p2->rest_seat, &p2->prize);

        printf("请输入起飞时间(年 月 日 时 分):\n");
        scanf("%d %d %d %d %d", &p2->take_off_time[0], &p2->take_off_time[1], 
                &p2->take_off_time[2], &p2->take_off_time[3], &p2->take_off_time[4]);

        printf("请输入着陆时间(年 月 日 时 分):\n");
        scanf("%d %d %d %d %d", &p2->landing_time[0], &p2->landing_time[1], 
                &p2->landing_time[2], &p2->landing_time[3], &p2->landing_time[4]);
        printf("是否要继续录入航班信息(y/n)\n");      
    }   
    printf("退出程序\n");
    p2->next=NULL;
    return head;
}




/*@breif	添加航班信息
* @param	航班信息结构体头指针 
* @return	航班信息结构体头指针
*/
Plane_information* Add_Plane(Plane_information *head)
{
    Plane_information*p1,*p2;
    p1=p2=(Plane_information*)malloc(sizeof(Plane_information));
    printf("请输入：航班号 总座位 剩余座位 票价\n");
    scanf("%s %d %d %d", p1->id, &p1->whole_seat, &p1->rest_seat, &p1->prize);

    printf("请输入起飞时间(年 月 日 时 分): ");
    scanf("%d %d %d %d %d", &p1->take_off_time[0], &p1->take_off_time[1], 
      &p1->take_off_time[2], &p1->take_off_time[3], &p1->take_off_time[4]);

    printf("请输入着陆时间(年 月 日 时 分): ");
    scanf("%d %d %d %d %d", &p1->landing_time[0], &p1->landing_time[1], 
    &p1->landing_time[2], &p1->landing_time[3], &p1->landing_time[4]);
    if(head==NULL)
    {
        head=p1;
        p1->next=NULL;
        return head;
    }
    else
    {
        p2=head;
        while(p2->next!=NULL)
        {
            p2=p2->next;
        }
        p2->next=p1;
        p1->next=NULL;
        return head;
    }

}


/*@breif	删除航班信息
* @param	航班信息结构体头指针
* @param    航班编号
* @return	航班信息结构体头指针
*/
Plane_information* Delete_Plane(HWND hwnd,Plane_information*head)
{
    char id[20] = "";
    GetDlgItemText(hwnd, ID_EDIT_SEARCH_ID, id, 20);
    struct Plane_information*p1=head;
    struct Plane_information*p2=NULL;

    if(head==NULL)
    {
       MessageBox(hwnd, "航班列表为空", "提示", MB_OK);
        return head;
    }

    while(p1->next!=NULL&&strcmp(p1->id,id)!=0)
    {
        p2=p1;
        p1=p1->next;
    }

    if(strcmp(p1->id,id)==0)
    {
        if(p1==head)
        {
            head=p1->next;
            free(p1);
            MessageBox(hwnd, "已删除", "提示", MB_OK);
            return head;
            
        }
        else
        {
            p2->next=p1->next;
            free(p1);
            MessageBox(hwnd, "已删除", "提示", MB_OK);         
            return head;
           
        }
    }
    else
    {
        MessageBox(hwnd, "未查找到相应的航班号", "提示", MB_OK);
        return head;
    }
     
}



/*@breif	修改航班信息
* @param	航班信息结构体头指针
* @param    航班编号
* @return	无
*/
void update_Plane(Plane_information*head)
{   
    Plane_information* p=head;
    char id[20];
    int choice;

    printf("请输入要修改的航班号\n");
    scanf("%s",id);

    if (head == NULL) {
        printf("航班列表为空\n");
        return;
    }
    
    while(p->next!=NULL&&strcmp(p->id,id)!=0)
    {
        p=p->next;
    }

    if(strcmp(p->id,id)==0)//找到了要修改的航班
    {
        while(1)
        {
            printf("请输入你想更改的信息\n");
            printf("0.退出1.飞机编号 2.总座位数 3.剩余座位数 4.起飞时间 5.着陆时间 6.机票价格\n");
            scanf("%d",&choice);
            switch (choice)
            {
                case 0:
                {
                    printf("退出修改\n");
                    return;
                }
                case 1:
                {
                    printf("请输入新的航班号\n");
                    char temp[20];
                    scanf("%s",temp);
                    strcpy(p->id,temp);
                    printf("已把%s的航班号修改为%s\n",id,temp);
                    break;
                }           
                case 2:
                {
                    printf("请输入新的总座位数\n");
                    int temp;
                    scanf("%d",&temp);
                    p->whole_seat=temp;
                    printf("已把%s的总座位数修改为%d\n",id,temp);
                    break;
                }
                case 3:
                {
                    printf("请输入新的剩余座位数\n");
                    int temp;
                    scanf("%d",&temp);
                    p->rest_seat=temp;
                    printf("已把%s的剩余座位数修改为%d\n",id,temp);
                    break;
                }
                case 4:
                {
                    printf("请输入新的起飞时间(年 月 日 时 分)\n");
                    int temp[5];
                    for(int i=0;i<5;i++)
                    {
                        scanf("%d",&temp[i]);
                    }
                    for(int i=0;i<5;i++)
                    {
                        p->take_off_time[i]=temp[i];
                    }
                    printf("已把%s的起飞时间修改为%d-%d-%d %d:%d\n",id,temp[0],temp[1],temp[2],temp[3],temp[4]);
                    break;
                }
                case 5:
                {
                    printf("请输入新的着陆时间(年 月 日 时 分)\n");
                    int temp[5];
                    for(int i=0;i<5;i++)
                    {
                        scanf("%d",&temp[i]);
                    }
                    for(int i=0;i<5;i++)
                    {
                        p->landing_time[i]=temp[i];
                    }
                    printf("已把%s的着陆时间修改为%d-%d-%d %d:%d\n",id,temp[0],temp[1],temp[2],temp[3],temp[4]);
                    break;
                }
                case 6:
                {
                    printf("请输入新的机票价格\n");
                    float temp;
                    scanf("%f",&temp);
                    p->prize=temp;
                    printf("已把%s的机票价格修改为%.2f\n",id,temp);
                    break;
                }
                
                default:
                {
                    printf("输入错误\n");
                    break;
                }
            }
        }
    }
    else
    {
        printf("未查找到相应的航班号\n");
    }
}


/*@breif	根据起飞时间查找航班信息
* @param	航班信息结构体头指针
* @return	找到的航班结构体指针orNULL
*/
struct Plane_information* Find_Plane_Day(Plane_information*head)
{
    Plane_information*p=head;
    int take_off_time[5];
    printf("请输入要查询的航班的起飞时间(年 月 日 时 分): \n");
    scanf("%d %d %d %d %d", &take_off_time[0], &take_off_time[1], 
    &take_off_time[2], &take_off_time[3], &take_off_time[4]);

    while(p->next!=NULL)
    {
        if(memcmp(p->take_off_time,take_off_time,5*sizeof(int))==0)
        {
            printf("已找到相应航班\n");
            return p;
        }
        p=p->next;
    }

    if(memcmp(p->take_off_time,take_off_time,5*sizeof(int))==0)
    {
        printf("已找到相应航班\n");
        return p;
    }
    else
    {
        printf("未找到相应航班\n");
        return NULL;
    }
}



/*@breif	根据ID查找航班
* @param    windows窗口句柄
* @param	航班信息结构体头指针
* @return	找到的航班结构体指针orNULL
*/
struct Plane_information* Find_Plane_ID(HWND hwnd,Plane_information*head)
{
    Plane_information*p=head;
    char id[20] = "";
    GetDlgItemText(hwnd, ID_EDIT_SEARCH_ID, id, 20);

    if(head==NULL)
    {
        MessageBox(hwnd, "航班信息为空", "提示", MB_OK);	
    }

    while(p->next!=NULL)
    {
        if(strcmp(p->id,id)==0)
        {
            MessageBox(hwnd, "已找到相应航班", "提示", MB_OK);	
            return p;
        }
        p=p->next;
    }

    if(strcmp(p->id,id)==0)
    {
        MessageBox(hwnd, "已找到相应航班", "提示", MB_OK);	
        return p;
    }
    else
    {
        MessageBox(hwnd, "未找到相应航班", "提示", MB_OK);	
        return NULL;
    }
}