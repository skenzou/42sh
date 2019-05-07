#include <stdio.h>
#include <stdlib.h>
#include <string.h>



t_ast *newNode(t_token *item) 
{ 
	t_ast *temp =  (t_ast *)malloc(sizeof(t_ast)); 
	if (item)
		temp->val = item;
	else
		temp->val = NULL;
	temp->left = temp->right = NULL; 
	return temp;
}




void inorder(t_ast *root) 
{ 
	if (root != NULL) 
	{ 
		inorder(root->left);
		printf("%s \n", root->val);
		inorder(root->right);
	} 
}



t_ast *insert(t_ast *node, void *val) 
{
	if (node == NULL) 
		return newNode(val);
	if (val < node->val)
		node->left  = insert(node->left, val);
	else if (val > node->val)
		node->right = insert(node->right, val);
	return node;
}




int main()
{
	t_ast *tree = NULL;;
	
	tree = insert(tree,"hello");
	insert(tree,"Mac");
	insert(tree,"bob");
	insert(tree,"jole");
	insert(tree,"jame");
	inorder(tree);

	return 0;
}
