#include "final_test.h"
#include "tourist.h"
#include "windows_Define.h"
#include "Manager.h"
/*======================== 全局变量定义 ========================*/
Plane_information* g_head = NULL;

int g_planeCount = 0;
tourist g_currentUser;
int g_userType = 0;  // 0-未登录，1-管理员，2-普通用户
HWND g_hMainWindow = NULL;
// 账户数组
tourist g_accounts[MAX_ACCOUNTS];
int g_accountCount = 0;
tourist *Now_Account=NULL;
tourist *tourist_head=NULL;
// 管理员账户（硬编码）
const char* ADMIN_USERNAME = "admin";
const char* ADMIN_PASSWORD = "admin123";

/*======================== 工具函数 ========================*/

/**
 * @brief 初始化测试数据（仅用于演示）
 */
void Init_Test_Data(void)
{
    // 添加一个测试航班
    Plane_information* p1 = (Plane_information*)malloc(sizeof(Plane_information));
    strcpy(p1->id, "CA1001");
    p1->whole_seat = 200;
    p1->rest_seat = 150;
    p1->prize = 800.0;
    p1->take_off_time[0] = 2024;
    p1->take_off_time[1] = 3;
    p1->take_off_time[2] = 15;
    p1->take_off_time[3] = 8;
    p1->take_off_time[4] = 0;
    p1->landing_time[0] = 2024;
    p1->landing_time[1] = 3;
    p1->landing_time[2] = 15;
    p1->landing_time[3] = 10;
    p1->landing_time[4] = 30;
    p1->num = ++g_planeCount;
    p1->next = NULL;
    
    g_head = p1;
    
    // 添加第二个航班
    Plane_information* p2 = (Plane_information*)malloc(sizeof(Plane_information));
    strcpy(p2->id, "CA1002");
    p2->whole_seat = 180;
    p2->rest_seat = 180;
    p2->prize = 650.0;
    p2->take_off_time[0] = 2024;
    p2->take_off_time[1] = 3;
    p2->take_off_time[2] = 16;
    p2->take_off_time[3] = 14;
    p2->take_off_time[4] = 20;
    p2->landing_time[0] = 2024;
    p2->landing_time[1] = 3;
    p2->landing_time[2] = 16;
    p2->landing_time[3] = 16;
    p2->landing_time[4] = 45;
    p2->num = ++g_planeCount;
    p2->next = NULL;
    
    p1->next = p2;
}



/*======================== 账户管理功能实现 ========================*/


/**
 * @brief 用户登录
 */
int Login_User(char username[], char password[], int type)
{
    if(type == 1)  // 管理员登录
    {
        if(strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0)
        {
            strcpy(g_currentUser.name, username);
            strcpy(g_currentUser.password, password);
        
            g_currentUser.plane = NULL;
            g_userType = 1;
            return 1;
        }
    }
    else if(type == 2)  // 普通用户登录
    {
        for(int i = 0; i < g_accountCount; i++)
        {
            if(strcmp(g_accounts[i].name, username) == 0 && 
               strcmp(g_accounts[i].password, password) == 0)
            {
                g_currentUser = g_accounts[i];
                g_userType = 2;
                return 1;
            }
        }
    }
    
    return 0;
}

/*======================== Windows界面实现 ========================*/

// 函数声明
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowLoginWindow(HWND hwnd);
void ShowAddPlaneDialog(HWND hwnd);
void ShowDeletePlaneDialog(HWND hwnd);
void ShowUpdatePlaneDialog(HWND hwnd);


