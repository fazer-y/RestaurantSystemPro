#pragma once
#include "Core_System.h"
#include "Core_Type.h"


//��ö�����͵Ĳ�Ʒ��Ϣת��Ϊ�ַ����Ա����
char* switchenumtos(enum foodType type);
//���ַ�������ת��Ϊö�������Ա�ʳƷ¼��
enum foodType switchstoenum(char* type);
//��ʼ��һ����ͷ����ʳ������
foodnode* InitfoodTable();
//���һ��ʳƷ��Ϣ��һ������β����
foodnode* addfood(foodnode* pHead, food data);
//���������ж�ӦID��ʳ�����ָ���ʳ�����ָ��
foodnode* findfoodByid(foodnode* pHead, char* ID);
//����id����ʳƷ����Ϣ
foodnode* updatefoodByid(foodnode* pHead, char* ID, food data);
//����ʳ��ı�������õ�һ�������������������
foodnode* orderfoodbycount(foodnode* pHead);
//����id�Ӳ˵���ɾ��ʳƷ
foodnode* deletefoodByID(foodnode* pHead, char* ID);
//��ʾ�˵�
void printfoodTable(foodnode* pHead);

//���ļ��ж�ȡʳ����Ϣ(�൱�ڴ������������)
foodnode* readfoodFromFile(foodnode* pHead);
//��������ʳ����Ϣд���ļ�
bool writefoodIntoFile(foodnode* pHead);

// ��ʾ�˵�
void ShowMenu();
// ���ļ�����˵�
void LoadMyMenu();
// ���������Ʒ��Ϣ
void Revereshow(foodnode* p);
// ����д�ز�Ʒ��Ϣ���ļ�
void ReWriteBackFood();
// ͨ��ID��ȡ��Ʒ�۸�
double getPriceoffood(char* id);
// ͨ��ID��ȡ��Ʒ����
char* getNameofFood(char* id);
// ���²�Ʒ�������
void UpdateCountofFood(char* id);

//�˵�����
void showAdminfoodUI(foodnode* fHead);
void addfoodUI(foodnode* pHead);
foodnode* findfoodUI(foodnode* pHead);
void updatefoodUI(foodnode* pHead);