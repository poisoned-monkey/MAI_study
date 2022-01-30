#pragma once
#include"../tools.h"
#include"figure.h"
#include<memory>
struct  rhombus : figure {
    rhombus(const std::array<vertex, 4>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer) const override {
        renderer.set_color(color_.r, color_.g, color_.b);
        for (int32_t i = 0; i < 4; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                               vertices_[(i + 1) % 4].x, vertices_[(i + 1) % 4].y);
        }
    }

    void save(std::ostream& os) const override {
        os << "rhombus" << std::endl;
        for (int32_t i = 0; i < 4; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }

        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }

private:
    std::array<vertex, 4> vertices_;

};


struct  rhombus_builder : builder {
private:
    int32_t n_ = 0;
    std::array<vertex, 4> vertices_;

public:
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        vertices_[n_] = v;
        n_ += 1;
        if (n_ != 4) {
            return nullptr;
        }
        return std::make_unique<rhombus>(vertices_);
    }

};