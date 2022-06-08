#define _CRT_SECURE_NO_WARNINGS
#include "Core_foodManage.h"

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

void Revereshow(foodnode* p) {
	if (p) {
		Revereshow(p->next);
		char foodtype[20];
		//将枚举类型的菜品信息转化为字符串以便输出
		switch (p->data.foodtype)
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
		printf("%-10s\t%-10s \t%-10s \t%-10d\t%-7.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
	}
}


void ShowMenu() {
	system("cls");
	printf("=============================菜单=================================\n");
	printf("%-10s\t%-10s\t%-5s\t%-5s\t%-7s\n", "食品id", "食品名称", "食品类型", "被点次数", "价格");
	LoadMyMenu();
	foodnode* p = foodsListHead->next;
	Revereshow(p);
	printf("\n===================================================================\n");
}

double getPriceoffood(char* id)
{
	foodnode* temp = foodsListHead->next;
	while (temp)
	{
		if (strcmp(id, temp->data.id) == 0)
			return temp->data.price;
		temp = temp->next;
	}
	return 0;
}

char* getNameofFood(char* id) {
	foodnode* temp = foodsListHead;
	while (temp)
	{
		if (strcmp(id, temp->data.id) == 0)
			return temp->data.name;
		temp = temp->next;
	}
	return NULL;
}

void UpdateCountofFood(char* id) {
	foodnode* temp = foodsListHead->next;
	while (temp) {
		if (strcmp(temp->data.id, id) == 0) {
			temp->data.orderCount += 1;
			break;
		}
		temp = temp->next;
	}
}

void ReWriteBackFood() {
	foodnode* temp = foodsListHead->next;
	FILE* fp = fopen("menu.txt", "w");
	if (fp == NULL) {
		perror("文件读取失败");
		return;
	}
	while (temp) {
		char typeoffood[FOODNAME_LENGTH_MAX];
		enum foodType type = temp->data.foodtype;
		switch (type) {
		case specaility:
			strcpy(typeoffood, "招牌菜");
			break;
		case staple:
			strcpy(typeoffood, "主食");
			break;
		case  hot:
			strcpy(typeoffood, "热菜");
			break;
		case cold:
			strcpy(typeoffood, "凉菜");
			break;
		case soup:
			strcpy(typeoffood, "汤");
			break;
		case beverage:
			strcpy(typeoffood, "饮料");
			break;
		}
		fprintf(fp, "%s %s %s %d %.2lf\n", temp->data.id, temp->data.name, typeoffood, temp->data.orderCount, temp->data.price);
		temp = temp->next;
	}
	fclose(fp);
}

void LoadMyMenu() {
	foodsListHead = (foodnode*)malloc(sizeof(foodnode));
	foodsListHead->next = NULL;
	FILE* fp = fopen("menu.txt", "r");
	if (fp == NULL) {
		perror("文件读取失败");
		return;
	}
	char id[10];
	char name[FOODNAME_LENGTH_MAX];
	char foodtype[20];
	double price;
	int orderCount;
	while (5 == fscanf(fp, "%s %s %s %d %lf", id, name, foodtype, &orderCount, &price))
	{
		foodnode* f = (foodnode*)malloc(sizeof(foodnode));
		strcpy(f->data.name, name);
		strcpy(f->data.id, id);
		f->data.price = price;
		f->data.orderCount = orderCount;


		if (strcmp(foodtype, "招牌菜") == 0)
		{
			f->data.foodtype = specaility;
		}
		else if (strcmp(foodtype, "热菜") == 0)
		{
			f->data.foodtype = hot;
		}
		else if (strcmp(foodtype, "凉菜") == 0)
		{
			f->data.foodtype = cold;
		}
		else if (strcmp(foodtype, "饮料") == 0)
		{
			f->data.foodtype = beverage;
		}
		else if (strcmp(foodtype, "汤品") == 0)
		{
			f->data.foodtype = soup;
		}
		else {
			f->data.foodtype = staple;
		}
		//加入链表
		f->next = foodsListHead->next;
		foodsListHead->next = f;
	}
	//关闭文件
	fclose(fp);
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