#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string className;
    float marks;
};

// Function to add a student record
void addStudent() {
    ofstream file("students.txt", ios::app);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student student;
    cout << "Enter Roll No: ";
    cin >> student.rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Class: ";
    getline(cin, student.className);
    cout << "Enter Marks: ";
    cin >> student.marks;

    file << student.rollNo << "," << student.name << "," << student.className << "," << student.marks << endl;
    file.close();
    cout << "Student record added successfully!" << endl;
}

// Function to view all student records
void viewStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "No records found!\n";
        return;
    }

    string line;
    cout << "Roll No  Name   Class   Marks\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string rollNo, name, studentClass, marks;

        getline(ss, rollNo, ',');
        getline(ss, name, ',');
        getline(ss, studentClass, ',');
        getline(ss, marks, ',');

        cout << rollNo << "        " << name << "     " << studentClass << "    " << marks << endl;
    }

    file.close();
}


// Function to delete a student record
void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    
    string line, rollNo;
    bool found = false;
    
    cout << "Enter Roll Number to delete: ";
    cin >> rollNo;

    while (getline(file, line)) {
        stringstream ss(line);
        string storedRollNo;
        getline(ss, storedRollNo, ',');  

        if (storedRollNo == rollNo) {
            found = true;
            continue;  // Skip writing this line to the temp file (i.e., delete it)
        }
        temp << line << endl;  // Write other records to the temp file
    }

    file.close();
    temp.close();
    
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student record deleted successfully!\n";
    else
        cout << "Student with Roll No " << rollNo << " not found!\n";
}

// Menu-driven program
int main() {
    int choice;
    do {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
