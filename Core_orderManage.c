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
        resetSeat(delnode->order.seat.captain, delnode->order.seat.order);//更新座位
    }
    temp->next = delnode->next;
}

void SearchOrder() {
    printf("\n请输入您要查找的订单的顾客名>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* temp = getOrderbyName(name);
    if (temp == NULL) {
        printf("\n未找到相关订单！");
    }
    else {
        printf("为您查询到以下订单信息:\n===============================================\n");
        printf("顾客名:  %s\n", temp->order.name);
        color(12);
        printf("%-10s \t%-10s \t%-10s\n", "菜品", "数量", "单价");
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
        //统计完成
        for (int i = 0; i < 1000; i++) {
            if (sum[i] != 0) {
                //将数字转化为#xxx，再找到菜名和价格
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
                //打印
                printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
            }
        }
        printf("\n累计:  %.2lf元\n===============================================\n", temp->order.MoneyPaid);
    }

}

//修改订单所有函数
void UpdateNameofOrder(ordernode* theorder) {
    printf("\n请输入更新后的顾客姓名(输入0取消更新) >>>_________");
    gotoxy(wherex() - 5, wherey());
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "0") == 0) {
        return;
    }
    //查重姓名
    ordernode* temp = getOrderbyName(name);
    if (temp != NULL && temp != theorder) {
        printf("\n该顾客名已存在，请重新输入！");
        UpdateNameofOrder(theorder);
        return;
    }
    strcpy(theorder->order.name, name);
    printf("\n更新成功！\n");
    system("pause");
    return;
}

void AddFoodtoOrder(ordernode* theorder) {
    printf("\n请输入要添加的菜品ID，以下是所有菜品\n");
    ShowMenu();
    printf("\n请输入您要添加的菜品ID，输入0结束>>>  ");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        strcpy(theorder->order.foods[theorder->order.sumoffood++], id);
        theorder->order.MoneyPaid += getPriceoffood(id);
    }
    printf("\n添加成功！\n");
    system("pause");
    return;
}

void DelFoodofOrder(ordernode* theorder) {
    printf("\n请输入要删除的菜品ID，以下是所有菜品\n");
    ShowMenu();
    printf("\n请输入您要删除的菜品ID，输入0结束>>>  ");
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
    printf("\n菜品删除成功!\n");
}

