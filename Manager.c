#include "Manager.h"
#include "windows_Define.h"
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



/////白轩宇的添加/////
// 在 Manager.c 中添加以下代码

/* 添加航班对话框的窗口过程函数 */
LRESULT CALLBACK AddPlaneDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            // 设置默认值
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

/**
 * @brief 根据航班号查找航班
 */
Plane_information* FindPlaneById(Plane_information* head, const char* id)
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

/**
 * @brief 修改航班对话框的窗口过程函数
 */
LRESULT CALLBACK UpdatePlaneDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static Plane_information* targetPlane = NULL;
    
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            // 获取传入的航班指针
            targetPlane = (Plane_information*)lParam;
            if (targetPlane == NULL)
            {
                MessageBox(hDlg, "未找到要修改的航班！", "错误", MB_OK);
                DestroyWindow(hDlg);
                return TRUE;
            }
            
            // 将现有数据填充到输入框中
            char buffer[32];
            
            // 航班号（只读或可修改，这里设置为可修改）
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_PLANE_ID, targetPlane->id);
            
            // 起点和终点
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_DEPARTURE, targetPlane->starting_point);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_DESTINATION, targetPlane->destination);
            
            // 座位数和价格
            sprintf(buffer, "%d", targetPlane->whole_seat);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_WHOLE_SEAT, buffer);
            sprintf(buffer, "%d", targetPlane->rest_seat);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_REST_SEAT, buffer);
            sprintf(buffer, "%.0f", targetPlane->prize);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_PRIZE, buffer);
            
            // 起飞时间
            sprintf(buffer, "%d", targetPlane->take_off_time[0]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_YEAR, buffer);
            sprintf(buffer, "%d", targetPlane->take_off_time[1]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_MONTH, buffer);
            sprintf(buffer, "%d", targetPlane->take_off_time[2]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_DAY, buffer);
            sprintf(buffer, "%d", targetPlane->take_off_time[3]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_HOUR, buffer);
            sprintf(buffer, "%d", targetPlane->take_off_time[4]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_MINUTE, buffer);
            
            // 着陆时间
            sprintf(buffer, "%d", targetPlane->landing_time[0]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_YEAR, buffer);
            sprintf(buffer, "%d", targetPlane->landing_time[1]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_MONTH, buffer);
            sprintf(buffer, "%d", targetPlane->landing_time[2]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_DAY, buffer);
            sprintf(buffer, "%d", targetPlane->landing_time[3]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_HOUR, buffer);
            sprintf(buffer, "%d", targetPlane->landing_time[4]);
            SetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_MINUTE, buffer);
            
            return TRUE;
        }
        
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
            if (wmId == ID_BUTTON_UPDATE_CONFIRM)  // 确认修改按钮
            {
                // 获取输入的所有数据
                char id[20], departure[20], destination[20];
                char whole_seat[10], rest_seat[10], prize[10];
                char takeoff_year[5], takeoff_month[3], takeoff_day[3];
                char takeoff_hour[3], takeoff_minute[3];
                char landing_year[5], landing_month[3], landing_day[3];
                char landing_hour[3], landing_minute[3];
                
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_PLANE_ID, id, 20);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_DEPARTURE, departure, 20);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_DESTINATION, destination, 20);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_WHOLE_SEAT, whole_seat, 10);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_REST_SEAT, rest_seat, 10);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_PRIZE, prize, 10);
                
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_YEAR, takeoff_year, 5);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_MONTH, takeoff_month, 3);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_DAY, takeoff_day, 3);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_HOUR, takeoff_hour, 3);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_TAKEOFF_MINUTE, takeoff_minute, 3);
                
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_YEAR, landing_year, 5);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_MONTH, landing_month, 3);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_DAY, landing_day, 3);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_HOUR, landing_hour, 3);
                GetDlgItemText(hDlg, ID_EDIT_UPDATE_LANDING_MINUTE, landing_minute, 3);
                
                // 检查必填项
                if (strlen(id) == 0 || strlen(whole_seat) == 0 || strlen(prize) == 0)
                {
                    MessageBox(hDlg, "航班号、总座位数和价格为必填项！", "提示", MB_OK | MB_ICONWARNING);
                    return TRUE;
                }
                
                // 更新数据
                strcpy(targetPlane->id, id);
                strcpy(targetPlane->starting_point, departure);
                strcpy(targetPlane->destination, destination);
                targetPlane->whole_seat = atoi(whole_seat);
                targetPlane->rest_seat = (strlen(rest_seat) > 0) ? atoi(rest_seat) : targetPlane->whole_seat;
                targetPlane->prize = atof(prize);
                
                targetPlane->take_off_time[0] = atoi(takeoff_year);
                targetPlane->take_off_time[1] = atoi(takeoff_month);
                targetPlane->take_off_time[2] = atoi(takeoff_day);
                targetPlane->take_off_time[3] = atoi(takeoff_hour);
                targetPlane->take_off_time[4] = atoi(takeoff_minute);
                
                targetPlane->landing_time[0] = atoi(landing_year);
                targetPlane->landing_time[1] = atoi(landing_month);
                targetPlane->landing_time[2] = atoi(landing_day);
                targetPlane->landing_time[3] = atoi(landing_hour);
                targetPlane->landing_time[4] = atoi(landing_minute);
                
                // 刷新主窗口的航班列表
                RefreshPlaneList(GetParent(hDlg));
                
                MessageBox(hDlg, "航班修改成功！", "提示", MB_OK);
                
                // 关闭对话框
                DestroyWindow(hDlg);
                return TRUE;
            }
            else if (wmId == ID_BUTTON_UPDATE_CANCEL)  // 取消按钮
            {
                if (MessageBox(hDlg, "确定要取消修改吗？", "确认取消", MB_YESNO | MB_ICONQUESTION) == IDYES)
                {
                    DestroyWindow(hDlg);
                }
                return TRUE;
            }
            else if (wmId == IDCANCEL)
            {
                if (MessageBox(hDlg, "确定要取消修改吗？", "确认取消", MB_YESNO | MB_ICONQUESTION) == IDYES)
                {
                    DestroyWindow(hDlg);
                }
                return TRUE;
            }
            break;
        }
        
        case WM_CLOSE:
        {
            if (MessageBox(hDlg, "确定要取消修改吗？", "确认取消", MB_YESNO | MB_ICONQUESTION) == IDYES)
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
 * @brief 显示修改航班对话框
 * @param hwnd 父窗口句柄
 */
void ShowUpdatePlaneDialog(HWND hwnd)
{
    // 获取输入框中的航班号
    char planeId[20] = "";
    GetDlgItemText(hwnd, ID_EDIT_SEARCH_ID, planeId, 20);
    
    if (strlen(planeId) == 0)
    {
        MessageBox(hwnd, "请在输入框中输入要修改的航班号！", "提示", MB_OK);
        return;
    }
    
    // 查找要修改的航班
    Plane_information* targetPlane = FindPlaneById(g_head, planeId);
    
    if (targetPlane == NULL)
    {
        MessageBox(hwnd, "未找到指定的航班！请检查航班号是否正确。", "提示", MB_OK);
        return;
    }
    
    // 创建修改航班对话框
    HWND hDlg = CreateWindow(
        "STATIC",  // 使用静态窗口类作为基础
        "修改航班",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 550,
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
    SetWindowLongPtr(hDlg, GWLP_WNDPROC, (LONG_PTR)UpdatePlaneDlgProc);
    
    // 创建对话框上的控件
    int y = 20;
    int label_width = 80;
    int edit_width = 150;
    int spacing = 30;
    
    // 航班号
    CreateWindow("STATIC", "航班号:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_UPDATE_PLANE_ID, NULL, NULL);
    
    // 起点
    y += spacing;
    CreateWindow("STATIC", "起点:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_UPDATE_DEPARTURE, NULL, NULL);
    
    // 终点
    y += spacing;
    CreateWindow("STATIC", "终点:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_UPDATE_DESTINATION, NULL, NULL);
    
    // 总座位
    y += spacing;
    CreateWindow("STATIC", "总座位:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_UPDATE_WHOLE_SEAT, NULL, NULL);
    
    // 剩余座位
    y += spacing;
    CreateWindow("STATIC", "剩余座位:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_UPDATE_REST_SEAT, NULL, NULL);
    
    // 价格
    y += spacing;
    CreateWindow("STATIC", "价格:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 110, y, edit_width, 20, hDlg, (HMENU)ID_EDIT_UPDATE_PRIZE, NULL, NULL);
    
    // 起飞时间
    y += spacing;
    CreateWindow("STATIC", "起飞时间:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 45, 20, hDlg, (HMENU)ID_EDIT_UPDATE_TAKEOFF_YEAR, NULL, NULL);
    CreateWindow("STATIC", "年", WS_CHILD | WS_VISIBLE,
                 160, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 180, y, 35, 20, hDlg, (HMENU)ID_EDIT_UPDATE_TAKEOFF_MONTH, NULL, NULL);
    CreateWindow("STATIC", "月", WS_CHILD | WS_VISIBLE,
                 220, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 240, y, 35, 20, hDlg, (HMENU)ID_EDIT_UPDATE_TAKEOFF_DAY, NULL, NULL);
    CreateWindow("STATIC", "日", WS_CHILD | WS_VISIBLE,
                 280, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    y += spacing;
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 35, 20, hDlg, (HMENU)ID_EDIT_UPDATE_TAKEOFF_HOUR, NULL, NULL);
    CreateWindow("STATIC", "时", WS_CHILD | WS_VISIBLE,
                 150, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 170, y, 35, 20, hDlg, (HMENU)ID_EDIT_UPDATE_TAKEOFF_MINUTE, NULL, NULL);
    CreateWindow("STATIC", "分", WS_CHILD | WS_VISIBLE,
                 210, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    // 着陆时间
    y += spacing * 2;
    CreateWindow("STATIC", "着陆时间:", WS_CHILD | WS_VISIBLE,
                 20, y, label_width, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 45, 20, hDlg, (HMENU)ID_EDIT_UPDATE_LANDING_YEAR, NULL, NULL);
    CreateWindow("STATIC", "年", WS_CHILD | WS_VISIBLE,
                 160, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 180, y, 35, 20, hDlg, (HMENU)ID_EDIT_UPDATE_LANDING_MONTH, NULL, NULL);
    CreateWindow("STATIC", "月", WS_CHILD | WS_VISIBLE,
                 220, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 240, y, 35, 20, hDlg, (HMENU)ID_EDIT_UPDATE_LANDING_DAY, NULL, NULL);
    CreateWindow("STATIC", "日", WS_CHILD | WS_VISIBLE,
                 280, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    y += spacing;
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 110, y, 35, 20, hDlg, (HMENU)ID_EDIT_UPDATE_LANDING_HOUR, NULL, NULL);
    CreateWindow("STATIC", "时", WS_CHILD | WS_VISIBLE,
                 150, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                 170, y, 35, 20, hDlg, (HMENU)ID_EDIT_UPDATE_LANDING_MINUTE, NULL, NULL);
    CreateWindow("STATIC", "分", WS_CHILD | WS_VISIBLE,
                 210, y, 20, 20, hDlg, NULL, NULL, NULL);
    
    // 按钮
    y += spacing * 2;
    CreateWindow("BUTTON", "确认修改", WS_CHILD | WS_VISIBLE,
                 110, y, 100, 30, hDlg, (HMENU)ID_BUTTON_UPDATE_CONFIRM, NULL, NULL);
    
    CreateWindow("BUTTON", "取消", WS_CHILD | WS_VISIBLE,
                 220, y, 100, 30, hDlg, (HMENU)ID_BUTTON_UPDATE_CANCEL, NULL, NULL);
    
    // 发送WM_INITDIALOG消息，传入航班指针
    SendMessage(hDlg, WM_INITDIALOG, 0, (LPARAM)targetPlane);
}





///白轩宇的添加结束/////
