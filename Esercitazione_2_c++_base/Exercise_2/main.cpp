#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/// \brief ImportText import the text for encryption
/// \param inputFilePath: the input file path
/// \param text: the resulting text
/// \return the result of the operation, true is success, false is error
bool ImportText(const string& inputFilePath,
                string& text);

/// \brief Encrypt encrypt the text
/// \param text: the text to encrypt
/// \param password: the password for encryption
/// \param encryptedText: the resulting encrypted text
/// \return the result of the operation, true is success, false is error
bool Encrypt(const string& text,
             const string& password,
             string& encryptedText);

/// \brief Decrypt decrypt the text
/// \param text: the text to decrypt
/// \param password: the password for decryption
/// \param decryptedText: the resulting decrypted text
/// \return the result of the operation, true is success, false is error
bool Decrypt(const string& text,
             const string& password,
             string& decryptedText);

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    cerr<< "Password shall passed to the program"<< endl;
    return -1;
  }
  string password = argv[1];

  string inputFileName = "./text.txt", text;
  if (!ImportText(inputFileName, text))
  {
    cerr<< "Something goes wrong with import"<< endl;
    return -1;
  }
  else
    cout<< "Import successful: result= "<< text<< endl;

  string encryptedText;
  if (!Encrypt(text, password, encryptedText))
  {
    cerr<< "Something goes wrong with encryption"<< endl;
    return -1;
  }
  else
    cout<< "Encryption successful: result= "<< encryptedText<< endl;

  string decryptedText;
  if (!Decrypt(encryptedText, password, decryptedText) /*|| text != decryptedText*/)
  {
    cerr<< "Something goes wrong with decryption"<< endl;
    return -1;
  }
  else
    cout<< "Decryption successful: result= "<< decryptedText<< endl;

  return 0;
}

bool ImportText(const string& inputFilePath,
                string& text)
{
    ifstream myFile(inputFilePath);

    if(!myFile.is_open())
        return false;

    getline(myFile,text);

    return true;
}

bool Encrypt(const string& text,
             const string& password,
             string& encryptedText)
{
    if(password.size() > text.size())
        return false;

    for(unsigned int i = 0; i < password.size(); i++){
        if(password[i] < 65 || password[i] > 90)
            return false;
    }

    unsigned int cont = 0;
    encryptedText = text;

    for(unsigned int i = 0; i < text.size(); i++){
        if(text[i] != ' '){
            encryptedText[i] = ((text[i] - 65) + (password[cont % password.size()] - 65))%26 + 65;
            cont++;
        }
    }

    return true;
}

bool Decrypt(const string& text,
             const string& password,
             string& decryptedText)
{
    unsigned int cont = 0;
    decryptedText = text;

    for(unsigned int i = 0; i < text.size(); i++){
        if(text[i] != ' '){
            decryptedText[i] = text[i] - password[cont % password.size()] + 65;
            if(text[i] - password[cont % password.size()] < 0){
                decryptedText[i] += 26;
            }
            cont++;
        }
    }

    return  true;
}
