#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <typename T>
class LinkedList {
  struct Node {
    T data;
    Node* next{nullptr};
    Node* prev{nullptr};
    Node(T data, Node* next = nullptr, Node* prev = nullptr) {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
  };

  Node* head{nullptr};
  Node* tail{nullptr};

public:
  LinkedList() {};

  ~LinkedList() {
    Node* n = head;
    while(n) {
      Node* next = n->next;
      delete n;
      n = nullptr;
      n = next;
    }
  }

  void push(T data) {
    if (!head) {
      head = new Node(data);
      tail = head;
    } else {
      Node* n = head;
      while (n->next) {
        n = n->next;
      }
      n->next = new Node(data);
      n->next->prev = n;
      tail = n->next;
    }
  }

  void display(std::ostream& os) const {
    Node* n = head;
    while (n) {
      os << n->data << '\n';
      n = n->next;
    }
  }

  void displayPrev(std::ostream& os) const {
    Node* n = head;
    while (n) {
      if (n->prev) {
        os << n->prev->data << '\n';
      }
      n = n->next;
    }
  }

  bool remove(T data) {
    Node* n = head;
    while (n) {
      if (n->data == data) {
        if (!n->prev && n->next) {
          head = n->next;
          delete n;
        } else if (n->prev && n->next) {
          n->prev->next = n->next;
          n->next->prev = n->prev;
          delete n;
        } else if (n->prev && !n->next) {
          tail = n->prev;
          n->prev->next = nullptr;
          delete n;
        } else {
          tail = nullptr;
          head = nullptr;
          delete n;
        }
        return true;
      }
    }

    return false;
  }

  Node* getHead() {
    return this->head;
  }
  
};

#endif //!LINKEDLIST