#include <iostream>
#include <memory>
#include <queue>

struct TreeNode {
    int val;
    std::shared_ptr<TreeNode> left, right;
    TreeNode(int v, const std::shared_ptr<TreeNode> & lchild = nullptr, const std::shared_ptr<TreeNode> & rchild = nullptr)
        : val(v), left(lchild), right(rchild) {}
};

using pNode = std::shared_ptr<TreeNode>;

class BSTIterator {
  public:
    BSTIterator(const pNode & rootNode)
        : root(rootNode)
    {
        curr = root;
        while (curr->left != nullptr)
            curr = curr->left;
    }

    bool hasNext() {
        return curr != nullptr;
    }

    int next() {
        if (curr != nullptr) {
            int rtn = curr->val;
            curr = inorderNext(root, curr);
            return rtn;
        }
    }

  private:
    pNode root;
    pNode curr;

    pNode inorderNext(const pNode & rNode, const pNode & currNode) {
        pNode next = nullptr;
        if (currNode->right != nullptr) {
            next = currNode->right;
            while (next->left != nullptr)
                next = next->left;
        }
        else {
            pNode parent = getParent(rNode, currNode);
            if (currNode == parent->left)
                next = parent;
            else {
                pNode grandparent = getParent(rNode, parent);
                while (grandparent != nullptr && parent == grandparent->right)
                {
                    parent = grandparent;
                    grandparent = getParent(rNode, parent);
                }
                next = grandparent;
            }
        }
        return next;
    }

    pNode getParent(const pNode & rootnode, const pNode & currnode) {
        std::queue<pNode> qu;
        qu.push(rootnode);
        while (!qu.empty()) {
            auto p = qu.front();
            qu.pop();
            if (p != nullptr) {
                if (p->left == currnode || p->right == currnode)
                    return p;
                else {
                    qu.push(p->left);
                    qu.push(p->right);
                }
            }
        }
        return nullptr;
    }
};

void inorder(const pNode & root) {
    if (root != nullptr) {
        inorder(root->left);
        std::cout << root->val << " ";
        inorder(root->right);
    }
}

int main() {
    pNode root = std::make_shared<TreeNode>(5);
    root->left = std::make_shared<TreeNode>(3);
    root->left->left = std::make_shared<TreeNode>(2);
    root->left->right = std::make_shared<TreeNode>(4);
    root->right = std::make_shared<TreeNode>(7);
    root->right->left = std::make_shared<TreeNode>(6);
    root->right->right = std::make_shared<TreeNode>(8);

    std::cout << "Recursive inorder:\n";
    inorder(root);

    BSTIterator it(root);
    std::cout << "\nIterative inorder:\n";
    while (it.hasNext())
        std::cout << it.next() << " ";
    std::cout << std::endl;
}
