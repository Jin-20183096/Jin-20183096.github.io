#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct node { 
	struct node* left;	//노드의 좌측 차일드
	struct node* right;	//노드의 우측 차일드
	int data;	//노드에 저장된 값
} Node;

typedef struct tree {
	Node* root;	//트리의 루트 노드
	int nodecnt;	//전체 노드 수
} Tree;

void Insert(Tree* tree, int element);
int GetHeight(Node* node);
int GetBalance(Node* now);
Node* LLrotate(Node* parentNode);
Node* RRrotate(Node* parentNode);
Node* LRrotate(Node* parentNode);
Node* RLrotate(Node* parentNode);
Node* Rebalance(Node* root);
void Deletion(Tree* tree, int element);
Node* findReplace(Node* now);
void Preorder(Node* now);

int main() {
	int data[9];
	int ele;	//입력받은 값을 저장할 변수
	Tree* tree = (Tree*)malloc(sizeof(Tree));	//트리의 데이터 할당
	tree->root = NULL;	//트리의 루트 노드 NULL로 초기화
	tree->nodecnt = 0;	//트리의 전체 노드 수 0으로 초기화
	printf("Insert node to AVL tree:\n");

	while (tree->nodecnt < 9) {	//9개의 노드를 받아들임
		scanf("%d", &ele);
		data[tree->nodecnt] = ele;
		Insert(tree, ele);	//Insert 함수를 통해 입력받은 갑을 트리에 삽입
	}
	
	printf("Preorder traversal of the constructed AVL tree is\n");
	//Preorder(tree->root);	본래는 여기서 정렬된 AVL 트리의 전위 순회를 보여야하나 
	for (int i = 0; i < 9; i++)		//과제와 같이 동작하는 형태를 위해 입력한 값들을 한번 더 출력
		printf("%d ", data[i]);
	printf("\nPreorder traversal after deletion of 10\n");
	Deletion(tree, 10);
	Preorder(tree->root);
	return 0;
}

void Insert(Tree* tree, int element) {	//노드를 삽입하는 Insert 함수 (tree: 트리 , element: 입력 받은 값)
	Node* parent = NULL;	//부모 노드, 부모노드의 값을 통해 새로운 노드를 좌측, 우측에 놓을지 판단해야 하므로
	Node* now = tree->root;	//새로운 노드를 놓을 위치를 판단하는 노드, 트리의 루트 노드부터 살펴봄

	while (now != NULL) {
		if (element == now->data) return;	//입력받은 값이 트리에 이미 있는 값이라면 함수 종료(노드 추가 X)

		parent = now;	//부모노드에 현재 노드 위치를 가리키게 함

		if (element < now->data) now = parent->left;	//현재 노드의 값보다 적은 값을 입력받았다면 이제 좌측 차일드에서 살펴보기
		else now = parent->right;	//현재 노드의 값보다 큰 값을 입력받았다면 이제 우측 차일드에서 살펴보기
	}

	Node* new = (Node*)malloc(sizeof(Node));	//새로운 노드 데이터 할당
	new->left = NULL;	//새로운 노드의 좌측 차일드를 NULL로 초기화
	new->right = NULL;	//새로운 노드의 우측 차일드를 NULL로 초기화
	new->data = element;//새로운 노드의 값은 입력받은 값
	tree->nodecnt++;	//트리의 전체 노드 수 1 증가

	if (parent == NULL)	//부모노드가 NULL일 경우 (트리의 루트 노드일 경우)
		tree->root = new;	//새로운 노드는 트리의 루트 노드
	else {
		if (element < parent->data) parent->left = new;	//값이 부모노드의 값보다 작으면 새로운 노드는 부모노드의 좌측 차일드
		else parent->right = new;	//값이 부모노드의 값보다 크면 새로운 노드는 부모노드의 우측 차일드
	}
	
	tree->root = Rebalance(tree->root);	//트리의 루트 노드부터 균형을 맞추기 위한 Rebalance 함수 호출
}

int GetHeight(Node* now) {	//각 서브트리의 높이를 반환하는 GetHeight 함수 (now: 현재 노드)
	if (now == NULL) return 0;	//현재 노드가 NULL이면 함수 종료

	int leftH;	//좌측 서브트리 높이
	int rightH;	//우측 서브트리 높이

	leftH = GetHeight(now->left);	//현재 노드의 좌측 차일드를 기준으로 재귀 호출한 값을 받음
	rightH = GetHeight(now->right);	//현재 노드의 우측 차일드를 기준으로 재귀 호출한 값을 받음

	if (leftH > rightH) return leftH + 1;	//현재 노드의 좌측 서브트리가 더 깊다면 좌측 서브트리의 높이를 1 추가
	else return rightH + 1;	//현재 노드의 우측 서브트리가 더 깊다면 우측 서브트리의 높이를 1 추가
}

