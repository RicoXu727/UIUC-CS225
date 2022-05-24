#include <iostream>
#include <math.h>
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cassert>
#include <algorithm>
#include <functional>

//#include "lodepng/lodepng.h"
#include "cs225/PNG.h"
#include "Image.h"
#include "cs225/RGB_HSL.h"
#include "cs225/HSLAPixel.h"


    void Image::darken() {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.l - 0.1 >= 0) {
                    pixel.l -= 0.1;
                } else {
                    pixel.l = 0;
                }
            }
        }
    }

    void Image::darken(double amount) {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.l - amount >= 0) {
                    pixel.l -= amount;
                } else {
                    pixel.l = 0;
                }
            }
        }
    }

    void Image::desaturate() {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.s >= 0.1) {
                    pixel.s -= 0.1;
                } else {
                    pixel.s = 0;
                }
            }
        }
    }

    void Image::desaturate(double amount) {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.s >= amount) {
                    pixel.s -= amount;
                } else {
                    pixel.s = 0;
                }
            }
        }
    } 

    void Image::grayscale() {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                pixel.s = 0;         
            }
        }
    }

    void Image::illinify() {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.h >= 113.5 && pixel.h <= 293.5) {
                    pixel.h = 216;
                } else {
                    pixel.h = 11;
                }
            }
        }
    }

    void Image::lighten() {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.l + 0.1 <= 1) {
                    pixel.l += 0.1;
                } else {
                    pixel.l = 1;
                }
            }
        }
    }

    void Image::lighten(double amount) {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.l + amount <= 1) {
                    pixel.l += amount;
                } else {
                    pixel.l = 1;
                }
            }
        }
    }

    void Image::rotateColor(double degrees) {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (degrees > 0) {
                    if ((pixel.h + degrees) < 360) {
                        pixel.h += degrees;
                    } else {
                        pixel.h += degrees - 360;
                    }
                } else {
                    if ((pixel.h + degrees) < 0) {
                        pixel.h += degrees + 360;
                    } else {
                        pixel.h += degrees;
                    }
                }
            }
        }
    }

    void Image::saturate() {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.s + 0.1 <= 1) {
                    pixel.s += 0.1;
                } else {
                    pixel.s = 1;
                }
            }
        }
    }

    void Image::saturate(double amount) {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.s + amount <= 1) {
                    pixel.s += amount;
                } else {
                    pixel.s = 1;
                }
            }
        }
    }



    void Image::scale(double factor) {
        // interpolation and pooling
        // Image newImage(floor(this->width() * factor), floor(this->height() * factor));
        // for (unsigned int x = 0; x < this->width() * factor; x++) {
        //     for (unsigned int y = 0; y < this->height() * factor; y++) {
        //         cs225::HSLAPixel & newPixel = newImage.getPixel(x,y);
        //         cs225::HSLAPixel & pixel = this->getPixel(floor(x / factor),floor(y / factor));
        //         newPixel = pixel;
        //     }
        // } 

        // unsigned int newWidth = width() * factor;
        // unsigned int newHeight = height() * factor;

        // Image * copyImage = new Image();
        // *copyImage = *this;
        // resize(newWidth, newHeight);

        // for (unsigned int x = 0; x < newWidth; x++) {
        //     for (unsigned int y = 0; y < newHeight; y++) {
        //         cs225::HSLAPixel & newPixel = getPixel(x,y);
        //         cs225::HSLAPixel & copyPixel = copyImage->getPixel(x / factor, y / factor);
        //         newPixel = copyPixel;
        //     }
        // }

        // delete copyImage;
        
        int newWidth = floor(this->width() * factor);
        int newHeight = floor(this->height() * factor);
        Image origin(*this);
        this->resize(newWidth, newHeight);
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & newPixel = this->getPixel(x,y);
                cs225::HSLAPixel & pixel = origin.getPixel(floor(x / factor),floor(y / factor)); 
                newPixel = pixel;
            }
        }

    }

    void Image::scale(unsigned w,unsigned h) {
        // do not needed to initialize a new object;
        // Image adimage;
        // adimage.resize(w, h);
        
        // if ((w / this->width()) < (h / this->height())) {
        //     adimage = w / this->width();
        // } else {
        //     adimage = this->height();
        // }

        // Image * copyImage = new Image();
        // *copyImage = *this;
        // resize(w, h);

        // double wFactor = w / width();
        // double hFactor = h / height();

        // for (unsigned int x = 0; x < w; x++) {
        //     for (unsigned int y = 0; y < h; y++) {
        //         cs225::HSLAPixel & newPixel = getPixel(x, y);
        //         cs225::HSLAPixel & copyPixel = copyImage->getPixel(x / wFactor, y / hFactor);
        //         newPixel = copyPixel;
        //     }
        // }
        // delete copyImage;

        double adimage;
        double w_fact = (double) w / (double) width();
        double h_fact = (double) h / (double) height();
        if (w_fact < h_fact) {
            adimage = w_fact;
        } else {
            adimage = h_fact;
        }
        this->scale(adimage);

    }


