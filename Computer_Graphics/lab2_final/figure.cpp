#include "figure.h"

Figure::Figure(QObject* parent)
    : QObject(parent) {}

Figure& Figure::setProjecter(Projecter *_projecter) {
    if (_projecter == projecter) {
        return *this;
    }
    if (projecter) {
        disconnect(projecter, &Projecter::updated, this, &Figure::projecterUpdated);
    }
    projecter = _projecter;
    if (projecter) {
        connect(projecter, &Projecter::updated, this, &Figure::projecterUpdated);
    }
    return *this;
}

Figure& Figure::setRasterizer(Rasterizer* _rasterizer) {
    rasterizer = _rasterizer;
    return *this;
}

Figure& Figure::setInvisibleDeleter(InvisibleDeleter* _deleter) {
    deleter = _deleter;
    return *this;
}

Figure& Figure::setTransformer(Transformer* _transformer) {
    if (transformer == _transformer) {
        return *this;
    }
    if (transformer) {
        disconnect(transformer, &Transformer::updated, this, &Figure::transformerUpdated);
    }
    transformer = _transformer;
    if (transformer) {
        connect(transformer, &Transformer::updated, this, &Figure::transformerUpdated);
    }
    return *this;
}

void Figure::projecterUpdated() {
    projecter_changed = true;
}

void Figure::transformerUpdated() {
    transformer_changed = true;
}

void Figure::updatePoints() {
    if (!transformer) {
        throw std::logic_error("No transformer");
    }
    if (!rasterizer) {
        throw std::logic_error("No rasterizer");
    }
    if (transformer_changed) {
        updateTransformedPoints();
        updateProjectedPoints();
        producePolygons();
        updateVisiblePoints();
        updateRasterizedPoints();
        transformer_changed = false;
        projecter_changed = false;
    } else if (!transformer_changed && projecter_changed) {
        updateProjectedPoints();
        producePolygons();
        updateVisiblePoints();
        updateRasterizedPoints();
        projecter_changed = false;
    }
}



void Figure::paint(QPainter *ptr) {
    updatePoints();
    drawFigure(ptr);
}

void Figure::drawFigure(QPainter *ptr) {
    for (const RasterPolygon& p : rasterized_polygons) {
        for (int i = 0; i < p.size(); ++i) {
            ptr->drawLine(p[i], p[(i + 1) % p.size()]);
        }
    }

}


void Figure::updateRasterizedPoints() {
    rasterized_polygons = rasterizer->rasterize(visible_polygons);
}

void Figure::updateTransformedPoints() {
    transformed_points = transformer->transform(figure_points);
}

void Figure::updateProjectedPoints() {
    if (!projecter) {
        projected_points = transformed_points;
    } else {
        projected_points = projecter->project(transformed_points);
    }
}

void Figure::updateVisiblePoints() {
    if (!deleter) {
        visible_polygons = polygons;
    } else {
        visible_polygons = deleter->deleteInvisible(polygons);
    }
}


Figure::~Figure() {
    if (transformer) {
        disconnect(transformer, &Transformer::updated, this, &Figure::transformerUpdated);
    }
    if (projecter) {
        disconnect(projecter, &Projecter::updated, this, &Figure::projecterUpdated);
    }
}
