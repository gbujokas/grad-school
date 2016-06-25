#ifndef PRIMEPOWER_H
#define PRIMEPOWER_H

class PrimePower{
 private:
  int p, a;
 public:
 PrimePower(int prime, int alpha):p(prime), a(alpha){};
  int prime(){
    return p;
  }
  int exp(){
    return a;
  }
};

#endif /*PRIMEPOWER_H */
