// Declaration and implementation of a generic linked list template.
// Stores any data type and provides safe management operations.

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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

    Node* node_at(std::size_t position) {
        if (position >= size_) {
            return nullptr;
        }

        Node* current = head_;
        std::size_t index = 0;
        while (current != nullptr && index < position) {
            current = current->next;
            ++index;
        }
        return current;
    }

    const Node* node_at(std::size_t position) const {
        if (position >= size_) {
            return nullptr;
        }

        const Node* current = head_;
        std::size_t index = 0;
        while (current != nullptr && index < position) {
            current = current->next;
            ++index;
        }
        return current;
    }

    void copy_from(const LinkedList& other) {
        for (const Node* current = other.head_; current != nullptr; current = current->next) {
            insert(current->data, size_);
        }
    }

public:
    LinkedList() : head_(nullptr), size_(0) {}

    LinkedList(const LinkedList& other) : head_(nullptr), size_(0) {
        copy_from(other);
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    LinkedList(LinkedList&& other) noexcept : head_(other.head_), size_(other.size_) {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~LinkedList() {
        clear();
    }

    void insert(const T& value, std::size_t position = 0) {
        if (position > size_) {
            position = size_;
        }

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

    void insert_at(const T& value, std::size_t position) {
        insert(value, position);
    }

    bool remove(const T& value) {
        Node* current = head_;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                if (previous == nullptr) {
                    head_ = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                --size_;
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    bool remove_at(std::size_t position) {
        if (position >= size_) {
            return false;
        }

        Node* current = head_;
        Node* previous = nullptr;
        std::size_t index = 0;

        while (current != nullptr && index < position) {
            previous = current;
            current = current->next;
            ++index;
        }

        if (current == nullptr) {
            return false;
        }

        if (previous == nullptr) {
            head_ = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
        --size_;
        return true;
    }

    T* get(std::size_t position) {
        Node* current = node_at(position);
        return (current == nullptr) ? nullptr : &current->data;
    }

    const T* get(std::size_t position) const {
        const Node* current = node_at(position);
        return (current == nullptr) ? nullptr : &current->data;
    }

    bool search(const T& value) const {
        const Node* current = head_;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

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

    bool update_at(std::size_t position, const T& new_value) {
        Node* current = node_at(position);
        if (current == nullptr) {
            return false;
        }

        current->data = new_value;
        return true;
    }

    void traverse() const {
        const Node* current = head_;
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

    void clear() {
        Node* current = head_;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head_ = nullptr;
        size_ = 0;
    }

    std::vector<T> to_vector() const {
        std::vector<T> values;
        const Node* current = head_;
        while (current != nullptr) {
            values.push_back(current->data);
            current = current->next;
        }
        return values;
    }

    std::size_t count_elements() const {
        return size_;
    }

    bool is_empty() const {
        return head_ == nullptr;
    }

    const T& front() const {
        if (is_empty()) {
            throw std::out_of_range("LinkedList is empty");
        }
        return head_->data;
    }
};

#endif // LINKED_LIST_H
