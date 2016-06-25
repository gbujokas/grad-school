--Setup: Degree d curves, tangent to order d-a at [0:1:0] along V(x)
--       and with a a+k order multiple point at [t:0:1].
--       We want to know the limit of these as t goes to 0.

--F=ZZ/101
F=QQ
--Can change to QQ or a higher prime.

R=F[x,y,z]
I=ideal (x,y,z)
J=ideal (y,z)

monomialsTangentAtInf= (d,k,a) -> gens (x*I^(d-1) + z^(d-a) *J^a)
--monomials tangent to V(x) at [0:1:0] to order d-a

partials= (d,k,a) -> gens I^(k+a-1)
--list of partials tha should vanish at [t:0:1]

M=(d,k,a)->diff(transpose partials(d,k,a),monomialsTangentAtInf(d,k,a))
--matrix of partial derivatives

Ft=F[t]
Ev=map(Ft,R, {t,0,1})
--evaluation map at [t:0:1]

Mt=(d,k,a)->Ev(M(d,k,a))
--matrix of partial der. evaluated at [t:0:1]

N=(d,k,a) -> generators (kernel Mt(d,k,a))
N0=(d,k,a) -> sub(N(d,k,a), {t=>0})
--Do we need to cancel some factors of t here?

FastLimitCurve= (d,k,a) -> monomialsTangentAtInf(d,k,a) *N0(d,k,a)

--Checking we got it all
 dimension= (limitCurve)-> numgens source limitCurve
 expectedDimension= (d,k,a) -> (d+2)*(d+1)/2 - (a+k+1)*(a+k)/2 -d +a
 
 dimensionCheck=(d,k,a,limitCurve) ->(dimension(d,k,a)==expectedDimension(limitCurve))

--Checking that they work
tValue=()->3
valueCheck=(d,k,a,listN )->
(sub(diff(partials(d,k,a) ,monomialsTangentAtInf(d,k,a)*sub(listN,{t=>tValue()})), {x=>tValue(),y=>0,z=>1})==0)

safeN=(d,k,a) -> (listN=N(d,k,a); if valueCheck(d,k,a,listN) then listN else error "ERROR AT VALUE CHECK")
safeN0=(d,k,a)->sub(safeN(d,k,a),{t=>0})

LimitCurve=(d,k,a) ->  monomialsTangentAtInf(d,k,a) *safeN0(d,k,a)

--Checking conjectural answer

K=(ideal (x,y))

ConjectureIdeal=(d,k,a) ->(m:=a+k; ConjIdeal:= x*z^(d-m-1) * K^m; for i from m+1 when i<d do ConjIdeal=ConjIdeal+ x*z^(d-i-1) * K^i ; for i from 1 when i<a+2 do ConjIdeal=ConjIdeal +(ideal (x^(m-i+1) * y^(i-1) * z^(d-m)));ConjIdeal)

LimitIdeal=(d,k,a) -> (ideal LimitCurve(d,k,a))
CheckConjecture=(d,k,a)-> ConjectureIdeal(d,k,a)==LimitIdeal(d,k,a)




for d from 3 when d<30 do
 ( <<"Degree "<<d<<endl,
 for a from 1 when a<d+1 do
  for k from 1 when k+a<d do
       if(expectedDimension(d,k,a)>0) then 
           if(CheckConjecture(d,k,a)==false) then
	     <<"FALSE FOR "<< d<< " "<<k<< " "<<a<< endl;
	     )
	

	
	
       