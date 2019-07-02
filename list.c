#include "list.h"
#include "tree.h"

/*
This function receives a pointer to a List, allocates memory for the list and sets the head and tail of the List to NULL.
*/
void makeEmptyList(List **lst) {
	*lst = (List*)calloc(1, sizeof(List));
	(*lst)->head = (*lst)->tail = NULL;
}

/*
This function receives a List and returns whether the List is empty or not.
*/
int isEmpty(const List* lst) {
	return lst->head == NULL;
}

/*
This function receives parameters for a ListNode, creates a ListNode with the given parameters and returns the created ListNode.
*/
ListNode* createNewListNode(struct treeNode *data, ListNode *next) {
	ListNode *res;

	res = (ListNode*)calloc(1, sizeof(ListNode)); //Allocating memory for the ListNode.
	res->data = data;
	res->next = next;

	return res;
}

/*
This function receives a List and the data of a new TreeNode, the function then creates a new ListNode that contains a TreeNode with the given data
and adds the ListNode to the tail of the List.
*/
void addValueToTail(List *lst, TreeType data) {
	ListNode *lNode;
	TreeNode *tNode;

	tNode = createNewTreeNode(data);
	lNode = createNewListNode(tNode, NULL);

	addNodeToTail(lst, lNode);
}

/*
This function receives a List and a ListNode and adds the ListNode to the tail of the List.
*/
void addNodeToTail(List *lst, ListNode *node) {
	if (isEmpty(lst)) {
		lst->head = lst->tail = node;
	}
	else {
		lst->tail->next = node;
		lst->tail = node;
	}
}

/*
This function receives a List and returns the amount of nodes found in the List.
*/
int getListSize(List *lst) {
	ListNode *temp;
	int counter;

	temp = lst->head;
	counter = 0;

	while (temp) {
		counter++;
		temp = temp->next;
	}

	return counter;
}