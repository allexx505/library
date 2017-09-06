#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<fstream>
#include"Book.h"

#define CMD_COLS 80
#define CMD_LINES 25
using namespace std;

void SetScreenGrid();
void ClearScreen();
void SetSysCaption();
void SetSysCaption(const char *pText);
void ShowWelcome();
void ShowRootMenu();
void WaitView(int  iCurPage);
void WaitUser();
void GuideInput();
int GetSelect();
long GetFileLength(ifstream & ifs);
void ViewData(int iSelPage);
void DeleteBookFromFile();
void mainloop();

void SetScreenGrid()//�����������������ͱ�����ɫ�ĺ���
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
void SetSysCaption()//�ڿ���̨�ı���������ʾsample��Ϣ������̨�ı�������Ϣ����ʹ��title����������
{
	system("title Sample");
}
void ClearScreen()//��������
{
	system("cls");
}
void SetSysCaption(const char* pText)//ʵ���ڿ���̨�ı���������ʾָ�����ַ�
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}
void ShowWelcome()//����Ļ�м���ʾ��ӭ��Ϣ
{
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "**************" << endl;
	cout << setw(40);
	cout << "ͼ�����ϵͳ" << endl;
	cout << setw(40);
	cout << "**************" << endl;
}
void ShowRootMenu()//��ʾϵͳ���˵�
{
	cout << setw(40);
	cout << "��ѡ����" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 �������" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 ������" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 ɾ��ͼ��" << endl;
}
void WaitUser()//���������һ���󣬵ȴ��û�ѡ�񷵻����˵������˳�ϵͳ�ĺ���
{
	int iInputPage = 0;
	cout << "enter�������˵���q�˳���ϵͳ" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
	system("exit");
}

int GetSelect()//��ȡ�û������ѡ��
{
	char buf[256];
	gets_s(buf,256);
	return atoi(buf);
}
void GuideInput()//�������û�¼��ͼ����Ϣ�ĺ�����Ȼ�󹹽�һ��CBook�����
{
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "����������" << endl;
		cin >> inName;
	cout << "������ISBN���" << endl;
		cin >> inIsbn;
	cout << "������۸�" << endl;
		cin >> inPrice;
	cout << "����������" << endl;
		cin >> inAuthor;
	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriteData();
	cout << "¼��ɹ�" << endl;
	WaitUser();
}
long GetFileLength(ifstream & ifs)//��ȡ�ļ�����
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}
void ViewData(int iSelPage = 1)//��ҳ����ʾͼ����Ϣ��ÿҳ��ʾ20��
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];//�洢�����ı���
	char inIsbn[NUM1];//�洢��ŵı���
	char inPrice[NUM2];//�洢�۸�ı���
	char inAuthor[NUM2];//�洢�������ֵı���
	bool bIndex = false;//��־λ�������ж�ͼ�������Ƿ����
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile; //���������ļ������
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);//��ȡ�ļ�����
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;

	ClearScreen();//�����Ļ��Ϣ

	cout << "���м�¼ " << iDataCount << " �� ";
	cout << "����ҳ�� " << iDataCount << " ҳ ";
	cout << "��ǰҳ��Ϊ�� " << iDataCount << " ҳ  ";
	cout << "n ��ʾ��һҳ m ����" << endl;
	cout << setw(5) << "Index";
	cout << setw(22) << "Name" << setw(22) << "Isbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;
	try
	{
		//����ͼ���¼��Ų������ļ��е�λ��
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)
			{
				memset(inName, 0, 128);
				memset(inIsbn, 0, 128);
				memset(inPrice, 0, 50);
				memset(inAuthor, 0, 50);
				if (bIndex)
					cout << setw(3) << ((iCurPage - 1) * 20 + i);
				ifile.read(inName, NUM1);//��ȡͼ������
				cout << setw(24) << inName;
				ifile.read(inIsbn, NUM1);//��ȡISBNͼ����
				cout << setw(24) << inIsbn;
				ifile.read(inPrice, NUM2);//��ȡͼ��۸�
				cout << setw(12) << inPrice;
				ifile.read(inAuthor, NUM2);//��ȡ��������
				cout << setw(12) << inAuthor;
				cout << endl;
				if (ifile.tellg() < 0)
					bIndex = false;
				else
					bIndex = true;
			}
		}
	}
	catch (...)
	{
		cout << "throw file exception" << endl;
		throw "�ļ���������";//�׳��쳣
		ifile.close();//�쳣���ֺ�ر��ļ���
	}
	if (iCurPage < iPage)
	{
		iCurPage = iCurPage + 1;
		WaitView(iCurPage);//�ȴ��û�����
	}
	else
	{
		WaitView(iCurPage);//�ȴ��û�����
	}
	ifile.close();
}

void DeleteBookFromFile()//ɾ��ͼ������
{
	int iDelCount;
	cout << "Input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "Delete Finish" << endl;
	WaitUser();
}
void WaitView(int iCurPage)//�鿴ͼ��ʱ����Ĳ���
{
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
		system("exit");
	if (buf[0] == 'm')
		mainloop();
	if (buf[0] == 'n')
		ViewData(iCurPage);
}
void mainloop()//��ѭ������
{
	ShowWelcome();
	while (1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch (GetSelect())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData();
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;
		}
	}
}
void main()
{
	SetScreenGrid();
	SetSysCaption("ͼ�����ϵͳ1.0");
	mainloop();
}