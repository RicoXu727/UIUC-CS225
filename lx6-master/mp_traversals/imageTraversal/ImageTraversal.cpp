#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {        
  /** @todo [Part 1] */
  traptr = nullptr;                    
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traptr, Point startpoint) {
  /** @todo [Part 1] */
  this->traptr = &traptr;                
  this->startpoint = startpoint;
  this->currentpoint = traptr.peek();               
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //return *this;
  Point currpoint = traptr->pop();
  traptr->setvector(currpoint.x, currpoint.y);
  	
  Point rightpoint(currpoint.x + 1, currpoint.y);
  Point belowpoint(currpoint.x, currpoint.y + 1);
  Point leftpoint(currpoint.x - 1, currpoint.y);
  Point abovepoint(currpoint.x, currpoint.y - 1);
  HSLAPixel & start = traptr->helpptr()->getPixel(startpoint.x, startpoint.y);
  
  double pngwidth = traptr->helpptr()->width();
  double pngheight = traptr->helpptr()->height();
  if (rightpoint.x < pngwidth) {
    HSLAPixel & pixel = traptr->helpptr()->getPixel(rightpoint.x, rightpoint.y);
    if (calculateDelta(start, pixel) < traptr->gettol()) {
      traptr->add(rightpoint);
    }
  }

  if (belowpoint.y < pngheight) {
    HSLAPixel & pixel = traptr->helpptr()->getPixel(belowpoint.x, belowpoint.y);
    if (calculateDelta(start, pixel) < traptr->gettol()) {
      traptr->add(belowpoint);
    }
  }
  
  if (leftpoint.x < pngwidth) {
    HSLAPixel & pixel = traptr->helpptr()->getPixel(leftpoint.x, leftpoint.y);
    if (calculateDelta(start, pixel) < traptr->gettol()) {
      traptr->add(leftpoint);
    }
  }


  if (abovepoint.y < pngheight) {
    HSLAPixel & pixel = traptr->helpptr()->getPixel(abovepoint.x, abovepoint.y);
    if (calculateDelta(start, pixel) < traptr->gettol()) {
      traptr->add(abovepoint);
    }
  } 
  

  while (traptr->empty() == false && (traptr->getvector(traptr->peek().x, traptr->peek().y)) == true) {
    traptr->pop();
  }

  if (traptr->empty() == true) {
    return *this;
  }

  currentpoint = traptr->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currentpoint;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //return !(mark && other.mark);
  // if (mark == true && other.mark == true) {
  //   return false;
  // } else if (mark != other.mark) {
  //   return true;
  // } else {
  //   return true;
  // }
  // if (this->currentpoint == other.currentpoint) {
  //   return false;
  // } else {
  //   return true;
  // }
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (traptr == NULL) { thisEmpty = true; }
  if (other.traptr == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traptr->empty(); }
  if (!otherEmpty) { otherEmpty = other.traptr->empty(); }

  if (thisEmpty && otherEmpty) return false; 
  else if ((!thisEmpty)&&(!otherEmpty)) return (traptr != other.traptr); 
  else return true; 
}

