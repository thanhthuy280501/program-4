#ifndef LLIST_H
#define LLIST_H

#include "link.h"
#include <iostream>

template <typename T>
class LList {
private:
    Link<T>* head;
    Link<T>* tail;
    int size;

public:
    LList() : head(nullptr), tail(nullptr), size(0) {}
    ~LList();

    void append(const T& item);
    void remove(const std::string& isbn);
    T* search(const std::string& isbn);
    void display() const;
};

#endif
