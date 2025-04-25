#pragma once
#include <string>
#include <vector>
#include <iostream>

class Media {
protected:
    char type;
    std::string title;
    std::string name;
    int rating;
    std::string genre;
    int length;
    int yearReleased;

public:
    Media();
    Media(char t, std::string ti, std::string n, int r, std::string g, int l, int yr);

    // Getters
    char getType() const;
    std::string getTitle() const;
    std::string getName() const;
    int getRating() const;
    std::string getGenre() const;
    int getLength() const;
    int getYearReleased() const;

    // Setters
    void setType(char t);
    void setTitle(std::string t);
    void setName(std::string n);
    void setRating(int r);
    void setGenre(std::string g);
    void setLength(int l);
    void setYearReleased(int yr);

    // Pure virtual print function
    virtual void print(std::ostream&, const std::vector<Media*>&) const = 0;
};
