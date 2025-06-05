#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tree node structure
typedef struct s_btree {
	struct s_btree *left;
	struct s_btree *right;
	void *item;
} t_btree;

// Create a new node
t_btree *btree_create_node(void *item) {
	t_btree *node = (t_btree *)malloc(sizeof(t_btree));
	if (node) {
		node->item = item;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

// Insert into binary search tree
void btree_insert_data(t_btree **root, void *item, int (*cmpf)(void *, void *)) {
	if (*root == NULL) {
		*root = btree_create_node(item);
	} else {
		if (cmpf(item, (*root)->item) < 0)
			btree_insert_data(&((*root)->left), item, cmpf);
		else
			btree_insert_data(&((*root)->right), item, cmpf);
	}
}

// Inorder traversal (Left, Root, Right)
void btree_apply_infix(t_btree *root, void (*applyf)(void *)) {
	if (root == NULL) return;
	btree_apply_infix(root->left, applyf);
	applyf(root->item);
	btree_apply_infix(root->right, applyf);
}

// Helper function to print a string item
void print_item(void *item) {
	printf("%s\n", (char *)item);
}

// Pretty print the tree structure (for debugging)
void btree_print(t_btree *root, int level) {
	if (root == NULL) return;
	btree_print(root->right, level + 1);
	for (int i = 0; i < level; i++) printf("    ");
	printf("%s\n", (char *)root->item);
	btree_print(root->left, level + 1);
}

// Free all nodes in the tree
void btree_free(t_btree *root) {
	if (root == NULL) return;
	btree_free(root->left);
	btree_free(root->right);
	free(root->item);  // only if item was dynamically allocated!
	free(root);
}

// void btree_apply_postfix(t_btree *root, void (*applyf)(void *)) {
// 	if (root == NULL) return;
// 	btree_apply_postfix(root->left, applyf);
// 	btree_apply_postfix(root->right, applyf);
// 	applyf(root->item);
// }

// void print_item_postorder(void *item) {
// 	printf("%s\n", (char *)item);
// }

// // Usage:
// btree_apply_postfix(root, print_item_postorder);


int main() {
	t_btree *root = NULL;

	// Insert some string items
	btree_insert_data(&root, "banana", (int (*)(void *, void *))strcmp);
	btree_insert_data(&root, "apple", (int (*)(void *, void *))strcmp);
	btree_insert_data(&root, "cherry", (int (*)(void *, void *))strcmp);
	btree_insert_data(&root, "grape", (int (*)(void *, void *))strcmp);
	btree_insert_data(&root, "date", (int (*)(void *, void *))strcmp);

	printf("Inorder traversal (sorted):\n");
	btree_apply_infix(root, print_item);

	printf("\nTree structure:\n");
	btree_print(root, 0);

	btree_free(root);
	return 0;
}

