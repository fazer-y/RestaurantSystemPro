#pragma once
#include "Core_System.h"
#include "Core_Type.h"


// 服务员主界面
void ShowWaitorMainUI();

// 服务员登录界面
void ShowWaitorLoginUI();

// 退出服务员主界面
void ExitWaitorMainUI();

// 更新服务员信息
void UpdateWaitorsNode();
// 验证服务员登录
int CheckPasswd(char* name, char* passwd);
// 添加服务员结点
void AddWaitorToList(char* name, char* passwd, int sumofserve);
// 更新服务员信息至文件
void UpdateWaitorsInfo();
// 更新服务员结点信息
void UpdateWaitorsNode();

//根据服务员的服务量得到一个降序排序的有序链表
waitor* orderWaitorbycount();

// 输出服务员信息
void PrintfWaitorsInfo();
// 删除服务员结点
void DeleteWaitorOfList(char* name);

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
void showWaitorManageUI(Adminnode* pHead);