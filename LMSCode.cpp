#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class Book {
    char bno[6];
    char bname[50];
    char aname[20];

public:
    void createBook() {
        cout << "\nEnter Book Number: ";
        cin >> bno;
        cin.ignore();
        cout << "Enter Book Name: ";
        cin.getline(bname, 50);
        cout << "Enter Author Name: ";
        cin.getline(aname, 20);
    }

    void showBook() const {
        cout << "\nBook Number: " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nAuthor Name: " << aname << endl;
    }

    void modifyBook() {
        cout << "\nModify Book Name: ";
        cin.ignore();
        cin.getline(bname, 50);
        cout << "Modify Author Name: ";
        cin.getline(aname, 20);
    }

    const char* getBookNo() const {
        return bno;
    }

    void report() const {
        cout << setw(10) << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

class Student {
    char admno[6];
    char name[20];
    char stbno[6];
    int token;

public:
    void createStudent() {
        cout << "\nEnter Admission Number: ";
        cin >> admno;
        cin.ignore();
        cout << "Enter Student Name: ";
        cin.getline(name, 20);
        token = 0;
        stbno[0] = '\0';
    }

    void showStudent() const {
        cout << "\nAdmission Number: " << admno;
        cout << "\nStudent Name: " << name;
        cout << "\nBooks Issued: " << token;
        if (token == 1)
            cout << "\nBook Number: " << stbno;
    }

    void modifyStudent() {
        cout << "\nModify Student Name: ";
        cin.ignore();
        cin.getline(name, 20);
    }

    const char* getAdmno() const {
        return admno;
    }

    const char* getStbno() const {
        return stbno;
    }

    int getToken() const {
        return token;
    }

    void addToken() {
        token = 1;
    }

    void resetToken() {
        token = 0;
    }

    void setStbno(const char* t) {
        strcpy(stbno, t);
    }

    void report() const {
        cout << setw(10) << admno << setw(20) << name << setw(10) << token << endl;
    }
};

void writeBook() {
    Book bk;
    ofstream outFile("book.dat", ios::binary | ios::app);
    bk.createBook();
    outFile.write(reinterpret_cast<char*>(&bk), sizeof(Book));
    outFile.close();
}

void writeStudent() {
    Student st;
    ofstream outFile("student.dat", ios::binary | ios::app);
    st.createStudent();
    outFile.write(reinterpret_cast<char*>(&st), sizeof(Student));
    outFile.close();
}

void displayAllBooks() {
    Book bk;
    ifstream inFile("book.dat", ios::binary);
    cout << "\n\nBook List:\n";
    cout << "===============================================================\n";
    cout << "Book No." << setw(30) << "Book Name" << setw(30) << "Author\n";
    cout << "===============================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        bk.report();
    }
    inFile.close();
}

void displayAllStudents() {
    Student st;
    ifstream inFile("student.dat", ios::binary);
    cout << "\n\nStudent List:\n";
    cout << "===============================================\n";
    cout << "Adm No." << setw(20) << "Name" << setw(10) << "Token\n";
    cout << "===============================================\n";
    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        st.report();
    }
    inFile.close();
}

void bookIssue() {
    Student st;
    Book bk;
    char admno[6], bno[6];
    int found = 0, flag = 0;
    fstream fs("student.dat", ios::binary | ios::in | ios::out);
    fstream fb("book.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Student Admission Number: ";
    cin >> admno;
    while (fs.read(reinterpret_cast<char*>(&st), sizeof(Student)) && !found) {
        if (strcmp(st.getAdmno(), admno) == 0) {
            found = 1;
            if (st.getToken() == 0) {
                cout << "\nEnter Book Number: ";
                cin >> bno;
                while (fb.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && !flag) {
                    if (strcmp(bk.getBookNo(), bno) == 0) {
                        flag = 1;
                        st.addToken();
                        st.setStbno(bk.getBookNo());
                        int pos = -1 * static_cast<int>(sizeof(Student));
                        fs.seekp(pos, ios::cur);
                        fs.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        cout << "\nBook Issued Successfully! Return within 15 days.";
                    }
                }
                if (!flag) cout << "\nBook Not Found!";
            } else {
                cout << "\nReturn previously issued book first.";
            }
        }
    }
    if (!found) cout << "\nStudent Record Not Found!";
    fs.close();
    fb.close();
}

void bookDeposit() {
    Student st;
    Book bk;
    char admno[6];
    int found = 0, flag = 0, days, fine = 0;
    fstream fs("student.dat", ios::binary | ios::in | ios::out);
    fstream fb("book.dat", ios::binary | ios::in);

    cout << "\nEnter Student Admission Number: ";
    cin >> admno;
    while (fs.read(reinterpret_cast<char*>(&st), sizeof(Student)) && !found) {
        if (strcmp(st.getAdmno(), admno) == 0) {
            found = 1;
            if (st.getToken() == 1) {
                while (fb.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && !flag) {
                    if (strcmp(bk.getBookNo(), st.getStbno()) == 0) {
                        flag = 1;
                        bk.showBook();
                        cout << "\nEnter Number of Days Book Was Taken: ";
                        cin >> days;
                        if (days > 15) {
                            fine = (days - 15) * 1;
                            cout << "\nLate Fine = Rs." << fine;
                        }
                        st.resetToken();
                        int pos = -1 * static_cast<int>(sizeof(Student));
                        fs.seekp(pos, ios::cur);
                        fs.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        cout << "\nBook Deposited Successfully!";
                    }
                }
                if (!flag) cout << "\nBook Not Found!";
            } else {
                cout << "\nNo Book Issued!";
            }
        }
    }
    if (!found) cout << "\nStudent Record Not Found!";
    fs.close();
    fb.close();
}

int main() {
    int option;
    do {
        cout << "\n\nLibrary Management System";
        cout << "\n1. Add Book";
        cout << "\n2. Add Student";
        cout << "\n3. Display All Books";
        cout << "\n4. Display All Students";
        cout << "\n5. Issue Book";
        cout << "\n6. Deposit Book";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> option;
        switch(option) {
            case 1: writeBook(); break;
            case 2: writeStudent(); break;
            case 3: displayAllBooks(); break;
            case 4: displayAllStudents(); break;
            case 5: bookIssue(); break;
            case 6: bookDeposit(); break;
            case 7: cout << "Exiting..."; break;
            default: cout << "\nInvalid choice!"; break;
        }
    } while(option != 7);

    return 0;
}
