#define _CRT_SECURE_NO_WARNINGS
#include "Core_tableManage.h"

//���ļ��ж�ȡ������Ϣ(�൱�ڴ������������)
tablenode* readtableFromFile()
{
	FILE* fp;  // �ļ�ָ��
	fp = fopen(TABLE_FILE_PATH, "a+");
	// �ж��ļ��Ƿ��ܹ���ȷ�� 
	if_Is_Null_Then_End_Program(fp);
	// ���ļ��ж�ȡʳ����Ϣ
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
	//�ر��ļ�
	fclose(fp);
	return tablesListHead;
}
//�������в�����Ϣд���ļ�
bool writetableIntoFile(tablenode* pHead)
{
	if (pHead == NULL) //�ձ���ֱ���˳�����,����д��
	{
		return false;
	}
	FILE* fp;  // �ļ�ָ��
	fp = fopen(TABLE_FILE_PATH, "w+");
	// �ж��ļ��Ƿ��ܹ���ȷ�� 
	if_Is_Null_Then_End_Program(fp);
	tablenode* p = pHead->next;
	while (!(p == NULL))//��������
	{
		fprintf(fp, "%d %d %d\n", p->captainOfSeat, p->numOfSeat, p->useTimes);
		p = p->next;
	}
	// ˢ�»���������������������д���ļ� 
	fflush(fp);
	// �����ļ��ڲ�λ��ָ�룬ȷ��λ��ָ��ָ���ļ���ͷ
	rewind(fp);
	return true;
}

// ��ʼ����������
tablenode* initTableList()
{
	tablenode* head = (tablenode*)malloc(sizeof(tablenode));
	head->seatList = NULL;
	head->captainOfSeat = 0;
	head->next = NULL;
	head->useTimes = 0;
	head->numOfSeat = 0;	// �洢������������
	return head;
}

// ��ʼ����λ����
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

// ��Ӳ������
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

// ɾ���������
bool deleteTableNode(int captain)
{
	tablenode* p = tablesListHead->next;
	tablenode* pre = tablesListHead;
	// ����ָ�����Ͳ���
	while (p != NULL && p->captainOfSeat == captain)
	{
		pre = p;
		p = p->next;
	}
	if (p != NULL)
	{
		// ɾ�����
		pre->next = p->next;
		tablesListHead->numOfSeat--;
		return true;
	}
	else
	{
		printf("\n�޸����Ͳ�����������ٴβ�����\n");
		system("pause");
		return false;
	}
}

// չʾ����ʾ��ͼ
void ShowTableUI()
{
	printf("\n===================������λͼ======================\n ");
	tablenode* p = tablesListHead->next;
	if (p == NULL)
	{
		printf("\n\t\t\t������δ���ò�����\n\n");
		system("pause");
		return;
	}
	while (p != NULL)
	{
		printf("%10d�˲���\t����������%d\tʹ�ô�����%d\n", p->captainOfSeat, p->numOfSeat, p->useTimes);
		for (int i = 0; i < p->numOfSeat; i++)
		{
			printf("[ ] ");
		}
		p = p->next;
		printf("\n\n");
	}
	printf("=========================================\n ");
}

// ���ָ�����������Ͳ���
bool addNewTableUI()
{
	system("cls");
	// չʾ��ǰ�����������
	ShowTableUI();
	printf("=========================================\n ");
	printf("��������������������������(�ո�ָ�)��\b");
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
			printf("��ӳɹ���\n");
			system("pause");
		}
		else
		{
			printf("���ʧ�ܣ������ԣ�\n");
			system("pause");
			return false;
		}
		return true;
	}
	else
	{
		printf("����������������������Ϊ����������������ԣ�\n");
		system("pause");
		return false;
	}
}

