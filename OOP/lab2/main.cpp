#include <iostream>
#include "Rectangle.h"

int main() {
    Rectangle rectangle1;
    Rectangle rectangle2;

    std::cin >> rectangle1;
    std::cin >> rectangle2;
    std::cout << rectangle1 << std::endl;
    std::cout << rectangle2 << std::endl;


    std::cout << (rectangle1 & rectangle2) << "\n";
    std::cout << (rectangle1 | rectangle2) << "\n";
    std::cout << (rectangle1 < rectangle2) << "\n";
    std::cout << (rectangle1 == rectangle2) << "\n";
    std::cout << double(rectangle1) << "\n";
    std::cout << rectangle1++ << "\n";
    std::cout << ++rectangle1 << "\n";
    std::cout << 1._square << "\n";





}
