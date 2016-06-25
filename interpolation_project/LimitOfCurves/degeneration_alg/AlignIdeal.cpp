#include "AlignIdeal.h"
#include "exceptions.h"
#include "AlignSing.h"
#include <string>
#include <iostream>

using namespace std;

AlignIdeal::AlignIdeal(int d, int number): maximumSing(number), numSing(0), degree(d),
			       total(d+1, true){
  singularity=new AlignSing*[number];
  for(int i=0;i<maximumSing;i++)
    singularity[i]=NULL;
}

AlignIdeal::AlignIdeal(const AlignIdeal& copy): total(copy.total){
  maximumSing=copy.maximumSing;
  numSing=copy.numSing;
  degree=copy.degree;
  singularity=new AlignSing*[maximumSing];
  for(int i=0;i<maximumSing;i++){
    if(copy.singularity[i]==NULL)
      singularity[i]=NULL;
    else
      singularity[i]=new AlignSing(*copy.singularity[i]);
  }
}

AlignIdeal& AlignIdeal::operator = (const AlignIdeal& copy){
  if(singularity!=NULL){
    for(int i=0;i<maximumSing;i++)
      try{
	if(singularity[i]!=NULL)
	  delete singularity[i];
      }catch(...){};
    delete singularity;
  }
  maximumSing=copy.maximumSing;
  numSing=copy.numSing;
  degree=copy.degree;
  singularity=new AlignSing*[maximumSing];
  for(int i=0;i<maximumSing;i++){
    if(copy.singularity[i]==NULL)
      singularity[i]=NULL;
    else
      singularity[i]=new AlignSing(*copy.singularity[i]);
  }
}

AlignIdeal::~AlignIdeal(){
  if(singularity!=NULL){
    for(int i=0;i<maximumSing;i++)
      try{
	if(singularity[i]!=NULL)
	  delete singularity[i];
      }catch(...){};
    delete singularity;
  }
}

int AlignIdeal::getDegree() const{
  return degree;
}

int AlignIdeal::multiplicity() const{
  return total.multiplicity();
}

void AlignIdeal::splitVerticalLine(){
  if(total.isZero())
    throw SplittingEmptySing();
  if(total.multiplicity()!=singularity[numSing-1]->multiplicity())
    throw NotValid();

  singularity[numSing-1]->splitVerticalLine();
  total.splitVerticalLine();
  degree--;
}

std::string AlignIdeal::toString(bool verbose) const{
  if(!verbose)
    return "AlignIdeal: "+total.toString();
  else{
    return "AlignIdeal: "+total.toString();
    //TODO
  }
}

void AlignIdeal::degenerate(int m){
  if(badtriple(m))
    throw BadTriple();
  if(numSing>=maximumSing)
    throw AlignIdealFull();
  AlignSing* newSing=singularity[numSing]=new AlignSing(m);
  numSing++;
  int excess;
  for(int i=0;;i++){
    excess=newSing->getAlpha(0) + total.getAlpha(0)-degree-1;
    if(excess<=-1)
      break;
    splitBaseLine();
    newSing->addSpillage(excess);
  }
  total.add(*newSing);
}

bool AlignIdeal::badtriple(int m) const{
  if(multiplicity()+m>degree)
    return true;
  for(int i=0;i<multiplicity()+4;i++)
    if(total.getAlpha(i)==total.getAlpha(i+1)+1 &&
       total.getAlpha(i)+i+m>degree+1)
      return true;
  return false;
}

void AlignIdeal::splitBaseLine(){
  degree--;
  total.splitBaseLine();
  for(int i=0;i<numSing;i++)
    singularity[i]->splitBaseLine();
}

AlignSing AlignIdeal::totalSing() const{
  return AlignSing(total);
}

/*bool AlignIdeal::operator == (AlignIdeal& compare) const{
  if(degree!= compare.getDegree() ||
     maximumSing!=compare.maximumSing ||
     numSing!=compare.numSing||
     !(total==compare.total))
    return false;
  for(int i=0;i<numSing;i++)
    if(!((*singularity[i])==(*compare.singularity[i])))
      return false;
  return true;
  }*/

bool AlignIdeal::valid() const{
  for(int i=0;i<numSing-1;i++)
    if(singularity[i]->multiplicity() > singularity[i+1]->multiplicity())
      return false;
  return true;
}

  
