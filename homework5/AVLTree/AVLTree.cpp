#include "AVLTree.h"

int AVLTree::Height(AVLNode *node) {
    if (node == nullptr)
        return 0;
    return node->Height;
}

int AVLTree::BalanceFactor(AVLNode *node) {
    if (node == nullptr)
        return 0;
    return Height(node->Left) - Height(node->Right);
}

AVLNode *AVLTree::RightRotate(AVLNode *node) {
    AVLNode *leftNode = node->Left;
    AVLNode *T2 = leftNode->Right;

    leftNode->Right = node;
    node->Left = T2;

    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1;
    leftNode->Height =
        std::max(Height(leftNode->Left), Height(leftNode->Right)) + 1;

    return leftNode;
}

AVLNode *AVLTree::LeftRotate(AVLNode *node) {
    AVLNode *rightChild = node->Right;
    AVLNode *T2 = rightChild->Left;

    rightChild->Left = node;
    node->Right = T2;

    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1;
    rightChild->Height =
        std::max(Height(rightChild->Left), Height(rightChild->Right)) + 1;

    return rightChild;
}

AVLNode *AVLTree::Insert(AVLNode *node, int key) {
    if (node == nullptr) {
        return new AVLNode(key);
    }
    if (key < node->Value) {
        node->Left = Insert(node->Left, key);
    }
    else if (key > node->Value) {
        node->Right = Insert(node->Right, key);
    }
    else {
        return node;
    }

    node->Height = 1 + std::max(Height(node->Left), Height(node->Right));

    int balance = BalanceFactor(node);

    if (balance > 1 && key < node->Left->Value) {
        return RightRotate(node);
    }

    if (balance < -1 && key > node->Right->Value) {
        return LeftRotate(node);
    }

    if (balance > 1 && key > node->Left->Value) {
        node->Left = LeftRotate(node->Left);
        return RightRotate(node);
    }

    if (balance < -1 && key < node->Right->Value) {
        node->Right = RightRotate(node->Right);
        return LeftRotate(node);
    }
    return node;
}
void AVLTree::PrintHelper(AVLNode *root, std::string indent, bool last) {
    if (root != nullptr) {

        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        }
        else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->Value << "(" << root->Height << ")" << std::endl;
        PrintHelper(root->Left, indent, false);
        PrintHelper(root->Right, indent, true);
    }
}
void AVLTree::Print() {
    if (root == nullptr) {
        std::cout << "Дерево пустое." << std::endl;
    }
    else {
        std::cout << "AVL дерево:" << std::endl;
        PrintHelper(root, "", true);
    }
}

AVLNode *AVLTree::MinValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current->Left != nullptr)
        current = current->Left;
    return current;
}

AVLNode *AVLTree::DeleteNode(AVLNode *node, int key) {
    // Perform standard BST delete
    if (node == nullptr)
	{
		return node;
	}

    if (key < node->Value)
	{
		node->Left = DeleteNode(node->Left, key);
	}
    else if (key > node->Value)
	{
		node->Right = DeleteNode(node->Right, key);
	}
    else {
        // Node with only one child or no child
        if ((node->Left == nullptr) || (node->Right == nullptr)) {
            AVLNode *temp = node->Left ? node->Left : node->Right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else
                *node = *temp;
            delete temp;
        }
        else {

            AVLNode *temp = MinValueNode(node->Right);
            node->Value = temp->Value;
            node->Right = DeleteNode(node->Right, temp->Value);
        }
    }

    if (node == nullptr)
	{
		return node;
	}

    // Update height of the current node
    node->Height = 1 + std::max(Height(node->Left), Height(node->Right));

    // Get the balance factor of this node
    int balance = BalanceFactor(node);

    // If this node becomes unbalanced, then there are 4
    // cases

    // Left Left Case
    if (balance > 1 && BalanceFactor(node->Left) >= 0)
	{
		return RightRotate(node);
	}

    // Left Right Case
    if (balance > 1 && BalanceFactor(node->Left) < 0) {
        node->Left = LeftRotate(node->Left);
        return RightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && BalanceFactor(node->Right) <= 0)
        return LeftRotate(node);

    // Right Left Case
    if (balance < -1 && BalanceFactor(node->Right) > 0) {
        node->Right = RightRotate(node->Right);
        return LeftRotate(node);
    }

    return node;
}

void AVLTree::Insert(int key) {
    root = Insert(root, key);
}

void AVLTree::Remove(int key) {
    root = DeleteNode(root, key);
}

