/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using namespace std;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);
  ~BFS();
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  bool getvector(unsigned x, unsigned y); 
  void setvector(unsigned x, unsigned y);
  double gettol();
  PNG * helpptr();
   

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;


private:
  /** @todo [Part 1] */
  /** add private members here*/ 
   
  vector<vector<bool>> markvector;
	PNG thepng;
	Point thestart;
  double thetolerance;
	queue<Point> inqueue;
};
