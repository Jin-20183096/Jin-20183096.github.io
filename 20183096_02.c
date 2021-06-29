#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void ArrayCheck(int* arr, int arrLength);	//�Լ����� (Ư�� ���̸�ŭ �迭 �� ���)

int main() {
	int array[50];
	int posLast = 5;	//�迭�� ������ �� ��ġ
	int pos = 0;		//�� ������ ��ġ
	printf("Enter elements in array: ");

	for (int i = 0; i < posLast; i++) {	//�迭�� �� �־��ֱ�
		scanf("%d", &array[i]);
	}

	printf("Stored element in array: ");

	ArrayCheck(array, posLast);

	while (posLast > 0) {	// �迭�� ���� ���������� �ݺ�
		printf("\nEnter pos. of element to delete: ");
		scanf("%d", &pos);

		for (int s = pos; s < posLast; s++) {	//�迭�� �� �� ĭ�� �о��ֱ�
			array[s - 1] = array[s];
			if (s == posLast - 1) {
				array[s] = 0;
			}
		}
		posLast--;

		printf("Stored data in array: ");

		ArrayCheck(array, posLast);	//�迭 �� ��� �Լ�
	}

	printf("\nNo more element!");
	

	return 0;
}

void ArrayCheck(int* arr, int arrLength) {	//�Է¹��� �迭�� �Է¹��� ũ�⸸ŭ ����ϴ� �Լ�
	for (int i = 0; i < arrLength; i++) {
		printf("%d ", arr[i]);
	}

}