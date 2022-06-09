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
			ShowWelcomeUI();  // ���ؽ�ɫѡ�����
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