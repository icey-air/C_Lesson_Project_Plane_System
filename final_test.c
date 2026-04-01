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
int Add_What=0;//添加乘客用


int g_accountCount = 0;
tourist *Now_Account=NULL;
tourist *tourist_head=NULL;
/*管理员账户（硬编码）
const char* ADMIN_USERNAME = "admin";
const char* ADMIN_PASSWORD = "admin123";*/

/*======================== 工具函数 ========================*/
// 定义航线信息数组，包含 50 条预置航线
typedef struct {
    char id[10];
    int whole_seat;
    double prize;
    char starting_point[20];
    char destination[20];
    int year, month, day, take_hour, take_min, land_hour, land_min;
} FlightTemplate;

// 预置 50 个航班数据（可根据需要修改）
FlightTemplate templates[] = {
    {"CA1001", 200, 800.0, "沈阳", "北京", 2024, 3, 15,  8,  0, 10, 30},
    {"CA1002", 180, 650.0, "沈阳", "广州", 2024, 3, 16, 14, 20, 16, 45},
    {"MU2001", 220, 950.0, "北京", "上海", 2024, 3, 17,  9,  0, 11, 15},
    {"MU2002", 210, 880.0, "北京", "深圳", 2024, 3, 18, 13, 30, 16, 45},
    {"CZ3001", 190, 720.0, "广州", "成都", 2024, 3, 19, 10, 15, 12, 40},
    {"CZ3002", 200, 780.0, "广州", "昆明", 2024, 3, 20, 15,  0, 17, 20},
    {"HU4001", 170, 600.0, "深圳", "西安", 2024, 3, 21,  7, 30, 10, 10},
    {"HU4002", 160, 550.0, "深圳", "重庆", 2024, 3, 22, 12, 45, 15,  5},
    {"3U5001", 150, 500.0, "成都", "拉萨", 2024, 3, 23,  8, 20, 11, 50},
    {"3U5002", 140, 480.0, "成都", "杭州", 2024, 3, 24, 16, 10, 18, 35},
    {"MF6001", 180, 700.0, "厦门", "北京", 2024, 3, 25,  9, 50, 12, 30},
    {"MF6002", 170, 660.0, "厦门", "上海", 2024, 3, 26, 14, 20, 16,  5},
    {"SC7001", 190, 750.0, "青岛", "广州", 2024, 3, 27, 10,  0, 12, 55},
    {"SC7002", 180, 720.0, "青岛", "深圳", 2024, 3, 28, 13, 15, 16,  5},
    {"ZH8001", 200, 820.0, "深圳", "北京", 2024, 3, 29, 11, 30, 14, 20},
    {"ZH8002", 190, 790.0, "深圳", "上海", 2024, 3, 30, 17, 45, 19, 55},
    {"JD9001", 160, 580.0, "三亚", "成都", 2024, 4,  1,  8,  0, 10, 35},
    {"JD9002", 150, 520.0, "三亚", "重庆", 2024, 4,  2, 12, 20, 14, 45},
    {"GJ0001", 140, 450.0, "杭州", "昆明", 2024, 4,  3,  9, 15, 12,  0},
    {"GJ0002", 130, 420.0, "杭州", "贵阳", 2024, 4,  4, 15, 30, 17, 50},
    // 继续填充至 50 个…… 以下为简写示例，实际可根据需要扩展
    {"CA1003", 210, 900.0, "沈阳", "上海", 2024, 4,  5, 10,  0, 12, 20},
    {"CA1004", 190, 780.0, "沈阳", "深圳", 2024, 4,  6, 14, 30, 17, 10},
    {"MU2003", 200, 850.0, "北京", "广州", 2024, 4,  7,  8, 45, 11, 55},
    {"MU2004", 180, 720.0, "北京", "成都", 2024, 4,  8, 13, 20, 16, 10},
    {"CZ3003", 170, 680.0, "广州", "杭州", 2024, 4,  9,  9, 30, 11, 45},
    {"CZ3004", 160, 620.0, "广州", "南京", 2024, 4, 10, 16,  0, 18, 10},
    {"HU4003", 150, 540.0, "深圳", "昆明", 2024, 4, 11, 11, 15, 13, 40},
    {"HU4004", 140, 510.0, "深圳", "西安", 2024, 4, 12, 14, 50, 17, 25},
    {"3U5003", 130, 470.0, "成都", "厦门", 2024, 4, 13, 10, 30, 12, 55},
    {"3U5004", 120, 430.0, "成都", "青岛", 2024, 4, 14, 15, 20, 17, 45},
    {"MF6003", 190, 760.0, "厦门", "成都", 2024, 4, 15,  9,  0, 11, 40},
    {"MF6004", 180, 730.0, "厦门", "重庆", 2024, 4, 16, 13, 45, 16, 10},
    {"SC7003", 170, 690.0, "青岛", "上海", 2024, 4, 17, 10, 20, 12,  5},
    {"SC7004", 160, 650.0, "青岛", "杭州", 2024, 4, 18, 14, 30, 16, 20},
    {"ZH8003", 200, 830.0, "深圳", "成都", 2024, 4, 19, 11, 40, 14, 15},
    {"ZH8004", 190, 800.0, "深圳", "重庆", 2024, 4, 20, 16, 20, 18, 45},
    {"JD9003", 150, 560.0, "三亚", "北京", 2024, 4, 21,  8, 30, 12, 15},
    {"JD9004", 140, 530.0, "三亚", "上海", 2024, 4, 22, 13, 10, 16,  0},
    {"GJ0003", 130, 470.0, "杭州", "广州", 2024, 4, 23,  9, 45, 12, 10},
    {"GJ0004", 120, 440.0, "杭州", "深圳", 2024, 4, 24, 15, 30, 17, 55},
    {"CA1005", 200, 860.0, "沈阳", "南京", 2024, 4, 25, 10, 15, 12, 30},
    {"CA1006", 180, 750.0, "沈阳", "杭州", 2024, 4, 26, 14,  0, 16, 20},
    {"MU2005", 210, 920.0, "北京", "昆明", 2024, 4, 27,  8, 20, 11, 45},
    {"MU2006", 190, 800.0, "北京", "厦门", 2024, 4, 28, 13, 50, 16, 35},
    {"CZ3005", 170, 670.0, "广州", "青岛", 2024, 4, 29, 10, 30, 12, 55},
    {"CZ3006", 160, 630.0, "广州", "西安", 2024, 4, 30, 15, 10, 17, 40},
    {"HU4005", 150, 590.0, "深圳", "南京", 2024, 5,  1,  9, 20, 11, 45},
    {"HU4006", 140, 560.0, "深圳", "杭州", 2024, 5,  2, 14, 15, 16, 30},
    {"3U5005", 130, 490.0, "成都", "深圳", 2024, 5,  3, 11,  0, 13, 25},
    {"3U5006", 120, 460.0, "成都", "三亚", 2024, 5,  4, 16, 40, 19,  5}
};

