#ifndef PORTA_H
#define PORTA_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

void encryptPorta(ifstream& inputFile, const string& key, ofstream& outputFile);
void decryptPorta(ifstream& inputFile, const string& key, ofstream& outputFile);
bool openInputFileP(const string& name, ifstream& fileStream);
bool openOutputFileP(const string& name, ofstream& fileStream);

extern "C" int cipher_run();

#endif
