#define _CRT_SECURE_NO_WARNINGS
#include "UI.h"

void ShowWelcomeUI()
{
    int typeInput = 0;
    while (true)
    {
        system("cls");
        printf("################## 蟹堡王餐厅 ##################\n\n");
        printf("\t\t请选择您的身份\n\n\n");
        printf("\t\t1) 服务员登录.\n\n");
        printf("\t\t2) 系统管理员登录.\n\n");
        printf("\t\t3) 退出系统.\n\n");
        printf("请输入你的身份对应的序号: [ ]\b\b");
        scanf("%d", &typeInput);
        if (typeInput == 1)
        {
            ShowWaitorLoginUI();
        }
        else if (typeInput == 2)
        {
            printf("########## 蟹堡王餐厅 ##########\n\n");
            ShowAdminLoginUI(adminListHead);
        }
        else
        {
            system("cls");
            printf("\n\n\n\n\n\n\t\t\t  感谢您的使用！\n\n\n\n\n\n");
            exit(1);
        }
    }
}