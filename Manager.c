#include "Manager.h"

/*@brief	管理员登录
* @param	windows句柄
* @return	无
*/
// 添加这行 - 声明外部变量
extern int g_planeCount;
extern Plane_information* g_head;

void Manager_Login(HWND hwnd)
{
    char username[20], password[20];
    GetDlgItemText(hwnd, ID_EDIT_ACCOUNT, username, 20);
    GetDlgItemText(hwnd, ID_EDIT_PASSWORD, password, 20);
    
    if(strcmp(username, MANAGER_ACCOUNT) == 0 && strcmp(password, MANAGER_PASSWORD) == 0)
    { 
        ShowAdminWindow(hwnd);
    }
    else
    {
        MessageBox(hwnd, "管理员登录失败", "提示", MB_OK);
    }
}


Plane_information* Manager_Delete_Plane(HWND hwnd,Plane_information*head)//多次一举的函数，不过相比直接用Delete_Plane函数，这个函数多了全局头指针的传参和刷新界面
{
    head=Delete_Plane(hwnd,head);
    g_head=head;//更新全局头指针,不然删除了但是全局头指针没变，刷新界面还是会显示被删除的航班，同时这行代码可以减少RefreshPlane的传参
    //这么一想，如果有地方需要刷新都得多写这一行代码，感觉不是很好
    //或者呢，下方多传一个参数      ---现在回头看这个觉得这样写勉强还可以接受
    RefreshPlaneList(hwnd);
    return head;
}

/**
 * @brief 显示添加航班对话框


void ShowAddPlaneDialog(HWND hwnd)
{
    // 简化版：使用DialogBox，这里用输入框演示
    char id[20] = "", whole_seat[10] = "", rest_seat[10] = "", prize[10] = "";
    char takeoff[50] = "", landing[50] = "";
    
    // 在实际应用中，这里应该创建一个对话框
    // 为简化，我们使用一个输入对话框
    id[0] = '\0';
    if(InputBox(hwnd, "请输入航班号:", id, 20))
    {
        // 这里简化处理，实际应该获取所有信息
        int w_seat = 200, r_seat = 200;
        float pr = 800.0;
        int takeoff_time[5] = {2024, 3, 15, 8, 0};
        int landing_time[5] = {2024, 3, 15, 10, 30};
        
      
        RefreshPlaneList(hwnd);
    }
    else//这里做了一个输入失败的改动
        //即没有输入信息就结束或输入不正确
        //暂时还没想到其它bug
    {
        MessageBox(hwnd,"没有输入，请重新添加","提示",MB_OK);

    }
}
*/
// 简单的输入框函数
BOOL InputBox(HWND hwnd, char* prompt, char* result, int max_len)
{
    //这里打算再写一个bool类型函数判断输入 这样方便后续tourist也一起改动
    /*if(){

        return FALSE;
    }*/
    MessageBox(hwnd, "在实际应用中，这里会弹出输入对话框", "提示", MB_OK);
    strcpy(result, "CA1003");
    return TRUE;
}

/**
 * @brief 判断输入是否全输入完成或输入不正确
 */
BOOL InputError(HWND hwnd, char* prompt, char* result, int max_len)
{
    
}

/**
 * @brief 显示修改航班对话框
 */
void ShowUpdatePlaneDialog(HWND hwnd)
{
    char id[20] = "";
    if(InputBox(hwnd, "请输入要修改的航班号:", id, 20))
    {
        // 简化处理
      
        RefreshPlaneList(hwnd);
    }
}


/////白轩宇的添加/////
// 在 Manager.c 中添加以下代码

