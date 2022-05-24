/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim < 0 || curDim >= Dim) {
      return false;
    }
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] > second[curDim]) {
      return false;
    } else {
      return first < second;
    }
    
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    unsigned currentDistance = 0;
    unsigned potentialDistance = 0;
    for (int i = 0; i < Dim; i++) {
      currentDistance += ((target[i] - currentBest[i]) * (target[i] - currentBest[i]));
      potentialDistance += ((target[i] - potential[i]) * (target[i] - potential[i]));
    }
    if (currentDistance < potentialDistance) {
      return false;
    } else if (currentDistance > potentialDistance) {
      return true;
    } else {
      return potential < currentBest;
    }
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.size() == 0) {
      root = nullptr;
      size = 0;
    }
    vector<Point<Dim>> copyPoints = newPoints;
    root = buildTree(copyPoints, 0, copyPoints.size() - 1, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& copyPoints, unsigned left, unsigned right, int d) {
  if (left < 0 || left >= copyPoints.size()) {
    return NULL;
  }
  if (right < 0 || right >= copyPoints.size()) {
    return NULL;
  }
  if (left > right) {
    return NULL;
  }
  int median = floor((left + right) / 2);
  KDTreeNode* root = new KDTreeNode(quick_select(copyPoints, left, right, median, d % Dim));
  size++;
  d++;
  root->left = buildTree(copyPoints, left, median - 1, d);
  root->right = buildTree(copyPoints, median + 1, right, d);
  return root;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy_(root, other.root);
  size = other.size;
}

template <int Dim>
int KDTree<Dim>::quick_partition(vector<Point<Dim>>& list, int left, int right, int pivotIndex, int d) {
  Point<Dim> pivotValue = list[pivotIndex];
  swap(list[pivotIndex], list[right]);
  int storeIndex = left;
  for (int i = left; i <= right - 1; i++) {
    if (smallerDimVal(list[i], pivotValue, d)) {
      swap(list[storeIndex], list[i]);
      storeIndex++;
    }
  }
  swap(list[right], list[storeIndex]);
  return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quick_select(vector<Point<Dim>>& list, int left, int right, int k, int d) {
  if (left == right) {
    return list[left];
  }
  int pivotIndex = quick_partition(list, left, right, floor((left + right)/2), d);
  if (k == pivotIndex) {
    return list[k];
  } else if (k < pivotIndex) {
    return quick_select(list, left, pivotIndex - 1, k, d);
  } else {
    return quick_select(list, pivotIndex + 1, right, k, d);
  }
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != rhs) {
    destroy_(root);
    copy_(root, rhs.root);
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  destroy_(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> output = findhelper(root, query, 0);
    return output;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findhelper(KDTreeNode * root, const Point<Dim>& query, int d) const {
  if (root == NULL) {
    return NULL;
  }
  if (root->left == NULL && root->right == NULL) {
    return root->point;
  }
  Point<Dim> current = root->point;
  KDTreeNode * other = nullptr;
  if (smallerDimVal(query, root->point, d)) {
    if (root->left != NULL) {
      current = findhelper(root->left, query, (d+1)%Dim);
    } else {
      current = findhelper(root->right, query, (d+1)%Dim);
    }
    if (root->right != NULL) {
      other = root->right;
    }
  } else {
    if (root->right != NULL) {
      current = findhelper(root->right, query, (d+1)%Dim);
    } else {
      current = findhelper(root->left, query, (d+1)%Dim);
    }
    if (root->left != NULL) {
      other = root->left;
    }
  }

  if (shouldReplace(query, current, root->point)) {
    current = root->point;
  }

  double radius = 0.0;
  for (int i = 0; i < Dim; i++) {
    radius += (current[i] - query[i]) * (current[i] - query[i]);
  }
  double distance = (root->point[d] - query[d]) * (root->point[d] - query[d]);
  if (distance <= radius) {
    if (other != NULL) {
      Point<Dim> otherPoints = findhelper(other, query, (d+1)%Dim);
      if (shouldReplace(query, current, otherPoints)) {
        current = otherPoints;
      }
    }
  } 
  return current;
}


template <int Dim>
void KDTree<Dim>::destroy_(KDTreeNode * root) {
  if (root == NULL) {
    return;
  }
  if (root->left != NULL) {
    destroy_(root->left);
  }
  if (root->right != NULL) {
    destroy_(root->right);
  }
  delete root;
  root = NULL;
}

template <int Dim>
void KDTree<Dim>::copy_(KDTreeNode * root, KDTreeNode * other) {
  root = new KDTreeNode(other->point);
  copy_(root->left, other->left);
  copy_(root->right, other->right);
}