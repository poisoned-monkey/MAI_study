#include <iostream>
#include "Rectangle.h"

void Rectangle::Input() {
    std::cout << "Введите координаты левой нижней точки" << std::endl;
    std::cin >> left_lower_x >> left_lower_y;
    std::cout << "Введите координаты правой верхней точки" << std::endl;
    std::cin >> right_upper_x >> right_upper_y;
}
void Rectangle::Output() {
    std::cout << "A - " << "(" << left_lower_x << "," << left_lower_y << ")" << std::endl;
    std::cout << "B - " << "(" << left_lower_x << "," << right_upper_y << ")" << std::endl;
    std::cout << "C - " << "(" << right_upper_x << "," << right_upper_y << ")" << std::endl;
    std::cout << "D - " << "(" << right_upper_x << "," << left_lower_y << ")" << std::endl;
}

void Rectangle::Square() {
    std::cout << "Введите координаты левой нижней точки" << std::endl;
    std::cin >> left_lower_x >> left_lower_y;
    std::cout << "Введите координаты правой верхней точки" << std::endl;
    std::cin >> right_upper_x >> right_upper_y;
    double a = right_upper_y - left_lower_y;
    double b = right_upper_x - left_lower_x;
    double square = a * b;
    std::cout << "Площадь прямоугольника равна: " << square << std::endl;
}

void Rectangle::Perimeter() {
    std::cout << "Введите координаты левой нижней точки" << std::endl;
    std::cin >> left_lower_x >> left_lower_y;
    std::cout << "Введите координаты правой верхней точки" << std::endl;
    std::cin >> right_upper_x >> right_upper_y;
    double a = right_upper_y - left_lower_y;
    double b = right_upper_x - left_lower_x;
    double perimeter = 2 * (a + b);
    std::cout << "Периметр прямоугольника равен: " << perimeter << std::endl;
}

void Rectangle::Move() {
    std::cout << "На сколько единиц вы хотите переместить прямоугольник по оси x?" << std::endl;
    std::cin >> move_x;
    std::cout << "На сколько единиц вы хотите переместить прямоугольник по оси y?" << std::endl;
    std::cin >> move_y;

    std::cout << "Координаты нового прямоугольника:" << std::endl;
    std::cout << "A:" << "(" << left_lower_x + move_x << ", " << left_lower_y + move_y << ")" << std::endl;
    std::cout << "B:" << "(" << left_lower_x + move_x << ", " << right_upper_y + move_y << ")" << std::endl;
    std::cout << "C:" << "(" << right_upper_x + move_x << ", " << right_upper_y + move_y << ")" << std::endl;
    std::cout << "D:" << "(" << right_upper_x + move_x << ", " << left_lower_y + move_y << ")" << std::endl;
}

void Rectangle::Size() {
    std::cout << "Во сколько раз вы хотите изменить размеры прямоугольника?" << std::endl;
    std::cin >> x_size;
    std::cout << "Координаты нового прямоугольника:" << std::endl;
    std::cout << "A - " << "(" << left_lower_x * x_size << "," << left_lower_y * x_size << ")" << std::endl;
    std::cout << "B - " << "(" << left_lower_x * x_size << "," << right_upper_y * x_size << ")" << std::endl;
    std::cout << "C - " << "(" << right_upper_x * x_size << "," << right_upper_y *x_size << ")" << std::endl;
    std::cout << "D - " << "(" << right_upper_x * x_size << "," << left_lower_y * x_size << ")" << std::endl;
}
double Rectangle::Compare() {
    double left_lower_x_2, left_lower_y_2, right_upper_x_2, right_upper_y_2, a_2, b_2;
    double square1 = square;
    double perimeter1 = perimetr;
    std::cout << "Введите координаты левой нижней точки второго прямоугольника" << std::endl;
    std::cin >> left_lower_x_2 >> left_lower_y_2;
    std::cout << "Введите координаты правой верхней точки второго прямоугольника" << std::endl;
    std::cin >> right_upper_x_2 >> right_upper_y_2;
    a_2 = right_upper_y_2 - left_lower_y_2;
    b_2 = right_upper_x_2 - left_lower_x_2;
    double square2 = a_2 * b_2;
    double perimeter2 = (a_2 + b_2) * 2;
    if (square1 < square2) {
        std::cout << "Площадь первого прямоугольника больше площади второго" << std::endl;
    } else if (square1 > square2) {
        std::cout << "Площадь второго прямоугольника больше площади первого" << std::endl;
    } else if (square1 == square2) {
        std::cout << "Площадь первого и второго прямоугольника равны" << std::endl;
    }
    if (perimeter1 < perimeter2) {
        std::cout << "Периметр первого прямоугольника больше периметра второго" << std::endl;
    } else if (perimeter1 > perimeter2) {
        std::cout << "Периметр второго прямоугольника больше периметра первого" << std::endl;
    } else if (perimeter1 == perimeter2) {
        std::cout << "Периметры первого и второго прямоугольника равны" << std::endl;
    }
}

