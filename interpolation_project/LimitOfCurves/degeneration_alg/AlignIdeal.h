#ifndef INC_ALIGNIDEAL_H
#define INC_ALIGNIDEAL_H

#include "exceptions.h"
#include "AlignSing.h"
#include <string>

class AlignIdeal{
  int maximumSing, numSing, degree;
  AlignSing** singularity;
  AlignSing total; 
  bool badtriple(int) const; 
  void splitBaseLine();
 public:
  AlignIdeal(int,int); //degree, number of sing
  AlignIdeal(const AlignIdeal&);
  ~AlignIdeal();
  AlignIdeal& operator = (const AlignIdeal&);
  //bool operator == (const AlignIdeal&) const;
  int getDegree() const;
  int multiplicity() const;
  void splitVerticalLine(); //throw splitting empty sing
  bool valid() const;
  //test if m(sing[i])<=m(sing[j]) for i<=j
  std::string toString(bool=false) const;
  void degenerate(int); //degenerate m onto the line. 
  //throws AlignIdealFULL, BadTriple 
  AlignSing totalSing() const;
};

#endif /*INC_ALIGNIDEAL_H */
