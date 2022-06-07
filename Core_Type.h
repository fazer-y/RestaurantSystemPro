#pragma once
#ifndef __CORE_TYPE_H_
#define __CORE_TYPE_H_

//系统管理员账号 最大长度
#define ADMINID_LENGTH_MAX 15
//系统管理员密码 最大长度
#define ADMINPAS_LENGTH_MAX 20
//系统管理员姓名 最大长度
#define ADMINNAME_LENGTH_MAX 10

//服务员姓名 最大长度
#define WaitorName_MaxLength 30
//服务员密码 最大长度
#define WaitorPasswd_MaxLength 10

//食物名称 最大长度
#define FOODNAME_LENGTH_MAX 30

#define WaitorName_MaxLength 50
#define WaitorPasswd_MaxLength 10
#define CustomerName_MaxLength 50
#define SumFoodsOfOrder_Max 50
#define ForeColorIndex 7
#define BackColorIndex 0

//系统管理员
typedef struct Admin
{
    char ID[ADMINPAS_LENGTH_MAX];
    char password[ADMINPAS_LENGTH_MAX];
    char name[ADMINNAME_LENGTH_MAX];
    char sex[10];
    int age;
} Admin;

//链表节点(系统管理员)
typedef struct Adminnode
{
    struct Admin data;
    struct Adminnode* next;
    int number; //总数量
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
    int numbers; //用餐人数
    char foods[50][50];
    int sumoffood;
    double MoneyPaid;
    int isCheckedout; //是否结账
    DateOfOrder date;
    seat seat;
} Order;

typedef struct OrderNode
{
    Order order;
    struct OrderNode* next;
} ordernode;

//食物类型
enum foodType
{
    specaility, //招牌菜
    staple,     //主食
    hot,        //热菜
    cold,       //凉菜
    soup,       //汤
    beverage,   //饮料
};

//菜品
typedef struct food
{
    char id[10];                    //食物ID(唯一性)
    char name[FOODNAME_LENGTH_MAX]; //食物名称
    enum foodType foodtype;
    double price;   //食物价格
    int orderCount; //这个菜从添加到系统里以来一共被点的次数
} food;

//链表节点(食物)
typedef struct foodnode
{
    struct food data;
    struct foodnode* next;
    int number; //总数量
} foodnode;

#endif