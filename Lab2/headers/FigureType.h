#ifndef ENUM_H
#define ENUM_H
#include <iostream>
enum class  FigureType {
    CIRCLE,
    SQUARE,
    TRIANGLE
};
inline std::string FigureTypeToString(FigureType shape) {
    switch (shape) {
        case FigureType::CIRCLE:
            return "Круг";
        case FigureType::SQUARE:
            return "Квадрат";
        case FigureType::TRIANGLE:
            return "Треугольник";
        default:
            return "Неизвестная фигура";
    }
}
#endif
