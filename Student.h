#pragma once
#include <vector>
#include <map>
#include <string>
#include "constants.h"
using namespace std;

class Student
{
private:
    string name, college, branch, attendance;
    map<string, short> grades;
    static int latestStudentRoll;
    int roll;

public:
    Student(StudentData data, int roll);
    Student(const vector<string>& data);
    vector<string> getFullData();
};
