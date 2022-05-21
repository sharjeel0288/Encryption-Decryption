#include "Cipher.h"
#include <istream>
#include <string>
#include <vector>
#include "Ong.h"

using namespace std;

// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong() {}
// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted)
{
    this->SetMessage(message);
    if (isEncrypted != this->GetIsEncrypted())
        this->ToggleEncrypted();
}
// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong() {}
// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char c)
{
    if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U')
        return true;
    if ((c >= 33 && c <= 47))
        return true;
    return false;
}
// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt()
{
    string temp = this->GetMessage();
    string encryptMsg = "";
    bool isspace = true;
    char c = temp[0];
    string desh = "-";
    if (this->GetIsEncrypted() == false) // for first char 
    {
        if (this->IsVowel(c))
        {
            encryptMsg = c; // if vowel simply copy it in encryptMsg
            // cout << "space if" << endl;
        }
        else
        {
            encryptMsg = c + ong; //if not a vowel add ong
            // cout << "space else" << endl;
        }
        for (int i = 1; i < int(temp.size()); i++)
        {
            c = temp[i];
            if (c == ' ') // check for the space
                isspace = true;
            else
                isspace = false;
            if (isspace)
            {
                if (IsVowel(c))
                {
                    encryptMsg += "" + c; // if  space followed by a vowel simply copy it in encryptMsg
                }
                else
                {
                    encryptMsg += c + ong; // if  space followed by a consonant then add ong 
                }
            }
            else
            {
                if (IsVowel(c))
                {
                    encryptMsg += desh + (c);  // if   a vowel simply add desh and copy it in encryptMsg
                }
                else
                {
                    encryptMsg += desh + (c) + ong;
                }
            }
        }
        // Get the first occurrence
        string toSearch = " ong-", replaceStr = " "; // for removing extra and unwanted ong
        size_t pos = encryptMsg.find(toSearch);
        // Repeat till end is reached
        while (pos != std::string::npos)
        {
            // Replace this occurrence of Sub String
            encryptMsg.replace(pos, toSearch.size(), replaceStr);
            // Get the next occurrence from the current position
            pos = encryptMsg.find(toSearch, pos + replaceStr.size());
        }
        this->SetMessage(encryptMsg);
        this->ToggleEncrypted();
    }
}
// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Double check words like "wrong" so that they work correctly!
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt()
{
    string temp = this->GetMessage();
    size_t pos = std::string::npos;
    string toErase = "ong";
    // Search for the substring in string in a loop untill nothing is found
    if (this->GetIsEncrypted() == true) // if already decrypted then do nothing
    {
        while ((pos = temp.find(toErase)) != std::string::npos) // to erase ong
        {
            // If found then erase it from string
            temp.erase(pos, toErase.length());
        }
        toErase = "-";
        // Search for the substring in string in a loop untill nothing is found
        while ((pos = temp.find(toErase)) != std::string::npos) // to erase desh
        {
            // If found then erase it from string
            temp.erase(pos, toErase.length());
        }
        this->SetMessage(temp);
        this->ToggleEncrypted();
    }
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString() { return "(Ong)"; }
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput()
{
    string encryption; // to convert int type to string type
    stringstream s1;
    s1 << this->GetIsEncrypted();
    s1 >> encryption;
    string result = DELIMITER + encryption + DELIMITER + this->GetMessage() + DELIMITER;
    result = "o" + result;

    return result;
}