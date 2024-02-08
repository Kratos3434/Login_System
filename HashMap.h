#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <iostream>
#include "LinkedList.h"

template <typename T, typename S>
class HashMap
{
  struct Node
  {
    T key;
    S value;
    Node(T key, S value)
    {
      this->key = key;
      this->value = value;
    }
  };

  std::vector<LinkedList<Node *> *> map;
  S defaultValue{S()};
  size_t cap{0};
  size_t len{0};

public:
  HashMap(size_t cap)
  {
    map.reserve(cap);
    for (size_t i=0;i<cap;i++) {
      map[i] = nullptr;
    }
    this->cap = cap;
  }

  ~HashMap()
  {
    deallocate(this->cap);
  }

  HashMap(const HashMap<T, S> &m)
  {
    deallocate(this->cap);
    this->cap = m.cap;
    this->len = 0;
    map.reserve(this->cap);
    for (size_t i=0;i<this->cap;i++) {
      map[i] = nullptr;
    }
    for (size_t i = 0; i < this->cap; i++)
    {
      if (m.map[i]) {
        auto n = m.map[i]->getHead();
        while (n) {
          size_t idx = hashKey(n->data->key);
          if (!map[idx]) {
            map[idx] = new LinkedList<Node*>();
          }
          map[idx]->push(new Node(n->data->key, n->data->value));
          this->len++;
          n = n->next;
        }
      }
    }
  }

  HashMap<T, S>& operator=(const HashMap<T, S>& m) {
    deallocate(this->cap);
    this->cap = m.cap;
    this->len = 0;
    map.reserve(this->cap);
    for (size_t i=0;i<this->cap;i++) {
      map[i] = nullptr;
    }
    for (size_t i = 0; i < this->cap; i++)
    {
      if (m.map[i]) {
        auto n = m.map[i]->getHead();
        while (n) {
          size_t idx = hashKey(n->data->key);
          if (!map[idx]) {
            map[idx] = new LinkedList<Node*>();
          }
          map[idx]->push(new Node(n->data->key, n->data->value));
          this->len++;
          n = n->next;
        }
      }
    }
    return *this;
  }

  size_t hashKey(T key) const
  {
    std::hash<T> myHash;
    return myHash(key) % cap;
  }

  void add(T key, S value)
  {
    size_t idx = hashKey(key);
    if (find(key))
    {
    }
    else
    {
      if (!map[idx])
      {
        map[idx] = new LinkedList<Node *>();
      }
      map[idx]->push(new Node(key, value));
      this->len++;
      const float loadFactor = (float)len / (float)cap;
      if (loadFactor >= 0.75)
      {
        std::cout << "Load factor exceeded" << std::endl;
        this->cap *= 2;
        HashMap<T, S> temp = *this;

        deallocate(this->cap/2);
        map.clear();
        map.reserve(this->cap);
        // for (size_t i = 0; i < this->cap / 2; i++)
        // {
        //   if (temp[i])
        //   {
        //     auto n = temp[i]->getHead();
        //     while (n)
        //     {
        //       size_t idx = hashKey(n->data->key);
        //       if (!map[idx])
        //       {
        //         map[idx] = new LinkedList<Node *>();
        //       }
        //       map[idx]->push(new Node(n->data->key, n->data->value));
        //       n = n->next;
        //     }
        //   }
        // }
      }
    }
  }

  bool find(T key) const
  {
    size_t idx = hashKey(key);
    if (map[idx])
    {
      auto n = map[idx]->getHead();
      while (n)
      {
        if (n->data->key == key)
        {
          return true;
        }
        n = n->next;
      }
    }
    return false;
  }

  S &operator[](T key)
  {
    size_t idx = hashKey(key);
    if (map[idx])
    {
      auto n = map[idx]->getHead();
      while (n)
      {
        if (n->data->key == key)
        {
          return n->data->value;
        }
        n = n->next;
      }
    }
    return defaultValue;
  }

  void deallocate(size_t length)
  {
    for (size_t i = 0; i < length; i++)
    {
      if (map[i])
      {
        auto n = map[i]->getHead();
        while (n)
        {
          delete n->data;
          n = n->next;
        }
        delete map[i];
      }
    }
  }
};

#endif //! HASHMAP_H