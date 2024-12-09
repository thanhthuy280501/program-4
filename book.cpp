#include "Book.h"
#include <algorithm>
#include <iostream>

Book::Book() : title(""), author(""), ISBN(""), publisher("") {}

Book::Book(string t, string a, string i, string p)
    : title(t), author(a), ISBN(i), publisher(p) {}

Book::~Book() {}
// Constructors
Book::Book() : LibraryItem(), author("") {}
Book::Book(const std::string &t, const std::string &a, const std::string &i, const std::string &p, const std::string &s)
    : LibraryItem(t, i, p, s), author(a) {}

// Getters
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return ISBN; }
string Book::getPublisher() const { return publisher; }

// Setters
void Book::setTitle(const string &t) { title = t; }
void Book::setAuthor(const string &a) { author = a; }
void Book::setISBN(const string &i) { ISBN = i; }
void Book::setPublisher(const string &p) { publisher = p; }

// String Manipulation
void Book::convertTitleToUppercase() {
    transform(title.begin(), title.end(), title.begin(), ::toupper);
}

void Book::convertTitleToLowercase() {
    transform(title.begin(), title.end(), title.begin(), ::tolower);
}

void Book::convertAuthorToUppercase() {
    transform(author.begin(), author.end(), author.begin(), ::toupper);
}

void Book::convertAuthorToLowercase() {
    transform(author.begin(), author.end(), author.begin(), ::tolower);
}

// Overloaded Operators
bool Book::operator==(const Book &other) const { return ISBN == other.ISBN; }
bool Book::operator!=(const Book &other) const { return ISBN != other.ISBN; }
ostream &operator<<(ostream &os, const Book &book) {
    os << book.title << " by " << book.author << ", ISBN: " << book.ISBN
       << ", Publisher: " << book.publisher;
    return os;
}
void sortLibrary(vector<Book> &library) {
    sort(library.begin(), library.end(), [](const Book &a, const Book &b) {
        return a.getISBN() < b.getISBN();
    });
}
Book *searchBookByISBN(vector<Book> &library, const string &isbn, int index = 0) {
    if (index >= library.size()) return nullptr;
    if (library[index].getISBN() == isbn) return &library[index];
    return searchBookByISBN(library, isbn, index + 1);
}
// Overridden Functions
void Book::displayDetails() const {
    std::cout << "Book Details:\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << ISBN << "\n"
              << "Publisher: " << publisher << "\n"
              << "Status: " << status << "\n";
}
void Book::borrowItem() {
    if (status == "available") {
        status = "borrowed";
        std::cout << "Book borrowed successfully.\n";
    } else {
        std::cout << "Book is already borrowed.\n";
    }
}

void Book::returnItem() {
    if (status == "borrowed") {
        status = "available";
        std::cout << "Book returned successfully.\n";
    } else {
        std::cout << "Book is already available.\n";
    }
}

