#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "bill.h"

using namespace std;

void printKey(const string& key) {
    cout << "Ваш ключ: ";
    for (char c : key) {
        cout << static_cast<int>(static_cast<unsigned char>(c)) << " ";
    }
    cout << endl;
}

string readKeyFromConsole() {
    string keyString;
    cout << "Введите ключ (числа, разделенные пробелами):" << endl;

    int byteValue;
    while (cin >> byteValue) {
        keyString += static_cast<char>(byteValue);
        if (cin.peek() == '\n') {
            break;
        }
    }
    cin.ignore();
    return keyString;
}

string generateKey(ifstream& inputFile, const string& key) {
    string fullKey = key;
    char byte;
    int bytesRead = 0;
    int maxBytes = 100;
    while (inputFile.get(byte) && bytesRead < maxBytes) {
        fullKey += byte;
        bytesRead++;
    }
    inputFile.clear();
    inputFile.seekg(0, ios::beg);
    return fullKey;
}

void encryptBill(ifstream& inputFile, const string& key, ofstream& outputFile) {
    char byte;
    int keyIndex = 0;
    int keyLen = key.length();
    while (inputFile.get(byte)) {
        char keyByte = key[keyIndex % keyLen];
        int encryptedByte = (static_cast<unsigned char>(byte) + static_cast<unsigned char>(keyByte)) % 256;
        outputFile.put(static_cast<char>(encryptedByte));
        keyIndex++;
    }
}

void decryptBill(ifstream& inputFile, const string& key, ofstream& outputFile) {
    char byte;
    int keyIndex = 0;
    int keyLen = key.length();
    while (inputFile.get(byte)) {
        char keyByte = key[keyIndex % keyLen];
        int decryptedByte = (static_cast<unsigned char>(byte) - static_cast<unsigned char>(keyByte) + 256) % 256;
        outputFile.put(static_cast<char>(decryptedByte));
        keyIndex++;
    }
}

bool openInputFileBl(const string& name, ifstream& fileStream) {
    fileStream.open(name, ios::binary);
    return fileStream.is_open();
}

bool openOutputFileBl(const string& name, ofstream& fileStream) {
    fileStream.open(name, ios::binary);
    return fileStream.is_open();
}

extern "C" int cipher_run() {
    int mode;
    cout << "Выберите режим:" << endl;
    cout << "1. Шифрование" << endl;
    cout << "2. Дешифрование" << endl;
    cout << "Ваш выбор: ";
    cin >> mode;
    cin.ignore();

    string inputName, outputName, key;

    if (mode == 1) {
        cout << "Введите название исходного файла: ";
        getline(cin, inputName);
        cout << "Введите название выходного файла: ";
        getline(cin, outputName);
        cout << "Введите начальный ключ: ";
        getline(cin, key);
    }
    else if (mode == 2) {
        cout << "Введите название исходного зашифрованного файла: ";
        getline(cin, inputName);
        cout << "Введите название выходного файла для дешифрования: ";
        getline(cin, outputName);
        key = readKeyFromConsole();
    }
    else {
        cout << "Неверный выбор. Завершение" << endl;
        return 0;
    }

    ifstream inputFile;
    ofstream outputFile;
    if (openInputFileBl(inputName, inputFile) && openOutputFileBl(outputName, outputFile)) {
        cout << "Файлы успешно открыты." << endl;

        if (mode == 1) {
            string fullKey = generateKey(inputFile, key);
            printKey(fullKey);
            encryptBill(inputFile, fullKey, outputFile);
            cout << "Шифрование завершено." << endl;
        }
        else {
            decryptBill(inputFile, key, outputFile);
            cout << "Дешифрование завершено." << endl;
        }

        inputFile.close();
        outputFile.close();
    }
    else {
        cout << "Ошибка: не удалось открыть файл." << endl;
    }
    return 0;
}
