#ifndef KG_KP_BEZIER_H
#define KG_KP_BEZIER_H
#include <stdexcept>
#include <glm/glm.hpp>
#include <vector>
#include "../math/math.h"

class Bezier {
public:
    Bezier() = default;
    Bezier(std::vector<glm::vec3> points);

    void UpdatePointVector(std::vector<glm::vec3> points);
    void UpdatePoint(size_t index, glm::vec3 point);
    void AppendPoint(glm::vec3 point);
    void SetPrecision(size_t p);
    const std::vector<glm::vec3>& GetPoints() const;
    const std::vector<glm::vec3>& GetKeyPoints() const;

    bool isChanged() const;
    void setChanged(bool ch);

private:
    mutable std::vector<glm::vec3> points;
    static double J(double t, int n, int i);
    mutable bool changed = true;
    size_t precision = 2;

    std::vector<glm::vec3> key_points;
};


#endif //KG_KP_BEZIER_H
