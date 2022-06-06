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

enum UserType { undefine, Waiter, Administrator };
bool initializeSystem(int argc, char const* argv[]);
//设置光标位置
void gotoxy(int x, int y);
//获取光标位置x
int wherex();
//获取光标的位置y
int wherey();
//如果传入的指针是NULL那么就报错并结束程序
void if_Is_Null_Then_End_Program(void* ptr);

#endif /* __CORE_SYSTEM_H_ */