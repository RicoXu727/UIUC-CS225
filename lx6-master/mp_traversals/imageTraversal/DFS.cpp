#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  thetolerance = tolerance; 
	thepng = png; 
	thestart = start;
	instack.push(start);
  
  vector<bool> height(thepng.height());
  markvector.resize(thepng.width(), height);
  for (unsigned i = 0; i < markvector.size(); i++) {
    for (unsigned j = 0; j < markvector[i].size(); j++) {
      markvector[i][j] = false;
    }
  }
  markvector[start.x][start.y] = true;
}

DFS::~DFS() {
}

bool DFS::getvector(unsigned x, unsigned y) {
    return markvector[x][y];
}

void DFS::setvector(unsigned x, unsigned y) {
    markvector[x][y] = true;
}

double DFS::gettol() {
  return thetolerance;
}

PNG * DFS::helpptr() {
    return &thepng;
}




/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal * dfsptr = new DFS(thepng, thestart, thetolerance);
  ImageTraversal::Iterator theit(*dfsptr, thestart);
  return theit; 
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  instack.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  //return Point(0, 0);
  Point tmp = instack.top();
  instack.pop();
  return tmp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  //return Point(0, 0);
  return instack.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return instack.empty();
}


