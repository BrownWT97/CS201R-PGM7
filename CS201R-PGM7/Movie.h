#pragma once
#include "Media.h"
#include <vector>
#include <string>

class Movie : public Media {
private:
    std::vector<std::string> stars;

public:
    Movie();
    Movie(char t, std::string ti, std::string n, int r, std::string g, int l, int yr, const std::vector<std::string>& s);

    // Getters
    std::vector<std::string> getStars() const;

    // Setters
    void setStars(const std::vector<std::string>& s);

    // Print function
    void print(std::ostream&, const std::vector<Media*>&) const override;
};
