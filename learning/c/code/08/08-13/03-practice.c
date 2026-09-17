/*
请编写一个函数，计算二叉树的深度（高度）。函数的输入参数是struct TreeNode* root，其中struct TreeNode是二叉树节点的定义。函数的返回值是二叉树的深度（高度）。


*/
#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void prePrintfTree(struct TreeNode *root){
    if(NULL == root) return;
    printf("%d", root->val);
    prePrintfTree(root->left);
    prePrintfTree(root->right);
    return ;
}

int main(){
    struct TreeNode root;
    root.val = 0;
    struct TreeNode node_1;
    node_1.val = 1;
    struct TreeNode node_2;
    node_2.val = 2;
    root.left = &node_1;
    root.right = &node_2;
    node_2.left = NULL;
    node_2.right = NULL;
    struct TreeNode node_1_1;
    node_1_1.val = 3;
    struct TreeNode node_1_2;
    node_1_2.val = 4;
    node_1.left = &node_1_1;
    node_1.right = &node_1_2;
    node_1_1.right = NULL;
    node_1_1.left = NULL;
    node_1_2.left = NULL;
    node_1_2.right = NULL;
    prePrintfTree(&root);
    return 0;
}