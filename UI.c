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
        printf("################## 蟹堡王餐厅 ##################\n\n");
        printf("\t\t请选择您的身份\n\n\n");
        printf("\t\t1) 服务员登录.\n\n");
        printf("\t\t2) 系统管理员登录.\n\n");
        printf("请输入你的身份对应的序号: [ ]\b\b");
        scanf("%d", &typeInput);
        clearScreenBuffer();
        system("cls");
        if (typeInput == 1)
        {
            ShowWaitorLoginUI();
        }
        else if (typeInput == 2)
        {
            printf("########## 蟹堡王餐厅 ##########\n\n");
            ShowAdminLoginUI(adminListHead);
        }
    }
    return userType;
}