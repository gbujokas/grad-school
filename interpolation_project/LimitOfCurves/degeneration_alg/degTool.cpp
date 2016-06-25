#include "InterProblem.h"
#include "exceptions.h"
#include "AlignSing.h"
#include "AlignIdeal.h"
#include "blownupprojplane.h"
#include "baseLocus.h"
#include <iostream>
#include <fstream>

using namespace std;

int mult[1000];


inline int expectedDim(int d,int m,int n){
  return ((d+2)*(d+1) - n * m * (m+1))/2;
}

inline int genus(int d, int m, int n){
  return ((d-1)*(d-2) - n * m*(m-1))/2;
}
void automaticHomogeneous(){
  int d,n,m;
  cout<<"Enter number of points"<<endl;
  cin>>n;
  cout<<"Enter the multiplicity"<<endl;
  cin>>m;
  for(int i=0;i<n;i++)
    mult[i]=m;

  d= m;

  while(true){
    if(expectedDim(d+1,m,n)<=0){
      d++;
      continue;
    }
    cout<<"Degree d:"<<d<<" Expected dimension: "<<expectedDim(d,m,n)<<" Genus: "<<genus(d,m,n)<<" - ";

    InterProblem problem(d,n,mult);
    bool nonspecial=problem.solve(false);
    cout<<(nonspecial?"Non special":"Found double line")<<endl;
    if(nonspecial)
      break;
    if(!nonspecial && n>8){
      HomInterProblem problem(d,m,n);
      problem.findBaseLocus();
    }

    d++;
  }
}


void homogeneous(){
  int d,n,m;
  cout<<"Enter number of points"<<endl;
  cin>>n;
  cout<<"Enter the multiplicity"<<endl;
  cin>>m;
  for(int i=0;i<n;i++)
    mult[i]=m;

  d= m;

  while(expectedDim(d,m,n)<0)
    d++;

  cout<<"Degree d:"<<d<<" Expected dimension: "<<expectedDim(d,m,n)<<" Genus: "<<genus(d,m,n)<<endl;

  InterProblem problem(d,n,mult);
  bool nonspecial=problem.solve(true);
  if(!nonspecial && n>8){
    HomInterProblem problem(d,m,n);
    problem.findBaseLocus();
  }

}

void workOutExample(){
  int d,n;
  cout<<"Enter degree"<<endl;
  cin>>d;
  cout<<"Enter number of points"<<endl;
  cin>>n;
  cout<<"Enter multiplicities"<<endl;
  for(int i=0;i<n;i++)
    cin>>mult[i];
  InterProblem problem(d,n,mult);
  problem.solve(true);
}

void cremonatable(){
  int number;
  cout<<"Number of points to blow up"<<endl;
  cin>>number;
  BlownUpProjPlane surface(number);
  int* curve;
  int tests=100;
  for(int k=0;k<tests;k++){
    curve=surface.nextMinusOneCurve();
    for(int i=0;i<number;i++)
      mult[i]=2*curve[i+1];
    InterProblem problem(2*curve[0],number,mult);
    bool result=problem.solve(false);
    if(result){
      cout<<"ERROR!!"<<endl;
      break;
    }
  }
  cout<<"Tested "<<tests<<" special systems, all of them returned double line."<<endl;
}


int main(){
  try{
    cout<<"Degeneration tool"<<endl
	<<"1) Work out example"<<endl
	<<"2) Test using Cremona table"<<endl
	<<"3) Test homogeneous case"<<endl
	<<"4) Test multiple homogeneous cases"<<endl;

    int option;
    cin>>option;
    switch(option){
    case 1:
      workOutExample();
      break;
    case 2:
      cremonatable();
      break;
    case 3:
      homogeneous();
      break;
    case 4:
      automaticHomogeneous();
      break;

    }
    /* 
      


     */

  }catch(BadTriple){
    cerr<<"Exception: BadTriple"<<endl;
  }catch(SpillageDoesNotFit){
    cerr<<"Exception: SpillageDoesNotFit"<<endl;
  }catch(SplittingEmptySing){    
    cerr<<"Exception: SplittingEmptySing"<<endl;
  }catch(SingDoesNotFit){
    cerr<<"Exception: SingDoesNotFit"<<endl;
  }catch(AlignIdealFull){
    cerr<<"Exception: AlignIdealFull"<<endl;
  }catch(NotValid){
    cerr<<"Exception: NotValid"<<endl;
  }catch(InvalidInterProblem){
    cerr<<"Exception: InvalidInterProblem"<<endl;
  }catch(...){
    cerr<<"Exception: Unknown"<<endl;
  }
  return 0;

}
