#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include <iostream>
#include "Media.h"
#include "Movie.h"
#include "Book.h"
#include "Song.h"

// PRE: str1 is a string
// POST: Returns true if str1 contains only digits, false otherwise
bool isDigits(const std::string& str1);

// PRE: inFile is open and valid, outFile is open for writing, mediaLib is empty
// POST: Reads media data from inFile, validates it, stores valid entries in mediaLib,
//       writes errors to outFile, returns number of valid entries
int readMediaList(std::istream& inFile, std::ostream& outFile, std::vector<Media*>& mediaLib);

// PRE: outFile is open, mediaLib contains Media pointers
// POST: Writes total counts of Movies, Songs, Books to outFile
void printTotals(std::ostream& outFile, const std::vector<Media*>& mediaLib);

// PRE: commandRecord is a valid command string, outFile and errFile are open,
//      mediaLib contains Media pointers
// POST: Processes command, writes output to outFile, errors to errFile
void printReport(const std::string& commandRecord, std::ostream& outFile, std::ostream& errFile, const std::vector<Media*>& mediaLib);

// PRE: commandRecord is a command with rating, outFile and errFile are open,
//      mediaLib contains Media pointers
// POST: Processes rating-based command, writes output to outFile, errors to errFile
void printReportRating(const std::string& commandRecord, std::ostream& outFile, std::ostream& errFile, const std::vector<Media*>& mediaLib);

// PRE: commandRecord is a command with genre, outFile and errFile are open,
//      mediaLib contains Media pointers
// POST: Processes genre-based command, writes output to outFile, errors to errFile
void printReportGenre(const std::string& commandRecord, std::ostream& outFile, std::ostream& errFile, const std::vector<Media*>& mediaLib);

// PRE: commandRecord is an 'N' command, outFile and errFile are open,
//      mediaLib is a valid vector
// POST: Adds new Media to mediaLib if valid, writes errors to errFile
void addContent(const std::string& commandRecord, std::ostream& outFile, std::ostream& errFile, std::vector<Media*>& mediaLib);

// PRE: title is a string, outFile and errFile are open, mediaLib contains Media pointers
// POST: Prints stars of the movie with given title to outFile, errors to errFile
void listStars(const std::string& title, std::ostream& outFile, std::ostream& errFile, const std::vector<Media*>& mediaLib);

// PRE: star is a string, outFile and errFile are open, mediaLib contains Media pointers
// POST: Lists movies featuring the given star to outFile, errors to errFile
void listMoviesByStar(const std::string& star, std::ostream& outFile, std::ostream& errFile, const std::vector<Media*>& mediaLib);

// PRE: name is a string, outFile and errFile are open, mediaLib contains Media pointers
// POST: Lists all media by the given name to outFile, errors to errFile
void listMediaByName(const std::string& name, std::ostream& outFile, std::ostream& errFile, const std::vector<Media*>& mediaLib);

#endif // FUNCTIONS_H