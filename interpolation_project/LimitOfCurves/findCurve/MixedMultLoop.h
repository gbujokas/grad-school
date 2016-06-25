#ifndef MIXEDMULTLOOP_H
#define MIXEDMULTLOOP_H

#include<string>

const int NUM_PTS=10;
const int MAX_MULT=30;
class MixedMultLoop{
 private:
  int a[MAX_MULT+1];
  int counter;
  int cond[MAX_MULT+1];
  int delt[MAX_MULT+1];
  bool valid();
 public:
  MixedMultLoop();
  void next();
  bool over();
  int delta();
  int conditions();
  std::string toString();
  int min();
  int sum();
  int* multiplicities();

};


#endif
