#ifndef _Tree_H
#define _Tree_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

struct list;

typedef const char* TreeType;
typedef int BOOL;

typedef struct treeNode
{
	TreeType data;
	struct list* sons;
} TreeNode;

TreeNode* createNewTreeNode(TreeType name);
void printTree(TreeNode* tr);
void freeTree(TreeNode* tr, BOOL trueOrFalse);
int countNodes(TreeNode* family);
void addSons(TreeNode *family, char *parentName, ...);
TreeNode* findNodeByTreeType(TreeNode *family, TreeType data);
BOOL doesTreeNodeHasSons(TreeNode *parent);
int countNodesIf(TreeNode *family, BOOL(*condFunc)(TreeNode*));
void saveTreeToFile(TreeNode *family, char *fileName);
void saveTreeToFileRec(TreeNode *family, FILE *file);
TreeNode* loadTreeFromFile(char* fileName);
TreeNode* loadTreeFromFileRec(FILE* file);

#endif // _Tree_H