void LoadUnDoneOrders()
{

    FILE* fp = fopen("UnDoneOrders.txt", "r");
    if (fp == NULL) {
        perror("读取文件失败");
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
        perror("文件读取失败");
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
    printf("\n请输入您要修改订单的顾客名>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* temp = getOrderbyName(name);
    if (temp == NULL) {
        printf("\n未找到相关订单!\n");
        system("pause");
        return;
    }
    printf("该订单信息如下:\n===============================================\n");
    printf("顾客名:  %s\n", temp->order.name);
    color(12);
    printf("%-10s \t%-10s \t%-10s\n", "菜品", "数量", "单价");
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
            //打印
            printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
        }
    }
    printf("\n累计:  %.2lf元\n===============================================\n", temp->order.MoneyPaid);
    //修改选项
    while (true) {
        color(12);
        printf("\n(1)修改订单所属顾客名\n(2)添加菜品\n(3)删除菜品\n(4)退出\n\n");
        color(7);
        printf("\n请输入操作序号>>>_________");
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
    printf("请选择要结账订单的顾客名>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* ordertocheck = getOrderbyName(name);
    while (ordertocheck == NULL) {
        printf("\n顾客不存在，请重新输入,输入0取消结账 >>>");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) {
            return;
        }

        ordertocheck = getOrderbyName(name);
    }
    //具体结账操作
    //1.从链表中删除
    //2.写入DoneOrders.txt
    //3.座位改为0
    //4.增加菜品点单次数
    LoadMyMenu();
    for (int i = 0; i < ordertocheck->order.sumoffood; i++) {
        //修改次数，然后重写进文件
        UpdateCountofFood(ordertocheck->order.foods[i]);
    }
    ReWriteBackFood();

    deleteOrder(name);

    FILE* fp = fopen("DoneOrders.txt", "a+");
    if (fp == NULL) {
        perror("文件读取失败");
        return;
    }
    fprintf(fp, "%s %d %d %d %.2lf\n", ordertocheck->order.name, ordertocheck->order.date.year, ordertocheck->order.date.month, ordertocheck->order.date.day, ordertocheck->order.MoneyPaid);
    fclose(fp);
    free(ordertocheck);
}


void DeleteOrderUI() {
    printf("\n请输入您要删除的订单的顾客名>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* ordertocheck = getOrderbyName(name);
    while (ordertocheck == NULL) {
        printf("\n顾客不存在，请重新输入,输入0取消删除>>>");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) {
            return;
        }
        ordertocheck = getOrderbyName(name);
    }
    deleteOrder(name);
    printf("\n删除成功!");
    system("pause");

}



void ShowUnCheckedOrderUI() {
    system("cls");
    printf("==========================未结账订单界面=============================\n");
    ordernode* temp = OrderListHead->next;

    if (!temp)
    {
        printf("\n\t\t\t暂无未结账订单\n\n");
    }
    else
    {
        while (temp) {
            printf("顾客名:  %s\n", temp->order.name);
            color(12);
            printf("%-10s \t%-10s \t%-10s\n", "菜品", "数量", "单价");
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
            //统计完成
            for (int i = 0; i < 1000; i++) {
                if (sum[i] != 0) {
                    //将数字转化为#xxx，再找到菜名和价格
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
                    //打印
                    printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
                }
            }
            printf("\n累计:  %.2lf 元\n", temp->order.MoneyPaid);
            printf("----------------------------------------------------------------\n");
            temp = temp->next;
        }
    }
    system("pause");
}





void ShowCheckOutUI() {
    system("cls");
    printf("==========================结账界面=============================\n");
    ordernode* temp = OrderListHead->next;

    if (!temp)
    {
        printf("\n\t\t\t暂无未结账订单\n\n");
    }
    else
    {
        while (temp) {
            printf("顾客名:  %s\n", temp->order.name);
            color(12);
            printf("%-10s \t%-10s \t%-10s\n", "菜品", "数量", "单价");
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
            //统计完成
            for (int i = 0; i < 1000; i++) {
                if (sum[i] != 0) {
                    //将数字转化为#xxx，再找到菜名和价格
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
                    //打印
                    printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
                }
            }
            printf("\n累计:  %.2lf 元\n", temp->order.MoneyPaid);
            printf("----------------------------------------------------------------\n");
            temp = temp->next;
        }

        printf("=================================================================\n");
        while (true) {
            printf("\n请选择以下操作：\n");
            printf("(1) 结账订单\n");
            printf("(2) 查询订单\n");
            printf("(3) 删除订单\n");
            printf("(4) 修改订单\n");
            printf("(5) 返回主界面\n");
            printf("请输入操作序号： 【  】");
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
    CurrentOrder = *order;//设置当前处理订单
    //设置订单时间
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    order->date.year = p->tm_year + 1900;
    order->date.day = p->tm_mday;
    order->date.month = p->tm_mon + 1;

    printf("***********************点餐界面************************\n\n\n");
    printf("请输入顾客姓名  >>>____________");
    int x = wherex(), y = wherey();
    gotoxy(x - 8, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    printf("请输入用餐人数  >>>____________");
    x = wherex(), y = wherey();
    gotoxy(x - 8, y);
    int num;
    scanf("%d", &num);

    //设置订单属性
    order->numbers = num;
    strcpy(order->name, name);
    order->sumoffood = 0;
    order->isCheckedout = 0;
    order->MoneyPaid = 0;

    //增加服务员服务人员的数量
    currentWaitor->sumofserve += num;

    printf("店内用餐请按 a\n打包带走请按 b\n预定店内用餐请按 c\n>>>");
    char select[2];
    scanf("%s", select);

    // 预定或店内用餐选座
    int col, row;
    if (strcmp(select, "a") == 0 || strcmp(select, "c") == 0)
    {
        while (true)
        {
            system("cls");
            ShowSeatMap();
            printf("请选择桌号  【  】【  】");
            int x = wherex(), y = wherey();
            gotoxy(x - 10, y);

            scanf("%d", &col);
            gotoxy(x - 3, y);
            scanf("%d", &row);
            //设置订单属性
            int isSelect = isSelected(col, row);

            if (isSelect == 1 || isSelect == 0)
            {
                while (isSelected(col, row) == 1)
                {
                    printf("\n该位置已被占用，请重新选择座位！");
                    printf("\n请选择餐桌容量及座次  【  】【  】");
                    int x = wherex(), y = wherey();
                    gotoxy(x - 10, y);
                    scanf("%d", &col);
                    gotoxy(x - 3, y);
                    scanf("%d", &row);
                }
                if (col < num)
                {
                    printf("\n! 当前选择餐桌类型容量小于用餐人数，是否重新选择？（y/n）:__\b");
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
        //设置该桌已经被占用
        setSelected(col, row);
        writetableIntoFile(tablesListHead);
    }
    else
    {
        order->DineInside = 0;
    }

    ShowMenu();
    printf("请输入菜品ID(如#001,以空格分割,按0结束,回车以输入) >>>  \n");
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
            printf("\n您所点菜品中，本餐厅暂无（%s）菜品，非常抱歉。\n", id);
            system("pause");
        }
    }

    //订单设置完成
    AddOrdertoOrderList(order);//加入系统正在处理的订单链表中
    printf("\n点餐完成！\n");
    system("pause");
}


void ShowOrderUI() {
    system("cls");
    printf("======================订单界面============================\n");
    printf("%-10s \t%-10s \t%-10s \t%-10s\n", "序号", "顾客姓名", "时间", "支付金额");
    //显示DoneOrders
    FILE* fp = fopen("DoneOrders.txt", "r");
    char name[30];
    int year, month, date;
    double moneypaid, sum = 0.0;
    int count = 0;
    while (5 == fscanf(fp, "%s %d %d %d %lf", name, &year, &month, &date, &moneypaid))
    {
        sum += moneypaid;
        printf("%-10d \t%-10s  \t%d年%d月%d日 \t%-10.2lf\n", ++count, name, year, month, date, moneypaid);
    }
    printf("订单总金额共计: %.2f元\n", sum);
    printf("\n============================================================");
    printf("\n按任意键返回主界面");
    system("pause");
}

// 订单
void showOrderBrowseUI()
{
    while (true)
    {
        system("cls");
        printf("=======================订单浏览界面=========================\n");
        printf("\n请选择以下操作：\n");
        printf("(1) 浏览已完成订单\n");
        printf("(2) 浏览未完成订单\n");
        printf("(3) 按日期查看已完成订单\n");
        printf("(4) 按日期查询已完成订单\n");
        printf("(5) 返回主界面\n");
        printf("请输入操作序号： 【  】");
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
            printf("请输入日期（年月日,空格分隔）：");
            int year, month, day;
            scanf("%d %d %d", &year, &month, &day);
            if (year > 0 && day > 0 && month > 0)
            {
                searchOrderByDate(year, month, day);
            }
            else
            {
                printf("\n日期格式有误，请检查后重新输入！\n");
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

// 按日期展示订单
void showOrderByDate()
{
    system("cls");
    printf("======================订单浏览界面============================\n\n");
    //显示DoneOrders
    FILE* fp = fopen("DoneOrders.txt", "r");
    char name[30];
    int year = 0, month = 0, date = 0;
    double moneypaid, sum = 0;
    fscanf(fp, "%s %d %d %d %lf", name, &year, &month, &date, &moneypaid);
    int nowY = year, nowM = month, nowD = date;
    rewind(fp);
    printf("\n------------------%d年%d月%d日------------------\n", nowY, nowM, nowD);
    printf("%-10s \t%-10s \t%-10s\n", "序号", "顾客姓名", "支付金额");
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
            printf("订单总金额共计: %.2f元\n", sum);
            printf("-----------------------------------------------\n\n");
            printf("------------------%d年%d月%d日------------------\n", nowY, nowM, nowD);
            printf("%-10s \t%-10s \t%-10s\n", "序号", "顾客姓名", "支付金额");
            printf("%-10d \t%-10s  \t%-10.2lf\n", ++count, name, moneypaid);
            nowD = date, nowM = month, nowY = year;
            count = 1;
            sum = moneypaid;  // 重置每日总金额
        }
    }

    printf("\n============================================================\n\n");
    system("pause");
}

// 按日期查询订单
void searchOrderByDate(int syear, int smonth, int sday)
{
    system("cls");
    printf("======================订单浏览界面============================\n");
    printf("%-10s \t%-10s \t%-10s\n", "序号", "顾客姓名", "支付金额");
    //显示DoneOrders
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
    printf("%d年%d月%d日订单总金额共计: %.2f元\n", syear, smonth, sday, sum);
    printf("\n============================================================\n");
    system("pause");
}