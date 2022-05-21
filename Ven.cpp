#include "Cipher.h"
#include <istream>
#include <string>
#include "Vigenere.h"

using namespace std;

// Name: Vigenere (Default Constructor)
// Desc: Constructor to build an empty Vigenere Cipher (Defaults to shift 3)
// Preconditions - None
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere() {}
// Name: Vigenere (Overloaded Constructor)
// Desc: Constructor to build a populated Vigenere Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere(string message, bool isEncrypted, string key)
{
    this->SetMessage(message);
    if (isEncrypted != this->GetIsEncrypted())
        this->ToggleEncrypted();

    int x = message.size();
    keyWord = key;
    for (int i = 0;; i++)
    {
        if (x == i)
            i = 0;
        if (key.size() == message.size())
            break;
        key.push_back(key[i]);
    }
    this->key = key;
}
// Name: Vigenere (Destructor)
// Desc: Destructor - Anything specific to Vigenere to delete?
// Preconditions - ~Vigenere exists
// Postconditions - Vigenere destroyed
Vigenere::~Vigenere() {}
// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Vigenere::Encrypt()
{

    if (this->GetIsEncrypted() == false)
    {
        string t = this->GetMessage();
        string output;
        for (int i = 0, j = 0; i < t.length(); ++i)
        {
            char c = t[i];
            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;
            output += (c + key[j] - 2 * 'A') % 26 + 'A'; // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
            j = (j + 1) % key.length();
        }
        this->SetMessage(output);
        this->ToggleEncrypted();
    }
}
// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
void Vigenere::Decrypt()
{
    if (this->GetIsEncrypted() == true)
    {
        string t = this->GetMessage();

        string output;
        for (int i = 0, j = 0; i < t.length(); ++i)
        {
            char c = t[i];
            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;
            output += (c - key[j] + 26) % 26 + 'A'; // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
            j = (j + 1) % key.length();
        }
        this->SetMessage(output);
        this->ToggleEncrypted();
    }
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Vigenere in this case)
string Vigenere::ToString() { return "(Vigenere)"; }
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_shift are returned for output
string Vigenere::FormatOutput()
{
    string shift; // to convert int type to string type

    string encryption; // to convert int type to string type
    stringstream s2;
    s2 << this->GetIsEncrypted();
    s2 >> encryption;

    string result = DELIMITER + encryption + DELIMITER + this->GetMessage() + DELIMITER + keyWord;
    result = "v" + result;
    return result;
}