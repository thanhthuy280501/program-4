#include "llist.h"

template <typename T>
LList<T>::~LList() {
    Link<T>* current = head;
    while (current) {
        Link<T>* temp = current;
        current = current->next;
        delete temp;
    }
}

template <typename T>
void LList<T>::append(const T& item) {
    Link<T>* newLink = new Link<T>(item);
    if (!head) {
        head = tail = newLink;
    } else {
        tail->next = newLink;
        tail = newLink;
    }
    size++;
}

template <typename T>
void LList<T>::remove(const std::string& isbn) {
    Link<T>* current = head;
    Link<T>* prev = nullptr;

    while (current) {
        if (current->value.getISBN() == isbn) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            if (!current->next) {
                tail = prev;
            }
            delete current;
            size--;
            return;
        }
        prev = current;
        current = current->next;
    }
    std::cerr << "Item not found: " << isbn << std::endl;
}

template <typename T>
T* LList<T>::search(const std::string& isbn) {
    Link<T>* current = head;
    while (current) {
        if (current->value.getISBN() == isbn) {
            return &current->value;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
void LList<T>::display() const {
    Link<T>* current = head;
    while (current) {
        current->value.displayDetails();
        current = current->next;
    }
}
