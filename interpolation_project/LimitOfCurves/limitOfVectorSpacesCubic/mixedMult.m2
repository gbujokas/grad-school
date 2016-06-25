--Setup: Degree d curves, 
--       
--       

--prime=101;
prime =641;
--prime=4289

F=ZZ/prime;

redMap= map(F,ZZ) --reductionMap
--F=QQ
--Can change to QQ or a higher prime.

R=F[x,y,z,t];
Ez= y^2 * z - x^3 - x* z^2 -- homogeneous version of E

-- randomPoint() gives a random point on curve E

randomPointList= n -> (
     if (n==1) then
     {randomPoint()}
     else
     {randomPoint()}|randomPointList(n-1)
  )

randomPoint = () -> (use R; randomPointLoop(randomCoord(), 0)) ;

randomCoord= () -> random(1,prime);

randomPointLoop= (x0, y0) ->  
     (if(sub(Ez,{x=>x0, y =>y0, z=>1}) % prime ==0) 
	      then  (redMap x0,redMap y0,redMap 1) 
	      else (if(y0 == prime) 
      		     then randomPoint()     
      		     else randomPointLoop(x0,y0+1)))


recursionLimit=100000
--tail optimization problem...

---interpolation conditions

makePair = (m) -> (m, randomPoint())

InterpolationProblem = new Type of List

newProblem = (d,m,listMult) -> new InterpolationProblem from
                               {d, makePair(m), makePair \ listMult};

regen=method();


movingPoint=method();
fixedPoints=method();
allPoints=method();

interpolationMatrix=method();
limitLinearSeries=method();
dimLimitLinearSeries=method();

numExpDim=method();
expDim=method();
k=method();
limitProblem=method();
conjLimitLinearSeries=method();
conjMult=method();

reorder= (problem)->(
     	  newOrder = random(allPoints problem);
        new InterpolationProblem from (degree problem, first newOrder, drop( newOrder, {0,0})))

getResidualCurve= (problem)->(
     limitIdeal= limitLinearSeries problem;
     pol=(gens limitIdeal)_0_0;
     pol/(Ez^(conjMult problem))
     )


			       
degree InterpolationProblem := problem -> problem#0;
movingPoint InterpolationProblem := problem -> problem#1;
fixedPoints InterpolationProblem := problem -> problem#2;
allPoints InterpolationProblem := problem -> {movingPoint problem} | (fixedPoints problem) ;

regen InterpolationProblem :=problem -> newProblem(degree problem, first (movingPoint problem),
     first \ (fixedPoints problem))

--- interpolation conditions:
 
 I=ideal (x,y,z);
 
 monomialsOfDeg= (d) -> gens I^d; 
 partials= (m) -> gens I^(m-1);
 
 
 M=(d,m)->diff(transpose partials(m),monomialsOfDeg(d)); --sort of the Jacobian matrix
 
 
-- F[t]; -- t is the family parameter

