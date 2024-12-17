#include "link.h"
#include "llist.h"
#include "llist.cpp"
#include "LibraryItem.h"
#include "Book.h"
#include "Book.cpp"
#include "DVD.h"
#include "DVD.cpp"
#include "Member.h"
#include "Member.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // For sorting
using namespace std;
//***************************************************************************
// Name:         Thi Thanh Thuy Nguyen
// Program:      CSC 275 Program 5
// Due Date:     12/16/24
// Compiler:     C Lion
// ***************************************************************************
// This program is to deepen the understanding of the use of
// inheritance, with a little bit of emphasis on polymorphism 
// and how to implement generic data structures using 
// templates and manage data using linked structures (i.e. through a linked list)
//******************************************************************************

// Custom Exceptions
class ItemNotFoundException : public exception {
public:
    const char *what() const noexcept override {
        return "Error: Item not found!";
    }
};

class DuplicateItemException : public exception {
public:
    const char *what() const noexcept override {
        return "Error: Item already exists!";
    }
};



// Function prototypes
void loadLibrary(const string &filename, LList<LibraryItem *> &libList);
void saveLibrary(const string &filename, const LList<LibraryItem *> &libList);
void newItem(LList<LibraryItem *> &libList);
void updateItem(LList<LibraryItem *> &libList);
void displayLibrary(const LList<LibraryItem *> &libList);
void infoItem(const LList<LibraryItem *> &libList);

int main(int argc, char *argv[]) {
    // Command-line argument handling
    string libInput = "library01.txt";
    string libOutput = "lout.txt";

    try {
        if (argc != 3) {
            throw invalid_argument("Incorrect arguments. Defaulting to library01.txt and lout.txt.");
        } else {
            libInput = argv[1];
            libOutput = argv[2];
        }
    } catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }

    LList<LibraryItem *> library; // Single list for polymorphic library items
    loadLibrary(libInput, library);

    string command;
    while (true) {
        cout << "\nEnter command (info, library, newitem, update, quit): ";
        cin >> command;
        cin.ignore(); // Clear input buffer

        if (command == "info") {
            infoItem(library);
        } else if (command == "library") {
            displayLibrary(library);
        } else if (command == "newitem") {
            newItem(library);
        } else if (command == "update") {
            updateItem(library);
        } else if (command == "quit") {
            saveLibrary(libOutput, library);
            cout << "Library saved. Exiting program." << endl;
            break;
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}

// Load Library from File
void loadLibrary(const string &filename, LList<LibraryItem *> &libList) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string type, title, isbn, publisher, status, author, director;
    int runtime;

    while (inFile >> type) {
        inFile.ignore(); // Ignore newline
        getline(inFile, title);
        getline(inFile, isbn);
        getline(inFile, publisher);
        getline(inFile, status);

        if (type == "book") {
            getline(inFile, author);
            LibraryItem *newBook = new Book(title, isbn, publisher, author, status);
            libList.sortedInsert(newBook);
        } else if (type == "dvd") {
            getline(inFile, director);
            inFile >> runtime;
            inFile.ignore();
            LibraryItem *newDVD = new DVD(title, isbn, publisher, director, runtime, status);
            libList.sortedInsert(newDVD);
        }
    }
    cout << "Library loaded successfully." << endl;
}

// Save Library to File
void saveLibrary(const string &filename, const LList<LibraryItem *> &libList) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Could not open file for saving." << endl;
        return;
    }

    LibraryItem *item;
    for (libList.setStart(); libList.getValue(item); libList.next()) {
        outFile << item->getType() << endl;
        outFile << item->getTitle() << endl;
        outFile << item->getISBN() << endl;
        outFile << item->getPublisher() << endl;
        outFile << item->getStatus() << endl;

        if (item->getType() == "book") {
            outFile << item->getAuthor() << endl;
        } else if (item->getType() == "dvd") {
            outFile << item->getDirector() << endl;
            outFile << item->getRuntime() << endl;
        }
    }
    cout << "Library saved successfully." << endl;
}

// Add New Item
void newItem(LList<LibraryItem *> &libList) {
    string type;
    cout << "Enter item type (book/dvd): ";
    cin >> type;
    cin.ignore();

    LibraryItem *newItem;
    try {
        if (type == "book") {
            newItem = new Book();
        } else if (type == "dvd") {
            newItem = new DVD();
        } else {
            cout << "Invalid item type!" << endl;
            return;
        }

        newItem->newItem();
        if (libList.search(newItem)) {
            throw DuplicateItemException();
        }
        libList.sortedInsert(newItem);
        cout << "New item added successfully." << endl;
    } catch (const DuplicateItemException &e) {
        cerr << e.what() << endl;
        delete newItem; // Avoid memory leak
    }
}

// Update Item
void updateItem(LList<LibraryItem *> &libList) {
    string isbn;
    cout << "Enter ISBN of item to update: ";
    getline(cin, isbn);

    LibraryItem *item = libList.search(isbn);
    if (item) {
        item->updateItem();
        cout << "Item updated successfully." << endl;
    } else {
        cerr << "Error: Item not found!" << endl;
    }
}

// Display Library
void displayLibrary(const LList<LibraryItem *> &libList) {
    LibraryItem *item;
    for (libList.setStart(); libList.getValue(item); libList.next()) {
        item->displayDetails();
        cout << "----------------------" << endl;
    }
}

// Info Command
void infoItem(const LList<LibraryItem *> &libList) {
    string isbn;
    cout << "Enter ISBN: ";
    getline(cin, isbn);

    LibraryItem *item = libList.search(isbn);
    if (item) {
        item->displayDetails();
    } else {
        throw ItemNotFoundException();
    }
}
