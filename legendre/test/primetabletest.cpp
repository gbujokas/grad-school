#include <iostream>
#include "../primetable.h"

using namespace std;

int primes[]={2,3,5,7,11,13,17};
int length=7;

int main(){
  cout<<"TEST PRIMETABLE: ";
  try{
    PrimeTable& table= PrimeTable::instance();
    for(int i=0;i<length;i++){
      //cout<<table.getPrime(i)<<" ";
      if(table.getPrime(i)!=primes[i]){
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
