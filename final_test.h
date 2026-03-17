#ifndef __FINAL_TEST_H
#define __FINAL_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "tourist.h"
#include "Ticket.h"
#include "Manager.h"
/*======================== 数据结构定义 ========================*/

/*======================== 常量定义 ========================*/

/*======================== 全局变量声明 ========================*/

extern int g_planeCount;                // 航班数量
extern tourist g_currentUser;           // 当前登录用户
extern int g_userType;                  // 用户类型：0-未登录，1-管理员，2-普通用户



/**
 * @brief 初始化测试数据（仅用于演示，实际使用时注释掉）
 */
void Init_Test_Data(void);
BOOL InputBox(HWND hwnd, char* prompt, char* result, int max_len);
#endif
