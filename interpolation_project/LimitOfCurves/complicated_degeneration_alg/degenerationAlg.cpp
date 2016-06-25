#include<iostream>
#include<vector>
#include<algorithm>
#define MAX_MULT 2000
#define MAX_NUMBER_MULT 1000
#define MAX_DEG 100000
#define INFTY 1000
using namespace std;

class AlignedSingularity{
  int alpha[MAX_DEG];
  int begin, end;
public:
  AlignedSingularity(){
    begin=end=0;
    for(int i=0;i<MAX_DEG;i++)
      alpha[i]=0;
  }
  int degenerate(int, int); // degree, multiplicity. returns how many lines are split off.
  int multiplicity();
  void splitLine(){
    begin++;
  }
  int tangency(){
    if(begin==end)
      return 0;
    return alpha[begin];
  }

  bool isBadTriple(int, int );//degree, mult
  void printOut(){
    cout<<"AlignedSingularity: [";
    for(int i=end-1;i>=begin+1;i--)
      cout<<alpha[i]<<", ";
    if(end>begin)
      cout<<alpha[begin];
    cout<<"]"<<endl;
    //cout<<"Multiplicity:"<<multiplicity()<<endl;
    return;
  }
};

bool AlignedSingularity::isBadTriple(int degree, int m){
  for(int i=0; i<end-begin;i++)
    if(alpha[begin+i]==alpha[begin+i+1]+1 &&
       alpha[begin+i]+i + m >degree+1)
      return true;
  return false;

}
int AlignedSingularity::multiplicity(){
  if(end<=begin)
    return 0;
  int M=INFTY;
  for(int i=0; begin+i<MAX_DEG;i++){
    int k=alpha[begin+i]+i;
    M=M<k?M:k;
    if(alpha[begin+i]+i>M && alpha[begin+i]==0)
      break;
  }
  return M;
}

int AlignedSingularity::degenerate(int d, int b){
  int k=0;
  int newIdeal[MAX_MULT];
  //  cout<<"newIdeal: ";
  for(int i=0;i<MAX_MULT;i++){
    newIdeal[i]=(b-i<0?0:b-i);
    //  cout<<newIdeal[i]<<" ";
  }
  //  cout<<endl;
  for(int i=0;newIdeal[i]!=0;i++){
    //cout<<i<<" begin: "<<begin<<" end:"<<end<<endl;
    alpha[begin+i]+=newIdeal[i];
    if(end<=begin+i)
      end=begin+i+1;
    if(alpha[begin+i]>d-k){
      //   cout<<"ERROR "<<alpha[begin+i]<<" d "<<d<<endl;
      int excess= alpha[begin+i]-d-1+k;
      for(int j=0;j<excess;j++)
	newIdeal[i+j+1]++;
      k++;
    }
  }
  begin+=k;
  return k;
}

void testAlignedSingularity(){
  cout<<"AlignedSingularity Test"<<endl;
  AlignedSingularity sing;
  sing.printOut(); // []
  sing.degenerate(4,1);
  sing.degenerate(4,1);
  sing.degenerate(4,1);
  sing.degenerate(4,1); 
  sing.printOut();// [4]
  cout<<"false:"<<sing.isBadTriple(4,3)<<" false:"<<sing.isBadTriple(5,3)<<endl;
  sing.degenerate(4,3);
  sing.printOut();// [2,3]
  cout<<"true:"<<sing.isBadTriple(4,3)<<" false:"<<sing.isBadTriple(5,3)<<endl;
  sing.degenerate(6,5);
  sing.printOut();//[1,2,4]
  cout<<"true:"<<sing.isBadTriple(4,3)<<" false:"<<sing.isBadTriple(5,3)<<endl;
}


class MultSet{
  int begin, end;
  int mult[MAX_NUMBER_MULT];
  void sortMult(){
    sort(mult+begin, mult+end);
    while(mult[begin]==0)
      begin++;
  }
public:
  MultSet(int multiplicities[],int number){
    begin=0;
    end=number;
    for(int i=0;i<number;i++)
      mult[i]=multiplicities[i];
    sortMult();
  }

