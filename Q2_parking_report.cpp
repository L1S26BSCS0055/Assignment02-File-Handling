
/*
 * Name       : Abdullah Wahaj
 * Reg No     : L1S26BSCS0055
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    ifstream inFile("parking.txt");

    if (!inFile)
    {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int day, month, year;
    char slash;

    inFile >> day >> slash >> month >> slash >> year;

    // Skip the date line and column headings.
    inFile.ignore(1000, '\n');
    inFile.ignore(1000, '\n');

    ofstream outFile("receipts.txt");

    outFile << "Receipts for "
        << day << "/" << month << "/" << year << endl;

    cout << "Parking report for "
        << day << "/" << month << "/" << year << endl;

    char plate[15];
    char type;
    char inColon, outColon;

    int inHour, inMin, outHour, outMin;

    int vehicles = 0;
    int cars = 0;
    int bikes = 0;
    int totalCollected = 0;

    int longestMinutes = -1;
    char longestPlate[15] = "";
    int longestHours = 0;
    int longestRemainder = 0;

    while (inFile >> plate >> type
        >> inHour >> inColon >> inMin
        >> outHour >> outColon >> outMin)
    {
        int startMinutes = inHour * 60 + inMin;
        int endMinutes = outHour * 60 + outMin;

        int parkedMinutes = endMinutes - startMinutes;

        // Charge for every started hour.
        int hoursCharged = (parkedMinutes + 59) / 60;

        // Even zero minutes costs one hour.
        if (hoursCharged == 0)
        {
            hoursCharged = 1;
        }

        int fee;

        if (type == 'C')
        {
            fee = hoursCharged * 100;
            cars++;
        }
        else
        {
            fee = hoursCharged * 40;
            bikes++;
        }

        // Actual parking duration, not charged hours.
        int actualHours = parkedMinutes / 60;
        int remainingMinutes = parkedMinutes % 60;

        if (type == 'C')
        {
            cout << plate << " Car ";
        }
        else
        {
            cout << plate << " Bike ";
        }

        cout << actualHours << " h "
            << remainingMinutes << " min Fee: "
            << fee << endl;

        outFile << plate << " " << fee << endl;

        vehicles++;
        totalCollected += fee;

        if (parkedMinutes > longestMinutes)
        {
            longestMinutes = parkedMinutes;

            strcpy(longestPlate, plate);

            longestHours = actualHours;
            longestRemainder = remainingMinutes;
        }
    }

    if (vehicles == 0)
    {
        cout << "No vehicles found!" << endl;
    }
    else
    {
        cout << "Vehicles: " << vehicles << endl;

        cout << "Cars: " << cars
            << " Bikes: " << bikes << endl;

        cout << "Total collected: "
            << totalCollected << endl;

        cout << "Longest stay: " << longestPlate
            << " (" << longestHours << " h "
            << longestRemainder << " min)"
            << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}
