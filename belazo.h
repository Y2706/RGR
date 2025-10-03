#ifndef BELAZO_H
#define BELAZO_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

void encryptBelazo(ifstream& inputFile, const string& key, ofstream& outputFile);
void decryptBelazo(ifstream& inputFile, const string& key, ofstream& outputFile);
bool openInputFileB(const string& name, ifstream& fileStream);
bool openOutputFileB(const string& name, ofstream& fileStream);
int cipher_belazo();

#endif