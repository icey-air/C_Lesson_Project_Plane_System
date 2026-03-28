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

typedef struct {
    char id[20];
    int whole_seat;
    int rest_seat;
    double prize;
    char starting_point[20];
    char destination[20];
    int take_off_time[5];
    int landing_time[5];
} PlaneStaticData;

// 100个固定航班数据
static const PlaneStaticData plane_data[] = {
    // 航班 1-10
    {"CA1001", 200, 150, 800.0, "沈阳", "北京", {2024,3,15,8,0}, {2024,3,15,10,30}},
    {"CA1002", 180, 180, 650.0, "沈阳", "广州", {2024,3,16,14,20}, {2024,3,16,16,45}},
    {"CA1003", 220, 220, 950.0, "上海", "深圳", {2024,3,17,9,0}, {2024,3,17,11,20}},
    {"CA1004", 190, 190, 720.0, "北京", "成都", {2024,3,17,13,30}, {2024,3,17,16,10}},
    {"CA1005", 210, 210, 880.0, "广州", "杭州", {2024,3,18,10,45}, {2024,3,18,12,50}},
    {"CA1006", 175, 175, 560.0, "成都", "西安", {2024,3,18,15,0}, {2024,3,18,16,30}},
    {"CA1007", 250, 250, 1200.0, "深圳", "北京", {2024,3,19,7,30}, {2024,3,19,10,0}},
    {"CA1008", 165, 165, 540.0, "重庆", "武汉", {2024,3,19,12,15}, {2024,3,19,14,0}},
    {"CA1009", 230, 230, 1050.0, "杭州", "成都", {2024,3,20,9,45}, {2024,3,20,12,20}},
    {"CA1010", 195, 195, 780.0, "西安", "南京", {2024,3,20,14,30}, {2024,3,20,16,45}},
    // 航班 11-20
    {"CA1011", 205, 205, 890.0, "武汉", "厦门", {2024,3,21,8,0}, {2024,3,21,9,50}},
    {"CA1012", 185, 185, 690.0, "南京", "青岛", {2024,3,21,11,20}, {2024,3,21,13,0}},
    {"CA1013", 215, 215, 920.0, "厦门", "昆明", {2024,3,22,10,15}, {2024,3,22,12,40}},
    {"CA1014", 170, 170, 580.0, "青岛", "长沙", {2024,3,22,15,0}, {2024,3,22,17,10}},
    {"CA1015", 240, 240, 1100.0, "昆明", "上海", {2024,3,23,9,30}, {2024,3,23,12,0}},
    {"CA1016", 188, 188, 710.0, "长沙", "重庆", {2024,3,23,13,45}, {2024,3,23,15,30}},
    {"CA1017", 260, 260, 1350.0, "沈阳", "深圳", {2024,3,24,7,0}, {2024,3,24,10,20}},
    {"CA1018", 202, 202, 850.0, "北京", "广州", {2024,3,24,12,15}, {2024,3,24,15,0}},
    {"CA1019", 178, 178, 620.0, "成都", "南京", {2024,3,25,14,0}, {2024,3,25,16,10}},
    {"CA1020", 225, 225, 980.0, "西安", "杭州", {2024,3,25,17,30}, {2024,3,25,19,45}},
    // 航班 21-30
    {"CA1021", 192, 192, 740.0, "武汉", "青岛", {2024,3,26,8,20}, {2024,3,26,10,0}},
    {"CA1022", 208, 208, 870.0, "厦门", "北京", {2024,3,26,11,45}, {2024,3,26,14,15}},
    {"CA1023", 168, 168, 550.0, "昆明", "长沙", {2024,3,27,9,0}, {2024,3,27,10,45}},
    {"CA1024", 245, 245, 1150.0, "深圳", "成都", {2024,3,27,13,30}, {2024,3,27,16,0}},
    {"CA1025", 185, 185, 680.0, "重庆", "厦门", {2024,3,28,15,15}, {2024,3,28,17,30}},
    {"CA1026", 212, 212, 900.0, "杭州", "西安", {2024,3,28,18,45}, {2024,3,28,20,55}},
    {"CA1027", 195, 195, 760.0, "南京", "沈阳", {2024,3,29,7,30}, {2024,3,29,9,45}},
    {"CA1028", 232, 232, 1020.0, "青岛", "上海", {2024,3,29,10,0}, {2024,3,29,12,10}},
    {"CA1029", 172, 172, 590.0, "长沙", "昆明", {2024,3,30,13,15}, {2024,3,30,15,20}},
    {"CA1030", 218, 218, 940.0, "广州", "武汉", {2024,3,30,16,30}, {2024,3,30,18,15}},
    // 航班 31-40
    {"CA1031", 188, 188, 720.0, "成都", "深圳", {2024,3,31,8,0}, {2024,3,31,10,30}},
    {"CA1032", 205, 205, 860.0, "北京", "杭州", {2024,3,31,12,20}, {2024,3,31,14,35}},
    {"CA1033", 248, 248, 1250.0, "上海", "昆明", {2024,4,1,9,15}, {2024,4,1,12,0}},
    {"CA1034", 176, 176, 610.0, "西安", "重庆", {2024,4,1,14,45}, {2024,4,1,16,20}},
    {"CA1035", 222, 222, 970.0, "沈阳", "南京", {2024,4,2,7,30}, {2024,4,2,9,40}},
    {"CA1036", 190, 190, 730.0, "厦门", "青岛", {2024,4,2,11,0}, {2024,4,2,12,50}},
    {"CA1037", 215, 215, 910.0, "武汉", "成都", {2024,4,3,13,20}, {2024,4,3,15,45}},
    {"CA1038", 169, 169, 570.0, "长沙", "广州", {2024,4,3,16,10}, {2024,4,3,18,0}},
    {"CA1039", 238, 238, 1080.0, "杭州", "北京", {2024,4,4,8,45}, {2024,4,4,11,10}},
    {"CA1040", 182, 182, 650.0, "昆明", "西安", {2024,4,4,14,0}, {2024,4,4,16,15}},
    // 航班 41-50
    {"CA1041", 196, 196, 770.0, "深圳", "武汉", {2024,4,5,9,30}, {2024,4,5,11,20}},
    {"CA1042", 210, 210, 890.0, "南京", "厦门", {2024,4,5,12,45}, {2024,4,5,14,30}},
    {"CA1043", 252, 252, 1280.0, "重庆", "上海", {2024,4,6,7,15}, {2024,4,6,9,45}},
    {"CA1044", 174, 174, 600.0, "青岛", "长沙", {2024,4,6,10,30}, {2024,4,6,12,10}},
    {"CA1045", 228, 228, 1010.0, "成都", "杭州", {2024,4,7,13,0}, {2024,4,7,15,20}},
    {"CA1046", 203, 203, 840.0, "广州", "南京", {2024,4,7,16,45}, {2024,4,7,18,55}},
    {"CA1047", 185, 185, 700.0, "北京", "西安", {2024,4,8,8,20}, {2024,4,8,10,10}},
    {"CA1048", 235, 235, 1120.0, "沈阳", "成都", {2024,4,8,11,40}, {2024,4,8,14,30}},
    {"CA1049", 166, 166, 530.0, "昆明", "青岛", {2024,4,9,15,0}, {2024,4,9,17,20}},
    {"CA1050", 219, 219, 960.0, "厦门", "武汉", {2024,4,9,18,30}, {2024,4,9,20,15}},
    // 航班 51-60
    {"CA1051", 200, 200, 810.0, "上海", "重庆", {2024,4,10,7,0}, {2024,4,10,9,30}},
    {"CA1052", 180, 180, 660.0, "深圳", "杭州", {2024,4,10,10,20}, {2024,4,10,12,40}},
    {"CA1053", 225, 225, 990.0, "南京", "昆明", {2024,4,11,13,15}, {2024,4,11,15,45}},
    {"CA1054", 190, 190, 740.0, "成都", "北京", {2024,4,11,16,30}, {2024,4,11,18,50}},
    {"CA1055", 245, 245, 1180.0, "广州", "沈阳", {2024,4,12,8,45}, {2024,4,12,11,30}},
    {"CA1056", 172, 172, 580.0, "西安", "长沙", {2024,4,12,12,0}, {2024,4,12,13,45}},
    {"CA1057", 215, 215, 930.0, "武汉", "深圳", {2024,4,13,14,20}, {2024,4,13,16,10}},
    {"CA1058", 188, 188, 710.0, "青岛", "成都", {2024,4,13,17,0}, {2024,4,13,19,15}},
    {"CA1059", 255, 255, 1300.0, "杭州", "广州", {2024,4,14,9,30}, {2024,4,14,11,55}},
    {"CA1060", 178, 178, 630.0, "厦门", "南京", {2024,4,14,12,45}, {2024,4,14,14,35}},
    // 航班 61-70
    {"CA1061", 195, 195, 780.0, "北京", "昆明", {2024,4,15,8,0}, {2024,4,15,10,45}},
    {"CA1062", 212, 212, 900.0, "上海", "西安", {2024,4,15,11,15}, {2024,4,15,13,30}},
    {"CA1063", 230, 230, 1050.0, "沈阳", "重庆", {2024,4,16,14,0}, {2024,4,16,16,20}},
    {"CA1064", 185, 185, 690.0, "成都", "武汉", {2024,4,16,17,30}, {2024,4,16,19,10}},
    {"CA1065", 220, 220, 970.0, "深圳", "青岛", {2024,4,17,7,45}, {2024,4,17,9,55}},
    {"CA1066", 168, 168, 550.0, "长沙", "杭州", {2024,4,17,10,20}, {2024,4,17,12,0}},
    {"CA1067", 248, 248, 1220.0, "昆明", "北京", {2024,4,18,13,15}, {2024,4,18,16,0}},
    {"CA1068", 205, 205, 860.0, "南京", "广州", {2024,4,18,16,40}, {2024,4,18,18,55}},
    {"CA1069", 175, 175, 590.0, "西安", "厦门", {2024,4,19,8,30}, {2024,4,19,10,20}},
    {"CA1070", 238, 238, 1090.0, "重庆", "深圳", {2024,4,19,11,0}, {2024,4,19,13,30}},
    // 航班 71-80
    {"CA1071", 192, 192, 750.0, "杭州", "沈阳", {2024,4,20,14,15}, {2024,4,20,16,35}},
    {"CA1072", 210, 210, 880.0, "武汉", "上海", {2024,4,20,17,20}, {2024,4,20,19,10}},
    {"CA1073", 250, 250, 1260.0, "北京", "成都", {2024,4,21,9,0}, {2024,4,21,11,30}},
    {"CA1074", 182, 182, 670.0, "青岛", "昆明", {2024,4,21,12,45}, {2024,4,21,15,10}},
    {"CA1075", 228, 228, 1030.0, "广州", "西安", {2024,4,22,7,30}, {2024,4,22,9,50}},
    {"CA1076", 195, 195, 790.0, "厦门", "长沙", {2024,4,22,10,15}, {2024,4,22,12,5}},
    {"CA1077", 215, 215, 940.0, "深圳", "南京", {2024,4,23,13,0}, {2024,4,23,15,15}},
    {"CA1078", 172, 172, 570.0, "成都", "杭州", {2024,4,23,16,30}, {2024,4,23,18,20}},
    {"CA1079", 242, 242, 1160.0, "沈阳", "上海", {2024,4,24,8,0}, {2024,4,24,10,30}},
    {"CA1080", 188, 188, 700.0, "昆明", "武汉", {2024,4,24,11,20}, {2024,4,24,13,45}},
    // 航班 81-90
    {"CA1081", 205, 205, 850.0, "西安", "深圳", {2024,4,25,14,10}, {2024,4,25,16,40}},
    {"CA1082", 178, 178, 620.0, "重庆", "青岛", {2024,4,25,17,30}, {2024,4,25,19,25}},
    {"CA1083", 235, 235, 1070.0, "北京", "厦门", {2024,4,26,9,15}, {2024,4,26,11,45}},
    {"CA1084", 190, 190, 730.0, "南京", "成都", {2024,4,26,12,30}, {2024,4,26,14,50}},
    {"CA1085", 222, 222, 990.0, "杭州", "广州", {2024,4,27,15,0}, {2024,4,27,17,20}},
    {"CA1086", 165, 165, 540.0, "长沙", "沈阳", {2024,4,27,18,15}, {2024,4,27,20,5}},
    {"CA1087", 248, 248, 1230.0, "上海", "昆明", {2024,4,28,7,45}, {2024,4,28,10,30}},
    {"CA1088", 202, 202, 820.0, "武汉", "西安", {2024,4,28,11,0}, {2024,4,28,12,55}},
    {"CA1089", 218, 218, 950.0, "深圳", "成都", {2024,4,29,13,20}, {2024,4,29,15,50}},
    {"CA1090", 185, 185, 680.0, "青岛", "杭州", {2024,4,29,16,40}, {2024,4,29,18,30}},
    // 航班 91-100
    {"CA1091", 210, 210, 880.0, "昆明", "南京", {2024,4,30,8,30}, {2024,4,30,10,50}},
    {"CA1092", 195, 195, 760.0, "重庆", "北京", {2024,4,30,11,15}, {2024,4,30,13,45}},
    {"CA1093", 230, 230, 1040.0, "沈阳", "武汉", {2024,5,1,14,0}, {2024,5,1,16,20}},
    {"CA1094", 172, 172, 590.0, "厦门", "西安", {2024,5,1,17,30}, {2024,5,1,19,15}},
    {"CA1095", 255, 255, 1320.0, "广州", "上海", {2024,5,2,9,0}, {2024,5,2,11,30}},
    {"CA1096", 188, 188, 710.0, "成都", "青岛", {2024,5,2,12,20}, {2024,5,2,14,40}},
    {"CA1097", 225, 225, 1000.0, "北京", "深圳", {2024,5,3,15,10}, {2024,5,3,17,40}},
    {"CA1098", 180, 180, 650.0, "杭州", "重庆", {2024,5,3,18,25}, {2024,5,3,20,15}},
    {"CA1099", 240, 240, 1130.0, "南京", "昆明", {2024,5,4,7,30}, {2024,5,4,10,0}},
    {"CA1100", 200, 200, 820.0, "武汉", "厦门", {2024,5,4,10,45}, {2024,5,4,12,50}}
};

