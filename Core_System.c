#define _CRT_SECURE_NO_WARNINGS
#include "Core_System.h"
#include "Core_Administrater.h"

bool initializeSystem(int argc, char const* argv[])
{
    // 读入所有系统管理员信息
    adminListHead = readAdminFromFile();

    // 读入所有服务员信息
    LoadWaitors();

    // 读入所有菜品信息
    LoadMyMenu();

    // 订单链表
    OrderListHead = (ordernode*)malloc(sizeof(ordernode));
    OrderListHead->next = NULL;

    //设置控制台大小
    system("mode con cols=70 lines=40");
}

//光标控制
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.X + 1);
}
//获取光标的位置y
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.Y + 1);
}
//设置光标的位置
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
