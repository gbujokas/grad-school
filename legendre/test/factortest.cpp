#include <iostream>
#include "../factor.h"
#include "../primepower.h"
#include <list>

using namespace std;

int n[]={12,-63,91, 24};
int primes[]={2,3,3,7,7,13,2,3};
int exp[]={2,1,2,1,1,1,3,1};


int main(){
  try{
    cout<<"TESTFACTOR: ";
    int index=0;
    PrimePower primePower(0,0);
    for(int i=0;i<4;i++){
      list<PrimePower> fac= factor(n[i]);
      for(list<PrimePower>::iterator i= fac.begin();
	  i!=fac.end();
	  i++){
	primePower=*i;
	if(primePower.prime()!= primes[index] ||
	   primePower.exp()!=exp[index]){
	  cout<<"FAILED"<<endl;
	  return 0;
	}
	index++;
      }
    }

    cout<<"PASSED"<<endl;
  }catch(exception& e){
    cout<<"FAILED"<<endl;
  }
  return 0;
}