-- apply M to at a point point=(x0,y0,z0)
 subM=(d) -> ((m,point) ->  sub(M(d,m),{x=>point#0, y=>point#1,z=>point#2})) ;  
   
-- apply M to a family (t+x0,t+y0,t+z0)   
 degenM= (d) -> ((m,point) ->(sub(M(d,m), {x=>point#0+t,y=>point#1+t,z=>point#2+t})));
 
-- interpolation matrix concatenates all interpolation conditions at fixedPoints, and at the movingPoint 
 fixedInterpolationMatrix=(d, listMult) -> fold((a,b) -> a||b, subM(d) \  listMult); 
 interpolationMatrix InterpolationProblem := problem -> ((degenM(degree problem)) (movingPoint problem) || 
      fixedInterpolationMatrix(degree problem ,fixedPoints problem));    
 
 -- here A is the interpolationMatrix.
 getFamily= gens @@ kernel;
 getCentralFiber= (A) -> sub( getFamily(A), {t=>0});
 getLimitLinearSeries= (d,A) -> ideal (monomialsOfDeg(d) * getCentralFiber(A));  
 getDimLimitLinearSeries=  numgens @@ source @@ getFamily;
 getLinearSeries= (d,A) -> ideal  (monomialsOfDeg(d) * getFamily(A)); 
 
-- applying to interpolationMatrix:

 limitLinearSeries InterpolationProblem := problem -> getLimitLinearSeries(degree problem, 
                                            interpolationMatrix problem);
 dimLimitLinearSeries InterpolationProblem := problem ->
                                getDimLimitLinearSeries(interpolationMatrix(problem));
 
-- getting linearSeries for fixed point
 
 fixedLinearSeries=  (problem) -> getLinearSeries(degree problem, 
      fixedInterpolationMatrix(degree problem,allPoints problem));
 dimFixedLinearSeries=  (problem) -> getDimLimitLinearSeries(fixedInterpolationMatrix(degree problem,allPoints problem));
 
 
 -- Conjectural results:

 plus1Choose2 = (m) -> (m+1)*m /2 ;
 sumInt = (a,b) -> a+b;
 
 numExpDim InterpolationProblem := problem  -> (plus1Choose2((degree problem) +1) -
          fold(sumInt, (plus1Choose2 @@ first \ allPoints(problem))));
     
 expDim InterpolationProblem := problem  -> if numExpDim(problem)<0 then 0 else numExpDim(problem);
 
 k InterpolationProblem := problem -> fold(sumInt, (first \ allPoints(problem))) - 3* (degree problem) ;
 
 newMult= (k, m) -> if(m >= 2*k +1) then m- 2*k-1 else 2*k-m ;
 newPair= (k) ->( (m, point) -> (newMult(k, m), point) );
 
 
 limitProblem InterpolationProblem := problem -> new InterpolationProblem from
          {degree problem - 3*(2*(k problem) +1),
	       (newPair(k problem)) (movingPoint problem),
	       (newPair(k problem)) \ (fixedPoints problem)};

 conjMult InterpolationProblem := problem -> ( (degree problem) - (degree (limitProblem problem)))/3 ;
 
 
 conjLimitLinearSeries InterpolationProblem := problem -> (if( degree (limitProblem problem) < 0) then ideal(R)
                                 else Ez^(conjMult problem) * fixedLinearSeries( limitProblem problem));
 

 -- Tool for checking conjecture:
 checkConjecture =  (problem) -> (if(expDim(problem)==dimLimitLinearSeries(problem)) then limitLinearSeries(problem) == conjLimitLinearSeries(problem)
      else checkConjecture(regen problem)); 
 
 -- Automated testing
 -- which pairs should we test
 --valid= (d,m) -> ((numExpDim(d,m-1)>=0) and (conjMult(d,m)>0))     
 --valid= (d,m) -> true     
 
 --runtests= () -> (
 --    movingPoint=randomPoint();     
 --     <<"Moving point:"<<movingPoint<<endl;

 --    fixedPoints=randomPointList(9);
 --    <<"Fixed points:"<<fixedPoints<<endl;
   
 --  <<"Checking conjecture: "<<endl;
   
 --  for d from 3 to 20 do{   
 --   <<"d="<<d<<endl;
   
 --   for m from 0 to d do
 --   if(valid(d,m)) then {
 --     if(checkConjecture(d,m,movingPoint,fixedPoints)) 
 --     then (<<"   m="<<m<<":true"<<endl; )     
 --     else { <<"ERROR! Failed for m="<<m<<endl; 
 --    	      break;
 --    	   }
 --    }
 --  }
 --  )
 
 evaluateToZero= (f,x0,y0,t0)->(sub(f, {x=>x0, y=>y0, t=>t0}) % prime ==0)
 
 familyEquation = (problem) -> (
       use R;
      mat= interpolationMatrix(problem);
      fam=getFamily (mat);
      famPol=(monomialsOfDeg (degree problem))* fam;
      polFam=famPol_0_0;
      RAff=F[x,y,t];
      f=map(RAff,R,{x,y,1,t});      
      f(polFam))
 
 singularAt=(pol, x0, y0, t0) ->(
      use RAff;
      px=diff(x, pol);
      py=diff(y, pol);
      pt=diff(t, pol);
      evaluateToZero(pol,x0, y0, t0)
      and
      evaluateToZero(px, x0, y0, t0)
      and
      evaluateToZero(py, x0, y0, t0)
      and
      evaluateToZero(pt, x0, y0, t0))
 
 computeSingularLocus=(problem) -> (
     use R;
     pointList=randomPointList(30);
     affPol= familyEquation(problem);
     passed=true;
     for point in pointList do
      if not (singularAt(affPol, point_0, point_1, 0)) then (
  	     <<"FAILED AT "<<point<<endl;
	     passed=false;);
	
     if passed then
         <<"PASSED"<<endl;	     
 
      --singIdeal=ideal (affPol, px,py,pt);
      --topComponents(singIdeal)
      --singularLocus(RAff/ (ideal affPol))
      )
 
 homogeneousProblem =(d,m) -> (newProblem(d,m, {m,m,m,m,m,m,m,m,m}))