#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

void printKey(const string& key);
string readKeyFromConsole();
string generateKey(ifstream& inputFile, const string& key);
void encryptBill(ifstream& inputFile, const string& key, ofstream& outputFile);
void decryptBill(ifstream& inputFile, const string& key, ofstream& outputFile);
bool openInputFileBl(const string& name, ifstream& fileStream);
bool openOutputFileBl(const string& name, ofstream& fileStream);

extern "C" int cipher_run();

#endif
