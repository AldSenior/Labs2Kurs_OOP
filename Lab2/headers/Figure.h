#ifndef FIGURE_H
#define FIGURE_H
#include <string>
class Figure {
public:
    virtual ~Figure() = default;
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void displayInfo() const = 0;
    virtual std::string getType() const = 0;
};

#endif
