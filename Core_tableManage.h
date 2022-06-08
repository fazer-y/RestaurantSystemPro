#pragma once
#include "Core_System.h"
#include "Core_Type.h"


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
// 展示餐厅实时餐桌图
void ShowSeatMap();
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

// 管理员餐桌管理界面
void showAdminTableUI(tablenode* tHead);