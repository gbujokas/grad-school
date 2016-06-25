#include<iostream>
#define MAXD 1000
#define MAXM 1000
using namespace std;
/*
The basic theorem says that
M>m ( iff 19/6 >= d/m <-> 2k>= m )
or
M=0 ( iff d/m > 10/3 )
or
M=2k+1 (iff 10/3 >= d/m >19/6 ) 
or
empty


*/

int genus(int d, int m){
  return ((d-1)*(d-2) -10*m*(m-1))/2;
}

int dim(int d, int m){
  return (d*d+3*d+2 - 10* m*(m+1))/2;
}

int k(int d, int m){
  return 10*m-3*d;
}

int dimensionBound(int d, int m,  int M, int A){
  return M*(2*(10*m-3*d)+1- M) + 10* A * (2*M - 2*m -1 -A);
}

int genusBound(int d, int m, int M, int A){
  return (M-1)*(M - 2*(10*m-3*d)) + 10* (A-1) * (A - (2*M - 2*m -2));
}

int printValuesOfA( int d, int m, int M, bool print){
  int counter=0;
  if(dim(d,m)>0){
    for(int A=M-m;dimensionBound(d,m,M,A)>=0 ;A++){
      if(genusBound(d,m,M,A)>0){
	counter++;
	if(print)
	  cout<<A<<", ";
      }
    }
  }
  if(dim(d,m)<=0){
    for(int A=M-m; dim(d-3*M, A-(M-m)) > 0; A++){
      if(genusBound(d,m,M,A)>0){
	counter++;
	if(print)
	  cout<<A<<", ";
      }
    }
  }
  return counter;
}


int main(){
  bool positive=false;
  int cases=1;
  if(positive){
    cout<<"Positive dimension:"<<endl;
    for(int d=0;d<MAXD;d++)
      for(int m=0;m<MAXM;m++){
	if(6*d>19*m)
	  continue;
	if(dim(d,m)>0){
	  for(int M=m+1;( d>=3*M && dim(d-3*M,0) >= dim(d,m)); M++){
	    if(printValuesOfA(d,m,M,false)>0){
	      cout<<"Case "<<cases++<<": d:"<<d<<" m:"<<m<<" M:"<<M<<" 2k+1:"<<2*k(d,m)+1<<" exp-Dim:"
		  <<dim(d,m)<<" dimension gap:"<<dim(d-3*M,0)-dim(d,m)<<endl;
	      cout<<"Values of A:";
	      printValuesOfA(d,m,M,true);
	      cout<<endl;
	    }
	  }
	}
      }
  }
  else{
    cout<<"Empty systems:"<<endl;
    for(int d=0;d<MAXD;d++)
      for(int m=0;m<MAXM;m++){
	if(dim(d,m)<=0 && genus(d,m)>=0 ){
	  for(int M=m+1;d>=3*M ; M++){
	    // if(printValuesOfA(d,m,M,false)>0 && 37*d<117*m){
	    if(genus(d-3*M,0)+ 3*(d-3*M)<=genus(d,m)){
	      cout<<"Case "<<cases++<<": d:"<<d<<" m:"<<m<<" M:"<<M<<" 2k+1:"<<2*k(d,m)+1
		  <<" p_a(L):"<<genus(d,m)<<" genus bound:"<<genus(d-3*M,0)+ 3*(d-3*M)<<endl;
	      //cout<<"Values of A:";
	      //  printValuesOfA(d,m,M,true);
	      //cout<<endl;
	      //}
	    }
	  }
	}
      }
  }
  return 0;
}
