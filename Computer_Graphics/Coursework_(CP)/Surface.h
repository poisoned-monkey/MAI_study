#ifndef KG_KP_SURFACE_H
#define KG_KP_SURFACE_H
#include "curves/Bezier.h"
#include <glm/gtx/normal.hpp>

class Surface {
public:
    Surface() = default;
    Surface(std::vector<glm::vec3> curve1, std::vector<glm::vec3> curve2);

    Bezier& GetFirstCurve();
    const Bezier& GetFirstCurve() const;
    Bezier& GetSecondCurve();
    const Bezier& GetSecondCurve() const;
    void SetPrecision(size_t p);

    bool isChanged();

    std::vector<glm::vec3> GetPoints() const;
    std::vector<float> GetTriangles() const;


private:
    mutable std::vector<glm::vec3> surface_points;
    void RecalculatePoints() const;
    size_t precision = 2;
    mutable bool changed = true;
    Bezier first_curve{{glm::vec3(0.f),glm::vec3(0.f),glm::vec3(0.f),glm::vec3(0.f),glm::vec3(0.f)}};
    Bezier second_curve{{glm::vec3(0.f),glm::vec3(0.f),glm::vec3(0.f),glm::vec3(0.f),glm::vec3(0.f)}};
};


#endif //KG_KP_SURFACE_H
