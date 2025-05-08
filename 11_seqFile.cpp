
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Student{
    int rollno;
    string name;
    char div;
    string address;
};

void addStudent(){
    Student s;
    ofstream file("STUD.txt" , ios::app);
    char ans;

    do{
        cout<<"\nEnter Roll No. of Student : ";
        cin>>s.rollno;
        cout<<"Enter Name of Student : ";
        cin>>s.name;
        cout<<"Enter Div of Student : ";
        cin>>s.div;
        cout<<"Enter Address of Student : ";
        cin>>s.address;

        file<<s.rollno<<" "<<s.name<<"   "<<s.div<<"   "<<s.address<<endl;

        cout<<"\nAdd more student (y/n) : ";
        cin>>ans;
    }while(ans == 'y' || ans == 'Y');

    file.close();
}

void display(){
    Student s;
    ifstream file("STUD.txt");

    cout<<"\n --------- Student Details ---------"<<endl;
    cout<<"Roll No.| Name | Div | Address "<<endl;

    while(file>>s.rollno>>s.name>>s.div>>s.address){
        cout<<s.rollno<<" "<<s.name<<"    "<<s.div<<"    "<<s.address<<endl;
    }
    file.close();
}

void search(){
    Student s;
    ifstream file("STUD.txt");
    bool found = false;

    int searchRoll;
    cout<<"\nEnter Roll No. you want to Search : ";
    cin>>searchRoll;

    while(file>>s.rollno>>s.name>>s.div>>s.address){
        if(searchRoll == s.rollno){
            found = true;
            cout<<"\nRoll No. | Name | Div | Address "<<endl;
            cout<<s.rollno<<" "<<s.name<<"    "<<s.div<<"   "<<s.address<<endl;
        }
    }
    file.close();

    if(!found){
        cout<<"\nNo Such Record Found !"<<endl;
    }else{
        cout<<"\nRecord Found & Displayed Successfully !! "<<endl;
    }
}

void deleteStudent(){
    Student s;
    ifstream file("STUD.txt");
    ofstream tempfile("TEMP.txt");
    bool found = false;

    int deleteRoll;
    cout<<"Enter Roll No. to be Deleted : ";
    cin>>deleteRoll;

    while(file>>s.rollno>>s.name>>s.div>>s.address){
        if(s.rollno == deleteRoll){
            found = true;
        }else{
            tempfile<<s.rollno<<"  "<<s.name<<"   "<<s.div<<"   "<<s.address<<endl;
        }
    }
    file.close();
    tempfile.close();

    remove("STUD.txt");
    rename("TEMP.txt" , "STUD.txt");

    if(found){
        cout<<"\nRecord Deleted Successfully !"<<endl;
    }else{
        cout<<"\nRecord Not Found !"<<endl;
    }
}

int main(){
    int ch;
    cout<<"\nStudent Record Management System "<<endl;
    do{
        cout<<"\n1.Add Student\n2.Display Students\n3.Search\n4.Delete\n5.Exit"<<endl;
        cout<<"Enter Your Choice from Above Options : ";
        cin>>ch;

        switch (ch){
        case 1:
            addStudent();
            break;

        case 2:
            display();
            break;

        case 3:
            search();
            break;

        case 4:
            deleteStudent();
            break;

        case 5:
            cout<<"\nProgram Exited Successfully "<<endl;
            break;
        
        default:
            cout<<"Enter a valid Choice "<<endl;
            break;
        }
    }while(ch != 5);

    return 0;
}