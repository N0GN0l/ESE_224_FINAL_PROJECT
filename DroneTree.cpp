// DroneTree.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong
//
// Write every operation recursively using the private helpers (Section 6).
// The tree does NOT own the units: delete tree nodes only, never node->unit.

#include "DroneTree.h"
#include "DeliveryUnit.h"
#include <iostream>

DroneTree::DroneTree() : root(nullptr), count(0) {}

DroneTree::~DroneTree() { destroy(root); root = nullptr; count = 0;}

void DroneTree::destroy(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}

bool DroneTree::insert(DeliveryUnit* u)
{
    if (insertHelper(root, u)) { count++; return true; }
    return false;
}

bool DroneTree::insertHelper(TreeNode*& node, DeliveryUnit* u)
{
    // smaller IDs left, larger right; false on a duplicate
    if (node == nullptr)
    {
        node = new TreeNode(u, nullptr, nullptr);
        return true;
    }

    int id = u->getID();
    int nodeID = node->unit->getID();
    if (id == nodeID)
    {
        return false;
    }
    if (id < nodeID)
    {
        return insertHelper(node->left, u);
    }
    return insertHelper(node->right, u);
}

DeliveryUnit* DroneTree::search(int id, int& comparisons) const
{
    comparisons = 0;
    return searchHelper(root, id, comparisons);
}

DeliveryUnit* DroneTree::searchHelper(TreeNode* node, int id, int& comparisons) const
{
    // one comparison per node examined
    if(node == nullptr)
    {
        return nullptr;
    }
    comparisons++;
    
    if(node->unit->getID() == id)
    {
        return node->unit;
    }


    if(id > node->unit->getID())
    {
        return searchHelper(node->right, id, comparisons);
    }

    return searchHelper(node->left, id, comparisons);
}

bool DroneTree::remove(int id)
{
    if (removeHelper(root, id)) { count--; return true; }
    return false;
}

DroneTree::TreeNode* DroneTree::getSuccessor(TreeNode* curr)
{
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

bool DroneTree::removeHelper(TreeNode*& node, int id)
{
    // three cases; two children -> in-order successor
    if (node == nullptr)
    {
        return false;
    }

    int nodeID = node->unit->getID();
    if (id < nodeID)
    {
        return removeHelper(node->left, id);
    }
    if (id > nodeID)
    {
        return removeHelper(node->right, id);
    }

    if (node->left == nullptr || node->right == nullptr)
    {
        TreeNode* child = (node->left != nullptr) ? node->left : node->right;
        delete node;
        node = child;
        return true;
    }

    TreeNode* succ = getSuccessor(node);
    node->unit = succ->unit;
    return removeHelper(node->right, succ->unit->getID());
}

void DroneTree::inOrder() const { inOrderHelper(root); std::cout << std::endl; }
void DroneTree::preOrder() const { preOrderHelper(root); std::cout << std::endl; }
void DroneTree::postOrder() const { postOrderHelper(root); std::cout << std::endl; }

void DroneTree::inOrderHelper(TreeNode* node) const 
{
    if(node== nullptr)
    {
        return;
    }
    
    inOrderHelper(node->left);
    std::cout<< node->unit->getID()<<" ";
    inOrderHelper(node->right);
}

void DroneTree::preOrderHelper(TreeNode* node) const 
{
    if(node == nullptr)
    {
        return;
    }
    std::cout<<node->unit->getID()<<" ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
}

void DroneTree::postOrderHelper(TreeNode* node) const 
{
    if(node == nullptr)
    {
        return;
    }

    postOrderHelper(node->left);
    postOrderHelper(node->right);
    std::cout<<node->unit->getID()<<" ";
}

int DroneTree::height() const { return heightHelper(root); }

int DroneTree::heightHelper(TreeNode* node) const
{
    if (node == nullptr)
    {
        return 0;
    }

    int leftHeight = heightHelper(node->left);
    int rightHeight = heightHelper(node->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int DroneTree::size() const { return count; }


