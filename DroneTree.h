// DroneTree.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: TODO

#ifndef DRONETREE_H
#define DRONETREE_H

#include "DeliveryUnit.h"

// Binary search tree index of the fleet, keyed by unit ID.
// The tree does NOT own the units (the Fleet does); it only deletes its own nodes.
class DroneTree
{
private:
    struct TreeNode
    {
        DeliveryUnit* unit;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;
    int count;

    // Recursive helpers
    bool insertHelper(TreeNode*& node, DeliveryUnit* u);
    DeliveryUnit* searchHelper(TreeNode* node, int id, int& comparisons) const;
    bool removeHelper(TreeNode*& node, int id);
    void inOrderHelper(TreeNode* node) const;
    void preOrderHelper(TreeNode* node) const;
    void postOrderHelper(TreeNode* node) const;
    int heightHelper(TreeNode* node) const;
    void destroy(TreeNode* node);

public:
    DroneTree();
    ~DroneTree();
    DroneTree(const DroneTree&) = delete;
    DroneTree& operator=(const DroneTree&) = delete;

    bool insert(DeliveryUnit* u);                       // false if the ID is already present
    DeliveryUnit* search(int id, int& comparisons) const; // nullptr if not found
    bool remove(int id);                               // false if not found
    void inOrder() const;                              // prints IDs, ascending
    void preOrder() const;
    void postOrder() const;
    int height() const;                                // empty tree = 0, one node = 1
    int size() const;
};

#endif
