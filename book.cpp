#include "Book.h"
#include <iostream>
using namespace std;

// Default Constructor
Book::Book() : LibraryItem(), author("") {}

// Parameterized Constructor
Book::Book(const string &t, const string &i, const string &p, const string &a, const string &s)
    : LibraryItem(t, i, p, s), author(a) {}

// Display Book Details
void Book::displayDetails() const {
    cout << "Type: Book\n"
         << "Title: " << title << "\n"
         << "Author: " << author << "\n"
         << "ISBN: " << ISBN << "\n"
         << "Publisher: " << publisher << "\n"
         << "Status: " << status << endl;
}

// Borrow a Book
void Book::borrowItem() {
    if (status == "available") {
        status = "borrowed";
        cout << "Book '" << title << "' has been borrowed." << endl;
    } else {
        cout << "Book '" << title << "' is already borrowed." << endl;
    }
}

// Return a Book
void Book::returnItem() {
    if (status == "borrowed") {
        status = "available";
        cout << "Book '" << title << "' has been returned." << endl;
    } else {
        cout << "Book '" << title << "' was not borrowed." << endl;
    }
}

// Update Book Details
void Book::updateItem() {
    cout << "Updating Book Information:" << endl;
    cout << "Enter new title: ";
    getline(cin, title);
    cout << "Enter new author: ";
    getline(cin, author);
    cout << "Enter new publisher: ";
    getline(cin, publisher);
    cout << "Enter new status (available/borrowed): ";
    getline(cin, status);
}

// Add a New Book
void Book::newItem() {
    cout << "Adding New Book:" << endl;
    cout << "Enter title: ";
    getline(cin, title);
    cout << "Enter author: ";
    getline(cin, author);
    cout << "Enter ISBN: ";
    getline(cin, ISBN);
    cout << "Enter publisher: ";
    getline(cin, publisher);
    status = "available";
}

// Get Type
string Book::getType() const {
    return "book";
}

// Get Author
string Book::getAuthor() const {
    return author;
}

// Set Author
void Book::setAuthor(const string &a) {
    author = a;
}
