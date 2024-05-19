#include <iostream>
#include <cctype>
#include <limits>

using namespace std;

const int ROWS = 2;
const int SEATS_PER_ROW = 9; 

bool isValidSeat(int seatNumber, char customerType) {
    if (customerType == 'S') {
        return seatNumber >= 1 && seatNumber <= 17 && seatNumber != 8 && seatNumber != 18;
    } else if (customerType == 'R') {
        return seatNumber >= 4 && seatNumber <= 17 && seatNumber != 8 && seatNumber != 18;
    }
    return false;
}

bool isSeatAvailable(bool seats[ROWS][SEATS_PER_ROW], int seatNumber) {
    int row = (seatNumber - 1) / SEATS_PER_ROW;
    int col = (seatNumber - 1) % SEATS_PER_ROW;
    return !seats[row][col];
}

void reserveSeat(bool seats[ROWS][SEATS_PER_ROW], int seatNumber) {
    int row = (seatNumber - 1) / SEATS_PER_ROW;
    int col = (seatNumber - 1) % SEATS_PER_ROW;
    seats[row][col] = true;
}

void displaySeats(bool seats[ROWS][SEATS_PER_ROW]) {
    cout << "Current bus seating layout:\n\n";
    for (int row = 0; row < ROWS; ++row) {
        cout << "[D" << (row + 1) << "]  ";
        for (int col = 0; col < SEATS_PER_ROW; ++col) {
            int seatNumber = row * SEATS_PER_ROW + col + 1;
            if (isSeatAvailable(seats, seatNumber)) {
                if (seatNumber == 8) {
                    cout << "[8] ";
                } else if (seatNumber == 18) {
                    cout << "[BR] ";
                } else {
                    cout << "[" << to_string(seatNumber) << "] ";
                }
            } else {
                cout << "[X] ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}


int main() {
    bool seats[ROWS][SEATS_PER_ROW] = {}; 
    char customerType;
    int seatNumber;
    char reserveMore = 'y';

    do {
    	cout << "\n===========================" << endl;
        displaySeats(seats);
        cout << "===========================" << endl;
	

        cout << "Bus Seat# Reservation\n\n";
        cout << "Customer Type: \n[S] - Senior \n[R] - Regular \n\nPlease Select Customer Type: ";
        cin >> customerType;
        customerType = toupper(customerType);

        while (!cin || (customerType != 'S' && customerType != 'R')) {
            cout << "Invalid input. Please enter 'S' for Senior or 'R' for Regular: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> customerType;
            customerType = toupper(customerType);
        }

        cout << "Enter seat number to reserve (1-17, except 8 and 18): ";
        while (!(cin >> seatNumber) || !isValidSeat(seatNumber, customerType) || !isSeatAvailable(seats, seatNumber)) {
            cout << "Invalid input or seat not available. Please enter a valid seat number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        reserveSeat(seats, seatNumber);
        cout << "Seat #" << seatNumber << " has been reserved successfully." << endl;

        cout << "Would you like to reserve another seat? (y/n): ";
        cin >> reserveMore;
        reserveMore = tolower(reserveMore);

        while (!cin || (reserveMore != 'y' && reserveMore != 'n')) {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> reserveMore;
            reserveMore = tolower(reserveMore);
        }
    } while (reserveMore == 'y');

    cout << "Thank you for using the reservation system." << endl;

    return 0;
}
