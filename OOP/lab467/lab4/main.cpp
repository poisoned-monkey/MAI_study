#include <iostream>
#include <tuple>

#include "vertex.h"
#include "trapeze.h"
#include "rhombus.h"
#include "pentagon.h"
#include "templates.h"

template<class T>
void process() {
    T object;
    read(std::cin, object);
    print(std::cout, object);
    std::cout << square(object) << std::endl;
    std::cout << center(object) << std::endl;
}

int main() {
    std::cout << "Как вы хотите ввести фигуру: " << std::endl;
    std::cout << "1. Кортеж(Tuple)" << std::endl;
    std::cout << "2. Класс" << std::endl;
    int menu, angles, figure;
    std::cin >> menu;
    std::cout << "Сколько углов у фигуры (4, 5): " << std::endl;
    std::cin >> angles;
    switch (menu) {
        case 1 :
            switch (angles) {
                case 4:
                    process<std::tuple<Vertex<double>, Vertex<double>, Vertex<double>, Vertex<double>>>();
                    break;
                case 5:
                    process<std::tuple<Vertex<double>, Vertex<double>, Vertex<double>, Vertex<double>, Vertex<double>>>();
                    break;
            }
            break;
        case 2:
            switch (angles) {
                case 4:
                    std::cout << "Введите фигуру: " << std::endl;
                    std::cout << "1. Трапеция" << std::endl;
                    std::cout << "2. Ромб" << std::endl;
                    std::cin >> figure;
                    switch (figure) {
                        case 1:
                            process<Trapeze<double>>();
                            break;
                        case 2:
                            process<Rhombus<double>>();
                            break;
                    }
                    break;
                case 5:
                    process<Pentagon<double>>();
                    break;
            }
            break;
    }
    system("pause");
    return 0;
}