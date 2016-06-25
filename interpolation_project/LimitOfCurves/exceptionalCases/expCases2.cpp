#include<iostream>

using namespace std;

#define MAXM 300
#define MAXCASES 1000
/* Finds pairs (d,m) satisfying
3d >= 9m +9
19m >= 6d +1
*/

inline long long dim(long long d, long long m){
  return ((d+2)*(d+1) - 10* m* (m+1))/2;
}

inline long long gen(long long d, long long m){
  return ((d-1)*(d-2) - 10* m* (m-1))/2;
}

inline long long k(long long d, long long m){
  return 10*m-3*d;
}

inline long long gap(long long d, long long m, long long M){
  return gen(d,m)- 3*(d-3*M) - gen(d-3*M,0);
}

long long minM(long long d, long long m){
  long long M=m+1;
  while((gap(d,m,M)<=0 || dim(d,m) > dim(d-3*M, 0)) && M<d)
    M++;
  return M;
}


int main(){
  
  cout<<"Computing cases not coveres by conjecture:"<<endl;
  long long d,counter=1;
  long double maxRatio=0;
  for(long long m=19;m<=MAXM && counter<=MAXCASES;m++){
    d=(3*m+3);
    while(19*m>=6*d+1 && counter<=MAXCASES ){
      //if( gap(d,m)>=0){
      // if( dim(d,m)>=0){
      //long long M=minM(d,m);
      //if(d>=3*M ){
      //if(maxRatio<1.0*d/m)
      //  maxRatio=1.0*d/m;
      long long M=m-1;
      do{
	M++;
      }while(d >= 3*M && dim(d,m) <= dim(d-3*M,0));
      M--;
      if(gen(d,m)>=0)
	cout<<"Case "<<counter++<<": d="<<d<<" m="<<m<<" exp-dim:"<<dim(d,m)<<" arith-genus:"<<gen(d,m)
	    <<" k:"<<k(d,m)<<" max-M:"<<M<<endl;
      d++;
    }
  }
  cout<<"First "<<MAXCASES<<" cases up to m="<<MAXM<<endl;
}
