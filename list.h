#ifndef _List_H
#define _List_H

#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

struct treeNode;
typedef const char* TreeType;

typedef struct listNode
{
	struct treeNode* data;
	struct listNode* next;
} ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
} List;

void makeEmptyList(List **lst);
int isEmpty(const List* lst);
ListNode* createNewListNode(struct treeNode *data, ListNode *next);
void addValueToTail(List *lst, TreeType data);
void addNodeToTail(List *lst, ListNode *node);
int getListSize(List *lst);

#endif // _List_H
