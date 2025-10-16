#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <functional>

using namespace std;

int main() {
    vector<int> arr;

    // Ввод массива
    cout << "Введите элементы массива через пробел: ";
    string input;
    getline(cin, input);

    stringstream ss(input);
    int num;
    while (ss >> num) {
        arr.push_back(num);
    }

    if (arr.empty()) return 0;

    cout << "Исходный массив: ";
    for_each(arr.begin(), arr.end(), [](int x) { cout << x << " "; });
    cout << endl;

    cout << "Введите математические операции через пробел: ";
    getline(cin, input);

    stringstream opSS(input);
    string operation;

    while (opSS >> operation) {
        char op = operation[0];
        int value = stoi(operation.substr(1));

        auto processor = [op, value](int& x) {
            switch(op) {
                case '+': x += value; break;
                case '-': x -= value; break;
                case '*': x *= value; break;
                case '/':
                    if (value != 0) x /= value;
                    else cout << "Ошибка: деление на ноль!" << endl;
                    break;
                default: cout << "Неизвестная операция: " << op << endl;
            }
        };

        for_each(arr.begin(), arr.end(), processor);

        cout << "После " << operation << ": ";
        for_each(arr.begin(), arr.end(), [](int x) { cout << x << " "; });
        cout << endl;
    }

    cout << "Результат: ";
    for_each(arr.begin(), arr.end(), [](int x) { cout << x << " "; });
    cout << endl;

    return 0;
}
