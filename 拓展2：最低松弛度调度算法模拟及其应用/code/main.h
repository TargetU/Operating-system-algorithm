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

	int finishTime; // ��ֹʱ��

	int remainTime; // ʣ��ִ��ʱ��
	
	int relaxation; // �ɳڶ�

	int status; // ״̬��0->δ���1->������2->ִ���У�3->������ɣ�4->��ʱ���
	
	struct Task* next; // ��һ����ҵ��ַ

} Task, *TaskList;



#endif
