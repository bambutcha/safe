#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <thread>
#include <vector>
#include "SHA256.h"

using namespace std;

const string GRAY = "\033[90m";
const string BLUE = "\033[94m";
const string CYAN = "\033[96m";
const string GREEN = "\033[92m";
const string WARNING = "\033[93m";
const string FAIL = "\033[91m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";
const string ENDC = "\033[0m";

const string KEY_FILE = "key.txt";

// Константы для вывода
const string welcomeMessage[] = {
    "████ ████ ████ ████ █  █ ████ ████    ███ ████    ████  █  █ █  █ █   █ ████ █  █ █  █ ███",
    "█  █ █  █ █  █ █  █ █  █ █    █  █      █ █  █    █  ██ █  █ █  █ ██ ██ █  █ █  █ █  █ █  ",
    "█    █  █ ████ █    █ ██ ████ █  █    ███ ████    ████  ████ █ ██ █ █ █ ████ ████ █ ██ ███",
    "█  █ █  █ █  █ █  █ ██ █ █  █ █  █      █ █  █    █  ██ █  █ ██ █ █   █ █  █ █  █ ██ █ █  ",
    "████ █  █ █  █ ████ █  █ ████ ████    ███ █  █    ████  █  █ █  █ █   █ █  █ █  █ █  █ ███"
};

void saveKey(const string &key) {
    ofstream keyFile(KEY_FILE);
    char charArray[key.length()];
    strcpy(charArray, key.c_str());

    string temp = SHA256(charArray);

    keyFile << temp;

    keyFile.close();
}

string loadKey() {
    ifstream keyFile(KEY_FILE);
    string key;
    getline(keyFile, key);
    return key;
}

bool keyExists() {
    ifstream keyFile(KEY_FILE);
    return keyFile.good() && keyFile.peek() != ifstream::traits_type::eof(); // Проверка на пустоту
}

void requestKey(string &key) {
    if (!keyExists()) { // Запрашиваем ключ только если его нет
        cout << "Введите ключ-пароль для шифрования паролей: ";
        cin >> key;
        saveKey(key);
    } else {
        key = loadKey(); // Загружаем ключ, если он существует
    }
}

bool verifyPassword() {
    string inputKey;
    cout << "Введите ключ-пароль для проверки: ";
    cin >> inputKey;

    string savedKey = loadKey();
    if (savedKey.empty()) {
        cout << "Не удалось загрузить ключ-пароль!" << endl;
        return false;
    }

    char inputKeyCharArray[inputKey.length()];
    strcpy(inputKeyCharArray, inputKey.c_str());

    if (SHA256(inputKeyCharArray) == savedKey) {
        cout << endl << "Пароль верный!" << endl << endl;
        return true;
    } else {
        cout << endl << "Неверный пароль!" << endl << endl;
        return false;
    }
}

void thanks(int waitTime = 15000) {
    cout << "\n\n" << CYAN << setw(10) << " ";
    for (const auto& line : welcomeMessage) {
        cout << line << setw(10) << " " << "\n";
    }
    cout << ENDC << "\n\n";
    this_thread::sleep_for(chrono::milliseconds(waitTime));
}

void encrypt(const string &password, const string &key) {
    vector<char> encryptedPassword(password.begin(), password.end());
    for (size_t i = 0; i < encryptedPassword.size(); i++) {
        encryptedPassword[i] ^= key[i % key.length()];
    }
    ofstream outfile("password.txt");
    if (outfile.is_open()) {
        outfile.write(encryptedPassword.data(), encryptedPassword.size());
        outfile.close();
        cout << "Пароль сохранен" << endl;
    } else {
        cout << "Не удалось открыть файл для записи!" << endl;
    }
}

