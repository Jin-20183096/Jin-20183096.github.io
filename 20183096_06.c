#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Stack {
	struct Node* top;	//스택 맨 위
};

struct Node {
	int data;	//노드에 저장된 값
	struct Node* next;	//다음 노드 주소값
};

void Push(struct Stack* stack);
void Display(struct Stack* stack);
void Pop(struct Stack* stack);

int main() {
	int opt = 0;	//옵션 선택 값
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));	//스택 구조체
	stack->top = NULL;	//스택의 맨 위는 NULL (처음에는 아무 노드도 없으므로)

	while (1) {	//옵션 선택에서 EIXT하기까지 루프
		printf("\n1: push \n2: pop \n3: display \n4: exit");
		printf("\nenter your choice: ");
		scanf("%d", &opt);	//옵션 선택 값 입력받기

		switch (opt) {
		case 1:
			Push(stack);	//선택 1: 값 넣기 함수
			break;
		case 2:
			Pop(stack);	//선택 2: 값 꺼내기 함수
			break;
		case 3:
			Display(stack);	//선택 3: 값 보기 함수
			break;
		case 4:
			break;	//선택 4: 루프 탈출
		default:
			continue;	//선택지외의 선택: 다시 선택지 제시
		}
		if (opt == 4) break; // 루프 탈출
	}

	return 0;
}

void Push(struct Stack* stack) {	//값 넣기 함수
	while (1) {	//그만 넣을 때까지 루프
		printf("\nEnter element in stack: ");
		int element;
		scanf("%d", &element);	//노드에 넣을 값 입력받음

		struct Node* new = (struct Node*)malloc(sizeof(struct Node));	//새 노드
		new->data = element;	//노드에 입력받은 값 주기
		new->next = stack->top;	//새 노드의 다음(아래) 노드는 스택 맨 위였던 노드

		stack->top = new;	//스택의 맨 위 노드는 이제 새 노드

		printf("\nPushed an element (Y/N): ");	//값을 더 넣을것인가?
		int ans = getchar();	//대답 입력 받음

		if (ans == 'y' || ans == 'Y') continue;	//대답이 y,Y이면 한번 더 넣기 
		else break;	//이외의 대답이면 루프 탈출
	}
	printf("\n");
}

void Pop(struct Stack* stack) {	//값 꺼내기 함수
	if (stack->top == NULL) {	//맨 위 노드가 NULL이면 (값이 없으면)
		printf("\nNo more element!");
		return;	//함수 종료
	}

	printf("\ndeleted data is: %d", stack->top->data);	//꺼낸 맨 위 노드의 값 출력
	
	struct Node* del = stack->top;	//꺼낸 맨 위 노드 주소값
	stack->top = stack->top->next;	//맨 위 노드는 이제 그 아래 노드
	free(del);	//꺼낸 맨 위 노드 할당 해제!

	printf("\n");

	printf("\nPushed an element (Y/N): ");	//새로운 값을 넣을것인가?
	int ans = getchar();	//대답 입력 받음

	if (ans == 'y' || ans == 'Y') Push(stack);	//대답이 y,Y이면 노드 한번 더 넣기
}

void Display(struct Stack* stack) {	//값 보기 함수
	struct Node* now = stack->top;	//맨 위 노드부터 살피기
	while (now != NULL) {	//맨 아래 노드에 도달할떄까지 루프
		printf("\n");
		printf("%d", now->data);
		now = now->next;	//다음(아래) 노드 살피기
	}
	printf("\n");

	printf("\nPushed an element (Y/N): ");	//새로운 값을 넣을것인가?
	int ans = getchar();	//대답 입력 받음

	if (ans == 'y' || ans == 'Y') Push(stack);	//대답이 y,Y이면 노드 한번 더 넣기
}