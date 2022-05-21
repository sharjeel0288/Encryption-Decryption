#include "Cipher.h"
#include "Caesar.h"
#include "RailFence.h"
#include "Ong.h"
#include "CipherTool.h"
#include "Vigenere.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string file)
{
    m_filename = file;
}
// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers deallocated and vector emptied
CipherTool::~CipherTool()
{
    for (int j = 0, i = m_ciphers.size(); j < i; j++) // iterates through each item in m_routes and deallocates memory
    {
        Cipher *p = m_ciphers.at(j);

        delete (p);
    }
    m_ciphers.clear();
    m_ciphers.shrink_to_fit();
}
// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (c is Caesar, r is RailFence, and o is Ong)
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile()
{
    ifstream input;
    input.open(m_filename);
    bool success = true;
    Caesar *ceasar = nullptr;
    Ong *ong = nullptr;
    Vigenere *vig = nullptr;
    RailFence *railfence = nullptr;
    while (success) // success condition for a successful read file and push_back
    {
        string type, isEncrypted, Msg, SHIFT;
        double shift;
        getline(input, type, '|');
        if (type.length() <= 0)
            success = false;
        getline(input, isEncrypted, DELIMITER);
        getline(input, Msg, DELIMITER);
        getline(input, SHIFT);
        // cout << Msg << "  " << type << "  " << isEncrypted << endl;
        if (success != false)
        {
            if (SHIFT.length() > 0 && type != "o" && type != "v")
                shift = stoi(SHIFT);
            if (type == "c")
            {
                ceasar = new Caesar(Msg, this->StringToBoolean(isEncrypted), shift);
                m_ciphers.push_back(ceasar);
            }
            if (type == "r")
            {
                railfence = new RailFence(Msg, this->StringToBoolean(isEncrypted), shift);
                m_ciphers.push_back(railfence);
            }
            if (type == "o")
            {
                ong = new Ong(Msg, this->StringToBoolean(isEncrypted));
                m_ciphers.push_back(ong);
            }
            if (type == "v")
            {
                vig = new Vigenere(Msg, this->StringToBoolean(isEncrypted), SHIFT);
                m_ciphers.push_back(vig);
            }
        }
    }
    ong = nullptr;
    ceasar = nullptr;
    railfence = nullptr;
    delete (ong);
    delete (ceasar);
    delete (railfence);
    cout << "Opened File" << endl;
    // cout << "Ports loaded: " << m_ports.size() << endl;
    input.close();
}
// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
// Preconditions - Passed string of either 0 or 1
// Postconditions - Returns false if 0 else true
bool CipherTool::StringToBoolean(string input)
{
    if (input == "0")
        return false;
    return true;
}
// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers()
{
    for (int i = 0; i < int(m_ciphers.size()); i++)
    {
        cout << i + 1 << ". ";
        cout << *m_ciphers.at(i);
    }
}
// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool performEncryption)
{
    int enc = 0, dec = 0;
    for (int i = 0; i < int(m_ciphers.size()); i++) // to count no. of encryption or decryption
    {
        if (m_ciphers.at(i)->GetIsEncrypted() == false)
            enc++;
        else
            dec++;
    }

    for (int i = 0; i < int(m_ciphers.size()); i++)
    {
        if (performEncryption)
        {
            if (m_ciphers.at(i)->GetIsEncrypted() == false)
                m_ciphers.at(i)->Encrypt();
        }
        else
        {
            if (m_ciphers.at(i)->GetIsEncrypted() == true)
                m_ciphers.at(i)->Decrypt();
        }
    }
    if (performEncryption)
        cout << enc << " ciphers Encrypted" << endl;
    else
        cout << dec << " ciphers Decrypted" << endl;
}
// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export()
{
    string file;
    cout << "Enter file Name : ";
    cin >> file;
    ofstream MyFile(file);
    if (!MyFile)
    {
        cout << "File not created!" << endl;
    }
    else
    {
        cout << "Export to file successfully!" << endl;
    }
    for (int i = 0; i < int(m_ciphers.size()); i++)
    {
        // cout<< m_ciphers.at(i)->FormatOutput()<<endl;
        MyFile << m_ciphers.at(i)->FormatOutput() << endl;
    }
    MyFile.close();
}
// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu()
{
    int choice;
    do
    {
        cout << "What would you like to do?" << endl;
        cout << "1. Display All Ciphers" << endl;
        cout << "2. Encrypt All Ciphers" << endl;
        cout << "3. Decrypt All Ciphers" << endl;
        cout << "4. Export All Ciphers" << endl;
        cout << "5. QUIT" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            this->DisplayCiphers();
            break;
        case 2:
            this->EncryptDecrypt(true);
            break;
        case 3:
            this->EncryptDecrypt(false);
            break;
        case 4:
            this->Export();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice selected, please try again!" << endl;
            break;
        }

    } while (choice != 5);
    return 0;
}
// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start()
{
    this->LoadFile();
    this->Menu();
}