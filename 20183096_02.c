#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct node { 
	struct node* left;	//����� ���� ���ϵ�
	struct node* right;	//����� ���� ���ϵ�
	int data;	//��忡 ����� ��
} Node;

typedef struct tree {
	Node* root;	//Ʈ���� ��Ʈ ���
	int nodecnt;	//��ü ��� ��
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
	int ele;	//�Է¹��� ���� ������ ����
	Tree* tree = (Tree*)malloc(sizeof(Tree));	//Ʈ���� ������ �Ҵ�
	tree->root = NULL;	//Ʈ���� ��Ʈ ��� NULL�� �ʱ�ȭ
	tree->nodecnt = 0;	//Ʈ���� ��ü ��� �� 0���� �ʱ�ȭ
	printf("Insert node to AVL tree:\n");

	while (tree->nodecnt < 9) {	//9���� ��带 �޾Ƶ���
		scanf("%d", &ele);
		data[tree->nodecnt] = ele;
		Insert(tree, ele);	//Insert �Լ��� ���� �Է¹��� ���� Ʈ���� ����
	}
	
	printf("Preorder traversal of the constructed AVL tree is\n");
	//Preorder(tree->root);	������ ���⼭ ���ĵ� AVL Ʈ���� ���� ��ȸ�� �������ϳ� 
	for (int i = 0; i < 9; i++)		//������ ���� �����ϴ� ���¸� ���� �Է��� ������ �ѹ� �� ���
		printf("%d ", data[i]);
	printf("\nPreorder traversal after deletion of 10\n");
	Deletion(tree, 10);
	Preorder(tree->root);
	return 0;
}

void Insert(Tree* tree, int element) {	//��带 �����ϴ� Insert �Լ� (tree: Ʈ�� , element: �Է� ���� ��)
	Node* parent = NULL;	//�θ� ���, �θ����� ���� ���� ���ο� ��带 ����, ������ ������ �Ǵ��ؾ� �ϹǷ�
	Node* now = tree->root;	//���ο� ��带 ���� ��ġ�� �Ǵ��ϴ� ���, Ʈ���� ��Ʈ ������ ���캽

	while (now != NULL) {
		if (element == now->data) return;	//�Է¹��� ���� Ʈ���� �̹� �ִ� ���̶�� �Լ� ����(��� �߰� X)

		parent = now;	//�θ��忡 ���� ��� ��ġ�� ����Ű�� ��

		if (element < now->data) now = parent->left;	//���� ����� ������ ���� ���� �Է¹޾Ҵٸ� ���� ���� ���ϵ忡�� ���캸��
		else now = parent->right;	//���� ����� ������ ū ���� �Է¹޾Ҵٸ� ���� ���� ���ϵ忡�� ���캸��
	}

	Node* new = (Node*)malloc(sizeof(Node));	//���ο� ��� ������ �Ҵ�
	new->left = NULL;	//���ο� ����� ���� ���ϵ带 NULL�� �ʱ�ȭ
	new->right = NULL;	//���ο� ����� ���� ���ϵ带 NULL�� �ʱ�ȭ
	new->data = element;//���ο� ����� ���� �Է¹��� ��
	tree->nodecnt++;	//Ʈ���� ��ü ��� �� 1 ����

	if (parent == NULL)	//�θ��尡 NULL�� ��� (Ʈ���� ��Ʈ ����� ���)
		tree->root = new;	//���ο� ���� Ʈ���� ��Ʈ ���
	else {
		if (element < parent->data) parent->left = new;	//���� �θ����� ������ ������ ���ο� ���� �θ����� ���� ���ϵ�
		else parent->right = new;	//���� �θ����� ������ ũ�� ���ο� ���� �θ����� ���� ���ϵ�
	}
	
	tree->root = Rebalance(tree->root);	//Ʈ���� ��Ʈ ������ ������ ���߱� ���� Rebalance �Լ� ȣ��
}

