#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <limits>

using namespace std;

const int MAX_STUDENTS = 100;

struct Student {
    int studentID;
    char firstName[50];
    char lastName[50];
    float GPA;
};

void addStudent(Student students[], int &numStudents);
void displayStudents(const Student students[], int numStudents);
float calculateAverageGPA(const Student students[], int numStudents);
void findStudentsByLastName(const Student students[], int numStudents, const char lastName[]);

void clearScreen();

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    int choice;

    do {
        clearScreen();

        cout << "===================\n       Menu:\n===================\n"
             << "\n[1] - Add Student\n"
             << "[2] - Display All Students\n"
             << "[3] - Calculate Average GPA\n"
             << "[4] - Find Students by Last Name\n"
             << "[5] - Exit\n===================\n\n"
             << "Enter Number 1-5 ONLY (DONT USE LETTERS!): ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\nPlease enter Number 1-5 ONLY (DONT USE LETTERS!): ";
        }

        cin.ignore();

        switch (choice) {
            case 1:
                addStudent(students, numStudents);
                break;
            case 2:
                displayStudents(students, numStudents);
                break;
            case 3:
                cout << "Average GPA: " << calculateAverageGPA(students, numStudents) << endl;
                break;
            case 4: {
                char searchLastName[50];
                cout << "Enter last name to search: ";
                cin.getline(searchLastName, sizeof(searchLastName));
                findStudentsByLastName(students, numStudents, searchLastName);
                break;
            }
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (choice != 5) {
            char continueChoice;
            do {
                cout << "\nDo you want to continue? (y/n): ";
                cin >> continueChoice;
                if (cin.fail() || (tolower(continueChoice) != 'y' && tolower(continueChoice) != 'n')) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter 'y' or 'n': ";
                }
            } while (cin.fail() || (tolower(continueChoice) != 'y' && tolower(continueChoice) != 'n'));

            if (tolower(continueChoice) != 'y') {
                break;
            }
        }

    } while (choice != 5);

    return 0;
}

void addStudent(Student students[], int &numStudents) {
    if (numStudents < MAX_STUDENTS) {
        cout << "Enter details for the new student:\n";
        students[numStudents].studentID = numStudents + 1;
        cout << "First Name: ";
        cin.getline(students[numStudents].firstName, sizeof(students[numStudents].firstName));
        cout << "Last Name: ";
        cin.getline(students[numStudents].lastName, sizeof(students[numStudents].lastName));
        cout << "GPA: ";
        cin >> students[numStudents].GPA;
        numStudents++;
        cout << "Student added successfully.\n";
    } else {
        cout << "Database is full. Cannot add more students.\n";
    }
}

void displayStudents(const Student students[], int numStudents) {
    if (numStudents > 0) {
        cout << "\n" << setw(10) << "StudentID" << setw(20) << "First Name"
             << setw(20) << "Last Name" << setw(13) << "GPA\n";
        cout << "----------------------------------------------------------------\n";
        for (int i = 0; i < numStudents; ++i) {
            cout << setw(10) << students[i].studentID << setw(20) << students[i].firstName
                 << setw(20) << students[i].lastName << setw(10) << students[i].GPA << endl;
        }
    } else {
        cout << "No students to display.\n";
    }
}

float calculateAverageGPA(const Student students[], int numStudents) {
    if (numStudents > 0) {
        float totalGPA = 0;
        for (int i = 0; i < numStudents; ++i) {
            totalGPA += students[i].GPA;
        }
        return totalGPA / numStudents;
    } else {
        return 0.0;
    }
}

void findStudentsByLastName(const Student students[], int numStudents, const char lastName[]) {
    bool found = false;
    cout << setw(10) << "StudentID" << setw(20) << "First Name"
         << setw(20) << "Last Name" << setw(10) << "GPA\n";

    char searchLastNameLower[50];
    for (int i = 0; lastName[i] != '\0'; ++i) {
        searchLastNameLower[i] = tolower(lastName[i]);
    }
    searchLastNameLower[strlen(lastName)] = '\0';

    for (int i = 0; i < numStudents; ++i) {
        char storedLastNameLower[50];
        for (int j = 0; students[i].lastName[j] != '\0'; ++j) {
            storedLastNameLower[j] = tolower(students[i].lastName[j]);
        }
        storedLastNameLower[strlen(students[i].lastName)] = '\0';

        if (strcmp(storedLastNameLower, searchLastNameLower) == 0) {
            cout << setw(10) << students[i].studentID << setw(20) << students[i].firstName
                 << setw(20) << students[i].lastName << setw(10) << students[i].GPA << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No students found with the specified last name.\n";
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

