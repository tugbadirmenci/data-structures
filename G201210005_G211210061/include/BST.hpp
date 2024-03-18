#ifndef BST_HPP
#define BST_HPP

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
};

class BST {
public:
    BSTNode* root;

    BST();
    void insert(int data);
    int height();
    int sum();
    void postorder();

private:
    BSTNode* insertHelper(BSTNode* node, int data);
    int heightHelper(BSTNode* node);
    int sumHelper(BSTNode* node);
    void postorderHelper(BSTNode* node);
};

#endif // BST_HPP
