#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int roll;
    string name;
    char div;
    string address;
};

void create() {
    Student s;
    ofstream fout("stud.txt", ios::app); // Append mode to add new records
    char ans;

    do {
        cout << "\nEnter Roll No: ";
        cin >> s.roll;
        cout << "Enter Name: ";
        cin >> s.name;
        cout << "Enter Division: ";
        cin >> s.div;
        cout << "Enter Address: ";
        cin >> s.address;

        fout << s.roll << " " << s.name << " " << s.div << " " << s.address << endl;
        cout << "Do you want to add another record (y/n)? ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');
    fout.close();
}

void display() {
    Student s;
    ifstream fin("stud.txt");

    cout << "\nStudent Records:\n";
    cout << "Roll No | Name | Division | Address\n";
    while (fin >> s.roll >> s.name >> s.div >> s.address) {
        cout << s.roll << " | " << s.name << " | " << s.div << " | " << s.address << endl;
    }
    fin.close();
}

void deleteRecord() {
    int rollToDelete;
    cout << "Enter Roll No to delete: ";
    cin >> rollToDelete;

    ifstream fin("stud.txt");
    ofstream fout("temp.txt"); // Temporary file for storing remaining records

    Student s;
    bool found = false;
    while (fin >> s.roll >> s.name >> s.div >> s.address) {
        if (s.roll == rollToDelete) {
            found = true;  // Record found, don't write to temp.txt
        } else {
            fout << s.roll << " " << s.name << " " << s.div << " " << s.address << endl;
        }
    }
    fin.close();
    fout.close();

    remove("stud.txt");
    rename("temp.txt", "stud.txt");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

void search() {
    int rollToSearch;
    cout << "Enter Roll No to search: ";
    cin >> rollToSearch;

    ifstream fin("stud.txt");
    Student s;
    bool found = false;
    while (fin >> s.roll >> s.name >> s.div >> s.address) {
        if (s.roll == rollToSearch) {
            cout << "\nRecord Found: \n";
            cout << "Roll No | Name | Division | Address\n";
            cout << s.roll << " | " << s.name << " | " << s.div << " | " << s.address << endl;
            found = true;
            break;
        }
    }
    fin.close();

    if (!found)
        cout << "Record not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n2. Display All Students\n3. Delete Student\n4. Search Student\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: create(); break;
            case 2: display(); break;
            case 3: deleteRecord(); break;
            case 4: search(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
