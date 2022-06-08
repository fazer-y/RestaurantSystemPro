#define _CRT_SECURE_NO_WARNINGS
#include "Core_orderManage.h"


ordernode* getOrderbyName(char* name) {
    ordernode* temp = OrderListHead->next;
    while (temp) {
        if (strcmp(name, temp->order.name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteOrder(char* name) {
    ordernode* temp = OrderListHead;
    while (temp->next && strcmp(temp->next->order.name, name) != 0) {
        temp = temp->next;
    }
    ordernode* delnode = temp->next;

    if (delnode->order.DineInside == 1) {
        resetSeat(delnode->order.seat.captain, delnode->order.seat.order);//������λ
    }
    temp->next = delnode->next;
}

void SearchOrder() {
    printf("\n��������Ҫ���ҵĶ����Ĺ˿���>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* temp = getOrderbyName(name);
    if (temp == NULL) {
        printf("\nδ�ҵ���ض�����");
    }
    else {
        printf("Ϊ����ѯ�����¶�����Ϣ:\n===============================================\n");
        printf("�˿���:  %s\n", temp->order.name);
        color(12);
        printf("%-10s \t%-10s \t%-10s\n", "��Ʒ", "����", "����");
        color(7);
        int sum[1000] = { 0 };
        for (int i = 0; i < temp->order.sumoffood; i++) {
            char id[50];
            for (int j = 0; temp->order.foods[i][j + 1]; j++) {
                id[j] = temp->order.foods[i][j + 1];
            }
            int index = atoi(id);
            sum[index]++;

        }
        //ͳ�����
        for (int i = 0; i < 1000; i++) {
            if (sum[i] != 0) {
                //������ת��Ϊ#xxx�����ҵ������ͼ۸�
                char id[50];
                sprintf(id, "#%03d", i);
                char name[FOODNAME_LENGTH_MAX];
                double price;
                LoadMyMenu();
                foodnode* temp = foodsListHead->next;
                while (temp) {
                    if (strcmp(temp->data.id, id) == 0)
                    {
                        strcpy(name, temp->data.name);
                        price = temp->data.price;
                        break;
                    }
                    temp = temp->next;
                }
                //��ӡ
                printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
            }
        }
        printf("\n�ۼ�:  %.2lfԪ\n===============================================\n", temp->order.MoneyPaid);
    }

}

//�޸Ķ������к���
void UpdateNameofOrder(ordernode* theorder) {
    printf("\n��������º�Ĺ˿�����(����0ȡ������) >>>_________");
    gotoxy(wherex() - 5, wherey());
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "0") == 0) {
        return;
    }
    //��������
    ordernode* temp = getOrderbyName(name);
    if (temp != NULL && temp != theorder) {
        printf("\n�ù˿����Ѵ��ڣ����������룡");
        UpdateNameofOrder(theorder);
        return;
    }
    strcpy(theorder->order.name, name);
    printf("\n���³ɹ���\n");
    system("pause");
    return;
}

void AddFoodtoOrder(ordernode* theorder) {
    printf("\n������Ҫ��ӵĲ�ƷID�����������в�Ʒ\n");
    ShowMenu();
    printf("\n��������Ҫ��ӵĲ�ƷID������0����>>>  ");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        strcpy(theorder->order.foods[theorder->order.sumoffood++], id);
        theorder->order.MoneyPaid += getPriceoffood(id);
    }
    printf("\n��ӳɹ���\n");
    system("pause");
    return;
}

void DelFoodofOrder(ordernode* theorder) {
    printf("\n������Ҫɾ���Ĳ�ƷID�����������в�Ʒ\n");
    ShowMenu();
    printf("\n��������Ҫɾ���Ĳ�ƷID������0����>>>  ");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        for (int i = 0; i < theorder->order.sumoffood; i++) {
            if (strcmp(theorder->order.foods[i], id) == 0) {
                for (int j = i; j < theorder->order.sumoffood - 1; j++) {
                    strcpy(theorder->order.foods[j], theorder->order.foods[j + 1]);
                }
                break;
            }
        }
        theorder->order.MoneyPaid -= getPriceoffood(id);
        theorder->order.sumoffood--;
    }
    printf("\n��Ʒɾ���ɹ�!\n");
}

void LoadUnDoneOrders()
{

    FILE* fp = fopen("UnDoneOrders.txt", "r");
    if (fp == NULL) {
        perror("��ȡ�ļ�ʧ��");
        return;
    }
    char name[CustomerName_MaxLength];
    while (fscanf(fp, "%s", name) != EOF) {
        Order* temp = (Order*)malloc(sizeof(Order));
        strcpy(temp->name, name);
        int DineInside, col, row, nums;
        fscanf(fp, "%d %d %d %d", &DineInside, &col, &row, &nums);
        temp->DineInside = DineInside;
        temp->seat.captain = col;
        temp->seat.order = row;
        if (DineInside == 1) {
            setSelected(col, row);
        }
        temp->isCheckedout = 0;
        temp->numbers = nums;
        int sumoffood;
        fscanf(fp, "%d", &sumoffood);
        temp->sumoffood = 0;
        temp->MoneyPaid = 0;
        for (int i = 0; i < sumoffood; i++) {
            char id[10];
            fscanf(fp, "%s", id);
            strcpy(temp->foods[temp->sumoffood++], id);
            temp->MoneyPaid += getPriceoffood(id);
        }
        time_t timep;
        struct tm* p;
        time(&timep);
        p = gmtime(&timep);
        int year = p->tm_year + 1900;
        int day = p->tm_mday;
        int month = p->tm_mon + 1;
        temp->date.year = year;
        temp->date.month = month;
        temp->date.day = day;

        AddOrdertoOrderList(temp);
    }
    fclose(fp);
}

void ReWriteUnDoneOrders() {
    ordernode* temp = OrderListHead->next;
    FILE* fp = fopen("UnDoneOrders.txt", "w");
    if (fp == NULL) {
        perror("�ļ���ȡʧ��");
        return;
    }
    while (temp) {
        fprintf(fp, "%s", temp->order.name);
        fprintf(fp, "\n%d %d %d %d", temp->order.DineInside, temp->order.seat.captain, temp->order.seat.order, temp->order.numbers);
        fprintf(fp, "\n%d\n", temp->order.sumoffood);
        for (int i = 0; i < temp->order.sumoffood; i++) {
            fprintf(fp, "%s ", temp->order.foods[i]);
        }
        fprintf(fp, "\n");
        temp = temp->next;
    }
    fclose(fp);
}

void ChangeOrder() {
    printf("\n��������Ҫ�޸Ķ����Ĺ˿���>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* temp = getOrderbyName(name);
    if (temp == NULL) {
        printf("\nδ�ҵ���ض���!\n");
        system("pause");
        return;
    }
    printf("�ö�����Ϣ����:\n===============================================\n");
    printf("�˿���:  %s\n", temp->order.name);
    color(12);
    printf("%-10s \t%-10s \t%-10s\n", "��Ʒ", "����", "����");
    color(7);
    int sum[1000] = { 0 };
    for (int i = 0; i < temp->order.sumoffood; i++) {
        char id[50];
        for (int j = 0; temp->order.foods[i][j + 1]; j++) {
            id[j] = temp->order.foods[i][j + 1];
        }
        int index = atoi(id);
        sum[index]++;

    }
    for (int i = 0; i < 1000; i++) {
        if (sum[i] != 0) {
            char id[50];
            sprintf(id, "#%03d", i);
            char name[FOODNAME_LENGTH_MAX];
            double price;
            LoadMyMenu();
            foodnode* temp = foodsListHead->next;
            while (temp) {
                if (strcmp(temp->data.id, id) == 0)
                {
                    strcpy(name, temp->data.name);
                    price = temp->data.price;
                    break;
                }
                temp = temp->next;
            }
            //��ӡ
            printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
        }
    }
    printf("\n�ۼ�:  %.2lfԪ\n===============================================\n", temp->order.MoneyPaid);
    //�޸�ѡ��
    while (true) {
        color(12);
        printf("\n(1)�޸Ķ��������˿���\n(2)��Ӳ�Ʒ\n(3)ɾ����Ʒ\n(4)�˳�\n\n");
        color(7);
        printf("\n������������>>>_________");
        gotoxy(wherex() - 4, wherey());
        int index;
        scanf("%d", &index);
        switch (index) {
        case 1:
            UpdateNameofOrder(temp);
            break;
        case 2:
            AddFoodtoOrder(temp);
            break;
        case 3:
            DelFoodofOrder(temp);
            break;
        default:
            ShowCheckOutUI();
            return;
        }
    }
}

void AddOrdertoOrderList(Order* order) {
    ordernode* temp = OrderListHead;
    while (temp && temp->next) {
        temp = temp->next;
    }
    ordernode* add = (ordernode*)malloc(sizeof(ordernode));
    add->order = *order;
    add->next = NULL;
    temp->next = add;
}

void CheckOut() {
    printf("��ѡ��Ҫ���˶����Ĺ˿���>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* ordertocheck = getOrderbyName(name);
    while (ordertocheck == NULL) {
        printf("\n�˿Ͳ����ڣ�����������,����0ȡ������ >>>");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) {
            return;
        }

        ordertocheck = getOrderbyName(name);
    }
    //������˲���
    //1.��������ɾ��
    //2.д��DoneOrders.txt
    //3.��λ��Ϊ0
    //4.���Ӳ�Ʒ�㵥����
    LoadMyMenu();
    for (int i = 0; i < ordertocheck->order.sumoffood; i++) {
        //�޸Ĵ�����Ȼ����д���ļ�
        UpdateCountofFood(ordertocheck->order.foods[i]);
    }
    ReWriteBackFood();

    deleteOrder(name);

    FILE* fp = fopen("DoneOrders.txt", "a+");
    if (fp == NULL) {
        perror("�ļ���ȡʧ��");
        return;
    }
    fprintf(fp, "%s %d %d %d %.2lf\n", ordertocheck->order.name, ordertocheck->order.date.year, ordertocheck->order.date.month, ordertocheck->order.date.day, ordertocheck->order.MoneyPaid);
    fclose(fp);
    free(ordertocheck);
}


void DeleteOrderUI() {
    printf("\n��������Ҫɾ���Ķ����Ĺ˿���>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* ordertocheck = getOrderbyName(name);
    while (ordertocheck == NULL) {
        printf("\n�˿Ͳ����ڣ�����������,����0ȡ��ɾ��>>>");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) {
            return;
        }
        ordertocheck = getOrderbyName(name);
    }
    deleteOrder(name);
    printf("\nɾ���ɹ�!");
    system("pause");

}



void ShowUnCheckedOrderUI() {
    system("cls");
    printf("==========================δ���˶�������=============================\n");
    ordernode* temp = OrderListHead->next;

    if (!temp)
    {
        printf("\n\t\t\t����δ���˶���\n\n");
    }
    else
    {
        while (temp) {
            printf("�˿���:  %s\n", temp->order.name);
            color(12);
            printf("%-10s \t%-10s \t%-10s\n", "��Ʒ", "����", "����");
            color(7);
            int sum[1000] = { 0 };
            for (int i = 0; i < temp->order.sumoffood; i++) {
                char id[50];
                for (int j = 0; temp->order.foods[i][j + 1]; j++) {
                    id[j] = temp->order.foods[i][j + 1];
                }
                int index = atoi(id);
                sum[index]++;

            }
            //ͳ�����
            for (int i = 0; i < 1000; i++) {
                if (sum[i] != 0) {
                    //������ת��Ϊ#xxx�����ҵ������ͼ۸�
                    char id[50];
                    sprintf(id, "#%03d", i);
                    char name[FOODNAME_LENGTH_MAX];
                    double price = 0.0;
                    LoadMyMenu();
                    foodnode* temp = foodsListHead->next;
                    while (temp) {
                        if (strcmp(temp->data.id, id) == 0)
                        {
                            strcpy(name, temp->data.name);
                            price = temp->data.price;
                            break;
                        }
                        temp = temp->next;
                    }
                    //��ӡ
                    printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
                }
            }
            printf("\n�ۼ�:  %.2lf Ԫ\n", temp->order.MoneyPaid);
            printf("----------------------------------------------------------------\n");
            temp = temp->next;
        }
    }
    system("pause");
}





void ShowCheckOutUI() {
    system("cls");
    printf("==========================���˽���=============================\n");
    ordernode* temp = OrderListHead->next;

    if (!temp)
    {
        printf("\n\t\t\t����δ���˶���\n\n");
    }
    else
    {
        while (temp) {
            printf("�˿���:  %s\n", temp->order.name);
            color(12);
            printf("%-10s \t%-10s \t%-10s\n", "��Ʒ", "����", "����");
            color(7);
            int sum[1000] = { 0 };
            for (int i = 0; i < temp->order.sumoffood; i++) {
                char id[50];
                for (int j = 0; temp->order.foods[i][j + 1]; j++) {
                    id[j] = temp->order.foods[i][j + 1];
                }
                int index = atoi(id);
                sum[index]++;

            }
            //ͳ�����
            for (int i = 0; i < 1000; i++) {
                if (sum[i] != 0) {
                    //������ת��Ϊ#xxx�����ҵ������ͼ۸�
                    char id[50];
                    sprintf(id, "#%03d", i);
                    char name[FOODNAME_LENGTH_MAX];
                    double price;
                    LoadMyMenu();
                    foodnode* temp = foodsListHead->next;
                    while (temp) {
                        if (strcmp(temp->data.id, id) == 0)
                        {
                            strcpy(name, temp->data.name);
                            price = temp->data.price;
                            break;
                        }
                        temp = temp->next;
                    }
                    //��ӡ
                    printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
                }
            }
            printf("\n�ۼ�:  %.2lf Ԫ\n", temp->order.MoneyPaid);
            printf("----------------------------------------------------------------\n");
            temp = temp->next;
        }

        printf("=================================================================\n");
        while (true) {
            printf("\n��ѡ�����²�����\n");
            printf("(1) ���˶���\n");
            printf("(2) ��ѯ����\n");
            printf("(3) ɾ������\n");
            printf("(4) �޸Ķ���\n");
            printf("(5) ����������\n");
            printf("�����������ţ� ��  ��");
            int x = wherex(), y = wherey();
            gotoxy(x - 3, y);
            int index;
            scanf("%d", &index);
            switch (index) {
            case 1:
                CheckOut();
                break;
            case 2:
                SearchOrder();
                break;
            case 3:
                DeleteOrderUI();
                break;
            case 4:
                ChangeOrder();
                break;
            case 5:
                ShowWaitorMainUI();
                break;
            default:
                ShowWaitorMainUI();
                break;
            }
        }
    }
    system("pause");
}



void ShowTakeOrderUI() {
    system("cls");
    Order* order = (Order*)malloc(sizeof(Order));
    CurrentOrder = *order;//���õ�ǰ������
    //���ö���ʱ��
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    order->date.year = p->tm_year + 1900;
    order->date.day = p->tm_mday;
    order->date.month = p->tm_mon + 1;

    printf("***********************��ͽ���************************\n\n\n");
    printf("������˿�����  >>>____________");
    int x = wherex(), y = wherey();
    gotoxy(x - 8, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    printf("�������ò�����  >>>____________");
    x = wherex(), y = wherey();
    gotoxy(x - 8, y);
    int num;
    scanf("%d", &num);

    //���ö�������
    order->numbers = num;
    strcpy(order->name, name);
    order->sumoffood = 0;
    order->isCheckedout = 0;
    order->MoneyPaid = 0;

    //���ӷ���Ա������Ա������
    currentWaitor->sumofserve += num;

    printf("�����ò��밴 a\n��������밴 b\nԤ�������ò��밴 c\n>>>");
    char select[2];
    scanf("%s", select);

    // Ԥ��������ò�ѡ��
    int col, row;
    if (strcmp(select, "a") == 0 || strcmp(select, "c") == 0)
    {
        while (true)
        {
            system("cls");
            ShowSeatMap();
            printf("��ѡ������  ��  ����  ��");
            int x = wherex(), y = wherey();
            gotoxy(x - 10, y);

            scanf("%d", &col);
            gotoxy(x - 3, y);
            scanf("%d", &row);
            //���ö�������
            int isSelect = isSelected(col, row);

            if (isSelect == 1 || isSelect == 0)
            {
                while (isSelected(col, row) == 1)
                {
                    printf("\n��λ���ѱ�ռ�ã�������ѡ����λ��");
                    printf("\n��ѡ���������������  ��  ����  ��");
                    int x = wherex(), y = wherey();
                    gotoxy(x - 10, y);
                    scanf("%d", &col);
                    gotoxy(x - 3, y);
                    scanf("%d", &row);
                }
                if (col < num)
                {
                    printf("\n! ��ǰѡ�������������С���ò��������Ƿ�����ѡ�񣿣�y/n��:__\b");
                    getchar();
                    char option = 0;
                    scanf("%c", &option);
                    if (option == 'y' || option == 'Y')
                    {
                        continue;
                    }
                    else
                    {
                        addTableUseTimes(col);
                        break;
                    }
                }
                else
                {
                    addTableUseTimes(col);
                    break;
                }
            }
            else if (isSelect == -1)
            {
                continue;
            }
        }

        if (strcmp(select, "c") == 0)
        {
            order->DineInside = 2;
        }
        else
        {
            order->DineInside = 1;
        }
        
        order->seat.captain = col;
        order->seat.order = row;
        //���ø����Ѿ���ռ��
        setSelected(col, row);
        writetableIntoFile(tablesListHead);
    }
    else
    {
        order->DineInside = 0;
    }

    ShowMenu();
    printf("�������ƷID(��#001,�Կո�ָ�,��0����,�س�������) >>>  \n");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        if (getNameofFood(id) != NULL)
        {
            strcpy(order->foods[order->sumoffood++], id);
            order->MoneyPaid += getPriceoffood(id);
        }
        else
        {
            printf("\n�������Ʒ�У����������ޣ�%s����Ʒ���ǳ���Ǹ��\n", id);
            system("pause");
        }
    }

    //�����������
    AddOrdertoOrderList(order);//����ϵͳ���ڴ���Ķ���������
    printf("\n�����ɣ�\n");
    system("pause");
}


void ShowOrderUI() {
    system("cls");
    printf("======================��������============================\n");
    printf("%-10s \t%-10s \t%-10s \t%-10s\n", "���", "�˿�����", "ʱ��", "֧�����");
    //��ʾDoneOrders
    FILE* fp = fopen("DoneOrders.txt", "r");
    char name[30];
    int year, month, date;
    double moneypaid, sum = 0.0;
    int count = 0;
    while (5 == fscanf(fp, "%s %d %d %d %lf", name, &year, &month, &date, &moneypaid))
    {
        sum += moneypaid;
        printf("%-10d \t%-10s  \t%d��%d��%d�� \t%-10.2lf\n", ++count, name, year, month, date, moneypaid);
    }
    printf("�����ܽ���: %.2fԪ\n", sum);
    printf("\n============================================================");
    printf("\n�����������������");
    system("pause");
}

// ����
void showOrderBrowseUI()
{
    while (true)
    {
        system("cls");
        printf("=======================�����������=========================\n");
        printf("\n��ѡ�����²�����\n");
        printf("(1) �������ɶ���\n");
        printf("(2) ���δ��ɶ���\n");
        printf("(3) �����ڲ鿴����ɶ���\n");
        printf("(4) �����ڲ�ѯ����ɶ���\n");
        printf("(5) ����������\n");
        printf("�����������ţ� ��  ��");
        int x = wherex(), y = wherey();
        gotoxy(x - 4, y);
        int index;
        int count = 0;
        Adminnode* ap = InitAdminTable();
        scanf("%d", &index);
        switch (index)
        {
        case 1:
            ShowOrderUI();
            break;
        case 2:
            ShowUnCheckedOrderUI();
            break;
        case 3:
            showOrderByDate();
            break;
        case 4:
            printf("���������ڣ�������,�ո�ָ�����");
            int year, month, day;
            scanf("%d %d %d", &year, &month, &day);
            if (year > 0 && day > 0 && month > 0)
            {
                searchOrderByDate(year, month, day);
            }
            else
            {
                printf("\n���ڸ�ʽ����������������룡\n");
                system("pause");
            }
            break;
        default:
            ap = readAdminFromFile(ap);
            ShowAdminMainUI(ap);
            break;
        }
    }
}

// ������չʾ����
void showOrderByDate()
{
    system("cls");
    printf("======================�����������============================\n\n");
    //��ʾDoneOrders
    FILE* fp = fopen("DoneOrders.txt", "r");
    char name[30];
    int year = 0, month = 0, date = 0;
    double moneypaid, sum = 0;
    fscanf(fp, "%s %d %d %d %lf", name, &year, &month, &date, &moneypaid);
    int nowY = year, nowM = month, nowD = date;
    rewind(fp);
    printf("\n------------------%d��%d��%d��------------------\n", nowY, nowM, nowD);
    printf("%-10s \t%-10s \t%-10s\n", "���", "�˿�����", "֧�����");
    int count = 0;
    while (5 == fscanf(fp, "%s %d %d %d %lf", name, &year, &month, &date, &moneypaid))
    {
        if (year == nowY && month == nowM && nowD == date)
        {
            sum += moneypaid;
            printf("%-10d \t%-10s  \t%-10.2lf\n", ++count, name, moneypaid);
        }
        else
        {
            printf("�����ܽ���: %.2fԪ\n", sum);
            printf("-----------------------------------------------\n\n");
            printf("------------------%d��%d��%d��------------------\n", nowY, nowM, nowD);
            printf("%-10s \t%-10s \t%-10s\n", "���", "�˿�����", "֧�����");
            printf("%-10d \t%-10s  \t%-10.2lf\n", ++count, name, moneypaid);
            nowD = date, nowM = month, nowY = year;
            count = 1;
            sum = moneypaid;  // ����ÿ���ܽ��
        }
    }

    printf("\n============================================================\n\n");
    system("pause");
}

// �����ڲ�ѯ����
void searchOrderByDate(int syear, int smonth, int sday)
{
    system("cls");
    printf("======================�����������============================\n");
    printf("%-10s \t%-10s \t%-10s\n", "���", "�˿�����", "֧�����");
    //��ʾDoneOrders
    FILE* fp = fopen("DoneOrders.txt", "r");
    char name[30];
    int nowY = 0, nowM = 0, nowD = 0;
    int year, month, date;
    double moneypaid, sum = 0;
    int count = 0;
    while (5 == fscanf(fp, "%s %d %d %d %lf", name, &year, &month, &date, &moneypaid))
    {
        if (syear == year && smonth == month && sday == date)
        {
            sum += moneypaid;
            printf("%-10d \t%-10s  \t%-10.2lf\n", ++count, name, moneypaid);
        }
    }
    printf("%d��%d��%d�ն����ܽ���: %.2fԪ\n", syear, smonth, sday, sum);
    printf("\n============================================================\n");
    system("pause");
}