#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "Figure.h"
#include <cmath>
#include <memory>
#include <iomanip>
#include <vector>
class Triangle : public Figure {
private:
    double side;
public:
    Triangle(double s) : side(s) {}

    double calculateArea() const override {
        return (sqrt(3) / 4) * side * side;
    }

    double calculatePerimeter() const override {
        return 3 * side;
    }

    void displayInfo() const override {
        std::cout << "Треугольник: сторона = " << side
                  << ", площадь = " << calculateArea()
                  << ", периметр = " << calculatePerimeter() << std::endl;
    }

    std::string getType() const override {
        return "Треугольник";
    }
};

#endif
