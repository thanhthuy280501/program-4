#ifndef BOOK_H
#define BOOK_H
#include "LibraryItem.h"
#include <string>
#include <iostream>
using namespace std;

class Book : : public LibraryItem {
private:
    string title;
    string author;
    string ISBN;
    string publisher;
    std::string author;

public:
    // Constructors and Destructor
    Book();
    Book(const std::string &t, const std::string &a, const std::string &i, const std::string &p, const std::string &s = "available");
    ~Book() {}

    // Getters and Setter for Author
    string getTitle() const;
    string getAuthor() const;
    string getISBN() const;
    string getPublisher() const;
    std::string getAuthor() const;
    void setAuthor(const std::string &a);

    // Setters
    void setTitle(const string &t);
    void setAuthor(const string &a);
    void setISBN(const string &i);
    void setPublisher(const string &p);

    // String Manipulation
    void convertTitleToUppercase();
    void convertTitleToLowercase();
    void convertAuthorToUppercase();
    void convertAuthorToLowercase();

    // Overloaded Operators
    bool operator==(const Book &other) const;
    bool operator!=(const Book &other) const;
    friend ostream &operator<<(ostream &os, const Book &book);

    // Overridden Functions
    void displayDetails() const override;
    void borrowItem() override;
    void returnItem() override;
};


#endif
