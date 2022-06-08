/*
 * @Author: ��
 * @ID: 202000810081
 * @Date: 2022-05-31
 * @LastEditors: LAPTOP-44TSMLLA
 * @Description:��Դ�����ļ���¼��ϵͳ����Ա�����������������Ҫ�õ�������������ļ������������壬�󲿷�UI������ƺ������壬��������Ϊ����
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
	if (pHead == NULL)//���Ҫ��ӵ�һ����������
	{
		pNode->next = pHead;
		pHead = pNode;
	}
	else//���Ҫ��ӵ�һ�� �ǿ����� ��
	{
		if (pNode->data.age <= pHead->data.age)//���Ӧ����ӵ��ǿ������ ��һλ ��
		{
			pNode->next = pHead;
			pHead = pNode;
		}
		else//���Ӧ����ӵ��ǿ������ �ǵ�һλ ��
		{
			Adminnode* pr = pHead;
			Adminnode* q = pr->next;
			while (1)//��ͼ��������
			{
				if (pr->data.age <= pNode->data.age)//���п��ܡ�����������½��õ���λ������
				{
					if (q == NULL)//�����ǰλ�� �� �������һλ
					{
						//ֱ����������ӵ�����β��
						pNode->next = pr->next;
						pr->next = pNode;
						break;
					}
					else//�����ǰλ�� ���� �������һλ
					{
						if (q->data.age >= pNode->data.age)//��ĵ���������½��õ���λ������
						{
							//����½�㵽���λ����
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
				q = q->next;//��������ڵ�
			}
		}
	}

	//һ��Ҫ�����µ�����ͷ��ַ����Ϊ�п�������ͷ��ַ���ϱߴ����б��޸���
	return pHead;
}

Adminnode* findAdminByID(Adminnode* pHead, char* ID)
{
	if (pHead == NULL) //�ձ���ֱ���˳�����
	{
		return NULL;
	}
	Adminnode* p = pHead;
	while (!(p == NULL))//��������
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
	printf("%-15s\t%-10s\t%-10s\t%-2s\t%-4s\n", "�˺�", "����", "����", "�Ա�", "����");
	while (!(p == NULL))//��������
	{
		printf("%-15s\t%-10s\t%-10s\t%-2s\t%-4d\n", p->data.ID, p->data.password, p->data.name, p->data.sex, p->data.age);
		p = p->next;
	}
}

Adminnode* updateAdminByID(Adminnode* pHead, char* ID, Admin data)
{
	if (pHead == NULL) //�ձ���ֱ���˳�����
	{
		return NULL;
	}
	Adminnode* p = pHead;
	while (!(p == NULL))//��ͼ��������
	{
		if (strcmp(p->data.ID, ID) == 0)
		{
			p->data = data;//���½����Ϣ
		}
		p = p->next;
	}
	return pHead;
}

Adminnode* readAdminFromFile()
{
	FILE* fp;  // �ļ�ָ��
	fp = fopen(ADMIN_FILE_PATH, "a+");
	// �ж��ļ��Ƿ��ܹ���ȷ�� 
	if_Is_Null_Then_End_Program(fp);
	// ���ļ��ж�ȡ����Ա��Ϣ
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
	//�ر��ļ�
	fclose(fp);
	return an;
}

bool writeAdminIntoFile(Adminnode* pHead)
{
	if (pHead == NULL) //�ձ���ֱ���˳�����,����д��
	{
		return false;
	}
	FILE* fp;  // �ļ�ָ��
	fp = fopen(ADMIN_FILE_PATH, "w+");
	// �ж��ļ��Ƿ��ܹ���ȷ�� 
	if_Is_Null_Then_End_Program(fp);
	Adminnode* p = pHead;
	while (!(p == NULL))//��������
	{
		fprintf(fp, "%s %s %s %s %d\n", p->data.ID, p->data.password, p->data.name, p->data.sex, p->data.age);
		p = p->next;
	}
	// ˢ�»���������������������д���ļ� 
	fflush(fp);
	// �����ļ��ڲ�λ��ָ�룬ȷ��λ��ָ��ָ���ļ���ͷ
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
	//���ݴ������ݴ���һ���µ�����ڵ�
	foodnode* pNode = (foodnode*)malloc(sizeof(foodnode));
	if_Is_Null_Then_End_Program(pNode);
	pNode->data = data;
	pNode->next = NULL;

	if (pHead == NULL)//���Ҫ��ӵ�һ�� ������ ��
	{
		pNode->next = pHead;
		pHead = pNode;
	}
	else//���Ҫ��ӵ�һ�� �ǿ����� ��
	{
		foodnode* pr = NULL;
		pr = pHead;
		while (!(pr->next == NULL))//����������β��
		{
			pr = pr->next;
		}
		pr->next = pNode;//����½�㵽����β��
	}
	return pHead;
}

foodnode* findfoodByid(foodnode* pHead, char* ID)
{
	if (pHead == NULL) //�ձ���ֱ���˳�����
	{
		return NULL;
	}
	foodnode* p = pHead;
	while (!(p == NULL))//��������
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
		strcpy(foodtype, "���Ʋ�");
		break;
	case hot:
		strcpy(foodtype, "�Ȳ�");
		break;
	case cold:
		strcpy(foodtype, "����");
		break;
	case soup:
		strcpy(foodtype, "��Ʒ");
		break;
	case staple:
		strcpy(foodtype, "��ʳ");
		break;
	case beverage:
		strcpy(foodtype, "����");
		break;
	default:
		break;
	}
	return foodtype;
}

enum foodType switchstoenum(char* type)
{
	if (strcmp(type, "���Ʋ�") == 0)
	{
		return specaility;
	}
	else if (strcmp(type, "�Ȳ�") == 0)
	{
		return hot;
	}
	else if (strcmp(type, "����") == 0)
	{
		return cold;
	}
	else if (strcmp(type, "����") == 0)
	{
		return beverage;
	}
	else if (strcmp(type, "��Ʒ") == 0)
	{
		return soup;
	}
	else if (strcmp(type, "��ʳ") == 0)
	{
		return staple;
	}
	else
	{
		printf("�������");
	}
}

foodnode* deletefoodByID(foodnode* pHead, char* ID)
{
	if (pHead == NULL) //�ձ�
	{
		return NULL;
	}
	//�����ڱ�ͷ���������⴦��
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
			if (ID == pNext->data.id)//����ҵ�
			{
				pDelete = pNext;
				pLast->next = pNext->next;
			}

			if (pNext->next == NULL)//������������β
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
	if (pf == NULL)//��������������Ϊ��
	{
		return NULL;
	}

	else
	{
		foodnode* pfa = pHead->next;//��Զָ���ѱ����������һ�����
		while (1)
		{
			if (pNode == NULL || pf->data.orderCount >= pNode->data.orderCount)//���Ӧ����ӵ�����ĵ�һλ��
			{
				pf->next = pNode;
				pNode = pf;
			}
			else//���Ӧ����ӵ��ǿ�����ķǵ�һλ��
			{
				foodnode* pr = pNode;
				foodnode* q = pr->next;
				while (1)//��ͼ��������
				{
					if (pr->data.orderCount >= pf->data.orderCount)//���п��ܡ�����������½��õ���λ������
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
							if (q->data.orderCount <= pf->data.orderCount)//��ĵ���������½��õ���λ������
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

foodnode* updatefoodByid(foodnode* pHead, char* ID, food data)
{
	if (pHead == NULL) //�ձ���ֱ���˳�����
	{
		return NULL;
	}
	foodnode* p = pHead;
	while (!(p == NULL))//��������
	{
		if (strcmp(p->data.id, ID) == 0) {
			p->data = data;//���½����Ϣ
		}
		p = p->next;
	}
	return pHead;
}

void printfoodTable(foodnode* pHead)
{
	foodnode* p = pHead;
	printf("%-10s\t%-10s\t%-5s\t%-5s\t%-7s\n", "ʳƷid", "ʳƷ����", "ʳƷ����", "�������", "�۸�");
	while (!(p == NULL))//��������
	{
		char foodtype[20];
		strcpy(foodtype, switchenumtos(p->data.foodtype));
		printf("%-10s\t%-10s \t%-10s \t%-10d\t%-7.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
		p = p->next;
	}
}

foodnode* readfoodFromFile(foodnode* pHead)
{
	FILE* fp;  // �ļ�ָ��
	fp = fopen(FOOD_FILE_PATH, "a+");
	// �ж��ļ��Ƿ��ܹ���ȷ�� 
	if_Is_Null_Then_End_Program(fp);
	// ���ļ��ж�ȡʳ����Ϣ
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
		//���ı��ж������ַ�����Ʒ����ת��Ϊö�������Ա�洢
		f.foodtype = switchstoenum(foodtype);
		fn = addfood(fn, f);
		num++;
		fn->number = num;
	}
	//�ر��ļ�
	fclose(fp);
	return fn;
}

bool writefoodIntoFile(foodnode* pHead)
{
	if (pHead == NULL) //�ձ���ֱ���˳�����,����д��
	{
		return false;
	}
	FILE* fp;  // �ļ�ָ��
	fp = fopen(FOOD_FILE_PATH, "w+");
	// �ж��ļ��Ƿ��ܹ���ȷ�� 
	if_Is_Null_Then_End_Program(fp);
	foodnode* p = pHead;
	while (!(p == NULL))//��������
	{
		char foodtype[20];
		strcpy(foodtype, switchenumtos(p->data.foodtype));
		fprintf(fp, "%s %s %s %d %.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
		p = p->next;
	}
	// ˢ�»���������������������д���ļ� 
	fflush(fp);
	// �����ļ��ڲ�λ��ָ�룬ȷ��λ��ָ��ָ���ļ���ͷ
	rewind(fp);
	return true;
}

void if_Is_Null_Then_End_Program(void* ptr)
{
	if (ptr == NULL)
	{
		printf("���������� !\n�����˳�����...\n");
		exit(EXIT_FAILURE);
	}
}

void ShowUserManageUI(Adminnode* pHead)
{
	system("cls");
	printf("========================�û��������===========================\n");
	printf("\n��ѡ�����²�����\n");
	printf("(1) ����ϵͳ����Ա��Ϣ\n");
	printf("(2) �������Ա��Ϣ\n");
	printf("(3) ����������\n");
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

void addAdminUI(Adminnode* pHead)
{
	system("cls");
	printf("========================���ϵͳ����Ա==========================\n");
	printf("�����������ϵͳ����Ա����Ϣ:\n");
	Admin a;
	printf("ID��"); scanf("%s", a.ID);
	printf("���룺"); scanf("%s", a.password);
	printf("������"); scanf("%s", a.name);
	printf("�Ա�"); scanf("%s", a.sex);
	printf("���䣺"); scanf("%d", &a.age);
	pHead = addAdminByOrder(pHead, a);
	writeAdminIntoFile(pHead);
	printf("��ӳɹ�\n\n");
	system("pause");
	ShowUserManageUI(pHead);
}

void findAdminUI(Adminnode* pHead)
{
	system("cls");
	printf("========================���ҹ���Ա��Ϣ===========================\n");
	Adminnode* an;
	char ID[ADMINID_LENGTH_MAX];
	printf("����������ҹ���Ա��ID��"); scanf("%s", ID);
	an = findAdminByID(pHead, ID);
	if (an == NULL)
	{
		printf("����ʧ��\n\n");
		system("pause");
		showAdminManageUI(pHead);
	}
	else
	{
		printf("���ҳɹ�\n\n");
		printf("�ù���Ա����ϢΪ��\n");
		printf("ID��%s\n", an->data.ID);
		printf("���룺%s\n", an->data.password);
		printf("������%s\n", an->data.name);
		printf("�Ա�%s\n", an->data.sex);
		printf("���䣺%d\n", an->data.age);
	}
	system("pause");
	showAdminManageUI(pHead);
}

void updateAdminUI(Adminnode* pHead)
{
	system("cls");
	printf("========================���¹���Ա��Ϣ===========================\n");
	Adminnode* an;
	char ID[ADMINID_LENGTH_MAX];
	printf("����������¹���Ա��ID��"); scanf("%s", ID);
	an = findAdminByID(pHead, ID);
	if (an == NULL)
	{
		printf("δ�ҵ��ù���Ա\n\n");
		system("pause");
		showAdminManageUI(pHead);
	}
	else
	{
		printf("���ҳɹ�\n\n");
		printf("�ù���Ա����ϢΪ��\n");
		printf("ID��%s\n", an->data.ID);
		printf("���룺%s\n", an->data.password);
		printf("������%s\n", an->data.name);
		printf("�Ա�%s\n", an->data.sex);
		printf("���䣺%d\n\n", an->data.age);
		printf("\n�����Ը��¸ù���Ա�ģ�\n");
		printf("(1) ����\n");
		printf("(2) �Ա�\n");
		printf("(3) ����\n");
		printf("(4) ȡ������\n");
		int index;
		scanf("%d", &index);
		switch (index)
		{
		case 1:
			printf("���������޸�Ϊ��"); scanf("%s", an->data.name);
			pHead = updateAdminByID(pHead, ID, an->data);
			writeAdminIntoFile(pHead);
			break;
		case 2:
			printf("���Ա����޸�Ϊ��"); scanf("%s", an->data.sex);
			pHead = updateAdminByID(pHead, ID, an->data);
			writeAdminIntoFile(pHead);
			break;
		case 3:
			printf("���Ա�������Ϊ��"); scanf("%d", &an->data.age);
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
	printf("=====================ϵͳ����Ա��Ϣ��������=====================\n");
	printf("\n��ѡ�����²�����\n");
	printf("(1) ���ϵͳ����Ա\n");
	printf("(2) ���ҹ���Ա��Ϣ\n");
	printf("(3) ���¹���Ա��Ϣ\n");
	printf("(4) ���ȫ��ϵͳ����Ա\n");
	printf("(5) ����������\n");
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
			addAdminUI(pHead);
			break;
		case 2:
			findAdminUI(pHead);
			break;
		case 3:
			updateAdminUI(pHead);
		case 4:
			system("cls");
			printf("=======================���ȫ�����Ա��Ϣ==========================\n");
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
	printf("========================��Ӳ�Ʒ===========================\n");
	printf("����������Ӳ�Ʒ����Ϣ:\n");
	food a;
	printf("ID��"); scanf("%s", a.id);
	printf("������"); scanf("%s", a.name);
	char foodtype[20];
	printf("���ࣺ"); scanf("%s", foodtype);
	a.foodtype = switchstoenum(foodtype);
	printf("�۸�"); scanf("%lf", &a.price);
	printf("������"); scanf("%d", &a.orderCount);
	pHead = addfood(pHead, a);
	writefoodIntoFile(pHead);
	printf("��ӳɹ�\n\n");
	system("pause");
	showAdminfoodUI(pHead);
}

foodnode* findfoodUI(foodnode* pHead)
{
	system("cls");
	printf("=======================���Ҳ�Ʒ��Ϣ==========================\n");
	foodnode* an;
	char ID[10];
	printf("����������Ҳ�Ʒ��ID��"); scanf("%s", ID);
	an = findfoodByid(pHead, ID);
	if (an == NULL)
	{
		printf("����ʧ��\n\n");
		system("pause");
		showAdminfoodUI(pHead);
	}
	else
	{
		char foodtype[20];
		printf("���ҳɹ�\n\n");
		printf("�ò�Ʒ����ϢΪ��\n");
		printf("ID��%s\n", an->data.id);
		printf("������%s\n", an->data.name);
		strcpy(foodtype, switchenumtos(an->data.foodtype));
		printf("���ͣ�%s\n", foodtype);
		printf("�۸�%.2lf\n", an->data.price);
		printf("������%d\n", an->data.orderCount);
	}
	system("pause");
	showAdminfoodUI(pHead);
	return an;
}

void updatefoodUI(foodnode* pHead)
{
	system("cls");
	printf("======================���²�Ʒ��Ϣ=========================\n");
	foodnode* an;
	char ID[10];
	printf("����������Ҳ�Ʒ��ID��"); scanf("%s", ID);
	an = findfoodByid(pHead, ID);
	if (an == NULL)
	{
		printf("����ʧ��\n\n");
		system("pause");
		showAdminfoodUI(pHead);
	}
	else
	{
		char foodtype[20];
		printf("���ҳɹ�\n\n");
		printf("�ò�Ʒ����ϢΪ��\n");
		printf("ID��%s\n", an->data.id);
		printf("������%s\n", an->data.name);
		strcpy(foodtype, switchenumtos(an->data.foodtype));
		printf("���ͣ�%s\n", foodtype);
		printf("�۸�%.2lf\n", an->data.price);
		printf("������%d\n", an->data.orderCount);
		printf("\n�����Ը��¸ò�Ʒ�ģ�\n");
		printf("(1) id\n");
		printf("(2) ����\n");
		printf("(3) ����\n");
		printf("(4) �۸�\n");
		printf("(5) ɾ���ò�Ʒ\n");
		printf("(6) ȡ������\n");
		int index;
		scanf("%d", &index);
		switch (index)
		{
		case 1:
			printf("����id�޸�Ϊ��"); scanf("%s", an->data.id);
			pHead = updatefoodByid(pHead, an->data.id, an->data);
			writefoodIntoFile(pHead);
			break;
		case 2:
			printf("���������޸�Ϊ��"); scanf("%s", an->data.name);
			pHead = updatefoodByid(pHead, an->data.id, an->data);
			writefoodIntoFile(pHead);
			break;
		case 3:
			printf("���������޸�Ϊ��"); scanf("%s", foodtype);
			strcpy(foodtype, switchenumtos(an->data.foodtype));
			pHead = updatefoodByid(pHead, an->data.id, an->data);
			writefoodIntoFile(pHead);
			break;
		case 4:
			printf("����۸�Ϊ��"); scanf("%lf", &an->data.price);
			pHead = updatefoodByid(pHead, an->data.id, an->data);
			writefoodIntoFile(pHead);
			break;
		case 5:
			pHead = deletefoodByID(pHead, an->data.id);
			printf("ɾ���ɹ�!\n");
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
	printf("========================�˵���Ϣ��������===========================\n");
	printf("\n��ѡ�����²�����\n");
	printf("(1) ��Ӳ�Ʒ\n");
	printf("(2) ���Ҳ�Ʒ\n");
	printf("(3) ���²�Ʒ��Ϣ\n");
	printf("(4) ����˵�\n");
	printf("(5) ����������\n");
	while (true)
	{
		printf("�����������ţ� ��  ��");
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
			printf("========================����˵���Ϣ===========================\n");
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
		printf("========================ͳ�Ʒ�������===========================\n");
		printf("\n��ѡ�����²�����\n");
		printf("(1) �鿴��Ʒ����ǰʮ\n");
		printf("(2) ���ҽ��շ���Ա������ǰ��\n");
		printf("(3) �鿴����ʹ���������\n");
		printf("(4) ����������\n");
		printf("�����������ţ� ��  ��");
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

			printf("%-10s\t%-10s\t%-5s\t%-5s\t%-7s\n", "ʳƷid", "ʳƷ����", "ʳƷ����", "�������", "�۸�");
			while (!(p == NULL))//��������
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
			printf("\n%-10s \t%-10s \t%-10s", "����", "����", "���շ�������");
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
	printf("*********************ϵͳ����Ա������**********************\n\n\n");
	printf("             ---------------------------------             \n\n");
	printf("            |        (1) �û�����             |            \n");
	printf("            |        (2) �˵�����             |            \n");
	printf("            |        (3) ͳ�Ʒ���             |            \n");
	printf("            |        (4) ��λ����             |            \n");
	printf("            |        (5) �������             |            \n");
	printf("            |        (6) �˳�                 |            \n");
	printf("             ---------------------------------             \n\n\n");
	printf("***********************************************************\n\n");
	while (true)
	{
		printf("��ѡ�������� ��  ��");
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
		printf("**********************����Ա��¼����********************\n��ID����-1���ؽ�ɫѡ����棩\n\n               ����������ID   >>>___________");
		int x = wherex(), y = wherey();
		gotoxy(x - 10, y);
		char ID[ADMINPAS_LENGTH_MAX];
		scanf("%s", ID);
		if (strcmp(ID, "-1") == 0)
		{
			break;  // ���ؽ�ɫѡ�����
		}
		printf("\n               �������������� >>>___________");
		x = wherex(), y = wherey();
		gotoxy(x - 10, y);
		char password[ADMINPAS_LENGTH_MAX];
		scanf("%s", password);
		Adminnode* currentAdmin = findAdminByID(pHead, ID);
		if (currentAdmin != NULL && strcmp(currentAdmin->data.password, password) == 0)
		{
			printf("\n\n\n��¼�ɹ�!\n\n");
			system("pause");
			system("cls");
			ShowAdminMainUI(pHead);
		}
		else
		{
			printf("\n\n\nError>>>�˻��������ڻ���������������������룡\n\n");
			system("pause");
			continue;
		}
	}
	
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
		t->seatList = initSeatList(captainOfSeat ,numOfSeat);
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
	while (p != NULL && p->next!=NULL)
	{
		printf("\n\t%-10d \t%-10d \t%-10d", p->captainOfSeat, p->numOfSeat, p->useTimes);
		p = p->next;
	}
	printf("\n");
	system("pause");
	return;
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