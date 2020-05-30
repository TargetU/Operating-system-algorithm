#include"main.h"

int nowTime = 0; // ��ǰʱ��

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

// ��ʼ����ҵ
void initTask(pTask &thead) {
	thead = (pTask)malloc(sizeof(Task));
	thead->next = NULL;
}

// ������ҵ
void destroyTask(pTask head) {
	pTask help;
	while (head != NULL) {
		help = head;
		head = head->next;
		free(help);
	}
}
// ������ҵ
pTask newTask(char name[10], int arriveTime, int serverTime) {
	pTask p = (pTask)malloc(sizeof(Task));
	strcpy(p->name, name);
	p->arriveTime = arriveTime;
	p->serverTime = serverTime;
	p->remainTime = serverTime;
	p->status = 0;
	p->next = NULL;
	return p;
}
// ���뵽��ҵ����
void addTask(pTask head, pTask p) {
	
	while(head->next != NULL) {
		head = head->next;
	}
	head->next = p;
}

// ��ӡһ�������е���ҵ
void printTasks(pTask head) {
	pTask p = head->next;
	if (p == NULL) {
		printf("\n ���ա���ӡ��ҵΪ��");
	}
	printf("\n ��ҵ�� ����ʱ�� ����ʱ�� ʣ��ִ��ʱ�� ��ҵ״̬");
	while(p != NULL) {
		printf("\n %3s   %4d    %4d     %6d       ", p->name, p->arriveTime, p->serverTime, p->remainTime);
		if(p->status == 0) {
			printf(" %4s", "δ����");
		} else if (p->status == 1) {
			printf(" %4s", "������");
		} else if (p->status == 2) {
			printf(" %4s", "ִ����");
		} else if (p->status == 3) {
			printf(" %4s", "�����");
		}
		p = p->next;
	}	
	printf("\n");
}

// ��ʼ����������
void initQueue(pQueue &qhead) {
	qhead = (pQueue)malloc(sizeof(Queue));
	qhead->t_head = NULL;
	qhead->next = NULL;
}

// ���ٷ�������
void destroyQueue(pQueue head) {
	pQueue help;
	while (head != NULL) {
		help = head;
		head = head->next;
		destroyTask(help->t_head);
		free(help);
	}
}

// ��ӷ�������
void addQueue(pQueue head, int queue_ID, int priority, int serverTime) {
	pQueue p = (pQueue)malloc(sizeof(Queue));
	initTask(p->t_head);
	p->queue_ID = queue_ID;
	p->priority = priority;
	p->serverTime = serverTime;
	p->remainTime = serverTime;
	p->next = NULL;

	while(head->next != NULL) {
		head = head->next;
	}
	head->next = p;
}

// ��ӡ��������״̬
void printQueue(pQueue head) {
	pQueue p = head->next;
	if (p == NULL) {
		printf("\n ���ա���ӡ��������Ϊ��");
	}
	printf("\n ����id ���ȼ� ȫ��ʱ��Ƭ ʣ��ʱ��Ƭ ������ҵ��");
	while(p != NULL) {
		printf("\n %3d    %3d    %5d      %5d     ", p->queue_ID, p->priority, p->serverTime, p->remainTime);
		if(p->t_head->next == NULL) { 
			printf("%7s", "��");
		} else { 
			pTask p2 = p->t_head->next;
			while(p2 != NULL) {
				printf("%6s(ʣ%d��)->", p2->name, p2->remainTime);
				p2= p2->next;
			}
		}
		p = p->next;
	}
}

