#include <iostream>
#include <string>
#include <vector>

#include "metrics.h"
#include "program2.h"
using std::vector;


#include "gtest/gtest.h"


using namespace std;
using std::string;


template <typename T>
vector<Point<T> > square8(){
  vector<Point<T> > v;

  Point<T> pt0(0.0,0.0);
  Point<T> pt1(0.0,1.0);
  Point<T> pt2(0.0,2.0);
  Point<T> pt3(1.0,2.0);
  Point<T> pt4(2.0,2.0);
  Point<T> pt5(2.0,1.0);
  Point<T> pt6(2.0,0.0);
  Point<T> pt7(1.0,0.0);

  v.push_back(pt0);
  v.push_back(pt1);
  v.push_back(pt2);
  v.push_back(pt3);
  v.push_back(pt4);
  v.push_back(pt5);
  v.push_back(pt6);
  v.push_back(pt7);

  return v;
}



TEST(square8, URdouble){
  vector<Point<double> > v = square8<double> ();
  v.push_back(Point<double>(2.1,2.1));
  std::pair<Point<double> ,Point<double> > cp = closestPairBF(v);
  double d = dist(cp.first,cp.second);
  std::pair<Point<double> ,Point<double> > cp2 = closestPair(v);
  double d2 =  dist(cp2.first,cp2.second);
  stringstream ss;
  ss<<"Pairs found: \nb.f. pair = ("<<cp.first<<","<<cp.second
    <<") \ndivide and conquer pair = ("<<cp2.first<<","<<cp2.second<<")\n";
  ASSERT_TRUE(epsZero(d-d2,1e-6) ) << ss.str();
}

TEST(square8, LLdouble){
  vector<Point<double> > v = square8<double> ();
  v.push_back(Point<double>(0.1,-0.1));
  std::pair<Point<double> ,Point<double> > cp = closestPairBF(v);
  double d = dist(cp.first,cp.second);
  std::pair<Point<double> ,Point<double> > cp2 = closestPair(v);
  double d2 =  dist(cp2.first,cp2.second);
  stringstream ss;
  ss<<"Pairs found: \nb.f. pair = ("<<cp.first<<","<<cp.second
    <<") \ndivide and conquer pair = ("<<cp2.first<<","<<cp2.second<<")\n";
  ASSERT_TRUE(epsZero(d-d2,1e-6) ) << ss.str();
}

TEST(square8, URfloat){
  vector<Point<float> > v = square8<float> ();
  v.push_back(Point<float>(2.1,2.1));
  std::pair<Point<float> ,Point<float> > cp = closestPairBF(v);
  float d = dist(cp.first,cp.second);
  std::pair<Point<float> ,Point<float> > cp2 = closestPair(v);
  float d2 =  dist(cp2.first,cp2.second);
  stringstream ss;
  ss<<"Pairs found: \nb.f. pair = ("<<cp.first<<","<<cp.second
    <<") \ndivide and conquer pair = ("<<cp2.first<<","<<cp2.second<<")\n";
  ASSERT_TRUE(epsZero(d-d2,float(1e-6)) ) << ss.str();
}

TEST(square8, LLfloat){
  vector<Point<float> > v = square8<float> ();
  v.push_back(Point<float>(0.1,-0.1));
  std::pair<Point<float> ,Point<float> > cp = closestPairBF(v);
  float d = dist(cp.first,cp.second);
  std::pair<Point<float> ,Point<float> > cp2 = closestPair(v);
  float d2 =  dist(cp2.first,cp2.second);
  stringstream ss;
  ss<<"Pairs found: \nb.f. pair = ("<<cp.first<<","<<cp.second
    <<") \ndivide and conquer pair = ("<<cp2.first<<","<<cp2.second<<")\n";
  ASSERT_TRUE(epsZero(d-d2,float(1e-6)) ) << ss.str();
}


template<typename T>
vector<Point<T> > randomPoints(unsigned n){

  double maxV =10.0;
  double minV =-10.0;
  double diff = maxV-minV;
  
  vector<Point<T> > pts;
  for(unsigned i = 0;i<n;++i){
    T rand_X = T(diff*(double(rand())/RAND_MAX)+minV);  
    T rand_Y = T(diff*(double(rand())/RAND_MAX)+minV);
    pts.push_back(Point<T>(rand_X,rand_Y));
//    std::cerr<<"rand_X = "<<rand_X<<"rand_Y = " <<rand_Y<<std::endl;

  }

  return pts;
}

int n = 4000;


TEST(randomPoints,randNtwiceBF){
  vector<Point<double> > v = randomPoints<double>(n);
  std::pair<Point<double> ,Point<double> > cp = closestPairBF(v);
  double d = dist(cp.first,cp.second);
  std::pair<Point<double> ,Point<double> > cp2 = closestPairBF(v);
  double d2 =  dist(cp2.first,cp2.second);
  stringstream ss;
  ss<<"Pairs found: \nb.f. pair = ("<<cp.first<<","<<cp.second
    <<") \ndivide and conquer pair = ("<<cp2.first<<","<<cp2.second<<")\n";
  ASSERT_TRUE(epsZero(d-d2,double(1e-3)) ) << ss.str();
}

TEST(randomPoints,randN){
  vector<Point<double> > v = randomPoints<double>(n);
  std::pair<Point<double> ,Point<double> > cp = closestPairBF(v);
  double d = dist(cp.first,cp.second);
  std::pair<Point<double> ,Point<double> > cp2 = closestPair(v);
  double d2 =  dist(cp2.first,cp2.second);
  stringstream ss;
  ss<<"Pairs found: \nb.f. pair = ("<<cp.first<<","<<cp.second
    <<") \ndivide and conquer pair = ("<<cp2.first<<","<<cp2.second<<")\n";
  ASSERT_TRUE(epsZero(d-d2,double(1e-3)) ) << ss.str();
}


