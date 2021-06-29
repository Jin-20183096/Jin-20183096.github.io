#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void ArrayCheck(int* arr, int arrLength);	//함수선언 (특정 길이만큼 배열 값 출력)

int main() {
	int array[50];
	int posLast = 5;	//배열의 마지막 값 위치
	int pos = 0;		//값 제거할 위치
	printf("Enter elements in array: ");

	for (int i = 0; i < posLast; i++) {	//배열에 값 넣어주기
		scanf("%d", &array[i]);
	}

	printf("Stored element in array: ");

	ArrayCheck(array, posLast);

	while (posLast > 0) {	// 배열의 값이 없을때까지 반복
		printf("\nEnter pos. of element to delete: ");
		scanf("%d", &pos);

		for (int s = pos; s < posLast; s++) {	//배열속 값 한 칸씩 밀어주기
			array[s - 1] = array[s];
			if (s == posLast - 1) {
				array[s] = 0;
			}
		}
		posLast--;

		printf("Stored data in array: ");

		ArrayCheck(array, posLast);	//배열 값 출력 함수
	}

	printf("\nNo more element!");
	

	return 0;
}

void ArrayCheck(int* arr, int arrLength) {	//입력받은 배열을 입력받은 크기만큼 출력하는 함수
	for (int i = 0; i < arrLength; i++) {
		printf("%d ", arr[i]);
	}

}