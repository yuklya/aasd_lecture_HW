#ifndef BILIST_HPP
#define BILIST_HPP

#include <initializer_list>
#include <iostream>

template<typename T>
class BiList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value, Node* p = nullptr, Node* n = nullptr)
            : data(value), prev(p), next(n) {}
    };
    Node* head;
    Node* tail;
    size_t count;
public:
    BiList() : head(nullptr), tail(nullptr), count(0) {}
    BiList(const BiList& other) : head(nullptr), tail(nullptr), count(0) {
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    BiList(std::initializer_list<T> init) : head(nullptr), tail(nullptr), count(0) {
        for (const T& value : init) {
            push_back(value);
        }
    }
    ~BiList() {
        clear();
    }
    BiList& operator=(const BiList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    T& front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }
    const T& front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }
    T& back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }
    const T& back() const {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }
    void push_front(const T& value) {
        Node* newNode = new Node(value, nullptr, head);
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        count++;
    }
    void push_back(const T& value) {
        Node* newNode = new Node(value, tail, nullptr);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        count++;
    }
    void pop_front() {
        if (empty()) return;
        Node* toDelete = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete toDelete;
        count--;
    }
    void pop_back() {
        if (empty()) return;
        Node* toDelete = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete toDelete;
        count--;
    }
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    bool empty() const {
        return count == 0;
    }
    size_t size() const {
        return count;
    }
};
#endif
