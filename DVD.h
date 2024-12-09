#ifndef DVD_H
#define DVD_H

#include "LibraryItem.h"

class DVD : public LibraryItem {
private:
    std::string director;
    int runtime; // in minutes

public:
    // Constructors and Destructor
    DVD();
    DVD(const std::string &t, const std::string &d, int r, const std::string &i, const std::string &p, const std::string &s = "available");
    ~DVD() {}

    // Getters and Setters
    std::string getDirector() const;
    void setDirector(const std::string &d);
    int getRuntime() const;
    void setRuntime(int r);

    // Overridden Functions
    void displayDetails() const override;
    void borrowItem() override;
    void returnItem() override;
};

#endif
