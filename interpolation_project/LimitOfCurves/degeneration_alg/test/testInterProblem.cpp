#include "../AlignSing.h"
#include "../AlignIdeal.h"
#include "../exceptions.h"
#include "../InterProblem.h"

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

bool test1(){

  ifstream in;
  try{
    in.open("test/testCases1.in");
    if(! in)
      throw 1;
  }catch(...){
    cerr<<"ERROR: Could not open file testCases1.in"<<endl;
    return false;
  }
  int tests,d,n, mult[100];
  in>>tests;
  while(tests-->0){
    in>>d>>n;
    for(int i=0;i<n;i++)
      in>>mult[i];
    InterProblem problem(d,n,mult);
    bool nonspecial=problem.solve();
    int answer;
    in>>answer;
    if((answer!=0) != nonspecial)
      return false;
  }
  in.close();
  return true;
}

int main(){
  cout<<"Testing InterProblem:";
  try{
    if(!test1()){
      cout<<"FAILED TEST 1"<<endl;
      return 0;
    }
    /*
    if(!test2()){
      cout<<"FAILED TEST 2"<<endl;
      return 0;
    }
    
    if(!test3()){
      cout<<"FAILED TEST 3"<<endl;
      return 0;
    }
    
    if(!test4()){
      cout<<"FAILED TEST 4"<<endl;
      return 0;
    }
    if(!test5()){
      cout<<"FAILED TEST 5"<<endl;
      return 0;
      }*/
    cout<<"PASSED"<<endl;
  }catch(exception e){
    cerr<<"FAILED TEST _ CAUGHT EXCEPTION: "<<e.what()<<endl;
  };
  return 0;
}
