#include "../blownupprojplane.h"
#include<iostream>

using namespace std;

int main(){
  int number=9;
  cout<<endl<<endl<<"Cremona table for "<<number<<" points"<<endl;
  BlownUpProjPlane surface(number);
  int* curve;
  for(int i=0;i<10;i++){
    curve= surface.nextMinusOneCurve();
    for(int j=0;j<number+1;j++)
      cout<<curve[j]<<" ";

    int selfIntersection=curve[0]*curve[0];
    for(int i=1;i<number+1;i++)
      selfIntersection-=curve[i]*curve[i];
    cout<<" Self intersection: "<<selfIntersection<<endl;
  }
  return 0;
}
