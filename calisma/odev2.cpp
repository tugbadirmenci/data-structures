#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <sstream>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};


void insertInBST(TreeNode*& root, int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
        return;
    }

    if (value < root->data) {
        insertInBST(root->left, value);
    } else if (value > root->data) {
        insertInBST(root->right, value);
    }
}

int getHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

int getSum(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->data + getSum(root->left) + getSum(root->right);
}

void postorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    char asciiValue = static_cast<char>(root->data % 128); // ASCII karakter sınırlarını aşmamak için % 128 ekliyoruz.
    std::cout << asciiValue;
}


int main() {
    std::ifstream file("Sayilar.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::stack<int> stack;
        std::vector<TreeNode*> trees;

        int max_height = 0;
        int max_sum = 0;
        TreeNode* selected_tree = nullptr;

        // Satırdaki sayıları yığıta ekleyin
        std::istringstream iss(line); // <--- istringstream için gerekli tanımlama
        int number;
        while (iss >> number) {
            if (stack.empty() || number > stack.top()) {
                stack.push(number);
            } else {
                // Yığıtta en büyük sayıyı bulduk, yeni ağaç oluşturup yığıttaki sayıları ekleyelim
                TreeNode* root = nullptr;
                while (!stack.empty()) {
                    insertInBST(root, stack.top());
                    stack.pop();
                }
                trees.push_back(root);

                // Ağacın yüksekliğini ve toplam değerini hesaplayalım
                int height = getHeight(root);
                int sum = getSum(root);

                // En uygun ağacı seçelim
                if (height > max_height || (height == max_height && sum > max_sum)) {
                    max_height = height;
                    max_sum = sum;
                    selected_tree = root;
                }
            }
        }

        // Eğer yığıtta kalan sayılar varsa, onları da ağaçlara ekleyelim
        if (!stack.empty()) {
            TreeNode* root = nullptr;
            while (!stack.empty()) {
                insertInBST(root, stack.top());
                stack.pop();
            }
            trees.push_back(root);

            // Ağacın yüksekliğini ve toplam değerini hesaplayalım
            int height = getHeight(root);
            int sum = getSum(root);

            // En uygun ağacı seçelim
            if (height > max_height || (height == max_height && sum > max_sum)) {
                max_height = height;
                max_sum = sum;
                selected_tree = root;
            }
        }

        // Seçilen ağacı postorder olarak yazdıralım
        postorderTraversal(selected_tree);
        std::cout << std::endl;

        // Her satır için 10 milisaniye bekleyelim
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // Ağaçları temizleyelim
        for (TreeNode* tree : trees) {
            delete tree;
        }
    }

    return 0;
}
