#pragma once
/*
 * @Author: 林鹏飞
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

// 字体颜色
#define ForeColorIndex 7
// 背景颜色
#define BackColorIndex 0

//初始化服务员链表
waitor* WaitorListHead;
Adminnode* adminListHead;
waitor* currentWaitor;
foodnode* foodsListHead;
ordernode* OrderListHead; //系统当前未结账订单头结点
Order CurrentOrder;
tablenode* tablesListHead;

bool initializeSystem(int argc, char const* argv[]);
//设置光标位置
void gotoxy(int x, int y);
//获取光标位置x
int wherex();
//获取光标的位置y
int wherey();
//如果传入的指针是NULL那么就报错并结束程序
void if_Is_Null_Then_End_Program(void* ptr);

// 控制台颜色
void color(const unsigned short textColor);
//设置字体前景色和背景色
void SetColor();

#endif /* __CORE_SYSTEM_H_ */