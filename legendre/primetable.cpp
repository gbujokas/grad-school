#include "primetable.h"
#define MAXINT 200


int PrimeTable::getPrime(int index){
  if(index>=maxIndex)
    return -1;
  return primeList[index];
}

PrimeTable::PrimeTable(){
  bool * euclid= new bool[MAXINT+5];
  for(int i=1;i<MAXINT;i++)
    euclid[i]=true;

  euclid[1]=false;
  for(int i=0;i<MAXINT;i++){
    if(!euclid[i])
      continue;
    for(int k=2;k*i<MAXINT;k++)
      euclid[k*i]=false;
  }

  primeList=new int[MAXINT+5];
  maxIndex=0;
  for(int i=1;i<MAXINT;i++)
    if(euclid[i]){
      primeList[maxIndex++]=i;
    }
  delete euclid;
}


PrimeTable::~PrimeTable(){
  delete primeList;  
}
