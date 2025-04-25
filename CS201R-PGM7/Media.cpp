#include "Media.h"
using namespace std;

Media::Media() : type(' '), title(""), name(""), rating(-1), genre(""), length(-1), yearReleased(-1) {}

Media::Media(char t, string ti, string n, int r, string g, int l, int yr)
    : type(t), title(ti), name(n), rating(r), genre(g), length(l), yearReleased(yr) {
}

// Getters
char Media::getType() const { return type; }
string Media::getTitle() const { return title; }
string Media::getName() const { return name; }
int Media::getRating() const { return rating; }
string Media::getGenre() const { return genre; }
int Media::getLength() const { return length; }
int Media::getYearReleased() const { return yearReleased; }

// Setters
void Media::setType(char t) { type = t; }
void Media::setTitle(string t) { title = t; }
void Media::setName(string n) { name = n; }
void Media::setRating(int r) { rating = r; }
void Media::setGenre(string g) { genre = g; }
void Media::setLength(int l) { length = l; }
void Media::setYearReleased(int yr) { yearReleased = yr; }