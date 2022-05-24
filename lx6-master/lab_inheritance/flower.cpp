/**
 * @file flower.cpp
 * Implementation of the Flower class.
 */

#include "flower.h"

#include <cmath>
#include <cstdio>

#include "circle.h"
#include "color.h"
#include "rectangle.h"
#include "triangle.h"

using cs225::PNG;
using cs225::HSLAPixel;

const int STEM_HEIGHT = 32;
const int STEM_WIDTH = 2;
const HSLAPixel STEM_COLOR = color::GREEN;

const int LEAF_WIDTH = 16;
const int LEAF_HEIGHT = 16;
const HSLAPixel LEAF_COLOR = color::GREEN;

const int PISTIL_RADIUS = 12;
const HSLAPixel PISTIL_COLOR = color::YELLOW;

const int PETAL_RADIUS = 2;
const HSLAPixel PETAL_COLOR = color::RED;

Flower::Flower(const Vector2& center)
{
    const Vector2 stem_center(center.x(), center.y() + STEM_HEIGHT / 2);
    Rectangle my_stem(stem_center, STEM_COLOR, STEM_WIDTH, STEM_HEIGHT);
    stem = new Rectangle(stem_center, STEM_COLOR, STEM_WIDTH, STEM_HEIGHT);
    // if we just write: stem = newsteam, the newsteam is not a pointer

    Circle my_pistil(Vector2(center.x(), center.y() - PISTIL_RADIUS / 2),
                     PISTIL_COLOR, PISTIL_RADIUS);
    // if we just write: pistil = newpistil,  is not a pointer
    pistil = new Circle(Vector2(center.x(), center.y() - PISTIL_RADIUS / 2),
                     PISTIL_COLOR, PISTIL_RADIUS);
    // if we just write: leaf = newleaf,  is not a pointer
    const Vector2 leaf_center(stem_center.x() - STEM_WIDTH / 2 + 1,
                              stem_center.y() + STEM_HEIGHT / 4);
    // if we just write: leaf = newleaf,  is not a pointer
    leaf = new Triangle(LEAF_COLOR,
        Vector2(leaf_center.x(), leaf_center.y() - STEM_HEIGHT / 4),
        Vector2(leaf_center.x() - LEAF_WIDTH, leaf_center.y() - LEAF_HEIGHT),
        Vector2(leaf_center.x() - LEAF_WIDTH / 2, leaf_center.y()));
}


void Flower::drawPetals(PNG* canvas, const Vector2& center, int x, int y) const
{
    Circle petal(center, PETAL_COLOR, PETAL_RADIUS);
    petal.set_center(Vector2(center.x() + x, center.y() + y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + x, center.y() - y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - x, center.y() + y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - x, center.y() - y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + y, center.y() + x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + y, center.y() - x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - y, center.y() + x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - y, center.y() - x));
    petal.draw(canvas);
}

void Flower::draw(PNG* canvas) const
{
    stem->draw(canvas);
    pistil->draw(canvas);
    leaf->draw(canvas);
    for (int x = 0; x < PISTIL_RADIUS; x++) {
        const double radius2 = PISTIL_RADIUS * PISTIL_RADIUS;
        const int y = static_cast<int>(sqrt(radius2 - (x * x)));
        drawPetals(canvas, pistil->center(), x, y);
    }
}

Flower::~Flower() {
    if (stem != NULL) {
        delete stem; 
        stem = NULL;
    }
    if (pistil != NULL) {
        delete pistil; 
        pistil = NULL;
    }
    if (leaf != NULL) {
        delete leaf; 
        leaf = NULL;
    }
}