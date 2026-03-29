 #include "windows_Define.h"
HBITMAP g_hBmp=NULL;
HWND g_hPic=NULL;
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
        if(hChild!=g_hPic)
        {
        DestroyWindow(hChild);
        }
        hChild = hNext;
    }
    Show_Background(hwnd);
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
    CreateWindow("STATIC", "航班号:", WS_CHILD | WS_VISIBLE,
                 460, 20, 50, 25, hwnd, NULL, NULL, NULL);

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
    int label_width = 80;
    int y=400;

    // 清除所有现有控件
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while(hChild != NULL)
    {
        HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
        if(hChild!=g_hPic)
        {
        DestroyWindow(hChild);
        }
        hChild = hNext;
    }
    Show_Background(hwnd);   
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

    CreateWindow("BUTTON", "修改信息", WS_CHILD | WS_VISIBLE,
                 570, 20, 80, 25, hwnd, (HMENU)ID_BUTTON_CHANGE_INFO, NULL, NULL);
    
    CreateWindow("BUTTON", "退出登录", WS_CHILD | WS_VISIBLE,
                 760, 20, 100, 30, hwnd, (HMENU)ID_BUTTON_LOGOUT, NULL, NULL);

    CreateWindow("BUTTON", "添加同行乘客", WS_CHILD | WS_VISIBLE,
                 20, 280, 100, 30, hwnd, (HMENU)ID_BUTTON_ADD_PASSENGERS, NULL, NULL);
    
    // 创建列表框显示所有航班
    CreateWindow("LISTBOX", NULL,
                 WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                 20, 60, 450, 200, hwnd, (HMENU)ID_LIST_PLANE, NULL, NULL);
    
    // 创建静态文本框显示预定信息
    CreateWindow("STATIC", "我的预定信息:", WS_CHILD | WS_VISIBLE,
                 500, 60, 100, 20, hwnd, NULL, NULL, NULL);

    // 创建列表框显示预定信息
    CreateWindow("LISTBOX", NULL,
                 WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                 500, 80, 360, 470, hwnd, (HMENU)ID_STATIC_INFO, NULL, NULL);

    // 筛选航班按钮，放在起飞时间控件上方
    CreateWindow("BUTTON", "筛选航班", WS_CHILD | WS_VISIBLE,
                 20, 360, 80, 25, hwnd, (HMENU)ID_BUTTON_FILTER_PLANE, NULL, NULL);

    // CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
    //              500, 90, 260, 350, hwnd, (HMENU)ID_STATIC_INFO, NULL, NULL);
    //请问这个代码是干什么的，遮挡到User的预定了 

 
    CreateWindow("STATIC", "起点:", WS_CHILD | WS_VISIBLE,
                 20, 475, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 70, 475, 50, 20, hwnd, (HMENU)ID_EDIT_SEARCH_STARTING_POINT, NULL, NULL);


    CreateWindow("STATIC", "终点:", WS_CHILD | WS_VISIBLE,
                 20, 500, 50, 25, hwnd, NULL, NULL, NULL);
    
     CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 70, 500, 50, 20, hwnd, (HMENU)ID_EDIT_SEARCH_DESTINATION, NULL, NULL);
    
    
       // 起飞时间
    CreateWindow("STATIC", "起飞时间:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hwnd, NULL, NULL, NULL);
    
    // 起飞时间输入框（一行显示）
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 45, 20, hwnd, (HMENU)ID_EDIT_TAKEOFF_YEAR, NULL, NULL);
    CreateWindow("STATIC", "年", WS_CHILD | WS_VISIBLE,
                 160, y, 20, 20, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 180, y, 35, 20, hwnd, (HMENU)ID_EDIT_TAKEOFF_MONTH, NULL, NULL);
    CreateWindow("STATIC", "月", WS_CHILD | WS_VISIBLE,
                 220, y, 20, 20, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 240, y, 35, 20, hwnd, (HMENU)ID_EDIT_TAKEOFF_DAY, NULL, NULL);
    CreateWindow("STATIC", "日", WS_CHILD | WS_VISIBLE,
                 280, y, 20, 20, hwnd, NULL, NULL, NULL);
    // 显示所有航班
    RefreshPlaneList(hwnd);
}




