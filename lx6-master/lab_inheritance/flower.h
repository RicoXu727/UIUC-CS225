/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once

#include "shape.h"

/**
 * A subclass of Drawable that can draw a flower
 */
class Flower : public Drawable
{
  private:
    Shape* stem; // we need to let stem be a pointer here;
    // as well as pistil and leaf;
    // when the variable become a pointer, we can just use it change object.
    Shape* pistil; // center piece of flower
    Shape* leaf;

    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);
    ~Flower();
    void draw(cs225::PNG* canvas) const;
};
