#include "../AlignSing.h"
#include "../AlignIdeal.h"
#include "../exceptions.h"

#include<iostream>
#include<string>

using namespace std;

bool test1(){
  AlignIdeal ideal(8,5);
  ideal.degenerate(2);
  ideal.degenerate(2);
  ideal.degenerate(2);
  ideal.degenerate(2);
  int expectedTotal1Vec[2]={8,4};
  AlignSing expectedTotal1(2,expectedTotal1Vec);
  if(!(ideal.totalSing()==expectedTotal1) || 
     ideal.getDegree()!=8)
    return false;

  ideal.degenerate(2);
  int expectedTotal2Vec[1]={6};
  AlignSing expectedTotal2(1,expectedTotal2Vec);
  if(!(ideal.totalSing()==expectedTotal2) || 
     ideal.getDegree()!=7)
    return false;

  return true;
}

bool test2(){
  AlignIdeal ideal(4,5);
  ideal.degenerate(1);
  ideal.degenerate(1);
  ideal.degenerate(1);
  ideal.degenerate(1);
  ideal.degenerate(3); //should get cusp!
  int cuspIdeal[2]={3,2};
  AlignSing cusp(2,cuspIdeal);
  if(!(cusp==ideal.totalSing()))
    return false;
  ideal.splitVerticalLine(); //should get node
  AlignSing node(2);
  if(!(ideal.totalSing()==node))
    return false;
  
  return true;
}

bool test3(){
  AlignIdeal ideal(10,2);
  ideal.degenerate(2);
  try{
    ideal.degenerate(10);
    return false;
  }
  catch(BadTriple e){}
  catch(...){return false;}

  ideal.degenerate(2);

  try{
    ideal.degenerate(2);
    return false;
  }catch(AlignIdealFull){}
  catch(...){return false;}

  return true;
}

bool test4(){
  /*d=24, 14, 10, 4^6
    should get ad triple on last step
  */
  AlignIdeal ideal(24,8);
  ideal.degenerate(4);
  ideal.degenerate(4);
  ideal.degenerate(4);
  ideal.degenerate(4);
  ideal.degenerate(4);
  ideal.degenerate(4);
  ideal.degenerate(10);
  int expectedIdeal[8]={22,15,8,7,5,4,3,2};
  AlignSing sing(8,expectedIdeal);
  if(!(ideal.totalSing()==sing))
    return false;
  if(ideal.multiplicity()!=8)
    return false;
  if(!ideal.valid())
    return false;

  try{
    ideal.degenerate(14);
    return false;
  }catch(BadTriple){}
  catch(...){return false;}

  ideal.splitVerticalLine();
  sing.splitVerticalLine();
  if(!(ideal.totalSing()==sing))
    return false;

  ideal.degenerate(1);
  if(ideal.valid())
    return false;
  return true;

}

int main(){
  cout<<"Testing AlignIdeal:";
  try{
    if(!test1()){
      cout<<"FAILED TEST 1"<<endl;
      return 0;
    }
    
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
    /*if(!test5()){
      cout<<"FAILED TEST 5"<<endl;
      return 0;
      }*/
    cout<<"PASSED"<<endl;
  }catch(exception e){
    cerr<<"FAILED TEST _ CAUGHT EXCEPTION: "<<e.what()<<endl;
  };
  return 0;
}
