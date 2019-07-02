#include "list.h"
#include "tree.h"

// this function creates a root in our family tree
TreeNode* createNewTreeNode(TreeType name) {
	TreeNode* newTreeNode;
	int len;

	newTreeNode = (TreeNode*)calloc(1, sizeof(TreeNode));

	len = strlen(name) + 1;

	newTreeNode->data = (char*)calloc((len + 1), sizeof(char));
	strcpy((char*)newTreeNode->data, (char*)name);
	makeEmptyList(&newTreeNode->sons);

	return newTreeNode;
}

// this recursive function gets a root of a tree and print all the children and the nodes of the root 
void printTree(TreeNode* tr) {
	ListNode* curr;

	// if the root is null, dont do nothing
	if (tr == NULL)
	{
		return;
	}

	if (isEmpty(tr->sons)) // if we have only a name of root withoit chidren
		printf("%s: [] ", tr->data);
	else // if we have a root with children
	{
        curr = tr->sons->head;
		printf("%s: [", tr->data);

		while (curr) // go over all the children
		{
			printTree(curr->data);
			curr = curr->next;
		}

		printf(" ] ");
	}
}

// this functiom free the used memroy of our family tree
void freeTree(TreeNode* tr, BOOL trueOrFalse) {
	ListNode* curr, *tmp;

	// if the root is null, dont do nothing
	if (tr == NULL)
	{
		return;
	}

	curr = tr->sons->head; // the adress of the first son
	tmp = curr;

	while (curr)
	{
		if (!(isEmpty(curr->data->sons))) // if the List of the of the sons of the son's root is not empty, get in.
		{
			tmp = curr->next; // save the adress of the next son
			freeTree(curr->data, trueOrFalse);
			free(curr);
			curr = tmp;
		}
		else
		{
			if (trueOrFalse == TRUE) // check if we need to relise name memory or not
				free((char*)curr->data->data);

			tmp = curr->next;
			free(curr->data);
			free(curr);
			curr = tmp;
		}
	}

	// free memory of the root.
	if (trueOrFalse == TRUE)
		free((char*)tr->data);

	free(tr->sons);
	free(tr);
}

// this function counts all the nodes in the family tree we have build
int countNodes(TreeNode* family) {
	ListNode* curr;
	int countNodesOfFamily;

	if (family == NULL)
		return 0;
    else
	{
		countNodesOfFamily = 1;
		curr = family->sons->head;

		while (curr)
		{
			countNodesOfFamily = countNodesOfFamily + countNodes(curr->data); //add to the current node all the nodes in his sub tree
			curr = curr->next;
		}
	}

	return countNodesOfFamily;
}

/*
This function receives the head of a family tree, a parent name and a list of sons.
The function finds the parent in the family and adds the given sons to the parent.
*/
void addSons(TreeNode *family, char *parentName, ...) {
	TreeNode *parent;
	char *currentSon;
	va_list argsList;

	va_start(argsList, parentName); //Fetching the arguments after the parentName argument.

	currentSon = va_arg(argsList, char*); //Getting the first son after the parentName argument.
	parent = findNodeByTreeType(family, (TreeType)parentName); //Finding the parent's TreeNode in the family tree.

	while (currentSon != NULL && parent != NULL) { //Looping through the arguments until we reached a NULL.
		if (parent->sons == NULL) { //If the parent doesn't have any sons we should allocate memory for its List of sons
			makeEmptyList(&parent->sons);
		}

		addValueToTail(parent->sons, (TreeType)currentSon); //Adding the current son to the parent's sons list.

		currentSon = va_arg(argsList, char*); //Getting the next son from the given arguments.
	}

	va_end(argsList);
}

/*
This function receives a the head of a family tree and TreeType data.
The function scans the tree for a node that contains the given data and returns that node.
*/
TreeNode* findNodeByTreeType(TreeNode *family, TreeType data) {
	TreeNode *foundNode;
	ListNode *temp;

	if (strcmp((char*)family->data, (char*)data) == 0) { //If the family node contains the given data, then we should return the family node.
		return family;
	}

	temp = family->sons->head;
	foundNode = NULL;

	while (temp && foundNode == NULL) {
		foundNode = findNodeByTreeType(temp->data, data); //Checking if the node we are looking for is in the next son of the family's node.
		temp = temp->next; //Moving to the next son in the sons list.
	}

	return foundNode;
}

