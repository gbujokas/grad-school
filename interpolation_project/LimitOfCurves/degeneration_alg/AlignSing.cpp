#include "AlignSing.h"
#include "exceptions.h"
#include <string>
#include<sstream>
#define SLACK 5


using namespace std;

AlignSing::AlignSing(int m, bool empty){
  maximumLength=m;
  alpha= new int[m+SLACK];
  for(int i=0;i<m;i++)
    alpha[i]=empty?0:m-i;
  begin=0;
  end=empty?0:m;
}

AlignSing::AlignSing(int length, int* vector){
  end=maximumLength=length;
  alpha= new int[length+ SLACK];
  for(int i=0;i<length;i++)
    alpha[i]=vector[i];
  begin=0;
}

AlignSing::AlignSing(const AlignSing& copy){
  alpha= new int[copy.maximumLength +SLACK];
  end=copy.end;
  begin=copy.begin;
  maximumLength=copy.maximumLength;
  for(int i=0;i<maximumLength;i++)
    alpha[i]=copy.alpha[i];
}


AlignSing::~AlignSing(){
  if(this!=NULL){
    try{
      if(alpha!=NULL)
	delete alpha;
    }catch(...){}
  }
}

AlignSing& AlignSing::operator = (const AlignSing& copy){
  if(this!=&copy){
    try{
      delete alpha;
    }catch(exception e){};
    alpha= new int[copy.maximumLength +SLACK];
    end=copy.end;
    begin=copy.begin;
    maximumLength=copy.maximumLength;
    for(int i=0;i<maximumLength;i++)
      alpha[i]=copy.alpha[i];
  }
  return *this;
}


void AlignSing::addSpillage(int spill){
  if(spill>multiplicity())
    throw SpillageDoesNotFit();
  for(int i=0;i<spill;i++)
    alpha[i+begin]++;
}

void AlignSing::splitBaseLine(){
  if(end>begin)
    begin++;
}

bool AlignSing::isZero() const{
  return begin==end;
}

int AlignSing::multiplicity() const{
  return end-begin;
}

void AlignSing::splitVerticalLine(){
  if(isZero())
    throw SplittingEmptySing();

  for(int i=begin;i<end;i++)
    alpha[i]--;
  while(alpha[end-1]==0 && begin<end)
    end--;
}

void AlignSing::add(AlignSing& sing){
  for(int i=0;sing.getAlpha(i)!=0;i++){
    if(end<=begin+i)
      end=begin+i+1;
    if(end>maximumLength)
      throw SingDoesNotFit();
    alpha[begin+i]+=sing.getAlpha(i);
  }
}

std::string AlignSing::toString() const{
  std::stringstream output;
  output<<"[";
  if(!isZero()){
    for(int i=begin;i<end-1;i++){
      output<<alpha[i];
      output<<",";
    }
    output<<alpha[end-1];
  }
  output<<"]";
  return output.str();
}

int AlignSing::getAlpha(int i) const{
  if(begin+i>=end)
    return 0;
  return alpha[begin+i];
}

bool AlignSing::operator == (const AlignSing& sing) const{
  if(multiplicity()!=sing.multiplicity())
    return false;
  for(int i=0;i<sing.multiplicity();i++)
    if(getAlpha(i)!=sing.getAlpha(i))
      return false;
  return true;
}
