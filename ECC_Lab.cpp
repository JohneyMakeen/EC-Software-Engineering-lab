#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Function to extract numeric values from a string
double extractNumber(const string& str) {
    bool hasDecimal = false;  // This will tracksif a decimal point exists
    bool hasSign = false;     // This will track if a sign exists at the beginning
    string valid_number = "";  // This will store the valid numeric part

    // Traverses over each character in the string to check if its valid
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
// we first initilize i to 0, then check if i is less than the total number of characthers in the string, increment by 1, and then str[i] recieves the characther at position i in the string

        // Check if the character is a digit
        if (isdigit(c)) {
            valid_number += c; // if it is a digit, then we append the characher to the valid numeric part
        }
        // Check if the character is a decimal point
        else if (c == '.') {
            if (hasDecimal) {
                return -999999.99; // Invalid if more than one decimal point
            }
            hasDecimal = true; // Mark that we found a decimal point (yipee!)
            valid_number += c;  // Append decimal point to valid_number
        }
        // Checks if the character is a sign (+ or -) at the beginning
        else if ((c == '+' || c == '-') && i == 0) {
            if (hasSign) {
                return -999999.99; // Invalid if more than one sign
            }
            hasSign = true; // Mark that we found a sign (yippee!)
            valid_number += c; // Append sign to valid_number
        }
        // If the character is invalid
        else {
            return -999999.99; // Return invalid for any other character
        }
    }

    // Ensure the number is not empty or ends with a decimal point
    if (valid_number.empty() || valid_number.back() == '.') {
        return -999999.99;
    }

    // Manually convert the valid_number to a double precision number as desired
    double result = 0.0;
    bool isNegative = (valid_number[0] == '-'); // Check if the number is negative
    int start = (valid_number[0] == '+' || valid_number[0] == '-') ? 1 : 0; // Skip the sign if present
    bool afterDecimal = false;
    double decimalMultiplier = 0.1;

    for (int i = start; i < valid_number.length(); i++) { // iterating through each characther in valid_number from the start of the string to the end
        if (valid_number[i] == '.') {
            afterDecimal = true; // Start processing decimal part
            continue;
        }
        int digit = valid_number[i] - '0'; // Converts the current char to an int
        if (afterDecimal) { // if the loop is processing a decimal
            result += digit * decimalMultiplier; // the first digit will be 4 * 0.1 = 0.4, added to result
            decimalMultiplier /= 10; // reduces by a factor 10 for the next digit
        } else {
            result = result * 10 + digit; // if the loop isnt processing a decimal, result will be updated
        }
    }

    return isNegative ? -result : result; // Apply the sign if negative (true), or dont apply the sign if its positive (false)
}

int main() {
    string input; // Variable to store user input

    while (true) {
        cout << "Enter a string (or 'END' to quit): "; // Prompt user for input
        cin >> input; // Read the input string

        if (input == "END") { // Check if the user wants to quit
            break;
        }

        // Call the extractNumber function to validate and extract the number
        double number = extractNumber(input);

        if (number != -999999.99) {
            // If the number is valid, display it with fixed-point notation
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            // If the number is invalid, display an error message
            cout << "The input is invalid." << endl;
        }
    }

    return 0; // End the program
}
