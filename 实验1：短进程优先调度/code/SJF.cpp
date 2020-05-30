#include"SJF.h"




int nowTime = 0; // ��ǰʱ��
int pro_num = 0; // ִ�н��̸���



//  ��������
int inputInt(int min) {
	int a, result;
	fflush(stdin);
	a = scanf("%d",&result);
	if(a == 0)
	{
		printf("\n���������֡������������������: ");
        result = inputInt(min);
	} else if (result < min) {
		printf("\n���������֡����������%d������: ", min);
        result = inputInt(min);
	}
	return result;
}

// ��ӡȫ������״̬
void printAll(LinkedList link) {
	LinkedList p;
	printf("\n �ڡ� %d ����\n", nowTime);
	printf("\n  �������� ����ʱ�� ����ʱ�� ʣ��ʱ�� ��ʼʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ�� ����״̬");
	for(p = link->next; p != NULL; p = p->next) {
		printf("\n %5s  ", p->name);
		printf("  %5d  ", p->arriveTime);
		printf("  %5d  ", p->serverTime);
		printf("  %5d  ", p->remainTime);
		if (p->startTime == -1) {
			printf("   %5s ", "��");
		} else {
			printf("   %5d ", p->startTime);
		}
		if (p->finishTime == -1) {
			printf("   %5s ", "��");
		} else {
			printf("   %5d ", p->finishTime);
		}
		if (p->turnoverTime == -1) {
			printf("   %5s ", "��");
		} else {
			printf("   %5d ", p->turnoverTime);
		}
		if (p->weightTime == -1.0) {
			printf("   %7s   ", "��");
		} else {
			printf("   %7.3f   ", p->weightTime);
		}
		if (p->status == 0) {
			printf("    δ����  ");
		} else if (p->status == 1) {
			printf("    ������  ");
		} else if (p->status == 2) {
			printf("    ִ����  ");
		} else if (p->status == 3) {
			printf("    �����  ");
		}
	}
	printf("\n");
}

// �½��̵� [����ʱ��+����ʱ��] �����뵽��������
void insertLNode(LinkedList link, char name[10], int arriveTime, int serverTime) {
	LinkedList temp;
	LinkedList p = (LinkedList)malloc(sizeof(LNode));
	
	strcpy(p->name, name);
	p->arriveTime = arriveTime;
	p->remainTime = p->serverTime = serverTime;
	
	p->startTime = -1;
	p->finishTime = -1;
	p->turnoverTime = -1;
	p->weightTime = -1;
	p->status = 0;
	// p->next = NULL;

	p->next = link->next;
	link->next = p;

	return;

	for(temp = link; temp->next != NULL; temp = temp->next) {
		if (temp->next == NULL) {
			// ��������Ϊ�գ�ֱ�Ӳ����һ���ڵ�
			temp->next = p;
			break;
		} else {
			int pre_arriveTime = temp->next->arriveTime;
			int pre_serverTime = temp->next->serverTime;
			if (p->arriveTime < pre_arriveTime 
				|| (p->arriveTime == pre_arriveTime && p->serverTime < pre_serverTime)) {
				// �Ƚ� ����ʱ��+����ʱ�䣬ѡ�����λ��
				p->next = temp->next;
				temp->next = p;

			}
			break;
		}
	}
	if(temp->next == NULL) {
		// ���뵽��β
		temp->next = p;
	}
}


// ���һ������
void addPro(LinkedList link) {
	
	int arriveTime, serverTime;
	char name[10];

	printf("  ����ӡ�����[������](char *)��");
	fflush(stdin);
	gets(name);

	printf("  ����ӡ�����[�ﵽʱ��](int)��");
	arriveTime = inputInt(0) ;

	printf("  ����ӡ�����[����ʱ��](int)��");
	serverTime = inputInt(1);
	
	insertLNode(link, name, arriveTime, serverTime);
}

// ��������
void createPro(LinkedList &link) {
	// ��ʼ��
	link = (LinkedList)malloc(sizeof(LNode));
	link->next = NULL;
	// ���� pro_num ������
	printf("\n ������������ ���������봴���Ľ�������");
	pro_num = inputInt(1);
	for(int i = 0; i < pro_num; i++) {
		printf("\n ���������̡� ���ڴ����� %d ������\n", i);
		addPro(link);
	}
}

// ��ȡ��ǰʱ��ƬӦ��ִ�еĽ���
LinkedList getPro(LinkedList waitArr[], int num) {
	if(num == 0) {
		// û�о�������
		return NULL;
	}
	LinkedList result = waitArr[0];
	for(int i = 1; i < num; i++) {
		if(waitArr[i]->remainTime > result->remainTime) {
			continue;
		} else if(waitArr[i]->remainTime < result->remainTime) {
			result = waitArr[i];
		} else if(waitArr[i]->arriveTime < result->arriveTime) {
			result = waitArr[i];
		}
	}
	return result;
}

// ִ��һ��ʱ��Ƭ
LinkedList runOneTime(LinkedList link) {
	int num = 0;
	LinkedList p, p2;
	LinkedList *waitArr = (LinkedList*)malloc(sizeof(LinkedList)*pro_num);
	// ��ȡ���������б�
	for(p = link->next; p != NULL; p = p->next) {
		if(p->status == 1) { 
			waitArr[num] = p;
			num++;
		}
	}
	// ʱ��Ƭִ��p2ָ��Ľ���
	p2 = getPro(waitArr, num);
	if(p2 != NULL) {
		if(p2->remainTime == p2->serverTime) {
			p2->startTime = nowTime;
		}
		p2->remainTime--;
		p2->status = 2; // p2��������ִ��
		
	} 
	
	return p2;
}
// ���ݽ��̵ĵ���ʱ��͵�ǰʱ�䣬�ж��Ƿ������µĽ���
void pushPro(LinkedList link) {
	LinkedList p;
	// �ж��Ƿ����µĽ�����Ҫ����
	for(p = link->next; p != NULL; p = p->next) {
		if(p->arriveTime == nowTime) {
			p->status = 1; // δ����-->����
			// break;
		}
	}
}

// �ж��Ƿ�ȫ�����̶�ִ������
int ifAllFinish(LinkedList link) {
	int result = 1;
	LinkedList p;
	for(p = link->next; p != NULL; p = p->next) {
		if(p->status != 3) {
			result = 0;
			break;
		}
	}
	return result; // 0--> δȫ����ɣ�1--> ��ȫ�����
}
// ִ����ɺ�, ������תʱ��
void finished(LinkedList link) {
	LinkedList p;
	for(p = link->next; p != NULL; p = p->next) {
		p->turnoverTime = p->finishTime - p->arriveTime;
		p->weightTime = (float)p->turnoverTime / (float)p->serverTime;
	}
}

// ִ�н���
void run(LinkedList link) {
	LinkedList p2;
	while(ifAllFinish(link) == 0) {
		pushPro(link); // �����½���
	
		p2 = runOneTime(link); // ִ��һ��ʱ��Ƭ�������ص�ǰִ�еĽ���
		
		printAll(link); // ��ӡ��nowTime���ڵĸ�������״̬ 
		nowTime ++;
		if(p2 != NULL) { // ��ִ����Ľ��̻ع鵽 ����/���
			if(p2->remainTime == 0) {
				p2->status = 3;
				p2->finishTime = nowTime;
			} else {
				p2->status = 1;
			}
		}
	}
	finished(link);
	printAll(link);
}
