#include<iostream>
#include"Figures.h"
#include<cmath>
#include<cassert>

Trapeze::Trapeze() {};
Trapeze::Trapeze(std::istream& in) {
    in >> Vertexes[0].x >> Vertexes[0].y >> Vertexes[1].x >> Vertexes[1].y >> Vertexes[2].x >> Vertexes[2].y >> Vertexes[3].x >> Vertexes[3].y;
    assert(vector_product(Vertexes[0] - Vertexes[3], Vertexes[1] - Vertexes[2]) == 0);
}

Vertex Trapeze::center() const {

    Vertex res;
    for (int i = 0; i<4; i++)
        res += Vertexes[i];
    return res / 4;
}

double Trapeze::square() const {
    double Area = 0;
    for (int i = 0; i < 4; i++) {
        Area += (Vertexes[i].x) * (Vertexes[(i + 1) % 4].y) - (Vertexes[(i + 1) % 4].x)*(Vertexes[i].y);
    }
    Area *= 0.5;
    return abs(Area);
}

void Trapeze::print() const {
    std::cout << "Trapeze: ";
    for (int i = 0; i < 4; i++)
        std::cout << Vertexes[i] << ' ';
    std::cout << '\b';
}



Rhombus::Rhombus() {};
Rhombus::Rhombus(std::istream& in) {
    in >> Vertexes[0].x >> Vertexes[0].y >> Vertexes[1].x >> Vertexes[1].y >> Vertexes[2].x >> Vertexes[2].y >> Vertexes[3].x >> Vertexes[3].y;
    assert((distance(Vertexes[0], Vertexes[3]) == distance(Vertexes[0], Vertexes[1])) && (distance(Vertexes[0], Vertexes[3]) == distance(Vertexes[1], Vertexes[2])) && (distance(Vertexes[0], Vertexes[3]) == distance(Vertexes[2], Vertexes[3])));
}

Vertex Rhombus::center() const {
    Vertex res = Vertex();
    for (int i = 0; i<4; i++)
        res += Vertexes[i];
    return res / 4;
}

double Rhombus::square() const {
    double Area = 0;
    for (int i = 0; i < 4; i++) {
        Area += (Vertexes[i].x) * (Vertexes[(i + 1) % 4].y) - (Vertexes[(i + 1) % 4].x)*(Vertexes[i].y);
    }
    Area *= 0.5;
    return abs(Area);
}

void Rhombus::print() const  {
    std::cout << "Rhombus: ";
    for (int i = 0; i < 4; i++)
        std::cout << Vertexes[i] << ' ';
    std::cout << '\b';
}



Pentagon::Pentagon() {};
Pentagon::Pentagon(std::istream& in) {
    in >> Vertexes[0].x >> Vertexes[0].y >> Vertexes[1].x >> Vertexes[1].y >> Vertexes[2].x >> Vertexes[2].y >> Vertexes[3].x >> Vertexes[3].y >> Vertexes[4].x >> Vertexes[4].y;
}

Vertex Pentagon::center() const {
    Vertex res = Vertex();
    for (int i = 0; i < 5; i++)
        res += Vertexes[i];
    return res / 5;
}
double Pentagon::square() const  {
    /*double Area = 0;
    for (int i = 0; i < 5; i++) {
        Area += (Vertexes[i].x) * (Vertexes[(i + 1)%5].y) - (Vertexes[(i + 1)%5].x)*(Vertexes[i].y);
    }
    Area *= 0.5;
    return abs(Area); */

    double Area = 0;
    Area =(Vertexes[0].x*Vertexes[1].y+Vertexes[1].x*Vertexes[2].y+Vertexes[2].x*Vertexes[3].y+Vertexes[3].x*Vertexes[4].y+Vertexes[4].x*Vertexes[0].y-Vertexes[1].x*Vertexes[0].y-
       Vertexes[2].x*Vertexes[1].y-Vertexes[3].x*Vertexes[2].y-Vertexes[4].x*Vertexes[3].y-Vertexes[0].x*Vertexes[4].y)/2;
    if(Area < 0){
        return -Area;
    }else {
        return Area;
    }
}

void Pentagon::print() const {
    std::cout << "Pentagon: ";
    for (int i = 0; i < 5; i++)
        std::cout << Vertexes[i] << ' ';
    std::cout << '\b';
}