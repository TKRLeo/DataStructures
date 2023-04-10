//
// Created by Lev on 09.04.2023.
//
#include <iostream>
#ifndef PROJECTCPP_TREE_H
#define PROJECTCPP_TREE_H

template<typename NODETYPE> class Tree;

template <typename NODETYPE> class TreeNode {
    friend class Tree<NODETYPE>;
public:
    TreeNode(const NODETYPE &);
    NODETYPE getData();
protected:
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    NODETYPE data;
};

template <typename NODETYPE> class Tree {
public:
    Tree();
    int insertNode(const NODETYPE &);
    void deleteNode(TreeNode<NODETYPE>*);
    void inorderWalk(TreeNode<NODETYPE>*);
    TreeNode<NODETYPE>* findMax(TreeNode<NODETYPE>*);
    TreeNode<NODETYPE>* findMin(TreeNode<NODETYPE>*);
    TreeNode<NODETYPE>* findNode(TreeNode<NODETYPE>*, const NODETYPE &);
    TreeNode<NODETYPE>* findSuccsessor(const NODETYPE &);
    TreeNode<NODETYPE>* getRoot();
    void deleteTree(TreeNode<NODETYPE>* node);

    ~Tree();
private:
    TreeNode<NODETYPE>* root;
};

template <class NODETYPE>
Tree<NODETYPE>::Tree() {
    root = nullptr;
}

template<class NODETYPE>
TreeNode<NODETYPE>::TreeNode(const NODETYPE &a) {
    data = a;
    left = right = nullptr;
}

template<class NODETYPE>
NODETYPE TreeNode<NODETYPE>::getData() {
    return data;
}

template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::getRoot() {
    return root;
}


template<class NODETYPE>
void Tree<NODETYPE>::inorderWalk(TreeNode<NODETYPE> *node) {
    if(node != 0) {
        inorderWalk(node->left);
        std::cout<< node->getData()<<std::endl;
        inorderWalk(node->right);
    }
}


template<class NODETYPE>
int Tree<NODETYPE>::insertNode(const NODETYPE &x) {
    TreeNode<NODETYPE>* node = new TreeNode<NODETYPE>(x);
    TreeNode<NODETYPE>* ptr = root;
    TreeNode<NODETYPE>* ptr1 = nullptr;

    node->parent = node->left = node->right = nullptr;

    while (ptr != nullptr) {
        ptr1 = ptr;
        if (x < ptr->getData())
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    node->parent = ptr1;
    if (ptr1 == nullptr)
        root = node;
    else {
        if (x < ptr1->getData())
            ptr1->left = node;
        else
            ptr1->right = node;
    }

    return 0;
}

template <typename NODETYPE>
void Tree<NODETYPE>::deleteNode(TreeNode<NODETYPE> *node) {
    TreeNode<NODETYPE> *ptrPivot;
    TreeNode<NODETYPE> *ptrChild;

    if (node == nullptr)
        return;

    if (node->left == nullptr && node->right == nullptr) {
        if (node != root) {
            if (node->parent->left == node)
                node->parent->left = nullptr;
            else
                node->parent->right = nullptr;
        } else
            root = nullptr;
        delete (node);
    }
    else if(node->left != nullptr && node->right != nullptr) {
        ptrPivot = findSuccsessor(node->getData());
        deleteNode(ptrPivot);
        node->data = ptrPivot->getData();
    }
    else {
        ptrChild = (node->left != nullptr) ? node->left: node->right;
        if (node != root) {
            if (node == node->parent->left)
                node->parent->left = ptrChild;
            else
                node->parent->right = ptrChild;
        }
        else
            root = ptrChild;
        delete(node);
    }

}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::findSuccsessor(const NODETYPE &value) {
    TreeNode<NODETYPE>* ptr = findNode(root, value);
    TreeNode<NODETYPE>* prev = nullptr;

    if (ptr == nullptr)
        return nullptr;

    if(ptr->right != nullptr)
        return findMin(ptr->right);
    prev = ptr->parent;

    while(prev != nullptr && ptr == prev->right) {
        ptr = prev;
        prev = prev->parent;
    }

    return prev;
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::findNode(TreeNode<NODETYPE>* node,
                                              const NODETYPE & value) {
    if (node == nullptr || value == node->getData())
        return node;
    if (value > node->getData())
        return findNode(node->right, value);
    else
        return findNode(node->left,value);
}

template<typename NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::findMin(TreeNode<NODETYPE>* ptr) {
    while(ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;

}

template<typename NODETYPE>
Tree<NODETYPE>::~Tree() {
    deleteTree(root);
}

template<typename NODETYPE>
void Tree<NODETYPE>::deleteTree(TreeNode<NODETYPE> *node) {
    if(node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template<typename NODETYPE>
TreeNode<NODETYPE> *Tree<NODETYPE>::findMax(TreeNode<NODETYPE> *node) {
    while(node->right != nullptr)
        node = node->right;
    return node;
}


#endif //PROJECTCPP_TREE_H
