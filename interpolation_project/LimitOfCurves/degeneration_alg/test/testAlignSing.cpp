#include "../AlignSing.h"
#include "../exceptions.h"

#include<iostream>
#include<string>

using namespace std;

bool test1(){
  AlignSing sing (10);
  sing.addSpillage(3);
  int answer[10]={11,10,9,7,6,5,4,3,2,1};
  AlignSing expectedResult(10, answer);
  if(!(sing==expectedResult))
    return false;
  
  try{
    sing.addSpillage(11);
  }catch(SpillageDoesNotFit){
    return true;
  }catch(...){}

  return false;
}

bool test2(){
  AlignSing sing(3); //[3,2,1]
  if(sing.multiplicity()!=3)
    return false;
  if(sing.isZero())
    return false;


  sing.splitBaseLine(); //[2,1]

  if(!(sing==*(new AlignSing(2))))
    return false;


  sing.splitBaseLine(); //[1]

  if(sing.getAlpha(0)!=1)
    return false;
  if(sing.getAlpha(1)!=0)
     return false;
  if(sing.getAlpha(1000)!=0)
    return false;
  sing.splitBaseLine(); //[]


  if(!sing.isZero())
    return false;

  sing.splitBaseLine(); //[]
  if(!sing.isZero())
    return false;

  return true;
}

bool test3(){
  AlignSing sing(2); //[2,1]
  sing.addSpillage(2);//[3,2]


  //test splitverticalline
  sing.splitVerticalLine(); //[2,1]
  if(!(sing==*(new AlignSing(2))))
    return false;

  if(sing.getAlpha(0)!=2)
    return false;

  sing.splitVerticalLine(); //[1]
  if(!(sing==*(new AlignSing(1))))
    return false;
  sing.splitVerticalLine();// []
  if(!sing.isZero())
    return false;
  try{
    sing.splitVerticalLine(); // throw SplittingEmptySing
  }
  catch(SplittingEmptySing){
    return true;
  }
  catch(...){};
  return false;
}

bool test4(){
  AlignSing mult2(2),mult3(3),mult4(4);
  mult3.add(mult2);
  int sumVec[3]={5,3,1};
  AlignSing sum(3,sumVec);
  if(!(mult3==sum))
    return false;

  AlignSing sing(10,true);
  sing.add(mult3);
  
  sing.add(mult4);
  
  int sum2Vec[4]={9,6,3,1};
  AlignSing sum2(4,sum2Vec);
  if(!(sing==sum2))
    return false;

  try{
    mult3.add(mult4);
  }catch(SingDoesNotFit){
    return true;
  }catch(...){};
  return false;
}

bool test5(){
  //test copy constructor and assignment
  AlignSing original(5);
  AlignSing* copy;
  copy=new AlignSing(original);
  if(!(original==*copy))
    return false;
  
  AlignSing sing(6);
  if(sing==original)
    return false;
  sing=original;
  if(!(sing==original))
    return false;

  delete copy;
  //should not affect original.

  if(!(sing==original))
    return false;

  return true;
}

int main(){
  cout<<"Testing AlignSing:";
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
    if(!test5()){
      cout<<"FAILED TEST 5"<<endl;
      return 0;
    }
    cout<<"PASSED"<<endl;
  }catch(exception e){
    cerr<<"FAILED TEST _ CAUGHT EXCEPTION: "<<e.what()<<endl;
  }
  return 0;
}
