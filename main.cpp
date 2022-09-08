#include <iostream>
#include <vector>
using namespace std;

class BinaryTree {
public:
    int value;
    BinaryTree *left;
    BinaryTree *right;

    BinaryTree(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class TestBinaryTree : public BinaryTree {
public:
    explicit TestBinaryTree(int value) : BinaryTree(value){};

    BinaryTree *insert(vector<int> values, int i = 0) {
        if (i >= values.size())
            return nullptr;
        vector<BinaryTree *> queue = {this};
        while (!queue.empty()) {
            BinaryTree *current = queue[0];
            queue.erase(queue.begin());
            if (current->left == nullptr) {
                current->left = new BinaryTree(values[i]);
                break;
            }
            queue.push_back(current->left);
            if (current->right == nullptr) {
                current->right = new BinaryTree(values[i]);
                break;
            }
            queue.push_back(current->right);
        }
        insert(values, i + 1);
        return this;
    }
};

// O(n) time | O(n) space
void helperMethod(BinaryTree *node, vector<int> &sums, int runningSum) {
    if(node == nullptr) {
        return;
    }
    int newRunningSum = runningSum + node->value;
    if(node->left == nullptr && node->right == nullptr) {
        sums.push_back(newRunningSum);
        return;
    }
    helperMethod(node->left, sums, newRunningSum);// O(log(n)) time
    helperMethod(node->right, sums, newRunningSum);// O(log(n) time
}

// O(n) time | O(n) space
vector<int> branchSums(BinaryTree *root) {
    vector<int> sums;
    helperMethod(root, sums, 0);// O(n) time | O(n) space
    return sums;
}

int main() {
    auto *tree = new TestBinaryTree(1);
    tree->insert({2, 3, 4, 5, 6, 7, 8, 9, 10});
    vector<int> sums = branchSums(tree);
    for(int element : sums) {
        cout << element << " ";
    }
    return 0;
}
