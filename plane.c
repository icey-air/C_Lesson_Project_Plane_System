#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include <windows.h>
typedef struct Plane_information
{
char id[20];//飞机编号
int whole_seat;//总座位
int rest_seat;
int take_off_time[5];//起飞时间
int landing_time[5];//着陆时间
int prize;//价格
int num;//索引序号

struct Plane_information*next;
}Plane_information;


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
        printf("空");
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


//@return y返回666,n返回999
int quit(void)
{
    char key=0;
    printf("是否要继续录入航班信息(y/n)\n");
    while(1)
    {
        if(_kbhit())
        {
             key=_getch();
        
        if(key=='y')
        {
           return 666;

        }
        else if(key=='n')
        {
            return 999;
        }
        else
        {
            printf("输入错误 请重新输入");
        }
        }
    }


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
    int checkstatus=999;//询问是否要继续录入信息
    head=NULL;
    p1=p2=(Plane_information*)malloc(sizeof(Plane_information));
    printf("请输入：航班号 总座位 剩余座位 票价\n");
    scanf("%s %d %d %d", p1->id, &p1->whole_seat, &p1->rest_seat, &p1->prize);

    printf("请输入起飞时间(年 月 日 时 分): ");
    scanf("%d %d %d %d %d", &p1->take_off_time[0], &p1->take_off_time[1], 
      &p1->take_off_time[2], &p1->take_off_time[3], &p1->take_off_time[4]);

    printf("请输入着陆时间(年 月 日 时 分): ");
    scanf("%d %d %d %d %d", &p1->landing_time[0], &p1->landing_time[1], 
    &p1->landing_time[2], &p1->landing_time[3], &p1->landing_time[4]);
    head=p1;

    while(1)
    {
      key1= quit();
        if(key1==666||key1==999)
        {
            checkstatus=key1;
            break;
        }
        else
        {
            printf("输入错误 请重新输入");
        }
    }
    while(checkstatus==666)
    {
        
        p2=(Plane_information*)malloc(sizeof(Plane_information));
        p1->next=p2;
        p1=p2;

        printf("请输入：航班号 总座位 剩余座位 票价\n");
        scanf("%s %d %d %d", p2->id, &p2->whole_seat, &p2->rest_seat, &p2->prize);

        printf("请输入起飞时间(年 月 日 时 分): ");
        scanf("%d %d %d %d %d", &p2->take_off_time[0], &p2->take_off_time[1], 
                &p2->take_off_time[2], &p2->take_off_time[3], &p2->take_off_time[4]);

        printf("请输入着陆时间(年 月 日 时 分): ");
        scanf("%d %d %d %d %d", &p2->landing_time[0], &p2->landing_time[1], 
                &p2->landing_time[2], &p2->landing_time[3], &p2->landing_time[4]);
        printf("是否要继续录入航班信息(y/n)\n");
        checkstatus=quit();
        
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
Plane_information* Delete_Plane(Plane_information*head,char index[])
{
    Plane_information*p1=head,*p2=NULL;
    while(p1->next!=NULL&&strcmp(p1->id,index)!=0)
    {
        p1=p1->next;
        p2=p1;
    }
    if(p1!=NULL&&strcmp(p1->id,index)==0)
    {
        if(p1==head)
        {
            head=p1->next;
        }
        else
        {
            p2->next=p1->next;
            //还没写释放内存
        }
    }
    else
    {
        printf("未能成功删除相应航班");
    }
    return head;
}


/*@breif	修改航班信息
* @param	航班信息结构体头指针
* @param    航班编号
* @return	无
*/
void update_Plane(Plane_information*head,char index[])
{
    if (head == NULL) {
        printf("航班列表为空\n");
        return;
    }
    int choice;
    Plane_information* p=head;
    
    
        while(p->next!=NULL&&strcmp(p->id,index)!=0)
        {
            p=p->next;
        }
    
    if(p!=NULL)
    {
        printf("请输入你想更改的信息");
        printf("1.飞机编号 2.总座位数 3.剩余座位数 4.起飞时间 5.着陆时间 6.机票价格");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            
            break;
        case 2:{
            int temp;
            scanf("%d",&temp);
            p->whole_seat=temp;
            break;
        }
        case 3:{
            int temp;
            scanf("%d",&temp);
            p->rest_seat=temp;
            break;
        }
        case 4:{
            int temp[5];
            for(int i=0;i<5;i++)
            {
                scanf("%d",&temp[i]);
            }
            for(int i=0;i<5;i++)
            {
                p->take_off_time[i]=temp[i];
            }
            break;
        }
        case 5:{
            int temp[5];
            for(int i=0;i<5;i++)
            {
                scanf("%d",&temp[i]);
            }
            for(int i=0;i<5;i++)
            {
                p->landing_time[i]=temp[i];
            }
            break;
        }
        case 6:{
            float temp;
            scanf("%f",&temp);
            p->prize=temp;
            break;
        }
        
        default:
            printf("输入错误");
            break;
        }
    }
    else
    {
        printf("未查找到相应的航班号");
    }
}


/*@breif	根据起飞时间查找航班信息
* @param	航班信息结构体头指针
* @return	航班信息结构体指针
*/
struct Plane_information* Find_Plane_Day(Plane_information*head)
{
    Plane_information*p=head;
    int take_off_time[5];

    printf("请输入起飞时间(年 月 日 时 分): ");
    scanf("%d %d %d %d %d", &take_off_time[0], &take_off_time[1], 
    &take_off_time[2], &take_off_time[3], &take_off_time[4]);

    while(p->next!=NULL)
    {
        if(memcmp(p->take_off_time,take_off_time,5*sizeof(int))==0)
        {
            printf("已找到相应航班");
            return p;
        }
        p=p->next;
    }

    if(memcmp(p->take_off_time,take_off_time,5*sizeof(int))==0)
    {
        printf("已找到相应航班");
        return p;
    }
    else
    {
        printf("未找到相应航班");
        return NULL;
    }
}
