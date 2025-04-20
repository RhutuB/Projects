#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Book {
    string bno;
    string bname;
    string aname;
public:
    void createBook() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "ENTER BOOK NO.: ";
        cin >> bno;
        cin.ignore();
        cout << "ENTER BOOK NAME: ";
        getline(cin, bname);
        cout << "ENTER AUTHOR NAME: ";
        getline(cin, aname);
        cout << "\nBook Created.\n";
    }

    void showBook() const {
        cout << "\nBook Number: " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nAuthor Name: " << aname << endl;
    }

    void modifyBook() {
        cout << "Modify Book Name: ";
        getline(cin, bname);
        cout << "Modify Author Name: ";
        getline(cin, aname);
    }

    string getBookNo() const {
        return bno;
    }

    void report() const {
        cout << left << setw(10) << bno << setw(30) << bname << setw(20) << aname << endl;
    }
};

class Student {
    string admno;
    string name;
    string stbno;
    int token = 0;
public:
    void createStudent() {
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "Enter Admission No.: ";
        cin >> admno;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        token = 0;
        stbno = "";
        cout << "\nStudent Record Created.\n";
    }

    void showStudent() const {
        cout << "\nAdmission Number: " << admno;
        cout << "\nStudent Name: " << name;
        cout << "\nBooks Issued: " << token;
        if (token == 1) {
            cout << "\nBook Number: " << stbno;
        }
        cout << endl;
    }

    void modifyStudent() {
        cout << "Modify Student Name: ";
        getline(cin, name);
    }

    string getAdmNo() const {
        return admno;
    }

    string getBookNo() const {
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

    void setBookNo(const string& bn) {
        stbno = bn;
    }

    void report() const {
        cout << left << setw(10) << admno << setw(20) << name << setw(10) << token << endl;
    }
};

// Global file objects and class objects
Book bk;
Student st;
fstream fp, fp1;

// Sample function to write books
void writeBook() {
    char ch;
    do {
        bk.createBook();
        fp.open("book.dat", ios::out | ios::app | ios::binary);
        fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
        fp.close();
        cout << "Do you want to add more records? (y/n): ";
        cin >> ch;
        cin.ignore();
    } while (ch == 'y' || ch == 'Y');
}

// Sample function to display all books
void displayAllBooks() {
    fp.open("book.dat", ios::in | ios::binary);
    if (!fp) {
        cerr << "Cannot open file.\n";
        return;
    }

    cout << "\n\nBook List:\n";
    cout << "-------------------------------------------------------------\n";
    cout << left << setw(10) << "Book No" << setw(30) << "Book Name" << setw(20) << "Author" << endl;
    cout << "-------------------------------------------------------------\n";
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        bk.report();
    }
    fp.close();
}

// You can continue writing similar modern versions of functions like:
// - writeStudent()
// - displayAllStudents()
// - displaySpecificBook()
// - displaySpecificStudent()
// - modifyBook()
// - modifyStudent()
// - deleteBook()
// - deleteStudent()
// - bookIssue()
// - bookDeposit()
// - mainMenu()
// - adminMenu()

int main() {
    int choice;
    do {
        cout << "\nLIBRARY MANAGEMENT SYSTEM\n";
        cout << "1. Create Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                writeBook();
                break;
            case 2:
                displayAllBooks();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 3);
    return 0;
}
