#include "Book.h"
#include <iostream>
#include <iomanip>
using namespace std;

Book::Book() : Media(), weeksNYT(0) {}

Book::Book(char t, string ti, string n, int r, string g, int l, int yr, int w)
    : Media(t, ti, n, r, g, l, yr), weeksNYT(w) {
}

int Book::getWeeksNYT() const { return weeksNYT; }

void Book::setWeeksNYT(int w) { weeksNYT = w; }

void Book::print(ostream& os, const vector<Media*>&) const {
    os << left << setw(50) << title
        << setw(30) << name
        << setw(15) << genre
        << setw(10) << rating
        << setw(10) << length
        << setw(10) << yearReleased
        << " WeeksNYT: " << weeksNYT << endl;
}