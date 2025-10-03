#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "porta.h"

using namespace std;

void encryptPorta(ifstream& inputFile, const string& key, ofstream& outputFile) {
	char byte;
	int keyIndex = 0;
	int keyLen = key.length();
	while (inputFile.get(byte)) {
		char keyByte = key[keyIndex % keyLen];
		int dataByte = static_cast<unsigned char>(byte);
		int encryptedByte;
		int shift = static_cast<unsigned char>(keyByte) % 128;
		if (keyByte < 128) {
			encryptedByte = (dataByte + shift) % 256;
		}
		else {
			encryptedByte = (dataByte - shift + 256) % 256;
		}
		outputFile.put(static_cast<char>(encryptedByte));
		keyIndex++;
	}
}

void decryptPorta(ifstream& inputFile, const string& key, ofstream& outputFile) {
	char byte;
	int keyIndex = 0;
	int keyLen = key.length();
	while (inputFile.get(byte)) {
		char keyByte = key[keyIndex % keyLen];
		int dataByte = static_cast<unsigned char>(byte);
		int encryptedByte;
		int shift = static_cast<unsigned char>(keyByte) % 128;
		if (keyByte < 128) {
			encryptedByte = (dataByte - shift + 256) % 256;
		}
		else {
			encryptedByte = (dataByte + shift) % 256;
		}
		outputFile.put(static_cast<char>(encryptedByte));
		keyIndex++;
	}
}

bool openInputFileP(const string& name, ifstream& fileStream) {
	fileStream.open(name, ios::binary);
	return fileStream.is_open();
}

bool openOutputFileP(const string& name, ofstream& fileStream) {
	fileStream.open(name, ios::binary);
	return fileStream.is_open();
}

int cipher_porta() {
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
		cout << "Неверный выбор. Завершение";
		return 0;
	}

	cout << "Введите ключ: ";
	getline(cin, key);


	ifstream inputFile;
	ofstream outputFile;
	if (openInputFileP(inputName, inputFile) && openOutputFileP(outputName, outputFile)) {
		cout << "Файлы успешно открыты." << endl;

		if (mode == 1) {
			encryptPorta(inputFile, key, outputFile);
			cout << "Шифрование завершено." << endl;
		}
		else {
			decryptPorta(inputFile, key, outputFile);
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