void decrypt(const string &key) {
    ifstream infile("password.txt");
    if (!infile.is_open()) {
        cout << "Не удалось открыть файл для чтения!" << endl;
        return;
    }
    string line((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    infile.close();
    
    for (size_t i = 0; i < line.length(); i++) {
        line[i] ^= key[i % key.length()];
    }
    cout << "Расшифрованный пароль: " << line << endl;
}

void deletepass(const string &key) {
    if (!verifyPassword()) {
      return;
    }

    ifstream inputFile("passwords.txt");
    ifstream inputFile2("name.txt");
    ifstream inputFile3("login.txt");

    if (!inputFile.is_open() || !inputFile2.is_open() || !inputFile3.is_open()) {
        cout << "Ошибка при открытии файлов!" << endl;
        return;
    }

    vector<string> passwords, names, logins;
    string line, line2, line3;

    // Считываем данные из файлов
    while (getline(inputFile, line) && getline(inputFile2, line2) && getline(inputFile3, line3)) {
        passwords.push_back(line);
        names.push_back(line2);
        logins.push_back(line3);
    }

    // Проверка на пустоту файлов
    if (passwords.empty()) {
        cout << "Паролей нет." << endl;
        return;
    }

    // Выводим список паролей для удаления
    cout << "Список паролей:\n";
    for (size_t i = 0; i < passwords.size(); i++) {
        cout << i + 1 << ". " << names[i] << ", " << logins[i] << ", " << passwords[i] << endl;
    }

    long long unsigned int index;
    cout << "Введите номер пароля, который нужно удалить: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > passwords.size()) {
        cout << "Неверный номер пароля!" << endl;
        return;
    }

    // Удаляем выбранный пароль
    passwords.erase(passwords.begin() + index - 1);
    names.erase(names.begin() + index - 1);
    logins.erase(logins.begin() + index - 1);

    // Записываем обновленные данные обратно в файлы
    ofstream file("passwords.txt");
    ofstream file2("name.txt");
    ofstream file3("login.txt");

    if (!file.is_open() || !file2.is_open() || !file3.is_open()) {
        cout << "Ошибка при открытии файлов для записи!" << endl;
        return;
    }

    for (const auto &pass : passwords) {
        file << pass << endl;
    }
    for (const auto &nam : names) {
        file2 << nam << endl;
    }
    for (const auto &log : logins) {
        file3 << log << endl;
    }

    cout << "Пароль удален" << endl;

    inputFile.close();
    inputFile2.close();
    inputFile3.close();
    file.close();
    file2.close();
    file3.close();
}

void viewAllPasswords(const string &key) {
    if (!verifyPassword()) {
      return;
    }
    
    ifstream inputFile("passwords.txt");
    ifstream inputFile2("name.txt");
    ifstream inputFile3("login.txt");

    if (!inputFile.is_open() || !inputFile2.is_open() || !inputFile3.is_open()) {
        cout << "Ошибка при открытии файлов!" << endl;
        return;
    }

    // Проверка на пустоту файлов
    if (inputFile.peek() == ifstream::traits_type::eof() || 
        inputFile2.peek() == ifstream::traits_type::eof() || 
        inputFile3.peek() == ifstream::traits_type::eof()) {
        cout << "Паролей нет." << endl;
        return;
    }

    string line, line2, line3;
    vector<string> passwords, names, logins;

    // Считываем данные из файлов
    while (getline(inputFile, line) && getline(inputFile2, line2) && getline(inputFile3, line3)) {
        passwords.push_back(line);
        names.push_back(line2);
        logins.push_back(line3);
    }

    // Проверка на совпадение количества строк
    if (passwords.size() != names.size() || passwords.size() != logins.size()) {
        cout << "Ошибка: количество паролей, имен и логинов не совпадает!" << endl;
        return;
    }

    cout << "Список паролей:\n";
    for (size_t i = 0; i < passwords.size(); i++) {
        for (size_t j = 0; j < passwords[i].length(); j++) {
            passwords[i][j] ^= key[j % key.length()]; // Расшифровка пароля
        }
        cout << i + 1 << ". " << names[i] << ", " << logins[i] << ", " << passwords[i] << endl;
    }

    inputFile.close();
    inputFile2.close();
    inputFile3.close();
}

void addPassword() {
  string name, password, login, key = loadKey();

  if (!verifyPassword()) {
    return;
  }

  cout << BOLD << "Введите имя для пароля: ";
  cin >> name;
  cout << BOLD << "Введите логин: ";
  cin >> login;
  cout << BOLD << "Введите пароль: ";
  cin >> password;


  for (int i = 0; i < password.length(); i++) {
          password[i] = password[i] ^ key[i % key.length()];
      }
      ofstream outfile2("login.txt", ios::app);
      ofstream outfile("passwords.txt", ios::app);
      ofstream outfile3("name.txt", ios::app);
      outfile << password << endl;
      outfile2 << login << endl;
      outfile3 << name << endl;
      outfile.close();
      outfile2.close();
      outfile3.close();
      cout << BOLD << "Пароль сохранен." << endl;

}

// Функция для генерации случайного пароля
string generateRandPass(int length) {
    string password;

    srand(static_cast<unsigned int>(time(0))); // Установка сиды для генерации случайных чисел

    const char symbols[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=";

    int symbolsLength = sizeof(symbols) - 1; // Удаление символа конца строки

    for (int i = 0; i < length; i++) {
        password += symbols[rand() % symbolsLength]; // Генерация случайного символа
    }

    return password;
}
// Функция для генерации пароля
string generatePassword(string keyWord) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=";

    string keyPassword;
    
    keyPassword.reserve(16); // Резервируем память для повышения производительности

    int index = 0;
    
    for (char c : keyWord) {
        index += c; // Суммируем ASCII значения символов
    }

    for (int i = 0; i < 16; i++) {
        index = (17 * index + 11) % characters.size(); // Используем размер characters для избежания выхода за пределы
        keyPassword += characters[index]; // Генерация символа пароля
    }

    return keyPassword;
}

void header() {
    const string menuItems[] = {
        "Добавление пароля в список",
        "Создание рандомного пароля",
        "Генерация пароля по ключу ",
        "Вывод списка паролей",
        "Удаление пароля",
        "Выход"
    };

    cout << BOLD << CYAN << "/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\\" << endl;
    cout << "| " << GRAY << BOLD << setw(46) << left << "Выберите действие:" << ENDC << BOLD << CYAN << " |" << endl;
    cout << "|--------------------------------|" << endl;

    int width[6] = {26, 26, 31, 44, 40, 31};

    for (size_t i = 0; i < sizeof(menuItems) / sizeof(menuItems[0]); ++i) {
        cout << BOLD << CYAN << "| " << GREEN << BOLD << (i + 1) << "." << ENDC
             << BOLD << CYAN << "| " << WARNING << BOLD << setw(width[i]) << left << menuItems[i]
             << ENDC << BOLD << CYAN << " |" << endl;
        cout << "|---|----------------------------|" << endl;
    }

    cout << "\\--------------------------------/" << ENDC << endl << endl;
    cout << BOLD << "Ваш выбор - " << ENDC;
}

vector<string> readFile(const string& filename) {
    vector<string> content;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            content.push_back(line);
        }
        file.close();
    }
    return content;
}

