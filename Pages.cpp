#pragma once
#include <iostream>
#include "Student.h"
#include "Utils.h"
#include "DomainUtils.h"
#include "constants.h"
#include <fstream>
#include <algorithm>
#include <sstream>

void databasePage();
void adminPage();

void homePage() {
    clearScreen();
    cout << "Login As: " << endl;
    displayMenuOptions(HomeMenuOptions);
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    displayPage((Page)choice);
}

void addStudentPage() {
    clearScreen();
    char flag = 'n';

    do {
        cout << "\t\t| Enter a New Student |" << endl;

        string studentName, college, branch, attendance;
        vector<string*> stringTypeInputFieldsAddresses = { &studentName, &college, &branch, &attendance };
        short physicsMarks, chemistryMarks, mathsMarks;
        vector<short*> shortTypeInputFieldsAddresses = { &physicsMarks, &chemistryMarks, &mathsMarks };

        for (int i = 0; i < stringTypeInputFieldsAddresses.size(); i++) {
            cout << ADD_STUDENT_PAGE_PROMPTS[i];
            cin >> *(stringTypeInputFieldsAddresses[i]);
            cout << endl;
        }

        for (int i = stringTypeInputFieldsAddresses.size(); i < ADD_STUDENT_PAGE_PROMPTS.size(); i++) {
            cout << ADD_STUDENT_PAGE_PROMPTS[i];
            cin >> *(shortTypeInputFieldsAddresses[i % shortTypeInputFieldsAddresses.size()]);
            cout << endl;
        }

        map<string, short> grades;
        grades["physics"] = physicsMarks;
        grades["chemistry"] = chemistryMarks;
        grades["maths"] = mathsMarks;

        StudentData enteredStudentData;
        enteredStudentData.attendance = attendance;
        enteredStudentData.branch = branch;
        enteredStudentData.college = college;
        enteredStudentData.grades = grades;
        enteredStudentData.name = studentName;

        int latestRollInDatabase = getLatestRollInDatabase();
        Student* student = new Student(enteredStudentData, latestRollInDatabase + 1);
        addStudent(*student);
        delete student;

        cout << "Enter another? (y/n):";
        cin >> flag;

    } while (tolower(flag) != 'n');

    clearScreen();
    adminPage();
}


void updateStudentPage() {
    string roll;
    char continueFlag;
    do {
        cout << "Enter roll of student to be updated: ";
        cin >> roll;
        cout << endl;

        if (!studentIsInDatabase(roll)) {
            cout << "No student with the roll " << roll << " exists" << endl;
            cout << "try again? (y/n): ";
            cin >> continueFlag;
            cout << endl;
        }
        else {
            Student student = getStudentFromDatabase(roll);

            cout << "Please confirm that you want to update the student with the following data: " << endl;
            printTableRow(STUDENT_FULL_FIELDS);
            printTableRow(student.getFullData());
            cout << "Proceed? (y/n): ";
            char response;
            cin >> response;

            bool theUserDisplayedIsDesiredByAdmin = tolower(response) == 'y';

            if (theUserDisplayedIsDesiredByAdmin) {
                string enteredField;
                cout << "Type in the field to be updated: ";
                cin >> enteredField;
                
                if (theFieldIsAModifiableStudentField(enteredField)) {

                    cout << endl << "Please enter the new value: ";
                    string newValue;
                    cin >> newValue;

                    int fieldToBeUpdatedIndex = getStudentFieldIndex(enteredField);

                    vector<string> originalStudentDataCopy = student.getFullData();
                    originalStudentDataCopy[fieldToBeUpdatedIndex] = newValue;
                    Student updatedStudent(originalStudentDataCopy);
                    vector<string> updatedLines = getUpdatedRows(originalStudentDataCopy);

                    clearFile("data.csv");
                    appendDataToFile(updatedLines, "data.csv");

                    cout << "Data updated successfully!";
                    sleepForMilliSeconds(500);
                    break;
                }
                else {
                    cout << "The field " << enteredField << " does not exist" << endl
                         << "Would you like to try again? (y / n): ";
                }
            }
            else {
                cout << "Try again? (y/n): ";
            }
            cin >> continueFlag;
            cout << endl;
        }
    } while (tolower(continueFlag) != 'n');
    clearScreen();
    databasePage();
}

void deleteStudentPage() {
    clearScreen();
    char adminWantsToTryAgain = 'n';
    do
    {
        cout << "Enter roll of student to delete: ";
        string roll;
        cin >> roll;

        if (!studentIsInDatabase(roll)) {
            cout << "No such student is present in the database!" << endl
                 << "Would you like to try again? (y/ n): ";
            cin >> adminWantsToTryAgain;
            cout << endl;
        }
        else {
            char adminWantsToDeleteAgain = 'n';
            do
            {
                char adminWantsToDeleteTheSelectedStudent = 'n';
             
                Student selectedStudent = getStudentFromDatabase(roll);
                cout << "Are you sure that you want to delete the student with data:" << endl;
                vector<string> selectedStudentFullData = selectedStudent.getFullData();
                printTableRow(STUDENT_FULL_FIELDS);
                printTableRow(selectedStudentFullData);
                cout << "Proceed? (y/n): ";
                cin >> adminWantsToDeleteTheSelectedStudent;

                if (adminWantsToDeleteTheSelectedStudent == 'y') {
                    deleteStudent(roll);
                    cout << "Student deleted successfully!" << endl;
                    sleepForMilliSeconds(500);
                }
                
                cout << "Would you like to delete another student? (y / n): ";
                cin >> adminWantsToDeleteAgain;
                cout << endl;

                adminWantsToTryAgain = adminWantsToDeleteAgain;
            } while (tolower(adminWantsToDeleteAgain) != 'n');
        }
    } while (tolower(adminWantsToTryAgain) != 'n');

    clearScreen();
    adminPage();
}

void databasePage() {
    displayDatabase();
    displayMenuOptions(AdminDatabaseOptions);

    int choice;
    cout << "Enter choice: ";

    do {
        cin >> choice;
        switch (choice) {
        case 1:
            addStudentPage();
            break;
        case 2:
            deleteStudentPage();
            break;
        case 3:
            updateStudentPage();
            break;
        case 4:
            homePage();
            break;
        case 5:
            terminateApplication();
            break;
        default:
            cout << endl << "Please choose an option between 1 and " << AdminDatabaseOptions.size() << "." << endl;
            break;
        }
    } while (choice > AdminDatabaseOptions.size());
}

void adminPage() {
    
    cout << "| Logged In as Admin |\n\n";
    displayMenuOptions(AdminMenuOptions);

    cout << "Enter choice: ";
    short choice;
    cin >> choice;

    switch (choice) {
    case 1:
        addStudentPage();
        break;
    case 2:
        deleteStudentPage();
        break;
    case 3:
        databasePage();
        break;
    case 4:
        displayPage(Home);
        break;
    case 5:
        terminateApplication();
        break;
    }
}

void studentPage() {
    displayDatabase();
    pressAnyKeyToContinue();
    displayPage(Home);
}