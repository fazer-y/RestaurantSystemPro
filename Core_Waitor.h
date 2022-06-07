#pragma once
#ifndef __CORE_WAITOR_H_
#define __CORE_WAITOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "Core_Administrater.h"
#include "Core_Type.h"
#include "Core_System.h"


void ShowOrderUI();
void ShowWaitorMainUI();
void DeletetheOrder();
void ShowWaitorMainUI();
void ShowWaitorLoginUI();
void ShowCheckOutUI();
void ShowUnCheckedOrderUI();
void ShowTakeOrderUI();
void ExitWaitorMainUI();

void InitWaitorList(waitor* head);
void InitOrderList(ordernode* head);
void UpdateWaitorsNode();
void Revereshow(foodnode* p);
void ShowMenu();
void LoadMyMenu();
void ReWriteUnDoneOrders();
void color(const unsigned short textColor);
void SetColor();
void AddOrdertoOrderList(Order* order);
void SearchOrder();
void LoadSeatsMap(int rows, int cols);
void ShowSeatMap();
int CheckPasswd(char* name, char* passwd);
void AddWaitorToList(char* name, char* passwd, int sumofserve);
void UpdateWaitorsInfo();
void UpdateWaitorsNode();
double getPriceoffood(char* id);
char* getNameofFood(char* id);
ordernode* getOrderbyName(char* name);
void deleteOrder(char* name);
void CheckOut();
void DeletetheOrder();
void UpdateNameofOrder(ordernode* theorder);
void AddFoodtoOrder(ordernode* theorder);
void DelFoodofOrder(ordernode* theorder);
void ChangeOrder();
void LoadUnDoneOrders();
void Revereshow(foodnode* p);
void PrintfWaitorsInfo();
void DeleteWaitorOfList(char* name);
void UpdateCountofFood(char* id);
#endif