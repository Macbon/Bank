#define MAXSIZE 100
#include<iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#define BANK_FILE "bank.txt"
using namespace std;
typedef struct bank			//定义银行用户结构体
{			 
	char name[5];		//姓名 
	long long account;		//账户名 
	char password[6];		//密码 
	float money;		//金额 
	char idcard[18];	//身份证 
	int flag=1;	
	char phone[11];
}Bank[MAXSIZE],CBank;
typedef struct bill			//定义银行用户结构体
{			 
	long long account1;
	float money[MAXSIZE];
	int size1=0;
	float before_money[MAXSIZE];
}Bill[MAXSIZE];
Bill account_bill;
Bank Storage;
int size=0;
int size_bill=0;
int i2=0;
FILE *file,*fp;
int writeData();				//写入文件
int readData();					//读取文件 
int readData_Bill();			//写入账单文件 
int writeData_Bill();			//读取账单文件 
void Main_interface();			//主界面
void Open_account();			//开户 
void Del_account();				//销户 
long long Get_Account();		//分配卡号 
int Find_Account(long long Account);		//寻找卡号 
int Find_Password(int pos,char password[6]);		//寻找密码 
void Print_Account();			//输出 
void Out_money();				//取款 
void In_money();				//存款 
int Contrast_account_password(long long account,char password[6]);			//比对账号和密码 
void Transfer_money();				//转账 
void Search_account();				//查询账户 
void Print_Bill_account();			//打印账单 
void Bill_account(int pos,int symbol,float money);			//账单 
void Sort_Account();			//排序 
int Find_Bill(long long Account);
long long initID=10000001;
//**主函数**// 
int main()
{
	readData();
	readData_Bill();
	if(Storage[0].account==0) size=size-1;
	initID=initID+size;
	Main_interface();
	return 0;
}
void Main_interface()
{
	int option;
	printf("\t\t尊敬的用户您好，欢迎使用银行存储系统\n\n");
    printf("\t\t=================================\n");
    printf("\t\t|=1 开户               2 销户===|\n");
    printf("\t\t|=3 取款               4 存款===|\n");
    printf("\t\t|=5 查询               6 账单===|\n");
    printf("\t\t|=7 转账               8 排序===|\n");
    printf("\t\t|=0 退出               0 退出===|\n");
    printf("\t\t=================================\n");
    printf("请输入您要操作的指令:");
    scanf("%d",&option);
    while(option)
	{
		if(option==1) Open_account();//开户 
		else if(option==2) Del_account();//销户
		else if(option==3) Out_money();//取款
		else if(option==4) In_money();//存款
		else if(option==5) Search_account();//查询 
		else if(option==6) Print_Bill_account();//账单 
		else if(option==7) Transfer_money();//转账
		else if(option==8) Sort_Account();//排序 
		else printf("操作序号错误请重新输入\n");
		printf("\n请输入要操作的序号\n");
		scanf("%d",&option); 
	}
}
//**开户函数**// 
void Open_account()
{
	char name[5],idcard[18];
	char password1[6],password2[6];
	char phone[11];
	CBank a;
	int i;
	printf("请输入持卡人的姓名:\n");
	scanf("%s",name);
	printf("请输入您的手机号:\n");
	scanf("%s",phone);
	while(true)
	{
		if(strlen(phone)==11) break;
		else
		{
			printf("您的手机号输入错误，请重新输入:\n");
			scanf("%s",phone);
		}
		for(int i=0;i<11;i++)
		{
			if(phone[i]>'9'&&phone[i]<'0')
			{
				printf("输入的手机号不合法，请重新输入:\n");
				scanf("%s",phone);
			}
		}		
	}
	printf("请输入您的身份证号;\n");
	scanf("%s",idcard);
	while(true)
	{
		if(strlen(idcard)==18) break;
		else
		{
			printf("您的身份证输入错误，请重新输入:\n");
			scanf("%s",idcard);
		}
		for(int i=0;i<17;i++)
		{
			if(idcard[17]=='X'||idcard[17]=='x'||(idcard[17]<='9'&&idcard[17]>='0')) 
			{
				if(idcard[i]>'9'&&idcard[i]<'0')
				{
					printf("输入的身份证不合法，请重新输入:\n");
					scanf("%s",idcard);
				}
			}
			else
			{
				printf("输入的身份证不合法，请重新输入:\n");
				scanf("%s",idcard);
			}			
		}
	}
	printf("请输入密码:\n");
	scanf("%s",password1);
	printf("请再次输入密码与上保持一致:\n");
	scanf("%s",password2);
	if(strcmp(password1,password2)!=0)
	{
		printf("两次输入的密码不一致请重新输入\n");
		Open_account();
	}
	else
	{
		//将信息赋给定义类型CBank的变量 		
		a.account=Get_Account();
		if(a.account==Storage[size-1].account&&a.account!=10000001) a.account=a.account+1;
		for(i=0;i<size;i++)
		{
			if(a.account==Storage[i].account) a.account=a.account+1;
		}	
		a.money=0;
		strcpy(a.phone,phone);
		strcpy(a.name,name);
		strcpy(a.password,password1);
		strcpy(a.idcard,idcard);
		a.flag=1;
		//将a暂时存放到定义的结构体数组中	
		Storage[size]=a;
		size++;
		//输出开卡人的信息 
		printf("\t\t=====================================================================================================\n");
		printf("\t\t|姓名   |卡号      |身份证                  |手机号           |余额               |状态|密码     ===|\n");
		printf("\t\t=====================================================================================================\n");
		printf("\t\t|%-7s|%-10lld|%-24s|%-17s|%-19.2f|%-4s|%-9s===|\n",a.name,a.account,a.idcard,a.phone,a.money,"正常",a.password);
		printf("\t\t=====================================================================================================\n");
		writeData();
		printf("开卡成功,返回主界面......\n");
		getch();
		system("cls");//清屏 
		Main_interface();
	}
}
//**销户函数**// 
void Del_account()
{
    long long account;
    int pos,a;
    char password[7];
    printf("请输入要销户的卡号:\n");
    scanf("%lld",&account);
    pos=Find_Account(account);
    if(pos==-1)
    {
        printf("卡号输入有误，请再次核实后输入\n");
        Del_account();
    }
    else
    {
        printf("请输入密码:\n");
        scanf("%s",password);
        if(strcmp(password,Storage[pos].password)==0)
        {
            int i=0;
            file=fopen("bank.txt","w");
            if(file==NULL)
            {
                printf("打开失败\n");
                return ;
            }
            for(i=0; i<size; i++)
            {
                if(i==pos)
                {
                    continue;
                    i--;
                }
                if(i==size-1)
                {
                    fprintf(file,"%lld %s %s %s %s %.2f %d",Storage[i].account,Storage[i].name,Storage[i].phone,Storage[i].idcard,Storage[i].password,Storage[i].money,Storage[i].flag);
                }
                else
                {
                    fprintf(file,"%lld %s %s %s %s %.2f %d\n",Storage[i].account,Storage[i].name,Storage[i].phone,Storage[i].idcard,Storage[i].password,Storage[i].money,Storage[i].flag);
                }
            }
            size--;
            fclose(file);
            printf("销户成功,按1继续销户,按2返回主界面\n");
            scanf("%d",&a);
            if(a==1)
            {
                getch();
                system("cls");
                Del_account();
            }
            if(a==2)
            {
                system("cls");
                Main_interface();
            }
        }
        else if(strcmp(password,Storage[pos].password)!=0)
        {
            printf("密码输入错误，请重新输入\n");
            Del_account();
        }        
    }
	readData();
}
//**对比卡号函数**// 
int Find_Account(long long Account)
{
    int i,pos=-1;
    for(i=0; i<size; i++)		//循环到存储的信息末尾 
    {
        if(Storage[i].account==Account) pos=i;       
    }
    return pos;
}
//**对比密码函数**//
int Find_Password(int pos,char password[6])
{
	if(strcmp(password,Storage[pos].password)==0) return 1;
	else return -1;
}
//**比对函数**//
int Contrast_account_password(long long account,char password[6])
{
	int pos,pos1,pos2;
	pos1=Find_Account(account);
	pos2=Find_Password(pos1,password);
	if(pos1!=-1&&pos2!=-1)
	{
		pos=pos1;
		return pos;
	}
	else return -1;
}
//**账单对比函数**//
int Find_Bill(long long Account)
{
	int i,pos=-1;
    for(i=0; i<size; i++)		//循环到存储的信息末尾 
    {
        if(account_bill[i].account1==Account) pos=i;       
    }
    return pos;
} 
//**输出函数**//
void Print_Account(int pos,float a)
{
	float before_money;
	before_money=a;
	printf("\t\t===============================================================\n");
	printf("\t\t|卡号      |操作前余额            |余额               |状态===|\n");
	printf("\t\t===============================================================\n");
	printf("\t\t|%-10lld|%-22.2f|%-19.2f|%-4s===|\n",Storage[pos].account,before_money,Storage[pos].money,"正常");
	printf("\t\t===============================================================\n");
}		
//**文件处理等函数**// 
int readData()
{
	int i1=0;
	file=fopen("bank.txt","a+");
	if(file==NULL)
	{
		printf("打开失败\n");
		return 0;
	}
	while(!feof(file))
	{
		fscanf(file,"%lld %s %s %s %s %f %d\n",&Storage[i1].account,Storage[i1].name,Storage[i1].phone,Storage[i1].idcard,Storage[i1].password,&Storage[i1].money,&Storage[i1].flag);
		i1++;
		size++;		
	}
    fclose(file);
    return 1;
}
int writeData()
{
    int i;
    file=fopen("bank.txt","w+");
    if(file==NULL)
    {
    	printf("打开失败");
        return 0;
    }
    for(i=0; i<size; i++)
    {
        if(i==size-1)
        {
            fprintf(file,"%lld %s %s %s %s %.2f %d",Storage[i].account,Storage[i].name,Storage[i].phone,Storage[i].idcard,Storage[i].password,Storage[i].money,Storage[i].flag);
        }
        else
        {
            fprintf(file,"%lld %s %s %s %s %.2f %d\n",Storage[i].account,Storage[i].name,Storage[i].phone,Storage[i].idcard,Storage[i].password,Storage[i].money,Storage[i].flag);
        }
    }
    fclose(file);
    return 1; 
}
int readData_Bill()
{
	int i1=0,j;
	fp=fopen("bill.txt","a+");
	if(fp==NULL)
	{
		printf("打开失败\n");
		return 0;
	}
	
	while(!feof(fp))
	{	
		fscanf(fp,"%lld %f %f %d\n",&account_bill[i1].account1,&account_bill[i1].money[0],&account_bill[i1].before_money[0],&account_bill[i1].size1);
		for(j=1;j<account_bill[i1].size1;j++)
		{
			fscanf(fp,"%lld %f %f %d\n",&account_bill[i1].account1,&account_bill[i1].money[j],&account_bill[i1].before_money[j],&account_bill[i1].size1);
			size_bill++;
		}
		i1++;				
	}
	fclose(fp);
    return 1;
}
int writeData_Bill()
{
	int i,j;
    fp=fopen("bill.txt","w+");
    if(fp==NULL)
    {
    	printf("打开失败");
        return 0;
    }
    for(i=0;i<size;i++)
    {
    	for(j=0;j<account_bill[i].size1;j++)
		{
			if(i==size_bill-1)
        	{
            	fprintf(fp,"%lld %.2f %.2f %d\n",account_bill[i].account1,account_bill[i].money[j],account_bill[i].before_money[j],account_bill[i].size1);
        	}
        	else
        	{
            	fprintf(fp,"%lld %.2f %.2f %d\n",account_bill[i].account1,account_bill[i].money[j],account_bill[i].before_money[j],account_bill[i].size1);
        	}
		}        
    }
    fclose(fp);
    return 1; 
}
//**银行卡号分配函数**// 
long long Get_Account()
{
	return initID++;
}
//**存款函数**// 
void In_money()
{
	long long account;
	float money,before_money;
	int pos,a;
	char password[6];
	printf("请输入要存款的卡号:\n");
	scanf("%lld",&account);
	printf("请输入您的密码:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account,password);
	before_money=Storage[pos].money;
	if(pos==-1)
	{
		printf("您输入的银行卡号或者密码错误,请重新输入:\n");
		In_money();
	}
	else
	{
		printf("请输入您要存款的金额:\n");
		scanf("%f",&money);
		if(money<=0)
		{
			printf("存款金额不能为0,请重新输入:\n");
			scanf("%f",&money);
		}
		else
		{
			Storage[pos].money+=money;
			int a1=1;
			Bill_account(pos,a1,money);
			Print_Account(pos,before_money);
			writeData();
			printf("存款成功,继续存款请按1,返回主界面请按0\n");
			scanf("%d",&a);
			if(a==1)
			{
				system("cls");
				In_money();
			}
			else if(a==0)
			{
				system("cls");
				Main_interface();
			}
		}
	}
}
//**取款函数**// 
void Out_money()
{
	long long account;
	float money,before_money;
	int pos,a;
	char password[6];
	printf("请输入要取款的卡号:\n");
	scanf("%lld",&account);
	printf("请输入您的密码:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account,password);
	before_money=Storage[pos].money;
	if(pos==-1)
	{
		printf("您输入的银行卡号或密码错误,请重新输入:\n");
		In_money();
	}
	else
	{				
		printf("请输入要取款的金额:\n");
		scanf("%f",&money);
		while(money<=0)
		{
			printf("存款金额不能的少于0\n");
			printf("按1继续存款,按0返回主界面\n");
			scanf("%d",&a);
			if(a==1) scanf("%f",&money);
			else if(a==0)
			{
				system("cls");
				Main_interface();
			}
		}
		if(Storage[pos].money<=0) printf("您的余额不足\n");		
		else
		{
			if(Storage[pos].money-money<0) printf("您的余额不足\n");
			else
			{
				Storage[pos].money-=money;
				printf("取款成功\n");
			} 
		}
		int a1=0;
		Bill_account(pos,a1,money);
		Print_Account(pos,before_money);
		writeData();		
		printf("按1继续存款,按0返回主界面\n");
		scanf("%d",&a);
		if(a==1)
		{
			system("cls");
			Out_money();
		}
		else if(a==0)
		{
			system("cls");
			Main_interface();
		}
	}
}
//**查询函数**// 
void Search_account()
{
	long long account;
	int pos,a;
	char password[6];
	printf("请输入要查询的卡号:\n");
	scanf("%lld",&account);
	printf("请输入您的密码:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account,password);
	if(pos==-1)
	{
		printf("您输入的银行卡号错误,请重新输入:\n");
		Search_account();
	}
	else
	{
		printf("\t\t========================================\n");
		printf("\t\t|卡号      |余额               |状态===|\n");
		printf("\t\t========================================\n");
		printf("\t\t|%-10lld|%-19.2f|%-4s===|\n",Storage[pos].account,Storage[pos].money,"正常");
		printf("\t\t========================================\n");
		printf("您的信息如上所示\n");
		printf("按1继续查询,按0返回主界面\n");
		scanf("%d",&a);
		if(a==1)
		{
			system("cls");
			Search_account();
		} 
		else if(a==0)
		{
			system("cls");
			Main_interface();
		}
	}
}
//**转账函数**// 
void Transfer_money()
{
	long long account1,account2;
	int pos,pos1,a;
	float money,before_money,before_money1;
	char password[6];
	printf("请输入您的卡号:\n");
	scanf("%lld",&account1);
	printf("请输入您的密码:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account1,password);
	before_money=Storage[pos].money;
	if(pos==-1)
	{
		printf("您输入的银行卡号或密码错误,请重新输入:\n");
		Transfer_money();
	}	
	else
	{
		printf("请输入要您要转账的账户:\n");
		scanf("%lld",&account2);
		pos1=Find_Account(account2);
		before_money1=Storage[pos1].money;
		while(pos1==-1)
		{
			printf("您要转账的卡号不存在,请重新输入:\n");
			scanf("%lld",&account2);
			pos1=Find_Account(account2);
		}
		printf("请输入要转账的金额:\n");
		scanf("%f",&money);
		while(money<=0)
		{
			printf("输入的金额有误请重新输入\n");
			scanf("%f",&money);
		}
		if(Storage[pos].money<=0) printf("您的余额不足\n");		
		else
		{
			if(Storage[pos].money-money<0) printf("您的余额不足\n");
			else
			{
				Storage[pos].money-=money;
				printf("转账成功\n");
			} 
		}
		Storage[pos1].money+=money;
		int a1=1;int b=0;
		Bill_account(pos,b,money);		
		Bill_account(pos1,a1,money);
		Print_Account(pos,before_money);
		Print_Account(pos1,before_money1);
		writeData();
		printf("按1继续转账,按0返回主界面\n");
		scanf("%d",&a);
		if(a==1)
		{
			system("cls");
			Transfer_money();
		}
		else if(a==0)
		{
			system("cls");
			Main_interface();
		}
	}
}
////**排序函数**// 
void Sort_Account()
{
	int a;
	printf("\t\t=====================================================================================================\n");
	printf("\t\t|姓名   |卡号      |身份证                  |手机号           |余额               |状态|密码     ===|\n");
	printf("\t\t=====================================================================================================\n");
	for(int i=0;i<size;i++)
	{
		printf("\t\t|%-7s|%-10lld|%-24s|%-17s|%-19.2f|%-4s|%-9s===|\n",Storage[i].name,Storage[i].account,Storage[i].idcard,Storage[i].phone,Storage[i].money,"正常",Storage[i].password);
		printf("\t\t=====================================================================================================\n");
	}
	printf("按0返回主界面\n");
	scanf("%d",&a);
	if(a==0)
	{
		system("cls");
		Main_interface();
	}	
}
//**账单函数**//
void Bill_account(int pos,int symbol,float money)
{
	int i;
	if(symbol!=1)
	{
		float sub_money;
		sub_money=-money;
		account_bill[pos].account1=Storage[pos].account;
		account_bill[pos].money[account_bill[pos].size1]=sub_money;
		account_bill[pos].before_money[account_bill[pos].size1]=Storage[pos].money;
		account_bill[pos].size1++;		
	}
	else
	{
		account_bill[pos].account1=Storage[pos].account;
		account_bill[pos].money[account_bill[pos].size1]=money;
		account_bill[pos].before_money[account_bill[pos].size1]=Storage[pos].money;
		account_bill[pos].size1++;				
	}
	size_bill++;
	writeData_Bill();
}
//**输出账单函数**//
void Print_Bill_account()
{
	int pos,pos1,j,a;
	long long account;char password[6];
	printf("请输入要查询账单的账户:\n");
	scanf("%lld",&account);
	printf("请输入您的密码:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account,password);
	if(pos==-1)
	{
		printf("您输入的银行卡号或密码错误,请重新输入:\n");
		Print_Bill_account();
	}
	else pos1=Find_Bill(account);	
	printf("\t\t============================================================\n");
	printf("\t\t|卡号      |支出               |金额               |状态===|\n");
	printf("\t\t============================================================\n");
	for(j=0;j<account_bill[pos1].size1;j++)
	{
		printf("\t\t|%-10lld|%-19.2f|%-19.2f|%-4s===|\n",account_bill[pos1].account1,account_bill[pos1].money[j],account_bill[pos1].before_money[j],"正常");
	}
	printf("按1继续查询账单,按0返回主界面\n");
	scanf("%d",&a);
	if(a==1)
	{
		system("cls");
		Print_Bill_account();
	}
	else if(a==0)
	{
		system("cls");
		Main_interface();
	}
}
