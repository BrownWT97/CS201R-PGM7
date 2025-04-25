// CS201R-PGM7.cpp : Main program for Media Library Part 2
//Used Grok 3 for bugtesting and adding notes, also used to generate functions.h and functions.cpp
//prompts used: "Help me solve these issues" with the errors listed and the .cpp files in question
//"add notes to files" with all the files included to give it access to add notes
//used the program assignment document as a prompt to help create functions.h and functions.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Functions.h"
#include "Media.h"
#include "Movie.h"
#include "Book.h"
#include "Song.h"
using namespace std;

int main() {
    ifstream inList, inCommands;
    ofstream outFile, outErr;

    try {
        inList.open("mediaList.txt");
        inCommands.open("mediaCommands.txt");
        outFile.open("mediaReport.txt");
        outErr.open("mediaError.txt");

        if (!inList.is_open() || !inCommands.is_open() || !outFile.is_open() || !outErr.is_open()) {
            throw ios_base::failure("File opening failed");
        }
    }
    catch (const ios_base::failure& e) {
        cout << "Could not open file: " << e.what() << endl;
        return 1;
    }

    vector<Media*> myLib;

    // Read data into myLib
    readMediaList(inList, outErr, myLib);
    inList.close();

    // Process commands
    string commandRecord;
    while (getline(inCommands, commandRecord)) {
        if (commandRecord.empty()) continue;

        size_t commaPos = commandRecord.find(',');
        char cmd = commandRecord[0];

        if (cmd == 'L' && commaPos != string::npos) {
            string param = commandRecord.substr(commaPos + 1);
            listStars(param, outFile, outErr, myLib);
        }
        else if (cmd == 'F' && commaPos != string::npos) {
            string param = commandRecord.substr(commaPos + 1);
            listMoviesByStar(param, outFile, outErr, myLib);
        }
        else if (cmd == 'K' && commaPos != string::npos) {
            string param = commandRecord.substr(commaPos + 1);
            listMediaByName(param, outFile, outErr, myLib);
        }
        else if (commaPos != string::npos) {
            string secondPart = commandRecord.substr(commaPos + 1);
            if (isDigits(secondPart)) {
                printReportRating(commandRecord, outFile, outErr, myLib);
            }
            else {
                printReportGenre(commandRecord, outFile, outErr, myLib);
            }
        }
        else {
            char choice = cmd;
            if (choice == 'Q') {
                outFile << "Thank You for Using Media Everywhere" << endl;
                break;
            }
            else if (choice == 'A' || choice == 'M' || choice == 'B' || choice == 'S') {
                printReport(commandRecord, outFile, outErr, myLib);
            }
            else if (choice == 'T') {
                printTotals(outFile, myLib);
            }
            else if (choice == 'N') {
                addContent(commandRecord, outFile, outErr, myLib);
            }
            else {
                outErr << "Unknown command: " << commandRecord << endl;
            }
        }
    }

    // Clean up memory
    for (Media* media : myLib) {
        delete media;
    }
    myLib.clear();

    inCommands.close();
    outFile.close();
    outErr.close();
    return 0;
}