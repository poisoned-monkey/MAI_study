#include <iostream>
#include "Rectangle.h"
#include <algorithm>

void Rectangle::Input(std::istream& is) {
    is >> left_lower_x >> left_lower_y;
    is >> right_upper_x >> right_upper_y;
}
void Rectangle::Output(std::ostream& os) const {
    os << "A - " << "(" << left_lower_x << "," << left_lower_y << ")" << std::endl;
    os << "B - " << "(" << left_lower_x << "," << right_upper_y << ")" << std::endl;
    os << "C - " << "(" << right_upper_x << "," << right_upper_y << ")" << std::endl;
    os << "D - " << "(" << right_upper_x << "," << left_lower_y << ")" << std::endl;
}

double Rectangle::Square() const {
    double a = right_upper_y - left_lower_y;
    double b = right_upper_x - left_lower_x;
    double square = a * b;
    return square;
}

double Rectangle::Perimeter() const {
    double a = right_upper_y - left_lower_y;
    double b = right_upper_x - left_lower_x;
    double perimeter = 2 * (a + b);
    return perimeter;
}

Rectangle Rectangle::Move(double dx, double dy) const {
    Rectangle result;
    result.left_lower_x = left_lower_x  + dx;
    result.left_lower_y = left_lower_y + dy;
    result.right_upper_x = right_upper_x + dx;
    result.right_upper_y = right_upper_y + dy;
    return result;
}

Rectangle Rectangle::Resize(double alpha) const {
    Rectangle result;
    result.left_lower_x = left_lower_x * alpha;
    result.left_lower_y = left_lower_y * alpha;
    result.right_upper_x = right_upper_x * alpha;
    result.right_upper_y = right_upper_y * alpha;
    return result;
}
bool Rectangle::Compare_by_square(const Rectangle& other) const {
    return Square() > other.Square();
}


bool Rectangle::Compare_by_perimeter(const Rectangle& other) const {
    return Perimeter() > other.Perimeter();
}

Rectangle Rectangle::Min(const Rectangle& other) const {
    Rectangle result;
    result.left_lower_x = std::min(left_lower_x, other.left_lower_x);
    result.left_lower_y = std::min(left_lower_y, other.left_lower_y);
    result.right_upper_x = std::max(right_upper_x, other.right_upper_x);
    result.right_upper_y = std::max(right_upper_y, other.right_upper_y);
    return result;

}

Rectangle Rectangle::Cross(const Rectangle& other) const {
    Rectangle result;
    result.left_lower_x = std::max(left_lower_x, other.left_lower_x);
    result.left_lower_y = std::max(left_lower_y, other.left_lower_y);
    result.right_upper_x = std::min(right_upper_x, other.right_upper_x);
    result.right_upper_y = std::min(right_upper_y, other.right_upper_y);

    if (result.left_lower_x > result.right_upper_x || result.left_lower_y > result.right_upper_y) {
        result.right_upper_x = result.left_lower_x;
        result.right_upper_y = result.left_lower_y;
    }
    return result;
}



Rectangle::operator double() const {
    return Square();
}

Rectangle Rectangle::operator++(){
    right_upper_x++;
    right_upper_y++;
    return *this;
}


//Rectangle Rectangle::operator++(int) {
  //  Rectangle result = *this;
    //right_upper_x++;
    //right_upper_y++;
    //return result;
//}

Rectangle Rectangle::operator++(int) {
  Rectangle temp = *this;
  ++(*this);
  return temp;
}

bool Rectangle::operator>(const Rectangle& other) const{
    return Square() > other.Square();
}

bool Rectangle::operator<(const Rectangle& other) const{
    return Square() < other.Square();
}

bool Rectangle::operator==(const Rectangle& other) const {
    return Square() == other.Square();
}

bool Rectangle::operator!=(const Rectangle& other) const {
    return Square() != other.Square();
}

std::istream& operator >> (std::istream& stream, Rectangle& in)
{
    stream >> in.left_lower_x >> in.left_lower_y >> in.right_upper_x >> in.right_upper_y;
    return stream;
}

std::ostream& operator << (std::ostream& stream, const Rectangle& out) {
    out.Output(stream);
    return stream;
}

Rectangle Rectangle::operator&(const Rectangle& other) const{
    return Cross(other);
}

Rectangle Rectangle::operator|(const Rectangle& other) const{
    return Min(other);
}

Rectangle operator"" _square(long double n) {
    Rectangle lit(0, 0, n, n);
    return lit;
}

