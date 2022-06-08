#pragma once
#include "Core_System.h"
#include "Core_Type.h"


//���ļ��ж�ȡ������Ϣ(�൱�ڴ������������)
tablenode* readtableFromFile();
//�������в�����Ϣд���ļ�
bool writetableIntoFile(tablenode* pHead);

// ��ʼ����������
tablenode* initTableList();
// ��ʼ����λ����
seat* initSeatList(int captain, int length);
// ��Ӳ������
bool addTableNode(tablenode* addNode);
// ɾ���������
bool deleteTableNode(int captain);

// չʾ����ʾ��ͼ
void ShowTableUI();
// չʾ����ʵʱ����ͼ
void ShowSeatMap();
// ���ָ�����������Ͳ���
bool addNewTableUI();
// ɾ��ĳ���͵Ĳ���
bool removeTableTypeUI();
// ���ָ������ĳ���͵Ĳ���
bool increaseTableNumUI();
// ����ָ������ĳ���͵Ĳ���
bool decreaseTableNumUI();
// ����ĳ���Ͳ�����ʹ�ô���
bool addTableUseTimes(int captain);
// ͳ�Ʋ���ʹ��Ƶ�ʲ�����
tablenode* orderTableByUseTimes();
// ��ʾ����ʹ�ô��������
void ShowTableUseTimesUI(tablenode* orderList);
// ������λ����
bool resetSeat(int captain, int order);
// ����ĳ���Ͳ���������
seat* resizeSeatList(seat* seatList, int changeNum);
// �ж�ĳ���͵�order����λ�Ƿ�Ϊ��
int isSelected(int captain, int order);
// �����λ��ѡ��
void setSelected(int captain, int order);

// ����Ա�����������
void showAdminTableUI(tablenode* tHead);