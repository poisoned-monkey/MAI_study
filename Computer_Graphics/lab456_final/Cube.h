#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>

void PushPointToVector(std::vector<float>& points, glm::vec3 p);

class Cube {
public:
    Cube() = default;

    std::vector<float> GetTriangles() const;
};