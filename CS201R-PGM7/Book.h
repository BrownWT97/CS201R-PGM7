#pragma once
#include "Media.h"

class Book : public Media {
private:
    int weeksNYT;

public:
    Book();
    Book(char t, std::string ti, std::string n, int r, std::string g, int l, int yr, int w);

    // Getters
    int getWeeksNYT() const;

    // Setters
    void setWeeksNYT(int w);

    // Print function
    void print(std::ostream&, const std::vector<Media*>&) const override;
};