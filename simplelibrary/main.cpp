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

void SetScreenGrid()//可以设置行数列数和背景颜色的函数
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
void SetSysCaption()//在控制台的标题栏上显示sample信息，控制台的标题栏信息可以使用title命令来设置
{
	system("title Sample");
}
void ClearScreen()//清屏函数
{
	system("cls");
}
void SetSysCaption(const char* pText)//实现在控制台的标题栏上显示指定的字符
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}
void ShowWelcome()//在屏幕中间显示欢迎信息
{
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "**************" << endl;
	cout << setw(40);
	cout << "图书管理系统" << endl;
	cout << setw(40);
	cout << "**************" << endl;
}
void ShowRootMenu()//显示系统主菜单
{
	cout << setw(40);
	cout << "请选择功能" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 添加新书" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 浏览书库" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 删除图书" << endl;
}
void WaitUser()//当程序完成一定后，等待用户选择返回主菜单还是退出系统的函数
{
	int iInputPage = 0;
	cout << "enter返回主菜单，q退出本系统" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
	system("exit");
}

int GetSelect()//获取用户输入的选择
{
	char buf[256];
	gets_s(buf,256);
	return atoi(buf);
}
void GuideInput()//用于让用户录入图书信息的函数，然后构建一个CBook类对象
{
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "请输入书名" << endl;
		cin >> inName;
	cout << "请输入ISBN编号" << endl;
		cin >> inIsbn;
	cout << "请输入价格" << endl;
		cin >> inPrice;
	cout << "请输入坐着" << endl;
		cin >> inAuthor;
	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriteData();
	cout << "录入成功" << endl;
	WaitUser();
}
long GetFileLength(ifstream & ifs)//获取文件长度
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}
void ViewData(int iSelPage = 1)//按页数显示图书信息，每页显示20条
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];//存储书名的变量
	char inIsbn[NUM1];//存储编号的变量
	char inPrice[NUM2];//存储价格的变量
	char inAuthor[NUM2];//存储作者名字的变量
	bool bIndex = false;//标志位，用来判断图书数量是否合理
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile; //定义输入文件类对象
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);//获取文件长度
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;

	ClearScreen();//清楚屏幕信息

	cout << "共有记录 " << iDataCount << " 条 ";
	cout << "共有页数 " << iDataCount << " 页 ";
	cout << "当前页数为第 " << iDataCount << " 页  ";
	cout << "n 显示下一页 m 返回" << endl;
	cout << setw(5) << "Index";
	cout << setw(22) << "Name" << setw(22) << "Isbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;
	try
	{
		//根据图书记录编号查找在文件中的位置
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
				ifile.read(inName, NUM1);//读取图书名称
				cout << setw(24) << inName;
				ifile.read(inIsbn, NUM1);//读取ISBN图书编号
				cout << setw(24) << inIsbn;
				ifile.read(inPrice, NUM2);//获取图书价格
				cout << setw(12) << inPrice;
				ifile.read(inAuthor, NUM2);//获取作者名字
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
		throw "文件发生错误";//抛出异常
		ifile.close();//异常出现后关闭文件流
	}
	if (iCurPage < iPage)
	{
		iCurPage = iCurPage + 1;
		WaitView(iCurPage);//等待用户处理
	}
	else
	{
		WaitView(iCurPage);//等待用户处理
	}
	ifile.close();
}

void DeleteBookFromFile()//删除图书数据
{
	int iDelCount;
	cout << "Input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "Delete Finish" << endl;
	WaitUser();
}
void WaitView(int iCurPage)//查看图书时允许的操作
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
void mainloop()//主循环函数
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
	SetSysCaption("图书管理系统1.0");
	mainloop();
}