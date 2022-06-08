#pragma once
/*
 * @Author: 彭京
 * @ID: 202000810081
 * @Date: 2022-05-31
 * @LastEditors: LAPTOP-44TSMLLA
 * @Description:该源代码文件记录了系统管理员的五个功能需求中所要用到的所有链表和文件操作函数声明，大部分UI界面设计函数声明，主创作者为彭京。
 */
#ifndef __CORE_ADMINISTRATER_H_
#define __CORE_ADMINISTRATER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "Core_Type.h"



 //存放系统管理员信息的文本文档
#define ADMIN_FILE_PATH "admin.txt"

//存放食品信息的文本文档
#define FOOD_FILE_PATH "menu.txt"

// 存放餐厅餐桌信息
#define TABLE_FILE_PATH "table.txt"



//初始化服务员链表
waitor* WaitorListHead;
Adminnode* adminListHead;
waitor* currentWaitor;
foodnode* foodsListHead;
ordernode* OrderListHead; //系统当前未结账订单头结点
Order CurrentOrder;
tablenode* tablesListHead;




//初始化一个无头结点的系统管理员链表
Adminnode* InitAdminTable();
//添加一个系统管理员数据到一个有序链表 根据系统管理员年龄递增排序
Adminnode* addAdminByOrder(Adminnode* pHead, struct Admin data);
//按年龄顺序打印系统管理员信息链表（浏览系统管理员信息）
void printAdminTable(Adminnode* pHead);
//查找链表中是否有对应ID的管理员
Adminnode* findAdminByID(Adminnode* pHead, char* ID);
//根据ID更新系统管理员信息
Adminnode* updateAdminByID(Adminnode* pHead, char* ID, struct Admin data);

//从文件中读取管理员信息(相当于创建单链表操作)
Adminnode* readAdminFromFile();
//将链表中管理员信息写入文件
bool writeAdminIntoFile(Adminnode* pHead);

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

//根据服务员的服务量得到一个降序排序的有序链表
waitor* orderWaitorbycount();   
//-->应该是这个函数出了点问题，但我现在找不出来
// 已修复√

//部分系统管理员UI界面
//系统管理员登录
void ShowAdminLoginUI(Adminnode* pHead);
//系统管理员主界面
void ShowAdminMainUI(Adminnode* pHead);
void ShowUserManageUI(Adminnode* pHead);
//用户管理
void showAdminManageUI(Adminnode* pHead);
void showWaitorManageUI(Adminnode* pHead);
//管理员信息管理
void addAdminUI(Adminnode* pHead);
void findAdminUI(Adminnode* pHead);
void updateAdminUI(Adminnode* pHead);
//服务员信息管理
void AddWaitorToList(char* name, char* passwd, int sumofserve);
void DeleteWaitorOfList(char* name);
void UpdateWaitorsInfo();
//将服务员文件中的信息读入链表
void LoadWaitors();
waitor* getWaitorByName(char* name);
//更改服务员信息UI
void UpdateWaitorsNode();
void PrintfWaitorsInfo();

//菜单管理
void showAdminfoodUI(foodnode* fHead);
void addfoodUI(foodnode* pHead);
foodnode* findfoodUI(foodnode* pHead);
void updatefoodUI(foodnode* pHead);


//统计分析
void showcensusUI(foodnode* pHead);   //这里的第二个功能出现了点问题
// 已修复

// 餐桌管理
void showAdminTableUI(tablenode* tHead);
//从文件中读取餐桌信息(相当于创建单链表操作)
tablenode* readtableFromFile();
//将链表中餐桌信息写入文件
bool writetableIntoFile(tablenode* pHead);

// 初始化餐桌链表
tablenode* initTableList();
// 初始化座位数组
seat* initSeatList(int captain, int length);
// 添加餐桌结点
bool addTableNode(tablenode* addNode);
// 删除餐桌结点
bool deleteTableNode(int captain);

// 展示餐桌示意图
void ShowTableUI();
// 添加指定数量新类型餐桌
bool addNewTableUI();
// 删除某类型的餐桌
bool removeTableTypeUI();
// 添加指定数量某类型的餐桌
bool increaseTableNumUI();
// 减少指定数量某类型的餐桌
bool decreaseTableNumUI();
// 增加某类型餐桌的使用次数
bool addTableUseTimes(int captain);
// 统计餐桌使用频率并排序
tablenode* orderTableByUseTimes();
// 显示餐桌使用次数排序表
void ShowTableUseTimesUI(tablenode* orderList);
// 重置座位属性
bool resetSeat(int captain, int order);
// 调整某类型餐桌的数量
seat* resizeSeatList(seat* seatList, int changeNum);
// 判断某类型第order个座位是否为空
int isSelected(int captain, int order);
// 标记座位已选择
void setSelected(int captain, int order);

// 订单浏览
void showOrderBrowseUI();
// 按日期展示订单
void showOrderByDate();
// 按日期查询订单
void searchOrderByDate(int year, int month, int day);
#endif