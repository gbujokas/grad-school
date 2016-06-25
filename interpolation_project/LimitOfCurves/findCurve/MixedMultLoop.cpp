#include "MixedMultLoop.h"

#include<string>
#include<sstream>

MixedMultLoop::MixedMultLoop(){
  counter=0;
  for(int i=0;i<MAX_MULT+1;i++){
    a[i]=0;
    cond[i]=i*(i+1)/2;
    delt[i]=i*(i-1)/2;
  }
  next();
}

void MixedMultLoop::next(){
  if(over())
    return;
  counter++;
  do{
    for(int m=1;m++;m<=MAX_MULT){
      a[m]++;
      if(a[m]<=NUM_PTS)
	break;
      else{
	a[m]=0;
      }
    }
  }while(!valid());
}

bool MixedMultLoop::over(){
  return a[MAX_MULT]==NUM_PTS;
}

bool MixedMultLoop::valid(){
  int sum=0;
  for(int i=1;i<=MAX_MULT;i++)
    sum+=a[i];
  return sum==NUM_PTS;
}

int MixedMultLoop::delta(){
  int delta=0;
  for(int i=1;i<=MAX_MULT;i++)
    delta+=a[i]*delt[i];
  return delta;
}

int MixedMultLoop::conditions(){
  int conditions=0;
  for(int i=1;i<=MAX_MULT;i++)
    conditions+=a[i]*cond[i];
  return conditions;
}

std::string MixedMultLoop::toString(){
  std::stringstream sstream;
  sstream<<"Multiplicities: ";
  for(int i=1;i<=MAX_MULT;i++)
    if(a[i]!=0)
      sstream<<i<<":"<<a[i]<<" ";
  return sstream.str();

}
int MixedMultLoop::min(){
  int min=1;
  for(;min<=MAX_MULT&&a[min]==0; min++);
  return min;
}

int MixedMultLoop::sum(){
  int sum=0;
  for(int m=0;m<=MAX_MULT; m++)
    sum+=a[m]*m;
  return sum;
}

int* MixedMultLoop::multiplicities(){
  int* mult=new int[10];
  int counter=0;
  for(int i=0;i<=MAX_MULT;i++){
    int k=a[i];
    while((k--)>0)
      mult[counter++]=i;
  }
  return mult;
}
