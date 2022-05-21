// Title: Vigenere.h
// Author: Jeremy Dixon
// Date: 4/1/2022
// Description: This is part of the Cipher Project in CMSC 202 @ UMBC
#ifndef VIGENERE_H
#define VIGENERE_H
#include "Cipher.h"
#include <istream>
#include <string>
using namespace std;

class Vigenere : public Cipher
{
public:
    // Name: Vigenere (Default Constructor)
    // Desc: Constructor to build an empty Vigenere Cipher (Defaults to shift 3)
    // Preconditions - None
    // Postconditions - Creates a Vigenere cipher to be encrypted
    Vigenere();
    // Name: Vigenere (Overloaded Constructor)
    // Desc: Constructor to build a populated Vigenere Cipher (Defaults to shift 3)
    // Preconditions - Pass it the message, isEncrypted, and shift (any integer)
    // Postconditions - Creates a Vigenere cipher to be encrypted
    Vigenere(string, bool, string);
    // Name: Vigenere (Destructor)
    // Desc: Destructor - Anything specific to Vigenere to delete?
    // Preconditions - ~Vigenere exists
    // Postconditions - Vigenere destroyed
    ~Vigenere();
    // Name: Encrypt
    // Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
    // Preconditions - Message exists
    // Postconditions - Shifts each character "right".
    void Encrypt();
    // Name: Decrypt
    // Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
    // Preconditions - Message exists
    // Postconditions - Shifts each character "left".
    void Decrypt();
    // Name: ToString
    // Desc - A function that returns the string of the object type
    // Preconditions - The object exists
    // Postconditions - The subtype is returned (Vigenere in this case)
    string ToString();
    // Name: FormatOutput()
    // Desc - A function that returns the formatted output for Output function
    // Preconditions - The object exists (use stringstream)
    // Postconditions - c, delimiter, isencrypted, delimiter,
    //                  message, delimiter, m_shift are returned for output
    string FormatOutput();

private:
    string m_keyWord, m_key; // Number of characters to shift. (A shift 3 = D) (D shift -3 = A)
};

#endif
