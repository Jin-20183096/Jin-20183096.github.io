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
void DeleteNode(struct List* list, int pos);

int n = 5;	//���� ��� ��

int main() {
	int pos;

	struct List* list = (struct List*)malloc(sizeof(struct List));	//����Ʈ ����ü
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));	//head ���
	list->first = head;	//����Ʈ ù ���� head
	list->last = NULL;	//����Ʈ ������ ���� NULL

	printf("Enter element in array: ");
	for (int i = 0; i < n; i++) {	//��� �����ϰ� �� �ֱ�
		int e = 0;
		scanf("%d", &e);
		CreateNode(list, e);
	}

	printf("Stored element in array: ");
	PrintNode(list);	//����Ʈ ���

	while (1) {//��带 ���� ������ ������ ����
		printf("\nEnter poss. of element to delete: ");
		scanf("%d", &pos);	//������ ����� ��ġ �Է�

		if (pos <= n) DeleteNode(list, pos);	//��ġ�� ��� ���� �������� �ʴ´ٸ� ��ġ�� ���� ��� �ϳ� ����

		if (n <= 0) break;	//���� ��尡 ���ٸ� ���� Ż��

		printf("\nAfter deletion elements in array: ");
		PrintNode(list);	//������ �� ����Ʈ ���
	}

	printf("\nNo more element!");

	return 0;
}

void CreateNode(struct List* list, int element) {	//�Է¹��� ���� ������� ��� ���� �Լ�
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//�� ��� �Ҵ�
	new->data = element;	//���� ��忡 �ֱ�
	new->next = NULL;		//�� ����̹Ƿ� ���� ��� NULL

	if (list->last == NULL)	//������ ��尡 NULL�̸� (���� ��尡 head���̶��)
		list->first->next = new;	//�� ���� head ���� ���
	else 
		list->last->next = new;		//�� ���� ������ ����� ���� ���

	list->last = new;	//������ ���� ���� ���θ��� ���
}

void PrintNode(struct List* list) {	//����Ʈ�� ���� ��� �ϴ� �Լ�
	struct Node* now = list->first->next;	//����� ���� ���� �ִ� head ���� ��� ����
	while (now != NULL) {	//NULL��尡 ���ö����� ����
		printf("%d ", now->data);	
		now = now->next;	
	}
}

void DeleteNode(struct List* list, int pos) {	//��ġ�� �´� ��� ���� �Լ�
	struct Node* now = list->first;	
	int cnt = 0;
	while (now != NULL) {
		if (cnt == pos - 1) {	//������ ��� �ٷ� �� ��忡 ���� �ߴٸ�
			struct Node* del = now->next;	//������ ��� ������
			now->next = (now->next)->next;	//�����ϱ��� ���� ���� ���� ����� ������ �̾��ֱ�
			free(del);	//��� �Ҵ� ����!
			n--;	//��� ���� �ϳ� ���̱�
			return;	//��� ���� �ߴٸ� �Լ� ��
		}
		now = now->next;
		cnt++;
	}
}