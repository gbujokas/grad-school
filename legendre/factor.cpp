#include "factor.h"
#include "primetable.h"
#include "primepower.h"
#include <list>

//#include <iostream>
//using namespace std;

list<PrimePower> factor(int n){

  // cout<<"factor "<<n<<endl;

  list<PrimePower> list;
  PrimeTable& table= PrimeTable::instance();
  int e=0, p;
  for(int i=0; n!=1 && n!= -1; i++){
    p=table.getPrime(i);
    if(p==-1)
      throw 0;
    e=0;
    while(n%p==0){
      e++;
      n/=p;
    }
    //cout<<p<<" "<<e<<" "<<n<<endl;
    if(e!=0)
      list.push_back(PrimePower(table.getPrime(i),e));
  }
  return list;
}
