#pragma once
#include "Core_System.h"
#include "Core_Type.h"


// ͨ���˿������Ҷ���
ordernode* getOrderbyName(char* name);
// ɾ������
void deleteOrder(char* name);
// ����
void CheckOut();
// ���¶����Ĺ˿���
void UpdateNameofOrder(ordernode* theorder);
// ������Ӳ�Ʒ
void AddFoodtoOrder(ordernode* theorder);
// ����ɾ����Ʒ
void DelFoodofOrder(ordernode* theorder);
// �޸Ķ�������
void ChangeOrder();
// �����鿴ҳ��
void ShowOrderUI();
// �������˽���
void ShowCheckOutUI();
// �鿴δ���˶���
void ShowUnCheckedOrderUI();
// ��ͽ���
void ShowTakeOrderUI();
// ɾ������
void DeleteOrderUI();
// ��δ��ɶ���д���ļ�
void ReWriteUnDoneOrders();
// ����δ��ɶ�����Ϣ
void LoadUnDoneOrders();
// ��Ӷ������
void AddOrdertoOrderList(Order* order);
// ���Ҷ���
void SearchOrder();
// �������
void showOrderBrowseUI();
// ������չʾ����
void showOrderByDate();
// �����ڲ�ѯ����
void searchOrderByDate(int year, int month, int day);