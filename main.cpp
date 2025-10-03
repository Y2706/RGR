#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "belazo.h"
#include "porta.h"
#include "bill.h"

using namespace std;

enum cipher{
	belazo = 1,
	porta = 2,
	bill = 3,
	quit = 4
};

void choice(int num){
	cipher numCipher = (cipher)num;
	switch (numCipher) {
	case belazo:
		cout << "Запуск шифра Белазо" << endl;
		cipher_belazo();
		break;
	case porta:
		cout << "Запуск шифра Порты" << endl;
		cipher_porta();
		break;
	case bill:
		cout << "Запуск шифра Билла" << endl;
		cipher_billa();
		break;
	case quit:
		cout << "Выход из программы" << endl;
		break;
	default:
		cout << "Ошибка ввода" << endl;
		break;
	}

}

int main() {
	int parol = 1234;
	do {
		cout << "Введите пароль: ";
		int input;
		cin >> input;
		if (input == parol){
			cout << "Добро пожаловать" << endl;
			break;
		}
		cout << "Неверный пароль";
		cout << endl;
	} while(true);

	int num;
	do {
		cout << "Меню" << endl;
		cout << "Введите номер шифра:" << endl;
		cout << "1. Шифр Белазо" << endl;
		cout << "2. Шифр Порты" << endl;
		cout << "3. Шифр Билла" << endl;
		cout << "4. Выход" << endl;
		cin >> num;
		choice(num);
	} while (num != 4);
	return 0;
}