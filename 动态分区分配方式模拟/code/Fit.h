#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef FIT_H_INCLUDED
#define FIT_H_INCLUDED

typedef struct LNode {
	 
	int id; // ������
	 
	int begin; // ��ʼ��ַ
	
	int end; // ĩβ��ַ 
	
	int status; // ״̬ 0������У�1������ռ�� 

	struct LNode* next;

}LNode, *LinkedList;

#endif
