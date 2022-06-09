#define _CRT_SECURE_NO_WARNINGS
#include "CORE_Waitor.h"

int CheckPasswd(char* name, char* passwd) 
{
    FILE* fp = fopen("WaitorsInfo.txt", "r");
    if (fp == NULL)
    {
        perror("文件读取失败");
        return 0;
    }
    //把日期先读走
    int year, month, day;
    fscanf(fp, "%d %d %d", &year, &month, &day);


    char nametest[WaitorName_MaxLength], passwdtest[WaitorPasswd_MaxLength];
    int sumofserve;
    while (3 == fscanf(fp, "%s %s %d", nametest, passwdtest, &sumofserve))
    {
        if (strcmp(nametest, name) == 0 && strcmp(passwdtest, passwd) == 0)
        {
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void ShowManageWaitorsUI()
{
    system("cls");
    printf("===================服务员管理界面=====================\n");
    while (true)
    {
        color(12);
        printf("\n(1)添加服务员\n(2)更新服务员\n(3)退出\n");
        color(7);
        printf("请输入操作序号 【  】");
        gotoxy(wherex() - 3, wherey());
        int index;
        scanf("%d", &index);
        switch (index)
        {
        case 1:
        {
            printf("\n请输入您要添加的服务员姓名 >>>_________");
            gotoxy(wherex() - 6, wherey());
            char name[WaitorName_MaxLength];
            scanf("%s", name);
            printf("\n请输入服务员登录密码 >>>_________");
            char passwd[WaitorPasswd_MaxLength];
            gotoxy(wherex() - 6, wherey());
            scanf("%s", passwd);
            AddWaitorToList(name, passwd, 0);
            UpdateWaitorsInfo();
        }
        break;
        case 2:
        {
            UpdateWaitorsNode();
        }
        break;
        default:
            return;
        }
    }
}

void ExitWaitorMainUI() {
    UpdateWaitorsInfo();
    ReWriteUnDoneOrders();
}

void ShowWaitorMainUI() {
    while (true) {
        system("cls");
        printf("***********************服务员主界面************************\n\n\n");
        printf("             ---------------------------------             \n\n");
        printf("            |        (1) 查看菜单             |            \n");
        printf("            |        (2) 点餐                 |            \n");
        printf("            |        (3) 查看订单             |            \n");
        printf("            |        (4) 结账                 |            \n");
        printf("            |        (5) 查看座位             |            \n");
        printf("            |        (6) 查看未结账订单        |            \n");
        printf("            |        (7) 退出                 |            \n");
        printf("             ---------------------------------             \n\n\n");
        printf("***********************************************************\n\n");
        printf("请选择操作序号 【  】");
        int x = wherex(), y = wherey();
        gotoxy(x - 3, y);
        int index;
        scanf("%d", &index);
        switch (index) {
        case 1:
            //查看菜单，调用pj的
            system("cls");
            ShowMenu();
            system("pause");
            break;
        case 2:
            system("cls");
            ShowTakeOrderUI();
            break;
        case 3:
            system("cls");
            ShowOrderUI();
            break;
        case 4:
            ShowCheckOutUI();
            break;
        case 5:
            ShowSeatMap();
            break;
        case 6:
            ShowUnCheckedOrderUI();
            break;
        case 7:
            ExitWaitorMainUI();
            ShowWaitorLoginUI();
            return;
        default:
            continue;
        }
    }


}

void ShowWaitorLoginUI() {


    system("cls");
    printf("************************服务员登录界面**********************\n（账户名输入-1返回角色选择界面）\n\n               请输入您的账户名  >>>___________");
    int x = wherex(), y = wherey();
    gotoxy(x - 11, y);
    char name[WaitorName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "-1") == 0)
    {
        ShowWelcomeUI();  // 返回角色选择界面
    }
    printf("\n               请输入您的密码    >>>___________");
    x = wherex(), y = wherey();
    gotoxy(x - 11, y);
    char password[WaitorPasswd_MaxLength];
    scanf("%s", password);
    if (CheckPasswd(name, password) == 1)
    {
        printf("\n\n\n登录成功！");
        system("pause");
        system("cls");

        //设置系统当前服务员
        currentWaitor = getWaitorByName(name);

        ShowWaitorMainUI();
    }
    else
    {
        printf("\n\n\nError>>>账户名不存在或密码输入错误，请重新输入！");
        system("pause");
        system("cls");
        ShowWaitorLoginUI();
    }
}

void DeleteWaitorOfList(char* name) {
    waitor* temp = WaitorListHead;
    while (temp->next && strcmp(temp->next->name, name) == 0) {
        waitor* deletewaitor = temp->next;
        temp->next = deletewaitor->next;
        free(temp);
    }
}

void AddWaitorToList(char* name, char* passwd, int sumofserve) {
    waitor* add = (waitor*)malloc(sizeof(waitor));
    strcpy(add->name, name);
    strcpy(add->passwd, passwd);
    add->sumofserve = sumofserve;
    waitor* temp = WaitorListHead;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = add;
    add->next = NULL;
}

void UpdateWaitorsInfo() {
    //先写日期
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year + 1900;
    int day = p->tm_mday;
    int month = p->tm_mon + 1;

    FILE* fp = fopen("WaitorsInfo.txt", "w");
    if (fp == NULL) {
        perror("文件读取失败");
    }
    fprintf(fp, "%d %d %d\n", year, month, day);

    waitor* temp = WaitorListHead->next;
    while (temp != NULL) {
        if (temp->sumofserve >= 0)
        {
            fprintf(fp, "%s %s %d\n", temp->name, temp->passwd, temp->sumofserve);
            temp = temp->next;
        }
        else
        {
            temp->next = NULL;
            break;
        }
    }
    fclose(fp);
}

void LoadWaitors() {
    WaitorListHead = (waitor*)malloc(sizeof(waitor));
    WaitorListHead->next = NULL;
    FILE* fp = fopen("WaitorsInfo.txt", "r");
    if (fp == NULL)
    {
        perror("文件读取失败");
    }
    //读日期，如果不是今天的日期，将则服务人员数量全部清零，否则直接转化为链表
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year + 1900;
    int day = p->tm_mday;
    int month = p->tm_mon + 1;
    int yearoffile, monthoffile, dayoffile;
    fscanf(fp, "%d %d %d", &yearoffile, &monthoffile, &dayoffile);
    if (year != yearoffile || month != monthoffile || day != dayoffile) {
        char name[WaitorName_MaxLength], passwd[WaitorPasswd_MaxLength];
        int sumofserve;
        while (3 == fscanf(fp, "%s %s %d", name, passwd, &sumofserve))
        {
            AddWaitorToList(name, passwd, 0);
        }
        //修改文件
        UpdateWaitorsInfo();
    }
    else
    {
        char name[WaitorName_MaxLength], passwd[WaitorPasswd_MaxLength];
        int sumofserve;
        while (3 == fscanf(fp, "%s %s %d", name, passwd, &sumofserve))
        {
            AddWaitorToList(name, passwd, sumofserve);
        }
    }
    fclose(fp);
}

waitor* getWaitorByName(char* name) {
    waitor* temp = WaitorListHead->next;
    while (temp) {
        if (strcmp(name, temp->name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void UpdateWaitorsNode() {
    printf("\n请输入您要更新的服务员姓名（输入0取消）>>>___________");
    int x = wherex(), y = wherey();
    gotoxy(x - 6, y);
    char name[WaitorName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "0") == 0)
        return;
    waitor* temp = getWaitorByName(name);
    while (temp == NULL) {
        printf("\n服务员不存在，请重新输入（输入0取消）>>>___________");
        x = wherex(), y = wherey();
        gotoxy(x - 6, y);
        scanf("%s", name);
        if (strcmp(name, "0") == 0)
            return;
        waitor* temp = getWaitorByName(name);
    }

    printf("\n      (1)更新姓名\n      (2)更新密码\n      (3)更新服务人员数量\n      (4)删除\n      (5)返回");
    while (true) {
        printf("\n请输入您要选择的操作序号【  】");
        gotoxy(wherex() - 3, wherey());
        int index;
        scanf("%d", &index);

        switch (index) {
        case 1:
        {
            printf("\n请输入更新后的姓名（输入0取消）>>>________");
            gotoxy(wherex() - 5, wherey());
            scanf("%s", name);
            if (strcmp(name, "0") == 0)
                continue;
            //更新姓名
            strcpy(temp->name, name);
            printf("\n更新成功！");
            UpdateWaitorsInfo();
        }
        break;
        case 2:
        {
            printf("\n请输入更新后的密码（输入0取消）>>>________");
            gotoxy(wherex() - 5, wherey());
            scanf("%s", name);
            if (strcmp(name, "0") == 0)
                continue;
            //更新姓名
            strcpy(temp->passwd, name);
            printf("\n更新成功！");
            UpdateWaitorsInfo();
        }
        break;
        case 3:
        {
            printf("\n请输入更新后的服务数量（输入-1取消）>>>________");
            gotoxy(wherex() - 5, wherey());
            int sum;
            scanf("%d", &sum);
            if (sum < 0)
                continue;
            //更新姓名
            temp->sumofserve = sum;
            printf("\n更新成功！");
            UpdateWaitorsInfo();
        }
        break;
        case 4:
        {
            DeleteWaitorOfList(temp->name);
        }
        break;
        default:
            system("pause");
            return;
        }
    }
}

void PrintfWaitorsInfo() {
    waitor* temp = WaitorListHead->next;
    printf("\n============================全体服务员信息============================");
    printf("\n%-10s \t%-10s \t%-10s", "姓名", "密码", "今日服务数量");
    while (temp) {
        printf("\n%-10s \t%-10s \t%-10d", temp->name, temp->passwd, temp->sumofserve);
        temp = temp->next;
    }
    printf("\n");
    system("pause");
    Adminnode* p = InitAdminTable();
    p = readAdminFromFile(p);
    showWaitorManageUI(p);
}

void showWaitorManageUI(Adminnode* pHead)
{
    system("cls");
    printf("========================服务员信息操作界面==========================\n");
    printf("\n请选择以下操作：\n");
    printf("(1) 招入服务员\n");
    printf("(2) 更新服务员信息\n");
    printf("(3) 浏览全体服务员\n");
    printf("(4) 返回主界面\n");
    while (true)
    {
        printf("请输入操作序号： 【  】");
        int x = wherex(), y = wherey();
        gotoxy(x - 3, y);
        int index;
        scanf("%d", &index);
        switch (index)
        {
        case 1:
            printf("\n请输入您要添加的服务员姓名 >>>_________");
            gotoxy(wherex() - 6, wherey());
            char name[WaitorName_MaxLength];
            scanf("%s", name);
            printf("\n请输入服务员登录密码 >>>_________");
            char passwd[WaitorPasswd_MaxLength];
            gotoxy(wherex() - 6, wherey());
            scanf("%s", passwd);
            LoadWaitors();
            AddWaitorToList(name, passwd, 0);
            UpdateWaitorsInfo();
            system("pause");
            showWaitorManageUI(pHead);
            break;
        case 2:
            LoadWaitors();
            UpdateWaitorsNode();
            system("pause");
            showWaitorManageUI(pHead);
            break;
        case 3:
            LoadWaitors();
            PrintfWaitorsInfo();
            system("pause");
            showWaitorManageUI(pHead);
            break;
        default:
            ShowAdminMainUI(pHead);
            break;
        }
    }
}

waitor* orderWaitorbycount()
{
    waitor* pNode = (waitor*)malloc(sizeof(waitor));
    pNode->next = NULL;
    waitor* pf = WaitorListHead->next;
    if (pf == NULL)//如果待排序的链表为空
    {
        return NULL;
    }
    else if (pf->next == NULL)
    {
        return pf;
    }
    else
    {
        waitor* pfa = pf->next;//永远指向已被排序结点的下一个结点
        while (1)
        {
            if (pNode == NULL || pf->sumofserve >= pNode->sumofserve)//如果应当添加到链表的第一位上
            {
                pf->next = pNode;
                pNode = pf;
            }
            else//如果应当添加到非空链表的非第一位上
            {
                waitor* pr = pNode;
                waitor* q = pr->next;
                while (1)//试图遍历链表
                {
                    if (pr->sumofserve >= pf->sumofserve)//“有可能”迭代到这个新结点该到的位置上了
                    {
                        if (q == NULL)//如果当前位置 是 链表最后一位
                        {
                            //直接无条件添加到链表尾部
                            pf->next = pr->next;
                            pr->next = pf;
                            break;
                        }
                        else//如果当前位置 不是 链表最后一位
                        {
                            if (q->sumofserve <= pf->sumofserve)//真的迭代到这个新结点该到的位置上了
                            {
                                //添加新结点到这个位置上
                                pf->next = pr->next;
                                pr->next = pf;
                                break;
                            }
                        }
                    }
                    pr = q;
                    if (pr == NULL)
                    {
                        break;
                    }
                    q = q->next;//迭代链表节点
                }
            }
            pf = pfa;
            if (pf == NULL)
            {
                break;
            }
            pfa = pfa->next;
        }
    }
    //一定要返回新的链表头地址，因为有可能链表头地址在上边代码中被修改了
    return pNode;
}