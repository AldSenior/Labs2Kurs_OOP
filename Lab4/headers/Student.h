// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <locale>

using namespace std;

// Перечисление для проживания
enum class Residence {
    Local,      // Local
    NonLocal    // NonLocal
};

// Функция для преобразования enum в string (для вывода на русском)
string residenceToString(Residence res) {
    return (res == Residence::Local) ? "местный" : "иногородний";
}

// Функция для преобразования string в enum (только английский, без опечаток)
Residence stringToResidence(const string& str) {
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(),
              [](unsigned char c) { return tolower(c); });

    if (lower == "local") {
        return Residence::Local;
    } else if (lower == "nonlocal") {
        return Residence::NonLocal;
    }
    throw invalid_argument("Неверный тип проживания: '" + str + "'. Допустимые: 'local' или 'nonlocal'");
}

// Функция валидации даты (DD.MM.YYYY)
bool isValidDate(const string& dateStr) {
    int day, month, year;
    if (sscanf(dateStr.c_str(), "%d.%d.%d", &day, &month, &year) != 3) {
        return false;
    }
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2025) {
        return false;
    }
    // Простая проверка дней в месяце (без високосных)
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day > daysInMonth[month]) {
        return false;
    }
    return true;
}

// Класс Student
class Student {
private:
    string fio;         // ФИО
    string birthDate;   // Дата рождения
    double rating;      // Рейтинг успеваемости
    int number;         // Номер в списке группы
    Residence residence; // Проживание

public:
    // Конструктор по умолчанию
    Student(const string& f = "", const string& bd = "", double r = 0.0, int n = 0, Residence res = Residence::Local)
        : fio(f), birthDate(bd), rating(r), number(n), residence(res) {}

    // Геттеры
    string getFIO() const { return fio; }
    string getBirthDate() const { return birthDate; }
    double getRating() const { return rating; }
    int getNumber() const { return number; }
    Residence getResidence() const { return residence; }

    // Сеттеры
    void setFIO(const string& f) { fio = f; }
    void setBirthDate(const string& bd) { birthDate = bd; }
    void setRating(double r) {
        if (r < 0 || r > 5) throw invalid_argument("Рейтинг должен быть от 0 до 5");
        rating = r;
    }
    void setNumber(int n) {
        if (n < 1) throw invalid_argument("Номер должен быть положительным");
        number = n;
    }
    void setResidence(Residence res) { residence = res; }

    // Метод для вывода студента
    void print() const {
        cout << "Номер: " << number << ", ФИО: " << fio
             << ", Дата рождения: " << birthDate
             << ", Рейтинг: " << fixed << setprecision(2) << rating
             << ", Проживание: " << residenceToString(residence) << endl;
    }

    // Метод для сериализации в JSON (английские значения)
    string serializeToJSON() const {
        ostringstream oss;
        oss << "    {\n";
        oss << "      \"number\": " << number << ",\n";
        oss << "      \"fio\": \"" << fio << "\",\n";
        oss << "      \"birthDate\": \"" << birthDate << "\",\n";
        oss << "      \"rating\": " << fixed << setprecision(2) << rating << ",\n";
        oss << "      \"residence\": \"" << (getResidence() == Residence::Local ? "local" : "nonlocal") << "\"\n";
        oss << "    }";
        return oss.str();
    }

    // Статический метод для десериализации (robust парсер)
    static Student deserializeFromJSON(const string& jsonObj) {
        Student s;
        try {
            auto extractString = [&](const string& key) -> string {
                size_t pos = jsonObj.find("\"" + key + "\":", 0);
                if (pos == string::npos) return "";
                pos += key.length() + 3;  // after "key":
                while (pos < jsonObj.size() && isspace(static_cast<unsigned char>(jsonObj[pos]))) ++pos;
                if (pos < jsonObj.size() && jsonObj[pos] == '"') ++pos;
                size_t end = jsonObj.find("\"", pos);
                if (end == string::npos) return "";
                return jsonObj.substr(pos, end - pos);
            };

            auto extractNumber = [&](const string& key) -> double {
                size_t pos = jsonObj.find("\"" + key + "\":", 0);
                if (pos == string::npos) return 0.0;
                pos += key.length() + 3;
                while (pos < jsonObj.size() && isspace(static_cast<unsigned char>(jsonObj[pos]))) ++pos;
                size_t end = jsonObj.find_first_of(",}", pos);
                if (end == string::npos) return 0.0;
                string numStr = jsonObj.substr(pos, end - pos);
                numStr.erase(remove_if(numStr.begin(), numStr.end(), [](unsigned char ch){ return isspace(static_cast<int>(ch)); }), numStr.end());
                return numStr.empty() ? 0.0 : stod(numStr);
            };

            s.fio = extractString("fio");
            s.birthDate = extractString("birthDate");
            s.number = static_cast<int>(extractNumber("number"));
            s.rating = extractNumber("rating");

            string resStr = extractString("residence");
            if (!resStr.empty()) {
                s.residence = stringToResidence(resStr);
            } else {
                s.residence = Residence::Local;
            }
        } catch (const exception& e) {
            cerr << "Ошибка десериализации студента: " << e.what() << endl;
            s.residence = Residence::Local;
        }
        return s;
    }
};

#endif
