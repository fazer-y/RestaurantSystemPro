#pragma once
#include "Core_System.h"
#include "Core_Type.h"


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

//系统管理员登录
void ShowAdminLoginUI(Adminnode* pHead);
//系统管理员主界面
void ShowAdminMainUI(Adminnode* pHead);
void ShowUserManageUI(Adminnode* pHead);
//用户管理
void showAdminManageUI(Adminnode* pHead);
//管理员信息管理
void addAdminUI(Adminnode* pHead);
void findAdminUI(Adminnode* pHead);
void updateAdminUI(Adminnode* pHead);

//统计分析
void showcensusUI(foodnode* pHead);