bool continuePrompt() {
    int choice;
    cout << endl << "Желаете продолжить?\n1. Да\n2. Нет\n\nВаш выбор: ";
    cin >> choice;
    if (choice == 1) {
        system("clear");
        return true;
    } else if (choice == 2) {
        return false;
    } else {
        cout << BOLD << FAIL << "Некорректный выбор, попробуйте еще раз через 5 секунд." << endl;
        this_thread::sleep_for(chrono::milliseconds(5000));
        system("clear");
        return true;
    }
}

void generateAndDisplayRandomPassword() {
    string password = generateRandPass(16);
    cout << BOLD << "/---------------------------------------------\\" << endl;
    cout << "|  " << BOLD << CYAN << "Сгенерированный пароль : " << BOLD << GREEN << password << ENDC << BOLD << "  |" << endl;
    cout << "\\---------------------------------------------/" << ENDC << endl;
}

void generatePasswordFromKey() {
    const int SIZE = 100;
    char str[SIZE];

    cout << BOLD << "Пожалуйста, введите слово-ключ:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(str, SIZE);
    cout << BOLD << "Ваше слово-ключ: " << BOLD << GREEN << str << ENDC << endl;

    string sha256 = SHA256(str); // Хэш
    cout << BOLD << BLUE << "Хэш: " << sha256 << ENDC << endl;

    string password = generatePassword(sha256);
    cout << BOLD << CYAN << "Пароль: " << BOLD << GREEN << password << ENDC << endl;
}

int main() {
    vector<string> passwords = readFile("passwords.txt");
    vector<string> names = readFile("name.txt");
    vector<string> logins = readFile("login.txt");

    string key;
    if (!keyExists()) {
        requestKey(key);
    } else {
        key = loadKey();
    }

    while (true) {
        header(); // Выводит меню

        int choice;
        cin >> choice;
        cout << "\n";

        switch (choice) {
            case 1:
                addPassword();
                if (!continuePrompt()) break;
                break;
            case 2:
                generateAndDisplayRandomPassword();
                if (!continuePrompt()) break;
                break;
            case 3:
                generatePasswordFromKey();
                if (!continuePrompt()) break;
                break;
            case 4:
                viewAllPasswords(key);
                if (!continuePrompt()) break;
                break;
            case 5:
                deletepass(key);
                if (!continuePrompt()) break;
                break;
            case 6:
                thanks(); // Предполагается, что эта функция существует
                break;
            default:
                cout << BOLD << FAIL << "Некорректный выбор, попробуйте еще раз." << endl;
                this_thread::sleep_for(chrono::milliseconds(5000));
                system("clear");
                break;
        }
    }

    return 0;
}