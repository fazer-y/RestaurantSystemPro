#pragma once
/*
 * @Author: ������
 * @ID: 202000810047
 * @Date: 2022-05-30
 * @LastEditors: LAPTOP-3VNCP688
 * @Description:
 */

# ifndef __CORE_SYSTEM_H_
# define __CORE_SYSTEM_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>
#include "Core_foodManage.h"
#include "Core_orderManage.h"
#include "Core_tableManage.h"
#include "Core_Waitor.h"
#include "Core_Administrater.h"
#include "Core_Type.h"

// ������ɫ
#define ForeColorIndex 7
// ������ɫ
#define BackColorIndex 0

//��ʼ������Ա����
waitor* WaitorListHead;
Adminnode* adminListHead;
waitor* currentWaitor;
foodnode* foodsListHead;
ordernode* OrderListHead; //ϵͳ��ǰδ���˶���ͷ���
Order CurrentOrder;
tablenode* tablesListHead;

bool initializeSystem(int argc, char const* argv[]);
//���ù��λ��
void gotoxy(int x, int y);
//��ȡ���λ��x
int wherex();
//��ȡ����λ��y
int wherey();
//��������ָ����NULL��ô�ͱ�����������
void if_Is_Null_Then_End_Program(void* ptr);

// ����̨��ɫ
void color(const unsigned short textColor);
//��������ǰ��ɫ�ͱ���ɫ
void SetColor();

#endif /* __CORE_SYSTEM_H_ */