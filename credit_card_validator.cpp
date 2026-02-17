#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

// ANSI Escape Codes for Terminal Colors
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[1;32m";
const std::string RED = "\033[1;31m";
const std::string CYAN = "\033[1;36m";
const std::string YELLOW = "\033[1;33m";

// Function Prototypes
std::string sanitizeInput(const std::string& input);
bool isValidLuhn(const std::string& ccNumber);
std::string getCardIssuer(const std::string& ccNumber);
void displayMenu();

int main() {
    bool running = true;
    std::string rawInput;

    std::cout << CYAN << "=======================================\n";
    std::cout << "  Secure Credit Card Validator v2.0\n";
    std::cout << "=======================================\n" << RESET;

    while (running) {
        displayMenu();
        std::getline(std::cin, rawInput);

        if (rawInput == "2" || rawInput == "exit" || rawInput == "quit") {
            std::cout << "Shutting down validator. Goodbye!\n";
            running = false;
            continue;
        } 
        else if (rawInput != "1") {
            std::cout << RED << "Invalid option. Please enter 1 or 2.\n" << RESET;
            continue;
        }

        std::cout << "\nEnter a credit card number to validate: ";
        std::getline(std::cin, rawInput);

        // 1. Sanitize the input (remove spaces and dashes)
        std::string cleanNumber = sanitizeInput(rawInput);

        // 2. Edge case handling (empty input or letters)
        if (cleanNumber.empty()) {
            std::cout << RED << "[ERROR] Invalid input. Only numbers are allowed.\n" << RESET;
            continue;
        }

        // 3. Process the Luhn Algorithm
        std::cout << "Processing checksum...\n";
        bool isValid = isValidLuhn(cleanNumber);

        // 4. Output Results
        if (isValid) {
            std::string issuer = getCardIssuer(cleanNumber);
            std::cout << GREEN << "[SUCCESS] Valid Credit Card Detected!\n" << RESET;
            std::cout << YELLOW << "-> Issuer/Network: " << issuer << "\n" << RESET;
        } else {
            std::cout << RED << "[FAILED] Invalid Credit Card Number.\n" << RESET;
            std::cout << "-> Fails Luhn Algorithm Checksum.\n";
        }
    }

    return 0;
}

void displayMenu() {
    std::cout << "\n[1] Validate a Card Number\n";
    std::cout << "[2] Exit\n";
    std::cout << "Select an option: ";
}

// Removes any spaces or hyphens the user might have typed
std::string sanitizeInput(const std::string& input) {
    std::string sanitized = "";
    for (char c : input) {
        if (isdigit(c)) {
            sanitized += c;
        } else if (c != ' ' && c != '-') {
            // If it's a letter or special char, return empty to trigger an error
            return ""; 
        }
    }
    return sanitized;
}

// Corrected single-pass Luhn Algorithm
bool isValidLuhn(const std::string& ccNumber) {
    int sum = 0;
    bool alternate = false;

    // Traverse the card number from right to left
    for (int i = ccNumber.length() - 1; i >= 0; i--) {
        int n = ccNumber[i] - '0';

        if (alternate) {
            n *= 2;
            // If doubling results in a two-digit number, add the digits (e.g., 18 -> 1+8 = 9)
            // A math shortcut for this is subtracting 9 from the number (18 - 9 = 9)
            if (n > 9) {
                n -= 9;
            }
        }
        sum += n;
        alternate = !alternate; // Toggle the alternate flag
    }
    return (sum % 10 == 0);
}

// Checks the starting digits (IIN) and length to determine the card network
std::string getCardIssuer(const std::string& ccNumber) {
    int length = ccNumber.length();
    
    // American Express: Length 15, starts with 34 or 37
    if (length == 15 && (ccNumber.substr(0, 2) == "34" || ccNumber.substr(0, 2) == "37")) {
        return "American Express (Amex)";
    }
    // Visa: Length 13 or 16, starts with 4
    else if ((length == 13 || length == 16) && ccNumber[0] == '4') {
        return "Visa";
    }
    // MasterCard: Length 16, starts with 51-55
    else if (length == 16 && (ccNumber.substr(0, 2) >= "51" && ccNumber.substr(0, 2) <= "55")) {
        return "MasterCard";
    }
    // Discover: Length 16, starts with 6011
    else if (length == 16 && ccNumber.substr(0, 4) == "6011") {
        return "Discover";
    }
    
    return "Unknown / Other Network";
}