/*@brief	刷新飞机显示
* @param	windows句柄
* @return	无
*/
void RefreshPlaneList(HWND hwnd)
{
     //GetDLgItem获取列表框的句柄,为了后面用SendMessage发送信息时知道发给谁
    HWND hList = GetDlgItem(hwnd, ID_LIST_PLANE);
    if(hList == NULL) return;
    
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    
    if(g_head == NULL)
    {
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"当前没有航班信息");
        return;
    }
    
    Plane_information* p = g_head;
    char buffer[300];
    int index = 1;
    
    while(p != NULL)
    {
        sprintf(buffer, "%d. %s 总:%d 剩余:%d ￥%.0f 起点:%s 终点:%s",
                index++, p->id, p->whole_seat, p->rest_seat, p->prize,
                p->starting_point,p->destination);
        //LB_ADDStRING(ListBroad_addstring)向列表文本框添加个字符串，这里用缓冲区发过去 
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);// 


        sprintf(buffer,"起飞时间:%d/%d/%d %02d:%02d 到达时间:%d/%d/%d %02d:%02d", 
                p->take_off_time[0], p->take_off_time[1], p->take_off_time[2],
                p->take_off_time[3], p->take_off_time[4],
                p->landing_time[0], p->landing_time[1], p->landing_time[2],
                p->landing_time[3], p->landing_time[4]);
                
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);

        sprintf(buffer,"");
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);
        
        p = p->next;
    }
    {


    }
}




/*@brief	展示注册窗口
* @param	windows句柄
* @return	无
*/
void Show_Rejister_Window(HWND hwnd)
{
    // 清除所有现有控件
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while(hChild != NULL)
    {
        HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
        if(hChild!=g_hPic)
        {
        DestroyWindow(hChild);
        }
        hChild = hNext;
    }
    Show_Background(hwnd);
    // 创建注册界面控件
    CreateWindow("STATIC", "账户:", WS_CHILD | WS_VISIBLE,
                 300, 200, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 360, 200, 150, 25, hwnd, (HMENU)ID_EDIT_ACCOUNT, NULL, NULL);
    
    CreateWindow("STATIC", "密码:", WS_CHILD | WS_VISIBLE,
                 300, 240, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD,
                 360, 240, 150, 25, hwnd, (HMENU)ID_EDIT_PASSWORD, NULL, NULL);
    
    CreateWindow("STATIC", "再次输入:", WS_CHILD | WS_VISIBLE,
                 300, 280, 70, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 280, 150, 25, hwnd, (HMENU)ID_EDIT_PASSWORD_2, NULL, NULL);

    CreateWindow("STATIC", "电话:", WS_CHILD | WS_VISIBLE,
                 300, 320, 50, 25, hwnd, NULL, NULL, NULL);

     CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER|ES_NUMBER,
                  360, 320, 150, 25, hwnd, (HMENU)ID_EDIT_PHONE, NULL, NULL);

    CreateWindow("STATIC", "姓名:", WS_CHILD | WS_VISIBLE,
                 300, 360, 50, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 360, 150, 25, hwnd, (HMENU)ID_EDIT_NAME, NULL, NULL);
    
    CreateWindow("STATIC", "身份证:", WS_CHILD | WS_VISIBLE,
                 300, 390, 50, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 390, 150, 25, hwnd, (HMENU)ID_EDIT_IDENTIEY_CARD, NULL, NULL);


    CreateWindow("BUTTON", "确认注册", WS_CHILD | WS_VISIBLE,
                 360, 420, 80, 30, hwnd, (HMENU)ID_BUTTON_REGISTER_COMFIRM, NULL, NULL);

    CreateWindow("BUTTON", "取消注册", WS_CHILD | WS_VISIBLE,
                 360, 460, 80, 30, hwnd, (HMENU)ID_BUTTON_REGISTER_CANCLE, NULL, NULL);

}


