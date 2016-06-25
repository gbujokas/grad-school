#ifndef INC_BLOWNUPPROJPLANE_H
#define INC_BLOWNUPPROJPLANE_H

class BlownUpProjPlane{
  //Generates -1 curves on P^2 blown up at 
  //general points using Cremona transformations
  int numberOfPoints;
  int* table;
public:
  BlownUpProjPlane(int); // number of (general) points blown up
  int* nextMinusOneCurve(); // [d, m_1,m_2,...] <-> dH -m_1 E_1 - m_2 E_2 -...
};

#endif /*INC_BLOWNUPPROJPLANE */
