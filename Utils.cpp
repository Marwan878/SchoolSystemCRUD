#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>  // for cross-
#include <chrono>  // platform pausing
#include <sstream>
#include <numeric>
#include "DomainUtils.h"
// for cross platfrom "Press any key to continue..."
#ifdef _WIN32
#include <conio.h> // For _getch() on Windows
#else
#include <unistd.h>
#include <termios.h>
#endif
using namespace std;

fstream getDatabaseFile() {
    fstream file(DATABASE_FILENAME, ios::out | ios::in);
    if (!file.is_open()) {
        cerr << "Failed to open the data file!" << endl;
        exit(1);
    }
    return file;
}

void appendDataToFile(vector<string> data, string fileName) {
    ofstream outputFile(fileName, ios::app);
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file" << endl;
    }
    outputFile << endl;
    for (int i = 0; i < data.size(); i++) {
        outputFile << data[i];
        if (i < data.size() - 1) {
            outputFile << endl;
        }
    }
}

void clearFile(string fileName) {
    ofstream outputFile(fileName, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file" << endl;
        exit(1);
    }
    outputFile.close();
}

void terminateApplication() {
    cout << "Quitting .";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << ".";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << ".";
    exit(0);
}

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");  // Windows command to clear the console
    // Check for UNIX-like systems (Linux, macOS)
#elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
    system("clear");  // UNIX command to clear the console
#endif
}

void extractData() {
    fstream inputFile = getDatabaseFile();
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<string> currentRow;
        string cell;
        vector<int> row;
        while (getline(ss, cell, ',')) {
            currentRow.push_back(cell);
        }
        printTableRow(currentRow);
    }
    inputFile.close();
}

string convertToCSVString(vector<string> data) {
    string result = std::accumulate(data.begin() + 1, data.end(), data[0],
        [](const string& a, const string& b) {
            return a + ", " + b;
        });
    return result;
}

string toLowerCase(const string& baseString) {
    string lowerCasedString = "";
    for (int i = 0; i < baseString.length(); i++)
        lowerCasedString += tolower(baseString.at(i));
    return lowerCasedString;
}

void pressAnyKeyToContinue() {
#ifdef _WIN32
    std::cout << "Press any key to continue..." << std::endl;
    _getch(); // Windows-specific: wait for key press
#else
    std::cout << "Press any key to continue..." << std::endl;

    // Unix-specific: Disable terminal echo
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Get current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings

    getchar(); // Wait for key press

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
#endif
}

void sleepForMilliSeconds(int milliSeconds) {
    this_thread::sleep_for(chrono::milliseconds(milliSeconds));
}

