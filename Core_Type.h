#pragma once
#ifndef __CORE_TYPE_H_
#define __CORE_TYPE_H_

//ϵͳ����Ա�˺� ��󳤶�
#define ADMINID_LENGTH_MAX 15
//ϵͳ����Ա���� ��󳤶�
#define ADMINPAS_LENGTH_MAX 20
//ϵͳ����Ա���� ��󳤶�
#define ADMINNAME_LENGTH_MAX 10

//����Ա���� ��󳤶�
#define WaitorName_MaxLength 30
//����Ա���� ��󳤶�
#define WaitorPasswd_MaxLength 10

//ʳ������ ��󳤶�
#define FOODNAME_LENGTH_MAX 30

#define WaitorName_MaxLength 50
#define WaitorPasswd_MaxLength 10
#define CustomerName_MaxLength 50
#define SumFoodsOfOrder_Max 50
#define ForeColorIndex 7
#define BackColorIndex 0

//ϵͳ����Ա
typedef struct Admin
{
    char ID[ADMINPAS_LENGTH_MAX];
    char password[ADMINPAS_LENGTH_MAX];
    char name[ADMINNAME_LENGTH_MAX];
    char sex[10];
    int age;
} Admin;

//����ڵ�(ϵͳ����Ա)
typedef struct Adminnode
{
    struct Admin data;
    struct Adminnode* next;
    int number; //������
} Adminnode;

typedef struct waitor
{
    char name[WaitorName_MaxLength];
    char passwd[WaitorPasswd_MaxLength];
    int sumofserve;
    struct waitor* next;
} waitor;

typedef struct DateOfOrder
{
    int year;
    int month;
    int day;
} DateOfOrder;

typedef struct seat
{
    int captain;
    int order;
    int IsSelected;
} seat;

typedef struct tablenode
{
    seat* seatList;
    int captainOfSeat;
    int numOfSeat;
    int useTimes;
    tablenode* next;
}tablenode;

typedef struct Order
{
    char name[CustomerName_MaxLength];
    int DineInside;
    int numbers; //�ò�����
    char foods[50][50];
    int sumoffood;
    double MoneyPaid;
    int isCheckedout; //�Ƿ����
    DateOfOrder date;
    seat seat;
} Order;

typedef struct OrderNode
{
    Order order;
    struct OrderNode* next;
} ordernode;

//ʳ������
enum foodType
{
    specaility, //���Ʋ�
    staple,     //��ʳ
    hot,        //�Ȳ�
    cold,       //����
    soup,       //��
    beverage,   //����
};

//��Ʒ
typedef struct food
{
    char id[10];                    //ʳ��ID(Ψһ��)
    char name[FOODNAME_LENGTH_MAX]; //ʳ������
    enum foodType foodtype;
    double price;   //ʳ��۸�
    int orderCount; //����˴���ӵ�ϵͳ������һ������Ĵ���
} food;

//����ڵ�(ʳ��)
typedef struct foodnode
{
    struct food data;
    struct foodnode* next;
    int number; //������
} foodnode;

#endif