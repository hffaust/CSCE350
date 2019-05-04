#ifndef METRICS_H
#define METRICS_H

#include <cmath>
#include <vector>

using std::vector;

/*********************
* DO NOT MODIFY THIS FILE, it will be replaced
**********************/

template <class T>
class Point{
public:
  T x;
  T y;
  
  Point(T x,T y):x(x),y(y)
  {}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& pt){
  os<<'('<<pt.x<<','<<pt.y<<')';
  return os;
} 

template <typename T>
bool epsZero(T val, T eps){
  return(std::abs(val)<eps);
}

//OpenCV style points 
//typedef Point<double> Point2d;
//typedef Point<float> Point2f;

/****************
* Euclidean distance -- you MUST call this function to measure distance
*****************/
template <typename T>
T dist(Point<T> a,Point<T> b){
  T diffx = a.x-b.x;
  T diffy = a.y-b.y;
  return std::sqrt( diffx*diffx + diffy*diffy);
}

template <typename T>
std::pair<Point<T> ,Point<T> > closestPairBF( vector<Point<T> > pts){
  T min = dist(pts[0],pts[1]);
  size_t min1 = 0;
  size_t min2 = 1;  

  for(size_t i = 0; i< pts.size()-1; ++i){
    for(size_t j = i+1; j <pts.size(); ++j){
      T d = dist(pts[i],pts[j]);
      if (d<min) {
        min = d;
        min1 = i;
        min2 = j;
      }
    }
  }

  return std::pair<Point<T>, Point<T> > (pts[min1],pts[min2]);
}

#endif //METRICS_H
