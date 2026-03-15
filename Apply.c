#include "Apply.h"
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
    Book_Plane=Find_Plane_ID(hwnd,head);
    if(Book_Plane!=NULL)
    {  
        if(MessageBox(hwnd, "是否要预定id为航班的机票", "确认", MB_YESNO) == IDYES)//需要缓冲区字符串
        {
            Now_Account->plane=Book_Plane;
            MessageBox(hwnd, "已预定id为:的航班", "提示", MB_OK);
            printf("已预定航班%s的机票\n",Book_Plane->id);
        }
        else if(MessageBox(hwnd, "是否要预定id为航班的机票", "确认", MB_YESNO) == IDNO)
        {
            MessageBox(hwnd, "未预定id为航班的机票", "提示", MB_OK);
        }        
    }

    else
    {
        MessageBox(hwnd, "未找到id为航班的机票", "提示", MB_OK);
    }
     RefreshPlaneList(hwnd);
}

/*@breif    取消预定机票
* @param	当前账户结构体地址
* @return	无
*/
void Cancel_Ticket_Reservation(struct tourist*Now_Account)
{
    printf("正在为您查询已预定的机票");
    List_Ticket_Reservation(Now_Account);
    printf("是否要取消预定的机票(y/n)\n");
    char key;
    while(1)
    {
        scanf("%c",&key);
        if(key=='y')
        {
            Now_Account->plane=NULL;
            printf("已取消预定的机票\n");
            break;
        }
        else if(key=='n')
        {
            printf("未取消预定的机票\n");
            break;
        }
        else
        {
            printf("输入错误，请重新输入(y/n)\n");
        }
    }
}

/*@breif    查找并例出已预定的机票
* @param	当前账户结构体地址
* @return	无
*/
void List_Ticket_Reservation(struct tourist*Now_Account)
{
    if(Now_Account->plane!=NULL)
    {
        printf("您已预定的机票信息如下：\n");
        printf("航班号：%s\n",Now_Account->plane->id);
        printf("起飞时间：%d-%d-%d %d:%d\n",Now_Account->plane->take_off_time[0],Now_Account->plane->take_off_time[1],Now_Account->plane->take_off_time[2],Now_Account->plane->take_off_time[3],Now_Account->plane->take_off_time[4]);
        printf("着陆时间：%d-%d-%d %d:%d\n",Now_Account->plane->landing_time[0],Now_Account->plane->landing_time[1],Now_Account->plane->landing_time[2],Now_Account->plane->landing_time[3],Now_Account->plane->landing_time[4]);
        printf("价格：%d\n",Now_Account->plane->prize);
    }
    else
    {
        printf("您没有预定任何机票\n");
    }
}
