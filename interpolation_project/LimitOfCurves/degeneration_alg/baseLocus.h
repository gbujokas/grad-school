#ifndef BASELOCUS_H
#define BASELOCUS_H

/* Let S be the plane blown up at n points.
   Assuming that the system L=dH-mE is non-special (which is true for n>8, by HH),
   a curve D is in the base locus only if
     -expected dimension of D is at least 1
     -H^0(D, L)=0  => D(dH-mE)< g(D)
   We find possible classes of curves D satisfying both conditions.
   The technique is to reduce it to an integer linear program.

*/

class HomInterProblem{
  int d,m,n;
 public:
  HomInterProblem(int, int, int); //d,m,n
  bool findBaseLocus(); //returns false if there is no base locus
};


#endif /*BASELOCUS_H */
