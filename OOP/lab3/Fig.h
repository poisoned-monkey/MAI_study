#pragma once
#include<iostream>
#include<vector>
#include"Vertex.h"
class Figure {
public:
    virtual Vertex center() const = 0;
    virtual double square() const = 0;
    virtual void print() const = 0;
};