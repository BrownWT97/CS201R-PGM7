#include "Functions.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// Helper function to trim leading and trailing whitespace from a string
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

bool isDigits(const string& str1) {
    return str1.find_first_not_of("0123456789") == string::npos;
}

int readMediaList(istream& inFile, ostream& outFile, vector<Media*>& mediaLib) {
    string line;
    int validCount = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, '\t')) {
            tokens.push_back(trim(token));
        }
        if (tokens.empty() || all_of(tokens.begin(), tokens.end(), [](const string& s) { return s.empty(); })) continue;
        if (tokens.size() < 7) {
            outFile << "Invalid record (insufficient fields): " << line << endl;
            continue;
        }
        if (tokens[0].length() != 1 || (tokens[0][0] != 'M' && tokens[0][0] != 'B' && tokens[0][0] != 'S')) {
            outFile << "Invalid type in record: " << line << endl;
            continue;
        }
        char type = tokens[0][0];
        if (tokens[1].empty() || tokens[2].empty() || tokens[4].empty()) {
            outFile << "Missing required field in record: " << line << endl;
            continue;
        }
        int rating, length, year;
        try {
            rating = stoi(tokens[3]);
            length = stoi(tokens[5]);
            year = stoi(tokens[6]);
        }
        catch (const invalid_argument&) {
            outFile << "Non-numeric value in numeric field: " << line << endl;
            continue;
        }
        catch (const out_of_range&) {
            outFile << "Numeric value out of range: " << line << endl;
            continue;
        }
        if (rating < 1 || rating > 10) {
            outFile << "Rating out of range (1-10): " << line << endl;
            continue;
        }
        if (length <= 0) {
            outFile << "Invalid length (must be positive): " << line << endl;
            continue;
        }
        if (year < 1920 || year > 2024) {
            outFile << "Year out of range (1920-2024): " << line << endl;
            continue;
        }
        if (type == 'M') {
            vector<string> stars(tokens.begin() + 7, tokens.end());
            Movie* movie = new Movie(type, tokens[1], tokens[2], rating, tokens[4], length, year, stars);
            mediaLib.push_back(movie);
            validCount++;
        }
        else if (type == 'B') {
            if (tokens.size() != 8) {
                outFile << "Invalid number of fields for Book (expected 8): " << line << endl;
                continue;
            }
            string weeksStr = tokens[7];
            if (!isDigits(weeksStr) || stoi(weeksStr) < 0) {
                outFile << "Invalid weeksNYT for Book: " << line << endl;
                continue;
            }
            int weeks = stoi(weeksStr);
            Book* book = new Book(type, tokens[1], tokens[2], rating, tokens[4], length, year, weeks);
            mediaLib.push_back(book);
            validCount++;
        }
        else if (type == 'S') {
            if (tokens.size() != 8) {
                outFile << "Invalid number of fields for Song (expected 8): " << line << endl;
                continue;
            }
            string top40Str = tokens[7];
            if (top40Str != "0" && top40Str != "1") {
                outFile << "Invalid top40 value for Song (must be 0 or 1): " << line << endl;
                continue;
            }
            bool top40 = (top40Str == "1");
            Song* song = new Song(type, tokens[1], tokens[2], rating, tokens[4], length, year, top40);
            mediaLib.push_back(song);
            validCount++;
        }
    }
    return validCount;
}

void printTotals(ostream& outFile, const vector<Media*>& mediaLib) {
    int movieCount = 0, bookCount = 0, songCount = 0;
    for (const Media* media : mediaLib) {
        switch (media->getType()) {
        case 'M': movieCount++; break;
        case 'B': bookCount++; break;
        case 'S': songCount++; break;
        }
    }
    outFile << "Total Movies: " << movieCount << endl;
    outFile << "Total Books: " << bookCount << endl;
    outFile << "Total Songs: " << songCount << endl;
}

void printReport(const string& commandRecord, ostream& outFile, ostream& errFile, const vector<Media*>& mediaLib) {
    char command = commandRecord[0];
    bool found = false;
    outFile << "Report for command: " << commandRecord << endl;
    outFile << left << setw(50) << "Title" << setw(30) << "Name" << setw(15) << "Genre"
        << setw(10) << "Rating" << setw(10) << "Length" << setw(10) << "Year" << " Additional Info" << endl;
    outFile << string(125, '-') << endl;
    for (const Media* media : mediaLib) {
        if (command == 'A' || media->getType() == command) {
            media->print(outFile, mediaLib);
            found = true;
        }
    }
    if (!found) {
        outFile << "No entries found for command: " << commandRecord << endl;
    }
    outFile << endl;
}

void printReportRating(const string& commandRecord, ostream& outFile, ostream& errFile, const vector<Media*>& mediaLib) {
    stringstream ss(commandRecord);
    string command, ratingStr;
    getline(ss, command, ',');
    getline(ss, ratingStr);
    if (!isDigits(ratingStr)) {
        errFile << "Invalid rating in command: " << commandRecord << endl;
        return;
    }
    int rating = stoi(ratingStr);
    if (rating < 1 || rating > 10) {
        errFile << "Rating out of range in command: " << commandRecord << endl;
        return;
    }
    bool found = false;
    outFile << "Report for command: " << commandRecord << endl;
    outFile << left << setw(50) << "Title" << setw(30) << "Name" << setw(15) << "Genre"
        << setw(10) << "Rating" << setw(10) << "Length" << setw(10) << "Year" << " Additional Info" << endl;
    outFile << string(125, '-') << endl;
    for (const Media* media : mediaLib) {
        if ((command[0] == 'A' || media->getType() == command[0]) && media->getRating() >= rating) {
            media->print(outFile, mediaLib);
            found = true;
        }
    }
    if (!found) {
        outFile << "No entries found for command: " << commandRecord << endl;
    }
    outFile << endl;
}