/**
 * @brief WinMain - 程序入口
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    // 初始化测试数据（实际使用时可以注释掉）
    Init_Test_Data();
    
    const char CLASS_NAME[] = "FlightManagementSystem";
    
    // 注册窗口类
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClass(&wc);
    
    // 创建主窗口
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "航班管理系统 - 请登录",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );
    
    if(hwnd == NULL) return 0;
    
    g_hMainWindow = hwnd;
    
    ShowWindow(hwnd, nCmdShow);
    
    // 消息循环
    MSG msg = {0};
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

/**
 * @brief 窗口消息处理函数
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CREATE:
        {
            // 显示登录界面
            ShowLoginWindow(hwnd);
            return 0;
        }
        
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
            // 登录相关按钮
            if(wmId == ID_BUTTON_ADMIN_LOGIN)
            {
                Manager_Login(hwnd);
            }
            else if(wmId == ID_BUTTON_USER_LOGIN)
            {
                Now_Account=Loging_Account(hwnd, tourist_head);
            }
            else if(wmId == ID_BUTTON_REGISTER)
            {
                tourist_head=Register_Tourist(hwnd,tourist_head);
            }
            else if(wmId == ID_BUTTON_LOGOUT)
            {
                g_userType = 0;
                memset(&g_currentUser, 0, sizeof(tourist));
                SetWindowText(hwnd, "航班管理系统 - 请登录");
                ShowLoginWindow(hwnd);
            }
            
            // 管理员功能按钮
            else if(wmId == ID_BUTTON_ADD_PLANE)
            {
                ShowAddPlaneDialog(hwnd);
            }
            else if(wmId == ID_BUTTON_DELETE_PLANE)
            {
                ShowDeletePlaneDialog(hwnd);
            }
            else if(wmId == ID_BUTTON_UPDATE_PLANE)
            {
                ShowUpdatePlaneDialog(hwnd);
            }
            else if(wmId == ID_BUTTON_SHOW_PLANE)
            {
                RefreshPlaneList(hwnd);
            }
            
            // 用户功能按钮
            else if(wmId == ID_BUTTON_SEARCH_PLANE)//搜索航班id代码
            {
                char id[20] = "";
                GetDlgItemText(hwnd, ID_EDIT_SEARCH_ID, id, 20);
            }
            else if(wmId == ID_BUTTON_BOOK_TICKET)//预定机票代码BOOK_TICKET
            {
                    Book_Ticket(hwnd, Now_Account,g_head);
            }
            else if(wmId == ID_BUTTON_CANCEL_BOOK)
            {
               
                
                char info[500];
           

                SetDlgItemText(hwnd, ID_STATIC_INFO, info);
            }
            else if(wmId == ID_BUTTON_LIST_BOOK)
            {
                char info[500];
                SetDlgItemText(hwnd, ID_STATIC_INFO, info);
            }
            
            break;
        }
        
        case WM_CLOSE:
        {
            if(MessageBox(hwnd, "确定要退出吗？", "确认", MB_YESNO) == IDYES)
            {
                DestroyWindow(hwnd);
            }
            return 0;
        }
        
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
 * @brief 显示登录界面
 */
void ShowLoginWindow(HWND hwnd)
{
    // 清除所有现有控件
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while(hChild != NULL)
    {
        HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
        DestroyWindow(hChild);
        hChild = hNext;
    }
    
    // 创建登录界面控件
    CreateWindow("STATIC", "用户名:", WS_CHILD | WS_VISIBLE,
                 300, 200, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 360, 200, 150, 25, hwnd, (HMENU)ID_EDIT_USERNAME, NULL, NULL);
    
    CreateWindow("STATIC", "密码:", WS_CHILD | WS_VISIBLE,
                 300, 240, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD,
                 360, 240, 150, 25, hwnd, (HMENU)ID_EDIT_PASSWORD, NULL, NULL);
    
    CreateWindow("BUTTON", "管理员登录", WS_CHILD | WS_VISIBLE,
                 300, 280, 100, 30, hwnd, (HMENU)ID_BUTTON_ADMIN_LOGIN, NULL, NULL);
    
    CreateWindow("BUTTON", "用户登录", WS_CHILD | WS_VISIBLE,
                 410, 280, 100, 30, hwnd, (HMENU)ID_BUTTON_USER_LOGIN, NULL, NULL);
    
    CreateWindow("STATIC", "新用户注册:", WS_CHILD | WS_VISIBLE,
                 300, 330, 80, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("STATIC", "电话:", WS_CHILD | WS_VISIBLE,
                 300, 360, 50, 25, hwnd, NULL, NULL, NULL);
    
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                 360, 360, 150, 25, hwnd, (HMENU)ID_EDIT_PHONE, NULL, NULL);
    
    CreateWindow("BUTTON", "注册", WS_CHILD | WS_VISIBLE,
                 360, 400, 80, 30, hwnd, (HMENU)ID_BUTTON_REGISTER, NULL, NULL);
}


/**
 * @brief 显示添加航班对话框
 */
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
}

// 简单的输入框函数
BOOL InputBox(HWND hwnd, char* prompt, char* result, int max_len)
{
    // 这是一个简化函数，实际应用中应该创建对话框
    // 这里用MessageBox演示概念
    MessageBox(hwnd, "在实际应用中，这里会弹出输入对话框", "提示", MB_OK);
    strcpy(result, "CA1003");
    return TRUE;
}

/**
 * @brief 显示删除航班对话框
 */
void ShowDeletePlaneDialog(HWND hwnd)
{
    char id[20] = "";
    if(InputBox(hwnd, "请输入要删除的航班号:", id, 20))
    {

        RefreshPlaneList(hwnd);
    }
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