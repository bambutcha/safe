#define _CRT_SECURE_NO_WARNINGS

#include "library.h"

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

void systemclear() {
  string clear = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                 "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  cout << clear;
}

void encrypt(string password, string key) {
    for (int i = 0; i < password.length(); i++) {
        
      password[i] = password[i] ^ key[i % key.length()];
    }
    ofstream outfile("password.txt");
    outfile << password << endl;
    outfile.close();
    cout << BOLD << "Пароль сохранен" << endl;
}

void decrypt(string key) {
    string line;
    for (int i = 0; i < line.length(); i++) {
        line[i] = line[i] ^ key[i % key.length()];
    }
    cout << "Decrypted password: " << line << endl;
}

void deletepass(vector<string> &passwordss, vector<string> &nameee, vector<string> &loginnn) {
  long long unsigned int index;
  cout << BOLD << "Введите номер пароля, который нужно удалить: ";
  cin >> index;
  cin.ignore();
  if ((index >= 1 && index <= passwordss.size()) && (index >= 1 && index <= nameee.size()) && (index >= 1 && index <= loginnn.size())) {
    passwordss.erase(passwordss.begin() + index - 1);
    nameee.erase(nameee.begin() + index - 1);
    loginnn.erase(loginnn.begin() + index - 1);
    ofstream file("passwords.txt");
    ofstream file2("name.txt");
    ofstream file3("login.txt");
    if ((file.is_open()) && (file2.is_open()) && (file3.is_open())) {
      for (string pass : passwordss) {
        file << pass << endl;
      }

      for (string nam : nameee) {
        file2 << nam << endl;
      }

      for (string log : loginnn) {
        file3 << log << endl;
      }

    
      file.close();
      file2.close();
      file3.close();
      cout << BOLD << "Пароль удален из файла.\n";
    } else {
      cerr << BOLD << FAIL << "Ошибка при открытии файла.\n" << ENDC;
    }
  } else {
    cerr << BOLD << FAIL << "Неверный номер пароля.\n" << ENDC;
  }
}

void viewAllPasswords() {
  string key;
  cout << BOLD << "Введите ключ-пароль: ";
  cin >> key;
  ifstream inputFile("passwords.txt"); // открытие файла для чтения
  ifstream inputFile2("name.txt");
  ifstream inputFile3("login.txt");
  string line, line2, line3;
  
  if (inputFile.is_open()) { // проверка, открыт ли файл
    int cntr = 1;
    
    while (getline(inputFile, line), getline(inputFile2, line2), getline(inputFile3, line3)) { // считывание строк из файлов
      

    for (int i = 0; i < line.length(); i++) {
        line[i] = line[i] ^ key[i % key.length()];
    }

      cout << cntr << ". " << line2 << " - " << line3 << " - " << line << endl; // вывод строки в консоль
      cntr++;
    }
    cntr++;
    inputFile.close(); // закрытие файла
    inputFile2.close();
    inputFile3.close();
  } else {
    cout << BOLD << FAIL <<"Не удалось открыть файл" << ENDC
         << endl; // вывод сообщения об ошибке, если файл не удалось открыть
  }
}

