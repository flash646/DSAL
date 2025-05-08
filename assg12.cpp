#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

// Employee Class
class Employee {
public:
    int code;
    char name[20];
    float salary;
    char designation[20];

    void read();
    void display();
    int getEmpCode() { return code; }
    float getSalary() { return salary; }
    void updateSalary(float s) { salary = s; }
};

// Function to read employee details
void Employee::read() {
    cout << "Enter employee code: ";
    cin >> code;
    cout << "Enter name: ";
    cin.ignore();
    cin.getline(name, 20);
    cout << "Enter Designation: ";
    cin.getline(designation, 20);
    cout << "Enter salary: ";
    cin >> salary;
}

// Function to display employee details
void Employee::display() {
    cout << left << setw(15) << code 
         << setw(20) << name 
         << setw(15) << salary 
         << setw(20) << designation << endl;
}

// Function to update the index file
void updateIndex(int code, long long pos) {
    ofstream indexFile("INDEX.TXT", ios::app);
    indexFile << code << " " << pos << endl;
    indexFile.close();
}

// Function to add a new employee record
void addEmployee() {
    Employee emp;
    emp.read();

    bool writeHeader = false;
    ifstream checkFile("EMPLOYEE.TXT");
    if (!checkFile.good() || checkFile.peek() == ifstream::traits_type::eof()) {
        writeHeader = true;
    }
    checkFile.close();

    ofstream dataFile("EMPLOYEE.TXT", ios::app);
    if (!dataFile) {
        cerr << "Error opening EMPLOYEE.TXT\n";
        return;
    }

    if (writeHeader) {
        dataFile << left << setw(15) << "EmployeeCode" 
                 << setw(20) << "Name" 
                 << setw(15) << "Salary" 
                 << setw(20) << "Designation" << endl;
    }

    long long pos = static_cast<long long>(dataFile.tellp());
    dataFile << left << setw(15) << emp.code 
             << setw(20) << emp.name 
             << setw(15) << emp.salary 
             << setw(20) << emp.designation << endl;

    dataFile.close();
    updateIndex(emp.code, pos);
    cout << "Employee record added successfully.\n";
}

// Function to display all employee records
void displayAll() {
    ifstream dataFile("EMPLOYEE.TXT");
    if (!dataFile) {
        cerr << "Error opening EMPLOYEE.TXT\n";
        return;
    }

    string line;
    cout << "\n------------------ Employee Records ------------------\n";
    while (getline(dataFile, line)) {
        cout << line << endl;
    }
    cout << "------------------------------------------------------\n";

    dataFile.close();
}

// Function to increase an employee's salary
void increaseSalary() {
    int updateCode;
    float hikeAmount;
    cout << "Enter employee code to increase salary: ";
    cin >> updateCode;
    cout << "Enter amount to increase: ";
    cin >> hikeAmount;

    ifstream dataFile("EMPLOYEE.TXT");
    ofstream tempFile("TEMP.TXT");
    bool updated = false;

    if (!dataFile || !tempFile) {
        cerr << "Error opening files\n";
        return;
    }

    string header;
    getline(dataFile, header);
    tempFile << header << endl;

    Employee emp;
    while (dataFile >> emp.code >> emp.name >> emp.salary >> emp.designation) {
        if (emp.code == updateCode) {
            emp.updateSalary(emp.salary + hikeAmount);
            updated = true;
        }

        tempFile << left << setw(15) << emp.code 
                 << setw(20) << emp.name 
                 << setw(15) << emp.salary 
                 << setw(20) << emp.designation << endl;
    }

    dataFile.close();
    tempFile.close();

    remove("EMPLOYEE.TXT");
    rename("TEMP.TXT", "EMPLOYEE.TXT");

    if (updated) {
        cout << "Salary updated successfully.\n";
    } else {
        cout << "Employee not found!\n";
    }
}

//  Function to delete an employee record
void deleteEmployee() {
    int deleteCode;
    cout << "Enter employee code to delete: ";
    cin >> deleteCode;

    ifstream dataFile("EMPLOYEE.TXT");
    ofstream tempFile("TEMP.TXT");
    bool deleted = false;

    if (!dataFile || !tempFile) {
        cerr << "Error opening files\n";
        return;
    }

    string header;
    getline(dataFile, header);
    tempFile << header << endl;

    Employee emp;
    while (dataFile >> emp.code >> emp.name >> emp.salary >> emp.designation) {
        if (emp.code == deleteCode) {
            deleted = true;
            continue; // Skip writing this record
        }
        tempFile << left << setw(15) << emp.code 
                 << setw(20) << emp.name 
                 << setw(15) << emp.salary 
                 << setw(20) << emp.designation << endl;
    }

    dataFile.close();
    tempFile.close();

    remove("EMPLOYEE.TXT");
    rename("TEMP.TXT", "EMPLOYEE.TXT");

    if (deleted) {
        cout << "Employee deleted successfully.\n";
    } else {
        cout << "Employee not found!\n";
    }
}

// Main function with menu
int main() {
    char choice;
    do {
        int option;
        cout << "\nMENU:\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Increase Salary\n";
        cout << "4. Delete Employee\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: addEmployee(); break;
            case 2: displayAll(); break;
            case 3: increaseSalary(); break;
            case 4: deleteEmployee(); break;
            default: cout << "Invalid choice!\n";
        }

        cout << "Do you want to continue? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    return 0;
}
