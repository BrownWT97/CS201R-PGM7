#include "Movie.h"
#include <iostream>
#include <iomanip>
using namespace std;

Movie::Movie() : Media(), stars() {}

Movie::Movie(char t, string ti, string n, int r, string g, int l, int yr, const vector<string>& s)
    : Media(t, ti, n, r, g, l, yr), stars(s) {
}

vector<string> Movie::getStars() const { return stars; }

void Movie::setStars(const vector<string>& s) { stars = s; }

void Movie::print(ostream& os, const vector<Media*>&) const {
    os << left << setw(50) << title
        << setw(30) << name
        << setw(15) << genre
        << setw(10) << rating
        << setw(10) << length
        << setw(10) << yearReleased;
    for (const auto& star : stars) {
        os << " " << star;
    }
    os << endl;
}