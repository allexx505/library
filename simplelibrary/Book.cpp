#include"Book.h"
#include<string>
#include<fstream>
#include<iostream>
#include<iomanip>

using namespace std;

CBook::CBook(char* cName, char* cIsbn, char* cPrice, char*cAuthor)		//图书类成员函数的实现
{
	strncpy(mcName, cName, NUM1);
	strncpy(mcIsbn, cIsbn, NUM1);
	strncpy(mcPrice, cPrice, NUM2);
	strncpy(mcAuthor, cAuthor, NUM2);
}
char* CBook::GetName()
{
	return mcName;
}
void CBook::SetName(char* cName)
{
	strncpy(mcName, cName, NUM1);
}
char* CBook::GetIsbn()
{
	return mcIsbn;
}
void CBook::SetIsbn(char* cIsbn)
{
	strncpy(mcIsbn, cIsbn, NUM1);
}
char* CBook::GetPrice()
{
	return mcPrice;
}
void CBook::SetPrice(char* cPrice)
{
	strncpy(mcPrice, cPrice, NUM2);
}
char* CBook::GetAuthor()
{
	return mcAuthor;
}
void CBook::SetAuthor(char* cAuthor)
{
	strncpy(mcAuthor, cAuthor, NUM2);
}

void CBook::WriteData()							//将图书对象写入到文件中
{
	ofstream ofile;
	ofile.open("book.dat", ios::binary | ios::app);
	try
	{
		ofile.write(mcName, NUM1);
		ofile.write(mcIsbn, NUM1);
		ofile.write(mcPrice, NUM2);
		ofile.write(mcAuthor, NUM2);
	}
	catch (...)
	{
		throw"文档发生错误";
		ofile.close();
	}
	ofile.close();
}

void CBook::GetBookFromFile(int iCount)//从文件中提取信息，构建类对象
{
	char cName[NUM1];
	char cIsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	try
	{
		ifile.seekg(iCount*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		ifile.read(cName, NUM1);
		if (ifile.tellg() > 0)
			strncpy(mcName, cName, NUM1);
		ifile.read(cIsbn, NUM1);
		if (ifile.tellg() > 0)
			strncpy(mcIsbn, cIsbn, NUM1);
		ifile.read(cPrice, NUM2);
		if (ifile.tellg() > 0)
			strncpy(mcPrice,cPrice,NUM2);
		ifile.read(cAuthor,NUM2);
		if (ifile.tellg() > 0)
			strncpy(mcAuthor,cAuthor,NUM2);
	}
	catch (...)
	{
		throw"文件出现错误";
		ifile.close();
	}
	ifile.close();
}

void CBook::DeleteData(int iCount)//删除图书数据，采用覆盖的方式来删除
{
	long respos;
	int iDataCount = 0;
	fstream file;
	fstream tmpfile;
	ofstream ofile;
	char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2];
	file.open("book.dat", ios::binary | ios::in | ios::out);
	tmpfile.open("temp.dat", ios::binary | ios::in | ios::out | ios::trunc);
	file.seekg(0, ios::end);
	respos = file.tellg();
	iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iCount<0 && iCount>iDataCount)
	{
		throw"输入数值超出限制范围";
	}
	else
	{
		file.seekg((iCount)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		for (int j = 0; j < (iDataCount - iCount);j++)
		{
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
			file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
			tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
		}
		file.close();
		tmpfile.seekg(0, ios::beg);
		ofile.open("book.dat");
		ofile.seekp((iCount - 1)*(NUM1 + NUM1 + NUM2 + NUM2),ios::beg);
		for (int i = 0; i < (iDataCount - iCount); i++)
		{
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
			tmpfile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
			ofile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
		}
	}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");
}
