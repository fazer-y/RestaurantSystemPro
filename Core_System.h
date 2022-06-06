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

enum UserType { undefine, Waiter, Administrator };
bool initializeSystem(int argc, char const* argv[]);
//���ù��λ��
void gotoxy(int x, int y);
//��ȡ���λ��x
int wherex();
//��ȡ����λ��y
int wherey();
//��������ָ����NULL��ô�ͱ�����������
void if_Is_Null_Then_End_Program(void* ptr);

#endif /* __CORE_SYSTEM_H_ */