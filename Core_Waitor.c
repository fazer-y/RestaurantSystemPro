#define _CRT_SECURE_NO_WARNINGS
#include "CORE_Waitor.h"

int CheckPasswd(char* name, char* passwd) 
{
    FILE* fp = fopen("WaitorsInfo.txt", "r");
    if (fp == NULL)
    {
        perror("�ļ���ȡʧ��");
        return 0;
    }
    //�������ȶ���
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
    printf("===================����Ա�������=====================\n");
    while (true)
    {
        color(12);
        printf("\n(1)��ӷ���Ա\n(2)���·���Ա\n(3)�˳�\n");
        color(7);
        printf("������������ ��  ��");
        gotoxy(wherex() - 3, wherey());
        int index;
        scanf("%d", &index);
        switch (index)
        {
        case 1:
        {
            printf("\n��������Ҫ��ӵķ���Ա���� >>>_________");
            gotoxy(wherex() - 6, wherey());
            char name[WaitorName_MaxLength];
            scanf("%s", name);
            printf("\n���������Ա��¼���� >>>_________");
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
        printf("***********************����Ա������************************\n\n\n");
        printf("             ---------------------------------             \n\n");
        printf("            |        (1) �鿴�˵�             |            \n");
        printf("            |        (2) ���                 |            \n");
        printf("            |        (3) �鿴����             |            \n");
        printf("            |        (4) ����                 |            \n");
        printf("            |        (5) �鿴��λ             |            \n");
        printf("            |        (6) �鿴δ���˶���        |            \n");
        printf("            |        (7) �˳�                 |            \n");
        printf("             ---------------------------------             \n\n\n");
        printf("***********************************************************\n\n");
        printf("��ѡ�������� ��  ��");
        int x = wherex(), y = wherey();
        gotoxy(x - 3, y);
        int index;
        scanf("%d", &index);
        switch (index) {
        case 1:
            //�鿴�˵�������pj��
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
    printf("************************����Ա��¼����**********************\n���˻�������-1���ؽ�ɫѡ����棩\n\n               �����������˻���  >>>___________");
    int x = wherex(), y = wherey();
    gotoxy(x - 11, y);
    char name[WaitorName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "-1") == 0)
    {
        ShowWelcomeUI();  // ���ؽ�ɫѡ�����
    }
    printf("\n               ��������������    >>>___________");
    x = wherex(), y = wherey();
    gotoxy(x - 11, y);
    char password[WaitorPasswd_MaxLength];
    scanf("%s", password);
    if (CheckPasswd(name, password) == 1)
    {
        printf("\n\n\n��¼�ɹ���");
        system("pause");
        system("cls");

        //����ϵͳ��ǰ����Ա
        currentWaitor = getWaitorByName(name);

        ShowWaitorMainUI();
    }
    else
    {
        printf("\n\n\nError>>>�˻��������ڻ���������������������룡");
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
    //��д����
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year + 1900;
    int day = p->tm_mday;
    int month = p->tm_mon + 1;

    FILE* fp = fopen("WaitorsInfo.txt", "w");
    if (fp == NULL) {
        perror("�ļ���ȡʧ��");
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
        perror("�ļ���ȡʧ��");
    }
    //�����ڣ�������ǽ�������ڣ����������Ա����ȫ�����㣬����ֱ��ת��Ϊ����
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
        //�޸��ļ�
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
    printf("\n��������Ҫ���µķ���Ա����������0ȡ����>>>___________");
    int x = wherex(), y = wherey();
    gotoxy(x - 6, y);
    char name[WaitorName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "0") == 0)
        return;
    waitor* temp = getWaitorByName(name);
    while (temp == NULL) {
        printf("\n����Ա�����ڣ����������루����0ȡ����>>>___________");
        x = wherex(), y = wherey();
        gotoxy(x - 6, y);
        scanf("%s", name);
        if (strcmp(name, "0") == 0)
            return;
        waitor* temp = getWaitorByName(name);
    }

    printf("\n      (1)��������\n      (2)��������\n      (3)���·�����Ա����\n      (4)ɾ��\n      (5)����");
    while (true) {
        printf("\n��������Ҫѡ��Ĳ�����š�  ��");
        gotoxy(wherex() - 3, wherey());
        int index;
        scanf("%d", &index);

        switch (index) {
        case 1:
        {
            printf("\n��������º������������0ȡ����>>>________");
            gotoxy(wherex() - 5, wherey());
            scanf("%s", name);
            if (strcmp(name, "0") == 0)
                continue;
            //��������
            strcpy(temp->name, name);
            printf("\n���³ɹ���");
            UpdateWaitorsInfo();
        }
        break;
        case 2:
        {
            printf("\n��������º�����루����0ȡ����>>>________");
            gotoxy(wherex() - 5, wherey());
            scanf("%s", name);
            if (strcmp(name, "0") == 0)
                continue;
            //��������
            strcpy(temp->passwd, name);
            printf("\n���³ɹ���");
            UpdateWaitorsInfo();
        }
        break;
        case 3:
        {
            printf("\n��������º�ķ�������������-1ȡ����>>>________");
            gotoxy(wherex() - 5, wherey());
            int sum;
            scanf("%d", &sum);
            if (sum < 0)
                continue;
            //��������
            temp->sumofserve = sum;
            printf("\n���³ɹ���");
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
    printf("\n============================ȫ�����Ա��Ϣ============================");
    printf("\n%-10s \t%-10s \t%-10s", "����", "����", "���շ�������");
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
    printf("========================����Ա��Ϣ��������==========================\n");
    printf("\n��ѡ�����²�����\n");
    printf("(1) �������Ա\n");
    printf("(2) ���·���Ա��Ϣ\n");
    printf("(3) ���ȫ�����Ա\n");
    printf("(4) ����������\n");
    while (true)
    {
        printf("�����������ţ� ��  ��");
        int x = wherex(), y = wherey();
        gotoxy(x - 3, y);
        int index;
        scanf("%d", &index);
        switch (index)
        {
        case 1:
            printf("\n��������Ҫ��ӵķ���Ա���� >>>_________");
            gotoxy(wherex() - 6, wherey());
            char name[WaitorName_MaxLength];
            scanf("%s", name);
            printf("\n���������Ա��¼���� >>>_________");
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
    if (pf == NULL)//��������������Ϊ��
    {
        return NULL;
    }
    else if (pf->next == NULL)
    {
        return pf;
    }
    else
    {
        waitor* pfa = pf->next;//��Զָ���ѱ����������һ�����
        while (1)
        {
            if (pNode == NULL || pf->sumofserve >= pNode->sumofserve)//���Ӧ����ӵ�����ĵ�һλ��
            {
                pf->next = pNode;
                pNode = pf;
            }
            else//���Ӧ����ӵ��ǿ�����ķǵ�һλ��
            {
                waitor* pr = pNode;
                waitor* q = pr->next;
                while (1)//��ͼ��������
                {
                    if (pr->sumofserve >= pf->sumofserve)//���п��ܡ�����������½��õ���λ������
                    {
                        if (q == NULL)//�����ǰλ�� �� �������һλ
                        {
                            //ֱ����������ӵ�����β��
                            pf->next = pr->next;
                            pr->next = pf;
                            break;
                        }
                        else//�����ǰλ�� ���� �������һλ
                        {
                            if (q->sumofserve <= pf->sumofserve)//��ĵ���������½��õ���λ������
                            {
                                //����½�㵽���λ����
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
                    q = q->next;//��������ڵ�
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
    //һ��Ҫ�����µ�����ͷ��ַ����Ϊ�п�������ͷ��ַ���ϱߴ����б��޸���
    return pNode;
}