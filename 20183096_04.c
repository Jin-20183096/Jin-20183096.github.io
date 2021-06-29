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
void DeleteNode(struct List* list, int pos);

int n = 5;	//남은 노드 수

int main() {
	int pos;

	struct List* list = (struct List*)malloc(sizeof(struct List));	//리스트 구조체
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));	//head 노드
	list->first = head;	//리스트 첫 노드는 head
	list->last = NULL;	//리스트 마지막 노드는 NULL

	printf("Enter element in array: ");
	for (int i = 0; i < n; i++) {	//노드 생성하고 값 넣기
		int e = 0;
		scanf("%d", &e);
		CreateNode(list, e);
	}

	printf("Stored element in array: ");
	PrintNode(list);	//리스트 출력

	while (1) {//노드를 전부 삭제할 때까지 루프
		printf("\nEnter poss. of element to delete: ");
		scanf("%d", &pos);	//삭제할 노드의 위치 입력

		if (pos <= n) DeleteNode(list, pos);	//위치가 노드 수를 위반하지 않는다면 위치에 따른 노드 하나 삭제

		if (n <= 0) break;	//남은 노드가 없다면 루프 탈출

		printf("\nAfter deletion elements in array: ");
		PrintNode(list);	//삭제한 후 리스트 출력
	}

	printf("\nNo more element!");

	return 0;
}

void CreateNode(struct List* list, int element) {	//입력받은 값을 순서대로 노드 생성 함수
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//새 노드 할당
	new->data = element;	//값을 노드에 넣기
	new->next = NULL;		//새 노드이므로 다음 노드 NULL

	if (list->last == NULL)	//마지막 노드가 NULL이면 (현재 노드가 head뿐이라면)
		list->first->next = new;	//새 노드는 head 다음 노드
	else 
		list->last->next = new;		//새 노드는 마지막 노드의 다음 노드

	list->last = new;	//마지막 노드는 이제 새로만든 노드
}

void PrintNode(struct List* list) {	//리스트속 노드들 출력 하는 함수
	struct Node* now = list->first->next;	//출력할 노드는 값이 있는 head 다음 노드 부터
	while (now != NULL) {	//NULL노드가 나올때까지 루프
		printf("%d ", now->data);	
		now = now->next;	
	}
}

void DeleteNode(struct List* list, int pos) {	//위치에 맞는 노드 삭제 함수
	struct Node* now = list->first;	
	int cnt = 0;
	while (now != NULL) {
		if (cnt == pos - 1) {	//삭제할 노드 바로 앞 노드에 도달 했다면
			struct Node* del = now->next;	//삭제할 노드 포인터
			now->next = (now->next)->next;	//삭제하기전 이전 노드와 이후 노드의 포인터 이어주기
			free(del);	//노드 할당 해제!
			n--;	//노드 갯수 하나 줄이기
			return;	//노드 삭제 했다면 함수 끝
		}
		now = now->next;
		cnt++;
	}
}