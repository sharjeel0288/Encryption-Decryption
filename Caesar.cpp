#include "Cipher.h"
#include <istream>
#include <string>
#include "Caesar.h"

using namespace std;

// Name: Caesar (Default Constructor)
// Desc: Constructor to build an empty Caesar Cipher (Defaults to shift 3)
// Preconditions - None
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar() {}
// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(string message, bool isEncrypted, int shift)
{
    this->SetMessage(message);
    if (isEncrypted != this->GetIsEncrypted())
        this->ToggleEncrypted();
    m_shift = shift;
}
// Name: Caesar (Destructor)
// Desc: Destructor - Anything specific to Caesar to delete?
// Preconditions - ~Caesar exists
// Postconditions - Caesar destroyed
Caesar::~Caesar() {}
// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Caesar::Encrypt()
{
    if (this->GetIsEncrypted() == false)
    {
        string message;
        char ch;
        int i, key;
        message = this->GetMessage();
        key = this->m_shift;
        for (i = 0; i < int(message.length()); ++i)
        {
            ch = message[i];
            if (ch >= 'a' && ch <= 'z') // if lower case
            {
                ch = ch + key;
                if (ch > 'z') // if ch exceed from z then bring it again in the lower case
                {
                    ch = ch - 'z' + 'a' - 1; 
                }
                message[i] = ch;
            }
            else if (ch >= 'A' && ch <= 'Z') // if ch i an upper case
            {
                ch = ch + key;
                if (ch > 'Z')
                {
                    ch = ch - 'Z' + 'A' - 1;
                }
                message[i] = ch;
            }
        }
        this->SetMessage(message);
        this->ToggleEncrypted();
    }
}
// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
void Caesar::Decrypt()
{
    if (this->GetIsEncrypted() == true) //if already encrypted then don't do it again
    {
        string message;
        char ch;
        int i, key;
        message = this->GetMessage();
        key = this->m_shift;
        for (i = 0; i < int(message.length()); ++i)
        {
            ch = message[i];
            if (ch >= 'a' && ch <= 'z')
            {
                ch = ch - key;
                if (ch < 'a')
                {
                    ch = ch + 'z' - 'a' + 1;
                }
                message[i] = ch;
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                ch = ch - key;
                if (ch < 'A')
                {
                    ch = ch + 'Z' - 'A' + 1;
                }
                message[i] = ch;
            }
        }
        this->SetMessage(message);
        this->ToggleEncrypted();
    }
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Caesar in this case)
string Caesar::ToString() { return "(Caesar)"; }
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_shift are returned for output
string Caesar::FormatOutput()
{
    string shift; // to convert int type to string type
    stringstream s1;
    s1 << m_shift;
    s1 >> shift;

    string encryption; // to convert int type to string type
    stringstream s2;
    s2 << this->GetIsEncrypted();
    s2 >> encryption;

    string result = DELIMITER + encryption + DELIMITER + this->GetMessage() + DELIMITER + shift;
    result = "c" + result;
    return result;
}