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

void Revereshow(foodnode* p) {
	if (p) {
		Revereshow(p->next);
		char foodtype[20];
		//��ö�����͵Ĳ�Ʒ��Ϣת��Ϊ�ַ����Ա����
		switch (p->data.foodtype)
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
		printf("%-10s\t%-10s \t%-10s \t%-10d\t%-7.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
	}
}


void ShowMenu() {
	system("cls");
	printf("=============================�˵�=================================\n");
	printf("%-10s\t%-10s\t%-5s\t%-5s\t%-7s\n", "ʳƷid", "ʳƷ����", "ʳƷ����", "�������", "�۸�");
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
		perror("�ļ���ȡʧ��");
		return;
	}
	while (temp) {
		char typeoffood[FOODNAME_LENGTH_MAX];
		enum foodType type = temp->data.foodtype;
		switch (type) {
		case specaility:
			strcpy(typeoffood, "���Ʋ�");
			break;
		case staple:
			strcpy(typeoffood, "��ʳ");
			break;
		case  hot:
			strcpy(typeoffood, "�Ȳ�");
			break;
		case cold:
			strcpy(typeoffood, "����");
			break;
		case soup:
			strcpy(typeoffood, "��");
			break;
		case beverage:
			strcpy(typeoffood, "����");
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
		perror("�ļ���ȡʧ��");
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


		if (strcmp(foodtype, "���Ʋ�") == 0)
		{
			f->data.foodtype = specaility;
		}
		else if (strcmp(foodtype, "�Ȳ�") == 0)
		{
			f->data.foodtype = hot;
		}
		else if (strcmp(foodtype, "����") == 0)
		{
			f->data.foodtype = cold;
		}
		else if (strcmp(foodtype, "����") == 0)
		{
			f->data.foodtype = beverage;
		}
		else if (strcmp(foodtype, "��Ʒ") == 0)
		{
			f->data.foodtype = soup;
		}
		else {
			f->data.foodtype = staple;
		}
		//��������
		f->next = foodsListHead->next;
		foodsListHead->next = f;
	}
	//�ر��ļ�
	fclose(fp);
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