#define PLANE_COUNT (sizeof(plane_data) / sizeof(plane_data[0]))  // 结果为100

/**
 * @brief 
 */
void Init_Test_Data(void)
{
    Plane_information* head = NULL;
    Plane_information* tail = NULL;

    for (int i = 0; i < PLANE_COUNT; i++)
     {
        Plane_information* node = (Plane_information*)malloc(sizeof(Plane_information));
        if (!node) 
        {
            free(node);
            return;
        }

        // 复制静态数据
        strcpy(node->id, plane_data[i].id);
        node->whole_seat = plane_data[i].whole_seat;
        node->rest_seat = plane_data[i].rest_seat;
        node->prize = plane_data[i].prize;
        strcpy(node->starting_point, plane_data[i].starting_point);
        strcpy(node->destination, plane_data[i].destination);
        memcpy(node->take_off_time, plane_data[i].take_off_time, sizeof(node->take_off_time));
        memcpy(node->landing_time, plane_data[i].landing_time, sizeof(node->landing_time));

        node->num = ++g_planeCount;
        node->next = NULL;

        // 链接到链表//运用双指针添加链表，避免从头查到尾，好方法啊，按照这个思路可以优化查找的部分
        if (head == NULL) 
        {
            head = node;
            tail = node;
        } 
        else 
        {
            tail->next = node;
            tail = node;
        }
     }

    g_head = head;
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
 * @param 窗口句柄
 * @param 不知
 * @param 控件ID
 * @param ？
 * @return ？
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CREATE:
        {
            Show_Background(hwnd);
            // 显示登录界面
            ShowLoginWindow(hwnd);
            
            return 0;
        }
        //按钮，编辑框被点击双击时触发，即控件(按钮，编辑框)向父窗口发出消息时 
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);//获取控件ID以判断是什么触发了WM_COMMAND
            
            //修改账户信息的封装
            Chang_Account_Function(wmId,hwnd);
                         
            //注册_登录_登出代码
            Login_Logout_Rejister(wmId, hwnd);

            // 管理员功能按钮
            // 在 final_test.c 的 WindowProc 函数中，找到管理员功能按钮的处理部分
// 在 ID_BUTTON_DELETE_PLANE 的处理之前添加以下代码

            if(wmId == ID_BUTTON_ADD_PLANE)
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
    else if(wmId==ID_BUTTON_ADD_PASSENGERS)
    {
        Play_Button_Sound();
        Add_New_Passengers_Window(hwnd);
    }
    else if (wmId==ID_BUTTON_ADD_CONFIRM)//有bug要调
    {
        Play_Button_Sound();
        Add_Passenger(hwnd,Now_Account);
    }
    else if(wmId==ID_BUTTON_ADD_CANCLE)
    {
        Play_Button_Sound();
        Cancel_Passenger(hwnd,Now_Account);
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

void Login_Logout_Rejister(int wmId,HWND hwnd)
{

     
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
 
}