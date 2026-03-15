
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "tourist.h"



/*@breif	创造游客
* @param	无
* @return	头指针orNULL
*/
struct tourist* Register_Tourist(HWND hwnd,struct tourist*head)
{
	MessageBox(hwnd, "妈的终于搞定了", "提示", MB_OK);	
	struct tourist* HEAD,* p1, * p2;
	char name[20];
	char Password1[21];
	char Password2[21];
	int id;
	
	char username[20] = "", Password[20] = "", phone[20] = "";
	
	

	if(head!=NULL)//不是第一个注册账户
	{
		GetDlgItemText(hwnd, ID_EDIT_USERNAME, username, 20);
		GetDlgItemText(hwnd, ID_EDIT_PASSWORD, Password, 20);
    	GetDlgItemText(hwnd, ID_EDIT_PHONE, phone, 20);

		p1 = p2 = (struct tourist*)malloc(Tourist_LEN);//free问题
		head->next=p1;
		p1->next=NULL;

		scanf("%s",username);
			while(Find_Tourist_Account(head,username)!=NULL)//游客结构体中有重复的账户
			{
				MessageBox(hwnd, "账户已存在，请重新输入", "提示", MB_OK);			

				GetDlgItemText(hwnd, ID_EDIT_USERNAME, username, 20);
				GetDlgItemText(hwnd, ID_EDIT_PASSWORD, Password, 20);
    			GetDlgItemText(hwnd, ID_EDIT_PHONE, phone, 20);	
			}
			//两次密码

		strcpy(p1->Account,username);
		strcpy(p1->password,Password);

		strcpy(p1->phone_number,phone);
	



		MessageBox(hwnd, "注册成功", "提示", MB_OK);	
		return head;
	}
	
	else//第一个注册账户
	{
		GetDlgItemText(hwnd, ID_EDIT_USERNAME, username, 20);
		GetDlgItemText(hwnd, ID_EDIT_PASSWORD, Password, 20);
    	GetDlgItemText(hwnd, ID_EDIT_PHONE, phone, 20);

		//两次密码

		p1 = p2 = (struct tourist*)malloc(Tourist_LEN);
		p1->next=NULL;
		head=p1;
		strcpy(p1->Account,username);
		strcpy(p1->password,Password);
		strcpy(p1->phone_number,phone);
		return head;
	}	
}	


//这个还可以更进一步，与Find_tourist_Account合用，甚至可以考虑要不要和管理员登录合并
/*@breif	登录账户
* @param	游客头指针
* @return	登录账号的游客指针orNULL
*/
struct tourist* Loging_Account(struct tourist*head)
{
	char Account[11];
	char Password[21];
	struct tourist*p;
	p=head;
	printf("正在登录,请输入账户和密码\n");
	scanf("%s %s",Account,Password);
	while(p->next!=NULL)
	{
		if(strcmp(Account,p->Account)==0&&strcmp(Password,p->password)==0)
		{
			printf("登录成功\n");
			return p;
		}
		p=p->next;
	}
	if(strcmp(Account,p->Account)==0&&strcmp(Password,p->password)==0)
	{
		printf("登录成功\n");
		return p;
	}
	else
	{
		printf("登录失败\n");
		return NULL;
	}
}


/*@breif	列举游客
* @param	游客头指针
* @return	无
*/
void List_Tourist(struct tourist* head)
{
	struct tourist *p1;
	p1  = head;
	if (head != NULL)
	{
		while (p1->next != NULL)
		{
			printf("Phone:%s NAME:%s\n", p1->phone_number, p1->name);
			p1 = p1->next;
		}
		printf("Phone:%s NAME:%s\n", p1->phone_number, p1->name);
	}
	
		
}


/*@breif	删除游客
* @param	游客头指针
*@param		id
* @return	头指针
*/
struct tourist* Remove_Tourist(struct tourist*head,int id)
{
	printf("DelDone");
	struct tourist*p1,*p2;
	if(head==NULL)
	{
		printf("head wrong");
	}
	else
	{
		p1=head;
		while(p1->next!=NULL&&p1->id!=id)
		{
			p2=p1;
			p1=p1->next;
		}
		if(p1->id==id)
		{
			if(p1==head)
			{
			head=p1->next;
			free(p1);
			}
			else
			{
			p2->next=p1->next;			
			free(p1);
			}
		}
	}
	return head;
}


/*@breif	修改游客信息 没写完
* @param	当前游客结构体地址
* @return	无
*/

//内容要改
void Change_tourist(struct tourist*Now_Account)
{
	int mod;
	printf("请输入您想修改的信息\n");
	printf("1:name\n2:Phone_number\n3:password\n");
	scanf("%d",mod);

	switch (mod)
	{
		case 1:
			char name[10];
			printf("请输入名字");
			scanf("%s",name);
			strcpy(Now_Account->name,name);
			break;
		case 2:
			Change_Phone_Number(Now_Account);
			break;
		case 3:
			Change_Password(Now_Account);
			break;
		default:
			break;

	}
}


/*@breif	查找游客账户
* @param	游客结构体头指针
* @param	查找的账户
* @return	找到对应账户的指针或者NULL
*/
struct tourist* Find_Tourist_Account(struct tourist* head,char Account[11])
{
	struct tourist*p;
	p=head;
	printf("查找有无重复账户");
	while(p->next!=NULL)
	{
		if(strcmp(Account,p->Account)==0)
		{
			printf("有");
			return p;
		}
		p=p->next;
	}
	if(strcmp(Account,p->Account)==0)
		{
			printf("有");
			return p;
		}
	else
	{
	printf("无");
	return NULL;
	}
}


/*@breif	查找游客手机号
* @param	游客结构体头指针
* @param	查找的手机号
* @return	找到对应手机号的游客结构体指针或者NULL
*/
struct tourist* Find_Tourist_PhoneNumber(struct tourist* head,char Phone_Number[12])
{
	struct tourist*p;
	p=head;
	printf("查找有无对应手机号");
	while (p->next!=NULL)
	{
		if(strcmp(Phone_Number,p->phone_number)==0)
		{
			printf("有");
			return p;
		}
		p=p->next;
	} 
	if(strcmp(Phone_Number,p->phone_number)==0)
		{
			printf("有");
			return p;
		}
	else
	{
		printf("无");
		return NULL;
	}
}	


/*@breif	修改游客密码
* @param	游客结构体头指针
* @return	无
*/
void Change_Password(struct tourist*Now_Account)
{
	char Password1[21];	
	char Password2[21];
	while(1)
			{
			printf("请输入密码");//没有写二次输入确定密码代码
			scanf("%s",Password1);
			printf("请再次确认密码");
			scanf("%s",Password2);
			if(strcmp(Password1,Password2)==0)
			{
				break;	
			}
			else
			{
				printf("两次密码不一致");
			}
			}
}

/*@breif	修改游客手机号
* @param	游客结构体头指针
* @return	无
*/
void Change_Phone_Number(struct tourist*Now_Account)
{
	char phone_number[12];
	printf("请输入手机号");
	scanf("%s",phone_number);
	strcpy(Now_Account->phone_number,phone_number);
}

