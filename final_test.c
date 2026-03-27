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

int Change_What=0;//修改账户信息用，别动


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
    strcpy(p1->starting_point,"沈阳");
    strcpy(p1->destination,"北京");
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
    strcpy(p2->starting_point,"沈阳");
    strcpy(p2->destination,"广州");
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

/*======================== Windows界面实现 ========================*/

// 函数声明
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
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
        CW_USEDEFAULT, CW_USEDEFAULT, 900, 600,
        NULL, NULL, hInstance, NULL
    );
    
    if(hwnd == NULL) return 0;
    
    g_hMainWindow = hwnd;
    
    ShowWindow(hwnd, nCmdShow);
    Play_Button_Sound();
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
            Chang_Account_Function(wmId,hwnd);
            
            // 登录相关按钮
            if(wmId == ID_BUTTON_ADMIN_LOGIN)
            {
                Play_Button_Sound();
                Manager_Login(hwnd);
            }
            else if(wmId == ID_BUTTON_USER_LOGIN)
            {
                Play_Button_Sound();
                Now_Account=Loging_Account(hwnd, tourist_head);
                if(Now_Account!=NULL)
                {
                List_Ticket_Reservation(hwnd, Now_Account);
                }
            }
            else if(wmId == ID_BUTTON_REGISTER)
            {
                Play_Button_Sound();
                Show_Rejister_Window(hwnd);                
            }
            else if(wmId == ID_BUTTON_REGISTER_COMFIRM)
            {
                Play_Button_Sound();
                tourist_head=Register_Tourist(hwnd,tourist_head);
            }
            else if(wmId == ID_BUTTON_REGISTER_CANCLE)
            {
                Play_Button_Sound();
                ShowLoginWindow(hwnd);
            }
            else if(wmId == ID_BUTTON_LOGOUT)
            {
                Play_Button_Sound();
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
                Play_Button_Sound();
                ShowAddPlaneDialog(hwnd);
            }

            
            else if(wmId == ID_BUTTON_DELETE_PLANE)
            {
                Play_Button_Sound();
                g_head=Manager_Delete_Plane(hwnd,g_head);
            }
            else if(wmId == ID_BUTTON_UPDATE_PLANE)
            {
                Play_Button_Sound();
                ShowUpdatePlaneDialog(hwnd);
            }
            else if(wmId == ID_BUTTON_SHOW_PLANE)
            {
                Play_Button_Sound();
                RefreshPlaneList(hwnd);
            }
            //用户界面按钮功能封装
            User_Button_Function(wmId,hwnd);
            break;
        }
        
        case WM_CLOSE:
        {
            if(MessageBox(hwnd, "确定要退出吗？", "确认", MB_YESNO) == IDYES)
            {
                Play_Button_Sound();
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



/*@brief	修改账户信息功能封装
* @param	windows句柄
* @return	无
*/
void Chang_Account_Function(int wmId,HWND hwnd)
{
       if(wmId == ID_BUTTON_CHANGE_INFO)//修改信息
            {
                Play_Button_Sound();
                Show_Account_Information_Change_Window(hwnd);
            }  
            else if(wmId==ID_BUTTON_CHANGE_Account)
            {   
                Play_Button_Sound();
                if(Change_What==0||Change_What==3||Change_What==5||Change_What==8)
                {
                 Change_What+=Change_tourist(hwnd,wmId,Now_Account);
                }
            }
            else if(wmId==ID_BUTTON_CHANGE_Password)
            {
                Play_Button_Sound();
                if(Change_What==0||Change_What==1||Change_What==5||Change_What==6)
                {
                Change_What+=Change_tourist(hwnd,wmId,Now_Account);
                }
            }
            else if(wmId==ID_BUTTON_CHANGE_Phone)
            {  
                Play_Button_Sound();
                 if(Change_What==0||Change_What==1||Change_What==3||Change_What==4)
                {
                Change_What+=Change_tourist(hwnd,wmId,Now_Account);
                }
            }
            else if(wmId == ID_BUTTON_CHANGE_INFO_COMFIRM)//确认修改
            {
                Play_Button_Sound();
                Change_Information_Comfirm(hwnd,Change_What,Now_Account);
                Change_What=0;
            }
            else if(wmId == ID_BUTTON_CHANGE_INFO_CANCLE)//取消修改
            {
                Play_Button_Sound();
                ShowUserWindow(hwnd);
                Change_What=0;
            }
}



/*@brief	用户界面按钮功能封装
* @param	windows句柄
* @return	无
*/
void User_Button_Function(int wmId,HWND hwnd)
{
               
            // 用户功能按钮
            if(wmId == ID_BUTTON_SEARCH_PLANE)//搜索航班id代码
            {
                Play_Button_Sound();
                Find_Plane_ID(hwnd,g_head);
            }
            else if(wmId == ID_BUTTON_BOOK_TICKET)//预定机票代码BOOK_TICKET
            {
                Play_Button_Sound();
                Book_Ticket(hwnd, Now_Account,g_head);
                List_Ticket_Reservation(hwnd, Now_Account);
            }
            else if(wmId == ID_BUTTON_CANCEL_BOOK)//取消预定
            {
                Play_Button_Sound();
                Cancel_Ticket_Reservation(hwnd,Now_Account);
                List_Ticket_Reservation(hwnd, Now_Account);
            }
            else if(wmId == ID_BUTTON_LIST_BOOK)//列出预定
            {
                Play_Button_Sound();
                List_Ticket_Reservation(hwnd, Now_Account);
            }
            else if(wmId == ID_BUTTON_FILTER_PLANE)
            {
                Plane_information* result=Find_Plane(hwnd,wmId,g_head);
                if(result!=NULL){
                Refresh_FindPlaneList(hwnd,result);
                }
                else
                {
                    RefreshPlaneList(hwnd);
                }        
            }
  
}