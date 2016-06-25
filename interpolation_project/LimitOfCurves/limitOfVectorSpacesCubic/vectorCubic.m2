--Setup: Degree d curves, 
--       
--       

prime=73;
--prime =641;
--prime=4289

F=ZZ/prime;

redMap= map(F,ZZ) --reductionMap
--F=QQ
--Can change to QQ or a higher prime.

R=F[x,y,z];
E= y^2 - x^3 -x;
Ez= y^2 * z - x^3 - x* z^2 -- homogeneous version of E

-- randomPoint() gives a random point on curve E

randomPointList= n -> (
     if (n==1) then
     {randomPoint()}
     else
     {randomPoint()}|randomPointList(n-1)
  )

randomPoint = () -> randomPointLoop(randomCoord(), 0) ;

randomCoord= () -> random(1,prime);

randomPointLoop= (x0, y0) ->  
     (if(sub(Ez,{x=>x0, y =>y0, z=>1}) % prime ==0) 
	      then  (redMap x0,redMap y0,redMap 1) 
	      else (if(y0 == prime) 
      		     then randomPoint()     
      		     else randomPointLoop(x0,y0+1)))


recursionLimit=100000
--tail optimization problem...


--- interpolation conditions:
 
 I=ideal (x,y,z);
 
 monomialsOfDeg= (d) -> gens I^d; 
 partials= (m) -> gens I^(m-1);
 
 
 M=(d,m)->diff(transpose partials(m),monomialsOfDeg(d)); --sort of the Jacobian matrix
 
 
 F[t]; -- t is the family parameter

-- apply M to at a point (x0,y0,z0)
 subM=(d,m) -> ((x0,y0,z0) ->  sub(M(d,m),{x=>x0, y=>y0,z=>z0})) ;  
   
-- apply M to a family (t+x0,t+y0,t+z0)   
 degenM= (d,m) -> ((x0,y0,z0) ->(sub(M(d,m), {x=>x0+t,y=>y0+t,z=>z0+t})));
 
-- interpolation matrix concatenates all interpolation conditions at fixedPoints, and at the movingPoint 
 fixedInterpolationMatrix=(d,m,fixedPoints) -> fold((a,b) -> a||b, subM(d,m) \ fixedPoints) 
 interpolationMatrix= (d,m,movingPoint,fixedPoints) -> ((degenM(d,m)) movingPoint ) || fixedInterpolationMatrix(d,m,fixedPoints);    
 
 -- here A is the interpolationMatrix.
 getFamily= gens @@ kernel;
 getCentralFiber= (A) -> sub( getFamily(A), {t=>0});
 getLimitLinearSeries= (d,A) -> ideal (monomialsOfDeg(d) * getCentralFiber(A));  
 getDimLimitLinearSeries=  numgens @@ source @@ getFamily;
 getLinearSeries= (d,A) -> ideal  (monomialsOfDeg(d) * getFamily(A)); 
 
-- applying to interpolationMatrix:

 families=  (d,m,movingPoint,fixedPoints) -> getFamily(interpolationMatrix (d,m,movingPoint,fixedPoints));

 limitLinearSeries=  (d,m,movingPoint,fixedPoints) -> getLimitLinearSeries(d, interpolationMatrix(d,m,movingPoint,fixedPoints));
 dimLimitLinearSeries=  (d,m,movingPoint,fixedPoints) -> getDimLimitLinearSeries(interpolationMatrix(d,m,movingPoint,fixedPoints));
 
-- getting linearSeries for fixed point
 
 fixedLimitLinearSeries=  (d,m,fixedPoints) -> getLinearSeries(d, fixedInterpolationMatrix(d,m,fixedPoints));
 dimFixedLimitLinearSeries=  (d,m,fixedPoints) -> getDimLimitLinearSeries(fixedInterpolationMatrix(d,m,fixedPoints));
 
 
 -- Conjectural results:
 numExpDim=(d,m) -> ((d+2)*(d+1) -10 * (m+1)* m)/2;
 expDim=(d,m) -> if numExpDim(d,m)<0 then 0 else numExpDim(d,m);
 conjMult= (d,m) -> 2* (10* m -3 *d) +1 ;
 conjIdeal=(d,m,points) -> 
         (if( d< 3*conjMult(d,m)) then ideal (R)
                                  else if conjMult(d,m)<0  
				              then fixedLimitLinearSeries(d,m, points)
	                                      else  Ez^(conjMult(d,m)) * conjIdeal(d-3*conjMult(d,m),
	                                (if (m- conjMult(d,m)<0) then conjMult(d,m)-m-1 else m-conjMult(d,m)),
	                                points));


 -- Tool for checking conjecture:
 checkConjecture =  (d,m,movingPoint,fixedPoints) -> 
       ((dimLimitLinearSeries(d,m,movingPoint, fixedPoints) == expDim(d,m)) and
        (limitLinearSeries (d,m,movingPoint,fixedPoints) == conjIdeal(d,m,{movingPoint} | fixedPoints)));
 
 -- Automated testing
 -- which pairs should we test
 --valid= (d,m) -> ((numExpDim(d,m-1)>=0) and (conjMult(d,m)>0))     
 valid= (d,m) -> true     
 
 runtests= () -> (
     movingPoint=randomPoint();     
      <<"Moving point:"<<movingPoint<<endl;

     fixedPoints=randomPointList(9);
     <<"Fixed points:"<<fixedPoints<<endl;
   
   <<"Checking conjecture: "<<endl;
   
   for d from 3 to 20 do{   
    <<"d="<<d<<endl;
   
    for m from 0 to d do
    if(valid(d,m)) then {
      if(checkConjecture(d,m,movingPoint,fixedPoints)) 
      then (<<"   m="<<m<<":true"<<endl; )     
      else { <<"ERROR! Failed for m="<<m<<endl; 
     	      break;
     	   }
     }
   }
   )
 
 test=()->(
      movingPoint=randomPoint();
      fixedPoints=randomPointList(9);
      a=checkConjecture(16,5, movingPoint, fixedPoints);
      print a;
      b=checkConjecture(13,4, movingPoint, fixedPoints);
      print b;
      if (a and b) then (
      limit=limitLinearSeries(193,61,movingPoint, fixedPoints);
      limit== conjIdeal(193,61,{movingPoint} | fixedPoints)
      )
      )