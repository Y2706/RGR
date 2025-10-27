#include <iostream>
#include <string>
#include <dlfcn.h>

using namespace std;

typedef int (*cipher_run_func)();

int main() {
    int parol = 1234;
    do {
        cout << "Введите пароль: ";
        int input;
        cin >> input;
        if (input == parol) {
            cout << "Добро пожаловать" << endl;
            break;
        }
        cout << "Неверный пароль" << endl;
    } while (true);

    int num;
    do {
        cout << "\nМеню" << endl;
        cout << "Введите номер шифра:" << endl;
        cout << "1. Шифр Белазо" << endl;
        cout << "2. Шифр Порты" << endl;
        cout << "3. Шифр Билла" << endl;
        cout << "4. Выход" << endl;
        cin >> num;

        if (num == 4) {
            cout << "Выход из программы" << endl;
            break;
        }

        string lib_name;
        if (num == 1) lib_name = "./libbelazo.so";
        else if (num == 2) lib_name = "./libporta.so";
        else if (num == 3) lib_name = "./libbill.so";
        else {
            cout << "Ошибка ввода" << endl;
            continue;
        }

        void* handle = dlopen(lib_name.c_str(), RTLD_LAZY);
        if (!handle) {
            cerr << "Ошибка загрузки библиотеки " << lib_name << ": " << dlerror() << endl;
            continue;
        }

        cipher_run_func run_func = (cipher_run_func)dlsym(handle, "cipher_run");
        if (!run_func) {
            cerr << "Функция cipher_run не найдена в " << lib_name << endl;
            dlclose(handle);
            continue;
        }

        run_func();

        dlclose(handle);
    } while (num != 4);

    return 0;
}
