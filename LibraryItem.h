#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <string>
#include <iostream>

class LibraryItem {
protected:
    std::string title;
    std::string ISBN;
    std::string publisher;
    std::string status; // "available" or "borrowed"

public:
    // Constructors and Destructor
    LibraryItem();
    LibraryItem(const std::string &t, const std::string &i, const std::string &p, const std::string &s = "available");
    virtual ~LibraryItem() {}

    // Getters
    std::string getTitle() const;
    std::string getISBN() const;
    std::string getPublisher() const;
    std::string getStatus() const;

    // Setters
    void setTitle(const std::string &t);
    void setISBN(const std::string &i);
    void setPublisher(const std::string &p);
    void setStatus(const std::string &s);

    // Additional Virtual Getters for Derived Classes
    virtual std::string getAuthor() const { return ""; }
    virtual std::string getDirector() const { return ""; }
    virtual int getRuntime() const { return 0; }

    virtual void setAuthor(const std::string &a) {}
    virtual void setDirector(const std::string &d) {}
    virtual void setRuntime(int r) {}

    // Virtual Functions
    virtual void displayDetails() const = 0;
    virtual void borrowItem() = 0;
    virtual void returnItem() = 0;
    virtual void updateItem() = 0;
    virtual void newItem() = 0;

    virtual std::string getType() const = 0; // "book" or "dvd"

    // Operator Overloads
    virtual bool operator==(const LibraryItem &other) const;
    virtual bool operator!=(const LibraryItem &other) const;
    virtual bool operator<=(const LibraryItem &other) const;
};

#endif
