#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <limits>
#include "./headers/Figure.h"
#include "./headers/Circle.h"
#include "./headers/Square.h"
#include "./headers/Triangle.h"
#include "./headers/FigureType.h"

using namespace std;

// Двумерный вектор для хранения нескольких списков фигур
vector<vector<unique_ptr<Figure>>> allFiguresLists;
int currentListIndex = -1; // Индекс текущего активного списка


void displayMenu() {
    cout << "\n=== МЕНЮ ===" << endl;
    cout << "1. Создать новый список фигур" << endl;
    cout << "2. Выбрать существующий список" << endl;
    cout << "3. Добавить фигуру в текущий список" << endl;
    cout << "4. Показать все фигуры в текущем списке" << endl;
    cout << "5. Рассчитать площадь и периметр всех фигур в текущем списке" << endl;
    cout << "6. Показать все созданные списки" << endl;
    cout << "7. Выход" << endl;
    cout << "Выберите опцию: ";
}

void createNewList() {
    allFiguresLists.emplace_back();
    currentListIndex = allFiguresLists.size() - 1;
    cout << "Создан новый список фигур #" << (currentListIndex + 1) << endl;
}

void selectList() {
    if (allFiguresLists.empty()) {
        cout << "Нет созданных списков! Сначала создайте список." << endl;
        return;
    }

    cout << "\nДоступные списки:" << endl;
    for (size_t i = 0; i < allFiguresLists.size(); ++i) {
        cout << i + 1 << ". Список #" << i + 1 << " (фигур: " << allFiguresLists[i].size() << ")" << endl;
    }

    int choice;
    cout << "Выберите список (1-" << allFiguresLists.size() << "): ";
    cin >> choice;

    if (choice >= 1 && choice <= static_cast<int>(allFiguresLists.size())) {
        currentListIndex = choice - 1;
        cout << "Выбран список #" << choice << endl;
    } else {
        cout << "Неверный выбор!" << endl;
    }
}

void addFigure() {
    if (currentListIndex == -1) {
        cout << "Ошибка: сначала создайте или выберите список!" << endl;
        return;
    }

    int choice;
    while (true) {
        cout << "\nВыберите тип фигуры:" << endl;
        cout << "1. Квадрат" << endl;
        cout << "2. Круг" << endl;
        cout << "3. Треугольник" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            break;
        }
        cout << "Неверный выбор! Пожалуйста, выберите от 1 до 3." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double parameter;
    while (true) {
        cout << "Введите размер (сторону/радиус): ";
        cin >> parameter;

        if (cin.fail() || parameter <= 0) {
            cout << "Ошибка: размер должен быть положительным числом!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    switch (choice) {
        case 1:
            allFiguresLists[currentListIndex].push_back(make_unique<Square>(parameter));
            cout << "Квадрат добавлен в список #" << (currentListIndex + 1) << "!" << endl;
            break;
        case 2:
            allFiguresLists[currentListIndex].push_back(make_unique<Circle>(parameter));
            cout << "Круг добавлен в список #" << (currentListIndex + 1) << "!" << endl;
            break;
        case 3:
            allFiguresLists[currentListIndex].push_back(make_unique<Triangle>(parameter));
            cout << "Треугольник добавлен в список #" << (currentListIndex + 1) << "!" << endl;
            break;
    }
}


void showAllFiguresInList() {
    if (currentListIndex == -1) {
        cout << "Ошибка: сначала создайте или выберите список!" << endl;
        return;
    }

    auto& figures = allFiguresLists[currentListIndex];
    if (figures.empty()) {
        cout << "Список #" << (currentListIndex + 1) << " пуст!" << endl;
        return;
    }

    cout << "\n=== ФИГУРЫ В СПИСКЕ #" << (currentListIndex + 1) << " ===" << endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << i + 1 << ". ";
        figures[i]->displayInfo();
    }
}


void calculateAll() {
    if (currentListIndex == -1) {
        cout << "Ошибка: сначала создайте или выберите список!" << endl;
        return;
    }

    auto& figures = allFiguresLists[currentListIndex];
    if (figures.empty()) {
        cout << "Список #" << (currentListIndex + 1) << " пуст!" << endl;
        return;
    }

    double totalArea = 0;
    double totalPerimeter = 0;

    cout << "\n=== РАСЧЕТЫ ДЛЯ СПИСКА #" << (currentListIndex + 1) << " ===" << endl;
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


void showAllLists() {
    if (allFiguresLists.empty()) {
        cout << "Нет созданных списков!" << endl;
        return;
    }

    cout << "\n=== ВСЕ СОЗДАННЫЕ СПИСКИ ===" << endl;
    for (size_t i = 0; i < allFiguresLists.size(); ++i) {
        cout << "Список #" << i + 1 << ": " << allFiguresLists[i].size()
             << " фигур" << (i == currentListIndex ? " (текущий)" : "") << endl;
    }
}

int main() {
    int choice;

    setlocale(LC_ALL, "Russian");
    cout << "Программа для работы с геометрическими фигурами" << endl;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                createNewList();
                break;
            case 2:
                selectList();
                break;
            case 3:
                addFigure();
                break;
            case 4:
                showAllFiguresInList();
                break;
            case 5:
                calculateAll();
                break;
            case 6:
                showAllLists();
                break;
            case 7:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (choice != 7);

    return 0;
}
