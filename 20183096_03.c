#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct List {
	struct Node* first;	//����Ʈ ù ���
	struct Node* last;	//����Ʈ ������ ���
};

struct Node {
	int data;	//��忡 ����� ��
	struct Node* next;	//���� ��� �ּҰ�
};

void CreateNode(struct List* list, int element);
void PrintNode(struct List* list);
void InputNode(struct List* list, int pos, int element);

int n = 5;	//���� ��� ��

int main() {
	int pos;
	int element;

	struct List* list = (struct List*)malloc(sizeof(struct List));	//����Ʈ ����ü
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));	//head ���
	list->first = head;	//����Ʈ ù ���� head
	list->last = NULL;	//����Ʈ ������ ���� NULL

	printf("Enter 5 elements in array: ");
	for (int i = 0; i < n; i++) {	//��� �����ϰ� �� �ֱ�
		int e;
		scanf("%d", &e);
		CreateNode(list, e);
	}

	printf("Stored element in array: ");
	PrintNode(list);	//������ ���� ���

	while (n < 50) {	//50���� ��带 ���鶧 ���� ����
		printf("\nEnter position for enter element: ");
		scanf("%d", &pos);	//�߰��� ����� ��ġ �Է�

		printf("Enter new element: ");
		scanf("%d", &element);	//�߰��� ����� �� �Է�

		InputNode(list, pos, element);	//��ġ�� ���� ��� �߰�

		printf("Stored element in array: ");
		PrintNode(list);	//�� �߰��� ����Ʈ ���
	}

	printf("\nNo more space!!");

	return 0;
}

void CreateNode(struct List * list, int element) {	//�Է� ���� �� ������� ��� ���� �Լ�
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//�� ��� ����
	new->data = element;	//�� ��忡 �ֱ�
	new->next = NULL;		//�� ����̹Ƿ� ���� ���� NULL

	if (list->last == NULL)	//������ ��尡 NULL�̸� (���� ��尡 head���̶��)
		list->first->next = new;	//�� ���� head ���� ���
	else
		list->last->next = new;	//�� ���� ������ ����� ���� ���
	list->last = new;	//������ ���� ���� ���� ���� ���
}

void PrintNode(struct List* list) {	//����Ʈ �� ���� ��� �ϴ� �Լ�
	struct Node* now = list->first->next;	//����� ���� ���� �ִ� head ���� ��� ����
	while (now != NULL) {	//NULL��尡 ���ö����� ����
		printf("%d ", now->data);
		now = now->next;
	}
}

void InputNode(struct List * list, int pos, int element) {	//��ġ�� ��� ���� �Լ�
	struct Node* now = list->first;
	int cnt = 0;
	while (now != NULL) {
		if (cnt == pos - 1) {	//������ ��� �ٷ� �� ��忡 �����ߴٸ� 
			struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//�� ��� ����
			new->data = element;	//��忡 �� �ֱ�
			new->next = now->next;	//�� ��尡 ����Ű�� ���� ���� �� �ڸ� ��尡 ����Ű�� ���
			now->next = new;	//���� ��尡 ����Ű�� ���� ���� ���ο� ���
		}
		now = now->next;
		cnt++;
	}
	n++;	//��� �� ����
}