#ifndef __WINDOWS_DEFINE_H
#define __WINDOWS_DEFINE_H

#define YES 1
#define NO 0
#define MAX_ACCOUNTS 100

#include <windows.h>
#include "plane.h"
#include <stdio.h>
// 控件ID定义
#define ID_BUTTON_ADMIN_LOGIN     1001  // 管理员登录按钮ID
#define ID_BUTTON_USER_LOGIN      1002  // 用户登录按钮ID
#define ID_BUTTON_REGISTER        1003  // 注册按钮ID
#define ID_BUTTON_ADD_PLANE       1004  // 添加航班按钮ID
#define ID_BUTTON_DELETE_PLANE    1005  // 删除航班按钮ID
#define ID_BUTTON_UPDATE_PLANE    1006  // 更新航班按钮ID
#define ID_BUTTON_SHOW_PLANE      1007  // 显示航班按钮ID
#define ID_BUTTON_BOOK_TICKET     1008  // 预定机票按钮ID
#define ID_BUTTON_CANCEL_BOOK     1009  // 取消预定按钮ID
#define ID_BUTTON_LIST_BOOK       1010  // 列出预定按钮ID
#define ID_BUTTON_LOGOUT          1011  // 登出按钮ID
#define ID_BUTTON_BACK            1012  // 返回按钮ID
#define ID_BUTTON_CONFIRM_ADD     1013  // 确认添加按钮ID
#define ID_BUTTON_CONFIRM_DELETE  1014  // 确认删除按钮ID
#define ID_BUTTON_CONFIRM_UPDATE  1015  // 确认更新按钮ID
#define ID_BUTTON_SEARCH_PLANE    1016  // 搜索航班按钮ID
#define ID_BUTTON_CHANGE_ACCOUNT  1017  // 更改用户信息ID
#define ID_BUTTON_REGISTER_COMFIRM 1018  // 注册确认按钮
#define ID_BUTTON_REGISTER_CANCLE 1019  // 注册取消按钮

#define ID_EDIT_ACCOUNT          2001  // 账户输入框ID
#define ID_EDIT_PASSWORD          2002  // 密码输入框ID
#define ID_EDIT_PHONE             2003  // 电话输入框ID
#define ID_EDIT_PLANE_ID          2004  // 航班号输入框ID
#define ID_EDIT_WHOLE_SEAT        2005  // 总座位数输入框ID
#define ID_EDIT_REST_SEAT         2006  // 剩余座位数输入框ID
#define ID_EDIT_PRIZE             2007  // 价格输入框ID
#define ID_EDIT_SEARCH_ID         2008  // 搜索航班号输入框ID
#define ID_EDIT_IDENTIEY_CARD     2009  // 用户身份证输入框ID
#define ID_EDIT_NAME              2010  // 用户姓名输入框ID
#define ID_EDIT_CHANGE_INFO       2011  // 用户信息修改ID
#define ID_EDIT_CHANGE_INFO_COMFIRM 2012    //用户修改信息确认ID
#define ID_EDIT_CHANGE_INFO_CANCLE  2013    //用户修改信息取消ID

#define ID_LIST_PLANE             3001  // 航班列表框ID
#define ID_LIST_BOOKING           3002  // 预定列表框ID

#define ID_STATIC_INFO            4001  // 预定信息显示静态文本框ID
#define ID_STATIC_INFO_1          4002  //测试用，预定信息显示静态文本框ID

                    

/////////白轩宇的添加////////////
// 在 windows_Define.h 的控件ID定义部分添加以下内容

#define ID_DIALOG_ADD_PLANE        5001  // 添加航班对话框ID
#define ID_EDIT_PLANE_ID_ADD       5002  // 添加航班-航班号输入框
#define ID_EDIT_WHOLE_SEAT_ADD     5003  // 添加航班-总座位数输入框
#define ID_EDIT_REST_SEAT_ADD      5004  // 添加航班-剩余座位数输入框
#define ID_EDIT_PRIZE_ADD          5005  // 添加航班-价格输入框
#define ID_EDIT_DEPARTURE_ADD       5006  // 添加航班-起点输入框
#define ID_EDIT_DESTINATION_ADD     5007  // 添加航班-终点输入框

// 起飞时间输入框
#define ID_EDIT_TAKEOFF_YEAR       5008
#define ID_EDIT_TAKEOFF_MONTH      5009
#define ID_EDIT_TAKEOFF_DAY        5010
#define ID_EDIT_TAKEOFF_HOUR       5011
#define ID_EDIT_TAKEOFF_MINUTE     5012

// 着陆时间输入框
#define ID_EDIT_LANDING_YEAR       5013
#define ID_EDIT_LANDING_MONTH      5014
#define ID_EDIT_LANDING_DAY        5015
#define ID_EDIT_LANDING_HOUR       5016
#define ID_EDIT_LANDING_MINUTE     5017

#define ID_BUTTON_CONFIRM_ADD_PLANE 5018  // 确认添加按钮
#define ID_BUTTON_CANCEL_ADD_PLANE  5019  // 取消添加按钮

///白轩宇的添加结束/////////

#define ID_BUTTON_SETTING           6001    //设置按钮

/// @param hwnd 
void ShowAdminWindow(HWND hwnd);
void ShowUserWindow(HWND hwnd);
void RefreshPlaneList(HWND hwnd);
extern HWND g_hMainWindow;  
void Show_Rejister_Window(HWND hwnd);
void Show_Account_Information_Change_Window(HWND hwnd);

extern struct tourist*Now_Account;

// HWND g_hMainWindow = NULL;重要的变量，暂时没有想好放哪里，就丢final_test.c了     --这玩意是啥来着？

#endif