/*
    Module: Student System
    Owner: Farwa Eeman
    Description: Implementation of student system functions
*/



#include <iostream>
#include <string>
#include <limits>
using namespace std;

/* -------- Book Node -------- */
struct BookNode {
    int bookId;
    string title;
    BookNode* next;

    BookNode(int id, const string& t) : bookId(id), title(t), next(nullptr) {}
};

/* -------- Student Node -------- */
struct Student {
    int studentId;
    string name;
    string department;
    BookNode* borrowedBooks;
    Student* next;

    Student(int id, const string& n, const string& d) : studentId(id), name(n), department(d), borrowedBooks(nullptr), next(nullptr) {}
};

/* -------- Global Head & Transaction -------- */
Student* head = nullptr;
int transactionCounter = 1000;

/* -------- Helper Functions -------- */
int countBorrowedBooks(BookNode* bookHead) {
    int count = 0;
    BookNode* temp = bookHead;
    int safety = 0;
    while (temp && safety++ < 1000) {
        count++;
        temp = temp->next;
    }
    return count;
}

Student* searchStudent(int id) {
    Student* temp = head;
    int safety = 0;
    while (temp && safety++ < 1000) {
        if (temp->studentId == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

/* -------- Student Functions -------- */

//  Adds a new student to the linked list  //
void addStudent() {
    string input;
    int id;
    string name, dept;

    cout << "Enter Student ID: ";
    getline(cin, input);
    id = stoi(input);

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Department: ";
    getline(cin, dept);

    if (searchStudent(id)) {
        cout << "Student with this ID already exists!\n";
        return;
    }

    Student* newStudent = new Student(id, name, dept);
    if (!head) head = newStudent;
    else {
        Student* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newStudent;
    }

    cout << "Student added successfully.\n";
}

void displayStudents() {
    if (!head) {
        cout << "No students found.\n";
        return;
    }

    Student* temp = head;
    int safety = 0;
    while (temp && safety++ < 1000) {
        cout << "\nID: " << temp->studentId
             << "\nName: " << temp->name
             << "\nDepartment: " << temp->department
             << "\nBooks Borrowed: " << countBorrowedBooks(temp->borrowedBooks) << "\n";

        BookNode* book = temp->borrowedBooks;
        int bookSafety = 0;
        while (book && bookSafety++ < 1000) {
            cout << "  Book ID: " << book->bookId << ", Title: " << book->title << "\n";
            book = book->next;
        }

        temp = temp->next;
    }
}

/* -------- Borrowing Functions -------- */

void issueBook() {
    string input;
    int sid, bid;
    string title;

    cout << "Enter Student ID: ";
    getline(cin, input);
    sid = stoi(input);

    Student* student = searchStudent(sid);
    if (!student) { cout << "Student not found.\n"; return; }

    if (countBorrowedBooks(student->borrowedBooks) >= 3) {
        cout << "Limit reached (Max 3 books).\n";
        return;
    }

    cout << "Enter Book ID: ";
    getline(cin, input);
    bid = stoi(input);

    cout << "Enter Book Title: ";
    getline(cin, title);

    BookNode* newBook = new BookNode(bid, title);

    if (!student->borrowedBooks) student->borrowedBooks = newBook;
    else {
        BookNode* temp = student->borrowedBooks;
        while (temp->next) temp = temp->next;
        temp->next = newBook;
    }

    transactionCounter++;
    cout << "Book issued successfully. Transaction ID: " << transactionCounter << "\n";
}

void returnBook() {
    string input;
    int sid, bid;

    cout << "Enter Student ID: ";
    getline(cin, input);
    sid = stoi(input);

    Student* student = searchStudent(sid);
    if (!student || !student->borrowedBooks) { cout << "No borrowed books or student not found.\n"; return; }

    cout << "Enter Book ID to return: ";
    getline(cin, input);
    bid = stoi(input);

    BookNode* curr = student->borrowedBooks;
    BookNode* prev = nullptr;
    int safety = 0;
    while (curr && safety++ < 1000 && curr->bookId != bid) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) { cout << "Book not found.\n"; return; }

    if (!prev) student->borrowedBooks = curr->next;
    else prev->next = curr->next;

    delete curr;
    transactionCounter++;
    cout << "Book returned successfully. Transaction ID: " << transactionCounter << "\n";
}

void searchStudentById() {
    string input;
    int id;
    cout << "Enter Student ID to search: ";
    getline(cin, input);
    id = stoi(input);

    Student* temp = searchStudent(id);
    if (!temp) { cout << "Student not found.\n"; return; }

    cout << "\nID: " << temp->studentId
         << "\nName: " << temp->name
         << "\nDepartment: " << temp->department
         << "\nBooks Borrowed: " << countBorrowedBooks(temp->borrowedBooks) << "\n";

    BookNode* book = temp->borrowedBooks;
    int bookSafety = 0;
    while (book && bookSafety++ < 1000) {
        cout << "  Book ID: " << book->bookId << ", Title: " << book->title << "\n";
        book = book->next;
    }
}

/* -------- Main Menu -------- */
int main() {
    string input;
    int choice = -1;

    do {
        cout << "\n--- Student Borrowing System ---\n"
             << "1. Add Student\n"
             << "2. Display Students\n"
             << "3. Issue Book\n"
             << "4. Return Book\n"
             << "5. Search Student\n"
             << "0. Exit\n"
             << "Enter choice: ";
        getline(cin, input);
        choice = stoi(input);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: searchStudentById(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
