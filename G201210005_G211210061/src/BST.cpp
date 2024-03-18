/**
 * @G201210005_G211210061
 * Seçilen maksimum yüksekliğe sahip ikili arama ağacı postorder okunup sayısal değerlerin ASCII karakter karşılıkları ekrana yazar.
 * odev2
 * 1.öğretim 2 A 
 * 30/07/2023
 * Tuğba Dirmenci Aslı Döngez
 * tugba.dirmenci@ogr.sakarya.edu.tr
 */

#include "BST.hpp"
#include <iostream>

BST::BST() {
    root = NULL;
}

void BST::insert(int data) {
    root = insertHelper(root, data);
}

int BST::height() {
    return heightHelper(root);
}

int BST::sum() {
    return sumHelper(root);
}

void BST::postorder() {
    postorderHelper(root);
    std::cout << std::endl;
}

BSTNode* BST::insertHelper(BSTNode* node, int data) {
    if (node == NULL) {
        node = new BSTNode;
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    else if (data < node->data) {
        node->left = insertHelper(node->left, data);
    }
    else if (data > node->data) {
        node->right = insertHelper(node->right, data);
    }
    return node;
}

int BST::heightHelper(BSTNode* node) {
    if (node == NULL) {
        return 0;
    }
    else {
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }
}

int BST::sumHelper(BSTNode* node) {
    if (node == NULL) {
        return 0;
    }
    else {
        int leftSum = sumHelper(node->left);
        int rightSum = sumHelper(node->right);
        return node->data + leftSum + rightSum;
    }
}

void BST::postorderHelper(BSTNode* node) {
    if (node != NULL) {
        postorderHelper(node->left);
        postorderHelper(node->right);
        std::cout << char(node->data) << " ";
    }
}
