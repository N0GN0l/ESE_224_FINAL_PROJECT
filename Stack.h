// Stack.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong
//
// A last-in first-out stack built on your own singly linked list (Section 4.1).
// Templates must be written entirely in the header file.

#ifndef STACK_H
#define STACK_H

#include <iostream>

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node* next;
    };
    Node* topNode;
    int count;

public:
    Stack() : topNode(nullptr), count(0) {}

    ~Stack()
    {
        // TODO: free every node (hint: clear())
        clear();
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& item)
    {
        // TODO: add a new node on top
        if(topNode == nullptr)
        {
            topNode = new Node(item, nullptr);
            return;
        }

        Node* temp = topNode;
        topNode = new Node(item , temp);

        count++;
    }

    bool pop(T& item)
    {
        return false;
        if(isEmpty())
        {
            std::cerr<<"Stack is empty, cannot pop"<<std::endl;
            return false;
        }
        
        Node* temp = topNode;
        item = topNode->data;
        
        topNode = topNode->next;
        
        delete(temp);

        return true;
        // TODO: remove the top node, copy its data into item, return true; false if empty
    }

    bool top(T& item) const
    {
        // TODO: copy the top data into item without removing it
        return false;
    }

    bool isEmpty() const { return topNode == nullptr; }
    int size() const { return count; }

    void clear()
    {
        // TODO: remove every node
    }
};

#endif
