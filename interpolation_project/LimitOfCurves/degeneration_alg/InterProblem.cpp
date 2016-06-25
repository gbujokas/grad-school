#include "InterProblem.h"
#include "AlignIdeal.h"
#include "AlignSing.h"
#include "exceptions.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

InterProblem::InterProblem(int d, int n, int* multiplicities): ideal(d,n){
  begin=0;
  end=n;
  mult= new int[n];
  for(int i=0;i<n;i++)
    mult[i]=multiplicities[i];
  sort(mult,mult+end);
}

InterProblem:: ~ InterProblem(){
  delete mult;
}

bool InterProblem::isValid() const{
  return ( (begin < end) && mult[begin]>=ideal.multiplicity() && ideal.valid());
}
    
bool InterProblem::solve(bool verbose){
  while(true){
    if(verbose){
      cout<<toString();
    }
    if(!isValid())
      throw InvalidInterProblem();
    if(begin+1==end){
      if(verbose)
	cout<<"Result: NON_SPECIAL"<<endl;
      return true;
    }
    if(mult[end-1]+mult[end-2]>= ideal.getDegree() +2){
      if(verbose)
	cout<<"Result: DOUBLE-LINE"<<endl;
      return false;
    }
    if(mult[begin]+ideal.multiplicity()==ideal.getDegree()+1){
      mult[begin]--;
      ideal.splitVerticalLine();
    }
    ideal.degenerate(mult[begin++]);
  }
}

std::string InterProblem::toString() const{
  stringstream ss;
  ss<<"InterProblem - Degree:"<<ideal.getDegree()<<endl;
  ss<<"    Multiplicity: ";
  for(int i=begin;i<end;i++)
    ss<<mult[i]<<" ";
  ss<<endl;
  ss<<"    "<<ideal.toString()<<endl;
  return ss.str();
}