/*@brief	展示账户信息修改窗口
* @param	windows句柄
* @return	无
*/
void Show_Account_Information_Change_Window(HWND hwnd)
{
    // 清除所有现有控件
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while(hChild != NULL)
    {
        HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
        if(hChild!=g_hPic)
        {
        DestroyWindow(hChild);
        }
        hChild = hNext;
    }
    Show_Background(hwnd);
    // 创建注册界面控件
    CreateWindow("STATIC", "账户:", WS_CHILD | WS_VISIBLE,
                 300, 200, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("STATIC", Now_Account->Account, WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 200, 150, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("BUTTON", "修改", WS_CHILD | WS_VISIBLE,
                 520, 200, 80, 30, hwnd, (HMENU)ID_BUTTON_CHANGE_Account, NULL, NULL);

    
    CreateWindow("STATIC", "密码:", WS_CHILD | WS_VISIBLE,
                 300, 240, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("STATIC", (Now_Account->password), WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 240, 150, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("BUTTON", "修改", WS_CHILD | WS_VISIBLE,
                 520, 240, 80, 30, hwnd, (HMENU)ID_BUTTON_CHANGE_Password, NULL, NULL);
    
    CreateWindow("STATIC", "电话:", WS_CHILD | WS_VISIBLE,
                 300, 280, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("STATIC", Now_Account->phone_number, WS_CHILD | WS_VISIBLE | WS_BORDER|ES_NUMBER,
                  360, 280, 150, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("BUTTON", "修改", WS_CHILD | WS_VISIBLE,
                 520, 280, 80, 30, hwnd, (HMENU)ID_BUTTON_CHANGE_Phone, NULL, NULL);

    CreateWindow("STATIC", "姓名:", WS_CHILD | WS_VISIBLE,
                 300, 320, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("STATIC", Now_Account->name, WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 320, 150, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("STATIC", "身份证:", WS_CHILD | WS_VISIBLE,
                 300, 360, 50, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("STATIC", Now_Account->identity_card, WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 360, 150, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("BUTTON", "确认修改", WS_CHILD | WS_VISIBLE,
                 360, 400, 80, 30, hwnd, (HMENU)ID_BUTTON_CHANGE_INFO_COMFIRM, NULL, NULL);

    CreateWindow("BUTTON", "退出", WS_CHILD | WS_VISIBLE,
                 670, 55, 80, 30, hwnd, (HMENU)ID_BUTTON_CHANGE_INFO_CANCLE, NULL, NULL);

}



/*@brief	展现注册窗口
* @param	windows句柄
* @return	无
*/
void ShowLoginWindow(HWND hwnd)
{
    // 清除所有现有控件
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while(hChild != NULL)
    {
        HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
        if(hChild!=g_hPic)
        {
            DestroyWindow(hChild);
        }
        hChild = hNext;
    }
    Show_Background(hwnd);
    // 创建登录界面控件
    CreateWindow("STATIC", "用户名:", WS_CHILD | WS_VISIBLE,
                 300, 200, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 360, 200, 150, 25, hwnd, (HMENU)ID_EDIT_ACCOUNT, NULL, NULL);
    
    CreateWindow("STATIC", "密码:", WS_CHILD | WS_VISIBLE,
                 300, 240, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD,
                 360, 240, 150, 25, hwnd, (HMENU)ID_EDIT_PASSWORD, NULL, NULL);
    
    CreateWindow("BUTTON", "管理员登录", WS_CHILD | WS_VISIBLE,
                 300, 280, 100, 30, hwnd, (HMENU)ID_BUTTON_ADMIN_LOGIN, NULL, NULL);
    
    CreateWindow("BUTTON", "用户登录", WS_CHILD | WS_VISIBLE,
                 410, 280, 100, 30, hwnd, (HMENU)ID_BUTTON_USER_LOGIN, NULL, NULL);
    
    CreateWindow("BUTTON", "设置", WS_CHILD | WS_VISIBLE,
                 360, 400, 80, 30, hwnd, (HMENU)ID_BUTTON_SETTING, NULL, NULL);
        
    CreateWindow("BUTTON", "注册", WS_CHILD | WS_VISIBLE,
                 360, 330, 80, 30, hwnd, (HMENU)ID_BUTTON_REGISTER, NULL, NULL);
}

//@brief 显示添加同行乘客窗口
//@param 窗口句柄(其实就是handle windows的简称)
//@return 无
void Add_New_Passengers_Window(HWND hwnd)
{
    // 清除所有现有控件
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while(hChild != NULL)
    {
        HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
        if(hChild!=g_hPic)
        {
            DestroyWindow(hChild);
        }
        hChild = hNext;
    }
    
    Show_Background(hwnd);

    CreateWindow("STATIC", "电话:", WS_CHILD | WS_VISIBLE,
                 300, 280, 50, 25, hwnd, NULL, NULL, NULL);

     CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 280, 150, 25, hwnd, (HMENU)ID_EDIT_PHONE, NULL, NULL);

    CreateWindow("STATIC", "姓名:", WS_CHILD | WS_VISIBLE,
                 300, 320, 50, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 320, 150, 25, hwnd, (HMENU)ID_EDIT_NAME, NULL, NULL);
    
    CreateWindow("STATIC", "身份证:", WS_CHILD | WS_VISIBLE,
                 300, 360, 50, 25, hwnd, NULL, NULL, NULL);

    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                  360, 360, 150, 25, hwnd, (HMENU)ID_EDIT_IDENTIEY_CARD, NULL, NULL);

    CreateWindow("BUTTON", "确认添加", WS_CHILD | WS_VISIBLE,
                 360, 400, 80, 30, hwnd, (HMENU)ID_BUTTON_ADD_CONFIRM, NULL, NULL);

    CreateWindow("BUTTON", "取消添加", WS_CHILD | WS_VISIBLE,
                 360, 440, 80, 30, hwnd, (HMENU)ID_BUTTON_ADD_CANCLE, NULL, NULL);

    CreateWindow("BUTTON", "退出", WS_CHILD | WS_VISIBLE,
                 670, 55, 80, 30, hwnd, (HMENU)ID_BUTTON_ADD_CANCLE, NULL, NULL);


}

//@brief 显示背景
//@param 窗口句柄(其实就是handle windows的简称)
//@return 无
void Show_Background(HWND hwnd)
{   
    //只加载一次位图，免得多次加载还要去除放泄漏，代码麻烦
    if(g_hBmp==NULL)
    {
        //hBmp接受LoadImage返回值(加载失败应该就是NULL)(应该是个整数int,然后转成hbmp的类型了)
        g_hBmp = (HBITMAP)LoadImage(NULL, "C:\\Users\\windows\\Desktop\\STMproject\\c\\project1\\Picture\\Plane_BackGround.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        //hBmp handle.bmp图片的句柄
        //检查能否成功加载
        if(g_hBmp==NULL)
        {
            MessageBox(hwnd,"加载背景失败","Error",MB_OK);
        }
    }
    if(g_hPic==NULL)
    {
        //WS(Windows)_CHILD(孩子，即子窗口),WS_VISIBLE(显示可见),SS(Static Style)静态控件_BITMAP(.bmp图片)
        g_hPic = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP,0, 0, 900, 600, hwnd, NULL, NULL, NULL);
        //hPic变量是专门接受图片的窗口句柄
       //HWND_BOTTOM(窗口_底部),SWP(Set Windows Position),这里的意思就是不改变一开始加载图片的位置大小
        SetWindowPos(g_hPic, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    }

    //SendMessage下次有空再研究
    SendMessage(g_hPic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hBmp);
        
}