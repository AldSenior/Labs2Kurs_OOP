#include "Complex.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Complex parseComplex(const string& input) {
    string s = input;
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    if (s.empty()) {
        return Complex(0, 0);
    }

    size_t i_pos = s.find('i');
    if (i_pos == string::npos) {
        // Только действительная часть
        size_t pos = 0;
        double real = stod(s, &pos);
        if (pos != s.length()) {
            throw invalid_argument("Лишние символы в действительной части");
        }
        return Complex(real, 0);
    }

    // Есть мнимая часть
    if (i_pos + 1 != s.length()) {
        throw invalid_argument("Лишние символы после 'i'");
    }

    string before_i = s.substr(0, i_pos);
    size_t op_pos = before_i.find_first_of("+-", 1);
    if (op_pos == string::npos) {
        // Только мнимая часть
        double imag;
        if (before_i.empty()) {
            imag = 1;
        } else if (before_i == "+") {
            imag = 1;
        } else if (before_i == "-") {
            imag = -1;
        } else {
            size_t pos = 0;
            imag = stod(before_i, &pos);
            if (pos != before_i.length()) {
                throw invalid_argument("Неверный коэффициент мнимой части");
            }
        }
        return Complex(0, imag);
    }

    // Разделитель для real и imag
    string real_str = before_i.substr(0, op_pos);
    size_t rpos = 0;
    double real = stod(real_str, &rpos);
    if (rpos != real_str.length()) {
        throw invalid_argument("Неверная действительная часть");
    }

    char op = before_i[op_pos];
    string imag_str = before_i.substr(op_pos + 1);
    double imag;
    if (imag_str.empty()) {
        imag = (op == '+') ? 1.0 : -1.0;
    } else {
        size_t ipos = 0;
        imag = stod(imag_str, &ipos);
        if (ipos != imag_str.length()) {
            throw invalid_argument("Неверная мнимая часть");
        }
    }

    return Complex(real, imag);
}

void printHelp() {
    cout << "\n=== КАЛЬКУЛЯТОР КОМПЛЕКСНЫХ ЧИСЕЛ ===" << endl;
    cout << "Форматы ввода комплексных чисел:" << endl;
    cout << "  3+4i     - действительная и мнимая части" << endl;
    cout << "  2.5-1.5i" << endl;
    cout << "  5i       - только мнимая часть" << endl;
    cout << "  7        - только действительная часть" << endl;
    cout << "  -3+2i    - отрицательная действительная часть" << endl;
    cout << "  i        - мнимая единица" << endl;
    cout << "  -i       - отрицательная мнимая единица" << endl;
    cout << endl;
    cout << "Доступные операции:" << endl;
    cout << "  a + b    - сложение" << endl;
    cout << "  a - b    - вычитание" << endl;
    cout << "  a * b    - умножение" << endl;
    cout << "  a / b    - деление" << endl;
    cout << "  a == b   - проверка равенства" << endl;
    cout << "  a != b   - проверка неравенства" << endl;
    cout << "  a < b    - сравнение по модулю (меньше)" << endl;
    cout << "  a > b    - сравнение по модулю (больше)" << endl;
    cout << "  a <= b   - сравнение по модулю (меньше или равно)" << endl;
    cout << "  a >= b   - сравнение по модулю (больше или равно)" << endl;
    cout << "  all      - все операции с двумя числами" << endl;
    cout << "  help     - показать справку" << endl;
    cout << "  exit     - выход" << endl;
    cout << endl;
    cout << "Примеры:" << endl;
    cout << "  3+4i + 2-1i" << endl;
    cout << "  5i * 3" << endl;
    cout << "  7 == 7+0i" << endl;
    cout << "  1+2i < 3+4i" << endl;
    cout << "=====================================" << endl;
}

// Функция для поиска оператора, который разделяет два комплексных числа
pair<string, size_t> findOperator(const string& input) {
    // Все возможные операторы (многосимвольные сначала)
    vector<string> operators = {"==", "!=", "<=", ">=", "+", "-", "*", "/", "<", ">"};

    // Сначала найдем все позиции операторов
    vector<pair<string, size_t>> foundOperators;

    for (const string& op : operators) {
        size_t pos = 0;
        while ((pos = input.find(op, pos)) != string::npos) {
            // Пропускаем операторы в начале строки
            if (pos == 0) {
                pos += op.length();
                continue;
            }

            foundOperators.push_back({op, pos});
            pos += op.length();
        }
    }

    // Сортируем по позиции (слева направо)
    sort(foundOperators.begin(), foundOperators.end(),
         [](const auto& a, const auto& b) { return a.second < b.second; });

    // Ищем оператор, который разделяет два комплексных числа
    for (const auto& [op, pos] : foundOperators) {
        string leftPart = input.substr(0, pos);
        string rightPart = input.substr(pos + op.length());

        // Убираем пробелы
        leftPart.erase(remove(leftPart.begin(), leftPart.end(), ' '), leftPart.end());
        rightPart.erase(remove(rightPart.begin(), rightPart.end(), ' '), rightPart.end());

        // Проверяем, что слева и справа - валидные комплексные числа
        bool leftValid = false, rightValid = false;

        try {
            parseComplex(leftPart);
            leftValid = true;
        } catch (...) {}

        try {
            parseComplex(rightPart);
            rightValid = true;
        } catch (...) {}

        if (leftValid && rightValid) {
            return {op, pos};
        }
    }

    return {"", string::npos};
}