int GetHeight(Node* now) {	//�� ����Ʈ���� ���̸� ��ȯ�ϴ� GetHeight �Լ� (now: ���� ���)
	if (now == NULL) return 0;	//���� ��尡 NULL�̸� �Լ� ����

	int leftH;	//���� ����Ʈ�� ����
	int rightH;	//���� ����Ʈ�� ����

	leftH = GetHeight(now->left);	//���� ����� ���� ���ϵ带 �������� ��� ȣ���� ���� ����
	rightH = GetHeight(now->right);	//���� ����� ���� ���ϵ带 �������� ��� ȣ���� ���� ����

	if (leftH > rightH) return leftH + 1;	//���� ����� ���� ����Ʈ���� �� ��ٸ� ���� ����Ʈ���� ���̸� 1 �߰�
	else return rightH + 1;	//���� ����� ���� ����Ʈ���� �� ��ٸ� ���� ����Ʈ���� ���̸� 1 �߰�
}

int GetBalance(Node* now) {	//��, ���� ����Ʈ���� ���̸� �Ǵ��ؼ� ������ ������ ��ȯ�ϴ� GetBalance �Լ� (now: ���� ���)
	if (now == NULL) return 0;	//���� ��尡 NULL�̸� �Լ� ����

	int leftH;	//���� ����Ʈ�� ����
	int rightH;	//���� ����Ʈ�� ����

	leftH = GetHeight(now->left);	//GetHeight �Լ��� ���� ���� ��� ���� ���� ����Ʈ�� ���̰� ����
	rightH = GetHeight(now->right);	//GetHeight �Լ��� ���� ���� ��� ���� ���� ����Ʈ�� ���̰� ����

	return leftH - rightH;	//����Ʈ�� ������ ���� ��ȯ (Balance factor)
}

Node* LLrotate(Node* parentNode) {	//LLȸ���� ���� LLrotate �Լ�(parentNode: Balance factor�� 2 �̻��� ���)
	Node* parent = parentNode;	//parent�� parentNode
	Node* now = parent->left;	//now�� parent�� ���� ���ϵ�

	parent->left = now->right;	//parent�� ���� ���ϵ带 now�� ���� ���ϵ��
	now->right = parent;	//now�� ���� ���ϵ带 parent��

	return now;	//parent�ڸ��� ���� now�� ����
}

Node* RRrotate(Node* parentNode) {	//RRȸ���� ���� RRrotate �Լ�(parentNode: Balance factor�� 2 �̻��� ���)
	Node* parent = parentNode;	//parent�� parentNode
	Node* now = parent->right;	//now�� parent�� ���� ���ϵ�

	parent->right = now->left;	//parent�� ���� ���ϵ带 now�� ���� ���ϵ��
	now->left = parent;	//now�� ���� ���ϵ带 parent��

	return now;	//parent�ڸ��� ���� now�� ����
}

Node* LRrotate(Node* parentNode) {	//LRȸ���� ���� LRrotate �Լ�(parentNode: Balance factor�� 2 �̻��� ���)
	Node* parent = parentNode;	//parent�� parentNode
	Node* now = parent->left;	//now�� parent�� ���� ���ϵ�
	Node* nowR = now->right;	//nowR�� now�� ���� ���ϵ�

	now->right = nowR->left;	//now�� ���� ���ϵ带 nowR�� ���� ���ϵ��
	nowR->left = now;	//nowR�� ���� ���ϵ带 now��

	parent->left = nowR->right;	//parent�� ���� ���ϵ带 nowR�� ���� ���ϵ��
	nowR->right = parent;	//nowR�� ���� ���ϵ带 parent��

	return nowR;	//parent�ڸ��� ���� nowR�� ����
}

Node* RLrotate(Node* parentNode) {	//RLȸ���� ���� RLrotate �Լ�(parentNode: Balance factor�� 2 �̻��� ���)
	Node* parent = parentNode;	//parent�� parentNode
	Node* now = parent->right;	//now�� parent�� ���� ���ϵ�
	Node* nowL = now->left;	//nowL�� now�� ���� ���ϵ�

	now->left = nowL->right;	//now�� ���� ���ϵ带 nowL�� ���� ���ϵ��
	nowL->right = now;	//nowL�� ���� ���ϵ带 now��

	parent->right = nowL->left;	//parent�� ���� ���ϵ带 nowL�� ���� ���ϵ��
	nowL->left = parent;	//nowL�� ���� ���ϵ带 parent��

	return nowL;	//parent�ڸ��� ���� nowL�� ����
}

