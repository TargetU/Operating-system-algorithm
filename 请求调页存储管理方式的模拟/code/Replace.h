#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#ifndef REPLACE_H_INCLUDED
#define REPLACE_H_INCLUDED 


//�ڴ��ṹ��
typedef struct LNode {

	int page; // ҳ��
	
	int inTime; // ����ʱ�䣨FIFO��

	int useTime; // Ԥ��ʹ�ô�����OPT��
	
	int unUsedTime; // δʹ�ô�����FIFO��LRU��

	LNode* next;

}LNode, *LinkedList;

#endif