// ɾ��ĳ���͵Ĳ���
bool removeTableTypeUI()
{
	system("cls");
	ShowTableUI();
	printf("=========================================\n ");
	printf("������Ҫɾ���Ĳ������ͣ������������� ");
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
			printf("ɾ���ɹ���\n");
			system("pause");
			return true;
		}
		else
		{
			printf("�޸����Ͳ�������������ԣ�\n");
			system("pause");
			return false;
		}

	}
	else
	{
		printf("��������������������ԣ�\n");
		system("pause");
		return false;
	}
}
// ���ָ������ĳ���͵Ĳ���
bool increaseTableNumUI()
{
	system("cls");
	ShowTableUI();
	printf("=========================================\n ");
	printf("������Ҫ�����Ĳ������ͣ���������������������(�ո�ָ�)��__ __\b\b\b\b\b");
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
			printf("�����ɹ���\n");
			system("pause");
			return true;
		}
		else
		{
			printf("�޸����Ͳ�������������ԣ�\n");
			system("pause");
			return false;
		}
	}
	else
	{
		printf("�����������������������������ԣ�\n");
		system("pause");
		return false;
	}
}
// ����ָ������ĳ���͵Ĳ���
bool decreaseTableNumUI()
{
	system("cls");
	ShowTableUI();
	printf("=========================================\n ");
	printf("������Ҫ�����Ĳ������ͣ���������������������(�ո�ָ�)��__ __\b\b\b\b");
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
			printf("�����ɹ���\n");
			system("pause");
			return true;
		}
		else
		{
			printf("�޸����Ͳ�������������ԣ�\n");
			system("pause");
			return false;
		}
	}
	else
	{
		printf("�����������������������������ԣ�\n");
		system("pause");
		return false;
	}
}
// ����ĳ���Ͳ�����ʹ�ô���
bool addTableUseTimes(int captain)
{
	tablenode* p = tablesListHead->next;
	// ����ָ�����Ͳ���
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
		printf("\n�޸����Ͳ�����������ٴβ�����\n");
		system("pause");
		return false;
	}
}


// ͳ�Ʋ���ʹ��Ƶ�ʲ�����
tablenode* orderTableByUseTimes()
{
	tablenode* pNode = (tablenode*)malloc(sizeof(tablenode));
	pNode->next = NULL;
	tablenode* pf = tablesListHead->next;
	if (pf == NULL)//��������������Ϊ��
	{
		return NULL;
	}
	else if (pf->next == NULL)  // ֻ��һ���ڵ㣬��������
	{
		return pf;
	}
	else
	{
		tablenode* pfa = pf->next;//��Զָ���ѱ����������һ�����
		while (1)
		{
			if (pNode == NULL || pf->useTimes >= pNode->useTimes)//���Ӧ����ӵ�����ĵ�һλ��
			{
				pf->next = pNode;
				pNode = pf;
			}
			else//���Ӧ����ӵ��ǿ�����ķǵ�һλ��
			{
				tablenode* pr = pNode;
				tablenode* q = pr->next;
				while (1)//��ͼ��������
				{
					if (pr->useTimes >= pf->useTimes)//���п��ܡ�����������½��õ���λ������
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
							if (q->useTimes <= pf->useTimes)//��ĵ���������½��õ���λ������
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

// ������λ����
bool resetSeat(int captain, int order)
{
	tablenode* p = tablesListHead->next;
	// ����ָ�����Ͳ���
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
		printf("\n�޸ò�����������ٴβ�����\n");
		system("pause");
		return false;
	}
}

// �ж�ĳ���͵�order����λ�Ƿ�Ϊ��
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
		printf("\n���޸����Ͳ�����%d��������������ѡ��\n", captain);
		system("pause");
		return -1;
	}

}

// �����λ��ѡ��
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

// ��ʾ����ʹ�ô��������
void ShowTableUseTimesUI(tablenode* orderList)
{
	tablenode* p = orderList->next;
	system("cls");
	printf("======================�����������=========================\n");
	if (p == NULL)
	{
		printf("\n\t\t\t���޲�������\n\n");
		system("pause");
		return;
	}
	printf("\n\t%-10s \t%-10s \t%-10s", "��������", "��������", "ʹ�ô���");
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
	printf("===============����ʵʱ��λͼ==================\n ");
	tablenode* p = tablesListHead->next;
	if (p == NULL)
	{
		printf("\n\t\t\t������δ���ò�����\n\n");
		system("pause");
		return;
	}
	while (p != NULL)
	{
		printf("\t%d�˲���\n", p->captainOfSeat);
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

// ��������
void showAdminTableUI(tablenode* tHead)
{
	while (true)
	{
		system("cls");
		printf("======================�����������=========================\n");
		ShowTableUI();
		printf("\n��ѡ�����²�����\n");
		printf("(1) ����²�������\n");
		printf("(2) �Ƴ��ɲ�������\n");
		printf("(3) �޸�ĳ���Ͳ�������\n");
		printf("(4) �鿴����ʹ�����\n");
		printf("(5) ����������\n");
		printf("�����������ţ� ��  ��");
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
			// д�����
			writetableIntoFile(tablesListHead);
			break;
		case 2:
			removeTableTypeUI();
			printf("\n");
			writetableIntoFile(tablesListHead);
			break;
		case 3:
			printf("��ѡ���޸ķ�ʽ��������1��������0����");
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