#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int MAX = 1000000;

int check[1000000] = { 0, };

typedef struct node{
	int data;
	struct node *left;
	struct node *right;
}Node;
 
Node* newNode(int data){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

Node* constructTreeUtil(int *pre, int* preIndex, int low, int high, int size){
	  
	if (*preIndex >= size || low > high)
		return NULL;

	Node* root = newNode(pre[*preIndex]);
	*preIndex = *preIndex + 1;

  
	if (low == high)
		return root;

  
	int i;
	for (i = low; i <= high; ++i)
		if (pre[i] > root->data)
			break;

 
	root->left = constructTreeUtil(pre, preIndex, *preIndex, i - 1, size);
	root->right = constructTreeUtil(pre, preIndex, i, high, size);

	return root;
}
 
Node *constructTree(int pre[], int size){
	int preIndex = 0;
	return constructTreeUtil(pre, &preIndex, 0, size - 1, size);
}

 
void printInorder(Node* node){
	if (node == NULL)
		return;
	printInorder(node->left);

	printf("%d ", node->data);

	printInorder(node->right);
}

void printPostorder(Node* node) {

	if (node == NULL)
		return;
	printPostorder(node->left);

	printPostorder(node->right);

	printf("%d ",node->data);
}

 
int main(){
	int n;
	scanf("%d", &n);
	int* pre = (int*)malloc(n * sizeof(int));
	int size = n;
	for (int i = 0; i < n; i++) {
		scanf("%d", &pre[i]);
		if (!check[pre[i]]) check[pre[i]] = 1;
		else {

			printf("cannot construct BST\n");
			return 0;

		}
	}
	Node *root = constructTree(pre, size);

	printf("Inorder: ");
	printInorder(root);
	printf("\n");
	printf("Postorder: ");
	printPostorder(root);
	free(pre);
	return 0;
}
