/*****Please include following header files*****/
// string
// ctype.h
/***********************************************/

/*****Please use following namespaces*****/
// std
/*****************************************/
#include <string>
#include <iostream>
using namespace std;
static int Mod(int a, int b)
{
    return (a % b + b) % b;
}

static string Cipher(string input, string key, bool encipher)
{
}

static string Encipher(string input, string key)
{
    bool encipher = true;
    int keyLen = key.size();

    for (int i = 0; i < keyLen; ++i)
        if (!isalpha(key[i]))
            return ""; // Error

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
            int k = (cIsUpper ? toupper(key[keyIndex]) : tolower(key[keyIndex])) - offset;
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

    return output;
}

static string Decipher(string input, string key)
{
    bool encipher = false;
    int keyLen = key.size();

    for (int i = 0; i < keyLen; ++i)
        if (!isalpha(key[i]))
            return ""; // Error

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
            int k = (cIsUpper ? toupper(key[keyIndex]) : tolower(key[keyIndex])) - offset;
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

    return output;
}
int main()
{

    string text = "Never leave that till tomorrow which you can do today. (Benjamin Franklin)";
    string cipherText = Encipher(text, "happy");
    string plainText = Decipher(cipherText, "happy");
    cout << "encrypted : " << cipherText << endl
         << "Decrypted : " << plainText << endl;
}