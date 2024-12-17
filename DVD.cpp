#include "DVD.h"
#include <iostream>
using namespace std;

// Default Constructor
DVD::DVD() : LibraryItem(), director(""), runtime(0) {}

// Parameterized Constructor
DVD::DVD(const string &t, const string &i, const string &p, const string &d, int r, const string &s)
    : LibraryItem(t, i, p, s), director(d), runtime(r) {}

// Display DVD Details
void DVD::displayDetails() const {
    cout << "Type: DVD\n"
         << "Title: " << title << "\n"
         << "Director: " << director << "\n"
         << "Runtime: " << runtime << " minutes\n"
         << "ISBN: " << ISBN << "\n"
         << "Publisher: " << publisher << "\n"
         << "Status: " << status << endl;
}

// Borrow a DVD
void DVD::borrowItem() {
    if (status == "available") {
        status = "borrowed";
        cout << "DVD '" << title << "' has been borrowed." << endl;
    } else {
        cout << "DVD '" << title << "' is already borrowed." << endl;
    }
}

// Return a DVD
void DVD::returnItem() {
    if (status == "borrowed") {
        status = "available";
        cout << "DVD '" << title << "' has been returned." << endl;
    } else {
        cout << "DVD '" << title << "' was not borrowed." << endl;
    }
}

// Update DVD Details
void DVD::updateItem() {
    cout << "Updating DVD Information:" << endl;
    cout << "Enter new title: ";
    getline(cin, title);
    cout << "Enter new director: ";
    getline(cin, director);
    cout << "Enter new runtime: ";
    cin >> runtime;
    cin.ignore();
    cout << "Enter new status (available/borrowed): ";
    getline(cin, status);
}

// Add a New DVD
void DVD::newItem() {
    cout << "Adding New DVD:" << endl;
    cout << "Enter title: ";
    getline(cin, title);
    cout << "Enter director: ";
    getline(cin, director);
    cout << "Enter runtime: ";
    cin >> runtime;
    cin.ignore();
    cout << "Enter ISBN: ";
    getline(cin, ISBN);
    cout << "Enter publisher: ";
    getline(cin, publisher);
    status = "available";
}

// Get Type
string DVD::getType() const {
    return "dvd";
}

// Get Director
string DVD::getDirector() const {
    return director;
}

// Get Runtime
int DVD::getRuntime() const {
    return runtime;
}

// Set Director
void DVD::setDirector(const string &d) {
    director = d;
}

// Set Runtime
void DVD::setRuntime(int r) {
    runtime = r;
}