// ������ҵ����������
void InsertTaskToQueue(pQueue queue, pTask task) {
	pTask pro = queue->t_head;
	while(pro->next != NULL) {
		pro = pro->next;
	}
	pTask p = (pTask)malloc(sizeof(Task));
	strcpy(p->name, task->name);
	p->arriveTime = task->arriveTime;
	p->serverTime = task->serverTime;
	p->remainTime = task->remainTime;
	p->status = 1;
	p->next = NULL;
	pro->next = p;
}
// �ж��Ƿ����µ���ҵ����
void runNewTask(pQueue qhead, pTask thead) {
	pTask task;
	for (task = thead->next; task != NULL; task = task->next) {
		if (task->arriveTime == nowTime) {
			task->status = 1;
			task->arriveTime = nowTime;
			printf("\n����ӡ���%s(��%d��) �������", task->name, task->serverTime);
			InsertTaskToQueue(qhead->next, task);
		}
	}
	return;
	pQueue q = qhead->next;
}
// �ж��Ƿ����ִ��
int ifContinueRun(pQueue qhead, pTask thead) {
	pTask p = thead->next;
	pQueue q = qhead->next;
	while(p != NULL) {
		// ����δ������
		if(p->status != 1) {
			return 1;
		}
		p = p->next;
	}
	while(q != NULL) {
		// ����δ��ɵ�
		if(q->t_head->next != NULL) {
			return 1;
		}
		q = q->next;
	}
	return 0;
}
// ��ȡ��ǰӦ�����еķ�������
pQueue getRunQueue(pQueue qhead) {
	pQueue q, now;

	q = qhead->next;
	now = NULL;
	while(q != NULL) {
		if(q->t_head->next != NULL) {
			now = q;
			break;
		} 
		q = q->next;
	}
	return now;
}
// ִ��һ��ʱ��Ƭ
void runOneTime(pQueue qhead, pTask thead) {
	runNewTask(qhead, thead);
	pQueue now = getRunQueue(qhead); // ִ�еķ�������
	if(now == NULL) {
		return;
	}
	pTask runTask = now->t_head->next; // ִ�е���ҵ
	printf("\n��ִ�С���%s(ʣ%d��) ִ��", runTask->name, runTask->remainTime);
	// ִ��
	now->remainTime--;
	runTask->remainTime--;
	// ִ�����
	if(runTask->remainTime == 0) {
		// ����ҵ�Ѿ�ִ�����
		now->t_head->next = runTask->next;
		printf(" --> ִ����ϣ��Ƴ���������");
		free(runTask);
		if(now->remainTime == 0) { // ʱ��Ƭ���꣬����
			now->remainTime = now->serverTime;
		}
	} else {
		// ����ҵ��ҵûִ�����
		if(now->remainTime == 0) { // ʱ��Ƭ���꣬����
			now->remainTime = now->serverTime;
			now->t_head->next = runTask->next;
			// �Ѹ���ҵ�ŵ���һ������
			printf(" --> ûִ���꣬������һ����������");
			InsertTaskToQueue(now->next, runTask);
		}
	}
}

// ִ��
void run(pQueue qhead, pTask thead) {
	if(qhead == NULL || qhead->next == NULL) {
		printf("\n������ӷ������С�\n");
		return;
	}
	if(thead == NULL || thead->next == NULL) {
		printf("\n������ҵ��\n");
		return;
	}
	while(ifContinueRun(qhead, thead) == 1) { // ������ҵûִ����
		
		printf("\n ������������������������������������������������");
		printf("\n���� %d �롿", nowTime);
		runOneTime(qhead, thead); // ִ��һ��ʱ��Ƭ
		printf("\n���������");
		printQueue(qhead);
		printf("\n ������������������������������������������������\n");
		nowTime++;
	}
	
}

void test(pQueue qhead, pTask thead) {

	// ��ʼ�� ����
	initQueue(qhead);
	addQueue(qhead, 1, 1, 2);
	addQueue(qhead, 2, 2, 4);
	addQueue(qhead, 3, 3, 8);
	addQueue(qhead, 4, 4, 16);
	// ��ʼ����ҵ
	initTask(thead);
	addTask(thead, newTask("��ҵ1", 0, 3));
	addTask(thead, newTask("��ҵ2", 1, 2));
	addTask(thead, newTask("��ҵ3", 3, 1));
	addTask(thead, newTask("��ҵ4", 3, 6));
	addTask(thead, newTask("��ҵ5", 7, 2));
	
	// ��ʼ����ҵ
	run(qhead, thead);
	
	// �������ݣ��ͷ��ڴ�
	destroyTask(thead);
	destroyQueue(qhead);

	printf("\n\n������ִ����ϣ���лʹ�á�");

}