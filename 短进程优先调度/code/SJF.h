#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef SJF_H_INCLUDED
#define SJF_H_INCLUDED 

typedef struct LNode {

	char name[10]; //��������

	int status; //����״̬, 0->δ���1->������2->����ִ�У�3->���

	int arriveTime; //����ʱ��

	int serverTime; //����ʱ��

	int remainTime; // ʣ��ִ��ʱ��

	int startTime; //��ʼʱ��

	int finishTime; //���ʱ��

	int turnoverTime; //��תʱ��(���ʱ��-����ʱ��)

	float weightTime; //��Ȩ��תʱ��(��תʱ��/����ʱ��)
	
	struct LNode* next; //��һ�����̵�ַ

} LNode, *LinkedList;


#endif