Node* Rebalance(Node* now) {	//Ʈ���� ��ü ������ ������ Rebalance �Լ� (now: ���� ���)
	if (now == NULL) return NULL;	//���� ��尡 NULL�̸� ��ȯ�ϴ� ��� NULL

	now->left = Rebalance(now->left);	//���� ����� ���� ���ϵ带 �������� Rebalance ��� ȣ��
	now->right = Rebalance(now->right);	//���� ����� ���� ���ϵ带 �������� Rebalance ��� ȣ��
	int bFactor = GetBalance(now);	//GetBalance �Լ��� �̿��� ���� ��忡 ���� balance factor �޾ƿ�

	if (bFactor >= -1 && bFactor <= 1) {	//balance factor�� ���� ������ �´ٸ�
		return now;	//���� ��� �״뵵 ��ȯ
	}
	if (bFactor > 1) {	//balance factor�� 1���� ũ��
		if (GetBalance(now->left) > 0) now = LLrotate(now);	//LLȸ���� �ʿ��� �����̸� LLrotate ȣ��
		else now = LRrotate(now);	//LRȸ���� �ʿ��� �����̸� LRrotate ȣ��
	}
	if (bFactor < -1) {	//balance factor�� -1���� ������
		if (GetBalance(now->right) < 0) now = RRrotate(now);	//RRȸ���� �ʿ��� �����̸� RLrotate ȣ��
		else now = RLrotate(now);	//RLȸ���� �ʿ��� �����̸� RLrotate ȣ��
	}
	return now; //���� ������ ���� ���� now�ڸ��� ������ ���ο� now ��ȯ
}

void Deletion(Tree* tree, int element) {	//Ʈ���� ��带 �����ϴ� Deletion �Լ� (tree: Ʈ��, element: ������ ��)
	Node* parent = NULL;	//���� ����Ű�� ����� �θ���
	Node* now = tree->root;	//���� ����Ű�� ��� (�ʱⰪ�� Ʈ���� ��Ʈ)

	if (now == NULL) {	//�� ó�� ��尡 ���ٸ� (Ʈ���� ��Ʈ�� ����, �� Ʈ���� ��尡 �ϳ��� ���� ��)
		printf("Tree does not hava node...");
		return;	//�Լ� ����
	}

	while (now != NULL) {	//���� ����Ű�� ��尡 �����ϸ�
		if (now->data == element) break;	//������ ��带 �߰��ߴٸ� ���� ����
		parent = now;	//�θ��带 �������ְ�

		if (element < now->data) now = parent->left;	//���� ���Ͽ� ���� ���ϵ� Ȥ��
		else now = parent->right;						//���� ���ϵ�� �̵��Ѵ�
	}

	if (now == NULL) {	//���� ���� �Ŀ��� ���� ����Ű�� ��尡 ���ٸ�
		printf("Can not find data to delete...\n");	//������ ���� ã�� ���Ѱ�
	}
	else {	//������ ��带 ã�Ҵٸ�
		if (now->left == NULL && now->right == NULL) { //case 1: �� ��尡 ��������� ��
			if (parent->left->data == element) {	//������ �θ����� ���� ���ϵ尡 ������ �����
				free(parent->left);					//������ �Ҵ� ���� ��
				parent->left = NULL;				//�ش� �ڸ��� NULL��
			}
			else if (parent->right->data == element) {	//������ �θ����� ���� ���ϵ尡 ������ �����
				free(parent->right);					//������ �Ҵ� ���� ��
				parent->right = NULL;					//�ش� �ڸ��� NULL��
			}
		}
		else if (now->left != NULL && now->right == NULL) {	//case 2-1: �� ��尡 ���� ���ϵ常 ������ ���� ��
			Node* delChild = now->left;						//������ ����� ���� ���ϵ� �ּҸ� �����ص� ��
			if (parent->left->data == element) {			//������ �θ����� ���� ���ϵ尡 ������ �����
				free(parent->left);							//������ �Ҵ� ���� ��
				parent->left = delChild;					//�����ص� ���� ���ϵ带 �θ����� ���� ���ϵ��
			}
			else if (parent->right->data == element) {		//������ �θ����� ���� ���ϵ尡 ������ �����
				free(parent->right);						//������ �Ҵ� ���� ��
				parent->right = delChild;					//�����ص� ���� ���ϵ带 �θ����� ���� ���ϵ��
			}
		}
		else if (now->left == NULL && now->right != NULL) {	//case 2-2: �� ��尡 ���� ���ϵ常 ������ ���� ��
			Node* delChild = now->right;					//������ ����� ���� ���ϵ� �ּҸ� �����ص� ��
			if (parent->left->data == element) {			//������ �θ����� ���� ���ϵ尡 ������ �����
				free(parent->left);							//������ �Ҵ� ���� ��
				parent->left = delChild;					//�����ص� ���� ���ϵ带 �θ����� ���� ���ϵ��
			}
			else if (parent->right->data == element) {		//������ �θ����� ���� ���ϵ尡 ������ �����
				free(parent->right);						//������ �Ҵ� ���� ��
				parent->right = delChild;					//�����ص� ���� ���ϵ带 �θ����� ���� ���ϵ��
			}
		}
		else {												//case 3: �� ��尡 �� ���ϵ带 ������ ���� ��
			Node* replace = findReplace(now);				//������ �� �ڸ��� ��ü�� ��带 ã�� �Լ� findReaplace �Լ� ȣ��
			now->data = replace->data;						//�����ϴ� ��� ���� ����� ���� ��ü�� ����� ������ �ٲٰ�
			free(replace);									//��ü�� ��带 ����
		}
	}

	tree->root = Rebalance(tree->root);						//���� �Ŀ� Ʈ�� ����
}

