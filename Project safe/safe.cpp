#include "library.h"

using namespace std;

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
    cout << "Пароль сохранен" << endl;
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
  cout << "Введите номер пароля, который нужно удалить: ";
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
      cout << "Пароль удален из файла.\n";
    } else {
      cerr << "Ошибка при открытии файла.\n";
    }
  } else {
    cerr << "Неверный номер пароля.\n";
  }
}

void viewAllPasswords() {
  string key;
  cout << "Введите ключ-пароль: ";
  cin >> key;
  ifstream inputFile("passwords.txt"); // открытие файла для чтения
  ifstream inputFile2("name.txt");
  ifstream inputFile3("login.txt");
  string line, line2, line3;
  
  if (inputFile.is_open()) { // проверка, открыт ли файл
    int cntr = 1;
    
    while (getline(inputFile, line), getline(inputFile2, line2), getline(inputFile3, line3)) { // считывание строк из файла
      

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
    cout << "Не удалось открыть файл"
         << endl; // вывод сообщения об ошибке, если файл не удалось открыть
  }
}

void addPassword() {
  string name, password, login, key;
  cout << "Введите имя: ";
  cin >> name;
  cout << "Введите логин: ";
  cin >> login;
  cout << "Введите пароль: ";
  cin >> password;
  cout << "Введите ключ-пароль: ";
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
      cout << "Пароль сохранен." << endl;

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

  cout << "/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\\" << endl;
  cout << "| " << setw(46) << left << "Выберите действие:"
       << " |" << endl;
  cout << "|--------------------------------|" << endl;
  cout << "| "
       << "1."
       << "| " << setw(26) << left << "Добавление пароля в список"
       << " |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << "| "
       << "2."
       << "| " << setw(26) << left << "Создание рандомного пароля"
       << " |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << "| "
       << "3."
       << "| " << setw(31) << left << "Генерация пароля по ключу"
       << "  |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << "| "
       << "4."
       << "| " << setw(44) << left << "Вывод списка паролей"
       << " |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << "| "
       << "5."
       << "| " << setw(40) << left << "Удаление пароля"
       << " |" << endl;
  cout << "|---|----------------------------|" << endl;
  cout << "| "
       << "6."
       << "| " << setw(31) << left << "Выход"
       << " |" << endl;
  cout << "\\--------------------------------/" << endl << endl;

  cout << "Ваш выбор - ";
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
      this_thread::sleep_for(chrono::milliseconds(5000));
      systemclear();
    } else if (choice == 2) {
      // Создание рандомного пароля
      string password = generateRandPass(16);
      cout << "/---------------------------------------------\\" << endl;
      cout << "|  "
           << "Сгенерированный пароль : " << password << "  |" << endl;
      cout << "\\---------------------------------------------/" << endl;
      this_thread::sleep_for(chrono::milliseconds(5000));
      systemclear();
    } else if (choice == 3) {
      const int SIZE = 100;
      char str[SIZE];

      cout << "Пожалуйста, введите слово-ключ:\n";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin.get(str, SIZE);
      cout << "Ваше слово-ключ: " << str << endl;

      string sha256 = SHA256(str); // Хэш
      cout << sha256 << endl;

      string password = generatePassword(sha256);
      cout << "Хэш: " << sha256;
      cout << endl;
      cout << "Пароль: " << password << endl;
      this_thread::sleep_for(chrono::milliseconds(5000));
      systemclear();
    } else if (choice == 4) {
      cout << "Формат: Имя - Логин - Пароль" << endl;
      viewAllPasswords();
      this_thread::sleep_for(chrono::milliseconds(5000));
      systemclear();
    } else if (choice == 5) {
      cout << "Формат: Имя - Логин - Пароль" << endl;
      viewAllPasswords();
      deletepass(passwordss, nameee, loginnn);
      this_thread::sleep_for(chrono::milliseconds(5000));
      systemclear();
    } else if (choice == 6) {
      // Выход
      break;
    } else if (choice == 9) {
      cout << " /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\\" << endl;
      cout << "|  Проект по C++                     ==SAFE==     |" << endl;
      cout << "|  Автор: Ягольник Даниил Сергеевич               |" << endl;
      cout << "|  Ученик Школа::Кода 22/23 C++                   |" << endl;
      cout << "|  Преподаватель: Зверев Алексей Евгеньевич       |" << endl;
      cout << " \\_______________________________________________/" << endl;
      this_thread::sleep_for(chrono::milliseconds(10000));
      systemclear();
    } else {
      cout << "Некорректный выбор, попробуйте еще раз через 5 секунд" << endl;
      this_thread::sleep_for(chrono::milliseconds(50000));
      systemclear();
    }
  }

  return 0;
}
