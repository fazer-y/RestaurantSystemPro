#pragma once
/*
 * @Author: ������
 * @ID: 202000810047
 * @Date: 2022-05-30
 * @LastEditors: LAPTOP-3VNCP688
 * @Description:
 */

# ifndef __UI_H_
# define __UI_H_

#include "Core_System.h"
#include "Core_Administrater.h"
#include "Core_Waitor.h"

 // ��ʾ������
int ShowMainUI();

// ��ʾ��ӭ���棬���ص�¼�û�����{Admin, User}
enum UserType ShowWelcomeUI();

// 

// ������뻺����
void clearScreenBuffer(void);

#define MAX 1000

# endif 