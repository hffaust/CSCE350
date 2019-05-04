#ifndef PROGRAM2_H
#define PROGRAM2_H

#include "metrics.h"
#include <algorithm>


template <typename T>
std::pair<Point<T>, Point<T> > closestPair( vector<Point<T> > v){

  return std::pair<Point<T>, Point<T> > (v[0],v[1]);
 
}

#endif //PROGRAM2_H
