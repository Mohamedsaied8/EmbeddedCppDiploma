#include <iostream>

// Templated Queue Class
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t size;

public:
    // Constructor
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // Destructor
    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }

    // Enqueue operation
    void enqueue(T value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Dequeue operation
    void dequeue() {
        if (empty()) {
            std::cerr << "Queue is empty!" << std::endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
    }

    // Get front element
    T peek() const {
        if (empty()) {
            throw std::underflow_error("Queue is empty");
        }
        return front->data;
    }

    // Check if the queue is empty
    bool empty() const {
        return size == 0;
    }

    // Get size of the queue
    size_t getSize() const {
        return size;
    }
};
