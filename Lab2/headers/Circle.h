#ifndef CIRCLE_H
#define CIRCLE_H
#include "Figure.h"
#include <iostream>
#include <cmath>


class Circle : public Figure {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double calculateArea() const override {
        return M_PI * radius * radius;
    }

    double calculatePerimeter() const override {
        return 2 * M_PI * radius;
    }

    void displayInfo() const override {
        std::cout << "Круг: радиус = " << radius
                  << ", площадь = " << calculateArea()
                  << ", периметр = " << calculatePerimeter() << std::endl;
    }

    std::string getType() const override {
        return "Круг";
    }
};

#endif
