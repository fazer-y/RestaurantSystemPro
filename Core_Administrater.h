#pragma once
#include "Core_System.h"
#include "Core_Type.h"


//��ʼ��һ����ͷ����ϵͳ����Ա����
Adminnode* InitAdminTable();
//���һ��ϵͳ����Ա���ݵ�һ���������� ����ϵͳ����Ա�����������
Adminnode* addAdminByOrder(Adminnode* pHead, struct Admin data);
//������˳���ӡϵͳ����Ա��Ϣ�������ϵͳ����Ա��Ϣ��
void printAdminTable(Adminnode* pHead);
//�����������Ƿ��ж�ӦID�Ĺ���Ա
Adminnode* findAdminByID(Adminnode* pHead, char* ID);
//����ID����ϵͳ����Ա��Ϣ
Adminnode* updateAdminByID(Adminnode* pHead, char* ID, struct Admin data);

//���ļ��ж�ȡ����Ա��Ϣ(�൱�ڴ������������)
Adminnode* readAdminFromFile();
//�������й���Ա��Ϣд���ļ�
bool writeAdminIntoFile(Adminnode* pHead);

//ϵͳ����Ա��¼
void ShowAdminLoginUI(Adminnode* pHead);
//ϵͳ����Ա������
void ShowAdminMainUI(Adminnode* pHead);
void ShowUserManageUI(Adminnode* pHead);
//�û�����
void showAdminManageUI(Adminnode* pHead);
//����Ա��Ϣ����
void addAdminUI(Adminnode* pHead);
void findAdminUI(Adminnode* pHead);
void updateAdminUI(Adminnode* pHead);

//ͳ�Ʒ���
void showcensusUI(foodnode* pHead);