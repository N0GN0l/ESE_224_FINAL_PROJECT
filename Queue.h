// Queue.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong
//
// A first-in first-out queue built on your own singly linked list (Section 4.1).
// Templates must be written entirely in the header file.

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node* next;
    };
    Node* frontNode;
    Node* backNode;
    int count;

public:
    Queue() : frontNode(nullptr), backNode(nullptr), count(0) {}

    ~Queue()
    {
        clear();
        frontNode = nullptr;
        backNode = nullptr;
    }

    // A queue owns its nodes, so copying is not allowed
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void enqueue(const T& item)
    {
        if(isEmpty())
        {
            frontNode = new Node{item, nullptr};
            backNode = frontNode;
        }
        else {
            backNode->next = new Node{item, nullptr};
            backNode = backNode->next;
        }

        count++;
    }

    bool dequeue(T& item)
    {
        if(isEmpty())
        {
            std::cerr<<"Queue is empty, cannot dequeue"<<std::endl;
            return false;
        }

        Node* temp = frontNode;
        item = frontNode->data;
        frontNode = frontNode->next;
        delete(temp);

        count--;
        return true;
    }

    bool front(T& item) const
    {
        if(isEmpty())
        {
            std::cerr<<"Queue is empty, cannot access front"<<std::endl;
            return false;
        }

        item = frontNode->data;
        return true;
        
    }

    bool isEmpty() const { return frontNode == nullptr; }
    int size() const { return count; }

    void clear()    //Clears the queue
    {
        while(frontNode->next != nullptr)
        {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete(temp);
        }

        frontNode = nullptr;
        backNode = nullptr;
        count = 0;
    }
};

#endif
