#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void ArrayCheck(int * arr, int arrLength);	//�Լ����� (Ư�� ���̸�ŭ �迭 �� ���)

int main() {
	int array[50] = {0};
	int posLast = 5;	//�迭�� ������ ��ġ
	int pos = 0;		//�� �Է��� ��ġ
	int newEle = 0;		//���� �Է��� ��
	printf("Enter 5 elements in array: ");

	for (int i = 0; i < posLast; i++) {	//�迭�� ��
		scanf("%d", &array[i]);
	}

	printf("Stored element in array: ");
	
	ArrayCheck(array, posLast);

	while (posLast < sizeof(array)/sizeof(int)) {
		printf("\nEnter position for enter element: ");
		scanf("%d", &pos);
		printf("Enter new element: ");
		scanf("%d", &newEle);

		for (int s = posLast; s > pos - 1; s--) {
			array[s] = array[s - 1];
			if (pos == s) {
				array[s - 1] = newEle;
			}
		}
		posLast++;

		printf("Stored data in array: ");

		ArrayCheck(array, posLast);
	}
	
	printf("No more space!");

	return 0;
}

void ArrayCheck(int * arr, int arrLength) {	//�Է¹��� �迭�� �Է¹��� ũ�⸸ŭ ����ϴ� �Լ�
	for (int i = 0; i < arrLength; i++) {
		printf("%d ", arr[i]);
	}

}