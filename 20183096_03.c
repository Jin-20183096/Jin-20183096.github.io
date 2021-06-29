#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct List {
	struct Node* first;	//리스트 첫 노드
	struct Node* last;	//리스트 마지막 노드
};

struct Node {
	int data;	//노드에 저장된 값
	struct Node* next;	//다음 노드 주소값
};

void CreateNode(struct List* list, int element);
void PrintNode(struct List* list);
void InputNode(struct List* list, int pos, int element);

int n = 5;	//남은 노드 수

int main() {
	int pos;
	int element;

	struct List* list = (struct List*)malloc(sizeof(struct List));	//리스트 구조체
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));	//head 노드
	list->first = head;	//리스트 첫 노드는 head
	list->last = NULL;	//리스트 마지막 노드는 NULL

	printf("Enter 5 elements in array: ");
	for (int i = 0; i < n; i++) {	//노드 생성하고 값 넣기
		int e;
		scanf("%d", &e);
		CreateNode(list, e);
	}

	printf("Stored element in array: ");
	PrintNode(list);	//생성된 노드들 출력

	while (n < 50) {	//50개의 노드를 만들때 까지 루프
		printf("\nEnter position for enter element: ");
		scanf("%d", &pos);	//추가할 노드의 위치 입력

		printf("Enter new element: ");
		scanf("%d", &element);	//추가할 노드의 값 입력

		InputNode(list, pos, element);	//위치에 따른 노드 추가

		printf("Stored element in array: ");
		PrintNode(list);	//값 추가한 리스트 출력
	}

	printf("\nNo more space!!");

	return 0;
}

void CreateNode(struct List * list, int element) {	//입력 받은 값 순서대로 노드 생성 함수
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//새 노드 생성
	new->data = element;	//값 노드에 넣기
	new->next = NULL;		//새 노드이므로 다음 노드는 NULL

	if (list->last == NULL)	//마지막 노드가 NULL이면 (현재 노드가 head뿐이라면)
		list->first->next = new;	//새 노드는 head 다음 노드
	else
		list->last->next = new;	//새 노드는 마지막 노드의 다음 노드
	list->last = new;	//마지막 노드는 이제 새로 만든 노드
}

void PrintNode(struct List* list) {	//리스트 속 노드들 출력 하는 함수
	struct Node* now = list->first->next;	//출력할 노드는 값이 있는 head 다음 노드 부터
	while (now != NULL) {	//NULL노드가 나올때까지 루프
		printf("%d ", now->data);
		now = now->next;
	}
}

void InputNode(struct List * list, int pos, int element) {	//위치에 노드 삽입 함수
	struct Node* now = list->first;
	int cnt = 0;
	while (now != NULL) {
		if (cnt == pos - 1) {	//삽입할 노드 바로 앞 노드에 도달했다면 
			struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//새 노드 생성
			new->data = element;	//노드에 값 넣기
			new->next = now->next;	//새 노드가 가리키는 노드는 원래 그 자리 노드가 가리키던 노드
			now->next = new;	//원래 노드가 가리키는 노드는 이제 새로운 노드
		}
		now = now->next;
		cnt++;
	}
	n++;	//노드 값 증가
}