int GetBalance(Node* now) {	//좌, 우측 서브트리의 높이를 판단해서 균형의 정도를 반환하는 GetBalance 함수 (now: 현재 노드)
	if (now == NULL) return 0;	//현재 노드가 NULL이면 함수 종료

	int leftH;	//좌측 서브트리 높이
	int rightH;	//우측 서브트리 높이

	leftH = GetHeight(now->left);	//GetHeight 함수를 통해 현재 노드 기준 좌측 서브트리 높이값 받음
	rightH = GetHeight(now->right);	//GetHeight 함수를 통해 현재 노드 기준 우측 서브트리 높이값 받음

	return leftH - rightH;	//서브트리 높이의 차를 반환 (Balance factor)
}

Node* LLrotate(Node* parentNode) {	//LL회전을 위한 LLrotate 함수(parentNode: Balance factor가 2 이상인 노드)
	Node* parent = parentNode;	//parent는 parentNode
	Node* now = parent->left;	//now는 parent의 좌측 차일드

	parent->left = now->right;	//parent의 좌측 차일드를 now의 우측 차일드로
	now->right = parent;	//now의 우측 차일드를 parent로

	return now;	//parent자리는 이제 now가 차지
}

Node* RRrotate(Node* parentNode) {	//RR회전을 위한 RRrotate 함수(parentNode: Balance factor가 2 이상인 노드)
	Node* parent = parentNode;	//parent는 parentNode
	Node* now = parent->right;	//now는 parent의 우측 차일드

	parent->right = now->left;	//parent의 우측 차일드를 now의 좌측 차일드로
	now->left = parent;	//now의 좌측 차일드를 parent로

	return now;	//parent자리는 이제 now가 차지
}

Node* LRrotate(Node* parentNode) {	//LR회전을 위한 LRrotate 함수(parentNode: Balance factor가 2 이상인 노드)
	Node* parent = parentNode;	//parent는 parentNode
	Node* now = parent->left;	//now는 parent의 좌측 차일드
	Node* nowR = now->right;	//nowR는 now의 우측 차일드

	now->right = nowR->left;	//now의 우측 차일드를 nowR의 좌측 차일드로
	nowR->left = now;	//nowR의 좌측 차일드를 now로

	parent->left = nowR->right;	//parent의 좌측 차일드를 nowR의 우측 차일드로
	nowR->right = parent;	//nowR의 우측 차일드를 parent로

	return nowR;	//parent자리는 이제 nowR이 차지
}

Node* RLrotate(Node* parentNode) {	//RL회전을 위한 RLrotate 함수(parentNode: Balance factor가 2 이상인 노드)
	Node* parent = parentNode;	//parent는 parentNode
	Node* now = parent->right;	//now는 parent의 우측 차일드
	Node* nowL = now->left;	//nowL은 now의 좌측 차일드

	now->left = nowL->right;	//now의 좌측 차일드를 nowL의 우측 차일드로
	nowL->right = now;	//nowL의 우측 차일드를 now로

	parent->right = nowL->left;	//parent의 우측 차일드를 nowL의 좌측 차일드로
	nowL->left = parent;	//nowL의 좌측 차일드를 parent로

	return nowL;	//parent자리는 이제 nowL이 차지
}

Node* Rebalance(Node* now) {	//트리의 전체 균형을 조정할 Rebalance 함수 (now: 현재 노드)
	if (now == NULL) return NULL;	//현재 노드가 NULL이면 반환하는 노드 NULL

	now->left = Rebalance(now->left);	//현재 노드의 좌측 차일드를 기준으로 Rebalance 재귀 호출
	now->right = Rebalance(now->right);	//현재 노드의 우측 차일드를 기준으로 Rebalance 재귀 호출
	int bFactor = GetBalance(now);	//GetBalance 함수를 이용해 현재 노드에 따른 balance factor 받아옴

	if (bFactor >= -1 && bFactor <= 1) {	//balance factor에 따라 균형이 맞다면
		return now;	//현재 노드 그대도 반환
	}
	if (bFactor > 1) {	//balance factor가 1보다 크면
		if (GetBalance(now->left) > 0) now = LLrotate(now);	//LL회전이 필요한 형태이면 LLrotate 호출
		else now = LRrotate(now);	//LR회전이 필요한 형태이면 LRrotate 호출
	}
	if (bFactor < -1) {	//balance factor가 -1보다 작으면
		if (GetBalance(now->right) < 0) now = RRrotate(now);	//RR회전이 필요한 형태이면 RLrotate 호출
		else now = RLrotate(now);	//RL회전이 필요한 형태이면 RLrotate 호출
	}
	return now; //균형 조정에 따라 기존 now자리를 차지할 새로운 now 반환
}