void printReportGenre(const string& commandRecord, ostream& outFile, ostream& errFile, const vector<Media*>& mediaLib) {
    stringstream ss(commandRecord);
    string command, genre;
    getline(ss, command, ',');
    getline(ss, genre);
    bool found = false;
    outFile << "Report for command: " << commandRecord << endl;
    outFile << left << setw(50) << "Title" << setw(30) << "Name" << setw(15) << "Genre"
        << setw(10) << "Rating" << setw(10) << "Length" << setw(10) << "Year" << " Additional Info" << endl;
    outFile << string(125, '-') << endl;
    for (const Media* media : mediaLib) {
        if ((command[0] == 'A' || media->getType() == command[0]) && media->getGenre() == genre) {
            media->print(outFile, mediaLib);
            found = true;
        }
    }
    if (!found) {
        outFile << "No entries found for command: " << commandRecord << endl;
    }
    outFile << endl;
}

void addContent(const string& commandRecord, ostream& outFile, ostream& errFile, vector<Media*>& mediaLib) {
    stringstream ss(commandRecord);
    vector<string> tokens;
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }
    if (tokens.size() < 8 || tokens[0] != "N") {
        errFile << "Invalid new media command: " << commandRecord << endl;
        return;
    }
    string typeStr = tokens[1];
    if (typeStr.length() != 1 || (typeStr[0] != 'M' && typeStr[0] != 'B' && typeStr[0] != 'S')) {
        errFile << "Invalid type in new media: " << commandRecord << endl;
        return;
    }
    char type = typeStr[0];
    string title = tokens[2];
    string name = tokens[3];
    string ratingStr = tokens[4];
    string genre = tokens[5];
    string lengthStr = tokens[6];
    string yearStr = tokens[7];
    if (!isDigits(ratingStr) || !isDigits(lengthStr) || !isDigits(yearStr)) {
        errFile << "Invalid numeric fields in new media: " << commandRecord << endl;
        return;
    }
    int rating = stoi(ratingStr);
    int length = stoi(lengthStr);
    int year = stoi(yearStr);
    if (rating < 1 || rating > 10 || length <= 0 || year < 1920 || year > 2024) {
        errFile << "Invalid values in new media: " << commandRecord << endl;
        return;
    }
    if (type == 'M') {
        if (tokens.size() < 9) {
            errFile << "Insufficient fields for new Movie: " << commandRecord << endl;
            return;
        }
        vector<string> stars(tokens.begin() + 8, tokens.end());
        Movie* movie = new Movie(type, title, name, rating, genre, length, year, stars);
        mediaLib.push_back(movie);
        outFile << "Added new Movie: " << title << endl;
    }
    else if (type == 'B') {
        if (tokens.size() != 9) {
            errFile << "Invalid number of fields for new Book: " << commandRecord << endl;
            return;
        }
        string weeksStr = tokens[8];
        if (!isDigits(weeksStr) || stoi(weeksStr) < 0) {
            errFile << "Invalid weeksNYT in new Book: " << commandRecord << endl;
            return;
        }
        int weeks = stoi(weeksStr);
        Book* book = new Book(type, title, name, rating, genre, length, year, weeks);
        mediaLib.push_back(book);
        outFile << "Added new Book: " << title << endl;
    }
    else if (type == 'S') {
        if (tokens.size() != 9) {
            errFile << "Invalid number of fields for new Song: " << commandRecord << endl;
            return;
        }
        string top40Str = tokens[8];
        if (top40Str != "0" && top40Str != "1") {
            errFile << "Invalid top40 in new Song: " << commandRecord << endl;
            return;
        }
        bool top40 = (top40Str == "1");
        Song* song = new Song(type, title, name, rating, genre, length, year, top40);
        mediaLib.push_back(song);
        outFile << "Added new Song: " << title << endl;
    }
}

void listStars(const string& title, ostream& outFile, ostream& errFile, const vector<Media*>& mediaLib) {
    for (const Media* media : mediaLib) {
        if (media->getTitle() == title && media->getType() == 'M') {
            Movie* movie = static_cast<Movie*>(const_cast<Media*>(media));
            const vector<string>& stars = movie->getStars();
            outFile << "Stars in " << title << ": ";
            for (const auto& star : stars) {
                outFile << star << " ";
            }
            outFile << endl;
            return;
        }
    }
    errFile << "Movie not found: " << title << endl;
}

void listMoviesByStar(const string& star, ostream& outFile, ostream& errFile, const vector<Media*>& mediaLib) {
    outFile << "Movies featuring " << star << ":" << endl;
    bool found = false;
    for (const Media* media : mediaLib) {
        if (media->getType() == 'M') {
            Movie* movie = static_cast<Movie*>(const_cast<Media*>(media));
            const vector<string>& stars = movie->getStars();
            if (find(stars.begin(), stars.end(), star) != stars.end()) {
                outFile << media->getTitle() << endl;
                found = true;
            }
        }
    }
    if (!found) {
        errFile << "No movies found for star: " << star << endl;
    }
}

void listMediaByName(const string& name, ostream& outFile, ostream& errFile, const vector<Media*>& mediaLib) {
    outFile << "Media by " << name << ":" << endl;
    bool found = false;
    for (const Media* media : mediaLib) {
        if (media->getName() == name) {
            media->print(outFile, mediaLib);
            found = true;
        }
    }
    if (!found) {
        errFile << "No media found for name: " << name << endl;
    }
}