#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void ArrayCheck(int * arr, int arrLength);	//함수선언 (특정 길이만큼 배열 값 출력)

int main() {
	int array[50] = {0};
	int posLast = 5;	//배열의 마지막 위치
	int pos = 0;		//값 입력할 위치
	int newEle = 0;		//새로 입력할 값
	printf("Enter 5 elements in array: ");

	for (int i = 0; i < posLast; i++) {	//배열에 값
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

void ArrayCheck(int * arr, int arrLength) {	//입력받은 배열을 입력받은 크기만큼 출력하는 함수
	for (int i = 0; i < arrLength; i++) {
		printf("%d ", arr[i]);
	}

}