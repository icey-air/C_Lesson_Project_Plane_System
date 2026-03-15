// #include "windows_Define.h"
// LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// /**
//  * @brief WinMain - 程序入口
//  */
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//                    LPSTR lpCmdLine, int nCmdShow)
// {
//     // 初始化测试数据（实际使用时可以注释掉）
//     Init_Test_Data();
    
//     const char CLASS_NAME[] = "FlightManagementSystem";
    
//     // 注册窗口类
//     WNDCLASS wc = {0};
//     wc.lpfnWndProc = WindowProc;
//     wc.hInstance = hInstance;
//     wc.lpszClassName = CLASS_NAME;
//     wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//     wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
//     RegisterClass(&wc);
    
//     // 创建主窗口
//     HWND hwnd = CreateWindowEx(
//         0, CLASS_NAME, "航班管理系统 - 请登录",
//         WS_OVERLAPPEDWINDOW,
//         CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
//         NULL, NULL, hInstance, NULL
//     );
    
//     if(hwnd == NULL) return 0;
    
//     g_hMainWindow = hwnd;
    
//     ShowWindow(hwnd, nCmdShow);
    
//     // 消息循环
//     MSG msg = {0};
//     while(GetMessage(&msg, NULL, 0, 0))
//     {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }
    
//     return 0;
// }

// /**
//  * @brief 显示登录界面
//  */
// void ShowLoginWindow(HWND hwnd)
// {
//     // 清除所有现有控件
//     HWND hChild = GetWindow(hwnd, GW_CHILD);
//     while(hChild != NULL)
//     {
//         HWND hNext = GetWindow(hChild, GW_HWNDNEXT);
//         DestroyWindow(hChild);
//         hChild = hNext;
//     }
    
//     // 创建登录界面控件
//     CreateWindow("STATIC", "用户名:", WS_CHILD | WS_VISIBLE,
//                  300, 200, 50, 25, hwnd, NULL, NULL, NULL);
    
//     CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
//                  360, 200, 150, 25, hwnd, (HMENU)ID_EDIT_USERNAME, NULL, NULL);
    
//     CreateWindow("STATIC", "密码:", WS_CHILD | WS_VISIBLE,
//                  300, 240, 50, 25, hwnd, NULL, NULL, NULL);
    
//     CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD,
//                  360, 240, 150, 25, hwnd, (HMENU)ID_EDIT_PASSWORD, NULL, NULL);
    
//     CreateWindow("BUTTON", "管理员登录", WS_CHILD | WS_VISIBLE,
//                  300, 280, 100, 30, hwnd, (HMENU)ID_BUTTON_ADMIN_LOGIN, NULL, NULL);
    
//     CreateWindow("BUTTON", "用户登录", WS_CHILD | WS_VISIBLE,
//                  410, 280, 100, 30, hwnd, (HMENU)ID_BUTTON_USER_LOGIN, NULL, NULL);
    
//     CreateWindow("STATIC", "新用户注册:", WS_CHILD | WS_VISIBLE,
//                  300, 330, 80, 25, hwnd, NULL, NULL, NULL);
    
//     CreateWindow("STATIC", "电话:", WS_CHILD | WS_VISIBLE,
//                  300, 360, 50, 25, hwnd, NULL, NULL, NULL);
    
//     CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
//                  360, 360, 150, 25, hwnd, (HMENU)ID_EDIT_PHONE, NULL, NULL);
    
//     CreateWindow("BUTTON", "注册", WS_CHILD | WS_VISIBLE,
//                  360, 400, 80, 30, hwnd, (HMENU)ID_BUTTON_REGISTER, NULL, NULL);
// }