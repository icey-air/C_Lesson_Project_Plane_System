#include "final_test.h"
#include "tourist.h"
#include "windows_Define.h"
#include "Manager.h"

#include "Ticket.h"

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
/*管理员账户（硬编码）
const char* ADMIN_USERNAME = "admin";
const char* ADMIN_PASSWORD = "admin123";*/

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



/*======================== Windows界面实现 ========================*/

// 函数声明
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowLoginWindow(HWND hwnd);
void ShowAddPlaneDialog(HWND hwnd);
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
            // 在 final_test.c 的 WindowProc 函数中，找到管理员功能按钮的处理部分
// 在 ID_BUTTON_DELETE_PLANE 的处理之前添加以下代码

            else if(wmId == ID_BUTTON_ADD_PLANE)
            {
              ShowAddPlaneDialog(hwnd);
            }

            
            else if(wmId == ID_BUTTON_DELETE_PLANE)
            {
                g_head=Manager_Delete_Plane(hwnd,g_head);
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
                Find_Plane_ID(hwnd,g_head);//只是查找ID，没有显示信息的代码//可能要再封装一次
            }
            else if(wmId == ID_BUTTON_BOOK_TICKET)//预定机票代码BOOK_TICKET
            {
                    Book_Ticket(hwnd, Now_Account,g_head);//里面有一个刷新函数我应该用错了--后记：现在我已经不知道之前注释是什么意思什么了
            }
            else if(wmId == ID_BUTTON_CANCEL_BOOK)//取消预定
            {
                Cancel_Ticket_Reservation(hwnd,Now_Account);
            }
            else if(wmId == ID_BUTTON_LIST_BOOK)//列出预定
            {
              List_Ticket_Reservation(hwnd, Now_Account);
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


