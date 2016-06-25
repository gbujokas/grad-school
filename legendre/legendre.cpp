#include "legendre.h"
#include "factor.h"
#include <list>
#include "primepower.h"

int eps(int p){
  p=(p-1)/2;
  return (p%2?-1:1);
}

int recLegendre(int q, int p){
  if(q==2){
    int e=(p*p-1)/8;
    return (e%2?-1:1);
  }
  int e=(p-1)*(q-1);
  e/=4;
  int leg=(e%2?-1:1);
  return leg*legendre(p,q);
}


int legendre(int a, int p){
  a%=p;
  if(a==0)
    return 0;
  
  list<PrimePower> factorization =factor(a);
  int leg=1;
  if(a<0)
    leg=eps(p);
  PrimePower primePower(0,0);
  for(list<PrimePower>::iterator i = factorization.begin();
      i!= factorization.end();
      i++){
    primePower=*i;
    if(primePower.exp()%2==1)
      leg*=recLegendre(primePower.prime(),p);
  }
  return leg;
}

