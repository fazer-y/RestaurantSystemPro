#define _CRT_SECURE_NO_WARNINGS
#include "UI.h"

void ShowWelcomeUI()
{
    int typeInput = 0;
    while (true)
    {
        system("cls");
        printf("################## з�������� ##################\n\n");
        printf("\t\t��ѡ���������\n\n\n");
        printf("\t\t1) ����Ա��¼.\n\n");
        printf("\t\t2) ϵͳ����Ա��¼.\n\n");
        printf("\t\t3) �˳�ϵͳ.\n\n");
        printf("�����������ݶ�Ӧ�����: [ ]\b\b");
        scanf("%d", &typeInput);
        if (typeInput == 1)
        {
            ShowWaitorLoginUI();
        }
        else if (typeInput == 2)
        {
            printf("########## з�������� ##########\n\n");
            ShowAdminLoginUI(adminListHead);
        }
        else
        {
            system("cls");
            printf("\n\n\n\n\n\n\t\t\t  ��л����ʹ�ã�\n\n\n\n\n\n");
            exit(1);
        }
    }
}