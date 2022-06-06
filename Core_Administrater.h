#pragma once
/*
 * @Author: ����
 * @ID: 202000810081
 * @Date: 2022-05-31
 * @LastEditors: LAPTOP-44TSMLLA
 * @Description:��Դ�����ļ���¼��ϵͳ����Ա�����������������Ҫ�õ��������������ļ����������������󲿷�UI������ƺ�����������������Ϊ������
 */
#ifndef __CORE_ADMINISTRATER_H_
#define __CORE_ADMINISTRATER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "Core_Type.h"



 //���ϵͳ����Ա��Ϣ���ı��ĵ�
#define ADMIN_FILE_PATH "admin.txt"

//���ʳƷ��Ϣ���ı��ĵ�
#define FOOD_FILE_PATH "menu.txt"



//��ʼ������Ա����
waitor* WaitorListHead;
Adminnode* adminListHead;
waitor* currentWaitor;
foodnode* foodsListHead;
ordernode* OrderListHead; //ϵͳ��ǰδ���˶���ͷ���
Order CurrentOrder;
seat**  SeatsMap;




//��ʼ��һ����ͷ����ϵͳ����Ա����
Adminnode* InitAdminTable();
//����һ��ϵͳ����Ա���ݵ�һ���������� ����ϵͳ����Ա�����������
Adminnode* addAdminByOrder(Adminnode* pHead, struct Admin data);
//������˳���ӡϵͳ����Ա��Ϣ���������ϵͳ����Ա��Ϣ��
void printAdminTable(Adminnode* pHead);
//�����������Ƿ��ж�ӦID�Ĺ���Ա
Adminnode* findAdminByID(Adminnode* pHead, char* ID);
//����ID����ϵͳ����Ա��Ϣ
Adminnode* updateAdminByID(Adminnode* pHead, char* ID, struct Admin data);

//���ļ��ж�ȡ����Ա��Ϣ(�൱�ڴ�������������)
Adminnode* readAdminFromFile();
//�������й���Ա��Ϣд���ļ�
bool writeAdminIntoFile(Adminnode* pHead);

//��ö�����͵Ĳ�Ʒ��Ϣת��Ϊ�ַ����Ա����
char* switchenumtos(enum foodType type);
//���ַ�������ת��Ϊö�������Ա�ʳƷ¼��
enum foodType switchstoenum(char* type);
//��ʼ��һ����ͷ����ʳ������
foodnode* InitfoodTable();
//����һ��ʳƷ��Ϣ��һ��������β����
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

//���ļ��ж�ȡʳ����Ϣ(�൱�ڴ�������������)
foodnode* readfoodFromFile(foodnode* pHead);
//��������ʳ����Ϣд���ļ�
bool writefoodIntoFile(foodnode* pHead);

//���ݷ���Ա�ķ������õ�һ�������������������
waitor* orderWaitorbycount();   
//-->Ӧ��������������˵����⣬���������Ҳ�����
// ���޸���

//����ϵͳ����ԱUI����
//ϵͳ����Ա��¼
void ShowAdminLoginUI(Adminnode* pHead);
//ϵͳ����Ա������
void ShowAdminMainUI(Adminnode* pHead);
void ShowUserManageUI(Adminnode* pHead);
//�û�����
void showAdminManageUI(Adminnode* pHead);
void showWaitorManageUI(Adminnode* pHead);
//����Ա��Ϣ����
void addAdminUI(Adminnode* pHead);
void findAdminUI(Adminnode* pHead);
void updateAdminUI(Adminnode* pHead);
//����Ա��Ϣ����
void AddWaitorToList(char* name, char* passwd, int sumofserve);
void DeleteWaitorOfList(char* name);
void UpdateWaitorsInfo();
//������Ա�ļ��е���Ϣ��������
void LoadWaitors();
waitor* getWaitorByName(char* name);
//���ķ���Ա��ϢUI
void UpdateWaitorsNode();
void PrintfWaitorsInfo();

//�˵�����
void showAdminfoodUI(foodnode* fHead);
void addfoodUI(foodnode* pHead);
foodnode* findfoodUI(foodnode* pHead);
void updatefoodUI(foodnode* pHead);


//ͳ�Ʒ���
void showcensusUI(foodnode* pHead);   //����ĵڶ������ܳ����˵�����
// ���޸�

// ��λ����


#endif