// Функция для разделения выражения
pair<string, string> splitExpression(const string& input, const string& op, size_t opPos) {
    string leftPart = input.substr(0, opPos);
    string rightPart = input.substr(opPos + op.length());

    // Убираем пробелы по краям
    leftPart.erase(0, leftPart.find_first_not_of(" "));
    leftPart.erase(leftPart.find_last_not_of(" ") + 1);
    rightPart.erase(0, rightPart.find_first_not_of(" "));
    rightPart.erase(rightPart.find_last_not_of(" ") + 1);

    return {leftPart, rightPart};
}

void performOperation(const Complex& a, const Complex& b, const string& operation) {
    if (operation == "+") {
        cout << a << " + " << b << " = " << (a + b) << endl;
    } else if (operation == "-") {
        cout << a << " - " << b << " = " << (a - b) << endl;
    } else if (operation == "*") {
        cout << a << " * " << b << " = " << (a * b) << endl;
    } else if (operation == "/") {
        if (b.magnitude() == 0) {
            cout << "Ошибка: деление на ноль!" << endl;
        } else {
            cout << a << " / " << b << " = " << (a / b) << endl;
        }
    } else if (operation == "==") {
        cout << a << " == " << b << " : " << (a == b ? "true" : "false") << endl;
    } else if (operation == "!=") {
        cout << a << " != " << b << " : " << (a != b ? "true" : "false") << endl;
    } else if (operation == "<") {
        cout << a << " < " << b << " : " << (a < b ? "true" : "false") << " (по модулю)" << endl;
    } else if (operation == ">") {
        cout << a << " > " << b << " : " << (a > b ? "true" : "false") << " (по модулю)" << endl;
    } else if (operation == "<=") {
        cout << a << " <= " << b << " : " << (a <= b ? "true" : "false") << " (по модулю)" << endl;
    } else if (operation == ">=") {
        cout << a << " >= " << b << " : " << (a >= b ? "true" : "false") << " (по модулю)" << endl;
    } else if (operation == "all") {
        cout << "\n=== ВСЕ ОПЕРАЦИИ ===" << endl;
        cout << a << " + " << b << " = " << (a + b) << endl;
        cout << a << " - " << b << " = " << (a - b) << endl;
        cout << a << " * " << b << " = " << (a * b) << endl;
        if (b.magnitude() != 0) {
            cout << a << " / " << b << " = " << (a / b) << endl;
        } else {
            cout << a << " / " << b << " = невозможно (деление на ноль)" << endl;
        }
        cout << a << " == " << b << " : " << (a == b ? "true" : "false") << endl;
        cout << a << " != " << b << " : " << (a != b ? "true" : "false") << endl;
        cout << a << " < " << b << " : " << (a < b ? "true" : "false") << " (по модулю)" << endl;
        cout << a << " > " << b << " : " << (a > b ? "true" : "false") << " (по модулю)" << endl;
        cout << a << " <= " << b << " : " << (a <= b ? "true" : "false") << " (по модулю)" << endl;
        cout << a << " >= " << b << " : " << (a >= b ? "true" : "false") << " (по модулю)" << endl;
    }
}

int main() {
    string input;

    cout << "=== КАЛЬКУЛЯТОР КОМПЛЕКСНЫХ ЧИСЕЛ ===" << endl;
    printHelp();

    while (true) {
        cout << "\nВведите выражение (или 'exit' для выхода):" << endl;
        cout << ">>> ";
        getline(cin, input);

        if (input == "exit" || input == "выход") {
            cout << "Выход из программы..." << endl;
            break;
        }

        if (input == "help") {
            printHelp();
            continue;
        }

        if (input == "all") {
            // Для операции 'all' запрашиваем два числа
            Complex a, b;
            cout << "Введите первое комплексное число: ";
            string num1;
            getline(cin, num1);
            a = parseComplex(num1);

            cout << "Введите второе комплексное число: ";
            string num2;
            getline(cin, num2);
            b = parseComplex(num2);

            cout << "\nВы ввели:" << endl;
            cout << "a = " << a << " (|a| = " << a.magnitude() << ")" << endl;
            cout << "b = " << b << " (|b| = " << b.magnitude() << ")" << endl;

            performOperation(a, b, "all");
            continue;
        }

        // Парсим выражение
        try {
            // Ищем оператор в выражении
            auto [foundOperator, opPos] = findOperator(input);

            if (opPos == string::npos) {
                cout << "Ошибка: не найден оператор в выражении!" << endl;
                cout << "Пример: 3+4i + 2-1i" << endl;
                continue;
            }

            // Парсим числа из выражения
            auto [leftPart, rightPart] = splitExpression(input, foundOperator, opPos);

            if (leftPart.empty() || rightPart.empty()) {
                cout << "Ошибка: неверный формат выражения!" << endl;
                continue;
            }

            Complex a = parseComplex(leftPart);
            Complex b = parseComplex(rightPart);

            cout << "\nВычисление:" << endl;
            cout << "a = " << a << " (|a| = " << a.magnitude() << ")" << endl;
            cout << "b = " << b << " (|b| = " << b.magnitude() << ")" << endl;
            cout << "-------------------" << endl;

            performOperation(a, b, foundOperator);

        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            cout << "Проверьте правильность ввода и попробуйте снова" << endl;
            cout << "Введите 'help' для просмотра форматов ввода" << endl;
        }
    }

    cout << "Программа завершена." << endl;
    return 0;
}
