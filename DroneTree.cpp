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
    // TODO: smaller IDs left, larger right; false on a duplicate
    if (node == nullptr)
    {
        node = new TreeNode(u, nullptr, nullptr);
        return true;
    }
    
    int comparisons;
    if(search(u->getID(), comparisons) != nullptr)
    {
        std::cerr<<"Cannot insert duplicate delivery units"<<std::endl;
        return false;
    }


    if(node->left == nullptr && node->right == nullptr)
    {
        if(u->getID() < node->unit->getID())
        {
            node->left = new TreeNode(u,nullptr,nullptr);
        }
        else {
            node->right = new TreeNode(u, nullptr, nullptr);
        }
    }
    else //This runs when the right node isn't a nullptr
    {
        //The following if statements don't check for when the ID is equal because that should be impossible
        if(u->getID() < node->unit->getID())
        {
            insertHelper(node->left, u);
        }
        else //this block runs when the unit node id is larger than the node id 
        {
            insertHelper(node->right, u);
        }
    }
    return true;
}

DeliveryUnit* DroneTree::search(int id, int& comparisons) const
{
    comparisons = 0;
    return searchHelper(root, id, comparisons);
}

DeliveryUnit* DroneTree::searchHelper(TreeNode* node, int id, int& comparisons) const
{
    // TODO: one comparison per node examined
    comparisons++;
    if(node == nullptr)
    {
        return nullptr;
    }
    
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
    if (removeHelper(root, id) != nullptr) { count--; return true; }
    return false;
}

DroneTree::TreeNode* DroneTree::getSuccessor(TreeNode* curr) {
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

DroneTree::TreeNode* DroneTree::removeHelper(TreeNode*& node, int id)
{
    // TODO: three cases; two children -> in-order successor
    
    if(id > node->unit->getID())
    {
        node->right = removeHelper(node->right, id);
    }

    else if(id < node->unit->getID())
    {
        node->left = removeHelper(node->left, id);
    }

    else//if(id == node->unit->getID())
    {
        if(node->left == nullptr)
        {
            TreeNode* temp = node->right;
            delete(node);
            return temp;
        }
        if(node->right == nullptr)
        {
            TreeNode* temp = node->left;
            delete(node);
            return temp;
        }

        TreeNode* succ = getSuccessor(node);
        node->unit->setID(succ->unit->getID());
        node->right = removeHelper(node->right, succ->unit->getID());
    }
    return node;
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
    inOrderHelper(node->right);
    std::cout<< node->unit->getID()<<" ";
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