void Rectangle::Min() {
    double left_lower_x_2, left_lower_y_2, right_upper_x_2, right_upper_y_2, x_max = left_lower_x, y_max = left_lower_y, x_min = left_lower_x , y_min = left_lower_y;
    std::cout << "Введите координаты левой нижней точки второго прямоугольника" << std::endl;
    std::cin >> left_lower_x_2 >> left_lower_y_2;
    std::cout << "Введите координаты правой верхней точки второго прямоугольника" << std::endl;
    std::cin >> right_upper_x_2 >> right_upper_y_2;

    std::cout << "Координаты первого прямоугольника: " << std::endl;
    std::cout << "A - " << "(" << left_lower_x << "," << left_lower_y << ")" << std::endl;
    std::cout << "B - " << "(" << left_lower_x << "," << right_upper_y << ")" << std::endl;
    std::cout << "C - " << "(" << right_upper_x << "," << right_upper_y << ")" << std::endl;
    std::cout << "D - " << "(" << right_upper_x << "," << left_lower_y << ")" << std::endl;

    std::cout << "Координаты второго прямоугольника: " << std::endl;
    std::cout << "A - " << "(" << left_lower_x_2 << "," << left_lower_y_2 << ")" << std::endl;
    std::cout << "B - " << "(" << left_lower_x_2 << "," << right_upper_y_2 << ")" << std::endl;
    std::cout << "C - " << "(" << right_upper_x_2 << "," << right_upper_y_2 << ")" << std::endl;
    std::cout << "D - " << "(" << right_upper_x_2 << "," << left_lower_y_2 << ")" << std::endl;

    double A[4] = {left_lower_x, right_upper_x, left_lower_x_2, right_upper_x_2}, B[4] = {left_lower_y, right_upper_y, left_lower_y_2, right_upper_y_2};
    for (int i = 0; i < 4; i++) {
        if (x_min > A[i]) {
            x_min = A[i];
        }
        if (y_min > A[i]) {
            y_min = A[i];
        }
        if (x_max < A[i]) {
            x_max = A[i];
        }
        if (y_max < A[i]) {
            y_max = A[i];
        }
    }
    std::cout << "Координаты наименьшего прямоугольника, содержащего два введенных прямоугольника:" << std::endl;
    std::cout << "A - " << "(" << x_min << "," << y_min << ")" << std::endl;
    std::cout << "B - " << "(" << x_min << "," << y_max << ")" << std::endl;
    std::cout << "C - " << "(" << x_max << "," << y_max << ")" << std::endl;
    std::cout << "D - " << "(" << x_max << "," << y_min << ")" << std::endl;
}

void Rectangle::Cross() {
    double left_lower_x_2, left_lower_y_2, right_upper_x_2, right_upper_y_2, x_max = left_lower_x, y_max = left_lower_y, x_min = left_lower_x , y_min = left_lower_y, x_1_middle, x_2_middle, y_1_middle, y_2_middle;
    std::cout << "Введите координаты левой нижней точки второго прямоугольника" << std::endl;
    std::cin >> left_lower_x_2 >> left_lower_y_2;
    std::cout << "Введите координаты правой верхней точки второго прямоугольника" << std::endl;
    std::cin >> right_upper_x_2 >> right_upper_y_2;

    std::cout << "Координаты первого прямоугольника: " << std::endl;
    std::cout << "A - " << "(" << left_lower_x << "," << left_lower_y << ")" << std::endl;
    std::cout << "B - " << "(" << left_lower_x << "," << right_upper_y << ")" << std::endl;
    std::cout << "C - " << "(" << right_upper_x << "," << right_upper_y << ")" << std::endl;
    std::cout << "D - " << "(" << right_upper_x << "," << left_lower_y << ")" << std::endl;

    std::cout << "Координаты второго прямоугольника: " << std::endl;
    std::cout << "A - " << "(" << left_lower_x_2 << "," << left_lower_y_2 << ")" << std::endl;
    std::cout << "B - " << "(" << left_lower_x_2 << "," << right_upper_y_2 << ")" << std::endl;
    std::cout << "C - " << "(" << right_upper_x_2 << "," << right_upper_y_2 << ")" << std::endl;
    std::cout << "D - " << "(" << right_upper_x_2 << "," << left_lower_y_2 << ")" << std::endl;

    double A[4] = {left_lower_x, right_upper_x, left_lower_x_2, right_upper_x_2}, B[4] = {left_lower_y, right_upper_y, left_lower_y_2, right_upper_y_2};
    for (int i = 0; i < 4; i++) {
        if (x_min > A[i]) {
            x_min = A[i];
        }
        if (y_min > A[i]) {
            y_min = A[i];
        }
        if (x_max < A[i]) {
            x_max = A[i];
        }
        if (y_max < A[i]) {
            y_max = A[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        if ((A[i] !=  x_max) && (A[i] != x_min)) {
            x_1_middle = A[i];
            break;
            ;            }
    }

    for (int i = 0; i < 4; i++) {
        if ((A[i] != x_max) && (A[i] != x_min) && (A[i] != x_1_middle)) {
            x_2_middle = A[i];
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        if ((A[i] != y_max) && (A[i] != y_min)) {
            y_1_middle = A[i];
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        if ((A[i] != y_max) && (A[i] != y_min) && (A[i] != y_1_middle)) {
            y_2_middle = A[i];
            break;
        }
    }

    std::cout << "Прямоугольник, представляющий общую часть двух прямоугольников, имеет координаты: " << std::endl;
    std::cout << "A - " << "(" << x_1_middle << "," << y_2_middle << ")" << std::endl;
    std::cout << "B - " << "(" << x_2_middle << "," << y_2_middle << ")" << std::endl;
    std::cout << "C - " << "(" << x_2_middle << "," << y_1_middle << ")" << std::endl;
    std::cout << "D - " << "(" << x_1_middle << "," << y_1_middle << ")" << std::endl;
}
