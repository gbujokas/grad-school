#ifndef PRIMETABLE_H
#define PRIMETABLE_H


class PrimeTable{
 private:
  int * primeList;
  int maxIndex;
  PrimeTable();
  PrimeTable(PrimeTable const&);  
  PrimeTable& operator=(PrimeTable const&);
 public:
  static PrimeTable& instance(){
    static PrimeTable object;
    return object;
  }

  int getPrime(int index);
  ~PrimeTable();
   
};

#endif /*PRIMETABLE_H*/