  int size(){
    return end-begin;
  }
  int getMin(){
    return mult[begin];
  }
  int popMin(){
    return mult[begin++];
  }
  int getMax(){
    return mult[end-1];
  }
  void decreaseMaxTwo(){
    if(size()<2){
      cout<<"ERROR- LESS THAN TWO ELEMENTS IN MULT"<<endl;
      return;
    }
    mult[end-1]--;
    mult[end-2]--;
    sortMult();
  }
  int getMaxTwo(){
    if(size()<2){
      cout<<"ERROR- LESS THAN TWO ELEMENTS IN MULT"<<endl;
      return 0;
    }
    return mult[end-1]+mult[end-2];
  }

  void printOut(bool complete=false){
    cout<<"MultSet: [";
    for(int i=begin;i<end-1;i++)
      cout<<mult[i]<<", ";
    if(end>begin)
      cout<<mult[end-1];
    cout<<"]"<<endl;
    if(complete){
      cout<<"Max:"<<getMax()<<" Size:"<<size()
	  <<" Empty:"<<isEmpty()<<" MaxTwo:"<<getMaxTwo()<<endl;
    }
  }
  bool isEmpty(){
    return begin==end;
  }
};

void testMultSet(){
  cout<<endl<<"MultSet TEST"<<endl;
  int multArray[5]={1,2,2,3,7};
  MultSet mult(multArray,5);
  mult.printOut(true); //[1,2,2,3,7]
  cout<<"Min:" <<mult.popMin()<<endl;
  mult.printOut(true);//[2,2,3,7]
  mult.decreaseMaxTwo();
  mult.printOut(true);//[2,2,2,6]
  mult.decreaseMaxTwo();
  mult.printOut(true);//[1,2,2,5]
  mult.decreaseMaxTwo();
  mult.printOut(true);//[1,1,2,4]
  mult.decreaseMaxTwo();
  mult.printOut(true);//[1,1,1,3]
  mult.decreaseMaxTwo();
  mult.printOut(true);//[1,1,2]
  mult.decreaseMaxTwo();
  mult.printOut(true);//[1,1]
  mult.decreaseMaxTwo();
  mult.printOut(true);//[]
  
}
enum DegenProblemState {RUNNING, NON_SPECIAL, DOUBLE_LINE, BAD_TRIPLE, BAD_SETUP};

void printState( DegenProblemState state){
  switch(state){
  case RUNNING:
    cout<<"RUNNING"<<endl;
    break;
  case NON_SPECIAL:
    cout<<"NON_SPECIAL"<<endl;
    break;
  case DOUBLE_LINE:
    cout<<"DOUBLE_LINE"<<endl;
    break;
  case BAD_TRIPLE:
    cout<<"BAD_TRIPLE"<<endl;
    break;
  case BAD_SETUP:
    cout<<"BAD_SETUP"<<endl;
    break;
  default:
    cout<<"ERROR"<<endl;
  }
}

class DegenProblem{
  DegenProblemState state;
  int d;
  AlignedSingularity sing;
  MultSet mult;

  bool isBadSetup();
  void runIteration();


public:
  DegenProblem(int degree, int multArray[], int numberMult) :
    mult(multArray, numberMult),d(degree) , sing(){
    state=RUNNING;
  }

  DegenProblemState solve(bool);

  void printOut();
};

void DegenProblem::printOut(){
  cout<<"DegenProblem: State:";
  printState(state);
  cout<<" Degree:"<<d<<endl;
  mult.printOut();
  sing.printOut();
}

DegenProblemState DegenProblem::solve(bool debug=false){
  while(state==RUNNING){
    if(debug){
      printOut();
      cout<<endl;
    }
    runIteration();
  }
  if(debug){
    cout<<"FINAL STATE"<<endl;
    printOut();
  }
  return state;
}

