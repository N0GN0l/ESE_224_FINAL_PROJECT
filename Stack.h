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
        // works for an empty stack too: the new node's next is just nullptr
        topNode = new Node{item, topNode};
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

        count--;
        return true;
    }

    bool top(T& item) const
    {
        if(isEmpty())
        {
            std::cerr<<"Stack is empty, cannot access top"<<std::endl;
            return false;
        }

        item = topNode->data;

        return true;
    }

    bool isEmpty() const { return topNode == nullptr; }
    int size() const { return count; }

    void clear()
    {
        // TODO: remove every node
        while(topNode->next != nullptr)
        {
            Node* temp = topNode;
            topNode = topNode->next;
            delete(temp);
        }

        topNode = nullptr;
        count = 0;
    }
};

#endif
