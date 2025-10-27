#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "belazo.h"

using namespace std;

void encryptBelazo(ifstream& inputFile, const string& key, ofstream& outputFile) {
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

void decryptBelazo(ifstream& inputFile, const string& key, ofstream& outputFile) {
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

bool openInputFileB(const string& name, ifstream& fileStream) {
    fileStream.open(name, ios::binary);
    return fileStream.is_open();
}

bool openOutputFileB(const string& name, ofstream& fileStream) {
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
    }
    else if (mode == 2) {
        cout << "Введите название исходного зашифрованного файла: ";
        getline(cin, inputName);
        cout << "Введите название выходного файла для дешифрования: ";
        getline(cin, outputName);
    }
    else {
        cout << "Неверный выбор. Завершение" << endl;
        return 0;
    }

    cout << "Введите ключ: ";
    getline(cin, key);

    ifstream inputFile;
    ofstream outputFile;
    if (openInputFileB(inputName, inputFile) && openOutputFileB(outputName, outputFile)) {
        cout << "Файлы успешно открыты." << endl;

        if (mode == 1) {
            encryptBelazo(inputFile, key, outputFile);
            cout << "Шифрование завершено." << endl;
        }
        else {
            decryptBelazo(inputFile, key, outputFile);
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
