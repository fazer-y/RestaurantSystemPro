#pragma once

// 存放餐厅餐桌信息
#define TABLE_FILE_PATH "table.txt"

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
    struct tablenode* next;
}tablenode;


//存放食品信息的文本文档
#define FOOD_FILE_PATH "menu.txt"

//食物名称 最大长度
#define FOODNAME_LENGTH_MAX 30

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

//存放已完成订单信息的文本文档
#define DO_FILE_PATH "DoneOrders.txt"

//存放未完成订单信息的文本文档
#define UNDO_FILE_PATH "UnDoneOrders.txt"

#define CustomerName_MaxLength 50
#define SumFoodsOfOrder_Max 50

typedef struct DateOfOrder
{
    int year;
    int month;
    int day;
} DateOfOrder;


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

//服务员姓名 最大长度
#define WaitorName_MaxLength 30
//服务员密码 最大长度
#define WaitorPasswd_MaxLength 10

typedef struct waitor
{
    char name[WaitorName_MaxLength];
    char passwd[WaitorPasswd_MaxLength];
    int sumofserve;
    struct waitor* next;
} waitor;

//存放系统管理员信息的文本文档
#define ADMIN_FILE_PATH "admin.txt"


//系统管理员账号 最大长度
#define ADMINID_LENGTH_MAX 15
//系统管理员密码 最大长度
#define ADMINPAS_LENGTH_MAX 20
//系统管理员姓名 最大长度
#define ADMINNAME_LENGTH_MAX 10


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