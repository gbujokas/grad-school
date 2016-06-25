#include "hilbert.h"
#include "primetable.h"
#include "legendre.h"
#include <iostream>

using namespace std;

int epsi(int u){
  return (u-1)/2;
}
int omega(int u){
  return (u*u-1)/8;
}

int hilbert(int a, int b, int p){
  //cout<<"hilbert:"<<a<<" "<<b<<" "<<p<<endl;
  if(p==0){
    return a>0 || b>0;
  }
 int alpha=0, beta=0;
  while(a%p==0){
    a/=p;
    alpha++;
  }
  while(b%p==0){
    b/=p;
    beta++;
  }
 if(p==2){
   int e= epsi(a)*epsi(b) +alpha*omega(b)+beta*omega(a);
   return (e%2? -1 : 1);
  }
  int answer=1;
  if(alpha%2)
    answer=legendre(b,p);
  if(beta%2)
    answer=legendre(a,p);
  if(alpha%2 && beta%2)
    answer=legendre(-a*b, p);
  return answer;
}

bool hasIntegerSolution(int a, int b){

  // cout<<"Debug: intSol:"<<a<<" "<<b<<" ";
  PrimeTable& table= PrimeTable::instance();
  int p;
  for(int i=0;;i++){
    p=table.getPrime(i);

    // cout<<p<<" ";
    
    if(p==-1)
      break;
    if(hilbert(a,b,p)==-1){
      //cout<<endl;
      return false;
    }
  }
  //  cout<<endl;
  return hilbert(a,b,0)==1;
}
