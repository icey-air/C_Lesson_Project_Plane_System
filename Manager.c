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