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
// Program:      CSC 275 Program 4
// Due Date:     12/09/24
// Compiler:     C Lion
// ***************************************************************************
// This program is to deepen the understanding of the use of
// inheritance, with a little bit of emphasis on polymorphism 
// and how to implement generic data structures using 
// templates and manage data using linked structures (i.e. through a linked list)
//******************************************************************************

// Function prototypes
void updateBook(Book &book);
void loadBooksFromFile(const string &filename, vector<Book> &library);
void saveBooksToFile(const string &filename, const vector<Book> &library);
void switchMember(vector<Member> &members, Member *&currentMember);

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <library_input> <library_output> <member_input> <member_output>" << endl;
        return 1;
    }

    string libraryInputFile = argv[1];
    string libraryOutputFile = argv[2];
    string memberInputFile = argv[3];
    string memberOutputFile = argv[4];

    vector<Book> library;
    vector<Member> members;
    LList<Book> bookList;
    LList<DVD> dvdList;
    Member *currentMember = nullptr;

    cout << "Loading books from file..." << endl;
    loadBooksFromFile(libraryInputFile, library);
    cout << "Loading members from file..." << endl;

    string command;
    while (true) {
        cout << "Enter command (borrow, return, info, sortlibrary, quit): ";
        cin >> command;

        if (command == "borrow") {
            string isbn;
            cout << "Enter ISBN to borrow: ";
            cin >> isbn;

            LibraryItem* item = bookList.search(isbn);
            if (!item) item = dvdList.search(isbn);

            if (item) {
                item->borrowItem();
            } else {
                cerr << "Item not found in the library.\n";
            }
        } 
        else if (command == "return") {
            string isbn;
            cout << "Enter ISBN to return: ";
            cin >> isbn;

            LibraryItem* item = bookList.search(isbn);
            if (!item) item = dvdList.search(isbn);

            if (item) {
                item->returnItem();
            } else {
                cerr << "Item not found in the library.\n";
            }
        } 
        else if (command == "info") {
            string isbn;
            cout << "Enter ISBN to display details: ";
            cin >> isbn;

            LibraryItem* item = bookList.search(isbn);
            if (!item) item = dvdList.search(isbn);

            if (item) {
                item->displayDetails();
            } else {
                cerr << "Item not found.\n";
            }
        } 
        else if (command == "sortlibrary") {
            sort(library.begin(), library.end(), [](const Book &a, const Book &b) {
                return a.getISBN() < b.getISBN();
            });
            cout << "Library sorted by ISBN." << endl;
        } 
        else if (command == "quit") {
            cout << "Saving books to file..." << endl;
            saveBooksToFile(libraryOutputFile, library);
            break;
        } 
        else {
            cerr << "Invalid command." << endl;
        }
    }

    return 0;
}

// Update book details
void updateBook(Book &book) {
    string newTitle, newAuthor, newISBN, newPublisher;
    cout << "Current title: " << book.getTitle() << endl;
    cout << "Enter new title (leave blank to keep current): ";
    cin.ignore();
    getline(cin, newTitle);
    if (!newTitle.empty()) book.setTitle(newTitle);

    cout << "Current author: " << book.getAuthor() << endl;
    cout << "Enter new author (leave blank to keep current): ";
    getline(cin, newAuthor);
    if (!newAuthor.empty()) book.setAuthor(newAuthor);

    cout << "Current ISBN: " << book.getISBN() << endl;
    cout << "Enter new ISBN (leave blank to keep current): ";
    getline(cin, newISBN);
    if (!newISBN.empty()) book.setISBN(newISBN);

    cout << "Current publisher: " << book.getPublisher() << endl;
    cout << "Enter new publisher (leave blank to keep current): ";
    getline(cin, newPublisher);
    if (!newPublisher.empty()) book.setPublisher(newPublisher);
}

// Load books from file
void loadBooksFromFile(const string &filename, vector<Book> &library) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open the book file." << endl;
        return;
    }

    string title, author, isbn, publisher;
    while (getline(infile, title) && getline(infile, author) && getline(infile, isbn) && getline(infile, publisher)) {
        library.emplace_back(title, author, isbn, publisher);
    }
    infile.close();
}

// Save books to file
void saveBooksToFile(const string &filename, const vector<Book> &library) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open the book file for writing." << endl;
        return;
    }

    for (const auto &book : library) {
        outfile << book.getTitle() << endl;
        outfile << book.getAuthor() << endl;
        outfile << book.getISBN() << endl;
        outfile << book.getPublisher() << endl;
    }
    outfile.close();
}

Book *searchBookByISBN(vector<Book> &library, const string &isbn, int index = 0) {
    if (index >= library.size()) return nullptr;
    if (library[index].getISBN() == isbn) return &library[index];
    return searchBookByISBN(library, isbn, index + 1);
}
Book* binarySearchByISBN(vector<Book> &library, const string &isbn, int left, int right) {
    if (left > right) {
        return nullptr; // Base case: ISBN not found
    }

    int mid = left + (right - left) / 2; // Calculate mid-point

    if (library[mid].getISBN() == isbn) {
        return &library[mid]; // ISBN found
    } else if (library[mid].getISBN() > isbn) {
        return binarySearchByISBN(library, isbn, left, mid - 1); // Search left half
    } else {
        return binarySearchByISBN(library, isbn, mid + 1, right); // Search right half
    }
}
else if (command == "search") {
    string isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;

    if (library.empty()) {
        cout << "The library is empty. Please add books first." << endl;
        continue;
    }

    if (!is_sorted(library.begin(), library.end(), [](const Book &a, const Book &b) {
        return a.getISBN() < b.getISBN();
    })) {
        cout << "Error: Library is not sorted. Please use the sortlibrary command first." << endl;
        continue;
    }

    Book* foundBook = binarySearchByISBN(library, isbn, 0, library.size() - 1);
    if (foundBook) {
        cout << "Book found: " << *foundBook << endl;
    } else {
        cout << "Book not found." << endl;
    }
}


    return 0;
}