/* 添加航班对话框的窗口过程函数 */
LRESULT CALLBACK AddPlaneDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            // 设置默认值（可选）
            SetDlgItemText(hDlg, ID_EDIT_TAKEOFF_YEAR, "2024");
            SetDlgItemText(hDlg, ID_EDIT_TAKEOFF_MONTH, "1");
            SetDlgItemText(hDlg, ID_EDIT_TAKEOFF_DAY, "1");
            SetDlgItemText(hDlg, ID_EDIT_TAKEOFF_HOUR, "0");
            SetDlgItemText(hDlg, ID_EDIT_TAKEOFF_MINUTE, "0");
            
            SetDlgItemText(hDlg, ID_EDIT_LANDING_YEAR, "2024");
            SetDlgItemText(hDlg, ID_EDIT_LANDING_MONTH, "1");
            SetDlgItemText(hDlg, ID_EDIT_LANDING_DAY, "1");
            SetDlgItemText(hDlg, ID_EDIT_LANDING_HOUR, "2");
            SetDlgItemText(hDlg, ID_EDIT_LANDING_MINUTE, "0");
            
            SetDlgItemText(hDlg, ID_EDIT_WHOLE_SEAT_ADD, "200");
            SetDlgItemText(hDlg, ID_EDIT_REST_SEAT_ADD, "200");
            SetDlgItemText(hDlg, ID_EDIT_PRIZE_ADD, "800");
            SetDlgItemText(hDlg, ID_EDIT_DEPARTURE_ADD, "北京");
            SetDlgItemText(hDlg, ID_EDIT_DESTINATION_ADD, "上海");
            
            return TRUE;
        }
        
       case WM_COMMAND:
        {
           int wmId = LOWORD(wParam);
    
          if (wmId == ID_BUTTON_CONFIRM_ADD_PLANE)  // 输入完成按钮
       {
        // 获取输入的所有数据
        char id[20], whole_seat[10], rest_seat[10], prize[10];
        char takeoff_year[5], takeoff_month[3], takeoff_day[3], takeoff_hour[3], takeoff_minute[3];
        char landing_year[5], landing_month[3], landing_day[3], landing_hour[3], landing_minute[3];
        char departure[20], destination[20];
        
        GetDlgItemText(hDlg, ID_EDIT_PLANE_ID_ADD, id, 20);
        GetDlgItemText(hDlg, ID_EDIT_WHOLE_SEAT_ADD, whole_seat, 10);
        GetDlgItemText(hDlg, ID_EDIT_REST_SEAT_ADD, rest_seat, 10);
        GetDlgItemText(hDlg, ID_EDIT_PRIZE_ADD, prize, 10);
        GetDlgItemText(hDlg, ID_EDIT_DEPARTURE_ADD, departure, 20);
        GetDlgItemText(hDlg, ID_EDIT_DESTINATION_ADD, destination, 20);
        
        GetDlgItemText(hDlg, ID_EDIT_TAKEOFF_YEAR, takeoff_year, 5);
        GetDlgItemText(hDlg, ID_EDIT_TAKEOFF_MONTH, takeoff_month, 3);
        GetDlgItemText(hDlg, ID_EDIT_TAKEOFF_DAY, takeoff_day, 3);
        GetDlgItemText(hDlg, ID_EDIT_TAKEOFF_HOUR, takeoff_hour, 3);
        GetDlgItemText(hDlg, ID_EDIT_TAKEOFF_MINUTE, takeoff_minute, 3);
        
        GetDlgItemText(hDlg, ID_EDIT_LANDING_YEAR, landing_year, 5);
        GetDlgItemText(hDlg, ID_EDIT_LANDING_MONTH, landing_month, 3);
        GetDlgItemText(hDlg, ID_EDIT_LANDING_DAY, landing_day, 3);
        GetDlgItemText(hDlg, ID_EDIT_LANDING_HOUR, landing_hour, 3);
        GetDlgItemText(hDlg, ID_EDIT_LANDING_MINUTE, landing_minute, 3);
        
        // 检查必填项是否为空
        if (strlen(id) == 0 || strlen(whole_seat) == 0 || strlen(prize) == 0)
        {
            MessageBox(hDlg, "航班号、总座位数和价格为必填项！", "提示", MB_OK | MB_ICONWARNING);
            return TRUE;
        }
        
        // 创建新的航班节点
        Plane_information* new_plane = (Plane_information*)malloc(sizeof(Plane_information));
        if (new_plane == NULL)
        {
            MessageBox(hDlg, "内存分配失败！", "错误", MB_OK | MB_ICONERROR);
            return TRUE;
        }
        
        // 填充数据
        strcpy(new_plane->id, id);
        new_plane->whole_seat = atoi(whole_seat);
        new_plane->rest_seat = (strlen(rest_seat) > 0) ? atoi(rest_seat) : new_plane->whole_seat;
        new_plane->prize = atof(prize);
        
        // 复制起点和终点
        strcpy(new_plane->starting_point, departure);
        strcpy(new_plane->destination, destination);
        
        // 起飞时间
        new_plane->take_off_time[0] = atoi(takeoff_year);
        new_plane->take_off_time[1] = atoi(takeoff_month);
        new_plane->take_off_time[2] = atoi(takeoff_day);
        new_plane->take_off_time[3] = atoi(takeoff_hour);
        new_plane->take_off_time[4] = atoi(takeoff_minute);
        
        // 着陆时间
        new_plane->landing_time[0] = atoi(landing_year);
        new_plane->landing_time[1] = atoi(landing_month);
        new_plane->landing_time[2] = atoi(landing_day);
        new_plane->landing_time[3] = atoi(landing_hour);
        new_plane->landing_time[4] = atoi(landing_minute);
        
        // 设置序号和next指针
        new_plane->num = ++g_planeCount;
        new_plane->next = NULL;
        
        // 添加到链表末尾
        if (g_head == NULL)
        {
            g_head = new_plane;
        }
        else
        {
            Plane_information* p = g_head;
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = new_plane;
        }
        
        // 刷新主窗口的航班列表
        RefreshPlaneList(GetParent(hDlg));
        
        MessageBox(hDlg, "航班添加成功！", "提示", MB_OK);
        
        // 关闭对话框
        DestroyWindow(hDlg);
        return TRUE;
    }
    else if (wmId == ID_BUTTON_CANCEL_ADD_PLANE)  // 取消按钮
    {
        // 不保存任何数据，直接关闭对话框
        if (MessageBox(hDlg, "确定要取消添加吗？输入的数据将不会保存。", "确认取消", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
            DestroyWindow(hDlg);
        }
        return TRUE;
    }
    else if (wmId == IDCANCEL)  // 点击右上角X按钮
    {
        // 同样处理为取消
        if (MessageBox(hDlg, "确定要取消添加吗？输入的数据将不会保存。", "确认取消", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
            DestroyWindow(hDlg);
        }
        return TRUE;
    }
    break;
}
        
        case WM_CLOSE:
{
    if (MessageBox(hDlg, "确定要取消添加吗？输入的数据将不会保存。", "确认取消", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        DestroyWindow(hDlg);
    }
    return TRUE;
}
        
        case WM_DESTROY:
        {
            return TRUE;
        }
    }
    
    return DefWindowProc(hDlg, uMsg, wParam, lParam);
}

/**
 * @brief 显示添加航班对话框
 * @param hwnd 父窗口句柄
 */
void ShowAddPlaneDialog(HWND hwnd)
{
    // 创建对话框 - 增加高度确保所有控件可见
    HWND hDlg = CreateWindow(
     "STATIC",  // 使用静态窗口类作为基础
     "添加航班",
     WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
     CW_USEDEFAULT, CW_USEDEFAULT, 500, 550,  // 增加宽度和高度
     hwnd,
     NULL,
     GetModuleHandle(NULL),
     NULL
    );
    
    if (hDlg == NULL)
    {
        MessageBox(hwnd, "创建对话框失败！", "错误", MB_OK | MB_ICONERROR);
        return;
    }
    
    // 设置对话框窗口过程
    SetWindowLongPtr(hDlg, GWLP_WNDPROC, (LONG_PTR)AddPlaneDlgProc);
    
    // 创建对话框上的控件
    int y = 20;
    int label_width = 80;
    int edit_width = 150;
    int spacing = 30;
    
    // 航班号
    CreateWindow("STATIC", "航班号:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_PLANE_ID_ADD, NULL, NULL);
    
    // 起点
    y += spacing;
    CreateWindow("STATIC", "起点:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_DEPARTURE_ADD, NULL, NULL);
    
    // 终点
    y += spacing;
    CreateWindow("STATIC", "终点:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_DESTINATION_ADD, NULL, NULL);
    
    // 总座位
    y += spacing;
    CreateWindow("STATIC", "总座位:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_WHOLE_SEAT_ADD, NULL, NULL);
    
    // 剩余座位
    y += spacing;
    CreateWindow("STATIC", "剩余座位:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_REST_SEAT_ADD, NULL, NULL);
    
    // 价格
    y += spacing;
    CreateWindow("STATIC", "价格:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_PRIZE_ADD, NULL, NULL);
    
    // 起飞时间
    y += spacing;
    CreateWindow("STATIC", "起飞时间:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    
    // 起飞时间输入框（一行显示）
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 45, 20, hDlg, (HMENU)ID_EDIT_TAKEOFF_YEAR, NULL, NULL);
    CreateWindow("STATIC", "年", WS_CHILD | WS_VISIBLE,
                 160, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 180, y, 35, 20, hDlg, (HMENU)ID_EDIT_TAKEOFF_MONTH, NULL, NULL);
    CreateWindow("STATIC", "月", WS_CHILD | WS_VISIBLE,
                 220, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 240, y, 35, 20, hDlg, (HMENU)ID_EDIT_TAKEOFF_DAY, NULL, NULL);
    CreateWindow("STATIC", "日", WS_CHILD | WS_VISIBLE,
                 280, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    y += spacing;
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 35, 20, hDlg, (HMENU)ID_EDIT_TAKEOFF_HOUR, NULL, NULL);
    CreateWindow("STATIC", "时", WS_CHILD | WS_VISIBLE,
                 150, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 170, y, 35, 20, hDlg, (HMENU)ID_EDIT_TAKEOFF_MINUTE, NULL, NULL);
    CreateWindow("STATIC", "分", WS_CHILD | WS_VISIBLE,
                 210, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    // 着陆时间
    y += spacing * 2;
    CreateWindow("STATIC", "着陆时间:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 45, 20, hDlg, (HMENU)ID_EDIT_LANDING_YEAR, NULL, NULL);
    CreateWindow("STATIC", "年", WS_CHILD | WS_VISIBLE,
                 160, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 180, y, 35, 20, hDlg, (HMENU)ID_EDIT_LANDING_MONTH, NULL, NULL);
    CreateWindow("STATIC", "月", WS_CHILD | WS_VISIBLE,
                 220, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 240, y, 35, 20, hDlg, (HMENU)ID_EDIT_LANDING_DAY, NULL, NULL);
    CreateWindow("STATIC", "日", WS_CHILD | WS_VISIBLE,
                 280, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    y += spacing;
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 35, 20, hDlg, (HMENU)ID_EDIT_LANDING_HOUR, NULL, NULL);
    CreateWindow("STATIC", "时", WS_CHILD | WS_VISIBLE,
                 150, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 170, y, 35, 20, hDlg, (HMENU)ID_EDIT_LANDING_MINUTE, NULL, NULL);
    CreateWindow("STATIC", "分", WS_CHILD | WS_VISIBLE,
                 210, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    // 按钮
y += spacing * 2;
CreateWindow("BUTTON", "输入完成", WS_CHILD | WS_VISIBLE,
         110, y, 100, 30, hDlg, (HMENU)ID_BUTTON_CONFIRM_ADD_PLANE, NULL, NULL);

CreateWindow("BUTTON", "取消", WS_CHILD | WS_VISIBLE,
         220, y, 100, 30, hDlg, (HMENU)ID_BUTTON_CANCEL_ADD_PLANE, NULL, NULL);
}
///白轩宇的添加结束/////