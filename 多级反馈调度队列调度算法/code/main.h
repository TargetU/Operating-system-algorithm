#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef SJF_H_INCLUDED
#define SJF_H_INCLUDED 

// ��ҵ
typedef struct Task {
	
	char name[10]; // ��ҵ����

	int arriveTime; // ����ʱ��

	int serverTime; // ����ʱ��

	int remainTime; // ʣ��ִ��ʱ��

	int status; // �Ƿ���ӣ�0->δ��ӣ�1->�����
	
	struct Task* next; // ��һ����ҵ��ַ

} Task, *pTask;

// ��������
typedef struct Queue {

	int queue_ID; // ����id

	pTask t_head; // ������ҵ����

	int priority; // ���ȼ�������ԽС�ȼ�Խ��

	int serverTime; // ȫ��ʱ��Ƭ

	int remainTime; // ʣ��ʱ��Ƭ
	
	struct Queue* next; // ��һ����ҵ��ַ

} Queue, *pQueue;


#endif
