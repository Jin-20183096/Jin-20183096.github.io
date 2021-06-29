#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Queue {
	struct Node* front;	//큐 맨 앞 노드
	struct Node* rear;	//큐 맨 뒤 노드
};

struct Node {
	int data;	//노드에 저장된 값
	struct Node* next;	//다음 노드 주소값
};

void Enqueue(struct Queue* queue);
void Dequeue(struct Queue* queue);
void Display(struct Queue* queue);

int n = 0;		//현재 노드 수
int max = 3;	//최대로 들어갈 수 있는 노드 수

int main() {
	int opt = 0;	//옵션 선택 값
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));	//큐 구조체
	queue->front = NULL;	//큐 맨 앞 노드는 NULL(처음에는 아무 노드도 없으므로)
	queue->rear = NULL;		//큐 맨 뒤 노드는 NULL(처음에는 아무 노드도 없으므로)

	while (1) {	//옵션 선택이 EXIT일때까지 루프
		printf("\n1.Insertion \n2.Deletion \n3.Display \n0.Exit \n");
		printf("\nSelection Option : ");
		scanf("%d", &opt);	//옵션 선택 값 입력받기

		switch (opt) {
		case 1:	//선택 1: 큐에 값 넣기 함수
			Enqueue(queue);
			break;
		case 2:	//선택 2: 큐에서 값 꺼내기 함수
			Dequeue(queue);
			break;
		case 3:
			Display(queue);	//선택 3: 값 보기 함수
			break;
		case 0:
			break;	//선택 4: 루프 탈출
		default:
			continue;	//선택지 외의 선택: 다시 선택지 제시
		}
		if (opt == 0) break;	//루프 탈출
	}

	return 0;	
}

void Enqueue(struct Queue* queue) {	//값 넣기 함수
	int element;	
	printf("Element : ");
	scanf("%d", &element);	//노드에 넣을 값 입력

	if (n >= max) {	//큐에 다 찼다면
		printf("Queue is Full\n");

		return;	//함수 종료
	}

	struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//새 노드
	new->data = element;	//노드에 값 넣기

	if (queue->front == NULL && queue->rear == NULL) {	//큐에 노드가 아무것도 없었다면
		queue->front = new;	//맨 앞 노드는 이제 새 노드
		queue->rear = new;	//맨 뒤는 이제 새 노드
	}
	else {	//큐에 노드가 있었다면 
		queue->rear->next = new;	//맨 뒤 노드 다음 노드는 이제 새 노드
		queue->rear = new;	//맨 뒤 노드는 이제 새 노드
		
	}
	printf("Successfully Insert\n");
	n++;	//노드 수 증가
}

void Dequeue(struct Queue* queue) {	//값 꺼내기 함수
	if (n == 0) {	//큐에 노드가 없다면
		printf("No element...");
		return;	//함수 종료
	}

	struct Node* del = (struct Node*)malloc(sizeof(struct Node));	//꺼낼 노드 가리키는 포인터
	del = queue->front;	//꺼낼 노드는 맨 앞 노드

	printf("Deleted item : %d", queue->front->data);	//꺼낸 값 출력

	if (n != 1) {	//남은 노드가 하나가 아니면
		queue->front = queue->front->next;	//맨 앞 노드는 이제 맨 앞 다음 노드
	}
	else {	//남은 노드가 하나이면 
		queue->front = NULL;	//맨 앞 노드는 아무 노드도 없음
		queue->rear = NULL;		//맨 뒤 노드는 아무 노드도 없음
	}
	free(del);	//꺼내진 노드 삭제
	n--;	//노드 수 감소
	printf("\n");
}

void Display(struct Queue* queue) {	//값 보기 함수	
	struct Node* now = queue->front;	//맨 앞 노드 부터 보기 시작
	printf("Items : ");

	int cnt = 0;
	while (cnt < n) {//현재 노드 수 만큼 살필때 까지 루프
		printf("%d	", now->data);	//살핀 노드의 값 출력
		now = now->next;	//다음 노드 살피기
		cnt++;	//살핀 노드 수 증가
	}
	printf("\n");
}
