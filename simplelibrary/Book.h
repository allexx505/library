#pragma once
#define NUM1 128
#define NUM2 50
class CBook//定义图书的类
{
public:
	CBook() {}
	CBook(char* cName, char* cIsbn, char* cPrice, char*cAuthor);
	~CBook(){}
public:
	char* GetName();
	void SetName(char* cName);//获取以及设置书名
	char* GetIsbn();
	void SetIsbn(char* cIsbn);//获取以及设置编号
	char* GetPrice();
	void SetPrice(char* cPrice);//获取以及设置价格
	char* GetAuthor();
	void SetAuthor(char* cAuthor);//获取以及设置坐着
	void WriteData();
	void DeleteData(int iCount);
	void GetBookFromFile(int iCount);
protected:
	char mcName[NUM1];
	char mcIsbn[NUM1];
	char mcPrice[NUM2];
	char mcAuthor[NUM2];
};