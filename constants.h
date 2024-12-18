#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;

extern const string PASSWORD;

extern const vector<string> AdminDatabaseOptions;
extern const vector<string> schoolSubjects;
extern const vector<string> HomeMenuOptions;
extern const vector<string> AdminMenuOptions;
extern const vector<string> StudentFields;
extern const vector<string> STUDENT_FULL_FIELDS;
extern const vector<string> ADD_STUDENT_PAGE_PROMPTS;
extern const string DATABASE_FILENAME;

enum Page {
    Admin = 1,
    StudentPage,
    Exit,
    Home,
    Authentication,
};

struct StudentData {
    string name, college, branch, attendance;
    map<string, short> grades;
};