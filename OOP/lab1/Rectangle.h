#ifndef LABA1_HOME_RECTANGLE_H
#define LABA1_HOME_RECTANGLE_H
#include <iostream>

class Rectangle {
private:
    double left_lower_x;
    double left_lower_y;
    double right_upper_x;
    double right_upper_y;
    double a;
    double b;
    double move_x;
    double move_y;
    double x_size;

public:
    Rectangle(double llx, double lly, double rrx, double rry) : left_lower_x(llx), left_lower_y(lly),
                                                                right_upper_x(rrx), right_upper_y(rry) {}

    Rectangle() = default;

    double square;
    double perimetr;
    void Input(); // ввод с клавиатуры
    void Output(); // вывод на экран
    void Square(); // подсчет площади
    void Perimeter(); // подсчет периметра
    void Move(); // перемещение
    void Size(); // изменение размеров
    double Compare(); // сравнение по площади и периметру
    void Cross(); // Пересечение двух прямоугольников
    void Min(); // минимальный прямоугольник, включающий оба прямугольника
};

#endif LABA1_HOME_RECTANGLE_H

