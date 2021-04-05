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
typedef struct bank			//���������û��ṹ��
{			 
	char name[5];		//���� 
	long long account;		//�˻��� 
	char password[6];		//���� 
	float money;		//��� 
	char idcard[18];	//���֤ 
	int flag=1;	
	char phone[11];
}Bank[MAXSIZE],CBank;
typedef struct bill			//���������û��ṹ��
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
int writeData();				//д���ļ�
int readData();					//��ȡ�ļ� 
int readData_Bill();			//д���˵��ļ� 
int writeData_Bill();			//��ȡ�˵��ļ� 
void Main_interface();			//������
void Open_account();			//���� 
void Del_account();				//���� 
long long Get_Account();		//���俨�� 
int Find_Account(long long Account);		//Ѱ�ҿ��� 
int Find_Password(int pos,char password[6]);		//Ѱ������ 
void Print_Account();			//��� 
void Out_money();				//ȡ�� 
void In_money();				//��� 
int Contrast_account_password(long long account,char password[6]);			//�ȶ��˺ź����� 
void Transfer_money();				//ת�� 
void Search_account();				//��ѯ�˻� 
void Print_Bill_account();			//��ӡ�˵� 
void Bill_account(int pos,int symbol,float money);			//�˵� 
void Sort_Account();			//���� 
int Find_Bill(long long Account);
long long initID=10000001;
//**������**// 
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
	printf("\t\t�𾴵��û����ã���ӭʹ�����д洢ϵͳ\n\n");
    printf("\t\t=================================\n");
    printf("\t\t|=1 ����               2 ����===|\n");
    printf("\t\t|=3 ȡ��               4 ���===|\n");
    printf("\t\t|=5 ��ѯ               6 �˵�===|\n");
    printf("\t\t|=7 ת��               8 ����===|\n");
    printf("\t\t|=0 �˳�               0 �˳�===|\n");
    printf("\t\t=================================\n");
    printf("��������Ҫ������ָ��:");
    scanf("%d",&option);
    while(option)
	{
		if(option==1) Open_account();//���� 
		else if(option==2) Del_account();//����
		else if(option==3) Out_money();//ȡ��
		else if(option==4) In_money();//���
		else if(option==5) Search_account();//��ѯ 
		else if(option==6) Print_Bill_account();//�˵� 
		else if(option==7) Transfer_money();//ת��
		else if(option==8) Sort_Account();//���� 
		else printf("������Ŵ�������������\n");
		printf("\n������Ҫ���������\n");
		scanf("%d",&option); 
	}
}
//**��������**// 
void Open_account()
{
	char name[5],idcard[18];
	char password1[6],password2[6];
	char phone[11];
	CBank a;
	int i;
	printf("������ֿ��˵�����:\n");
	scanf("%s",name);
	printf("�����������ֻ���:\n");
	scanf("%s",phone);
	while(true)
	{
		if(strlen(phone)==11) break;
		else
		{
			printf("�����ֻ��������������������:\n");
			scanf("%s",phone);
		}
		for(int i=0;i<11;i++)
		{
			if(phone[i]>'9'&&phone[i]<'0')
			{
				printf("������ֻ��Ų��Ϸ�������������:\n");
				scanf("%s",phone);
			}
		}		
	}
	printf("�������������֤��;\n");
	scanf("%s",idcard);
	while(true)
	{
		if(strlen(idcard)==18) break;
		else
		{
			printf("�������֤�����������������:\n");
			scanf("%s",idcard);
		}
		for(int i=0;i<17;i++)
		{
			if(idcard[17]=='X'||idcard[17]=='x'||(idcard[17]<='9'&&idcard[17]>='0')) 
			{
				if(idcard[i]>'9'&&idcard[i]<'0')
				{
					printf("��������֤���Ϸ�������������:\n");
					scanf("%s",idcard);
				}
			}
			else
			{
				printf("��������֤���Ϸ�������������:\n");
				scanf("%s",idcard);
			}			
		}
	}
	printf("����������:\n");
	scanf("%s",password1);
	printf("���ٴ������������ϱ���һ��:\n");
	scanf("%s",password2);
	if(strcmp(password1,password2)!=0)
	{
		printf("������������벻һ������������\n");
		Open_account();
	}
	else
	{
		//����Ϣ������������CBank�ı��� 		
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
		//��a��ʱ��ŵ�����Ľṹ��������	
		Storage[size]=a;
		size++;
		//��������˵���Ϣ 
		printf("\t\t=====================================================================================================\n");
		printf("\t\t|����   |����      |���֤                  |�ֻ���           |���               |״̬|����     ===|\n");
		printf("\t\t=====================================================================================================\n");
		printf("\t\t|%-7s|%-10lld|%-24s|%-17s|%-19.2f|%-4s|%-9s===|\n",a.name,a.account,a.idcard,a.phone,a.money,"����",a.password);
		printf("\t\t=====================================================================================================\n");
		writeData();
		printf("�����ɹ�,����������......\n");
		getch();
		system("cls");//���� 
		Main_interface();
	}
}
//**��������**// 
void Del_account()
{
    long long account;
    int pos,a;
    char password[7];
    printf("������Ҫ�����Ŀ���:\n");
    scanf("%lld",&account);
    pos=Find_Account(account);
    if(pos==-1)
    {
        printf("���������������ٴκ�ʵ������\n");
        Del_account();
    }
    else
    {
        printf("����������:\n");
        scanf("%s",password);
        if(strcmp(password,Storage[pos].password)==0)
        {
            int i=0;
            file=fopen("bank.txt","w");
            if(file==NULL)
            {
                printf("��ʧ��\n");
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
            printf("�����ɹ�,��1��������,��2����������\n");
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
            printf("���������������������\n");
            Del_account();
        }        
    }
	readData();
}
//**�Աȿ��ź���**// 
int Find_Account(long long Account)
{
    int i,pos=-1;
    for(i=0; i<size; i++)		//ѭ�����洢����Ϣĩβ 
    {
        if(Storage[i].account==Account) pos=i;       
    }
    return pos;
}
//**�Ա����뺯��**//
int Find_Password(int pos,char password[6])
{
	if(strcmp(password,Storage[pos].password)==0) return 1;
	else return -1;
}
//**�ȶԺ���**//
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
//**�˵��ԱȺ���**//
int Find_Bill(long long Account)
{
	int i,pos=-1;
    for(i=0; i<size; i++)		//ѭ�����洢����Ϣĩβ 
    {
        if(account_bill[i].account1==Account) pos=i;       
    }
    return pos;
} 
//**�������**//
void Print_Account(int pos,float a)
{
	float before_money;
	before_money=a;
	printf("\t\t===============================================================\n");
	printf("\t\t|����      |����ǰ���            |���               |״̬===|\n");
	printf("\t\t===============================================================\n");
	printf("\t\t|%-10lld|%-22.2f|%-19.2f|%-4s===|\n",Storage[pos].account,before_money,Storage[pos].money,"����");
	printf("\t\t===============================================================\n");
}		
//**�ļ�����Ⱥ���**// 
int readData()
{
	int i1=0;
	file=fopen("bank.txt","a+");
	if(file==NULL)
	{
		printf("��ʧ��\n");
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
    	printf("��ʧ��");
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
		printf("��ʧ��\n");
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
    	printf("��ʧ��");
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
//**���п��ŷ��亯��**// 
long long Get_Account()
{
	return initID++;
}
//**����**// 
void In_money()
{
	long long account;
	float money,before_money;
	int pos,a;
	char password[6];
	printf("������Ҫ���Ŀ���:\n");
	scanf("%lld",&account);
	printf("��������������:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account,password);
	before_money=Storage[pos].money;
	if(pos==-1)
	{
		printf("����������п��Ż����������,����������:\n");
		In_money();
	}
	else
	{
		printf("��������Ҫ���Ľ��:\n");
		scanf("%f",&money);
		if(money<=0)
		{
			printf("������Ϊ0,����������:\n");
			scanf("%f",&money);
		}
		else
		{
			Storage[pos].money+=money;
			int a1=1;
			Bill_account(pos,a1,money);
			Print_Account(pos,before_money);
			writeData();
			printf("���ɹ�,��������밴1,�����������밴0\n");
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
//**ȡ���**// 
void Out_money()
{
	long long account;
	float money,before_money;
	int pos,a;
	char password[6];
	printf("������Ҫȡ��Ŀ���:\n");
	scanf("%lld",&account);
	printf("��������������:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account,password);
	before_money=Storage[pos].money;
	if(pos==-1)
	{
		printf("����������п��Ż��������,����������:\n");
		In_money();
	}
	else
	{				
		printf("������Ҫȡ��Ľ��:\n");
		scanf("%f",&money);
		while(money<=0)
		{
			printf("�����ܵ�����0\n");
			printf("��1�������,��0����������\n");
			scanf("%d",&a);
			if(a==1) scanf("%f",&money);
			else if(a==0)
			{
				system("cls");
				Main_interface();
			}
		}
		if(Storage[pos].money<=0) printf("��������\n");		
		else
		{
			if(Storage[pos].money-money<0) printf("��������\n");
			else
			{
				Storage[pos].money-=money;
				printf("ȡ��ɹ�\n");
			} 
		}
		int a1=0;
		Bill_account(pos,a1,money);
		Print_Account(pos,before_money);
		writeData();		
		printf("��1�������,��0����������\n");
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
//**��ѯ����**// 
void Search_account()
{
	long long account;
	int pos,a;
	char password[6];
	printf("������Ҫ��ѯ�Ŀ���:\n");
	scanf("%lld",&account);
	printf("��������������:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account,password);
	if(pos==-1)
	{
		printf("����������п��Ŵ���,����������:\n");
		Search_account();
	}
	else
	{
		printf("\t\t========================================\n");
		printf("\t\t|����      |���               |״̬===|\n");
		printf("\t\t========================================\n");
		printf("\t\t|%-10lld|%-19.2f|%-4s===|\n",Storage[pos].account,Storage[pos].money,"����");
		printf("\t\t========================================\n");
		printf("������Ϣ������ʾ\n");
		printf("��1������ѯ,��0����������\n");
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
//**ת�˺���**// 
void Transfer_money()
{
	long long account1,account2;
	int pos,pos1,a;
	float money,before_money,before_money1;
	char password[6];
	printf("���������Ŀ���:\n");
	scanf("%lld",&account1);
	printf("��������������:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account1,password);
	before_money=Storage[pos].money;
	if(pos==-1)
	{
		printf("����������п��Ż��������,����������:\n");
		Transfer_money();
	}	
	else
	{
		printf("������Ҫ��Ҫת�˵��˻�:\n");
		scanf("%lld",&account2);
		pos1=Find_Account(account2);
		before_money1=Storage[pos1].money;
		while(pos1==-1)
		{
			printf("��Ҫת�˵Ŀ��Ų�����,����������:\n");
			scanf("%lld",&account2);
			pos1=Find_Account(account2);
		}
		printf("������Ҫת�˵Ľ��:\n");
		scanf("%f",&money);
		while(money<=0)
		{
			printf("����Ľ����������������\n");
			scanf("%f",&money);
		}
		if(Storage[pos].money<=0) printf("��������\n");		
		else
		{
			if(Storage[pos].money-money<0) printf("��������\n");
			else
			{
				Storage[pos].money-=money;
				printf("ת�˳ɹ�\n");
			} 
		}
		Storage[pos1].money+=money;
		int a1=1;int b=0;
		Bill_account(pos,b,money);		
		Bill_account(pos1,a1,money);
		Print_Account(pos,before_money);
		Print_Account(pos1,before_money1);
		writeData();
		printf("��1����ת��,��0����������\n");
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
////**������**// 
void Sort_Account()
{
	int a;
	printf("\t\t=====================================================================================================\n");
	printf("\t\t|����   |����      |���֤                  |�ֻ���           |���               |״̬|����     ===|\n");
	printf("\t\t=====================================================================================================\n");
	for(int i=0;i<size;i++)
	{
		printf("\t\t|%-7s|%-10lld|%-24s|%-17s|%-19.2f|%-4s|%-9s===|\n",Storage[i].name,Storage[i].account,Storage[i].idcard,Storage[i].phone,Storage[i].money,"����",Storage[i].password);
		printf("\t\t=====================================================================================================\n");
	}
	printf("��0����������\n");
	scanf("%d",&a);
	if(a==0)
	{
		system("cls");
		Main_interface();
	}	
}
//**�˵�����**//
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
//**����˵�����**//
void Print_Bill_account()
{
	int pos,pos1,j,a;
	long long account;char password[6];
	printf("������Ҫ��ѯ�˵����˻�:\n");
	scanf("%lld",&account);
	printf("��������������:\n");
	scanf("%s",password);
	pos=Contrast_account_password(account,password);
	if(pos==-1)
	{
		printf("����������п��Ż��������,����������:\n");
		Print_Bill_account();
	}
	else pos1=Find_Bill(account);	
	printf("\t\t============================================================\n");
	printf("\t\t|����      |֧��               |���               |״̬===|\n");
	printf("\t\t============================================================\n");
	for(j=0;j<account_bill[pos1].size1;j++)
	{
		printf("\t\t|%-10lld|%-19.2f|%-19.2f|%-4s===|\n",account_bill[pos1].account1,account_bill[pos1].money[j],account_bill[pos1].before_money[j],"����");
	}
	printf("��1������ѯ�˵�,��0����������\n");
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
