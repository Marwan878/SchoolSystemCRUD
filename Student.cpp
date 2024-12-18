#pragma once
#include "Student.h"
#include <vector>
#include <string>
#include "DomainUtils.h"
using namespace std;

int Student::latestStudentRoll = getLatestRollInDatabase();

Student::Student(StudentData data, int roll) : roll(roll), name(data.name), college(data.college), branch(data.branch), attendance(data.attendance), grades(data.grades) {}
Student::Student(const vector<string> &data) {
    roll = stoi(data[0]);
    name = data[1];
    college = data[2];
    branch = data[3];
    attendance = data[4];
    grades["physics"] = (short)stoi(data[5]);
    grades["chemistry"] = (short)stoi(data[6]);
    grades["maths"] = (short)stoi(data[7]);
}

vector<string> Student::getFullData() {
    vector<string> result;
    result.push_back(to_string(roll));
    result.push_back(name);
    result.push_back(college);
    result.push_back(branch);
    result.push_back(attendance);
    result.push_back(to_string(grades["physics"]));
    result.push_back(to_string(grades["chemistry"]));
    result.push_back(to_string(grades["maths"]));
    return result;
}