#include "Replace.h"

int task[320]; // ���ָ�������
int taskIndex; // ��ǰִ��ָ�� task[taskIndex]
int nowTime; // ��¼ʱ��
int pageNum; // ��ǰ�ڴ�ҳ��
int interrupt; // ȱҳ�жϴ���


//�������320�������
void randomNum() {
	int flag = 0;
	srand((unsigned)time(NULL));   //ϵͳʱ��Ϊ��������� 
	int m = rand() % 320;
	for (int i = 0; i < 320; i++)
	{
		task[i] = m;
		if (flag % 2 == 0) m = ++m % 320;
		if (flag == 1) m = rand() % (m - 1);
		if (flag == 3) m = m + 1 + (rand() % (320 - (m + 1)));
		flag = ++flag % 4;
	}
}

// ��ʼ���ڴ�����
void init(LinkedList &head) {
	taskIndex = 0; 
	nowTime = 1; 
	pageNum = 0; 
	interrupt = 0;
	head = (LinkedList)malloc(sizeof(LNode));
	head->next = NULL;
}

// �����ڴ�����
void distory(LinkedList &head) {
	LinkedList p = head;
	while (p != NULL) {
		head = head->next;
		free(p);
		p = head;
	}
	head = NULL;
}

// ��ӡ�ڴ�����
void print(LinkedList head, int type) {
	LinkedList p;
	printf("\n ���ڴ�״������");
	printf("\n  ��������������������");
	if (type == 0) {
		// �Ƚ��ȳ���FIFO��
		printf ("\n  ҳ�� ����ʱ�� ");
		for(p = head->next; p != NULL; p = p->next) {
			printf("\n %4d %6d", p->page, p->inTime);
		}
	} else if (type == 1) {
		// ������δʹ�ã�LRU��
		printf ("\n  ҳ�� ����ʱ�� δʹ�ô���");
		for(p = head->next; p != NULL; p = p->next) {
			printf("\n %4d %6d %8d", p->page, p->inTime, p->unUsedTime);
		}
	} else if (type == 2) {
		// ����û���OPT��
		int i = 1;
		printf ("\n  ���� ҳ��");
		for(p = head->next; p != NULL; p = p->next) {
			printf("\n %4d %4d", i, p->page);
			i++;
		}
	}
	printf("\n  ��������������������\n ");
}


// ���Ƚ��ȳ���FIFO����ȱҳ�ж�ʱ����ָ��ҳ�����ڴ�
void FIFO(LinkedList head, LinkedList temp) {
	LinkedList p, pro;
	int minInTime = head->next->inTime; // �������ʱ��

	for(p = pro = head; p->next != NULL; p = p->next) {
		if (p->next->inTime < minInTime) {
			minInTime = p->next->inTime;
			pro = p;
		}
	}
	// pro Ϊ��������ҳ����һ���ڵ�
	printf("\n ��ҳ���û������û��� %d ҳΪ�� %d ҳ", pro->next->page, temp->page);
	temp->next = pro->next->next;
	free(pro->next);
	pro->next = temp;
}

// ��������δʹ�ã�LRU����ȱҳ�ж�ʱ����ָ��ҳ�����ڴ�
void LRU(LinkedList head, LinkedList temp) {
	LinkedList p, pro;
	int minInTime = head->next->inTime; // �������ʱ��
	int maxUnUsedTime = head->next->unUsedTime; // ���δʹ�ô���

	for(p = pro = head; p->next != NULL; p = p->next) {
		if (p->next->unUsedTime > maxUnUsedTime) {
			maxUnUsedTime = p->next->unUsedTime;
			minInTime = p->next->inTime;
			pro = p;
		} else if (p->next->unUsedTime == maxUnUsedTime) {
			if (p->next->inTime < minInTime) {
				minInTime = p->next->inTime;
				pro = p;
			}
		}
	}
	// pro Ϊ������δʹ�õ�ҳ����һ���ڵ�
	printf("\n ��ҳ���û������û��� %d ҳΪ�� %d ҳ", pro->next->page, temp->page);
	temp->next = pro->next->next;
	free(pro->next);
	pro->next = temp;
	
}

