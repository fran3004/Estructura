"""Linked list module.

This file contains a generic singly linked list implementation for storing
any type of value in the PITA project.
"""


class Node:
    """Represents a single node in the linked list."""

    def __init__(self, data, next_node=None):
        self.data = data
        self.next = next_node


class LinkedList:
    """Represents a singly linked list with basic operations."""

    def __init__(self):
        """Initializes an empty list."""
        self.head = None
        self.size = 0

    def insert(self, value, position=0):
        """Inserts a value at the given position.

        If position is 0, the value is inserted at the beginning. If the position
        is greater than the current size, it is added at the end.
        """
        new_node = Node(value)

        if self.head is None or position == 0:
            new_node.next = self.head
            self.head = new_node
            self.size += 1
            return

        current = self.head
        index = 0

        while current.next is not None and index < position - 1:
            current = current.next
            index += 1

        new_node.next = current.next
        current.next = new_node
        self.size += 1

    def remove(self, value):
        """Removes the first occurrence of the given value.

        Returns True if the element was removed, otherwise False.
        """
        if self.head is None:
            return False

        if self.head.data == value:
            self.head = self.head.next
            self.size -= 1
            return True

        current = self.head
        while current.next is not None and current.next.data != value:
            current = current.next

        if current.next is None:
            return False

        current.next = current.next.next
        self.size -= 1
        return True

    def search(self, value):
        """Searches for a value in the list.

        Returns True if the value exists, otherwise False.
        """
        current = self.head
        while current is not None:
            if current.data == value:
                return True
            current = current.next
        return False

    def update(self, target_value, new_value):
        """Updates the first value matching the target with the new value.

        Returns True if a change was made, otherwise False.
        """
        current = self.head
        while current is not None:
            if current.data == target_value:
                current.data = new_value
                return True
            current = current.next
        return False

    def traverse(self):
        """Traverses the list and prints each value in the console."""
        current = self.head
        values = []
        while current is not None:
            values.append(current.data)
            current = current.next

        print(values)

    def count_elements(self):
        """Returns the number of elements in the list."""
        return self.size

    def is_empty(self):
        """Returns True if the list is empty, otherwise False."""
        return self.head is None
