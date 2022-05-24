#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  PNG inputimage = PNG();
  inputimage.readFromFile(inputFile);
  PNG outputimage = PNG(inputimage.width(), inputimage.height());
  for (unsigned int x = 0; x < inputimage.width(); x++) {
    for (unsigned int y = 0; y < inputimage.height(); y++) {
      HSLAPixel & pixel = inputimage.getPixel(x, y);
      // int midWidth = inputimage.width() / 2;
      // int midHeight = inputimage.height() / 2;
      int m = inputimage.width() - x - 1; // midwidth + midwidth - x
      int n = inputimage.height() - y - 1;
      HSLAPixel & outpixel = outputimage.getPixel(m,n);
      outpixel = pixel;
    }
  }
  outputimage.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  
  for (unsigned int x = 0; x < 800; x++) {
    for (unsigned int y = 0; y < 800; y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      if (x < 200 && y < 200) {
        pixel.h = 45;
        pixel.a = 0.1;
        pixel.s = 0.2;
        pixel.l = 0.8;
      } else if (x < 400 && y < 400) {
        pixel.h = 90;
        pixel.a = 0.2;
        pixel.s = 0.4;
        pixel.l = 0.6;
      } else if (x < 600 && y < 600) {
        pixel.h = 135;
        pixel.a = 0.3;
        pixel.s = 0.6;
        pixel.l = 0.4;
      } else {
        pixel.h = 280;
        pixel.a = 0.4;
        pixel.s = 0.8;
        pixel.l = 0.2;
      }
    }
  }
  png.writeToFile("art.png");
  return png;
}
