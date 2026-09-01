// Declaration and implementation of a generic linked list template.
// Stores any data type and provides basic management operations.
// This structure can be reused by future system entities.

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& value, Node* next_node = nullptr) : data(value), next(next_node) {}
    };

    Node* head_;
    std::size_t size_;

public:
    // Constructor: initializes an empty list.
    LinkedList() : head_(nullptr), size_(0) {}

    // Destructor: releases all nodes to prevent memory leaks.
    ~LinkedList() {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        size_ = 0;
    }

    // Inserts an element at the given position.
    // Position 0 inserts at the beginning; positions beyond the size append at the end.
    void insert(const T& value, std::size_t position = 0) {
        Node* new_node = new Node(value);

        if (head_ == nullptr || position == 0) {
            new_node->next = head_;
            head_ = new_node;
            ++size_;
            return;
        }

        Node* current = head_;
        std::size_t index = 0;

        while (current->next != nullptr && index < position - 1) {
            current = current->next;
            ++index;
        }

        new_node->next = current->next;
        current->next = new_node;
        ++size_;
    }

    // Removes the first occurrence of the given value.
    // Returns true when removed and false when it does not exist.
    bool remove(const T& value) {
        if (head_ == nullptr) {
            return false;
        }

        if (head_->data == value) {
            Node* temporary = head_;
            head_ = head_->next;
            delete temporary;
            --size_;
            return true;
        }

        Node* current = head_;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        if (current->next == nullptr) {
            return false;
        }

        Node* temporary = current->next;
        current->next = temporary->next;
        delete temporary;
        --size_;
        return true;
    }

    // Checks whether a value exists in the list.
    // Returns true when found and false otherwise.
    bool search(const T& value) const {
        Node* current = head_;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Replaces the first matching value with a new value.
    // Returns true when changed and false when the target does not exist.
    bool update(const T& target_value, const T& new_value) {
        Node* current = head_;
        while (current != nullptr) {
            if (current->data == target_value) {
                current->data = new_value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Traverses the list and prints each element to the console.
    // Useful for debugging and viewing the current structure contents.
    void traverse() const {
        Node* current = head_;
        std::cout << "[";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << ", ";
            }
            current = current->next;
        }
        std::cout << "]" << std::endl;
    }

    // Returns the number of elements stored in the list.
    std::size_t count_elements() const {
        return size_;
    }

    // Checks whether the list is empty.
    bool is_empty() const {
        return head_ == nullptr;
    }
};

#endif // LINKED_LIST_H
