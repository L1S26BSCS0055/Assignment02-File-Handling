
/*
 * Name       : Abdullah Wahaj
 * Reg No     : L1S26BSCS0055
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    char path[100];
    char name[30];
    char topName[30] = "";

    int n;
    int count = 0;
    int eligible = 0;

    double cgpa;
    double totalCGPA = 0;
    double highestCGPA = -1;

    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);

    if (!inFile.is_open())
    {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    ofstream outFile("scholarship.txt");

    if (!(inFile >> n))
    {
        cout << "No students found!" << endl;
        inFile.close();
        outFile.close();
        return 0;
    }

    if (n > 30)
    {
        cout << "Too many students!" << endl;
        inFile.close();
        outFile.close();
        return 0;
    }

    inFile.ignore(1000, '\n');

    for (int i = 0; i < n; i++)
    {
        if (!inFile.getline(name, 30, ','))
        {
            break;
        }

        if (!(inFile >> cgpa))
        {
            break;
        }

        inFile.ignore(1000, '\n');

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        count++;
        totalCGPA += cgpa;

        if (cgpa >= 3.50)
        {
            outFile << name << "," << cgpa << endl;
            eligible++;
        }

        // Update only for a strictly higher CGPA,
        // so the first student wins a tie.
        if (cgpa > highestCGPA)
        {
            highestCGPA = cgpa;
            strcpy(topName, name);
        }
    }

    if (count < n)
    {
        cout << "Warning: only " << count
            << " of " << n << " records found." << endl;
    }

    if (count == 0)
    {
        cout << "No students found!" << endl;
    }
    else
    {
        cout << "Students: " << count << endl;

        cout << "Average CGPA: "
            << totalCGPA / count << endl;

        cout << "Eligible for scholarship: "
            << eligible << endl;

        cout << "Top student: " << topName
            << " (" << highestCGPA << ")" << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}
