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
void init(TaskList &head) {
	head = (TaskList)malloc(sizeof(Task));
	head->next = NULL;
}

// ������ҵ
void destroy(TaskList head) {
	TaskList help;
	while (head != NULL) {
		help = head;
		head = head->next;
		free(help);
	}
}
// ������ҵ
TaskList newTask(char name[10], int arriveTime, int serverTime, int finishTime) {
	TaskList p = (TaskList)malloc(sizeof(Task));
	strcpy(p->name, name);
	p->arriveTime = arriveTime;
	p->finishTime = finishTime;
	p->serverTime = serverTime;
	p->remainTime = serverTime;
	p->relaxation = finishTime - nowTime - serverTime;
	p->status = 0;
	p->next = NULL;
	return p;
}
// ���뵽��ҵ����
void add(TaskList head, TaskList p) {
	while(head->next != NULL) {
		head = head->next;
	}
	head->next = p;
}

// ��ӡ��ҵ
void printAll(TaskList head) {
	TaskList p = head->next;

	printf("\n���� %d �롿:", nowTime);
	if (p == NULL) {
		printf("\n ���ա���ӡ��ҵΪ��");
	}
	printf("\n ��ҵ�� ����ʱ�� ����ʱ�� ��ֹʱ�� ʣ��ִ��ʱ�� �ɳڶ�   ״̬");
	while(p != NULL) {
		printf("\n %3s   %4d    %4d      %4d      %4d       ", p->name, p->arriveTime, p->serverTime, p->finishTime, p->remainTime);
		if (p->status == 0) {
			printf("%4s    %4s", "��", "δ����");
		} else if (p->status == 1) {
			printf("%4d    %4s", p->relaxation, "������");
		} else if (p->status == 2) {
			printf("%4d    %4s", p->relaxation, "ִ����");
		} else if (p->status == 3) {
			printf("%4s    %4s", "��", "�����");
		} else if (p->status == 4) {
			printf("%4s    %4s", "��", "��ʱ���");
		}
		p = p->next;
	}	
	printf("\n");
}

// �ж��Ƿ����ִ��
int ifContinueRun(TaskList head) {
	TaskList p = head->next;
	while(p != NULL) {
		// ����δ��ɵ�
		if(p->status < 3) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}

// �����ɳڶ�
void setRelax(TaskList head) {
	TaskList p = head->next;
	while(p != NULL) {
		p->relaxation = p->finishTime - nowTime - p->remainTime;
		// �ɳڶ� = ��ֹʱ�� - ��ǰ - ʣ��ִ��ʱ��
		p = p->next;
	}
}
// ѡ��������ҵ�����ɳڶ���͵���ҵ
TaskList getRunTask(TaskList head) {
	int min;
	TaskList result, p;

	p = head->next;
	result = NULL;

	min = -1001; // ��ʼ����Сֵ�ı�־

	while(p != NULL) {
		if(p->status != 1) {
			p = p->next;
			continue;
		} 
		if (min == -1001) {
			// ��ʼ����Сֵ
			min = p->relaxation;
			result = p;
			p = p->next;
			continue;
		}
		if(p->relaxation < min) {
			min = p->relaxation;
			result = p;
		} else if (p->relaxation == min) {
			// �ɳڶ���ͬ����ѡ��������ȥ�����㷨
			if(p->arriveTime < result->arriveTime) {
				result = p;
			}
		}
		p = p->next;
	}
	return result;
}
// ִ��һ����ҵ
void runTask(TaskList head, TaskList task) {
	task->status = 2;
	task->remainTime --;
	if(task->remainTime == 0) {
		// ��ҵ���
		if (nowTime+1 <= task->finishTime) {
			task->status = 3; 
		} else {
			task->status = 4;
		}
	} 
}
// ��ҵ����
void arriveTask(TaskList head) {
	TaskList p = head->next;
	while(p != NULL) {
		if(p->arriveTime == nowTime) {
			p->status = 1;
		}
		p = p->next;
	}
}
// ִ��
void run(TaskList head) {
	
	arriveTask(head);
	printAll(head); 
	while(ifContinueRun(head) == 1 ) { // ������ҵûִ����
		TaskList task = getRunTask(head); // ��ȡҪִ�е���ҵ
		if(task != NULL) {
			runTask(head, task); // ִ��
		} 
		nowTime++;
		setRelax(head); // ����ȫ����ҵ�ɳڶ�
		arriveTask(head); // ����ҵ��������
		printAll(head);  // ��ӡ
		if(task != NULL && task->status == 2) {
			// ��ִ�е���ҵ�����û��ɣ�������Ϊ����
			task->status = 1;
		}
	}
}

void test(TaskList head) {

	// ��ʼ����ҵ
	init(head);
	// �����ҵ
	add(head, newTask("��ҵ1", 0, 4, 13)); // ���� ����ʱ�� ����ʱ�� ��ֹʱ��
	add(head, newTask("��ҵ2", 1, 4, 9));
	add(head, newTask("��ҵ3", 1, 3, 12));
	add(head, newTask("��ҵ4", 2, 2, 6));
	add(head, newTask("��ҵ5", 3, 1, 12));
	// ��ʼ����ҵ
	run(head);
	// �������ݣ��ͷ��ڴ�
	destroy(head);
	printf("\n\n������ִ����ϣ���лʹ�á�");

}