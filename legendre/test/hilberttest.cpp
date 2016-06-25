#include "../hilbert.h"
#include <iostream>

using namespace std;

int a[]={1,-1};
int b[]={1,-7};
int p[]={7,7};
int hil[]={1,-1};
int numTest=2;

int main(){
  cout<<"HILBERTTEST: ";
  for(int index=0;index<numTest;index++){
    cout<<hilbert(a[index],b[index], p[index])<<endl;
    //cout<<hasIntegerSolution(a[index],b[index])<<endl;
  }
  cout<<"FAILED"<<endl;


}
