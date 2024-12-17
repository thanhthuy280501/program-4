#ifndef DVD_H
#define DVD_H

#include "LibraryItem.h"

class DVD : public LibraryItem {
private:
    std::string director;
    int runtime; // in minutes

public:
    // Constructors
    DVD();
    DVD(const std::string &t, const std::string &i, const std::string &p, const std::string &d, int r, const std::string &s = "available");

    // Overridden Virtual Functions
    virtual void displayDetails() const override;
    virtual void borrowItem() override;
    virtual void returnItem() override;
    virtual void updateItem() override;
    virtual void newItem() override;
    virtual std::string getType() const override;

    // Getters and Setters
    virtual std::string getDirector() const override;
    virtual int getRuntime() const override;
    virtual void setDirector(const std::string &d) override;
    virtual void setRuntime(int r) override;
};

#endif
