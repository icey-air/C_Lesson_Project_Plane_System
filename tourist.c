
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "tourist.h"

#define Tourist_LEN sizeof(struct tourist)



/*@breif	创造游客
* @param	无
* @return	头指针orNULL
*/
struct tourist* Register_Tourist(struct tourist*head)
{
	struct tourist* HEAD,* p1, * p2;
	char phone_number[12];
	char name[20];
	char Account[11];
	char Password1[21];
	char Password2[21];
	int id;
	//没有写中途跳出代码，同时还有中途跳出清空结构体成员或free的注意

	if(head!=NULL)//不是第一个注册账户//有bug
	{
		p1 = p2 = (struct tourist*)malloc(Tourist_LEN);//free问题
		head->next=p1;
		p1->next=NULL;
		printf("请输入注册账户(1~10)");
		scanf("%s",Account);
			while(Find_Tourist_Account(head,Account)!=NULL)//游客结构体中有重复的账户
			{
				printf("账户已存在，请重新输入(输入0退出)");//没有写跳出while代码
				scanf("%s",Account);
	
			}
			if(Account[0]=='0')
				{
					printf("已退出注册程序");
					return head;
				}
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

		strcpy(p1->Account,Account);
		strcpy(p1->password,Password2);
		printf("请输入手机号");//有无手机号重复注册问题，没有写
		scanf("%s",phone_number);
		strcpy(p1->phone_number,phone_number);
		printf("请输入名字");
		scanf("%s",name);
		strcpy(p1->name,name);
		printf("注册成功");
		return head;
	}
	else//第一个注册账户
	{
		printf("请输入注册账户(1~10)\n");
		scanf("%s",Account);

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
		
		p1 = p2 = (struct tourist*)malloc(Tourist_LEN);
		p1->next=NULL;
		head=p1;
		strcpy(p1->Account,Account);
		strcpy(p1->password,Password2);
		printf("请输入手机号和名字");
		scanf("%s %s",phone_number, name);
		strcpy(p1->phone_number,phone_number);
 		strcpy(p1->name, name);
		return head;
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

