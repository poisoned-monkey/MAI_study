#include<iostream>
#include"Figures.h"
#include<locale>

int option() {
    int Menu;
    std::cout << "1. Ввести фигуру" << std::endl;
    std::cout << "2. Вычислить центр фигуры по индексу" << std::endl;
    std::cout << "3. Вычислить площадь фигуры по индексу" << std::endl;
    std::cout << "4. Распечатать коориднаты фигуры по индексу" << std::endl;
    std::cout << "5. Вычислить общую площадь всех фигур" << std::endl;
    std::cout << "6. Удалить фигуру по индексу" << std::endl;
    std::cin >> Menu;
    return Menu;
}

int figure() {
    int Menu;
    std::cout << "1. Ввести трапецию" << std::endl;
    std::cout << "2. Ввести ромб" << std::endl;
    std::cout << "3. Ввести пятиугольник" << std::endl;
    std::cin >> Menu;
    return Menu;
}

int main() {

    setlocale(LC_ALL, "rus");
    int Menu_1,Menu_2, Index;
    Figure* f;
    std::vector<Figure*> Figures;
    double SummaryArea = 0;
    while (true) {
        switch (Menu_1 = option()) {
            case 1:
                switch (Menu_2 = figure()) {
                    case 1:
                        f = new Trapeze{ std::cin };
                        break;
                    case 2:
                        f = new Rhombus{ std::cin };
                        break;
                    case 3:
                        f = new Pentagon(std::cin);
                        break;
                }
                Figures.push_back(f);
                break;
            case 2:
                std::cout << "Введите индекс: ";
                std::cin >> Index;
                if (Figures[Index] != nullptr)
                    std::cout << "Центр фигуры по индексу " << Index << ": " << (*Figures[Index]).center() << std::endl;
                break;
            case 3:
                std::cout << "Введите индекс: ";
                std::cin >> Index;
                if (Figures[Index] != nullptr)
                    std::cout << "Площадь фигуры по индексу " << Index << ": " << (*Figures[Index]).square() << std::endl;
                break;
            case 4:
                std::cout << "Введите индекс: ";
                std::cin >> Index;
                std::cout << "Координты фигуры по индексу " << Index << ": ";
                (*Figures[Index]).print();
                std::cout << std::endl;
                continue;
            case 5:
                for (int i = 0; i < (int)Figures.size(); i++)
                    if (Figures[i] != nullptr) {
                        (*Figures[i]).print();
                        std::cout << std::endl;
                        std::cout << "Area: " << (*Figures[i]).square() << std::endl;
                        std::cout << "Center: " << (*Figures[i]).center() << std::endl;
                    }
                for (int i = 0; i < Figures.size(); i++) {
                    SummaryArea += Figures[i]->square();
                }
                std::cout << "Общая площадь фигур: " << SummaryArea << std::endl;
                break;
            case 6:
                std::cout << "Введите индекс: ";
                std::cin >> Index;
                std::swap(Figures[Figures.size() - 1], Figures[Index]);
                delete Figures[Figures.size() - 1];
                Figures.pop_back();
                break;
            default:
                for (int i = 0; i < (int)Figures.size(); i++) {
                    delete Figures[i];
                    Figures[i] = nullptr;
                }

                return 0;
        }
    }
    return 0;
}