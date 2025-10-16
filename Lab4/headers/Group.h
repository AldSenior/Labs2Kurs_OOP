#ifndef GROUP_H
#define GROUP_H

#include "Student.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <locale>

using namespace std;

// Класс Группа
class Group {
private:
    int year;                   // Год поступления
    vector<Student> students;   // Список студентов

public:
    // Конструктор по умолчанию
    Group(int y = 2023) : year(y) {}

    // Добавить студента
    void addStudent(const Student& s) {
        int num = students.empty() ? 1 : students.back().getNumber() + 1;
        Student newStudent(s.getFIO(), s.getBirthDate(), s.getRating(), num, s.getResidence());
        students.push_back(newStudent);
    }

    // Удалить студента по номеру
    void removeStudent(int num) {
        auto it = find_if(students.begin(), students.end(),
                          [num](const Student& s) { return s.getNumber() == num; });
        if (it != students.end()) {
            students.erase(it);
            for (size_t i = 0; i < students.size(); ++i) {
                students[i].setNumber(static_cast<int>(i + 1));
            }
        } else {
            throw invalid_argument("Студент с таким номером не найден");
        }
    }

    // Редактировать студента по номеру (изменить ФИО)
    void editStudentFIO(int num, const string& newFIO) {
        auto it = find_if(students.begin(), students.end(),
                          [num](const Student& s) { return s.getNumber() == num; });
        if (it != students.end()) {
            it->setFIO(newFIO);
        } else {
            throw invalid_argument("Студент с таким номером не найден");
        }
    }

    // Вывод группы
    void print() const {
        cout << "Группа, год поступления: " << year << endl;
        cout << "Количество студентов: " << students.size() << endl;
        if (students.empty()) {
            cout << "Группа пуста." << endl;
        } else {
            for (const auto& s : students) {
                s.print();
            }
        }
        cout << endl;
    }

    // Сериализация в JSON
    string serializeToJSON() const {
        ostringstream oss;
        oss << "{\n";
        oss << "  \"year\": " << year << ",\n";
        oss << "  \"students\": [\n";
        for (size_t i = 0; i < students.size(); ++i) {
            oss << students[i].serializeToJSON() << (i < students.size() - 1 ? "," : "") << "\n";
        }
        oss << "  ]\n";
        oss << "}";
        return oss.str();
    }

    // Десериализация из JSON
    void deserializeFromJSON(const string& jsonStr) {
        students.clear();
        try {
            // Парсим year
            size_t pos = jsonStr.find("\"year\":", 0);
            if (pos != string::npos) {
                pos += 7;  // after "year":
                while (pos < jsonStr.size() && isspace(static_cast<unsigned char>(jsonStr[pos]))) ++pos;
                size_t end = jsonStr.find_first_of(",}", pos);
                if (end != string::npos) {
                    string yearStr = jsonStr.substr(pos, end - pos);
                    yearStr.erase(remove_if(yearStr.begin(), yearStr.end(), [](unsigned char ch){ return isspace(static_cast<int>(ch)); }), yearStr.end());
                    if (!yearStr.empty()) {
                        year = stoi(yearStr);
                    }
                }
            }

            // Парсим students array
            pos = jsonStr.find("\"students\": [", 0);
            if (pos != string::npos) {
                pos += 13;  // after "students": [
                while (true) {
                    while (pos < jsonStr.size() && (isspace(static_cast<unsigned char>(jsonStr[pos])) || jsonStr[pos] == ',')) ++pos;
                    if (pos >= jsonStr.size() || jsonStr[pos] == ']') break;
                    while (pos < jsonStr.size() && jsonStr[pos] != '{') ++pos;
                    if (pos >= jsonStr.size()) break;
                    size_t startObj = pos;
                    int braceCount = 1;
                    pos = startObj + 1;
                    while (pos < jsonStr.size() && braceCount > 0) {
                        if (jsonStr[pos] == '{') ++braceCount;
                        if (jsonStr[pos] == '}') --braceCount;
                        ++pos;
                    }
                    if (braceCount != 0) break;
                    size_t endObj = pos - 1;
                    string objStr = jsonStr.substr(startObj, endObj - startObj + 1);
                    try {
                        Student s = Student::deserializeFromJSON(objStr);
                        s.setNumber(static_cast<int>(students.size() + 1));
                        students.push_back(s);
                    } catch (const exception& e) {
                        cerr << "Пропуск студента: " << e.what() << endl;
                    }
                }
            }
        } catch (const exception& e) {
            cerr << "Ошибка десериализации: " << e.what() << endl;
            students.clear();
            year = 2023;
        }
    }

    // Сохранение в файл
    void saveToFile() const {
        try {
            locale utf8Locale("");
            ofstream file("group.json");
            file.imbue(utf8Locale);
            if (!file.is_open()) throw runtime_error("Не удалось открыть файл");
            file << serializeToJSON();
            file.close();
            cout << "Сохранено в group.json" << endl;
        } catch (const exception& e) {
            cerr << "Ошибка сохранения: " << e.what() << endl;
        }
    }

    // Загрузка из файла
    void loadFromFile() {
        try {
            locale utf8Locale("");
            ifstream file("group.json");
            file.imbue(utf8Locale);
            if (!file.is_open()) {
                cout << "Файл не найден." << endl;
                return;
            }
            string jsonContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();
            if (jsonContent.empty()) {
                cout << "Файл пуст." << endl;
                return;
            }
            deserializeFromJSON(jsonContent);
            cout << "Загружено из group.json" << endl;
        } catch (const exception& e) {
            cerr << "Ошибка загрузки: " << e.what() << endl;
        }
    }
};

#endif
