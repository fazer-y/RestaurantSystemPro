#pragma once
#include "Core_System.h"
#include "Core_Type.h"


//将枚举类型的菜品信息转化为字符串以便输出
char* switchenumtos(enum foodType type);
//将字符串类型转化为枚举类型以便食品录入
enum foodType switchstoenum(char* type);
//初始化一个无头结点的食物链表
foodnode* InitfoodTable();
//添加一个食品信息到一个链表（尾部）
foodnode* addfood(foodnode* pHead, food data);
//查找链表中对应ID的食物，返回指向该食物结点的指针
foodnode* findfoodByid(foodnode* pHead, char* ID);
//根据id更新食品的信息
foodnode* updatefoodByid(foodnode* pHead, char* ID, food data);
//根据食物的被点次数得到一个降序排序的有序链表
foodnode* orderfoodbycount(foodnode* pHead);
//根据id从菜单中删除食品
foodnode* deletefoodByID(foodnode* pHead, char* ID);
//显示菜单
void printfoodTable(foodnode* pHead);

//从文件中读取食物信息(相当于创建单链表操作)
foodnode* readfoodFromFile(foodnode* pHead);
//将链表中食物信息写入文件
bool writefoodIntoFile(foodnode* pHead);

// 显示菜单
void ShowMenu();
// 从文件载入菜单
void LoadMyMenu();
// 逆序输出菜品信息
void Revereshow(foodnode* p);
// 重新写回菜品信息至文件
void ReWriteBackFood();
// 通过ID获取菜品价格
double getPriceoffood(char* id);
// 通过ID获取菜品名称
char* getNameofFood(char* id);
// 更新菜品被点次数
void UpdateCountofFood(char* id);

//菜单管理
void showAdminfoodUI(foodnode* fHead);
void addfoodUI(foodnode* pHead);
foodnode* findfoodUI(foodnode* pHead);
void updatefoodUI(foodnode* pHead);