void DegenProblem::runIteration(){
  if(state!=RUNNING)
    return;
  if(mult.isEmpty()){
    state=NON_SPECIAL;
    return;
  }

  if(isBadSetup()){
    state= BAD_SETUP;
    return;
  }

  bool flag=false;
  while(true){
    if(mult.size()<2)
      break;
    int maxDegLine=mult.getMaxTwo();
    if(maxDegLine>d+1){
      state=DOUBLE_LINE;
      return;
    }
    if(maxDegLine==d+1){
      flag=true;
      d--;
      mult.decreaseMaxTwo();
      if(sing.tangency()>d){
	sing.splitLine();
	d--;
      }
      continue;
    }
    break;
  }
  if(flag)
    return;


  int minMult=mult.popMin();
  if(sing.isBadTriple(d, minMult)){
    state=BAD_TRIPLE;
    return;
  }
  int deltaD=sing.degenerate(d,minMult);
  d-=deltaD;
  return;
}

bool DegenProblem::isBadSetup(){
  return !(mult.getMin()>=sing.multiplicity()&& 
	   mult.getMax()+sing.multiplicity()<=d);
}

void testDegenProblem(){
  DegenProblem* problem;
  int vector1[3]={1,2,3};
  problem = new DegenProblem(10, vector1, 3);
  printState(problem->solve(true)); //NON_SPECIAL
  cout<<endl<<endl<<endl;
  delete problem;
  
  int vector2[5]={2,2,2,2,2};
  problem = new DegenProblem(4, vector2, 5);
  printState(problem->solve(true)); //DOUBLE_LINE
  cout<<endl<<endl<<endl;

  int vector3[7]={4,2,2,2,2,2,2};
  problem = new DegenProblem(6, vector3, 7);
  printState(problem->solve(true)); //DOUBLE_LINE
  cout<<endl<<endl<<endl;
  
  int vector4[9]={4,4,4,4,1,1,1,1,1};
  problem = new DegenProblem(8, vector4, 9);
  printState(problem->solve(true)); //BAD_SETUP
  cout<<endl<<endl<<endl;

  int vector5[9]={6,2,2,2,2,2,2,2,2};
  problem = new DegenProblem(8, vector5, 9);
  printState(problem->solve(true)); //DOUBLE_LINE
  cout<<endl<<endl<<endl;


  int vector6[5]={3,3,2,2,2};
  problem = new DegenProblem(5, vector6, 5);
  printState(problem->solve(true)); //DOUBLE_LINE
  cout<<endl<<endl<<endl;

  int vector7[5]={7,6,2,2,2};
  problem = new DegenProblem(8, vector7, 5);
  printState(problem->solve(true)); //DOUBLE_LINE
  cout<<endl<<endl<<endl;
}

class BlownUpProjPlane{
  //Generates -1 curves on P^2 blown up at 
  //general points using Cremona transformations
  int numberOfPoints;
  int table[MAX_NUMBER_MULT+1];
public:
  BlownUpProjPlane(int); // number of (general) points blown up
  int* nextMinusOneCurve(); // [d, m_1,m_2,...] <-> dH -m_1 E_1 - m_2 E_2 -...
};

BlownUpProjPlane::BlownUpProjPlane(int number){
  if(number<3){
    cout<<"ERROR - BLOW UP AT LEAST 3 POINTS"<<endl;
  }
  numberOfPoints=number;
  table[0]=table[number]=table[number-1]=1;
  for(int i=1;i<number-1;i++)
    table[i]=0;
}

int* BlownUpProjPlane::nextMinusOneCurve(){
  int delta= table[0]-table[1]-table[2]-table[3];
  for(int i=0;i<=3;i++)
    table[i]+=delta;

  sort(table+1, table+numberOfPoints+1);
  return table;
}

