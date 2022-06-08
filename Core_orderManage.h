#pragma once
#include "Core_System.h"
#include "Core_Type.h"


// 通过顾客名查找订单
ordernode* getOrderbyName(char* name);
// 删除订单
void deleteOrder(char* name);
// 结账
void CheckOut();
// 更新订单的顾客名
void UpdateNameofOrder(ordernode* theorder);
// 订单添加菜品
void AddFoodtoOrder(ordernode* theorder);
// 订单删除菜品
void DelFoodofOrder(ordernode* theorder);
// 修改订单界面
void ChangeOrder();
// 订单查看页面
void ShowOrderUI();
// 订单结账界面
void ShowCheckOutUI();
// 查看未结账订单
void ShowUnCheckedOrderUI();
// 点餐界面
void ShowTakeOrderUI();
// 删除订单
void DeleteOrderUI();
// 将未完成订单写回文件
void ReWriteUnDoneOrders();
// 载入未完成订单信息
void LoadUnDoneOrders();
// 添加订单结点
void AddOrdertoOrderList(Order* order);
// 查找订单
void SearchOrder();
// 订单浏览
void showOrderBrowseUI();
// 按日期展示订单
void showOrderByDate();
// 按日期查询订单
void searchOrderByDate(int year, int month, int day);