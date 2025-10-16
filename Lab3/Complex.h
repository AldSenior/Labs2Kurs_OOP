#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    // Конструкторы
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Геттеры
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Модуль комплексного числа
    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    // Арифметические операторы
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                      (imag * other.real - real * other.imag) / denominator);
    }

    // Операторы сравнения (сравниваем по модулю)
    bool operator<(const Complex& other) const {
        return magnitude() < other.magnitude();
    }

    bool operator>(const Complex& other) const {
        return magnitude() > other.magnitude();
    }

    bool operator<=(const Complex& other) const {
        return magnitude() <= other.magnitude();
    }

    bool operator>=(const Complex& other) const {
        return magnitude() >= other.magnitude();
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // Унарные операторы
    Complex operator-() const {
        return Complex(-real, -imag);
    }

    // Операторы присваивания
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }

    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }

    // Операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) {
            os << " + " << c.imag << "i";
        } else {
            os << " - " << -c.imag << "i";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Complex& c) {
        std::cout << "Введите действительную часть: ";
        is >> c.real;
        std::cout << "Введите мнимую часть: ";
        is >> c.imag;
        return is;
    }
};

#endif
