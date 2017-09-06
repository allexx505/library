#pragma once
#define NUM1 128
#define NUM2 50
class CBook//����ͼ�����
{
public:
	CBook() {}
	CBook(char* cName, char* cIsbn, char* cPrice, char*cAuthor);
	~CBook(){}
public:
	char* GetName();
	void SetName(char* cName);//��ȡ�Լ���������
	char* GetIsbn();
	void SetIsbn(char* cIsbn);//��ȡ�Լ����ñ��
	char* GetPrice();
	void SetPrice(char* cPrice);//��ȡ�Լ����ü۸�
	char* GetAuthor();
	void SetAuthor(char* cAuthor);//��ȡ�Լ���������
	void WriteData();
	void DeleteData(int iCount);
	void GetBookFromFile(int iCount);
protected:
	char mcName[NUM1];
	char mcIsbn[NUM1];
	char mcPrice[NUM2];
	char mcAuthor[NUM2];
};