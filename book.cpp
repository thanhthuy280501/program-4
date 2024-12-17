#ifndef BOOK_H
#define BOOK_H

#include "LibraryItem.h"

class Book : public LibraryItem {
private:
    std::string author;

public:
    // Constructors
    Book();
    Book(const std::string &t, const std::string &i, const std::string &p, const std::string &a, const std::string &s = "available");

    // Overridden Virtual Functions
    virtual void displayDetails() const override;
    virtual void borrowItem() override;
    virtual void returnItem() override;
    virtual void updateItem() override;
    virtual void newItem() override;
    virtual std::string getType() const override;

    // Getters and Setters
    virtual std::string getAuthor() const override;
    virtual void setAuthor(const std::string &a) override;
};

#endif
