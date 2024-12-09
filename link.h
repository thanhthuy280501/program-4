#ifndef LINK_H
#define LINK_H

template <typename T>
class Link {
public:
    T value;
    Link<T>* next;

    Link(const T& val, Link<T>* nxt = nullptr) : value(val), next(nxt) {}
};

#endif
