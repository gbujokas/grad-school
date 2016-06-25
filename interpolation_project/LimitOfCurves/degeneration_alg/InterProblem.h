#ifndef INC_INTERPROBLEM_H
#define INC_INTERPROBLEM_H
#include "AlignIdeal.h"
#include "AlignSing.h"
#include "exceptions.h"
#include<string>

class InterProblem{
  AlignIdeal ideal;
  int* mult;
  int begin, end;

  bool isValid() const;
 public:
  InterProblem(int, int, int*); //degree, number of points, multiplicities
  ~InterProblem();
  bool solve(bool=false); /*returns true if non special
		  false if found double line
		  potentially throws a number of exceptions, all listed on exceptions.h
		  i expected those to not happen, though */
  std::string toString() const;
};

#endif /*INC_INTERPROBLEM */