void addPassword() {
  string name, password, login, key;
  cout << BOLD << "Введите имя: ";
  cin >> name;
  cout << BOLD << "Введите логин: ";
  cin >> login;
  cout << BOLD << "Введите пароль: ";
  cin >> password;
  cout << BOLD << "Введите ключ-пароль: ";
  cin >> key;

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
  string password = "";
  srand(time(0)); // Установка сиды для генерации случайных чисел
  char symbols[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567"
                   "890!@#$%^&*()_+-=";
  int symbolsLength = sizeof(symbols) - 1; // Удаление символа конца строки

  for (int i = 0; i < length; i++) {
    password += symbols[rand() % symbolsLength];
  }

  return password;
}
// Функция для генерации пароля
string generatePassword(string a) {
  string password = "";
  string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234"
                      "567890!@#$%^&*()_+-=";
  int index = 0;
  for (int i = 0; i < 32; i++) {
    index += a[i];
  }
  for (int i = 0; i < 16; i++) {
    index = (17 * index + 11) % 62;
    password += characters[index];
  }
  return password;
}

void header() {

  cout << BOLD << CYAN << "/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\\" << endl;
  cout << "| " << GRAY << BOLD << setw(46) << left << "Выберите действие:"
       << ENDC << BOLD << CYAN << " |" << endl;
  cout << "|--------------------------------|" << endl;
  cout << BOLD << CYAN << "| "
       << GREEN << BOLD << "1." << ENDC
       << BOLD << CYAN << "| " << WARNING << BOLD << setw(26) << left << "Добавление пароля в список"
       << ENDC << BOLD << CYAN << " |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << BOLD << CYAN << "| "
       << GREEN << BOLD << "2." << ENDC
       << BOLD << CYAN << "| " << WARNING << BOLD << setw(26) << left << "Создание рандомного пароля"
       << ENDC << BOLD << CYAN << " |" << endl;
  cout << BOLD << CYAN << "|---|----------------------------|" << endl;
  cout << "| "
       << GREEN << BOLD << "3." << ENDC
       << BOLD << CYAN << "| " << WARNING << BOLD << setw(31) << left << "Генерация пароля по ключу"
       << ENDC << BOLD << CYAN << "  |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << "| "
       << GREEN << BOLD << "4." << ENDC
       << BOLD << CYAN << "| " << WARNING << BOLD << setw(44) << left << "Вывод списка паролей"
       << ENDC << BOLD << CYAN << " |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << "| "
       << GREEN << BOLD << "5." << ENDC
       << BOLD << CYAN << "| " << WARNING << BOLD << setw(40) << left << "Удаление пароля"
       << ENDC << BOLD << CYAN << " |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << "| "
       << GREEN << BOLD << "6." << ENDC
       << BOLD << CYAN << "| " << WARNING << BOLD << setw(31) << left << "Выход"
       << ENDC << BOLD << CYAN << " |" << endl;
  cout << "\\--------------------------------/" << ENDC << endl << endl;

  cout << BOLD << "Ваш выбор - " << ENDC;
}

int main() {

  while (true) {
    vector<string> passwordss;
    vector<string> passwords;
    int cnt = 1;
    vector<string> pass;
    ifstream file("passwords.txt");
    if (file.is_open()) {
      string pass;
      while (getline(file, pass)) {
        passwordss.push_back(pass);
        cnt++;
      }
      file.close();
    }

    vector<string> nameee;
    vector<string> namee;
    int cnt1 = 1;
    vector<string> nam;
    ifstream file2("name.txt");
    if (file2.is_open()) {
      string nam;
      while (getline(file2, nam)) {
        nameee.push_back(nam);
      }
      file2.close();
    }

    vector<string> loginnn;
    vector<string> loginn;
    int cnt2 = 1;
    vector<string> log;
    ifstream file3("login.txt");
    if (file3.is_open()) {
      string log;
      while (getline(file3, log)) {
        loginnn.push_back(log);
      }
      file3.close();
    }

    
    
    // Выводим меню
    // cout << "/--------------------------------\\" << endl;
    // cout << "| " << setw(46) << left << "Выберите действие:" << " |" << endl;
    // cout << "|--------------------------------|" << endl;
    // cout << "| " << "1." << "| " << setw(26) << left << "Добавление пароля в
    // список" << " |" << endl; cout << "|---|----------------------------|" <<
    // endl; cout << "| " << "2." << "| " << setw(26) << left << "Создание
    // рандомного пароля" << " |" << endl; cout <<
    // "|---|----------------------------|" << endl; cout << "| " << "3." << "|
    // " << setw(31) << left << "Генерация пароля по ключу" << "  |" << endl;
    // cout << "|---|----------------------------|" << endl;
    // cout << "| " << "4." << "| " << setw(44) << left << "Вывод списка
    // паролей" << " |" << endl; cout << "|---|----------------------------|" <<
    // endl; cout << "| " << "5." << "| " << setw(40) << left << "Удаление
    // пароля" << " |" << endl; cout << "|---|----------------------------|" <<
    // endl; cout << "| " << "6." << "| " << setw(31) << left << "Выход" << " |"
    // << endl; cout << "\\--------------------------------/" << endl << endl;

    // cout << "Ваш выбор - ";

    header(); // Выводит меню

    int choice;
    cin >> choice;
    cout << "\n";
    if (choice == 1) {
      addPassword();
            int choice1;
      cout << endl << endl << "Желаете продолжить ?\n1. Да\n2. Нет\n\nВаш выбор: ";
      cin >> choice1;
      if(choice1 == 1) system("clear");
      else if(choice1 == 2) break;
      else       
      cout << BOLD << FAIL << "Некорректный выбор, попробуйте еще раз через 5 секунд" << endl;
      this_thread::sleep_for(chrono::milliseconds(5000));
      system("clear");
    } else if (choice == 2) {
      // Создание рандомного пароля
      string password = generateRandPass(16);
      cout << BOLD << "/---------------------------------------------\\" << endl;
      cout << "|  "
           << BOLD << CYAN << "Сгенерированный пароль : " << BOLD << GREEN << password << ENDC << BOLD << "  |" << endl;
      cout << "\\---------------------------------------------/" << ENDC << endl;

      int choice1;
      cout << endl << endl << "Желаете продолжить ?\n1. Да\n2. Нет\n\nВаш выбор: ";
      cin >> choice1;
      if(choice1 == 1) system("clear");
      else if(choice1 == 2) break;
      else {
      cout << BOLD << FAIL << "Некорректный выбор, попробуйте еще раз через 5 секунд" << endl;
      this_thread::sleep_for(chrono::milliseconds(5000));
      }
    } else if (choice == 3) {
      const int SIZE = 100;
      char str[SIZE];

      cout << BOLD << "Пожалуйста, введите слово-ключ:\n";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin.get(str, SIZE);
      cout << BOLD << "Ваше слово-ключ: " << BOLD << GREEN << str << ENDC << endl;

      string sha256 = SHA256(str); // Хэш
      cout << sha256 << endl;

      string password = generatePassword(sha256);
      cout << BOLD << BLUE << "Хэш: " << sha256;
      cout << ENDC << endl;
      cout << BOLD << CYAN << "Пароль: " << BOLD << GREEN << password << endl;
      
      int choice1;
      cout << endl << endl << "Желаете продолжить ?\n1. Да\n2. Нет\n\nВаш выбор: ";
      cin >> choice1;
      if(choice1 == 1) system("clear");
      else if(choice1 == 2) break;
      else       
      cout << BOLD << FAIL << "Некорректный выбор, попробуйте еще раз через 5 секунд" << endl;
      this_thread::sleep_for(chrono::milliseconds(5000));
      system("clear");
    } else if (choice == 4) {
      cout << BOLD << "Формат: Имя - Логин - Пароль" << endl;
      viewAllPasswords();
      
      int choice1;
      cout << endl << endl << "Желаете продолжить ?\n1. Да\n2. Нет\n\nВаш выбор: ";
      cin >> choice1;
      if(choice1 == 1) system("clear");
      else if(choice1 == 2) break;
      else       
      cout << BOLD << FAIL << "Некорректный выбор, попробуйте еще раз через 5 секунд" << endl;
      this_thread::sleep_for(chrono::milliseconds(5000));
      system("clear");
    } else if (choice == 5) {
      cout << BOLD << "Формат: Имя - Логин - Пароль" << endl;
      viewAllPasswords();
      deletepass(passwordss, nameee, loginnn);
      
      int choice1;
      cout << endl << endl << "Желаете продолжить ?\n1. Да\n2. Нет\n\nВаш выбор: ";
      cin >> choice1;
      if(choice1 == 1) system("clear");
      else if(choice1 == 2) break;
      else       
      cout << BOLD << FAIL << "Некорректный выбор, попробуйте еще раз через 5 секунд" << endl;
      this_thread::sleep_for(chrono::milliseconds(5000));
      system("clear");
    } else if (choice == 6) {
      // Выход
      break;
    } else if (choice == 9) {
      cout << BOLD << " /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\\" << endl;
      cout << "|  Проект по C++                     ==SAFE==     |" << endl;
      cout << "|  Автор: Ягольник Даниил Сергеевич               |" << endl;
      cout << "|  Ученик Школа::Кода 22/23 C++                   |" << endl;
      cout << "|  Преподаватель: Зверев Алексей Евгеньевич       |" << endl;
      cout << " \\_______________________________________________/" << ENDC << endl;
      this_thread::sleep_for(chrono::milliseconds(10000));
      system("clear");
    } else {
      cout << BOLD << FAIL << "Некорректный выбор, попробуйте еще раз через 5 секунд" << endl;
      this_thread::sleep_for(chrono::milliseconds(5000));
      system("clear");
    }
  }

  return 0;
}
