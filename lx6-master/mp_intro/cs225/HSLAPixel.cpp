/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 */

#include "HSLAPixel.h"

namespace cs225 {
        cs225::HSLAPixel::HSLAPixel() {
            a = 1;
            l = 1;
        }
        cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) {
            a = 1;
            h = hue;
            s = saturation;
            l = luminance;
        }
        cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) {
            h = hue;
            s = saturation;
            l = luminance;
            a = alpha;
        }
}
