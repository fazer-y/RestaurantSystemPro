#define _CRT_SECURE_NO_WARNINGS
#include "Core_tableManage.h"

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
		t->seatList = initSeatList(captainOfSeat, numOfSeat);
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
int isSelected(int captain, int order)
{
	tablenode* p = tablesListHead->next;
	while (p != NULL && p->captainOfSeat != captain)
	{
		p = p->next;
	}
	if (p != NULL)
	{
		if (p->seatList[order].IsSelected == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		printf("\n暂无该类型餐桌（%d人桌），请重新选择！\n", captain);
		system("pause");
		return -1;
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
	while (p != NULL && p->next != NULL)
	{
		printf("\n\t%-10d \t%-10d \t%-10d", p->captainOfSeat, p->numOfSeat, p->useTimes);
		p = p->next;
	}
	printf("\n");
	system("pause");
	return;
}


void ShowSeatMap()
{
	system("cls");
	printf("===============餐厅实时座位图==================\n ");
	tablenode* p = tablesListHead->next;
	if (p == NULL)
	{
		printf("\n\t\t\t餐厅暂未配置餐桌！\n\n");
		system("pause");
		return;
	}
	while (p != NULL)
	{
		printf("\t%d人餐桌\n", p->captainOfSeat);
		for (int i = 0; i < p->numOfSeat; i++)
		{
			if (p->seatList[i].IsSelected == 0)
				printf(" [ ] ");
			else
				printf(" [1] ");
		}
		p = p->next;
		printf("\n");
	}
	printf("\n===================================================\n");
	system("pause");
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