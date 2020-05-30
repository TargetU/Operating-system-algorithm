#include "Fit.h"


int AllSize = 640;

//��ʼ��
void init(LinkedList& head) {
	head = (LinkedList)malloc(sizeof(LNode));
	if (NULL == head) {
		printf("\n ����ʼ���������ڴ�ʧ�ܣ�");
		exit(0);
	}
	head->id = -1;
	head->status = -1;
	head->next = (LinkedList)malloc(sizeof(LNode));
	head->next->id = 0;
	head->next->begin = 1;
	head->next->end = AllSize;
	head->next->status = 0;
	head->next->next = NULL;

}

//�������нڵ�����
void destory(LinkedList &head) {
	LinkedList help;
	while (head != NULL) {
		help = head;
		head = head->next;
		free(help);
	}
	printf("\n �����١����пռ����ͷţ�");
}
// ��ӡһ�����ڴ�״��
void printOne(LinkedList p) {
	if(p->status==0) {
		printf("\n  |%6s|", "��");
	} else {
		printf("\n  |%6d|", p->id);
	}
	printf("   |%8d|    |%8d|    |%7dKB|", p->begin, p->end, p->end - p->begin + 1);
	printf("     |%6s|", p->status==0 ? "����":"��ռ��");
}

// ��ӡȫ����ҵ��Ϣ
void printAll (LinkedList head) {
	LinkedList p;
	printf("\n ����������������������������������������������������������������");
	printf("\n  |������|   |��ʼ��ַ|    |ĩβ��ַ|    |�ڴ�ռ� |     |״̬  |");
	for (p = head->next; p != NULL; p = p->next) {
		printOne(p);
	}
	printf("\n ����������������������������������������������������������������\n");
}

// ��ȡ����ҵ�ڵ����� 
int getId(LinkedList head) {
	LinkedList p;
	int result = 0;
	for (p = head->next; p != NULL; p = p->next) {
		if (p->id > result) {
			result = p->id;
		}
	}
	return result + 1;
}


// ���״���Ӧ�㷨����ȡ�ʺϲ����½ڵ����һ���ڵ�
LinkedList getPro1(LinkedList head, int size) {
	LinkedList p;
	for (p = head; p->next != NULL; p = p->next) {
		if (p->next->status == 0 && (p->next->end - p->next->begin + 1) >= size) {
			break;
		}
	}
	if(size == 140) {
		// printOne(p->next);
	}
	return p;
}
// �������Ӧ�㷨����ȡ�ʺϲ����½ڵ����һ���ڵ�
LinkedList getPro2(LinkedList head, int size) {
	LinkedList p, resultPro;
	int minSize = AllSize;
	resultPro = NULL;
	for ( p = head; p->next != NULL; p = p->next) {
		if (p->next->status == 0) {
			int p_size = p->next->end - p->next->begin + 1;
			// printf("\n  p_size = %d, size= %d,  minSize=  %d \n", p_size, size, minSize);
			if (p_size >= size && p_size <= minSize) {
				
				minSize = p_size;
				resultPro = p;
			}
		}
	}
	return resultPro;
}
// ����ڵ㣨��ҵ����ռ䣩
void addNode(LinkedList head, int size, int type) {
	LinkedList p;
	int id = getId(head);
	printf("\n����ҵ%d����", id);
	if(type == 0) {
		// �״���Ӧ�㷨
		p = getPro1(head, size);
	} else {
		// �����Ӧ�㷨
		p = getPro2(head, size);
	}
	
	if(p==NULL || p->next == NULL) {
		// ������ҵ�ڴ�ռ�ʧ��
		printf("�����ڴ�ռ�ʧ�ܣ��ڴ治��");
	} else {
		
		LinkedList newNode = (LinkedList)malloc(sizeof(LNode));
		newNode->status = 1;
		newNode->id = id;
		newNode->begin = p->next->begin;
		newNode->end = newNode->begin + size - 1; 
		p->next->begin = newNode->end + 1;
		newNode->next = p->next;
		p->next = newNode;
		printf("�ɹ����� %4d KB�ڴ�ռ�", newNode->end - newNode->begin + 1);
	}
	printAll(head);
}

// ɾ���ڵ㣨��ҵ�ͷſռ䣩
void delNode(LinkedList head, int id) {
	LinkedList p;
	printf("\n����ҵ%d����", id);
	for (p = head; p->next != NULL; p = p->next) {
		if (p->next->id == id) {
			LinkedList pro = p;
			LinkedList del = p->next;
			LinkedList next = del->next;
			if(del->status == 1) {
				printf("�ɹ��ͷ� %4d KB�ڴ�ռ�",  del->end - del->begin + 1);
				// �ϲ�
				if( pro->id == -1) { // proΪͷ�ڵ�
					if(next->status == 0){ 
						// next����
						del->status = 0;
						del->end = next->end;
						del->next = next->next;
						free(next);
					} else { 
						//next��ռ�� 
						del->status = 0;
					} 
				} else { // pro��Ϊͷ�ڵ�
					if(pro->status == 0 && next->status == 1){ 
						// pro���У�next��ռ�� 
						pro->next = next;
						pro->end = del->end;
						free(del);
					} else if(pro->status == 1 && next->status == 0){ 
						// pro��ռ�ã�next����
						pro->next = next;
						next->begin = del->begin;
						free(del);
					} else if(pro->status == 0 && next->status == 0) { 
						// pro��next������
						pro->next = next->next;
						pro->end = next->end;
						free(del);
						free(next);
					} else {
						// pro��next����ռ��
						del->status = 0;
					}
					
				}
			} else {
				// û�и���ҵ
				printf("�ͷ��ڴ�ռ�ʧ�ܣ�û�и���ҵ");
			}
			break;
		}
	}
	printAll(head);
}



void test(LinkedList head, int type) {
	printf("��ҵ1 ����130 KB\n");
	//��ҵ1 ����130KB
	addNode(head, 130, type);
	//��ҵ2 ����60KB
	addNode(head, 60, type);
	//��ҵ3 ����100KB
	addNode(head, 100, type);
	//��ҵ2 �ͷ�60KB
	delNode(head, 2);
	//��ҵ4 ����200KB
	addNode(head, 200, type);
	//��ҵ3 �ͷ�100KB
	delNode(head, 3);
	//��ҵ1 �ͷ�130KB
	delNode(head, 1);
	//��ҵ5 ����140KB
	addNode(head, 140, type);
	//��ҵ6 ����60KB
	addNode(head, 60, type);
	//��ҵ7 ����50KB
	addNode(head, 50, type);
	//��ҵ8 ����60KB
	addNode(head, 60, type);
}
