// Title: RailFence.h
// Author: Jeremy Dixon
// Date: 4/1/2022
// Description: This is part of the Cipher Project in CMSC 202 @ UMBC

#include "Cipher.h"
#include "RailFence.h"
#include <istream>
#include <string>
#include <iostream>
using namespace std;

// Name: RailFence (Default Constructor)
// Desc: Constructor to build an empty RailFence Cipher (Defaults to 3 rails)
// Preconditions - None
// Postconditions - Creates a RailFence cipher
RailFence::RailFence()
{
  m_rails = 3;
}
// Name: RailFence (Overloaded Constructor)
// Desc: Constructor to build a populated RailFence Cipher (Defaults to 3 rails)
// Preconditions - Pass it the message, isEncrypted, and number of rails (any integer)
// Postconditions - Creates a RailFence cipher to be encrypted
RailFence::RailFence(string message, bool isEncrypted, int rails)
{
  this->SetMessage(message);
  if (isEncrypted != this->GetIsEncrypted())
    this->ToggleEncrypted();
  this->m_rails = rails;
}
// Name: RailFence (Destructor)
// Desc: Destructor - Anything specific part of RailFence to delete?
// Preconditions - ~RailFence exists
// Postconditions - RailFence destroyed
RailFence::~RailFence()
{
}
// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void RailFence ::Encrypt()
{
  // create the matrix to cipher plain text
  // m_rails = rows , length(text) = columns
  string text = this->GetMessage();
  char rail[m_rails][(text.length())];

  // filling the rail matrix to distinguish filled
  // spaces from blank ones
  if (this->GetIsEncrypted() == false)
  {
    for (int i = 0; i < m_rails; i++)
      for (int j = 0; j < int(text.length()); j++)
        rail[i][j] = '\n';

    // to find the direction
    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < int(text.length()); i++)
    {
      // check the direction of flow
      // reverse the direction if we've just
      // filled the top or bottom rail
      if (row == 0 || row == m_rails - 1)
        dir_down = !dir_down;

      // fill the corresponding alphabet
      rail[row][col++] = text[i];

      // find the next row using direction flag
      dir_down ? row++ : row--;
    }

    // now we can construct the cipher using the rail matrix
    string result;
    for (int i = 0; i < m_rails; i++)
      for (int j = 0; j < int(text.length()); j++)
        if (rail[i][j] != '\n')
          result.push_back(rail[i][j]);

    this->SetMessage(result);
    this->ToggleEncrypted();
  }
}
// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void RailFence ::Decrypt()
{

  string cipher = this->GetMessage();
  char rail[m_rails][int(cipher.length())];

  // filling the rail matrix to distinguish filled
  // spaces from blank ones
  if (this->GetIsEncrypted() == true)
  {
    for (int i = 0; i < m_rails; i++)
      for (int j = 0; j < int(cipher.length()); j++)
        rail[i][j] = '\n';

    // to find the direction
    bool dir_down;

    int row = 0, col = 0;

    // mark the places with '*'
    for (int i = 0; i < int(cipher.length()); i++)
    {
      // check the direction of flow
      if (row == 0)
        dir_down = true;
      if (row == m_rails - 1)
        dir_down = false;

      // place the marker
      rail[row][col++] = '*';

      // find the next row using direction flag
      dir_down ? row++ : row--;
    }

    // now we can construct the fill the rail matrix
    int index = 0;
    for (int i = 0; i < m_rails; i++)
      for (int j = 0; j < int(cipher.length()); j++)
        if (rail[i][j] == '*' && index < int(cipher.length()))
          rail[i][j] = cipher[index++];

    // now read the matrix in zig-zag manner to construct
    // the resultant text
    string result;

    row = 0, col = 0;
    for (int i = 0; i < int(int(cipher.length())); i++)
    {
      // check the direction of flow
      if (row == 0)
        dir_down = true;
      if (row == m_rails - 1)
        dir_down = false;

      // place the marker
      if (rail[row][col] != '*')
        result.push_back(rail[row][col++]);

      // find the next row using direction flag
      dir_down ? row++ : row--;
    }
    this->SetMessage(result);
    this->ToggleEncrypted();
  }
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (RailFence in this case)
string RailFence ::ToString() { return "(RailFence)"; }
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - r, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_rails are returned for output
string RailFence ::FormatOutput()
{

  string rail; // to convert int type to string type
  stringstream s1;
  s1 << m_rails;
  s1 >> rail;

  string encryption; // to convert int type to string type
  stringstream s2;
  s2 << this->GetIsEncrypted();
  s2 >> encryption;

  string result = DELIMITER + encryption + DELIMITER + this->GetMessage() + DELIMITER + rail;
  result = "r" + result;
  return result;
}
