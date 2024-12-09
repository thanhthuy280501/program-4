#include "LibraryItem.h"
#include <iostream>

// Constructors
LibraryItem::LibraryItem() : title(""), ISBN(""), publisher(""), status("available") {}
LibraryItem::LibraryItem(const std::string &t, const std::string &i, const std::string &p, const std::string &s)
    : title(t), ISBN(i), publisher(p), status(s) {}

// Getters
std::string LibraryItem::getTitle() const { return title; }
std::string LibraryItem::getISBN() const { return ISBN; }
std::string LibraryItem::getPublisher() const { return publisher; }
std::string LibraryItem::getStatus() const { return status; }

// Setters
void LibraryItem::setTitle(const std::string &t) { title = t; }
void LibraryItem::setISBN(const std::string &i) { ISBN = i; }
void LibraryItem::setPublisher(const std::string &p) { publisher = p; }
void LibraryItem::setStatus(const std::string &s) { status = s; }
