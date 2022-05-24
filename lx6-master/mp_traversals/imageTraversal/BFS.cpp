#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  thetolerance = tolerance; 
  thepng = png; 
  thestart = start;
  inqueue.push(start);

  vector<bool> height(thepng.height());
  markvector.resize(thepng.width(),height);
  for (unsigned i = 0; i < markvector.size(); i++) {
    for (unsigned j = 0; j < markvector[i].size(); j++) {
        markvector[i][j] = false;
    }
  }
  markvector[start.x][start.y] = true;
}
BFS::~BFS() {

}

bool BFS::getvector(unsigned x, unsigned y) {
    return markvector[x][y];
}

void BFS::setvector(unsigned x, unsigned y) {
    markvector[x][y] = true;
}

double BFS::gettol() {
    return thetolerance;
}

PNG * BFS::helpptr() {
    return &thepng;
}


/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal * bfsptr = new BFS(thepng, thestart, thetolerance);
  ImageTraversal::Iterator theit(*bfsptr, thestart);
  return theit; 
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  inqueue.push(point); // Inserts a new element at the end of the queue;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  //return Point(0, 0);
  Point tmp = inqueue.front();
  inqueue.pop();
  return tmp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return inqueue.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return inqueue.empty();
}
