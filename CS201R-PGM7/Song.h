#pragma once
#include "Media.h"

class Song : public Media {
private:
    bool top40;

public:
    Song();
    Song(char t, std::string ti, std::string n, int r, std::string g, int l, int yr, bool top);

    // Getters
    bool getTop40() const;

    // Setters
    void setTop40(bool top);

    // Print function
    void print(std::ostream&, const std::vector<Media*>&) const override;
};