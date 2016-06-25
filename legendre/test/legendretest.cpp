#include "../legendre.h"
#include <iostream>

using namespace std;

int a[]={-12, 21, 32, 5, 2 };
int p[]={17, 13, 7, 19, 3};
int leg[]={-1, -1, 1, 1, -1};
int numTest=5;

int main(){

  cout<<"LEGENDRETEST ";

  try{
    for(int i=0; i<numTest;i++){
      if(legendre(a[i],p[i])!=leg[i]){
	cout<<"FAILED"<<endl;
	return 0;
      }
    }
    cout<<"PASSED"<<endl;
  }catch(exception& e){
    cout<<"FAILED"<<endl;
  }
  return 0;
}

