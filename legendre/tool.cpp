#include "hilbert.h"
#include <iostream>

using namespace std;

int main(){
  cout<<"Encontrando valores de A e B tal que x^2=ay^2+bz^2 tem solucao inteira"<<endl;
  int M=10;
  for(int a=-M;a<=M;a++)
    for(int b=-M;b<=M;b++){
      if(a!=0 && b!=0){
	if(hasIntegerSolution(a,b)){
	  cout<<a<<" "<<b<<endl;
	}
      }
    }
    
  return 0;
}
