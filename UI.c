#define _CRT_SECURE_NO_WARNINGS
#include "UI.h"
#include "CORE_System.h"
#include "Core_Waitor.h"
#include "Core_Administrater.h"

int ShowMainUI()
{
    printf("111");
    return 1;
}

void clearScreenBuffer(void)
{
    char c;
    while ((c = getchar()) != EOF && c != '\n');
}

enum UserType ShowWelcomeUI()
{
    enum UserType userType = undefine;
    int typeInput = 0;
    system("cls");
    while (!(userType == Administrator || userType == Waiter))
    {
        printf("################## з�������� ##################\n\n");
        printf("\t\t��ѡ���������\n\n\n");
        printf("\t\t1) ����Ա��¼.\n\n");
        printf("\t\t2) ϵͳ����Ա��¼.\n\n");
        printf("�����������ݶ�Ӧ�����: [ ]\b\b");
        scanf("%d", &typeInput);
        clearScreenBuffer();
        system("cls");
        if (typeInput == 1)
        {
            ShowWaitorLoginUI();
        }
        else if (typeInput == 2)
        {
            printf("########## з�������� ##########\n\n");
            ShowAdminLoginUI(adminListHead);
        }
    }
    return userType;
}