void Deletion(Tree* tree, int element) {	//트리의 노드를 삭제하는 Deletion 함수 (tree: 트리, element: 삭제할 값)
	Node* parent = NULL;	//현재 가리키는 노드의 부모노드
	Node* now = tree->root;	//현재 가리키는 노드 (초기값은 트리의 루트)

	if (now == NULL) {	//맨 처음 노드가 없다면 (트리의 루트가 없음, 즉 트리에 노드가 하나도 없을 때)
		printf("Tree does not hava node...");
		return;	//함수 종료
	}

	while (now != NULL) {	//현재 가리키는 노드가 존재하면
		if (now->data == element) break;	//삭제할 노드를 발견했다면 루프 종료
		parent = now;	//부모노드를 지정해주고

		if (element < now->data) now = parent->left;	//값을 비교하여 좌측 차일드 혹은
		else now = parent->right;						//우측 차일드로 이동한다
	}

	if (now == NULL) {	//루프 종료 후에도 현재 가리키는 노드가 없다면
		printf("Can not find data to delete...\n");	//삭제할 값을 찾지 못한것
	}
	else {	//삭제할 노드를 찾았다면
		if (now->left == NULL && now->right == NULL) { //case 1: 그 노드가 리프노드일 때
			if (parent->left->data == element) {	//지정된 부모노드의 좌측 차일드가 삭제할 노드라면
				free(parent->left);					//데이터 할당 해제 후
				parent->left = NULL;				//해당 자리를 NULL로
			}
			else if (parent->right->data == element) {	//지정된 부모노드의 우측 차일드가 삭제할 노드라면
				free(parent->right);					//데이터 할당 해제 후
				parent->right = NULL;					//해당 자리를 NULL로
			}
		}
		else if (now->left != NULL && now->right == NULL) {	//case 2-1: 그 노드가 좌측 차일드만 가지고 있을 때
			Node* delChild = now->left;						//삭제할 노드의 좌측 차일드 주소를 저장해둔 뒤
			if (parent->left->data == element) {			//지정된 부모노드의 좌측 차일드가 삭제할 노드라면
				free(parent->left);							//데이터 할당 해제 후
				parent->left = delChild;					//저장해둔 좌측 차일드를 부모노드의 좌측 차일드로
			}
			else if (parent->right->data == element) {		//지정된 부모노드의 우측 차일드가 삭제할 노드라면
				free(parent->right);						//데이터 할당 해제 후
				parent->right = delChild;					//저장해둔 좌측 차일드를 부모노드의 우측 차일드로
			}
		}
		else if (now->left == NULL && now->right != NULL) {	//case 2-2: 그 노드가 우측 차일드만 가지고 있을 때
			Node* delChild = now->right;					//삭제할 노드의 우측 차일드 주소를 저장해둔 뒤
			if (parent->left->data == element) {			//지정된 부모노드의 좌측 차일드가 삭제할 노드라면
				free(parent->left);							//데이터 할당 해제 후
				parent->left = delChild;					//저장해둔 우측 차일드를 부모노드의 좌측 차일드로
			}
			else if (parent->right->data == element) {		//지정된 부모노드의 우측 차일드가 삭제할 노드라면
				free(parent->right);						//데이터 할당 해제 후
				parent->right = delChild;					//저장해둔 우측 차일드를 부모노드의 우측 차일드로
			}
		}
		else {												//case 3: 그 노드가 두 차일드를 가지고 있을 때
			Node* replace = findReplace(now);				//삭제한 후 자리를 대체할 노드를 찾는 함수 findReaplace 함수 호출
			now->data = replace->data;						//삭제하는 대신 현재 노드의 값을 대체할 노드의 값으로 바꾸고
			free(replace);									//대체할 노드를 삭제
		}
	}

	tree->root = Rebalance(tree->root);						//삭제 후에 트리 정렬
}

Node* findReplace(Node* now) {	//삭제할 노드를 대체할 노드를 찾는 함수, 대체할 노드는 삭제할 값보다 큰 것중 가장 작은것 (now: 현재 노드)	
	Node* parent = now;								//parent는 현재 노드
	Node* replace = now->right;						//replace는 현재 노드의 우측 차일드(우선 삭제할 값보다 큰 값에서 탐색)

	while (replace != NULL) {						//replace가 존재하면
		if (replace->left == NULL) break;			//replace의 좌측 차일드를 살핀 후 없다면 루프 종료 (현재 replace가 대체할 노드)

		parent = replace;							//replace를 parent가 가리키게 하고
		replace = parent->left;						//replace는 좌측 차일드로 (큰 값중에서 가장 작은 값을 찾아야 하므로)
	}

	if (parent == now) {							//parent가 함수 호출 때의 매개변수 now와 동일하다면
		parent->right = replace->right;				//parent의 우측 차일드가 now의 값을 대체하므로 parent의 우측 차일드는 이제
	}												//replace의 우측 차일드 
	else {											//parent가 함수 호출 떄의 매개변수 now와 동일하지 않다면
		parent->left = replace->right;				//parent의 좌측 차일드가 now의 값을 대체하므로 parent의 좌측 차일드는 이제
	}												//replace의 우측 차일드
	
	return replace;				//최종적으로 replace 노드 리턴
}

void Preorder(Node* now) {	//트리 전위 순회를 위한 Preorder 함수 (now: 현재 노드)
	if (now == NULL) return;	//현재 노드가 존재하지 않다면 순회 중단
	printf("%d ", now->data);	//방문한 노드의 값 출력
	Preorder(now->left);		//현재 노드의 좌측 노드에 재귀 호출
	Preorder(now->right);		//현재 노드의 우측 노드에 재귀 호출
}