void testBlownUpProjPlane(){
  int number=9;
  cout<<endl<<endl<<"Cremona table for "<<number<<" points"<<endl;
  BlownUpProjPlane surface(number);
  int* curve;
  for(int i=0;i<10;i++){
    curve= surface.nextMinusOneCurve();
    for(int j=0;j<number+1;j++)
      cout<<curve[j]<<" ";
    int selfIntersection=curve[0]*curve[0];
    for(int i=1;i<number+1;i++)
      selfIntersection-=curve[i]*curve[i];
    cout<<" Self intersection: "<<selfIntersection<<endl;
  }

}

void workSpecificExample(){
    int d, number, mult[MAX_MULT];
    cout<<"Enter the degree:"<<endl;
    cin>>d;
    cout<<"Enter the number o multiple points:"<<endl;
    cin>>number;
    cout<<"Enter multiplicities:"<<endl;
    for(int i=0;i<number;i++)
      cin>>mult[i];
    DegenProblem problem(d, mult, number);
    problem.solve(true);
}

void workASingleSurface(){
    int numberOfPoints;
    cout<<"Number of points to blow up (at least 3)"<<endl;
    cin>>numberOfPoints;
    BlownUpProjPlane surface(numberOfPoints);
    int* curve;
    int* doubleCurve =  new int[numberOfPoints];
    for(int i=0;i<100;i++){
      curve=surface.nextMinusOneCurve();
      if(2*curve[numberOfPoints]>=MAX_MULT){
	cout<<"MULTIPLICITY TOO HIGH"<<endl;
	break;
      }
      if(2*curve[0]>=MAX_DEG){
	cout<<"DEGREE TOO HIGH"<<endl;
	break;
      }
      cout<<"Degree:"<<2*curve[0]<<" Mult: ";
      
      for(int i=0;i<numberOfPoints;i++){
	cout<<2*curve[i+1]<<" ";
	doubleCurve[i]=2*curve[i+1];
      }
      DegenProblem problem(2*curve[0], doubleCurve, numberOfPoints);
      printState(problem.solve());
    }
}

void runtests(){
      testAlignedSingularity();
      testMultSet();
      testDegenProblem();
      testBlownUpProjPlane();
}

void automatedTesting(){
  for(int numberOfPoints=9;numberOfPoints<MAX_NUMBER_MULT-5;numberOfPoints++){
    cout<<"Number of points "<< numberOfPoints<<" - ";
    BlownUpProjPlane surface(numberOfPoints);
    int* curve;
    int* doubleCurve =  new int[numberOfPoints];
    int numcases;
    for(numcases=0;numcases<100;numcases++){
      curve=surface.nextMinusOneCurve();
      if(2*curve[numberOfPoints]>=MAX_MULT){
	//cout<<"MULTIPLICITY TOO HIGH"<<endl;
	break;
      }
      if(2*curve[0]>=MAX_DEG){
	//cout<<"DEGREE TOO HIGH"<<endl;
	break;
      }
      //cout<<"Degree:"<<2*curve[0]<<" Mult: ";
      
      for(int i=0;i<numberOfPoints;i++){
	//cout<<2*curve[i+1]<<" ";
	doubleCurve[i]=2*curve[i+1];
      }
      DegenProblem problem(2*curve[0], doubleCurve, numberOfPoints);
      DegenProblemState finalState= problem.solve();
      if(finalState!=DOUBLE_LINE){
	cout<<"NOT DOUBLE LINE!!!"<<endl;
      }
    }
    cout<<numcases<<" cases analysed."<<endl;
  }
}

int main(){
  int option=0;
  while(option!=1 && option!=2 && option!=3 && option!=4){
    cout<<"Options:"<<endl
	<<"1) Work out specific example"<<endl
	<<"2) Test all double -1 curves on a surface"<<endl
	<<"3) Run debug tests"<<endl
	<<"4) Automated testing (long)"<<endl;
    cin>>option;
  }
  switch(option){
  case 1:
    workSpecificExample();
    break;
  case 2:
    workASingleSurface();
    break;
  case 3:
    runtests();
    break;
  case 4:
    automatedTesting();
    break;
  }  
  return 0;
}
