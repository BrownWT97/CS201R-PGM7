#include "Song.h"
#include <iostream>
#include <iomanip>
using namespace std;

Song::Song() : Media(), top40(false) {}

Song::Song(char t, string ti, string n, int r, string g, int l, int yr, bool top)
    : Media(t, ti, n, r, g, l, yr), top40(top) {
}

bool Song::getTop40() const { return top40; }

void Song::setTop40(bool top) { top40 = top; }

void Song::print(ostream& os, const vector<Media*>&) const {
    os << left << setw(50) << title
        << setw(30) << name
        << setw(15) << genre
        << setw(10) << rating
        << setw(10) << length
        << setw(10) << yearReleased
        << " Top40: " << (top40 ? "Yes" : "No") << endl;
}