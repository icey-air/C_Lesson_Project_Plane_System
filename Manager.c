#include "Manager.h"

/*@brief	管理员登录
* @param	windows句柄
* @return	无
*/
void Manager_Login(HWND hwnd)
{
    char username[20], password[20];
    GetDlgItemText(hwnd, ID_EDIT_USERNAME, username, 20);
    GetDlgItemText(hwnd, ID_EDIT_PASSWORD, password, 20);
    
    if(strcmp(username, MANAGER_ACCOUNT) == 0 && strcmp(password, MANAGER_PASSWORD) == 0)
    {
        MessageBox(hwnd, "管理员登录成功", "提示", MB_OK);
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
    //或者呢，下方多传一个参数
    RefreshPlaneList(hwnd);
    return head;
}