/*
This function receives a TreeNode and returns whether the node has sons.
*/
BOOL doesTreeNodeHasSons(TreeNode *parent) {
	if (parent->sons == NULL || isEmpty(parent->sons)) {
		return FALSE;
	}

	return TRUE;
}

/*
This function receives a family tree and a condition function.
The function returns the amount of nodes that meet the supplied condition function.
*/
int countNodesIf(TreeNode *family, BOOL(*condFunc)(TreeNode*)) {
	ListNode *tempLNode;
	int counter = 0;

	if (!family) { //If the family tree is NULL then there are 0 nodes that meet the condition function.
		return 0;
	}

	if (condFunc(family)) { //If the root of the tree meets the condition function, we should increase the counter.
		counter++;
	}

	tempLNode = family->sons->head;

	while (tempLNode) { //Looping through the children of the given tree and scanning for more nodes that meet the condition function.
		counter += countNodesIf(tempLNode->data, condFunc);
		tempLNode = tempLNode->next;
	}

	return counter;
}

/*
This function receives a family tree and a file name, the function then saves the family tree into the file.
*/
void saveTreeToFile(TreeNode *family, char *fileName) {
	FILE *file;

	file = fopen(fileName, "wb"); //Opening the file for binary writing.

	if (!file) {
		printf("Could not open the file for writing.\n");
		return;
	}

	saveTreeToFileRec(family, file); //Calling the recursive function which saves the data from the family tree into the file.

	fclose(file);
}

/*
This function receives a family tree and a file, the function then saves the family tree into the file.
*/
void saveTreeToFileRec(TreeNode *family, FILE *file) {
	ListNode *sonLNode;
	int dataLength;
	int sonsAmount;

	sonLNode = family->sons->head; //Getting the first son in the family's sons list.
	dataLength = strlen((char*)family->data); //Getting the length of the data's string.
	sonsAmount = getListSize(family->sons); //Getting the amount of sons the current parent has.

	fwrite(&dataLength, sizeof(int), 1, file); //Writing the length of the data's string to the file.
	fwrite((char*)family->data, sizeof(char), dataLength, file); //Writing the data's string to the file.
	fwrite(&sonsAmount, sizeof(int), 1, file); //Writing the amount of sons the parent has to the file.

	while (sonLNode) { //Saving each son the parent has to the file.
		saveTreeToFileRec(sonLNode->data, file);
		sonLNode = sonLNode->next;
	}
}

/*
This function receives a file name, and the function load the family tree from the file.
*/
TreeNode* loadTreeFromFile(char* fileName)
{
	FILE *file;
	TreeNode* tr;

	file = fopen(fileName, "rb"); //Opening the file for binary reading.

	if (!file) {
		printf("Could not open the file for reading.\n");
		return NULL;
	}

	tr = loadTreeFromFileRec(file); //Calling the recursive function which loading the data from the file to the family tree.
	
	fclose(file);

	return tr;
}

/*
This recursive function receives a file, and the function then loads the family tree from the file.
*/
TreeNode* loadTreeFromFileRec(FILE *file)
{
	TreeNode* tr;
	char *name;
	ListNode* tmp;
	int nameLength, numberOfSons, i;

	tr = (TreeNode*)calloc(1, sizeof(TreeNode)); // Dynamic allocation for the person in our tree.

	fread(&nameLength, sizeof(int), 1, file); // Getting the length of the data's string, not include '\0'.
	
	if(feof(file)){
		return NULL;
	}
	
	name = (char*)malloc((nameLength + 1) * sizeof(char)); // Dynamic allocation of the data's string, include '\0' in the end.
	fread(name, sizeof(char), nameLength, file);// get the data string from the file.
	name[nameLength] = '\0';
	tr->data = name;

	fread(&numberOfSons, sizeof(int), 1, file); // Getting the amount of sons the current parent has.
	makeEmptyList(&(tr->sons)); // make an empty list and prepare for getting the sons.
	if (numberOfSons == 0)
		return tr;

	for (i = 0; i < numberOfSons; i++) // this look goes every child and put him in the list of sons
	{
		tmp = (ListNode*)calloc(1, sizeof(ListNode));
		tmp->data = loadTreeFromFileRec(file);
		addNodeToTail(tr->sons, tmp);
	}

	return tr;

}