// 初始化所有航班，构建链表
void init_all_flights() {
    g_head = NULL;
    g_planeCount = 0;
    Plane_information* tail = NULL;
    
    
    int num_templates = sizeof(templates) / sizeof(templates[0]);
    for (int i = 0; i < num_templates; i++) {
        Plane_information* p = (Plane_information*)malloc(sizeof(Plane_information));
        if (!p) continue;
        
        strcpy(p->id, templates[i].id);
        p->whole_seat = templates[i].whole_seat;
        p->rest_seat = p->whole_seat;   // 初始余票等于全票
        p->prize = templates[i].prize;
        strcpy(p->starting_point, templates[i].starting_point);
        strcpy(p->destination, templates[i].destination);
        p->take_off_time[0] = templates[i].year;
        p->take_off_time[1] = templates[i].month;
        p->take_off_time[2] = templates[i].day;
        p->take_off_time[3] = templates[i].take_hour;
        p->take_off_time[4] = templates[i].take_min;
        p->landing_time[0] = templates[i].year;
        p->landing_time[1] = templates[i].month;
        p->landing_time[2] = templates[i].day;
        p->landing_time[3] = templates[i].land_hour;
        p->landing_time[4] = templates[i].land_min;
        p->num = ++g_planeCount;
        p->next = NULL;
        
        if (g_head == NULL) {
            g_head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }
}
// /**
//  * @brief 初始化测试数据（仅用于演示）
//  */
// void Init_Test_Data(void)
// {
//     // 添加一个测试航班
//     Plane_information* p1 = (Plane_information*)malloc(sizeof(Plane_information));
//     strcpy(p1->id, "CA1001");
//     p1->whole_seat = 200;
//     p1->rest_seat = 150;
//     p1->prize = 800.0;
//     strcpy(p1->starting_point,"沈阳");
//     strcpy(p1->destination,"北京");
//     p1->take_off_time[0] = 2024;
//     p1->take_off_time[1] = 3;
//     p1->take_off_time[2] = 15;
//     p1->take_off_time[3] = 8;
//     p1->take_off_time[4] = 0;
//     p1->landing_time[0] = 2024;
//     p1->landing_time[1] = 3;
//     p1->landing_time[2] = 15;
//     p1->landing_time[3] = 10;
//     p1->landing_time[4] = 30;
//     p1->num = ++g_planeCount;
//     p1->next = NULL;
    
//     g_head = p1;
    
//     // 添加第二个航班
//     Plane_information* p2 = (Plane_information*)malloc(sizeof(Plane_information));
//     strcpy(p2->id, "CA1002");
//     p2->whole_seat = 180;
//     p2->rest_seat = 180;
//     p2->prize = 650.0;
//     strcpy(p2->starting_point,"沈阳");
//     strcpy(p2->destination,"广州");
//     p2->take_off_time[0] = 2024;
//     p2->take_off_time[1] = 3;
//     p2->take_off_time[2] = 16;
//     p2->take_off_time[3] = 14;
//     p2->take_off_time[4] = 20;
//     p2->landing_time[0] = 2024;
//     p2->landing_time[1] = 3;
//     p2->landing_time[2] = 16;
//     p2->landing_time[3] = 16;
//     p2->landing_time[4] = 45;
//     p2->num = ++g_planeCount;
//     p2->next = NULL;
    
//     p1->next = p2;
// }

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
    init_all_flights();
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
            else if (wmId == ID_BUTTON_ADD_PASSENGERS)
            {
                Play_Button_Sound();
                Add_New_Passengers_Window(hwnd);
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


void Add_New_Passengers_Function(int wmId,HWND hwnd)
{
    if(wmId == ID_BUTTON_ADD_PASSENGERS)
    {
        Play_Button_Sound();
        Add_Passengers(hwnd,Now_Account);
    }
     else if(wmId==ID_EDIT_PASSENGER_NAME)
            {   
                Play_Button_Sound();
                if(Add_What==0||Add_What==2||Add_What==4||Add_What==6)
                {                
                    Add_What+=Change_tourist(hwnd,wmId,Now_Account);
                }
            }
            else if(wmId==ID_EDIT_PASSENGER_PHONE)
            {  
                Play_Button_Sound();
                 if(Add_What==0||Add_What==1||Add_What==3||Add_What==4)
                {
                Add_What+=Change_tourist(hwnd,wmId,Now_Account);
                }
            }
             else if(wmId==ID_EDIT_PASSENGER_ID)
            {
                Play_Button_Sound();
                if(Add_What==0||Add_What==1||Add_What==5||Add_What==6)
                {
                Add_What+=Change_tourist(hwnd,wmId,Now_Account);
                }
            }
   else if(wmId == ID_BUTTON_ADD_CONFIRM)
    {
        Play_Button_Sound();
        Add_Passengers_Comfirm(hwnd,Add_What,Now_Account);
        Add_What=0;
    }
    else if(wmId == ID_BUTTON_ADD_CANCLE)
    {
        Play_Button_Sound();
        ShowUserWindow(hwnd);
        Add_What=0;
    }

}