#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(double hue, double saturation, double luminance) {
  hue = 100;
  saturation = 0.7;
  luminance = 0.7;
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(100, 0.7, 0.7);
  hue += 10;
  saturation -= 0.1;
  luminance -= 0.1;
  if (hue > 315) {
    hue = hue - 270; 
  } 
  if (saturation < 0.3) {
    saturation = 0.7;
  }
  if (luminance < 0.3) {
    luminance = 0.7;
  }
  return pixel;
}
