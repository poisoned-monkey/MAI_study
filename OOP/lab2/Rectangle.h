#ifndef LABA1_HOME_RECTANGLE_H
#define LABA1_HOME_RECTANGLE_H
#include <iostream>

class Rectangle {
private:
    double left_lower_x;
    double left_lower_y;
    double right_upper_x;
    double right_upper_y;

public:
    Rectangle(double llx, double lly, double rrx, double rry) : left_lower_x(llx), left_lower_y(lly),
                                                                right_upper_x(rrx), right_upper_y(rry) {}

    Rectangle() = default;

    void Input(std::istream&); // ввод с клавиатуры
    void Output(std::ostream&) const; // вывод на экран
    double Square() const; // подсчет площади
    double Perimeter() const; // подсчет периметра
    Rectangle Move(double dx, double dy) const; // перемещение
    Rectangle Resize(double alpha) const; // изменение размеров
    bool Compare_by_square(const Rectangle& other) const; // сравнение по площади
    bool Compare_by_perimeter(const Rectangle& other) const; // сравнение по периметру
    Rectangle Cross(const Rectangle& other) const; // Пересечение двух прямоугольников
    Rectangle Min(const Rectangle& other) const; // минимальный прямоугольник, включающий оба прямугольника

    operator double () const;
    Rectangle operator++();
    Rectangle operator++(int);
    bool operator>(const Rectangle& other) const;
    bool operator<(const Rectangle& other) const;
    bool operator==(const Rectangle& other) const;
    bool operator!=(const Rectangle& other) const;
    Rectangle operator&(const Rectangle& other) const;
    Rectangle operator|(const Rectangle& other) const;

   friend std::ostream& operator << (std::ostream& stream, const Rectangle& out);
   friend std::istream& operator >> (std::istream& stream, Rectangle& in);
};

   Rectangle operator"" _square(long double n);


#endif //LABA1_HOME_RECTANGLE_H

