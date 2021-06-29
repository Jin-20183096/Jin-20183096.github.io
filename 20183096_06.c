#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Stack {
	struct Node* top;	//���� �� ��
};

struct Node {
	int data;	//��忡 ����� ��
	struct Node* next;	//���� ��� �ּҰ�
};

void Push(struct Stack* stack);
void Display(struct Stack* stack);
void Pop(struct Stack* stack);

int main() {
	int opt = 0;	//�ɼ� ���� ��
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));	//���� ����ü
	stack->top = NULL;	//������ �� ���� NULL (ó������ �ƹ� ��嵵 �����Ƿ�)

	while (1) {	//�ɼ� ���ÿ��� EIXT�ϱ���� ����
		printf("\n1: push \n2: pop \n3: display \n4: exit");
		printf("\nenter your choice: ");
		scanf("%d", &opt);	//�ɼ� ���� �� �Է¹ޱ�

		switch (opt) {
		case 1:
			Push(stack);	//���� 1: �� �ֱ� �Լ�
			break;
		case 2:
			Pop(stack);	//���� 2: �� ������ �Լ�
			break;
		case 3:
			Display(stack);	//���� 3: �� ���� �Լ�
			break;
		case 4:
			break;	//���� 4: ���� Ż��
		default:
			continue;	//���������� ����: �ٽ� ������ ����
		}
		if (opt == 4) break; // ���� Ż��
	}

	return 0;
}

void Push(struct Stack* stack) {	//�� �ֱ� �Լ�
	while (1) {	//�׸� ���� ������ ����
		printf("\nEnter element in stack: ");
		int element;
		scanf("%d", &element);	//��忡 ���� �� �Է¹���

		struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//�� ���
		new->data = element;	//��忡 �Է¹��� �� �ֱ�
		new->next = stack->top;	//�� ����� ����(�Ʒ�) ���� ���� �� ������ ���

		stack->top = new;	//������ �� �� ���� ���� �� ���

		printf("\nPushed an element (Y/N): ");	//���� �� �������ΰ�?
		int ans = getchar();	//��� �Է� ����

		if (ans == 'y' || ans == 'Y') continue;	//����� y,Y�̸� �ѹ� �� �ֱ� 
		else break;	//�̿��� ����̸� ���� Ż��
	}
	printf("\n");
}

void Pop(struct Stack* stack) {	//�� ������ �Լ�
	if (stack->top == NULL) {	//�� �� ��尡 NULL�̸� (���� ������)
		printf("\nNo more element!");
		return;	//�Լ� ����
	}

	printf("\ndeleted data is: %d", stack->top->data);	//���� �� �� ����� �� ���
	
	struct Node* del = stack->top;	//���� �� �� ��� �ּҰ�
	stack->top = stack->top->next;	//�� �� ���� ���� �� �Ʒ� ���
	free(del);	//���� �� �� ��� �Ҵ� ����!

	printf("\n");

	printf("\nPushed an element (Y/N): ");	//���ο� ���� �������ΰ�?
	int ans = getchar();	//��� �Է� ����

	if (ans == 'y' || ans == 'Y') Push(stack);	//����� y,Y�̸� ��� �ѹ� �� �ֱ�
}

void Display(struct Stack* stack) {	//�� ���� �Լ�
	struct Node* now = stack->top;	//�� �� ������ ���Ǳ�
	while (now != NULL) {	//�� �Ʒ� ��忡 �����ҋ����� ����
		printf("\n");
		printf("%d", now->data);
		now = now->next;	//����(�Ʒ�) ��� ���Ǳ�
	}
	printf("\n");

	printf("\nPushed an element (Y/N): ");	//���ο� ���� �������ΰ�?
	int ans = getchar();	//��� �Է� ����

	if (ans == 'y' || ans == 'Y') Push(stack);	//����� y,Y�̸� ��� �ѹ� �� �ֱ�
}