#pragma once
#include "Core_System.h"
#include "Core_Type.h"


// ����Ա������
void ShowWaitorMainUI();

// ����Ա��¼����
void ShowWaitorLoginUI();

// �˳�����Ա������
void ExitWaitorMainUI();

// ���·���Ա��Ϣ
void UpdateWaitorsNode();
// ��֤����Ա��¼
int CheckPasswd(char* name, char* passwd);
// ��ӷ���Ա���
void AddWaitorToList(char* name, char* passwd, int sumofserve);
// ���·���Ա��Ϣ���ļ�
void UpdateWaitorsInfo();

//���ݷ���Ա�ķ������õ�һ�������������������
waitor* orderWaitorbycount();

// �������Ա��Ϣ
void PrintfWaitorsInfo();
// ɾ������Ա���
void DeleteWaitorOfList(char* name);

//����Ա��Ϣ����
void AddWaitorToList(char* name, char* passwd, int sumofserve);
//������Ա�ļ��е���Ϣ��������
void LoadWaitors();

// ���������ҷ���Ա���
waitor* getWaitorByName(char* name);

//���ķ���Ա��ϢUI
void showWaitorManageUI(Adminnode* pHead);