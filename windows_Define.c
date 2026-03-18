 #include "windows_Define.h"

/** 
* @brief	显示管理员界面
* @param	windows句柄
* @return	无
*/
void ShowAdminWindow(HWND hwnd)
{
    // 清除所有现有控件
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while(hChild != NULL)
    {
        HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
        DestroyWindow(hChild);
        hChild = hNext;
    }
    
    // 创建管理员界面控件
    CreateWindow("BUTTON", "添加航班", WS_CHILD | WS_VISIBLE,
                 20, 20, 100, 30, hwnd, (HMENU)ID_BUTTON_ADD_PLANE, NULL, NULL);
    
    CreateWindow("BUTTON", "删除航班", WS_CHILD | WS_VISIBLE,
                 130, 20, 100, 30, hwnd, (HMENU)ID_BUTTON_DELETE_PLANE, NULL, NULL);
    
    CreateWindow("BUTTON", "修改航班", WS_CHILD | WS_VISIBLE,
                 240, 20, 100, 30, hwnd, (HMENU)ID_BUTTON_UPDATE_PLANE, NULL, NULL);
    
    CreateWindow("BUTTON", "显示所有", WS_CHILD | WS_VISIBLE,
                 350, 20, 100, 30, hwnd, (HMENU)ID_BUTTON_SHOW_PLANE, NULL, NULL);
    
    CreateWindow("BUTTON", "退出登录", WS_CHILD | WS_VISIBLE,
                 650, 20, 100, 30, hwnd, (HMENU)ID_BUTTON_LOGOUT, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 460, 20, 100, 30, hwnd, (HMENU)ID_EDIT_SEARCH_ID, NULL, NULL);


    // 创建列表框显示航班信息
    CreateWindow("LISTBOX", NULL,
                 WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                 20, 70, 740, 450, hwnd, (HMENU)ID_LIST_PLANE, NULL, NULL);



    // 显示当前航班列表
    RefreshPlaneList(hwnd);
}



/** 
* @brief	显示用户界面
* @param	windows句柄
* @return	无
*/
void ShowUserWindow(HWND hwnd)
{
    // 清除所有现有控件
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while(hChild != NULL)
    {
        HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
        DestroyWindow(hChild);
        hChild = hNext;
    }
    
    // 创建用户界面控件
    CreateWindow("STATIC", "航班号:", WS_CHILD | WS_VISIBLE,
                 20, 20, 50, 25, hwnd, NULL, NULL, NULL);
    //输入类
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 80, 20, 120, 25, hwnd, (HMENU)ID_EDIT_SEARCH_ID, NULL, NULL);
    
    CreateWindow("BUTTON", "查询航班", WS_CHILD | WS_VISIBLE,
                 210, 20, 80, 25, hwnd, (HMENU)ID_BUTTON_SEARCH_PLANE, NULL, NULL);
    
    CreateWindow("BUTTON", "预定机票", WS_CHILD | WS_VISIBLE,
                 300, 20, 80, 25, hwnd, (HMENU)ID_BUTTON_BOOK_TICKET, NULL, NULL);
    
    CreateWindow("BUTTON", "取消预定", WS_CHILD | WS_VISIBLE,
                 390, 20, 80, 25, hwnd, (HMENU)ID_BUTTON_CANCEL_BOOK, NULL, NULL);
    
    CreateWindow("BUTTON", "我的预定", WS_CHILD | WS_VISIBLE,
                 480, 20, 80, 25, hwnd, (HMENU)ID_BUTTON_LIST_BOOK, NULL, NULL);
    
    CreateWindow("BUTTON", "退出登录", WS_CHILD | WS_VISIBLE,
                 650, 20, 100, 30, hwnd, (HMENU)ID_BUTTON_LOGOUT, NULL, NULL);
    
    // 创建列表框显示所有航班
    CreateWindow("LISTBOX", NULL,
                 WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                 20, 60, 450, 200, hwnd, (HMENU)ID_LIST_PLANE, NULL, NULL);
    
    // 创建静态文本框显示预定信息
    CreateWindow("STATIC", "我的预定信息:", WS_CHILD | WS_VISIBLE,
                 500, 60, 100, 20, hwnd, NULL, NULL, NULL);
    
    CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 500, 200, 260, 170, hwnd, (HMENU)ID_STATIC_INFO_1, NULL, NULL);

    CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 500, 90, 260, 350, hwnd, (HMENU)ID_STATIC_INFO, NULL, NULL);
                 
 




    // 显示所有航班
    RefreshPlaneList(hwnd);
}




/**
 * @brief 刷新航班列表显示
 */
void RefreshPlaneList(HWND hwnd)
{
    HWND hList = GetDlgItem(hwnd, ID_LIST_PLANE);
    if(hList == NULL) return;
    
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    
    if(g_head == NULL)
    {
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"当前没有航班信息");
        return;
    }
    
    Plane_information* p = g_head;
    char buffer[200];
    int index = 1;
    
    while(p != NULL)
    {
        sprintf(buffer, "%d. %s 总:%d 剩余:%d ￥%.0f  %d/%d/%d %02d:%02d",
                index++, p->id, p->whole_seat, p->rest_seat, p->prize,
                p->take_off_time[0], p->take_off_time[1], p->take_off_time[2],
                p->take_off_time[3], p->take_off_time[4]);
        
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);// 添加航班信息到列表框
        p = p->next;
    }
}