// ������û���OPT����ȱҳ�ж�ʱ����ָ��ҳ�����ڴ�
void OPT(LinkedList head, LinkedList temp) {
	LinkedList p, pro;
	int minUseTime = 320; // Ԥ������ʹ�ô���
	for(p = head->next; p != NULL; p = p->next) {
		p->useTime = 0;
	}
	for (int i = taskIndex + 1; i < 320; i++) {
		for(p = head->next; p != NULL; p = p->next) {
			if (p->page == task[i]/10) {
				p->useTime ++;
			}
		}
	}
	for(p = head; p->next != NULL; p = p->next) {
		printf("\n   �� %d ҳԤ�ƽ������� %d ����", p->next->page, p->next->useTime);
		if (p->next->useTime < minUseTime ) {
			minUseTime = p->next->useTime;
			pro = p;
		}
	}
	printf("\n ��ҳ���û������û��� %d ҳΪ�� %d ҳ", pro->next->page, temp->page);
	temp->next = pro->next->next;
	free(pro->next);
	pro->next = temp;
}

// ��ȡָ������ҳ���ڴ�ָ��
LinkedList getLnodeP(LinkedList head, int page) {
	LinkedList p;
	for(p = head->next; p != NULL; p = p->next) {
		if (p->page == page) {
			break;
		}
	}
	return p;
}

// ִ��һ��ָ��
void runTask(LinkedList head, int task, int type) {
	LinkedList p = getLnodeP(head, task/10);
	// ȱҳ�ж�
	if(p == NULL) {
		printf("��ȱҳ�жϡ�");
		// ��ʼ����ҳ
		p = (LinkedList)malloc(sizeof(LNode));
		p->page = task/10;
		p->inTime = nowTime;
		p->unUsedTime = 0;
		p->next = NULL;
		p->useTime = 0;
		// ������ҳ
		if(pageNum < 16) {
			printf("\n ��������ҳ�������õ� %d ҳ", p->page);
			p->next = head->next;
			head->next = p;
			pageNum ++;
		} else {
			if (type == 0) {
				FIFO(head, p);
			} else if (type == 1) {
				LRU(head, p);
			} else  {
				OPT(head, p);
			}
		}
		print(head, type);
		interrupt++;
	} else {
		printf("����ִ��\n");
	}
	p->unUsedTime = 0;
	// ��¼����ҳδʹ�ô���
	for(p = head->next; p != NULL; p = p->next) {
		if (p->page != task/10) {
			p->unUsedTime ++;
		}
	}
	nowTime++;
}

void test(LinkedList &head, int type) {
	if (type == 0) {
		printf("\n���Ƚ��ȳ���FIFO���㷨��\n");
	} else if (type == 1) {
		printf("\n��������δʹ�ã�LRU����\n");
	} else if (type == 2) {
		printf("\n������û���OPT��\n");
	}
	init(head);
	randomNum();
	for( ; taskIndex < 320; taskIndex++) {
		printf("\n��ִ�С���%dҳ��ָ�� %d��", task[taskIndex]/10, task[taskIndex]);
		runTask(head, task[taskIndex], type);
	}
	printf("\n\n��ִ����ϡ� ȫ��ָ��ִ�����\n");
	distory(head);
	if (type == 0) {
		printf("\n���Ƚ��ȳ���FIFO������\n");
	} else if (type == 1) {
		printf("\n��������δʹ�ã�LRU������\n");
	} else if (type == 2) {
		printf("\n������û���OPT������\n ");
	}
	printf("   ȱҳ�жϴ�����%d, \n    ȱҳ�жϸ��� %2.2f%% \n\n", interrupt, interrupt*100.0/320);
}