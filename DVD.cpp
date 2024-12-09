#include "DVD.h"
#include <iostream>

// Constructors
DVD::DVD() : LibraryItem(), director(""), runtime(0) {}
DVD::DVD(const std::string &t, const std::string &d, int r, const std::string &i, const std::string &p, const std::string &s)
    : LibraryItem(t, i, p, s), director(d), runtime(r) {}

// Getters and Setters
std::string DVD::getDirector() const { return director; }
void DVD::setDirector(const std::string &d) { director = d; }
int DVD::getRuntime() const { return runtime; }
void DVD::setRuntime(int r) { runtime = r; }

// Overridden Functions
void DVD::displayDetails() const {
    std::cout << "DVD Details:\n"
              << "Title: " << title << "\n"
              << "Director: " << director << "\n"
              << "Runtime: " << runtime << " minutes\n"
              << "ISBN: " << ISBN << "\n"
              << "Studio: " << publisher << "\n"
              << "Status: " << status << "\n";
}

void DVD::borrowItem() {
    if (status == "available") {
        status = "borrowed";
        std::cout << "DVD borrowed successfully.\n";
    } else {
        std::cout << "DVD is already borrowed.\n";
    }
}

void DVD::returnItem() {
    if (status == "borrowed") {
        status = "available";
        std::cout << "DVD returned successfully.\n";
    } else {
        std::cout << "DVD is already available.\n";
    }
}