Node* findReplace(Node* now) {	//������ ��带 ��ü�� ��带 ã�� �Լ�, ��ü�� ���� ������ ������ ū ���� ���� ������ (now: ���� ���)	
	Node* parent = now;								//parent�� ���� ���
	Node* replace = now->right;						//replace�� ���� ����� ���� ���ϵ�(�켱 ������ ������ ū ������ Ž��)

	while (replace != NULL) {						//replace�� �����ϸ�
		if (replace->left == NULL) break;			//replace�� ���� ���ϵ带 ���� �� ���ٸ� ���� ���� (���� replace�� ��ü�� ���)

		parent = replace;							//replace�� parent�� ����Ű�� �ϰ�
		replace = parent->left;						//replace�� ���� ���ϵ�� (ū ���߿��� ���� ���� ���� ã�ƾ� �ϹǷ�)
	}

	if (parent == now) {							//parent�� �Լ� ȣ�� ���� �Ű����� now�� �����ϴٸ�
		parent->right = replace->right;				//parent�� ���� ���ϵ尡 now�� ���� ��ü�ϹǷ� parent�� ���� ���ϵ�� ����
	}												//replace�� ���� ���ϵ� 
	else {											//parent�� �Լ� ȣ�� ���� �Ű����� now�� �������� �ʴٸ�
		parent->left = replace->right;				//parent�� ���� ���ϵ尡 now�� ���� ��ü�ϹǷ� parent�� ���� ���ϵ�� ����
	}												//replace�� ���� ���ϵ�
	
	return replace;				//���������� replace ��� ����
}

void Preorder(Node* now) {	//Ʈ�� ���� ��ȸ�� ���� Preorder �Լ� (now: ���� ���)
	if (now == NULL) return;	//���� ��尡 �������� �ʴٸ� ��ȸ �ߴ�
	printf("%d ", now->data);	//�湮�� ����� �� ���
	Preorder(now->left);		//���� ����� ���� ��忡 ��� ȣ��
	Preorder(now->right);		//���� ����� ���� ��忡 ��� ȣ��
}