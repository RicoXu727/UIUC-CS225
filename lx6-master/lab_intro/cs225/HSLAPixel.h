/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once 
//This directive will instruct the compiler that 
//the header file should only be compiled once
#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel {
        public: 
            double h, s, l, a;
            HSLAPixel();
            HSLAPixel(double hue, double saturation, double luminance);
            HSLAPixel(double hue, double saturation, double luminance, double alpha);
    };
}

