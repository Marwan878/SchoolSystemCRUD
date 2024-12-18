#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include "Utils.h"
#include "Student.h"
#include "Pages.h"
using namespace std;

void displayMenuOptions(vector<string> options) {
    for (int i = 0; i < options.size(); i++) {
        cout << i + 1 << ". " << options[i] << endl;
    }
}

void printTableRow(vector<string> rowCellsContent) {
    cout << left;
    for (int i = 0; i < rowCellsContent.size(); i++) {
        cout << setw(20) << rowCellsContent[i];
    }
    cout << endl;
}

void displayDatabase() {
    clearScreen();
    printTableRow({ "Roll", "Name", "College", "Branch", "Attendance","Physics", "Chemistry", "Maths" });
    extractData();
}

void authenticate() {
    clearScreen();
    string input;
    do {
        cout << "Enter Password: ";
        cin >> input;
    } while (input != PASSWORD);
    clearScreen();
}

bool studentIsInDatabase(string roll) {
    bool result = false;
    fstream inputFile = getDatabaseFile();
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ',');
        if (cell == roll) {
            return true;
        }
    }
    inputFile.close();
    return result;
}


void addStudent(Student student) {
    vector<string> studentData = student.getFullData();
    string record = convertToCSVString(studentData);
    appendDataToFile({ record }, "data.csv");
}

vector<string> extractValuesFromCSVString(string CSVString) {
    string aggregator = "";
    vector <string> result;
    for (int i = 0; i < CSVString.length(); i++) {
        if (CSVString.at(i) != ',' && CSVString.at(i) != ' ') {
            aggregator += CSVString.at(i);
        }
        else if (CSVString.at(i) == ',') {
            result.push_back(aggregator);
            aggregator = "";
        }
    }
    // in CSV last value does not have a ',' after it
    result.push_back(aggregator);
    return result;
}

Student getStudentFromDatabase(string roll) {
    string line;
    fstream inputFile = getDatabaseFile();
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ',');
        if (cell == roll) {
            vector<string> studentData = extractValuesFromCSVString(line);
            Student student(studentData);
            return student;
        }
    }
}

vector<string> filterDataUsingRollFromInputStream(string roll, fstream& inputFile) {
    vector<string> updatedRows;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ',');
        if (cell == roll) {
            continue;
        }
        updatedRows.push_back(line);
    }
    return updatedRows;
}

void deleteStudent(string roll) {
    fstream inputFile = getDatabaseFile();
    vector<string> filteredRows = filterDataUsingRollFromInputStream(roll, inputFile);
    clearFile("data.csv");
    appendDataToFile(filteredRows, "data.csv");
}

void displayPage(Page page) {
    switch (page) {
        case Home:
            homePage();
            break;
        case Admin:
            authenticate();
            adminPage();
            break;
        case StudentPage:
            studentPage();
            break;
        default:
            terminateApplication();
            break;
    }
}

string getLastLineInDatabase() {
    ifstream inputFile("data.csv", std::ios::ate);
    if (!inputFile.is_open()) {
        cerr << "Unable to open file" << endl;
    }

    std::streampos fileSize = inputFile.tellg();
    if (fileSize == 0)
        return "";

    string lastLine;
    char c;

    for (int i = 1; i <= fileSize; i++) {
        inputFile.seekg(-i, std::ios::end);
        inputFile.get(c);
        if (c == '\n')
            break;
        lastLine += c;
    }

    reverse(lastLine.begin(), lastLine.end());

    inputFile.close();

    return lastLine;
}

bool stringIsEmpty(string _string) {
    return _string == "";
}

int getLatestRollInDatabase() {
    string lastLineInDatabase = getLastLineInDatabase();
    vector<string> lastLineValues = extractValuesFromCSVString(lastLineInDatabase);
    string rollCell = lastLineValues[0];
    int roll = stringIsEmpty(rollCell) ? 0 : stoi(rollCell);
    return roll;
}

bool theFieldIsAModifiableStudentField(string field) {
    // here we start from index 1 as roll (which is at index 0) can never be modified
    return (find(StudentFields.begin() + 1, StudentFields.end(), toLowerCase(field)) != StudentFields.end());
}

int getStudentFieldIndex(string field) {
    int fieldToBeUpdatedIndex = 0;

    while (toLowerCase(STUDENT_FULL_FIELDS[fieldToBeUpdatedIndex]) != toLowerCase(field)) {
        fieldToBeUpdatedIndex++;
    }

    return fieldToBeUpdatedIndex;
}

vector<string> getUpdatedRows(const vector<string> & updatedStudentData) {
    string roll = updatedStudentData[0];
    fstream inputFile = getDatabaseFile();
    string line;
    vector<string> updatedRows;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ',');
        bool theCurrentLineHasTheNeededStudent = cell == roll;
        if (theCurrentLineHasTheNeededStudent) {
            updatedRows.push_back(convertToCSVString(updatedStudentData));
        }
        else {
            updatedRows.push_back(line);
        }
    }
    return updatedRows;
}