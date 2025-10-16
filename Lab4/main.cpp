#include "./headers/Group.h"
#include <limits>
#include <locale>

void printHelp() {
    cout << "\n=== УПРАВЛЕНИЕ ГРУППОЙ ===" << endl;
    cout << "add, print, save, load, help, exit" << endl;
}

void addStudentInteractive(Group& group) {
    string fio, birthDate, residenceStr;
    double rating;

    // Валидация FIO (не пустой)
    do {
        cout << "Введите ФИО: ";
        getline(cin, fio);
        if (!fio.empty()) break;
        cout << "ФИО не может быть пустым. Попробуйте снова." << endl;
    } while (true);

    // Валидация birthDate (формат DD.MM.YYYY и валидная дата)
    do {
        cout << "Введите дату рождения (DD.MM.YYYY): ";
        getline(cin, birthDate);
        if (isValidDate(birthDate)) break;
        cout << "Неверный формат или значение даты. Используйте DD.MM.YYYY (например, 01.01.2000). Попробуйте снова." << endl;
    } while (true);

    // Валидация rating (0-5)
    do {
        cout << "Введите рейтинг (0-5): ";
        string ratingStr;
        getline(cin, ratingStr);
        try {
            rating = stod(ratingStr);
            if (rating >= 0 && rating <= 5) break;
            cout << "Рейтинг должен быть между 0 и 5. Попробуйте снова." << endl;
        } catch (...) {
            cout << "Неверное число. Попробуйте снова." << endl;
        }
    } while (true);

    // Валидация residence (local/nonlocal)
    do {
        cout << "Введите место жительства (local/nonlocal): ";
        getline(cin, residenceStr);
        try {
            Residence res = stringToResidence(residenceStr);
            Student newStudent(fio, birthDate, rating, 0, res);
            group.addStudent(newStudent);
            cout << "Student added." << endl;
            return;  // Успешно добавлено
        } catch (const exception& e) {
            cout << "Error: " << e.what() << " Попробуйте снова." << endl;
        }
    } while (true);
}

int main() {
    locale::global(locale(""));
    cout.imbue(locale(""));
    cin.imbue(locale(""));

    Group group;
    string command;

    cout << "=== LAB 4 ===" << endl;
    printHelp();

    while (true) {
        cout << "\nCommand: ";
        getline(cin, command);

        if (command == "exit") break;
        if (command == "help") { printHelp(); continue; }
        if (command == "add") { addStudentInteractive(group); continue; }
        if (command == "print") { group.print(); continue; }
        if (command == "save") { group.saveToFile(); continue; }
        if (command == "load") { group.loadFromFile(); continue; }

        cout << "Unknown command." << endl;
    }

    return 0;
}
