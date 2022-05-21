#include "Cipher.h"
#include <istream>
#include <string>
#include <math.h>
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
    m_keyWord = key;
    for (int i = 0;; i++)
    {
        if (x == i)
            i = 0;
        if (key.size() == message.size())
            break;
        key.push_back(key[i]);
    }
    this->m_key = key;
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
static int Mod(int a, int b)
{
    return (a % b + b) % b;
}
void Vigenere::Encrypt()
{

    if (this->GetIsEncrypted() == false)
    {
        bool encipher = true;
        string input=this->GetMessage();
        int keyLen = m_keyWord.size();

        for (int i = 0; i < keyLen; ++i)
            if (!isalpha(m_keyWord[i]))
               ; // Error

        string output = "";
        int nonAlphaCharCount = 0;
        int inputLen = input.size();

        for (int i = 0; i < inputLen; ++i)
        {
            if (isalpha(input[i]))
            {
                bool cIsUpper = isupper(input[i]);
                char offset = cIsUpper ? 'A' : 'a';
                int keyIndex = (i - nonAlphaCharCount) % keyLen;
                int k = (cIsUpper ? toupper(m_keyWord[keyIndex]) : tolower(m_keyWord[keyIndex])) - offset;
                k = encipher ? k : -k;
                char ch = (char)((Mod(((input[i] + k) - offset), 26)) + offset);
                output += ch;
            }
            else
            {
                output += input[i];
                ++nonAlphaCharCount;
            }
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
        bool encipher = false;
        string input = this->GetMessage();
        int keyLen = m_keyWord.size();

        for (int i = 0; i < keyLen; ++i)
            if (!isalpha(m_keyWord[i]))
                ; // Error

        string output = "";
        int nonAlphaCharCount = 0;
        int inputLen = input.size();

        for (int i = 0; i < inputLen; ++i)
        {
            if (isalpha(input[i]))
            {
                bool cIsUpper = isupper(input[i]);
                char offset = cIsUpper ? 'A' : 'a';
                int keyIndex = (i - nonAlphaCharCount) % keyLen;
                int k = (cIsUpper ? toupper(m_keyWord[keyIndex]) : tolower(m_keyWord[keyIndex])) - offset;
                k = encipher ? k : -k;
                char ch = (char)((Mod(((input[i] + k) - offset), 26)) + offset);
                output += ch;
            }
            else
            {
                output += input[i];
                ++nonAlphaCharCount;
            }
        }
        this->SetMessage(output);
        this->ToggleEncrypted();
    }
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Vigenere in this case)
string Vigenere::ToString()
{
    return "(Vigenere)";
}
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

    string result = DELIMITER + encryption + DELIMITER + this->GetMessage() + DELIMITER + m_keyWord;
    result = "v" + result;
    return result;
}