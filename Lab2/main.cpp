#include <iostream>
#include "./headers/Figure.h"
#include "./headers/Circle.h"
#include "./headers/Square.h"
#include "./headers/Triangle.h"
#include "./headers/FigureType.h"
// Функция для отображения меню
using namespace std;
void displayMenu() {
    cout << "\n=== МЕНЮ ===" << endl;
    cout << "1. Создать новый список фигур" << endl;
    cout << "2. Добавить фигуру в список" << endl;
    cout << "3. Показать все фигуры" << endl;
    cout << "4. Рассчитать площадь и периметр всех фигур" << endl;
    cout << "5. Выход" << endl;
    cout << "Выберите опцию: ";
}

// Функция для добавления фигуры
void addFigure(vector<unique_ptr<Figure>>& figures) {
    int choice;
    cout << "\nВыберите тип фигуры:" << endl;
    cout << "1. Квадрат" << endl;
    cout << "2. Круг" << endl;
    cout << "3. Треугольник" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    double parameter;
    cout << "Введите размер (сторону/радиус): ";
    cin >> parameter;

    if (parameter <= 0) {
        cout << "Ошибка: размер должен быть положительным!" << endl;
        return;
    }

    switch (choice) {
        case 1:
            figures.push_back(make_unique<Square>(parameter));
            cout << "Квадрат добавлен!" << endl;
            break;
        case 2:
            figures.push_back(make_unique<Circle>(parameter));
            cout << "Круг добавлен!" << endl;
            break;
        case 3:
            figures.push_back(make_unique<Triangle>(parameter));
            cout << "Треугольник добавлен!" << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
    }
}

// Функция для отображения всех фигур
void showAllFigures(const vector<unique_ptr<Figure>>& figures) {
    if (figures.empty()) {
        cout << "Список фигур пуст!" << endl;
        return;
    }

    cout << "\n=== ВСЕ ФИГУРЫ ===" << endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << i + 1 << ". ";
        figures[i]->displayInfo();
    }
}

// Функция для расчета площади и периметра всех фигур
void calculateAll(const vector<unique_ptr<Figure>>& figures) {
    if (figures.empty()) {
        cout << "Список фигур пуст!" << endl;
        return;
    }

    double totalArea = 0;
    double totalPerimeter = 0;

    cout << "\n=== РАСЧЕТЫ ===" << endl;
    cout << fixed << setprecision(2);

    for (size_t i = 0; i < figures.size(); ++i) {
        double area = figures[i]->calculateArea();
        double perimeter = figures[i]->calculatePerimeter();

        totalArea += area;
        totalPerimeter += perimeter;

        cout << i + 1 << ". " << figures[i]->getType()
                  << ": площадь = " << area
                  << ", периметр = " << perimeter << endl;
    }

    cout << "\nОБЩИЕ РЕЗУЛЬТАТЫ:" << endl;
    cout << "Суммарная площадь: " << totalArea << endl;
    cout << "Суммарный периметр: " << totalPerimeter << endl;
}

int main() {
    vector<unique_ptr<Figure>> figures;
    int choice;

    setlocale(LC_ALL, "Russian");


    cout << "Программа для работы с геометрическими фигурами" << endl;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                figures.clear();
                cout << "Новый список фигур создан!" << endl;
                break;
            case 2:
                addFigure(figures);
                break;
            case 3:
                showAllFigures(figures);
                break;
            case 4:
                calculateAll(figures);
                break;
            case 5:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }

    } while (choice != 5);

    return 0;
}
