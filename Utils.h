#pragma once
#include <vector>
#include <string>
using namespace std;

void appendDataToFile(vector<string> data, string fileName);
void clearFile(string fileName);
void terminateApplication();
void clearScreen();
void extractData();
string convertToCSVString(vector<string> data);
void pressAnyKeyToContinue();
string toLowerCase(const string& baseString);
void sleepForMilliSeconds(int milliSeconds);
fstream getDatabaseFile();