#include "Ticket.h"
#include <stdio.h>

/*@breif    预定机票
* @param	当前窗口句柄
* @param	当前账户结构体地址
* @param	航班信息结构体头指针
* @return	无
*/         
void Book_Ticket(HWND hwnd,struct tourist*Now_Account,struct Plane_information*head)//我要把找对应日期改为找id了
{
    struct Plane_information* Book_Plane;
    struct Ticket *Ticket1;
    Ticket1=(struct Ticket*)malloc(Ticket_LEN);

    Book_Plane=Find_Plane_ID(hwnd,head);
    if(Book_Plane!=NULL)//重复订购同一飞机的飞机票代码没写，这样的更改要等同行乘客的代码编写完毕才方便修改
    {  
        if(MessageBox(hwnd, "是否要预定id为航班的机票", "确认", MB_YESNO) == IDYES)//需要缓冲区字符串
        {

            Add_Ticket(hwnd, Now_Account, Book_Plane);
            Now_Account->Airfare_Cost+=Book_Plane->prize;//价格在这加的
            MessageBox(hwnd, "已预定id为:的航班", "提示", MB_OK);
            printf("已预定航班%s的机票\n",Book_Plane->id);
        }      
    }
     RefreshPlaneList(hwnd);
}

/*@breif    取消预定机票
* @param	当前账户结构体地址
* @return	无
*///要先做List函数
void Cancel_Ticket_Reservation(HWND hwnd,struct tourist*Now_Account)
{
    
    Ticket*Ticket_Delete=Now_Account->Ticket_List;
    Ticket*Ticket_Forward=NULL;

    char id[20]="";
    GetDlgItemText(hwnd, ID_EDIT_SEARCH_ID, id, 20);

    if(Ticket_Delete==NULL)
    {
        MessageBox(hwnd, "您还没有预定机票", "提示", MB_OK);
        return;
    }

    while(Ticket_Delete->next!=NULL&&strcmp(Ticket_Delete->Plane_Ticket->id,id)!=0)
    {
        Ticket_Forward=Ticket_Delete;
        Ticket_Delete=Ticket_Delete->next;
    }

    if(strcmp(Ticket_Delete->Plane_Ticket->id,id)==0)
    {
        if(MessageBox(hwnd, "是否要取消预定id为航班的机票呢", "确认", MB_YESNO) == IDYES)
        {   

            if(Ticket_Delete==Now_Account->Ticket_List)//如果要删的是头指针
            {   
                Now_Account->Ticket_List=Now_Account->Ticket_List->next;
                Now_Account->Airfare_Cost-=Ticket_Delete->Plane_Ticket->prize;//减去票里面的飞机的价格
                free(Ticket_Delete);
            }
            else//否则是中间
            {
                Ticket_Forward->next=Ticket_Delete->next;
                Now_Account->Airfare_Cost-=Ticket_Delete->Plane_Ticket->prize;//减去票里面的飞机的价格
                free(Ticket_Delete);
            }
            MessageBox(hwnd, "已取消预定", "提示", MB_OK);

        }
        else
        {
            MessageBox(hwnd, "未取消预定", "提示", MB_OK);
        }
    }
    else
    {
        MessageBox(hwnd, "未找到预定的航班", "提示", MB_OK);
    }


}

/*@breif    查找并例出已预定的机票
* @param	windows窗口句柄
* @param    当前账户结构体地址
* @return	无
*/
void List_Ticket_Reservation(HWND hwnd,struct tourist*Now_Account)
{
    HWND hList = GetDlgItem(hwnd, ID_STATIC_INFO);

    Ticket*Ticket_List=Now_Account->Ticket_List;
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    if(Ticket_List==NULL)
    {
        char info[500];
        sprintf(info,"您当前没有预约任何航班。");
        SendMessage(hList, LB_ADDSTRING , 0, (LPARAM)info);
        return;
    }

    else//没有完善
    {   
        while(Ticket_List!=NULL)//由于都是在一个地方显示，所以会覆盖
        {
            char info[250];

        sprintf(info, "id: %s,￥%.0f,起点:%s 终点:%s",
                Ticket_List->Plane_Ticket->id,Ticket_List->Plane_Ticket->prize,Ticket_List->Plane_Ticket->starting_point,Ticket_List->Plane_Ticket->destination);
     
               SendMessage(hList, LB_ADDSTRING , 0, (LPARAM)info);



        sprintf(info, "起飞时间: %d/%d/%d %02d:%02d 着陆时间: %d/%d/%d %02d:%02d",
                Ticket_List->Plane_Ticket->take_off_time[0], Ticket_List->Plane_Ticket->take_off_time[1], Ticket_List->Plane_Ticket->take_off_time[2],
                Ticket_List->Plane_Ticket->take_off_time[3], Ticket_List->Plane_Ticket->take_off_time[4],
                Ticket_List->Plane_Ticket->landing_time[0], Ticket_List->Plane_Ticket->landing_time[1], Ticket_List->Plane_Ticket->landing_time[2],
                Ticket_List->Plane_Ticket->landing_time[3], Ticket_List->Plane_Ticket->landing_time[4]
            );
              SendMessage(hList, LB_ADDSTRING , 0, (LPARAM)info);

        sprintf(info,"");
        SendMessage(hList, LB_ADDSTRING , 0, (LPARAM)info);
        Ticket_List=Ticket_List->next;
        }
    }
}


/*@breif    添加预定机票到用户账户
* @param    当前窗口句柄
* @param	当前账户结构体地址
* @param	要预定的航班结构体指针
* @return	无
*/
void Add_Ticket(HWND hwnd,struct tourist*Now_Account,Plane_information*Book_Plane)
{
    struct Ticket *Ticket1;
    Ticket1=(struct Ticket*)malloc(Ticket_LEN);

    if(Now_Account->Ticket_List==NULL)//第一次预定机票
    {
        Now_Account->Ticket_List=Ticket1;
        Now_Account->Ticket_List->Plane_Ticket=Book_Plane;
        Now_Account->Ticket_List->next=NULL;
        return;
    }
    else
    {
        struct Ticket *p1;
        p1=Now_Account->Ticket_List;
        while(p1->next!=NULL)
        {
           if(Find_Ticket(Now_Account,Book_Plane)!=NULL)
            {
                MessageBox(hwnd, "您已预定过该航班的机票", "提示", MB_OK);
                return;
            }
            p1=p1->next;
        }

        if(Find_Ticket(Now_Account,Book_Plane)!=NULL)
            {
                MessageBox(hwnd, "您已预定过该航班的机票", "提示", MB_OK);
                return;
            }
        
        
        Ticket1->Plane_Ticket=Book_Plane;
        Ticket1->next=NULL;
        p1->next=Ticket1;
        MessageBox(hwnd, "已添加预定", "提示", MB_OK);
        return;
    }
   
}



/*@breif    添加预定机票到用户账户
* @param    当前账户结构体地址
* @param	要查找的飞机结构体指针
* @return	找到的机票结构体指针orNULL
*/
struct Ticket* Find_Ticket(struct tourist*Now_Account,Plane_information*Book_Plane)
{
    char id[20]="";
    strcpy(id,Book_Plane->id);

    struct Ticket *p1;
    p1=Now_Account->Ticket_List;

    if(p1==NULL)
    {
        return NULL;
    }

    while(p1->next!=NULL)
    {
        if(strcmp(p1->Plane_Ticket->id,id)==0)
        {
            return p1;
        }
        p1=p1->next;
    }

    if(strcmp(p1->Plane_Ticket->id,id)==0)
    {
        return p1;
    }
    else
    {
        return NULL;
    }
}   