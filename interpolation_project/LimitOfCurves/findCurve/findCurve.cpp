#include<iostream>
#include "MixedMultLoop.h"
using namespace std;

inline int genus(int d, int m){
  return ((d-1)*(d-2) - 10*m*(m-1))/2;
}

inline int genus(int d, MixedMultLoop& mult){
  return (d-1)*(d-2)/2 - mult.delta();
}

inline int dimension(int d, int m){
  return ((d+2)*(d+1) - 10* (m+1)*m)/2;
}

inline int dimension(int d, MixedMultLoop& mult){
  return (d+2)*(d+1)/2 - mult.conditions();
}

const int MAX_DEG=100000;

void homogeneous(bool hard=false){
  int d,m,g, counter=0;
  cout<< "Enter genus (or -1 if you don't care):"<<endl;
  cin>>g;
  for(d=1;d<10000;d++)
    for(m=1;m<1000;m++){
      if(counter==10)
	return;
      if(g==-1 || genus(d,m)==g){
	if(hard){
	  int k=10*m-3*d;
	  if(m>=2*k)
	    continue;
	  if(dimension(d,m)<0)
	    continue;
	}
	cout<<"Case "<<counter<<": d="<<d<<" mult:"<<m
	    <<" dimension:"<<dimension(d,m)<<endl;
	counter++;
      }
    }
  if(counter==0)
    cout<<"Did not find small cases."<<endl;
  return;
}

void mixed(bool hard=false){
  int g, counter=0;
  cout<< "Enter genus (or -1 if you don't care):"<<endl;
  cin>>g;
  MixedMultLoop mult;
  for(;!mult.over();mult.next()){
    for(int d=0;d<MAX_DEG;d++){
      if(counter==50)
	return;
      if(g==-1 || genus(d,mult)==g){
	if(hard){
	  int k=mult.sum()-3*d;
	  if(mult.min()>=2*k || dimension(d,mult)<=0)
	    continue;
	}
	counter++;
	cout<<"Case "<<counter<<": Deg:"<<d<<" "<< mult.toString()<<" dimension:"<<dimension(d,mult)<<endl;
      }
    }
  }
  if(counter==0)
    cout<<"Did not find small cases."<<endl;
  return ;
}

void printCommand(int d, MixedMultLoop mult){
  int* multi=mult.multiplicities();
  cout<<"problem=newProblem("<<d<<", "<<multi[0]<<",{";
  for(int i=1;i<=8;i++)
    cout<<multi[i]<<", ";
  cout<<multi[9]<<"});"<<endl;
  cout<<"<<\" Degree "<<d<<" "<<mult.toString()
      <<" dimension:\"<<(expDim problem)<<\" 2k+1:\"<<2*(k problem) +1<< \" -> \""
      <<"<<checkConjecture(problem) <<endl;"<<endl;
  delete multi;

}


void generateCode(){
  int counter=0;
  MixedMultLoop mult;
  for(;!mult.over();mult.next()){
    for(int d=0;d<MAX_DEG;d++){
      if(counter==50)
	return;
	int k=mult.sum()-3*d;
	if(mult.min()>=2*k  || dimension(d,mult)<=0)
          continue;
	counter++;
	printCommand(d,mult);
      }
    }
}


int main(){
  cout<<"1-Mixed  2-Homogeneous 3-Hard mixed 4-Hard homogeneous 5-generate macaulay2 testcode"<<endl;
  int option;
  cin>>option;
  switch(option){
  case 1:
    mixed();
    break;
  case 2: 
    homogeneous();
    break;
  case 3:
    mixed(true);
    break;
  case 4:
    homogeneous(true);
    break;
  case 5:
    generateCode();
  }
  return 0;
}
