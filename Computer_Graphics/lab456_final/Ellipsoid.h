
#ifndef KG45_ELLIPSOID_H
#define KG45_ELLIPSOID_H

#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>

void PushPointToVector(std::vector<float>& points, glm::vec3 p);


class Ellipsoid {
public:
    Ellipsoid() = default;
    Ellipsoid(float _a, float _b, float _c, float _up_cut, float _down_cut, int _layers, int _points);

    void SetCutFactors(float up, float down);

    void SetParams(float _a, float _b, float _c);

    void SetPointCount(int _count);

    void SetLayerCount(int _count);

    bool isChanged() const;



    std::vector<float> GetTriangles() const;

private:

    std::vector<glm::vec3> GetPoints() const;
    float a = 1,b = 1,c = 1;
    float up_cut_factor = 0;
    float down_cut_factor = 0;
    int layer_count = 100;
    int point_count = 100;
    mutable bool changed = false;
};


#endif //KG45_ELLIPSOID_H
