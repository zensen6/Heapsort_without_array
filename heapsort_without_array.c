#include<stdio.h>
#include<stdlib.h>
#define MIN -1000000000

int count = 0;
int last;
int existflag = 0;


typedef struct node {

	int key;
	struct node* parent;
	struct node* leftChild;
	struct node* rightChild;

}Node;



typedef struct Node *treePointer;



Node* root;

Node* searching;



void swap(Node* a, Node* b) {



	int tmp = a->key;

	a->key = b->key;

	b->key = tmp;

	return;



}



void init() {



	root = (Node*)malloc(sizeof(Node));

	root->key = MIN;

	root->leftChild = NULL;

	root->rightChild = NULL;

	root->parent = NULL;

}



int maximun(int a, int b) {

	return a > b ? a : b;

}



int smallbin(int x) {



	int sum = 0;

	int i = 1;

	while (sum <= x) {

		sum += i;
		i = i << 1;
	}

	return sum - (i >> 1);

}



int largebin(int x) {



	int sum = 0;

	int i = 1;

	while (sum < x) {

		sum += i;

		i = i << 1;
	}

	return sum;

}



void insertion(int key) {

	if (count==0) {

		root->key = key;
		count = 1;
		return;

	}

	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->leftChild = NULL;
	node->rightChild = NULL;
	node->parent = NULL;
	count += 1;
	Node* search = root;
	Node* cur = root;
	int start = smallbin(count - 1) + 1;
	int end = largebin(count);

	while (start <= end) {
		int mid = (start + end) / 2;

		if (count <= mid) {

			if (cur->leftChild == NULL) {

				cur->leftChild = node;
				node->parent = cur;
				search = node;
				break;
			}

			else cur = cur->leftChild;

			end = mid - 1;

		}

		else {

			if (cur->rightChild == NULL) {

				cur->rightChild = node;
				node->parent = cur;
				search = node;
				break;

			}

			else cur = cur->rightChild;
			start = mid + 1;

		}

	}

	//printf("%d\n", search->parent->key);
	
	while (search->parent != NULL) {

		if (search->key > search->parent->key) {

			swap(search, search->parent);

			search = search->parent;
		}
		else {
			break;

		}
	}
	
	return;

}



void search() {

	searching = root;
	int start = smallbin(count - 1) + 1;
	int end = largebin(count);

	while (start <= end) {

		int mid = (start + end) / 2;

		if (count <= mid) {

			searching = searching->leftChild;
			if (searching->leftChild == NULL && searching->rightChild == NULL) break;
			end = mid - 1;

		}

		else {

			searching = searching->rightChild;
			if (searching->leftChild == NULL && searching->rightChild == NULL) break;
			start = mid + 1;
		}


	}

}



int deletion() {

	if (count==0) {

		return -1;
	}

	int rootnum = root->key;

	if (count == 1) {

		count = 0;
		root->key = MIN;
		return rootnum;

	}

	Node* cur;
	search();
	cur = searching;
	last = cur->key;

	if (last == cur->parent->leftChild->key) {

		cur->parent->leftChild = NULL;

	}

	else {

		cur->parent->rightChild = NULL;

	}

	free(cur);

	count--;
	root->key = last;
	Node* pcur = root;

	while (!(pcur->leftChild == NULL && pcur->rightChild == NULL)) {

		if (pcur->leftChild != NULL && pcur->leftChild->key > pcur->key) {

			if (pcur->rightChild != NULL && pcur->leftChild->key > pcur->rightChild->key) {

				swap(pcur, pcur->leftChild);
				pcur = pcur->leftChild;

			}

			else if (pcur->rightChild != NULL && pcur->leftChild->key < pcur->rightChild->key) {

				swap(pcur, pcur->rightChild);
				pcur = pcur->rightChild;
			}

			else {

				swap(pcur, pcur->leftChild);
				pcur = pcur->leftChild;
			}

		}

		else if (pcur->rightChild != NULL && pcur->rightChild->key > pcur->key) {

			if (pcur->leftChild != NULL && pcur->leftChild->key < pcur->rightChild->key) {

				swap(pcur, pcur->rightChild);
				pcur = pcur->rightChild;

			}

			else if (pcur->leftChild != NULL && pcur->leftChild->key > pcur->rightChild->key) {

				swap(pcur, pcur->leftChild);
				pcur = pcur->leftChild;
			}

			else {

				swap(pcur, pcur->rightChild);
				pcur = pcur->rightChild;
			}

		}

		else break;
	}
	return rootnum;
}



void printing(Node* rt) {

	if (rt == NULL) return;
	printing(rt->leftChild);
	printf("%d ", rt->key);
	printing(rt->rightChild);
}



int existnumber(int num, Node* rt) {

	if (rt == NULL) return;
	if (num == rt->key) {

		printf("Exist number\n");
		existflag = 1;
		return;

	}

	else {

		existnumber(num, rt->leftChild);
		existnumber(num, rt->rightChild);
	}

}



int main() {

	init();
	
	char c;
	int d;
	do {
		existflag = 0;
		scanf("%c", &c);
		if (c == 'i') {
			//getchar();

			scanf("%d", &d);
			existnumber(d, root);
			if (existflag) {}

			else {

				printf("Insert %d\n", d);

				insertion(d);

			}

		}

		else if (c == 'd') {
			getchar();

			if (root->key == MIN) {

				printf("The heap is empty\n");
			}

			else printf("Delete %d\n", deletion());
		}

	} while (c != 'q');
	

	return 0;

}

