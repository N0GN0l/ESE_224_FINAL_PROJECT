// DroneTree.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong
//
// Write every operation recursively using the private helpers (Section 6).
// The tree does NOT own the units: delete tree nodes only, never node->unit.

#include "DroneTree.h"
#include <iostream>

DroneTree::DroneTree() : root(nullptr), count(0) {}

DroneTree::~DroneTree() { destroy(root); }

void DroneTree::destroy(TreeNode* node)
{
    if(node->left->left != nullptr)
    {
        destroy(node->left);
    }
    else if(node->left->left == nullptr)
    {
        if(node->left != nullptr)
        {
            delete(node->left);
        }

        if(node->right->right == nullptr)
        {
            delete(node->right);
            delete(root);
        }
        else if(node->right->right != nullptr)
        {
            destroy(node->right);    
        }
    }
    // TODO: delete every node (post-order)
}

bool DroneTree::insert(DeliveryUnit* u)
{
    if (insertHelper(root, u)) { count++; return true; }
    return false;
}

bool DroneTree::insertHelper(TreeNode*& node, DeliveryUnit* u)
{
    // TODO: smaller IDs left, larger right; false on a duplicate
    return false;
}

DeliveryUnit* DroneTree::search(int id, int& comparisons) const
{
    comparisons = 0;
    return searchHelper(root, id, comparisons);
}

DeliveryUnit* DroneTree::searchHelper(TreeNode* node, int id, int& comparisons) const
{
    // TODO: one comparison per node examined
    return nullptr;
}

bool DroneTree::remove(int id)
{
    if (removeHelper(root, id)) { count--; return true; }
    return false;
}

bool DroneTree::removeHelper(TreeNode*& node, int id)
{
    // TODO: three cases; two children -> in-order successor
    return false;
}

void DroneTree::inOrder() const { inOrderHelper(root); std::cout << std::endl; }
void DroneTree::preOrder() const { preOrderHelper(root); std::cout << std::endl; }
void DroneTree::postOrder() const { postOrderHelper(root); std::cout << std::endl; }

void DroneTree::inOrderHelper(TreeNode* node) const { /* TODO */ }
void DroneTree::preOrderHelper(TreeNode* node) const { /* TODO */ }
void DroneTree::postOrderHelper(TreeNode* node) const { /* TODO */ }

int DroneTree::height() const { return heightHelper(root); }

int DroneTree::heightHelper(TreeNode* node) const
{
    // TODO: empty tree 0, one node 1
    return 0;
}

int DroneTree::size() const { return count; }
