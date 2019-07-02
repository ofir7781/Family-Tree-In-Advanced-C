#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "tree.h"

#define FALSE 0
#define TRUE 1

void main()
{
	{
		TreeNode* family = createNewTreeNode("a1");

		addSons(family, "a1", "b1", NULL);
		addSons(family, "a1", "b2", "b3", NULL);

		addSons(family, "b1", "c1", "c2", NULL);

		addSons(family, "b3", "d1", "d2", "d3", NULL);
		addSons(family, "b3", "d4", NULL);

		addSons(family, "d3", "e1", NULL);
		addSons(family, "e1", "f1", "f2", NULL);

		saveTreeToFile(family, "family.bin");

		printTree(family);

		printf("\nNum of nodes: %d\n", countNodes(family));
		printf("Num of nodes with sons: %d\n",
			countNodesIf(family, doesTreeNodeHasSons));

		freeTree(family, FALSE);
	}

	{
		TreeNode* family = loadTreeFromFile("family.bin");
		printf("\n");
		printTree(family);
		printf("\nNum of nodes: %d\n", countNodes(family));
		printf("Num of nodes with sons: %d\n",
			countNodesIf(family, doesTreeNodeHasSons));

		freeTree(family, TRUE); // need to free strings as well!
	}
}

