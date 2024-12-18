#pragma once
#include <vector>
#include <string>
#include "Student.h"
#include "constants.h"

void displayMenuOptions(vector<string> options);
void printTableRow(vector<string> rowCellsContent);
void displayDatabase();
void authenticate();
bool studentIsInDatabase(string roll);
void addStudent(Student student);
Student getStudentFromDatabase(string roll);
StudentData extractValuesFromCSVString(string data);
vector<string> filterDataUsingRollFromInputStream(string roll, ifstream& inputFile);
void deleteStudent(string roll);
void displayPage(Page page);
int getLatestRollInDatabase();
bool theFieldIsAModifiableStudentField(string field);
int getStudentFieldIndex(string field);
vector<string> getUpdatedRows(const vector<string>& updatedStudentData);