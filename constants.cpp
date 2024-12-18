#pragma once
#include "constants.h"
#include <map>

const string PASSWORD = "password";

const vector<string> schoolSubjects = {
    "physics",
    "chemistry",
    "math"
};

const vector<string> HomeMenuOptions = {
    "Admin",
    "Student",
    "Exit"
};

const vector<string> AdminMenuOptions = {
    "Add Students Detail",
    "Delete Students",
    "View Table",
    "Main Menu",
    "Exit"
};

const vector<string> AdminDatabaseOptions = {
    "Add Record",
    "Delete Record",
    "Update Record",
    "Main Menu",
    "Exit"
};

const vector<string> StudentFields = {
    "roll", "name", "college", "branch", "attendance", "grades"
};

const vector<string> ADD_STUDENT_PAGE_PROMPTS = {
    "Enter Student's Name: ",
    "Enter College: ",
    "Enter Branch: ",
    "Enter Attendance: ",
    "Enter Physics Marks: ",
    "Enter Chemistry Marks: ",
    "Enter Maths Marks: "
};

const vector<string> STUDENT_FULL_FIELDS = { "Roll", "Name", "College", "Branch", "Attendance", "Physics", "Chemistry", "Maths" };

const string DATABASE_FILENAME = "data.csv";