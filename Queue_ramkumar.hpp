#ifndef QUEUE_RAMKUMAR_HPP
#define QUEUE_RAMKUMAR_HPP

#include <stdexcept> //For std::out_of_range exception

template <typename T>
class QueueNode {
public:
    T data;
    QueueNode* next;

    QueueNode(T value) : data(value), next(nullptr) {}
};

template <typename T>
class Queue {
private:
    QueueNode<T>* frontptr;
    QueueNode<T>* end;
    int blksize;

public:
    //Constructor
    Queue() : frontptr(nullptr), end(nullptr), blksize(0) {}

    //Destructor
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    //Add item to the queue
    void enqueue(T value) {
        QueueNode<T>* newNode = new QueueNode<T>(value);
        if (isEmpty()) {
            frontptr = newNode;
        } else {
            end->next = newNode;
        }
        end = newNode;
        blksize++;
    }

    //Remove the front node of the queue (follows FIFO - first in first out)
    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        QueueNode<T>* temp = frontptr;
        frontptr = frontptr->next;
        delete temp;
        if (frontptr == nullptr) {
            end = nullptr;
        }
        blksize--;
    }

    //Display the value of the item at the front of the queue without removing it
    T front() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return frontptr->data;
    }

    //Display the number of items in the queue
    int size() const {
        return blksize;
    }

    //Clear the queue by emptying all the values
    void empty() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    //Check to see whether the queue is empty or not
    bool isEmpty() const {
        return blksize == 0;
    }
};

#endif
