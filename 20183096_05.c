#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Queue {
	struct Node* front;	//ť �� �� ���
	struct Node* rear;	//ť �� �� ���
};

struct Node {
	int data;	//��忡 ����� ��
	struct Node* next;	//���� ��� �ּҰ�
};

void Enqueue(struct Queue* queue);
void Dequeue(struct Queue* queue);
void Display(struct Queue* queue);

int n = 0;		//���� ��� ��
int max = 3;	//�ִ�� �� �� �ִ� ��� ��

int main() {
	int opt = 0;	//�ɼ� ���� ��
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));	//ť ����ü
	queue->front = NULL;	//ť �� �� ���� NULL(ó������ �ƹ� ��嵵 �����Ƿ�)
	queue->rear = NULL;		//ť �� �� ���� NULL(ó������ �ƹ� ��嵵 �����Ƿ�)

	while (1) {	//�ɼ� ������ EXIT�϶����� ����
		printf("\n1.Insertion \n2.Deletion \n3.Display \n0.Exit \n");
		printf("\nSelection Option : ");
		scanf("%d", &opt);	//�ɼ� ���� �� �Է¹ޱ�

		switch (opt) {
		case 1:	//���� 1: ť�� �� �ֱ� �Լ�
			Enqueue(queue);
			break;
		case 2:	//���� 2: ť���� �� ������ �Լ�
			Dequeue(queue);
			break;
		case 3:
			Display(queue);	//���� 3: �� ���� �Լ�
			break;
		case 0:
			break;	//���� 4: ���� Ż��
		default:
			continue;	//������ ���� ����: �ٽ� ������ ����
		}
		if (opt == 0) break;	//���� Ż��
	}

	return 0;	
}

void Enqueue(struct Queue* queue) {	//�� �ֱ� �Լ�
	int element;	
	printf("Element : ");
	scanf("%d", &element);	//��忡 ���� �� �Է�

	if (n >= max) {	//ť�� �� á�ٸ�
		printf("Queue is Full\n");

		return;	//�Լ� ����
	}

	struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//�� ���
	new->data = element;	//��忡 �� �ֱ�

	if (queue->front == NULL && queue->rear == NULL) {	//ť�� ��尡 �ƹ��͵� �����ٸ�
		queue->front = new;	//�� �� ���� ���� �� ���
		queue->rear = new;	//�� �ڴ� ���� �� ���
	}
	else {	//ť�� ��尡 �־��ٸ� 
		queue->rear->next = new;	//�� �� ��� ���� ���� ���� �� ���
		queue->rear = new;	//�� �� ���� ���� �� ���
		
	}
	printf("Successfully Insert\n");
	n++;	//��� �� ����
}

void Dequeue(struct Queue* queue) {	//�� ������ �Լ�
	if (n == 0) {	//ť�� ��尡 ���ٸ�
		printf("No element...");
		return;	//�Լ� ����
	}

	struct Node* del = (struct Node*)malloc(sizeof(struct Node));	//���� ��� ����Ű�� ������
	del = queue->front;	//���� ���� �� �� ���

	printf("Deleted item : %d", queue->front->data);	//���� �� ���

	if (n != 1) {	//���� ��尡 �ϳ��� �ƴϸ�
		queue->front = queue->front->next;	//�� �� ���� ���� �� �� ���� ���
	}
	else {	//���� ��尡 �ϳ��̸� 
		queue->front = NULL;	//�� �� ���� �ƹ� ��嵵 ����
		queue->rear = NULL;		//�� �� ���� �ƹ� ��嵵 ����
	}
	free(del);	//������ ��� ����
	n--;	//��� �� ����
	printf("\n");
}

void Display(struct Queue* queue) {	//�� ���� �Լ�	
	struct Node* now = queue->front;	//�� �� ��� ���� ���� ����
	printf("Items : ");

	int cnt = 0;
	while (cnt < n) {//���� ��� �� ��ŭ ���ʶ� ���� ����
		printf("%d	", now->data);	//���� ����� �� ���
		now = now->next;	//���� ��� ���Ǳ�
		cnt++;	//���� ��� �� ����
	}
	printf("\n");
}
