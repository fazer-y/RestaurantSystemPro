#define _CRT_SECURE_NO_WARNINGS
#include "Core_Administrater.h"


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
			ShowWelcomeUI();  // 返回角色选择界面
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