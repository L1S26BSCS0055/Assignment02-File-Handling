
/*
 * Name       : Abdullah Wahaj
 * Reg No     : L1S26BSCS0055
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

 // FIX 1: Include fstream because file streams are used below.
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");

    // FIX 2: Check if the input file failed to open.
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: Use append mode to preserve existing reorder.txt lines.
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;

    // FIX 4: Use double so the total keeps decimal values.
    double total = 0;

    // FIX 5: Skip the header row before reading the stock items.
    inFile.ignore(1000, '\n');

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;

        if (qty < 10) {
            // FIX 6: Add endl to write each item on a separate line.
            reorder << code << " " << qty << endl;
            low++;
        }
    }

    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;

    return 0;
}
