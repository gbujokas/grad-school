#ifndef INC_ALIGNSING_H
#define INC_ALIGNSING_H
#include<string>


class AlignSing{
  int* alpha;
  int begin,end,maximumLength;
 public:
  AlignSing(int,bool=false); 
// size=m, true-> empty
//         false-> m-fold point
  AlignSing(int, int*);
  //size, alpha vector, in increasing order!
  AlignSing(const AlignSing&); //deep copy
  ~AlignSing();

  AlignSing& operator = (const AlignSing& copy);

  void addSpillage(int); //throws SpillageDoesNotFit
  void splitBaseLine();
  bool isZero() const;
  int multiplicity() const;
  void splitVerticalLine(); //throws SplittingEmptySing
  //throws NotValid if m(alpha(j))!=m(total)
  void add(AlignSing&); //throws SingDoesNotFit
  std::string toString() const;
  int getAlpha(int) const;
  bool operator == (const AlignSing&) const;
};


#endif //INC_ALIGNSING_H
