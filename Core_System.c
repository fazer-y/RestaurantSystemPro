#define _CRT_SECURE_NO_WARNINGS
#include "Core_System.h"
#include "Core_Administrater.h"

bool initializeSystem(int argc, char const* argv[])
{
    // ��������ϵͳ����Ա��Ϣ
    adminListHead = readAdminFromFile();

    // �������з���Ա��Ϣ
    LoadWaitors();

    // �������в�Ʒ��Ϣ
    LoadMyMenu();

    // ��������
    OrderListHead = (ordernode*)malloc(sizeof(ordernode));
    OrderListHead->next = NULL;

    //���ÿ���̨��С
    system("mode con cols=70 lines=40");
}

//������
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.X + 1);
}
//��ȡ����λ��y
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.Y + 1);
}
//���ù���λ��
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
