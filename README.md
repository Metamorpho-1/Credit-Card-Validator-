#  Secure Credit Card Validator (C++)

Hey there!  Welcome to my Secure Credit Card Validator.

I originally wrote this as a basic mathematical exercise to understand the Luhn algorithm. However, I decided to scale it up into a robust, interactive Command Line Interface (CLI) tool that handles real-world, messy data just like a production backend would. 

*Disclaimer: This tool operates entirely locally in your terminal. It does not store, log, or transmit any credit card data.*

##  Core Features

* **Single-Pass Luhn Algorithm:** I optimized the core checksum logic to run in $O(N)$ time complexity. Instead of looping through the card number multiple times for odd and even digits, it computes the entire validation in a single pass using a boolean toggle.
* **Input Sanitization:** Real users type spaces and dashes (e.g., `4532-1234...`). This application intercepts the raw input, safely strips out non-numeric characters, and flags invalid inputs (like letters) before they can crash the program.
* **Issuer Identification (IIN):** It doesn't just tell you if a card is valid; it parses the starting digits and length to identify the network (Visa, MasterCard, American Express, or Discover).
* **Interactive Terminal UX:** Wrapped in a continuous menu loop with ANSI color coding, making the CLI intuitive and easy to read.

##  How to Run It Locally

You will need a standard C++ compiler (like `g++`) installed on your machine.

1. Clone this repository:
   ```bash
   git clone [https://github.com/YOUR-USERNAME/cc-validator-cpp.git](https://github.com/YOUR-USERNAME/cc-validator-cpp.git)
   cd cc-validator-cpp

2. Compile the code
   ```bash
   g++ cc_validator.cpp -o validator

3. Run the application
   ```bash
   ./validator

##How It Works (The Math)

This tool uses the Luhn Algorithm (Modulus 10), which is the global standard used by banks to validate identification numbers.

1. Starting from the rightmost digit, it doubles the value of every second digit.

2. If doubling a number results in a two-digit number (e.g., 9 * 2 = 18), it adds those digits together (1 + 8 = 9).

3. It sums all the modified digits and the unmodified digits.

4. If the total modulo 10 equals zero, the card number is mathematically valid.

##What I Learned

Building this utility solidified my understanding of:

1. String Manipulation in C++: Efficiently parsing, iterating, and extracting substrings (std::string::substr) to check industry prefixes.

2. Algorithmic Optimization: Refactoring brute-force math into elegant, single-pass loops.

3. Defensive Programming: Anticipating edge cases (like empty strings or alphabetical inputs) and handling them gracefully without breaking the runtime loop.
