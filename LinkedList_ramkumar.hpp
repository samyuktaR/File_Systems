#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <iostream>

//Linked list node class template
template<typename T>
class Node {
public:
    T data; //Data stored in node
    Node* next; //Pointer to next node

    //Constructor initializing node with given value
    Node(T value) : data(value), next(nullptr) {}
};

//Linked list class template for single linked list
template<typename T>
class LinkedList {
private:
	Node<T>* head; //Pointer to head of linked list
    int size; //Size of linked list

public:
    //Constructor initializing empty linked list
    LinkedList() : head(nullptr), size(0) {}

    //Destructor
    ~LinkedList(){};
    //Get the head of the linked list
    Node<T>* getHead() {
    	return head;
    	}

    //Add a node to the end of the linked list
    void addNode(T value) {
    	//Check to see if list is empty
    	if (head == nullptr) {
    		head = new Node<T>(value); //Create new node and make it the head
    	} else {
    		Node<T>* current = head;
    		//Iterate through the linked list in order to find the last node
    		while (current->next != nullptr) {
    			current = current->next;
    		}
    		current->next = new Node<T>(value); //Attach new node to last node
    	}
    }

    //Method to remove a node from the linked list
    void removeNode(Node<T>* nodeToRemove) {
    	if (head == nullptr) {
    		std::cout << "List is empty. Cannot remove node." << std::endl;
    		return;
    	}

    	if (head == nodeToRemove) {
    		Node<T>* temp = head; //Store head in a temporary variable
    		head = head->next; //Move head to the next node
    		delete temp; //Delete old head
    		return;
    	}

    	Node<T>* current = head;
    	//Iterate though the list to find the node before the node to remove
    	while (current->next != nullptr && current->next != nodeToRemove) {
    		current = current->next;
    	}

    	if (current->next != nullptr) { //If the node to remove is found
    		Node<T>* temp = current->next;
    		current->next = current->next->next; //Skip to the node to be removed
    		delete temp;
    	}
    }
    //Return the size of the list
    int getSize() const {
        return size;
    }

    //Check if the list is empty
    bool isEmpty() const {
        return size == 0;
    }

    //Clear the list
    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next; //Store the next node
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0; //Reset the size of the list
    }

    LinkedList(const LinkedList& other) : head(nullptr), size(0) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            addNode(current->data);
            current = current->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            Node<T>* current = other.head;
            while (current != nullptr) {
                insertBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }
};

#endif
