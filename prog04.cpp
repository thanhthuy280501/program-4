
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
#include <string>
#include <vector>
using namespace std;



using namespace std;

// Function prototypes
void updateBook(Book &book);
void convertTitleToUppercase(Book &book);
void convertTitleToLowercase(Book &book);
void convertAuthorToUppercase(Book &book);
void convertAuthorToLowercase(Book &book);

int main(int argc, char *argv[]) {
    LList<Book> bookList;
    LList<DVD> dvdList;
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <library_input> <library_output> <member_input> <member_output>" << endl;
        return 1;
    }

    string libraryInputFile = argv[1];
    string libraryOutputFile = argv[2];
    string memberInputFile = argv[3];
    string memberOutputFile = argv[4];

    vector<Book> library; // Dynamically allocated library array
    vector<Member> members; // Dynamically allocated member array
    Member *currentMember = nullptr; // Pointer to track the active member

    cout << "Loading books from file..." << endl;
    loadBooksFromFile(libraryInputFile, library);
    cout << "Loading members from file..." << endl;
    loadMembersFromFile(memberInputFile, members);

    string command;
    while (true) {
        cout << "Enter command (borrow, return, account, newbook, updatebook, titleupper, titlelower, authorupper, authorlower, search, library, memberlist, sortlibrary, sortmembers, switch, quit): ";
        cin >> command;

        if (command == "borrow") {
            string isbn;
            cout << "Enter ISBN to borrow: ";
            cin >> isbn;

            LibraryItem* item = bookList.search(isbn); // Search in books
            if (!item) item = dvdList.search(isbn);   // Search in DVDs

            if (item) {
                item->borrowItem(); // Mark as borrowed
            } else {
                cerr << "Item not found in the library.\n";
            }
        } 
        else if (command == "return") {
    string isbn;
    cout << "Enter ISBN to return: ";
    cin >> isbn;

    LibraryItem* item = bookList.search(isbn); // Search in books
    if (!item) item = dvdList.search(isbn);   // Search in DVDs

    if (item) {
        item->returnItem(); // Mark as available
    } else {
        cerr << "Item not found in the library.\n";
    }

        } 
        else if (command == "switch") {
            switchMember(members, currentMember);
        } 
        else if (command == "sortlibrary") {
            sortLibrary(library);
            cout << "Library sorted by ISBN." << endl;
        } 
        else if (command == "sortmembers") {
            sortMembers(members);
            cout << "Members sorted by last name." << endl;
        } 
        else if (command == "search") {
            string isbn;
            cout << "Enter ISBN to search: ";
            cin >> isbn;
            Book *book = searchBookByISBN(library, isbn);
            if (book) {
                cout << "Book found: " << *book << endl;
            } else {
                cout << "Book not found." << endl;
            }
        } 
        else if (command == "library") {
            for (const auto &book : library) {
                cout << book.getISBN() << ": " << book << endl;
            }
        else if (command == "updatedvd") {
    string isbn;
    cout << "Enter ISBN of the DVD to update: ";
    cin >> isbn;

    DVD* dvd = dvdList.search(isbn);
    if (dvd) {
        string title, director, studio;
        int runtime;

        cout << "Current Title: " << dvd->getTitle() << endl;
        cout << "Enter New Title (leave blank to keep current): ";
        cin.ignore();
        getline(cin, title);
        if (!title.empty()) dvd->setTitle(title);

        cout << "Current Director: " << dvd->getDirector() << endl;
        cout << "Enter New Director (leave blank to keep current): ";
        getline(cin, director);
        if (!director.empty()) dvd->setDirector(director);

        cout << "Current Runtime: " << dvd->getRuntime() << " minutes\n";
        cout << "Enter New Runtime (leave blank to keep current): ";
        string runtimeStr;
        getline(cin, runtimeStr);
        if (!runtimeStr.empty()) dvd->setRuntime(stoi(runtimeStr));

        cout << "Current Studio: " << dvd->getPublisher() << endl;
        cout << "Enter New Studio (leave blank to keep current): ";
        getline(cin, studio);
        if (!studio.empty()) dvd->setPublisher(studio);

        cout << "DVD details updated successfully.\n";
    } 
    else {
        cerr << "DVD not found.\n";
    }
}
    else if (command == "info") {
    string isbn;
    cout << "Enter ISBN to display details: ";
    cin >> isbn;

    LibraryItem* item = bookList.search(isbn); // Search in books
    if (!item) item = dvdList.search(isbn);   // Search in DVDs

    if (item) {
        item->displayDetails(); // Call the polymorphic display function
    } else {
        cerr << "Item not found.\n";
    }
}


        } else if (command == "memberlist") {
            for (const auto &member : members) {
                cout << member << endl;
            }
        else if (command == "newdvd") {
    string title, director, isbn, studio;
    int runtime;

    cout << "Enter DVD Title: ";
    cin.ignore(); // Clear input buffer
    getline(cin, title);

    cout << "Enter Director: ";
    getline(cin, director);

    cout << "Enter ISBN: ";
    cin >> isbn;

    cout << "Enter Studio: ";
    cin.ignore();
    getline(cin, studio);

    cout << "Enter Runtime (in minutes): ";
    cin >> runtime;

    DVD newDvd(title, director, runtime, isbn, studio);
    dvdList.append(newDvd);
    cout << "New DVD added successfully.\n";
}

        } else if (command == "quit") {
            cout << "Saving books to file..." << endl;
            saveBooksToFile(libraryOutputFile, library);
            cout << "Saving members to file..." << endl;
            saveMembersToFile(memberOutputFile, members);
            break;
        } else {
            cout << "Invalid command or no member selected." << endl;
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
    if (!newTitle.empty()) {
        book.setTitle(newTitle);
    }

    cout << "Current author: " << book.getAuthor() << endl;
    cout << "Enter new author (leave blank to keep current): ";
    getline(cin, newAuthor);
    if (!newAuthor.empty()) {
        book.setAuthor(newAuthor);
    }

    cout << "Current ISBN: " << book.getISBN() << endl;
    cout << "Enter new ISBN (leave blank to keep current): ";
    getline(cin, newISBN);
    if (!newISBN.empty()) {
        book.setISBN(newISBN);
    }

    cout << "Current publisher: " << book.getPublisher() << endl;
    cout << "Enter new publisher (leave blank to keep current): ";
    getline(cin, newPublisher);
    if (!newPublisher.empty()) {
        book.setPublisher(newPublisher);
    }
}

// Convert title to uppercase
void convertTitleToUppercase(Book &book) {
    book.convertTitleToUppercase();
    cout << "Updated title to uppercase: " << book.getTitle() << endl;
}

// Convert title to lowercase
void convertTitleToLowercase(Book &book) {
    book.convertTitleToLowercase();
    cout << "Updated title to lowercase: " << book.getTitle() << endl;
}

// Convert author to uppercase
void convertAuthorToUppercase(Book &book) {
    book.convertAuthorToUppercase();
    cout << "Updated author to uppercase: " << book.getAuthor() << endl;
}

// Convert author to lowercase
void convertAuthorToLowercase(Book &book) {
    book.convertAuthorToLowercase();
    cout << "Updated author to lowercase: " << book.getAuthor() << endl;
}
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
