#include "blownupprojplane.h"
#include<iostream>

using namespace std;

BlownUpProjPlane::BlownUpProjPlane(int number){
  if(number<3){
    cout<<"ERROR - BLOW UP AT LEAST 3 POINTS"<<endl;
    throw 1;
  }
  numberOfPoints=number;
  table= new int[number+1];
  table[0]=table[number]=table[number-1]=1;
  for(int i=1;i<number-1;i++)
    table[i]=0;
}

int* BlownUpProjPlane::nextMinusOneCurve(){
  int delta= table[0]-table[1]-table[2]-table[3];
  for(int i=0;i<=3;i++)
    table[i]+=delta;

  sort(table+1, table+numberOfPoints+1);
  return table;
}
