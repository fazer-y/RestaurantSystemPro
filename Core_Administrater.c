/*
 * @Author: 彭京
 * @ID: 202000810081
 * @Date: 2022-05-31
 * @LastEditors: LAPTOP-44TSMLLA
 * @Description:该源代码文件记录了系统管理员的五个功能需求中所要用到的所有链表和文件操作函数定义，大部分UI界面设计函数定义，主创作者为彭京。
 */
#define _CRT_SECURE_NO_WARNINGS
#include "Core_Administrater.h"
#include "Core_Waitor.h"
#include "Core_System.h"


Adminnode* InitAdminTable()
{
	Adminnode* pHead;
	pHead = NULL;
	return pHead;
}

Adminnode* addAdminByOrder(Adminnode* pHead, Admin data)
{
	Adminnode* pNode = (Adminnode*)malloc(sizeof(Adminnode));
	if_Is_Null_Then_End_Program(pNode);
	pNode->data = data;
	pNode->next = NULL;
	if (pHead == NULL)//如果要添加到一个空链表中
	{
		pNode->next = pHead;
		pHead = pNode;
	}
	else//如果要添加到一个 非空链表 中
	{
		if (pNode->data.age <= pHead->data.age)//如果应当添加到非空链表的 第一位 上
		{
			pNode->next = pHead;
			pHead = pNode;
		}
		else//如果应当添加到非空链表的 非第一位 上
		{
			Adminnode* pr = pHead;
			Adminnode* q = pr->next;
			while (1)//试图遍历链表
			{
				if (pr->data.age <= pNode->data.age)//“有可能”迭代到这个新结点该到的位置上了
				{
					if (q == NULL)//如果当前位置 是 链表最后一位
					{
						//直接无条件添加到链表尾部
						pNode->next = pr->next;
						pr->next = pNode;
						break;
					}
					else//如果当前位置 不是 链表最后一位
					{
						if (q->data.age >= pNode->data.age)//真的迭代到这个新结点该到的位置上了
						{
							//添加新结点到这个位置上
							pNode->next = pr->next;
							pr->next = pNode;
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
	}

	//一定要返回新的链表头地址，因为有可能链表头地址在上边代码中被修改了
	return pHead;
}

Adminnode* findAdminByID(Adminnode* pHead, char* ID)
{
	if (pHead == NULL) //空表则直接退出函数
	{
		return NULL;
	}
	Adminnode* p = pHead;
	while (!(p == NULL))//遍历链表
	{
		if (strcmp(p->data.ID, ID) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void printAdminTable(Adminnode* pHead)
{
	Adminnode* p = pHead;
	printf("%-15s\t%-10s\t%-10s\t%-2s\t%-4s\n", "账号", "密码", "姓名", "性别", "年龄");
	while (!(p == NULL))//遍历链表
	{
		printf("%-15s\t%-10s\t%-10s\t%-2s\t%-4d\n", p->data.ID, p->data.password, p->data.name, p->data.sex, p->data.age);
		p = p->next;
	}
}

Adminnode* updateAdminByID(Adminnode* pHead, char* ID, Admin data)
{
	if (pHead == NULL) //空表则直接退出函数
	{
		return NULL;
	}
	Adminnode* p = pHead;
	while (!(p == NULL))//试图遍历链表
	{
		if (strcmp(p->data.ID, ID) == 0)
		{
			p->data = data;//更新结点信息
		}
		p = p->next;
	}
	return pHead;
}

Adminnode* readAdminFromFile()
{
	FILE* fp;  // 文件指针
	fp = fopen(ADMIN_FILE_PATH, "a+");
	// 判断文件是否能够正确打开 
	if_Is_Null_Then_End_Program(fp);
	// 从文件中读取管理员信息
	char ID[ADMINPAS_LENGTH_MAX];
	char password[ADMINPAS_LENGTH_MAX];
	char name[ADMINNAME_LENGTH_MAX];
	char sex[10];
	int age = 0;
	int num = 0;
	Adminnode* an = InitAdminTable();
	while (fscanf(fp, "%s %s %s %s %d", ID, password, name, sex, &age) != EOF)
	{
		Admin a;
		strcpy(a.ID, ID);
		strcpy(a.password, password);
		strcpy(a.name, name);
		strcpy(a.sex, sex);
		a.age = age;
		an = addAdminByOrder(an, a);
		num++;
		an->number = num;
	}
	//关闭文件
	fclose(fp);
	return an;
}

bool writeAdminIntoFile(Adminnode* pHead)
{
	if (pHead == NULL) //空表则直接退出函数,无需写入
	{
		return false;
	}
	FILE* fp;  // 文件指针
	fp = fopen(ADMIN_FILE_PATH, "w+");
	// 判断文件是否能够正确打开 
	if_Is_Null_Then_End_Program(fp);
	Adminnode* p = pHead;
	while (!(p == NULL))//遍历链表
	{
		fprintf(fp, "%s %s %s %s %d\n", p->data.ID, p->data.password, p->data.name, p->data.sex, p->data.age);
		p = p->next;
	}
	// 刷新缓冲区，将缓冲区的内容写入文件 
	fflush(fp);
	// 重置文件内部位置指针，确保位置指针指向文件开头
	rewind(fp);
	return true;
}

foodnode* InitfoodTable()
{
	foodnode* pHead;
	pHead = NULL;
	return pHead;
}

foodnode* addfood(foodnode* pHead, food data)
{
	//根据传入数据创建一个新的链表节点
	foodnode* pNode = (foodnode*)malloc(sizeof(foodnode));
	if_Is_Null_Then_End_Program(pNode);
	pNode->data = data;
	pNode->next = NULL;

	if (pHead == NULL)//如果要添加到一个 空链表 中
	{
		pNode->next = pHead;
		pHead = pNode;
	}
	else//如果要添加到一个 非空链表 中
	{
		foodnode* pr = NULL;
		pr = pHead;
		while (!(pr->next == NULL))//迭代到链表尾部
		{
			pr = pr->next;
		}
		pr->next = pNode;//添加新结点到链表尾部
	}
	return pHead;
}

foodnode* findfoodByid(foodnode* pHead, char* ID)
{
	if (pHead == NULL) //空表则直接退出函数
	{
		return NULL;
	}
	foodnode* p = pHead;
	while (!(p == NULL))//遍历链表
	{
		if (strcmp(p->data.id, ID) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

char* switchenumtos(enum foodType type)
{
	char* foodtype = (char*)malloc(sizeof(char) * 20);
	switch (type)
	{
	case specaility:
		strcpy(foodtype, "招牌菜");
		break;
	case hot:
		strcpy(foodtype, "热菜");
		break;
	case cold:
		strcpy(foodtype, "凉菜");
		break;
	case soup:
		strcpy(foodtype, "汤品");
		break;
	case staple:
		strcpy(foodtype, "主食");
		break;
	case beverage:
		strcpy(foodtype, "饮料");
		break;
	default:
		break;
	}
	return foodtype;
}

enum foodType switchstoenum(char* type)
{
	if (strcmp(type, "招牌菜") == 0)
	{
		return specaility;
	}
	else if (strcmp(type, "热菜") == 0)
	{
		return hot;
	}
	else if (strcmp(type, "凉菜") == 0)
	{
		return cold;
	}
	else if (strcmp(type, "饮料") == 0)
	{
		return beverage;
	}
	else if (strcmp(type, "汤品") == 0)
	{
		return soup;
	}
	else if (strcmp(type, "主食") == 0)
	{
		return staple;
	}
	else
	{
		printf("输入错误");
	}
}

foodnode* deletefoodByID(foodnode* pHead, char* ID)
{
	if (pHead == NULL) //空表
	{
		return NULL;
	}
	//对于在表头的数据特殊处理
	if (ID == pHead->data.id)
	{
		foodnode* pDelete = pHead;
		pHead = pHead->next;
		free(pDelete);
	}
	else
	{
		foodnode* pLast = pHead;
		foodnode* pNext = pHead->next;
		foodnode* pDelete = NULL;
		while (1)
		{
			if (ID == pNext->data.id)//如果找到
			{
				pDelete = pNext;
				pLast->next = pNext->next;
			}

			if (pNext->next == NULL)//如果到了链表结尾
			{
				break;
			}
			else
			{
				pLast = pLast->next;
				pNext = pNext->next;
			}
		}
		free(pDelete);
	}
	return pHead;
}

foodnode* orderfoodbycount(foodnode* pHead)
{
	foodnode* pNode = InitfoodTable();
	foodnode* pf = pHead;
	if (pf == NULL)//如果待排序的链表为空
	{
		return NULL;
	}

	else
	{
		foodnode* pfa = pHead->next;//永远指向已被排序结点的下一个结点
		while (1)
		{
			if (pNode == NULL || pf->data.orderCount >= pNode->data.orderCount)//如果应当添加到链表的第一位上
			{
				pf->next = pNode;
				pNode = pf;
			}
			else//如果应当添加到非空链表的非第一位上
			{
				foodnode* pr = pNode;
				foodnode* q = pr->next;
				while (1)//试图遍历链表
				{
					if (pr->data.orderCount >= pf->data.orderCount)//“有可能”迭代到这个新结点该到的位置上了
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
							if (q->data.orderCount <= pf->data.orderCount)//真的迭代到这个新结点该到的位置上了
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

foodnode* updatefoodByid(foodnode* pHead, char* ID, food data)
{
	if (pHead == NULL) //空表则直接退出函数
	{
		return NULL;
	}
	foodnode* p = pHead;
	while (!(p == NULL))//遍历链表
	{
		if (strcmp(p->data.id, ID) == 0) {
			p->data = data;//更新结点信息
		}
		p = p->next;
	}
	return pHead;
}

void printfoodTable(foodnode* pHead)
{
	foodnode* p = pHead;
	printf("%-10s\t%-10s\t%-5s\t%-5s\t%-7s\n", "食品id", "食品名称", "食品类型", "被点次数", "价格");
	while (!(p == NULL))//遍历链表
	{
		char foodtype[20];
		strcpy(foodtype, switchenumtos(p->data.foodtype));
		printf("%-10s\t%-10s \t%-10s \t%-10d\t%-7.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
		p = p->next;
	}
}

foodnode* readfoodFromFile(foodnode* pHead)
{
	FILE* fp;  // 文件指针
	fp = fopen(FOOD_FILE_PATH, "a+");
	// 判断文件是否能够正确打开 
	if_Is_Null_Then_End_Program(fp);
	// 从文件中读取食物信息
	char id[10];
	char name[FOODNAME_LENGTH_MAX];
	char foodtype[20];
	double price;
	int orderCount;
	int num = 0;
	foodnode* fn = InitfoodTable();
	while (fscanf(fp, "%s %s %s %d %lf", id, name, foodtype, &orderCount, &price) != EOF)
	{
		food f;
		strcpy(f.id, id);
		strcpy(f.name, name);
		f.orderCount = orderCount;
		f.price = price;
		//将文本中读出的字符串菜品类型转化为枚举类型以便存储
		f.foodtype = switchstoenum(foodtype);
		fn = addfood(fn, f);
		num++;
		fn->number = num;
	}
	//关闭文件
	fclose(fp);
	return fn;
}

bool writefoodIntoFile(foodnode* pHead)
{
	if (pHead == NULL) //空表则直接退出函数,无需写入
	{
		return false;
	}
	FILE* fp;  // 文件指针
	fp = fopen(FOOD_FILE_PATH, "w+");
	// 判断文件是否能够正确打开 
	if_Is_Null_Then_End_Program(fp);
	foodnode* p = pHead;
	while (!(p == NULL))//遍历链表
	{
		char foodtype[20];
		strcpy(foodtype, switchenumtos(p->data.foodtype));
		fprintf(fp, "%s %s %s %d %.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
		p = p->next;
	}
	// 刷新缓冲区，将缓冲区的内容写入文件 
	fflush(fp);
	// 重置文件内部位置指针，确保位置指针指向文件开头
	rewind(fp);
	return true;
}

void if_Is_Null_Then_End_Program(void* ptr)
{
	if (ptr == NULL)
	{
		printf("程序发生错误 !\n即将退出程序...\n");
		exit(EXIT_FAILURE);
	}
}

void ShowUserManageUI(Adminnode* pHead)
{
	system("cls");
	printf("========================用户管理界面===========================\n");
	printf("\n请选择以下操作：\n");
	printf("(1) 管理系统管理员信息\n");
	printf("(2) 管理服务员信息\n");
	printf("(3) 返回主界面\n");
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
			showAdminManageUI(pHead);
			break;
		case 2:
			showWaitorManageUI(pHead);
			break;
		default:
			ShowAdminMainUI(pHead);
			break;
		}
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

void addAdminUI(Adminnode* pHead)
{
	system("cls");
	printf("========================添加系统管理员==========================\n");
	printf("请输入欲添加系统管理员的信息:\n");
	Admin a;
	printf("ID："); scanf("%s", a.ID);
	printf("密码："); scanf("%s", a.password);
	printf("姓名："); scanf("%s", a.name);
	printf("性别："); scanf("%s", a.sex);
	printf("年龄："); scanf("%d", &a.age);
	pHead = addAdminByOrder(pHead, a);
	writeAdminIntoFile(pHead);
	printf("添加成功\n\n");
	system("pause");
	ShowUserManageUI(pHead);
}

void findAdminUI(Adminnode* pHead)
{
	system("cls");
	printf("========================查找管理员信息===========================\n");
	Adminnode* an;
	char ID[ADMINID_LENGTH_MAX];
	printf("请输入待查找管理员的ID："); scanf("%s", ID);
	an = findAdminByID(pHead, ID);
	if (an == NULL)
	{
		printf("查找失败\n\n");
		system("pause");
		showAdminManageUI(pHead);
	}
	else
	{
		printf("查找成功\n\n");
		printf("该管理员的信息为：\n");
		printf("ID：%s\n", an->data.ID);
		printf("密码：%s\n", an->data.password);
		printf("姓名：%s\n", an->data.name);
		printf("性别：%s\n", an->data.sex);
		printf("年龄：%d\n", an->data.age);
	}
	system("pause");
	showAdminManageUI(pHead);
}

void updateAdminUI(Adminnode* pHead)
{
	system("cls");
	printf("========================更新管理员信息===========================\n");
	Adminnode* an;
	char ID[ADMINID_LENGTH_MAX];
	printf("请输入待更新管理员的ID："); scanf("%s", ID);
	an = findAdminByID(pHead, ID);
	if (an == NULL)
	{
		printf("未找到该管理员\n\n");
		system("pause");
		showAdminManageUI(pHead);
	}
	else
	{
		printf("查找成功\n\n");
		printf("该管理员的信息为：\n");
		printf("ID：%s\n", an->data.ID);
		printf("密码：%s\n", an->data.password);
		printf("姓名：%s\n", an->data.name);
		printf("性别：%s\n", an->data.sex);
		printf("年龄：%d\n\n", an->data.age);
		printf("\n您可以更新该管理员的：\n");
		printf("(1) 姓名\n");
		printf("(2) 性别\n");
		printf("(3) 年龄\n");
		printf("(4) 取消更新\n");
		int index;
		scanf("%d", &index);
		switch (index)
		{
		case 1:
			printf("将其姓名修改为："); scanf("%s", an->data.name);
			pHead = updateAdminByID(pHead, ID, an->data);
			writeAdminIntoFile(pHead);
			break;
		case 2:
			printf("将性别名修改为："); scanf("%s", an->data.sex);
			pHead = updateAdminByID(pHead, ID, an->data);
			writeAdminIntoFile(pHead);
			break;
		case 3:
			printf("将性别名年龄为："); scanf("%d", &an->data.age);
			pHead = updateAdminByID(pHead, ID, an->data);
			writeAdminIntoFile(pHead);
		default:
			showAdminManageUI(pHead);
			break;
		}
		system("pause");
		showAdminManageUI(pHead);
	}
}

void showAdminManageUI(Adminnode* pHead)
{
	system("cls");
	printf("=====================系统管理员信息操作界面=====================\n");
	printf("\n请选择以下操作：\n");
	printf("(1) 添加系统管理员\n");
	printf("(2) 查找管理员信息\n");
	printf("(3) 更新管理员信息\n");
	printf("(4) 浏览全体系统管理员\n");
	printf("(5) 返回主界面\n");
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
			addAdminUI(pHead);
			break;
		case 2:
			findAdminUI(pHead);
			break;
		case 3:
			updateAdminUI(pHead);
		case 4:
			system("cls");
			printf("=======================浏览全体管理员信息==========================\n");
			printAdminTable(pHead);
			system("pause");
			showAdminManageUI(pHead);
			break;
		default:
			ShowAdminMainUI(pHead);
			break;
		}
	}
}

void addfoodUI(foodnode* pHead)
{
	system("cls");
	printf("========================添加菜品===========================\n");
	printf("请输入欲添加菜品的信息:\n");
	food a;
	printf("ID："); scanf("%s", a.id);
	printf("菜名："); scanf("%s", a.name);
	char foodtype[20];
	printf("种类："); scanf("%s", foodtype);
	a.foodtype = switchstoenum(foodtype);
	printf("价格："); scanf("%lf", &a.price);
	printf("销量："); scanf("%d", &a.orderCount);
	pHead = addfood(pHead, a);
	writefoodIntoFile(pHead);
	printf("添加成功\n\n");
	system("pause");
	showAdminfoodUI(pHead);
}

foodnode* findfoodUI(foodnode* pHead)
{
	system("cls");
	printf("=======================查找菜品信息==========================\n");
	foodnode* an;
	char ID[10];
	printf("请输入待查找菜品的ID："); scanf("%s", ID);
	an = findfoodByid(pHead, ID);
	if (an == NULL)
	{
		printf("查找失败\n\n");
		system("pause");
		showAdminfoodUI(pHead);
	}
	else
	{
		char foodtype[20];
		printf("查找成功\n\n");
		printf("该菜品的信息为：\n");
		printf("ID：%s\n", an->data.id);
		printf("菜名：%s\n", an->data.name);
		strcpy(foodtype, switchenumtos(an->data.foodtype));
		printf("类型：%s\n", foodtype);
		printf("价格：%.2lf\n", an->data.price);
		printf("销量：%d\n", an->data.orderCount);
	}
	system("pause");
	showAdminfoodUI(pHead);
	return an;
}

void updatefoodUI(foodnode* pHead)
{
	system("cls");
	printf("======================更新菜品信息=========================\n");
	foodnode* an;
	char ID[10];
	printf("请输入待查找菜品的ID："); scanf("%s", ID);
	an = findfoodByid(pHead, ID);
	if (an == NULL)
	{
		printf("查找失败\n\n");
		system("pause");
		showAdminfoodUI(pHead);
	}
	else
	{
		char foodtype[20];
		printf("查找成功\n\n");
		printf("该菜品的信息为：\n");
		printf("ID：%s\n", an->data.id);
		printf("菜名：%s\n", an->data.name);
		strcpy(foodtype, switchenumtos(an->data.foodtype));
		printf("类型：%s\n", foodtype);
		printf("价格：%.2lf\n", an->data.price);
		printf("销量：%d\n", an->data.orderCount);
		printf("\n您可以更新该菜品的：\n");
		printf("(1) id\n");
		printf("(2) 菜名\n");
		printf("(3) 类型\n");
		printf("(4) 价格\n");
		printf("(5) 删除该菜品\n");
		printf("(6) 取消更新\n");
		int index;
		scanf("%d", &index);
		switch (index)
		{
		case 1:
			printf("将其id修改为："); scanf("%s", an->data.id);
			pHead = updatefoodByid(pHead, an->data.id, an->data);
			writefoodIntoFile(pHead);
			break;
		case 2:
			printf("将其名称修改为："); scanf("%s", an->data.name);
			pHead = updatefoodByid(pHead, an->data.id, an->data);
			writefoodIntoFile(pHead);
			break;
		case 3:
			printf("将其类型修改为："); scanf("%s", foodtype);
			strcpy(foodtype, switchenumtos(an->data.foodtype));
			pHead = updatefoodByid(pHead, an->data.id, an->data);
			writefoodIntoFile(pHead);
			break;
		case 4:
			printf("将其价格为："); scanf("%lf", &an->data.price);
			pHead = updatefoodByid(pHead, an->data.id, an->data);
			writefoodIntoFile(pHead);
			break;
		case 5:
			pHead = deletefoodByID(pHead, an->data.id);
			printf("删除成功!\n");
			writefoodIntoFile(pHead);
			break;
		default:
			showAdminfoodUI(pHead);
			break;
		}
	}
	system("pause");
	showAdminfoodUI(pHead);
}

void showAdminfoodUI(foodnode* pHead)
{
	system("cls");
	printf("========================菜单信息操作界面===========================\n");
	printf("\n请选择以下操作：\n");
	printf("(1) 添加菜品\n");
	printf("(2) 查找菜品\n");
	printf("(3) 更新菜品信息\n");
	printf("(4) 浏览菜单\n");
	printf("(5) 返回主界面\n");
	while (true)
	{
		printf("请输入操作序号： 【  】");
		Adminnode* p = InitAdminTable();
		p = readAdminFromFile(p);
		int x = wherex(), y = wherey();
		gotoxy(x - 3, y);
		int index;
		scanf("%d", &index);
		switch (index)
		{
		case 1:
			addfoodUI(pHead);
			break;
		case 2:
			findfoodUI(pHead);
			break;
		case 3:
			updatefoodUI(pHead);
		case 4:
			system("cls");
			printf("========================浏览菜单信息===========================\n");
			printfoodTable(pHead);
			system("pause");
			showAdminfoodUI(pHead);
			break;
		default:
			ShowAdminMainUI(p);
			break;
		}
	}
}

void showcensusUI(foodnode* pHead)
{
	while (true)
	{
		system("cls");
		printf("========================统计分析界面===========================\n");
		printf("\n请选择以下操作：\n");
		printf("(1) 查看菜品销量前十\n");
		printf("(2) 查找今日服务员服务量前三\n");
		printf("(3) 查看餐桌使用情况排名\n");
		printf("(4) 返回主界面\n");
		printf("请输入操作序号： 【  】");
		int x = wherex(), y = wherey();
		gotoxy(x - 3, y);
		int index;
		int count = 0;
		waitor* w, * temp;
		foodnode* p = pHead;
		tablenode* orderTableListHead;
		Adminnode* ap = InitAdminTable();
		scanf("%d", &index);
		switch (index)
		{
		case 1:

			printf("%-10s\t%-10s\t%-5s\t%-5s\t%-7s\n", "食品id", "食品名称", "食品类型", "被点次数", "价格");
			while (!(p == NULL))//遍历链表
			{
				if (count >= 10) break;
				char* foodtype;
				foodtype = switchenumtos(p->data.foodtype);
				printf("%-10s\t%-10s \t%-10s \t%-10d\t%-7.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
				p = p->next;
				count++;
			}
			break;
		case 2:
			WaitorListHead->next = orderWaitorbycount();
			UpdateWaitorsInfo();
			LoadWaitors();
			temp = WaitorListHead->next;
			printf("\n%-10s \t%-10s \t%-10s", "姓名", "密码", "今日服务数量");
			count = 0;
			while (temp)
			{
				if (count >= 3) break;
				printf("\n%-10s \t%-10s \t%-10d", temp->name, temp->passwd, temp->sumofserve);
				temp = temp->next;
				count++;
			}
			printf("\n");
			break;
		case 3:
			orderTableListHead = orderTableByUseTimes();
			ShowTableUseTimesUI(orderTableListHead);
			readtableFromFile();
			break;
		default:
			ap = readAdminFromFile(ap);
			ShowAdminMainUI(ap);
			break;
		}
	}
}

void ShowAdminMainUI(Adminnode* pHead)
{
	system("cls");
	printf("*********************系统管理员主界面**********************\n\n\n");
	printf("             ---------------------------------             \n\n");
	printf("            |        (1) 用户管理             |            \n");
	printf("            |        (2) 菜单管理             |            \n");
	printf("            |        (3) 统计分析             |            \n");
	printf("            |        (4) 座位管理             |            \n");
	printf("            |        (5) 订单浏览             |            \n");
	printf("            |        (6) 退出                 |            \n");
	printf("             ---------------------------------             \n\n\n");
	printf("***********************************************************\n\n");
	while (true)
	{
		printf("请选择操作序号 【  】");
		int x = wherex(), y = wherey();
		gotoxy(x - 3, y);
		int index;
		scanf("%d", &index);
		foodnode* fHead = InitfoodTable();
		fHead = readfoodFromFile(fHead);
		switch (index)
		{
		case 1:
			ShowUserManageUI(pHead);
			break;
		case 2:
			showAdminfoodUI(fHead);
			break;
		case 3:
			showcensusUI(fHead);
			break;
		case 4:
			showAdminTableUI(tablesListHead);
			break;
		case 5:
			showOrderBrowseUI();
			break;
		case 6:
			ShowAdminLoginUI(pHead);
			return;
		}
	}
}

void ShowAdminLoginUI(Adminnode* pHead)
{
	while (true)
	{
		system("cls");
		printf("**********************管理员登录界面********************\n（ID输入-1返回角色选择界面）\n\n               请输入您的ID   >>>___________");
		int x = wherex(), y = wherey();
		gotoxy(x - 10, y);
		char ID[ADMINPAS_LENGTH_MAX];
		scanf("%s", ID);
		if (strcmp(ID, "-1") == 0)
		{
			break;  // 返回角色选择界面
		}
		printf("\n               请输入您的密码 >>>___________");
		x = wherex(), y = wherey();
		gotoxy(x - 10, y);
		char password[ADMINPAS_LENGTH_MAX];
		scanf("%s", password);
		Adminnode* currentAdmin = findAdminByID(pHead, ID);
		if (currentAdmin != NULL && strcmp(currentAdmin->data.password, password) == 0)
		{
			printf("\n\n\n登录成功!\n\n");
			system("pause");
			system("cls");
			ShowAdminMainUI(pHead);
		}
		else
		{
			printf("\n\n\nError>>>账户名不存在或密码输入错误，请重新输入！\n\n");
			system("pause");
			continue;
		}
	}
	
}

// 餐桌管理
void showAdminTableUI(tablenode* tHead)
{
	while (true)
	{
		system("cls");
		printf("======================餐桌管理界面=========================\n");
		ShowTableUI();
		printf("\n请选择以下操作：\n");
		printf("(1) 添加新餐桌类型\n");
		printf("(2) 移除旧餐桌类型\n");
		printf("(3) 修改某类型餐桌数量\n");
		printf("(4) 查看餐桌使用情况\n");
		printf("(5) 返回主界面\n");
		printf("请输入操作序号： 【  】");
		int x = wherex(), y = wherey();
		gotoxy(x - 3, y);
		int index;
		int count = 0;
		tablenode* p = tHead;
		Adminnode* ap = InitAdminTable();
		tablenode* orderTableListHead;
		scanf("%d", &index);
		switch (index)
		{
		case 1:
			addNewTableUI();
			// 写入更改
			writetableIntoFile(tablesListHead);
			break;
		case 2:
			removeTableTypeUI();
			printf("\n");
			writetableIntoFile(tablesListHead);
			break;
		case 3:
			printf("请选择修改方式（新增：1，削减：0）：");
			int option = 0;
			scanf("%d", &option);
			if (option)
			{
				increaseTableNumUI();
			}
			else
			{
				decreaseTableNumUI();
			}
			writetableIntoFile(tablesListHead);
			break;
		case 4:
			orderTableListHead = orderTableByUseTimes();
			ShowTableUseTimesUI(orderTableListHead);
			readtableFromFile();
			break;
		default:
			ap = readAdminFromFile(ap);
			ShowAdminMainUI(ap);
			break;
		}
	}
}
//从文件中读取餐桌信息(相当于创建单链表操作)
tablenode* readtableFromFile()
{
	FILE* fp;  // 文件指针
	fp = fopen(TABLE_FILE_PATH, "a+");
	// 判断文件是否能够正确打开 
	if_Is_Null_Then_End_Program(fp);
	// 从文件中读取食物信息
	int numOfSeat = 0;
	int captainOfSeat = 0;
	int useTimes = 0;
	tablesListHead = initTableList();
	while (fscanf(fp, "%d %d %d", &captainOfSeat, &numOfSeat, &useTimes) != EOF)
	{
		tablenode* t = (tablenode*)malloc(sizeof(tablenode));
		t->captainOfSeat = captainOfSeat;
		t->numOfSeat = numOfSeat;
		t->useTimes = useTimes;
		t->seatList = initSeatList(captainOfSeat ,numOfSeat);
		t->next = NULL;
		addTableNode(t);
	}
	//关闭文件
	fclose(fp);
	return tablesListHead;
}
//将链表中餐桌信息写入文件
bool writetableIntoFile(tablenode* pHead)
{
	if (pHead == NULL) //空表则直接退出函数,无需写入
	{
		return false;
	}
	FILE* fp;  // 文件指针
	fp = fopen(TABLE_FILE_PATH, "w+");
	// 判断文件是否能够正确打开 
	if_Is_Null_Then_End_Program(fp);
	tablenode* p = pHead->next;
	while (!(p == NULL))//遍历链表
	{
		fprintf(fp, "%d %d %d\n", p->captainOfSeat, p->numOfSeat, p->useTimes);
		p = p->next;
	}
	// 刷新缓冲区，将缓冲区的内容写入文件 
	fflush(fp);
	// 重置文件内部位置指针，确保位置指针指向文件开头
	rewind(fp);
	return true;
}

// 初始化餐桌链表
tablenode* initTableList()
{
	tablenode* head = (tablenode*)malloc(sizeof(tablenode));
	head->seatList = NULL;
	head->captainOfSeat = 0;  
	head->next = NULL;
	head->useTimes = 0;
	head->numOfSeat = 0;	// 存储餐桌类型数量
	return head;
}

// 初始化座位数组
seat* initSeatList(int captain, int length)
{
	seat* list = (seat*)malloc(sizeof(seat) * length);
	for (int i = 0; i < length; i++)
	{
		list[i].captain = captain;
		list[i].order = i + 1;
		list[i].IsSelected = 0;
	}
	return list;
}

seat* resizeSeatList(seat* seatList, int changeNum)
{
	seatList = (seat*)realloc(seatList, sizeof(seat) * changeNum);
	return seatList;
}

// 添加餐桌结点
bool addTableNode(tablenode* addNode)
{
	tablenode* p = tablesListHead;
	while (p->next != NULL)
	{
		p = p->next;
	}
	addNode->next = p->next;
	p->next = addNode;
	tablesListHead->numOfSeat++;
	return true;
}

// 删除餐桌结点
bool deleteTableNode(int captain)
{
	tablenode* p = tablesListHead->next;
	tablenode* pre = tablesListHead;
	// 查找指定类型餐桌
	while (p != NULL && p->captainOfSeat == captain)
	{
		pre = p;
		p = p->next;
	}
	if (p != NULL)
	{
		// 删除结点
		pre->next = p->next;
		tablesListHead->numOfSeat--;
		return true;
	}
	else
	{
		printf("\n无该类型餐桌，请检查后再次操作！\n");
		system("pause");
		return false;
	}
}

// 展示餐桌示意图
void ShowTableUI()
{
	printf("\n===================餐厅座位图======================\n ");
	tablenode* p = tablesListHead->next;
	if (p == NULL)
	{
		printf("\n\t\t\t餐厅暂未配置餐桌！\n\n");
		system("pause");
		return;
	}
	while (p != NULL)
	{
		printf("%10d人餐桌\t已有数量：%d\t使用次数：%d\n", p->captainOfSeat, p->numOfSeat, p->useTimes);
		for (int i = 0; i < p->numOfSeat; i++)
		{
			printf("[ ] ");
		}
		p = p->next;
		printf("\n\n");
	}
	printf("=========================================\n ");
}

// 添加指定数量新类型餐桌
bool addNewTableUI()
{
	system("cls");
	// 展示当前餐厅餐桌情况
	ShowTableUI();
	printf("=========================================\n ");
	printf("请输入餐桌可坐人数及添加数量(空格分隔)：\b");
	int captain, num;
	scanf("%d %d", &captain, &num);
	if (captain > 0 && num > 0)
	{
		tablenode* newNode = (tablenode*)malloc(sizeof(tablenode));
		newNode->captainOfSeat = captain;
		newNode->useTimes = 0;
		newNode->numOfSeat = num;
		newNode->seatList = (seat*)malloc(sizeof(seat));
		newNode->next = NULL;
		if (addTableNode(newNode))
		{
			printf("添加成功！\n");
			system("pause");
		}
		else
		{
			printf("添加失败，请重试！\n");
			system("pause");
			return false;
		}
		return true;
	}
	else 
	{
		printf("餐桌容量及餐桌数量必须为正整数，请检查后重试！\n");
		system("pause");
		return false;
	}
}

// 删除某类型的餐桌
bool removeTableTypeUI()
{
	system("cls");
	ShowTableUI();
	printf("=========================================\n ");
	printf("请输入要删除的餐桌类型（可坐人数）： ");
	int captain;
	scanf("%d", &captain);
	if (captain > 0)
	{
		tablenode* p = tablesListHead->next;
		tablenode* pre = tablesListHead;
		while (p->captainOfSeat != captain)
		{
			pre = p;
			p = p->next;
		}
		if (p != NULL)
		{
			pre->next = p->next;
			printf("删除成功！\n");
			system("pause");
			return true;
		}
		else 
		{
			printf("无该类型餐桌，请检查后重试！\n");
			system("pause");
			return false;
		}
		
	}
	else
	{
		printf("餐桌容量有误，请检查后重试！\n");
		system("pause");
		return false;
	}
}
// 添加指定数量某类型的餐桌
bool increaseTableNumUI()
{
	system("cls");
	ShowTableUI();
	printf("=========================================\n ");
	printf("请输入要调整的餐桌类型（可坐人数）及新增数量(空格分隔)：__ __\b\b\b\b\b");
	int captain, newNum;
	scanf("%d %d", &captain, &newNum);
	if (captain > 0 && newNum > 0)
	{
		tablenode* p = tablesListHead->next;
		while (p->captainOfSeat != captain)
		{
			p = p->next;
		}
		if (p != NULL)
		{
			p->numOfSeat += newNum;
			p->seatList = resizeSeatList(p->seatList, p->numOfSeat);
			printf("调整成功！\n");
			system("pause");
			return true;
		}
		else
		{
			printf("无该类型餐桌，请检查后重试！\n");
			system("pause");
			return false;
		}
	}
	else
	{
		printf("餐桌容量或调整数量有误，请检查后重试！\n");
		system("pause");
		return false;
	}
}
// 减少指定数量某类型的餐桌
bool decreaseTableNumUI()
{
	system("cls");
	ShowTableUI();
	printf("=========================================\n ");
	printf("请输入要调整的餐桌类型（可坐人数）及减少数量(空格分隔)：__ __\b\b\b\b");
	int captain, newNum;
	scanf("%d %d", &captain, &newNum);
	if (captain > 0 && newNum > 0)
	{
		tablenode* p = tablesListHead->next;
		while (p->captainOfSeat != captain)
		{
			p = p->next;
		}
		if (p != NULL)
		{
			p->numOfSeat -= newNum;
			p->seatList = resizeSeatList(p->seatList, p->numOfSeat);
			printf("调整成功！\n");
			system("pause");
			return true;
		}
		else
		{
			printf("无该类型餐桌，请检查后重试！\n");
			system("pause");
			return false;
		}
	}
	else
	{
		printf("餐桌容量或减少数量有误，请检查后重试！\n");
		system("pause");
		return false;
	}
}
// 增加某类型餐桌的使用次数
bool addTableUseTimes(int captain)
{
	tablenode* p = tablesListHead->next;
	// 查找指定类型餐桌
	while (p != NULL && p->captainOfSeat != captain)
	{
		p = p->next;
	}
	if (p != NULL)
	{
		p->useTimes++;
		return true;
	}
	else
	{
		printf("\n无该类型餐桌，请检查后再次操作！\n");
		system("pause");
		return false;
	}
}


// 统计餐桌使用频率并排序
tablenode* orderTableByUseTimes()
{
	tablenode* pNode = (tablenode*)malloc(sizeof(tablenode));
	pNode->next = NULL;
	tablenode* pf = tablesListHead->next;
	if (pf == NULL)//如果待排序的链表为空
	{
		return NULL;
	}
	else if (pf->next == NULL)  // 只有一个节点，无需排序
	{
		return pf;
	}
	else
	{
		tablenode* pfa = pf->next;//永远指向已被排序结点的下一个结点
		while (1)
		{
			if (pNode == NULL || pf->useTimes >= pNode->useTimes)//如果应当添加到链表的第一位上
			{
				pf->next = pNode;
				pNode = pf;
			}
			else//如果应当添加到非空链表的非第一位上
			{
				tablenode* pr = pNode;
				tablenode* q = pr->next;
				while (1)//试图遍历链表
				{
					if (pr->useTimes >= pf->useTimes)//“有可能”迭代到这个新结点该到的位置上了
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
							if (q->useTimes <= pf->useTimes)//真的迭代到这个新结点该到的位置上了
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

// 重置座位属性
bool resetSeat(int captain, int order)
{
	tablenode* p = tablesListHead->next;
	// 查找指定类型餐桌
	while (p != NULL && p->captainOfSeat == captain)
	{
		p = p->next;
	}
	if (p != NULL)
	{
		p->seatList[order].IsSelected = 0;
		return true;
	}
	else
	{
		printf("\n无该餐桌，请检查后再次操作！\n");
		system("pause");
		return false;
	}
}

// 判断某类型第order个座位是否为空
bool isSelected(int captain, int order)
{
	tablenode* p = tablesListHead->next;
	while (p != NULL && p->captainOfSeat != captain)
	{
		p = p->next;
	}
	if (p->seatList[order].IsSelected == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 标记座位已选择
void setSelected(int captain, int order)
{
	tablenode* p = tablesListHead->next;
	while (p != NULL && p->captainOfSeat != captain)
	{
		p = p->next;
	}
	if (p != NULL)
	{
		p->seatList[order].IsSelected = 1;
	}
	else
	{
		return;
	}
}

// 显示餐桌使用次数排序表
void ShowTableUseTimesUI(tablenode* orderList)
{
	tablenode* p = orderList->next;
	system("cls");
	printf("======================餐桌管理界面=========================\n");
	if (p == NULL)
	{
		printf("\n\t\t\t暂无餐桌配置\n\n");
		system("pause");
		return;
	}
	printf("\n\t%-10s \t%-10s \t%-10s", "餐桌类型", "现有数量", "使用次数");
	while (p != NULL && p->next!=NULL)
	{
		printf("\n\t%-10d \t%-10d \t%-10d", p->captainOfSeat, p->numOfSeat, p->useTimes);
		p = p->next;
	}
	printf("\n");
	system("pause");
	return;
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