#ifndef SQUARE_H
#define SQUARE_H
#include "Figure.h"
#include <iostream>
class Square : public Figure {
private:
    double side;
public:
    Square(double s) : side(s) {}

    double calculateArea() const override {
        return side * side;
    }

    double calculatePerimeter() const override {
        return 4 * side;
    }

    void displayInfo() const override {
        std::cout << "Квадрат: сторона = " << side
                  << ", площадь = " << calculateArea()
                  << ", периметр = " << calculatePerimeter() << std::endl;
    }

    std::string getType() const override {
        return "Квадрат";
    }
};
#endif
