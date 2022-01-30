#include <iostream>
#include "Rectangle.h"

int main() {
    std::cout << "Меню: \n 1 - Ввод данных \n 2 - Вывод данных \n 3 - Подсчет площади \n 4 - Подсчет периметра \n 5 - Перемещение прямоугольника \n 6 - Изменение размеров \n 7 - Сравнение двух прмоугольников \n 8 - Пересечение двух прямоугольников \n 9 - Минимальный прямоугольник, влючающий оба прямоугольника \n 0 - выход\n" << std::endl;

    Rectangle Object1;
    bool control=true;
    int myCase=-1;
    std::cout << ">" << std::endl;


while (control) {
    std::cin>>myCase;
        switch (myCase) {
            case 1: {
                Object1.Input();
                std::cout << ">" << std::endl;
                break;
            }
                case 2: {
                    Object1.Output();
                    std::cout << ">" << std::endl;
                    break;
                }
                    case 3: {
                        Object1.Square();
                        std::cout << ">" << std::endl;
                        break;
                    }
                        case 4: {
                            Object1.Perimeter();
                            std::cout << ">" << std::endl;
                            break;
                        }
                            case 5: {
                                Object1.Move();
                                std::cout << ">" << std::endl;
                                break;
                            }
                                case 6: {
                                    Object1.Size();
                                    std::cout << ">" << std::endl;
                                    break;
                                }
                                    case 7: {
                                        Object1.Compare();
                                        std::cout << ">" << std::endl;
                                        break;
                                    }
                                        case 8: {
                                            Object1.Cross();
                                            std::cout << ">" << std::endl;
                                            break;
                                        }
                                            case 9: {
                                                Object1.Min();
                                                std::cout << ">" << std::endl;
                                                break;
                                            }

                                                case 0:
                                                    {
                                                    control = false;
                                                    break;
                                                }
        }
    }
        return 0;
    }

